#include "pch.h"
#include "Thread.h"

TThread::~TThread()
{
    if (joinable())
        join();
}

bool TThread::IsTerminated()
{
    // 
    if (m_Terminated)
    {
        m_Terminated = false;
        return true;
    }
    else
        return false;
}

void TThread::Terminate()
{
    m_Terminated = true;
}