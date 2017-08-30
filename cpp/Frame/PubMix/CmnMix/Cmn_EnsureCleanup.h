/******************************************************************************
Module:  EnsureCleanup.h
Notices: Copyright (c) 2007 Jeffrey Richter & Christophe Nasarre
Purpose: These classes ensure object cleanup when an object goes out of scope.
         See Appendix A.
******************************************************************************/


#pragma once   // Include this header file once per compilation unit


///////////////////////////////////////////////////////////////////////////////


#include "Cmn_Hdr.h"
#include <boost/scope_exit.hpp>
#include "../DependSelfLib.h"

///////////////////////////////////////////////////////////////////////////////


// Data type representing the address of the object's cleanup function.
// I used UINT_PTR so that this class works properly in 64-bit Windows.
typedef VOID (WINAPI* PFNENSURECLEANUP)(UINT_PTR);


///////////////////////////////////////////////////////////////////////////////


// Each template instantiation requires a data type, address of cleanup 
// function, and a value that indicates an invalid value.
template<class TYPE, PFNENSURECLEANUP pfn, UINT_PTR tInvalid = NULL> 
class CEnsureCleanup {
public:
   // Default constructor assumes an invalid value (nothing to cleanup)
   CEnsureCleanup() { m_t = tInvalid; }

   // This constructor sets the value to the specified value
   CEnsureCleanup(TYPE t) : m_t((UINT_PTR) t) { }

   // The destructor performs the cleanup.
   ~CEnsureCleanup() { Cleanup(); }

   // Helper methods to tell if the value represents a valid object or not..
   BOOL IsValid() { return(m_t != tInvalid); }
   BOOL IsInvalid() { return(!IsValid()); }

   // Re-assigning the object forces the current object to be cleaned-up.
   TYPE operator=(TYPE t) { 
      Cleanup(); 
      m_t = (UINT_PTR) t;
      return(*this);  
   }

   // Returns the value (supports both 32-bit and 64-bit Windows).
   operator TYPE() { 
      return (TYPE) m_t;
   }
   operator TYPE() const{ 
	   return (TYPE) m_t;
   }

   // Cleanup the object if the value represents a valid object
   void Cleanup() { 
      if (IsValid()) {
         // In 64-bit Windows, all parameters are 64-bits, 
         // so no casting is required
         pfn(m_t);         // Close the object.
         m_t = tInvalid;   // We no longer represent a valid object.
      }
   }
   
private:
   UINT_PTR m_t;           // The member representing the object
};


///////////////////////////////////////////////////////////////////////////////


// Macros to make it easier to declare instances of the template 
// class for specific data types.

#define MakeCleanupClass(className, tData, pfnCleanup) \
   typedef CEnsureCleanup<tData, (PFNENSURECLEANUP) pfnCleanup> className;

#define MakeCleanupClassX(className, tData, pfnCleanup, tInvalid) \
   typedef CEnsureCleanup<tData, (PFNENSURECLEANUP) pfnCleanup, \
   (INT_PTR) tInvalid> className;


///////////////////////////////////////////////////////////////////////////////


// Instances of the template C++ class for common data types.
MakeCleanupClass(CEnsureCloseHandle,        HANDLE,    CloseHandle);
MakeCleanupClassX(CEnsureCloseFile,         HANDLE,    CloseHandle, 
   INVALID_HANDLE_VALUE);
MakeCleanupClass(CEnsureLocalFree,          HLOCAL,    LocalFree);
MakeCleanupClass(CEnsureGlobalFree,         HGLOBAL,   GlobalFree);
MakeCleanupClass(CEnsureRegCloseKey,        HKEY,      RegCloseKey);
//MakeCleanupClass(CEnsureCloseServiceHandle, SC_HANDLE, CloseServiceHandle);
MakeCleanupClass(CEnsureCloseWindowStation, HWINSTA,   CloseWindowStation);
MakeCleanupClass(CEnsureCloseDesktop,       HDESK,     CloseDesktop);
MakeCleanupClass(CEnsureUnmapViewOfFile,    PVOID,     UnmapViewOfFile);
MakeCleanupClass(CEnsureFreeLibrary,        HMODULE,   FreeLibrary);


///////////////////////////////////////////////////////////////////////////////


// Special class for releasing a reserved region.
// Special class is required because VirtualFree requires 3 parameters
class CEnsureReleaseRegion {
public:
   CEnsureReleaseRegion(PVOID pv = NULL);
   ~CEnsureReleaseRegion();

   PVOID operator=(PVOID pv);
   operator PVOID();
   void Cleanup();
   
private:
   PVOID m_pv;
};


///////////////////////////////////////////////////////////////////////////////


// Special class for freeing a block from a heap
// Special class is required because HeapFree requires 3 parameters
class CEnsureHeapFree {
public:
   CEnsureHeapFree(PVOID pv = NULL, HANDLE hHeap = GetProcessHeap()); 
   ~CEnsureHeapFree();

   PVOID operator=(PVOID pv);
   operator PVOID();
   void Cleanup();
   
private:
   HANDLE m_hHeap;
   PVOID m_pv;
};

//////////////////////////////////////////////////////////////////////////
//clean at scope exit
#pragma optimize("", off)
template<typename T>
class CleanAtScopeExit{
public:
	CleanAtScopeExit( const T& handler ) : handler_(handler){
		done_ = false;
	}
	~CleanAtScopeExit(){
		if (done_)
			return;
		handler_();
	}
	void operator() (){
		if (done_)
			return;
		done_ = true;
		handler_();
	}

private:
	const T&			handler_;
	bool				done_;
};
template<typename T>
CleanAtScopeExit<T> MakeCleanAtScopeExit( const T& handler ){
	assert(!"��BOOST_SCOPE_EXIT��BOOST_SCOPE_EXIT_ALL");
	return CleanAtScopeExit<T>(handler);
}
#pragma optimize("", on)
///////////////////////////////// End of File /////////////////////////////////
