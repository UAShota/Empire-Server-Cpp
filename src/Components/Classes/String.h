/////////////////////////////////////////////////
//
// Класс строки для упрощеной обработки
// Copyright(c) 2016 UAShota
//
// Rev F  2018.11.04
// Rev G  2018.11.10
//
/////////////////////////////////////////////////

#pragma once

// Класс реализации строки
class string
{
private:
	// Буфер
	char* m_Buffer = nullptr;
	// Длина
	int m_Length = 0;
public:
	// Пустой конструктор
	string();
	// Конструктор с буфера
	string(char* aBuffer, int aLength);
	// Базовый деструктор
	~string();
	// Текущая строка
	char* String();
	// Возвращение длины строки
	int Length();
};
