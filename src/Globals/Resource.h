//todo///////////////////////////////////////////////
//
// Модуль управления планетарной зоной
// Copyright(c) 2016 UAShota
//
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

namespace globals
{
    // Типы глобальных предметов
    namespace TItemType
    {
        enum E
        {
            Empty,
            Resource
        };
    }

    // Типы глобальных ресурсов
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