//
// ArchiveStrategy.cpp
//
// $Id: //poco/Main/Data/src/ArchiveStrategy.cpp#8 $
//
// Library: Data
// Package: Logging
// Module:  ArchiveStrategy
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
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


#include "Poco/Data/ArchiveStrategy.h"
#include "Poco/Ascii.h"

namespace Poco {
namespace Data {


using namespace Keywords;

//
// ArchiveStrategy
//


const std::string ArchiveStrategy::DEFAULT_ARCHIVE_DESTINATION = "T_POCO_LOG_ARCHIVE";


ArchiveStrategy::ArchiveStrategy(const std::string& connector,
	const std::string& connect, 
	const std::string& source, 
	const std::string& destination):
	_connector(connector),
	_connect(connect),
	_source(source),
	_destination(destination)
{
	open();
}


ArchiveStrategy::~ArchiveStrategy()
{
}


void ArchiveStrategy::open()
{
	if (_connector.empty() || _connect.empty())
		throw IllegalStateException("Connector and connect string must be non-empty.");

	_pSession = new Session(_connector, _connect);
}


//
// ArchiveByAgeStrategy
//


ArchiveByAgeStrategy::ArchiveByAgeStrategy(const std::string& connector, 
	const std::string& connect, 
	const std::string& sourceTable, 
	const std::string& destinationTable):
	ArchiveStrategy(connector, connect, sourceTable, destinationTable)
{
	initStatements();
}


ArchiveByAgeStrategy::~ArchiveByAgeStrategy()
{
}


void ArchiveByAgeStrategy::archive()
{
	if (!session().isConnected()) open();

	DateTime now;
	_archiveDateTime = now - _maxAge;
	getCountStatement().execute();
	if (_archiveCount > 0)
	{
		getCopyStatement().execute();
		getDeleteStatement().execute();
	}
}


void ArchiveByAgeStrategy::initStatements()
{
	std::string src = getSource();
	std::string dest = getDestination();

	setCountStatement();
	_archiveCount = 0;
	std::string sql;
	Poco::format(sql, "SELECT COUNT(*) FROM %s WHERE DateTime < ?", src);
	getCountStatement() << sql, into(_archiveCount), use(_archiveDateTime);

	setCopyStatement();
	sql.clear();
	Poco::format(sql, "INSERT INTO %s SELECT * FROM %s WHERE DateTime < ?", dest, src);
	getCopyStatement() << sql, use(_archiveDateTime);

	setDeleteStatement();
	sql.clear();
	Poco::format(sql, "DELETE FROM %s WHERE DateTime < ?", src);
	getDeleteStatement() << sql, use(_archiveDateTime);
}


void ArchiveByAgeStrategy::setThreshold(const std::string& age)
{
	std::string::const_iterator it  = age.begin();
	std::string::const_iterator end = age.end();
	int n = 0;
	while (it != end && Ascii::isSpace(*it)) ++it;
	while (it != end && Ascii::isDigit(*it)) { n *= 10; n += *it++ - '0'; }
	while (it != end && Ascii::isSpace(*it)) ++it;
	std::string unit;
	while (it != end && Ascii::isAlpha(*it)) unit += *it++;
	
	Timespan::TimeDiff factor = Timespan::SECONDS;
	if (unit == "minutes")
		factor = Timespan::MINUTES;
	else if (unit == "hours")
		factor = Timespan::HOURS;
	else if (unit == "days")
		factor = Timespan::DAYS;
	else if (unit == "weeks")
		factor = 7*Timespan::DAYS;
	else if (unit == "months")
		factor = 30*Timespan::DAYS;
	else if (unit != "seconds")
		throw InvalidArgumentException("setMaxAge", age);
		
	_maxAge = factor * n;
}


} } // namespace Poco::Data
