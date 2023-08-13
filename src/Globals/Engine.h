/////////////////////////////////////////////////
//
// Модуль управления движком
// Copyright(c) 2016 UAShota
//
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

#include "Engine/Log.h"
#include "Engine/Server.h"
#include "Components/Database/DatasetMySQL.h"

class TEngine
{
public:
    static engine::TLog * Log;
    static database::TConnection * DB;
    static engine::TServer * Server;
public:
    static void Start();
    static void Stop();
};