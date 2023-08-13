//todo///////////////////////////////////////////////
//
// ������ ���������� ����������� �����
// Copyright(c) 2016 UAShota
//
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

namespace globals
{
    // ���� ���������� ���������
    namespace TItemType
    {
        enum E
        {
            Empty,
            Resource
        };
    }

    // ���� ���������� ��������
    namespace TResourceType
    {
        enum E
        {
            Empty,
            Vodorod,
            Xenon,
            Modules,
            Fuel,
            Gold,
            Titan,
            Kremniy,
            Antikristals,
            Antimatery,
            Metall,
            Electronic,
            Food,
            Protoplazma,
            Plazma
        };
    }

    class TResource
    {
    public:
        TResource() noexcept;
        ~TResource();
    };
}