/////////////////////////////////////////////////
//
// ������ ���������� ����������� �����
// Copyright(c) 2016 UAShota
//
// Rev F  2018.10.24
//
/////////////////////////////////////////////////

#pragma once

#include "Globals/Player.h"

namespace planetar
{
    // ����� ����������� ����
    class TPlanetar
    {
    private:
        // ������
        enum Errors
        {
            // ������ ���
            ERR_SUCCESS = 0,
            // ������� �� ���������
            ERR_SYSTEM_UNLOADED = 0x1F01,
            // ������� �� �������
            ERR_SYSTEM_UNAVAILABLE = 0x1F02
        };
        // ��������
        enum Commands
        {
            // ������ ���������� ���������
            CMD_AVAILABLE = 0x1F01,
            // �������� �� ���������
            CMD_SUBSCRIBE = 0x1F02
        };
    private:
        // ��������� ����� �������� ������
        transport::TSocketBuffer m_Buffer;
        // ������� ����� ���������
        globals::TPlayer * m_Player = nullptr;
    private:
        // ���������� ���� ���������� � ����� ��������������� �������
        globals::TPlayer * FindPlayer(int & aPlanetarID, int & aErrorCode);
        // �������� �����
        void LoadAutoPlanetars();
        // �������� �������� �����������
        void SendAvailable(int aPlanetarID, int aErrorCode);
        // ������� ����������� ���������� ������
        void CheckAvailable();
        // ����������� � ����������
        void Subscribe();
        // ��������������� ������� ����������
        void Retranslate();
    public:
        // ������ ������
        void Start();
        // ��������� ������
        void Stop();
        // ������� �� ���������
        void Command(transport::TSocketConnection * aConnection);
    };
}