#ifndef PCH_H
#define PCH_H

#include <stdio.h>
#ifdef use_mysql
#include <mysql.h>
#endif
#include <libpq-fe.h>

#include <map>
#include <thread>
#include <cmath>
#include <set>
#include <fstream>
#include <iostream>
#include <cstdarg>
#include <mutex>
#include <queue>
#include <list>
#include "memory.h"
#include <cassert>
#include <condition_variable>
#include <time.h>
#include <stdlib.h>

#define qwe "qwe"

#ifdef _WIN32
#include <filesystem>
#include <SDKDDKVer.h>
#define FD_SETSIZE 400
#include <winsock2.h>
#include <ws2def.h>
typedef fd_set Sockets;
#pragma comment (lib,"Ws2_32.lib")
#else
#include <filesystem>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define SocketCount 400
#define SOCKET_ERROR -1
typedef int SOCKET;
#define INVALID_SOCKET -1
typedef struct Sockets {
        u_int fd_count;               /* how many are SET? */
        SOCKET  fd_array[SocketCount];   /* an array of SOCKETs */
} Sockets;
typedef int errno_t;

errno_t fopen_s(FILE **f, const char *name, const char *mode) {
    errno_t ret = 0;
    assert(f);
    *f = fopen(name, mode);
    /* Can't be sure about 1-to-1 mapping of errno and MS' errno_t */
    if (!*f)
        ret = errno;
    return ret;
}

#endif



typedef unsigned int uint;
typedef unsigned long ulong;
typedef wchar_t wchar;
#undef min
#undef max
constexpr auto NOT_IMPLEMENTED = "Not implemented";

    template <typename... T>
void Log(T... args) {
    /*TEngine::Log->Write(__func__, __FILE__, __LINE__,false, ...);*/
    /*printf(args);*/
}

template <typename... T>
void LogError(...) {

}

#endif //PCH_H