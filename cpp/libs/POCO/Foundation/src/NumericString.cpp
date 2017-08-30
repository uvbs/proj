//
// NumericString.h
//
// $Id: //poco/1.4/Foundation/src/NumericString.cpp#1 $
//
// Library: Foundation
// Package: Core
// Module:  NumericString
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

// +++ double conversion +++
#include "diy-fp.cc"
#include "cached-powers.cc"
#include "bignum-dtoa.cc"
#include "bignum.cc"
#include "fast-dtoa.cc"
#include "fixed-dtoa.cc"
#include "strtod.cc"
#include "double-conversion.cc"
// --- double conversion ---

#include "Poco/NumericString.h"
poco_static_assert(POCO_MAX_FLT_STRING_LEN == double_conversion::kMaxSignificantDecimalDigits);
#include "Poco/String.h"
#include <memory>
#include <cctype>


namespace {


void pad(std::string& str, int precision, int width, char prefix = ' ', char decSep = '.')
	/// Pads the string with prefix space and postfix 0.
	/// Alternative prefix (e.g. zero instead of space) can be supplied by caller.
	/// Used only internally.
{
	// these cases should never happen, if they do, it's a library bug
	poco_assert_dbg (precision > 0);
	poco_assert_dbg (str.length());

	std::string::size_type decSepPos = str.find(decSep);
	if (decSepPos == std::string::npos)
	{
		str.append(1, '.');
		decSepPos = str.size() - 1;
	}

	std::string::size_type frac = str.length() - decSepPos - 1;

	std::string::size_type ePos = str.find_first_of("eE");
	std::auto_ptr<std::string> eStr;
	if (ePos != std::string::npos)
	{
		eStr.reset(new std::string(str.substr(ePos, std::string::npos)));
		frac -= eStr->length();
		str = str.substr(0, str.length() - eStr->length());
	}

	if (frac != precision)
	{
		if (frac < precision)
			str.append(precision - frac, '0');
		else if ((frac > precision) && (decSepPos != std::string::npos)) 
			str = str.substr(0, decSepPos + 1 + precision);
	}

	if (eStr.get()) str += *eStr;

	if (width && (str.length() < width)) str.insert(str.begin(), width - str.length(), prefix);
}


void insertThousandSep(std::string& str, char thSep, char decSep = '.')
	/// Inserts thousand separators.
	/// Used only internally.
{
	poco_assert (decSep != thSep);

	std::string::size_type exPos = str.find('e');
	std::string::size_type decPos = str.find(decSep);
	// there's no rinsert, using forward iterator to go backwards
	std::string::iterator it = str.end();
	std::string::iterator begin = str.begin();
	if (exPos != std::string::npos)
	{
		while (it != begin)
		{
			--it;
			if ((*it == 'e') || (*it == 'E')) break;
		}
	}
	if (decPos != std::string::npos)
	{
		while (it != begin)
		{
			--it;
			if (*it == decSep) break;
		}
	}
	int thCount = 0;
	for (; it != begin; --it)
	{
		if (!std::isdigit(*it)) continue;
		if (++thCount == 3)
		{
			it = str.insert(it, thSep);
			thCount = 0;
		}
	}
}


} // namespace


namespace Poco {


void floatToStr(char* buffer, int bufferSize, float value, int lowDec, int highDec)
{
	using namespace double_conversion;

	StringBuilder builder(buffer, bufferSize);
	int flags = DoubleToStringConverter::UNIQUE_ZERO |
		DoubleToStringConverter::EMIT_POSITIVE_EXPONENT_SIGN;
	DoubleToStringConverter dc(flags, POCO_FLT_INF, POCO_FLT_NAN, POCO_FLT_EXP, lowDec, highDec, 0, 0);
	dc.ToShortestSingle(value, &builder);
	builder.Finalize();
}


std::string& floatToStr(std::string& str, float value, int precision, int width, char thSep, char decSep)
{
	if (!decSep) decSep = '.';
	if (precision == 0) value = std::floor(value);

	char buffer[POCO_MAX_FLT_STRING_LEN];
	floatToStr(buffer, POCO_MAX_FLT_STRING_LEN, value);
	str = buffer;
	
	if (decSep && (decSep != '.') && (str.find('.') != std::string::npos))
		replaceInPlace(str, '.', decSep);

	if (thSep) insertThousandSep(str, thSep, decSep);
	if (precision > 0 || width) pad(str, precision, width, ' ', decSep ? decSep : '.');
	return str;
}


void doubleToStr(char* buffer, int bufferSize, double value, int lowDec, int highDec)
{
	using namespace double_conversion;

	StringBuilder builder(buffer, bufferSize);
	int flags = DoubleToStringConverter::UNIQUE_ZERO |
		DoubleToStringConverter::EMIT_POSITIVE_EXPONENT_SIGN;
	DoubleToStringConverter dc(flags, POCO_FLT_INF, POCO_FLT_NAN, POCO_FLT_EXP, lowDec, highDec, 0, 0);
	dc.ToShortest(value, &builder);
	builder.Finalize();
}


std::string& doubleToStr(std::string& str, double value, int precision, int width, char thSep, char decSep)
{
	if (!decSep) decSep = '.';
	if (precision == 0) value = std::floor(value);

	char buffer[POCO_MAX_FLT_STRING_LEN];
	doubleToStr(buffer, POCO_MAX_FLT_STRING_LEN, value);
	str = buffer;
	
	if (decSep && (decSep != '.') && (str.find('.') != std::string::npos))
		replaceInPlace(str, '.', decSep);

	if (thSep) insertThousandSep(str, thSep, decSep);
	if (precision > 0 || width) pad(str, precision, width, ' ', decSep ? decSep : '.');
	return str;
}


float strToFloat(const char* str)
{
	using namespace double_conversion;

	int processed;
	int flags = StringToDoubleConverter::ALLOW_LEADING_SPACES |
		StringToDoubleConverter::ALLOW_TRAILING_SPACES;
	StringToDoubleConverter converter(flags, 0.0, Single::NaN(), POCO_FLT_INF, POCO_FLT_NAN);
	float result = converter.StringToFloat(str, static_cast<int>(strlen(str)), &processed);
	return result;
}


double strToDouble(const char* str)
{
	using namespace double_conversion;
	int processed;
	int flags = StringToDoubleConverter::ALLOW_LEADING_SPACES |
		StringToDoubleConverter::ALLOW_TRAILING_SPACES;
	StringToDoubleConverter converter(flags, 0.0, Double::NaN(), POCO_FLT_INF, POCO_FLT_NAN);
	double result = converter.StringToDouble(str, static_cast<int>(strlen(str)), &processed);
	return result;
}


bool strToFloat(const std::string& str, float& result, char decSep, char thSep)
{
	using namespace double_conversion;

	std::string tmp(str);
	trimInPlace(tmp);
	removeInPlace(tmp, thSep);
	removeInPlace(tmp, 'f');
	replaceInPlace(tmp, decSep, '.');
	result = strToFloat(tmp.c_str());
	return !FPEnvironment::isInfinite(result) &&
		!FPEnvironment::isNaN(result);
}


bool strToDouble(const std::string& str, double& result, char decSep, char thSep)
{
	if (str.empty()) return false;

	using namespace double_conversion;

	std::string tmp(str);
	trimInPlace(tmp);
	removeInPlace(tmp, thSep);
	replaceInPlace(tmp, decSep, '.');
	removeInPlace(tmp, 'f');
	result = strToDouble(tmp.c_str());
	return !FPEnvironment::isInfinite(result) &&
		!FPEnvironment::isNaN(result);
}


} // namespace Poco
