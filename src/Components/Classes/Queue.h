/////////////////////////////////////////////////
//
// Класс потокобезопасной очереди, реализация ожидания
// Copyright(c) 2016 UAShota
//
// Rev F  2018.11.04
// Rev G  2018.11.10
// Rev K  2023.05.16
//
/////////////////////////////////////////////////

#pragma once

#include "pch.h"

/**
 * Мьютекс очереди
 */
typedef std::mutex TAsyncMutex;

/**
 * RAII блокировщик мьютекса
 */
typedef std::unique_lock<TAsyncMutex> TAsyncLock;

/**
 * Класс потокобезопасной очереди
 */
template <typename T>
class TAsyncQueue
{
private:
    /**
     * Мьютекс блокировки доступа
     */
    TAsyncMutex m_MutexAccess;
    /**
     * Очередь 
     */
    std::queue<T> m_Queue;
protected:
    /**
     * Возвращение или выталкивание текущего объекта в очереди
     * @param  {aPeek} bool : возвращение вместо выталкивания
     */
    T GetContainer(bool aPeek)
    {
        TAsyncLock lock(m_MutexAccess);
        // Выделим элемент
        if (m_Queue.empty())
            return nullptr;
        else
        {
            T tmpResult = m_Queue.front();
            if (!aPeek)
                m_Queue.pop();
            return tmpResult;
        }
    }
public:
    // Добавление объекта в очередь
    void Push(T aContainer)
    {
        TAsyncLock lock(m_MutexAccess);
        m_Queue.push(aContainer);
    }

    // Выталкивание объекта из очереди
    T Pop()
    {
        return GetContainer(false);
    }

    // Возвращение текущего объекта в очереди
    T Peek()
    {
        return GetContainer(true);
    }
};

// Класс потокобезопасной очереди с ожиданием события
template <typename T>
class TAsyncQueueSignal : public TAsyncQueue<T>
{
private:
    // Мьютекс ожидания
    TAsyncMutex m_MutexSignal;
    // Светофор ожидания события
    std::condition_variable m_Signal;
protected:
    // Переопределенноый запрос объекта с учетом ожидания события
    T GetContainer(bool aPeek)
    {
        T tmpValue = TAsyncQueue<T>::GetContainer(aPeek);
        if (!tmpValue)
        {
            // Заблокируем мьютекс доступа
            TAsyncLock locker(m_MutexSignal);
            // Подождем появления сигнала
            m_Signal.wait(locker);
        }
        // Вернем
        return tmpValue;
    }
public:
    // Добавление в очередь
    void Push(T aContainer)
    {
        TAsyncQueue<T>::Push(aContainer);
        Awake();
    }
    // Событие пробуждения очереди
    void Awake()
    {
        m_Signal.notify_one();
    }
};
