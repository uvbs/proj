// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <config/targetver.h>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <afxwin.h>         // MFC core and standard components

#include <Common/UsefulFunc.h>
#include <Common/Hooker.h>
#include <boost/thread.hpp>
#include <Common/LogOut.h>
#include <Socket/PocoMore.h>

//functions
//ִ���߳�
boost::thread& GetImplThread();

#include <config/AdjustWin32.h>
#include <DependLibs.h>

bool GWndExecSync( const std::function<bool()>& func );
TimeDuration& GetGlobalTimeDuration();