#include "pch.h"
#include "Database.h"
#include "Components/Database/DatasetPostgreSQL.h"

namespace Engine
{
	void TDatabase::Start()
	{
		m_connection = new database::TConnectionPostgreSQL();
		m_connection->Connect();
	}

	void TDatabase::Stop()
	{
		m_connection->Disconnect();
		delete(m_connection);
	}

    template <typename... T>
	database::TDataset& TDatabase::Call(const char* aQuery, const char* aParams, T... args)
	{
		// Ðàçáåðåì ïàðàìåòðû
		/*va_list tmpList;
		va_start(tmpList, aParams);
		database::TDataset* tmpResult = m_connection->Call(aQuery, aParams, tmpList);
		va_end(tmpList);
		// Âåðíåì ðåçóëüòàò
		return *tmpResult;
         */
	}

	database::TDataset& TDatabase::Call(const char* aQuery)
	{
		return *m_connection->Call(aQuery, nullptr, nullptr);
	}
}