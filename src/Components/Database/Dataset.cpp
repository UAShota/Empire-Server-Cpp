#include "pch.h"
#include "Components/Classes/String.h"
#include "Globals/Engine.h"
#include "Dataset.h"

namespace database
{
    TDataset::~TDataset()
    {    
    }

    bool TDataset::ReadRow()
    {
        throw NOT_IMPLEMENTED;
    }

    int TDataset::ReadInt(const char * aFieldName)
    {
        throw NOT_IMPLEMENTED;
    }

    string & TDataset::ReadString(const char * aFieldName)
    {
        throw NOT_IMPLEMENTED;
    }

template <typename... T>
    TQuery::TQuery(const char * aQuery, const char * aFormat, T... args)
    {
        // Ðàçáåðåì ïàðàìåòðû
        va_list tmpList;
        va_start(tmpList, aFormat);
        m_Dataset = TEngine::DB->Call(aQuery, aFormat, tmpList);
        va_end(tmpList);
    }

    TQuery::TQuery(const char * aQuery)
    {
        m_Dataset = TEngine::DB->Call(aQuery, nullptr, nullptr);
    }

    TQuery::~TQuery()
    {
        delete(m_Dataset);
    }

    bool TQuery::ReadRow()
    {
        return m_Dataset->ReadRow();
    }

    int TQuery::ReadInt(const char * aFieldName)
    {
        return m_Dataset->ReadInt(aFieldName);
    }

    string & TQuery::ReadString(const char * aFieldName)
    {
        return m_Dataset->ReadString(aFieldName);
    }

    void TConnection::Connect()
    {
        throw NOT_IMPLEMENTED;
    }

    void TConnection::Disconnect()
    {
        throw NOT_IMPLEMENTED;
    }

    TDataset * TConnection::Call(const char * aQuery, const char * aFormat, va_list aParams)
    {
        throw NOT_IMPLEMENTED;
    }
}