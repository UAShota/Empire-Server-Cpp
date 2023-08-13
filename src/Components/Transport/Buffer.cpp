#include "pch.h"
#include "Buffer.h"

namespace transport
{
    TSocketBuffer::TSocketBuffer()
    {
        AllocMemory(iCapacity);
    }

    TSocketBuffer::TSocketBuffer(TSocketConnection * aSocketConnection)
    {
        AllocMemory(iCapacity);
        m_SocketConnection = aSocketConnection;
    }

    TSocketBuffer::TSocketBuffer(int aCommand)
    {
        AllocMemory(iCapacity);
        WriteCommand(aCommand);
    }

    TSocketBuffer::TSocketBuffer(TSocketBuffer * aBuffer)
    {
        WriteBuffer(aBuffer->Memory(), aBuffer->Size());
    }

    TSocketBuffer::~TSocketBuffer()
    {
        free(m_Memory);
    }

    TSocketConnection * TSocketBuffer::SocketConnection()
    {
        return m_SocketConnection;
    }

    char * TSocketBuffer::Memory()
    {
        return m_Memory;
    }

    int TSocketBuffer::Position()
    {
        return m_Position;
    }

    int TSocketBuffer::Size()
    {
        return m_Size;
    }

    void TSocketBuffer::AllocMemory(int aSize)
    {
        m_Memory = (char*)malloc(aSize);
        if (m_Memory)
            m_Capacity = aSize;
        else
            Log("Failed");
    }

    void TSocketBuffer::ReallocMemory(int aSize)
    {
        // Ïðîâåðèì íà âûõîä çà ïðåäåëû
        if (m_Size + aSize <= m_Capacity)
            return;
        // Ïåðåâûäåëèì ïàìÿòü
        m_Capacity += aSize + iCapacity;
        m_Memory = (char*)realloc(m_Memory, m_Capacity);
        m_Size = aSize;
        // Ïðîâåðèì âûäåëåíà ëè ïàìÿòü
        if (!m_Memory)
            Log("Failed");
    }

    void TSocketBuffer::Allocate()
    {
        m_Position = 0;
        // Ïðî÷èòàåì ðàçìåð áóôåðà
        int tmpSize = ReadInt(true);
        // Åñëè íóæíî çàãðóçèòü áîëüøå ÷åì åñòü, òî ðàñøèðÿåì
        ReallocMemory(tmpSize);
    }

    bool TSocketBuffer::Readable(int aSize)
    {
        return (aSize > 0) && (m_Position + aSize <= m_Size);
    }

    void TSocketBuffer::ReadBuffer(void * aValue, int aSize, bool aSkeepPointer)
    {
        // Ïðîâåðèì ãðàíèöû
        if (!Readable(aSize))
            Log("Not readable");
        // Ïîïðîáóåì ñêîïèðîâàòü
        else if (!memcpy(aValue, m_Memory + m_Position, aSize))
            Log("Failed");
        // Ñäâèíåì óêàçàòåëü
        else if (!aSkeepPointer)
            m_Position += aSize;
    }

    int TSocketBuffer::ReadInt(bool aSkipPointer)
    {
        int tmpSize = sizeof(int);
        int tmpValue = 0;
        ReadBuffer(&tmpValue, tmpSize, aSkipPointer);
        return tmpValue;
    }

    int TSocketBuffer::ReadInt()
    {
        return ReadInt(false);
    }

    int TSocketBuffer::PeekCommand()
    {
        return ReadInt(true);
    }

    int TSocketBuffer::ReadCommand()
    {
        return ReadInt(false);
    }

    string & TSocketBuffer::ReadString()
    {
        // Ñ÷èòàåì äëèíó ñòðîêè        
        int tmpLen = ReadInt();
        char * tmpBuf = nullptr;/* (char*)malloc(tmpLen);*/
        // Ñêîïèðóåì
        ReadBuffer(tmpBuf, tmpLen);
        // Âåðíåì
        return *(new string(tmpBuf, tmpLen));
    }

    void TSocketBuffer::WriteBuffer(void * aBuffer, int aSize, int aPosition)
    {
        // Ïðîâåðèì äîñòóïíîñòü ïàìÿòè
        ReallocMemory(aSize);
        // Çàïèøåì â òåêóùóþ èëè â óêàçàííóþ ïîçèöèþ
        if (!memcpy(m_Memory + (!aPosition ? m_Position : aPosition), aBuffer, aSize))
            Log("Failed");
        // Ñäâèíåì óêàçàòåëü è óâåëè÷èì ðàçìåð
        else if (!aPosition)
        {
            m_Position += aSize;
            m_Size += aSize;
        }
    }

    void TSocketBuffer::WriteBuffer(TSocketBuffer * aBuffer)
    {
        WriteBuffer(aBuffer->Memory(), aBuffer->Size());
    }

    void TSocketBuffer::WriteCommand(int aCommand)
    {
        m_CommandPos = m_Position;
        WriteInt(0);
        WriteInt(aCommand);
    }

    void TSocketBuffer::WriteInt(int aValue, int aPosition)
    {
        WriteBuffer(&aValue, sizeof(int), aPosition);
    }

    void TSocketBuffer::WriteInt(int aValue)
    {
        WriteInt(aValue, 0);
    }

    void TSocketBuffer::WriteBool(bool aValue)
    {
        WriteBuffer(&aValue, sizeof(bool));
    }

    void TSocketBuffer::WriteString(string & aValue)
    {
        int tmpLength = aValue.Length();
        WriteBuffer(&tmpLength, sizeof(int));
        WriteBuffer(aValue.String(), tmpLength);
    }

    void TSocketBuffer::Reset(bool aSkipSize)
    {
        m_Position = 0;
        if (!aSkipSize)
            m_Size = 0;
    }

    void TSocketBuffer::Commit()
    {
        WriteInt(m_Size - sizeof(int), m_CommandPos);
    }
}