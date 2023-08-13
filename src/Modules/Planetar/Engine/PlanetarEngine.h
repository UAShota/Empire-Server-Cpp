//todo///////////////////////////////////////////////
//
// ������ ���������� ����������� �����
// Copyright(c) 2016 UAShota
//
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

#include "Globals/Player.h"
#include "Modules/Planetar/Protocol/PlanetarProtocolReader.h"
#include "Modules/Planetar/Protocol/PlanetarProtocolWriter.h"

namespace planetar
{
    // ����� ����������� ���� ��������� ����������
    class TPlanetarEngine
    {
    private:
        // ������ ������
        TThread m_Thread;
        // ������� ����������� ���������
        bool m_Available = false;
        // ������ ������
        TPlanet::Map m_Planets;

        // ������ �� ���������� ������ ������
        globals::TPlayer * m_Player = nullptr;
        // ������������ � ��������� �������
           /*Clients: TPlClientsDict;
                // ���������� ��������
           ControlBuildings: TPlanetarBuildingsController;
                // ��������� ������
           ControlPlanets: TPlanetarPlanetsController;
                // ���������� ��������
           ControlShips: TPlanetarShipsController;
                // ���������� ��������
           ControlStorages: TPlanetarStorageController;
           */        
           // ���������� ����������� ������
        int MannedCount = 0;
        // ����� ���������� ��������
        int TimePulsarActive = 0;
        // ����� ���������� ��
        int TimeWormholeActive = 0;
        // ����� �������� ��
        int TimeWormholeOpen = 0;
        // ��������� ����������
           /*WorkerShips: TPlanetarWorkerShips;
                // ��������� ������
           WorkerPlanets: TPlanetarWorkerPlanets;
           */
           // ����� ������
        TPlanetarProtocolReader m_SocketReader;
        // ����� ������
        TPlanetarProtocolWriter m_SocketWriter;
        // ������ ��������� �� ���������
        int m_SizeX = 0;
        // ������ ��������� �� �����������
        int m_SizeY = 0;
    private:
        // ���� ��������� ���� ���� ������ ������
        static void Execute(TPlanetarEngine * aInstance);
    private:
        // �������� ���������� ���������
        void LoadParams();
        // ������ ������
        void Work();
    public:
        TPlanetarEngine(class globals::TPlayer * aPlayer);
        ~TPlanetarEngine();
        // ������ ��������� �� X
        int SizeX();
        // ������ ��������� �� Y
        int SizeY();
        // ������� �������
        TPlanet::Map Planets();
        // ������� ������������ ���������
        bool Available();
        // ������� � ������� ���������
        bool Command(class globals::TPlayer * aPlayer);
        // ����������� � �������
        void Subscribe(globals::TPlayer * aPlayer);
        // ���������� �� �������
        void Unsubscribe(globals::TPlayer * aPlayer);
    };
}