/////////////////////////////////////////////////
//
// Êîíòðîëëåð óïðàâëåíèÿ äîñòóïîì ê ÁÄ
// Copyright(c) 2016 UAShota
//
// Rev D  2018.03.13
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

#include "Components/Database/Dataset.h"

namespace Engine
{
    // Êîíòðîëëåð óïðàâëåíèÿ äîñòóïîì ê ÁÄ
    class TDatabase
    {
    private:
        // Êîííåêòîð
        database::TConnection * m_connection = nullptr;
    public:
        // Ñòàðò
        void Start();
        // Îñòàíîâêà
        void Stop();
            template <typename... T>
        // Âûçîâ õðàíèìîé ïðîöåäóðû ñ ïàðàìåòðàìè
        database::TDataset & Call(const char * aQuery, const char * aParams, T... args);
        // Âûçîâ õðàíèìîé ïðîöåäóðû ñ ïàðàìåòðàìè
        database::TDataset & Call(const char * aQuery);
    };
}