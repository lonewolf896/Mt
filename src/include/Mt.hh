/*
	Mt.hh - Generic and core includes and definitions
*/
#pragma once
// Named this way because str is defined in a *lot* of
// the standard headers, so I had do improvise
#define mk__str(s) __mkstr(s)
#define __mkstr(s) #s

#include <iostream>
#include <string>
#include <iomanip>
#include <csignal>

#include <immintrin.h>

#include <core/Config.hh>
#include <core/lang/SParser.hh>

#define ERROR_SUCCESS 0
#define ERROR_FAILURE 1

#if !defined(VERSION)
#define VERSION "N/A"
#endif

#if defined(_MSC_VER)
#define COMPILER "MSVC " mk__str(_MSC_VER)
#elif defined(__clang__)
#define COMPILER "clang " __clang_version__
#elif defined(__GNUC__)
#define COMPILER "GCC " mk__str( __GNUC__) "." mk__str(__GNUC_MINOR__)  "." mk__str(__GNUC_PATCHLEVEL__)
#endif

#if defined(_DEBUG) || defined(DEBUG)
#define MODE "DEBUG"
#else
#define MODE "RELEASE"
#endif


#define VERSION_STRING "Mt: Simple math and linear algebra environment. " << std::endl << "\tVer " VERSION " (" COMPILER ") " MODE " Build"

#define QUOTE "\"I'm so clever that even I don't understand myself sometimes.\""


void Term(int Signal);
