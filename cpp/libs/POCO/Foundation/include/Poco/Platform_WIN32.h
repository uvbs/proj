//
// Platform_WIN32.h
//
// $Id: //poco/1.4/Foundation/include/Poco/Platform_WIN32.h#2 $
//
// Library: Foundation
// Package: Core
// Module:  Platform
//
// Platform and architecture identification macros
// and platform-specific definitions for Windows.
//
// Copyright (c) 2004-2007, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Foundation_Platform_WIN32_INCLUDED
#define Foundation_Platform_WIN32_INCLUDED


#include "Poco/UnWindows.h"

#ifndef _WIN32_WINNT
// determine the real version
#if defined(_WIN32_WINNT_WIN8)
	//Windows 8	_WIN32_WINNT_WIN8 (0x0602)
	#ifdef _WIN32_WINNT
		#undef _WIN32_WINNT
	#endif
	#define _WIN32_WINNT _WIN32_WINNT_WIN8
#elif defined(_WIN32_WINNT_WIN7)
	//Windows 7	_WIN32_WINNT_WIN7 (0x0601)
	#ifdef _WIN32_WINNT
		#undef _WIN32_WINNT
	#endif
	#define _WIN32_WINNT _WIN32_WINNT_WIN7
#elif defined (_WIN32_WINNT_WS08)
	//Windows Server 2008 _WIN32_WINNT_WS08 (0x0600)
	#ifdef _WIN32_WINNT
		#undef _WIN32_WINNT
	#endif
	#define _WIN32_WINNT _WIN32_WINNT_WS08
#elif defined (_WIN32_WINNT_VISTA)
	//Windows Vista	_WIN32_WINNT_VISTA (0x0600)
	#ifdef _WIN32_WINNT
		#undef _WIN32_WINNT
	#endif
	#define _WIN32_WINNT _WIN32_WINNT_VISTA
#elif defined (_WIN32_WINNT_LONGHORN)
	//Windows Vista	and server 2008 Development _WIN32_WINNT_LONGHORN (0x0600)
	#ifdef _WIN32_WINNT
		#undef _WIN32_WINNT
	#endif
	#define _WIN32_WINNT _WIN32_WINNT_LONGHORN
#elif defined (_WIN32_WINNT_WS03)
	//Windows Server 2003 with SP1,
	//Windows XP with SP2 _WIN32_WINNT_WS03 (0x0502)
	#ifdef _WIN32_WINNT
		#undef _WIN32_WINNT
	#endif
	#define _WIN32_WINNT _WIN32_WINNT_WS03
#elif defined (_WIN32_WINNT_WINXP)
	//Windows Server 2003, Windows XP _WIN32_WINNT_WINXP (0x0501)
	#ifdef _WIN32_WINNT
		#undef _WIN32_WINNT
	#endif
	#define _WIN32_WINNT _WIN32_WINNT_WINXP
#elif defined (_WIN32_WINNT_WIN2K)
	//Windows 2000 _WIN32_WINNT_WIN2K (0x0500)
	#ifdef _WIN32_WINNT
		#undef _WIN32_WINNT
	#endif
	#define _WIN32_WINNT _WIN32_WINNT_WIN2K
#elif defined (WINVER)
	#ifdef _WIN32_WINNT
		#undef _WIN32_WINNT
	#endif
	#define _WIN32_WINNT WINVER
#endif

#endif


#if defined(_MSC_VER) && !defined(POCO_MSVC_SECURE_WARNINGS) && !defined(_CRT_SECURE_NO_DEPRECATE)
	#define _CRT_SECURE_NO_DEPRECATE
#endif 


// Verify that we're built with the multithreaded 
// versions of the runtime libraries
#if defined(_MSC_VER) && !defined(_MT)
	#error Must compile with /MD, /MDd, /MT or /MTd
#endif


// Check debug/release settings consistency
#if defined(NDEBUG) && defined(_DEBUG)
	#error Inconsistent build settings (check for /MD[d])
#endif


#if (_MSC_VER >= 1300) && (_MSC_VER < 1400) // Visual Studio 2003, MSVC++ 7.1
	#define POCO_MSVS_VERSION 2003
	#define POCO_MSVC_VERSION 71
#elif (_MSC_VER >= 1400) && (_MSC_VER < 1500) // Visual Studio 2005, MSVC++ 8.0
	#define POCO_MSVS_VERSION 2005
	#define POCO_MSVC_VERSION 80
#elif (_MSC_VER >= 1500) && (_MSC_VER < 1600) // Visual Studio 2008, MSVC++ 9.0
	#define POCO_MSVS_VERSION 2008
	#define POCO_MSVC_VERSION 90
#elif (_MSC_VER >= 1600) && (_MSC_VER < 1700) // Visual Studio 2010, MSVC++ 10.0
	#define POCO_MSVS_VERSION 2010
	#define POCO_MSVC_VERSION 100
#elif (_MSC_VER >= 1700) && (_MSC_VER < 1800) // Visual Studio 2012, MSVC++ 11.0
	#define POCO_MSVS_VERSION 2012
	#define POCO_MSVC_VERSION 110
#elif (_MSC_VER >= 1800) && (_MSC_VER < 1900) // Visual Studio 2013, MSVC++ 12.0
	#define POCO_MSVS_VERSION 2013
	#define POCO_MSVC_VERSION 120
#endif


// Unicode Support
#if defined(UNICODE) && !defined(POCO_WIN32_UTF8)
	#define POCO_WIN32_UTF8
#endif


// Turn off some annoying warnings
//#if defined(_MSC_VER)
#if defined(_MSC_VER_Unuse__)		//这是zhp加的，不能取消这些警告
	#pragma warning(disable:4018)	// signed/unsigned comparison
	#pragma warning(disable:4250)	// VC++ 11.0: inheriting from std stream classes produces C4250 warning;
									// see <http://connect.microsoft.com/VisualStudio/feedback/details/733720/inheriting-from-std-fstream-produces-c4250-warning>
	#pragma warning(disable:4251)	// ... needs to have dll-interface warning
	#pragma warning(disable:4275)	// non dll-interface class 'std::exception' used as base for dll-interface class 'Poco::Exception'
	#pragma warning(disable:4344)	// behavior change: use of explicit template arguments results in call to '...' but '...' is a better match
	#pragma warning(disable:4351)	// new behavior: elements of array '...' will be default initialized
	#pragma warning(disable:4355)	// 'this' : used in base member initializer list
	#pragma warning(disable:4675)	// resolved overload was found by argument-dependent lookup
	#pragma warning(disable:4996)	// VC++ 8.0 deprecation warnings
#endif


// Enable C++11 support for VS 2010 and newer
#if defined(_MSC_VER) && (_MSC_VER >= 1700) && !defined(POCO_ENABLE_CPP11)
	#define POCO_ENABLE_CPP11
#endif


#if defined(__INTEL_COMPILER)
	#pragma warning(disable:1738) // base class dllexport/dllimport specification differs from that of the derived class
	#pragma warning(disable:1478) // function ... was declared "deprecated"
	#pragma warning(disable:1744) // field of class type without a DLL interface used in a class with a DLL interface
#endif


#endif // Foundation_Platform_WIN32_INCLUDED
