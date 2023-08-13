#include <fcntl.h>

#include "Socket.h"

namespace transport
{
	void TSocket::Error()
	{
		/*char * tmpError = NULL;
		FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, WSAGetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPSTR)*tmpError, 0, NULL);
		LogError(tmpError);
		LocalFree(tmpError);*/
	}

	void TSocket::Start(int aPort, ISocketWrapper* aWrapper)
	{
		m_Wrapper = aWrapper;

		// Ïîïðîáóåì îïðåäåëèòü ñîêåò
		m_ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (m_ServerSocket == INVALID_SOCKET)
		{
			Error();
			exit(1);
		}

		// Ïîïðîáóåì ïåðåâåñòè â íåáëîêèðóþùèé ðåæèì
		if (!SetNonBlock(m_ServerSocket))
		{
			Error();
			exit(1);
		}

		// Îïðåäåëèì áèíäèíãè
		sockaddr_in tmpAddr;
		tmpAddr.sin_family = AF_INET;
		tmpAddr.sin_port = htons(aPort);
		tmpAddr.sin_addr.s_addr = INADDR_ANY;

		// Ïîïðîáóåì çàáèíäèòü
		if (bind(m_ServerSocket, (sockaddr*)&tmpAddr, sizeof(tmpAddr)) == SOCKET_ERROR)
		{
			Error();
			exit(1);
		}

		// Ïîäíèìàåì ñëóøàòåëü
		if (listen(m_ServerSocket, SOMAXCONN) == SOCKET_ERROR)
		{
			Error();
			exit(1);
		}

		// Äîáàâèì ñåáÿ â êëèåíòû
		m_Clients.insert_or_assign(m_ServerSocket, nullptr);

		// Çàïóñòèì ïîòîê çàïèñè
		(std::thread&)m_ThreadWrite = std::thread(ExecuteWrite, this);
		// Çàïóñòèì ïîòîê ÷òåíèÿ
		(std::thread&)m_ThreadRead = std::thread(ExecuteRead, this);
	}

	void TSocket::Stop()
	{
		m_ThreadRead.Terminate();
		m_ThreadWrite.Terminate();
#ifdef WIN32	
		closesocket(m_ServerSocket);
#else
		close(m_ServerSocket);
#endif        
	}

	bool TSocket::SetNonBlock(SOCKET aSocket)
	{
		u_long tmpMode = 0;
#ifdef _WIN32
		return (ioctlsocket(aSocket, FIONBIO, &tmpMode) == 0) ? true : false;
#else
		int flags = fcntl(aSocket, F_GETFL, 0);
		if (flags == -1) return false;
		flags = flags | O_NONBLOCK;
		return (fcntl(aSocket, F_SETFL, flags) == 0) ? true : false;
#endif
	}

	void TSocket::SetClients()
	{
		// Çàáüåì êëèåíòîâ â ýòîò áîëüíîé fd_set
		SOCKET* tmpSocket = m_Sockets.fd_array;
		for (auto tmpIt : m_Clients)
			*tmpSocket++ = tmpIt.first;
		m_Sockets.fd_count = m_Clients.size();
	}

	void TSocket::Connect()
	{
		SOCKADDR_IN tmpAddr;
		int tmpSize = sizeof(tmpAddr);
		// Íîâîå ñîåäèíåíèå
		SOCKET tmpSocket = accept(m_ServerSocket, (SOCKADDR*)&tmpAddr, &tmpSize);
		if (tmpSocket == SOCKET_ERROR)
		{
			Error();
			return;
		}
		// Ïåðåêëþ÷èì íîâûé ñîêåò â íåáëîêèðóþùèé ðåæèì
		if (!SetNonBlock(tmpSocket))
		{
			Error();
			return;
		}
		// Äîáàâèì êëèåíòà â ñïèñîê
		TSocketConnection* tmpConnection = new TSocketConnection(tmpSocket, tmpAddr);
		m_Clients.insert_or_assign(tmpSocket, tmpConnection);
		m_Wrapper->OnConnect(tmpConnection);
	}

	void TSocket::Disconnect(SOCKET aSocket, TSocketConnection* aConnection)
	{
		m_Wrapper->OnDisconnect(aConnection);
		m_Clients.erase(aSocket);
		delete(aConnection);
	}

	void TSocket::ExecuteRead(TSocket* aInstance)
	{
		aInstance->WorkRead();
	}

	void TSocket::ExecuteWrite(TSocket* aInstance)
	{
		aInstance->WorkWrite();
	}

	void TSocket::WorkRead()
	{
		// Ïîëíûé æèçíåííûé öèêë
		while (!m_ThreadRead.IsTerminated())
		{
			//  Êîïèðóåì íàáîð ÷òîáû íå æäàòü îáíóëåíèÿ
			SetClients();

			//  Æäåì ñîîáùåíèÿ ñ ñîêåòà
			if (!select(0, &m_Sockets, NULL, NULL, NULL))
			{
				Error();
				continue;
			}

			// Ïðèçíàê îñòàíîâêè
			if (m_ThreadRead.IsTerminated())
				break;

			// Ïðîâåðèì îñòàëüíûå ïîäêëþ÷åíèÿ
			for (u_int tmpI = 0; tmpI < m_Sockets.fd_count; tmpI++)
			{
				// Çàãîòîâèì ïàðàìåòðû
				SOCKET tmpSocket = m_Sockets.fd_array[tmpI];
				// Ïîäêëþ÷åíèå
				if (tmpSocket == m_ServerSocket)
				{
					Connect();
					continue;
				}
				// Íàéäåì êëèåíòà
				TSocketConnection* tmpConnection = m_Clients.find(tmpSocket)->second;
				// Çàïðîñèì âåñü áóôåð
				int tmpBytesRead = recv(tmpSocket, m_Buffer, I_BUFFER_LENGTH, 0);
				// Åñëè ïóñòîé - êëèåíò ðàçîðâàë ñâÿçü, èíà÷å ñ÷èòàåì áóôåð êëèåíòó
				if (tmpBytesRead == 0)
					Disconnect(tmpSocket, tmpConnection);
				else
					m_Wrapper->OnRead(tmpConnection, m_Buffer, tmpBytesRead);
			}
		}
	}

	void TSocket::WorkWrite()
	{
		TSocketConnection* tmpConnection = nullptr;
		TSocketBuffer* tmpBuffer = nullptr;
		// Ïîêà èäåò ïîòîê, îáðàáîòàåì î÷åðåäü
		while (!m_ThreadWrite.IsTerminated())
		{
			m_Wrapper->OnWrite(*&tmpConnection);
			if (!tmpConnection)
				continue;
			// Çàáåðåì ïàêåò 
		   /* tmpBuffer = tmpConnection->QueueWrite.Pop();
			// Ïðîáóåì îòïðàâèòü ïàêåò
			int tmpCount = send(tmpConnection->UID(), tmpBuffer->Memory(), tmpBuffer->Size(), 0);*/
		}
	}

	TSocketConnection::TSocketConnection(SOCKET aUID, SOCKADDR_IN& aAddr)
	{
		char tmpBuf[I_IP_LENGTH];
		sprintf_s(tmpBuf, "%d.%d.%d.%d",
			aAddr.sin_addr.S_un.S_un_b.s_b1,
			aAddr.sin_addr.S_un.S_un_b.s_b2,
			aAddr.sin_addr.S_un.S_un_b.s_b3,
			aAddr.sin_addr.S_un.S_un_b.s_b4
		);
		m_IP = *(new string((char*)tmpBuf, I_IP_LENGTH));
		m_UID = aUID;
	}

	SOCKET TSocketConnection::UID()
	{
		return m_UID;
	}

	string TSocketConnection::IP()
	{
		return m_IP;
	}

	void TSocketConnection::Send(TSocketBuffer* aBuffer)
	{
		m_QueueWrite.Push(aBuffer);
	}

	void ISocketWrapper::OnConnect(TSocketConnection* aConnection)
	{
		throw NOT_IMPLEMENTED;
	}

	void ISocketWrapper::OnRead(TSocketConnection* aConnection, char* aBuffer, int aBufferSize)
	{
		throw NOT_IMPLEMENTED;
	}

	void ISocketWrapper::OnWrite(TSocketConnection*& aConnection)
	{
		//   throw NOT_IMPLEMENTED;
	}

	void ISocketWrapper::OnDisconnect(TSocketConnection* aConnection)
	{
		throw NOT_IMPLEMENTED;
	}
}