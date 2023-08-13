/////////////////////////////////////////////////
//
// Àáñòðàêòíûé ìîäóëü óïðàâëåíèÿ äîñòóïîì ê ÁÄ
// Copyright(c) 2016 UAShota
//
// Rev D  2018.03.13
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

#include "Components/Classes/String.h"

namespace database
{
    // Äàòàñåò, âûïîëíÿþùèé çàïðîñû
    class TDataset
    {
    public:
        // Äåñòðóêòîð
        virtual ~TDataset();
        // ×òåíèå î÷åðåäíîé çàïèñè
        virtual bool ReadRow();
        // Âîçâðàò çíà÷åíèÿ êàê Int
        virtual int ReadInt(const char * aFieldName);
        // Âîçâðàò çíà÷åíèÿ êàê String
        virtual string & ReadString(const char * aFieldName);
    };

    // Êîíòåéíåð äëÿ ñîçäàíèÿ òàáëèö íà ñòåêå
    class TQuery
    {
    private:
        // Òàáëèöà çàïðîñà
        database::TDataset * m_Dataset = nullptr;
    public:
        // Âûçîâ õðàíèìîé ïðîöåäóðû ñ ïàðàìåòðàìè
        template <typename... T>
        TQuery(const char * aQuery, const char * aParams, T... args);
        // Âûçîâ õðàíèìîé ïðîöåäóðû áåç ïàðàìåòðîâ
        TQuery(const char * aQuery);
        // Äåñòðóêòîð
        ~TQuery();
        // ×òåíèå î÷åðåäíîé çàïèñè
        bool ReadRow();
        // Âîçâðàò çíà÷åíèÿ êàê Int
        int ReadInt(const char * aFieldName);
        // Âîçâðàò çíà÷åíèÿ êàê String
        string & ReadString(const char * aFieldName);
    };

    // Êîííåêòîð ê ÁÄ
    class TConnection
    {
    protected:
        // Ïîðò
        const int I_PORT = 3306;
        // Ñåðâåð
        const char * S_HOST = "localhost";
        // Ëîãèí
        const char * S_USERNAME = "root";
        // Ïàðîëü
        const char * S_PWD = "root";
        // Áàçà äàííûõ
        const char * S_DATABASE = "planetar";
    public:
        // Ñîåäèíåíèå
        virtual void Connect();
        // Îòñîåäèíåíèå
        virtual void Disconnect();
        // Âûçîâ õðàíèìîé ïðîöåäóðû ñ ïàðàìåòðàìè
        virtual TDataset * Call(const char * aQuery, const char * aFormat, va_list aParams);
    };
}