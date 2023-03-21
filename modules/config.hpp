//
// Created by grimreaper on 3/18/23.
//
#ifndef THESCYTHE_CONFIG_HPP
#define THESCYTHE_CONFIG_HPP


#ifdef INFO_OS_WINDOWS
/// DO NOT NEED TO WRITE #include<windows.h> INSIDE YOUR SOURCE CODE, it may cause redefinition errors
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
    #include <iostream>
    #include <string>
    #include <array>
    #include <memory>
#elif defined(INFO_OS_LINUX)
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#elif defined(INFO_OS_OSX)
#include <sys/mman.h>
    #include <errno.h>
#endif

#include <string>
#include <exception>
#include <stdexcept>

namespace TheScythe
{
    typedef char                schar;
    typedef unsigned char       suchar;
    typedef unsigned int        suint;
    typedef size_t              ssize;
    typedef unsigned long       sulong;

    namespace Config
    {
        /// Maximum packet size
        const suint    MAX_TCP_PACKET_SIZE = 4069;
        /// Maximum file size
        const sulong    MAX_FILE_SIZE = 32 * 1024 * 1024 * sizeof(suchar); // 64 MB
        /// Maximum xml value size
        const ssize    MAX_XML_VALUE_SIZE = 4069;
    }
    namespace Core
    {
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
        /// Sleep for a number of miliseconds
        void sleep(sulong milisec)
        {
#ifdef INFO_OS_WINDOWS
            ::SleepEx(milisec, FALSE);// (float)milisec / 1000.f );
#else
            ::usleep( milisec * 1000);
#endif
        }
    }
}

#endif //THESCYTHE_CONFIG_HPP
