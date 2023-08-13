//todo///////////////////////////////////////////////
//
// ������ ���������� ����������� �����
// Copyright(c) 2016 UAShota
//
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

#include "Resource.h"

namespace globals
{
    // �������� �����
    class TStorageOwner
    {
    };

    // ���� ���������
    class TStorageHolder
    {
    private:
        TStorageOwner * m_Owner = nullptr;
    public:
        TResourceType::E Resource = TResourceType::Empty;
        int Count = 0;
        int Type = 0;
    public:
        void Update(TStorageHolder * aStorageHolder);
    };

    // ������ ���������
    class TStorage
    {
    public:
        std::vector<TStorageHolder> * Holders = {};
    };
}