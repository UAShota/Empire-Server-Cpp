/////////////////////////////////////////////////
//
// ����� ������ ��� ��������� ���������
// Copyright(c) 2016 UAShota
//
// Rev F  2018.11.04
// Rev G  2018.11.10
//
/////////////////////////////////////////////////

#pragma once

// ����� ���������� ������
class string
{
private:
	// �����
	char* m_Buffer = nullptr;
	// �����
	int m_Length = 0;
public:
	// ������ �����������
	string();
	// ����������� � ������
	string(char* aBuffer, int aLength);
	// ������� ����������
	~string();
	// ������� ������
	char* String();
	// ����������� ����� ������
	int Length();
};
