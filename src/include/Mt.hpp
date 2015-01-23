/*
	Mt.hpp - Generic and core includes and definitions
*/
#pragma once

#define xstr(s) str(s)
#define str(s) #s

#include <iostream>
#include <string>
#include <iomanip>

#include <core/Config.hpp>
#include "core/Scope.hpp"

#define ERROR_SUCCESS 0
#define ERROR_FAILURE 1

#if !defined(VERSION)
#define VERSION "N/A"
#endif

#if defined(_MSC_VER)
#define COMPILER "MSVC " xstr(_MSC_VER)
#elif defined(__GNUC__)
#define COMPILER "GCC " xstr( __GNUC__) "." xstr(__GNUC_MINOR__)  "." xstr(__GNUC_PATCHLEVEL__)
#endif

#if defined(_DEBUG) || defined(DEBUG)
#define MODE "DEBUG"
#else
#define MODE "RELEASE"
#endif


#define VERSION_STRING "Mt: Simple math and linear algebra environment. " << std::endl << "\tVer " VERSION " (" COMPILER ") " MODE " Build"

#define QUOTE "\"I'm so clever that even I don't understand myself sometimes.\""
