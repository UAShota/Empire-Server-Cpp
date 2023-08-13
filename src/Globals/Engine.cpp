#include "pch.h"
#include "Engine.h"
#include "Components/Database/DatasetPostgreSQL.h"

engine::TLog* TEngine::Log;
database::TConnection* TEngine::DB;
engine::TServer* TEngine::Server;

void TEngine::Start()
{
	std::cout << "Init log\n";
	Log = new engine::TLog();
	Log->Start();

	std::cout << "Init database\n";
	DB = new database::TConnectionPostgreSQL();
	DB->Connect();

	std::cout << "Init server\n";
	Server = new engine::TServer();
	Server->Start();
}

void TEngine::Stop()
{
	std::cout << "Stop Server\n";
	Server->Stop();
	delete(Server);

	std::cout << "Stop database\n";
	DB->Disconnect();
	delete(DB);

	std::cout << "Stop log\n";
	Log->Stop();
	delete(Log);
}