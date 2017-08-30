//
// SesssionHandle.h
//
// $Id: //poco/1.4/Data/MySQL/include/Poco/Data/MySQL/SessionHandle.h#1 $
//
// Library: Data
// Package: MySQL
// Module:  SessionHandle
//
// Definition of the SessionHandle class.
//
// Copyright (c) 2008, Applied Informatics Software Engineering GmbH.
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


#ifndef Data_MySQL_SessionHandle_INCLUDED
#define Data_MySQL_SessionHandle_INCLUDED

#include <mysql.h>
#include "Poco/Data/MySQL/MySQLException.h"

#include <vector>

namespace Poco {
namespace Data {
namespace MySQL {

class SessionHandle
	/// MySQL session handle
{
public:

	explicit SessionHandle(MYSQL* mysql);
		/// Creates session handle

	~SessionHandle();
		/// Destroy handle, close connection

	void init(MYSQL* mysql = 0);
		/// Initializes the handle iff not initialized.

	void options(mysql_option opt);
		/// Set connection options

	void options(mysql_option opt, bool b);
		/// Set connection options

	void options(mysql_option opt, const char* c);
		/// Set connection options

	void options(mysql_option opt, unsigned int i);
		/// Set connection options

	void connect(const char* host, const char* user, const char* password, const char* db, unsigned int port);
		/// Connect to server

	void close();
		/// Close connection

	void startTransaction();
		/// Start transaction

	void commit();
		/// Commit transaction

	void rollback();
		/// Rollback trabsaction

	operator MYSQL* ();

private:

	SessionHandle(const SessionHandle&);
	SessionHandle& operator=(const SessionHandle&);

private:

	MYSQL* _pHandle;
};


//
// inlines
//

inline SessionHandle::operator MYSQL* ()
{
	return _pHandle;
}


}}}

#endif // Data_MySQL_SessionHandle_INCLUDED
