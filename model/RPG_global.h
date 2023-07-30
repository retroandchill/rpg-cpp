//
// Created by fcors on 6/9/2023.
//
#pragma once

#ifdef RPG_SHARED
    #ifdef _WIN32
        #ifdef RPG_BUILD
            #define RPG_API __declspec(dllexport)
        #else
            #define RPG_API __declspec(dllimport)
        #endif
    #else
        #define RPG_API __attribute__((visibility("default")))
    #endif
#else
    #define RPG_API
#endif