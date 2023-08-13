#include "pch.h"
#include "Log.h"
#include "Components/Classes/Queue.h"

namespace engine
{
    void TLog::Start()
    {
        // ×èñòî äëÿ óäîáñòâà
        int tmpchar;
        // Ïîïðîáóåì ñîçäàòü êàòàëîã ëîãà
        std::string tmpDir = std::filesystem::current_path().string() + "/" + S_LOG_DIR;
        std::error_code tmpDirError;
        if (!std::filesystem::is_directory(tmpDir)
            && !std::filesystem::create_directory(tmpDir, tmpDirError))
        {
            std::cout << S_LOG_INIT << " ";
            std::cout << tmpDirError.value() << " ";
            std::cout << tmpDirError.message() << " ";
            std::cout << tmpDir;
            tmpchar = std::getchar();
            exit(tmpDirError.value());
        }
        // Ñôîðìèðóåì èìÿ ôàéëà ëîãà
        std::string tmpFileName = tmpDir + "/" + DateTme(S_LOG_NAME) + S_LOG_EXT;
        // Ïîïðîáóåì ñîçäàòü ëîã ôàéë
        errno_t tmpFileError = fopen_s(&m_File, tmpFileName.c_str(), "a+");
        if (tmpFileError != 0)
        {
            std::cout << S_LOG_INIT;
            std::cout << tmpFileError;
            std::cout << tmpFileName;
            tmpchar = std::getchar();
            exit(tmpDirError.value());
        }
    }

    void TLog::Stop()
    {
        if (m_File != 0)
            fclose(m_File);
    }

    const char * TLog::DateTme(const char * aFormat)
    {
        // Ïîëó÷èì âðåìÿ â ñåêóíäàõ
        time_t tmpRawTime = time(NULL);
        struct tm tmpTimeConnection;
        errno_t tmpErr = localtime_s(&tmpTimeConnection, &tmpRawTime);
        // Îòôîðìàòèðóåì äëÿ ëîãà
        strftime(m_FormatBuff, sizeof(m_FormatBuff), aFormat, &tmpTimeConnection);
        // Âåðíåì ïîëó÷åííóþ äàòó
        return m_FormatBuff;
    }

    inline void TLog::InternalWrite(const char * aValue)
    {
        fwrite(aValue, sizeof(char), strlen(aValue), m_File);
#ifndef NDEBUG
        std::cout << aValue;
#endif
    }

    void TLog::Write(const char * aMethod, const char * aFile, long aLine, bool aCritical, const char * aMessage, ...)
    {
        TAsyncLock lock(m_Mutex);
        // Çàïèøåì çàãîëîâîê
        InternalWrite(DateTme(S_LOG_ROW));
        InternalWrite(" | ");
        InternalWrite(aFile);
        InternalWrite(" | ");
        InternalWrite(aMethod);
        InternalWrite(":");
        /*_ltoa_s(aLine, m_FormatBuff, sizeof(m_FormatBuff), 10);*/
        InternalWrite(m_FormatBuff);
        InternalWrite(" | ");
        InternalWrite(aMessage);
        // Çàïèøåì ìàññèâ ïàðàìåòðîâ
        va_list tmpList;
        va_start(tmpList, aMessage);
        while (aMessage = va_arg(tmpList, char*))
        {
            InternalWrite(" | ");
            InternalWrite(aMessage);
        }
        va_end(tmpList);
        InternalWrite("\n");
        // Ñîõðàíèì â ôàéë
        fflush(m_File);
        // Åñëè êðèò - çàïðîñèì ââîä
        if (aCritical)
        {
            std::cout << "Critical, press return  for stopping.\n";
            int tmpchar = std::getchar();
        }
    }
}