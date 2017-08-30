#pragma once
/*
@author zhp
@date 2017/2/27 5:46
@purpose for string release
*/
#ifndef RC_INVOKED
#include <iterator>
#include "RXutility.h"
#include "RXstring.h"
#include <string>

#pragma pack(push,_CRT_PACKING)
#pragma warning(push,3)
#pragma push_macro("new")
#undef new

#pragma warning(disable: 4189)
#pragma warning(disable: 4172)

__RSTD_BEGIN_
// basic_string INSERTERS AND EXTRACTORS
template<class _Elem,
class _Traits,
class _Alloc> inline
	_STD basic_istream<_Elem, _Traits>& operator>>(
	_STD basic_istream<_Elem, _Traits>&& _Istr,
	basic_string<_Elem, _Traits, _Alloc>& _Str)
{	// extract a string
	typedef _STD ctype<_Elem> _Ctype;
	typedef _STD basic_istream<_Elem, _Traits> _Myis;
	typedef basic_string<_Elem, _Traits, _Alloc> _Mystr;
	typedef typename _Mystr::size_type _Mysizt;

	_STD ios_base::iostate _State = _STD ios_base::goodbit;
	bool _Changed = false;
	const typename _Myis::sentry _Ok(_Istr);

	if (_Ok)
	{	// state okay, extract characters
		const _Ctype& _Ctype_fac = _USE(_Istr.getloc(), _Ctype);
		_Str.erase();

		_TRY_IO_BEGIN
			_Mysizt _Size = 0 < _Istr.width()
			&& (_Mysizt)_Istr.width() < _Str.max_size()
			? (_Mysizt)_Istr.width() : _Str.max_size();
		typename _Traits::int_type _Meta = _Istr.rdbuf()->sgetc();

		for (; 0 < _Size; --_Size, _Meta = _Istr.rdbuf()->snextc())
			if (_Traits::eq_int_type(_Traits::eof(), _Meta))
			{	// end of file, quit
				_State |= _STD ios_base::eofbit;
				break;
			}
			else if (_Ctype_fac.is(_Ctype::space,
				_Traits::to_char_type(_Meta)))
				break;	// whitespace, quit
			else
			{	// add character to string
				_Str.append(1, _Traits::to_char_type(_Meta));
				_Changed = true;
			}
			_CATCH_IO_(_Istr)
	}

	_Istr.width(0);
	if (!_Changed)
		_State |= _STD ios_base::failbit;
	_Istr.setstate(_State);
	return (_Istr);
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	_STD basic_istream<_Elem, _Traits>& getline(
	_STD basic_istream<_Elem, _Traits>&& _Istr,
	basic_string<_Elem, _Traits, _Alloc>& _Str,
	const _Elem _Delim)
{	// get characters into string, discard delimiter
	typedef _STD basic_istream<_Elem, _Traits> _Myis;

	_STD ios_base::iostate _State = _STD ios_base::goodbit;
	bool _Changed = false;
	const typename _Myis::sentry _Ok(_Istr, true);

	if (_Ok)
	{	// state okay, extract characters
		_TRY_IO_BEGIN
			_Str.erase();
		const typename _Traits::int_type _Metadelim =
			_Traits::to_int_type(_Delim);
		typename _Traits::int_type _Meta = _Istr.rdbuf()->sgetc();

		for (;; _Meta = _Istr.rdbuf()->snextc())
			if (_Traits::eq_int_type(_Traits::eof(), _Meta))
			{	// end of file, quit
				_State |= _STD ios_base::eofbit;
				break;
			}
			else if (_Traits::eq_int_type(_Meta, _Metadelim))
			{	// got a delimiter, discard it and quit
				_Changed = true;
				_Istr.rdbuf()->sbumpc();
				break;
			}
			else if (_Str.max_size() <= _Str.size())
			{	// string too large, quit
				_State |= _STD ios_base::failbit;
				break;
			}
			else
			{	// got a character, add it to string
				_Str += _Traits::to_char_type(_Meta);
				_Changed = true;
			}
			_CATCH_IO_(_Istr)
	}

	if (!_Changed)
		_State |= _STD ios_base::failbit;
	_Istr.setstate(_State);
	return (_Istr);
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	_STD basic_istream<_Elem, _Traits>& getline(
	_STD basic_istream<_Elem, _Traits>&& _Istr,
	basic_string<_Elem, _Traits, _Alloc>& _Str)
{	// get characters into string, discard newline
	return (getline(_Istr, _Str, _Istr.widen('\n')));
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	_STD basic_istream<_Elem, _Traits>& operator>>(
	_STD basic_istream<_Elem, _Traits>& _Istr,
	basic_string<_Elem, _Traits, _Alloc>& _Str)
{	// extract a string
	return (_STD move(_Istr) >> _Str);
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	_STD basic_istream<_Elem, _Traits>& getline(
	_STD basic_istream<_Elem, _Traits>& _Istr,
	basic_string<_Elem, _Traits, _Alloc>& _Str,
	const _Elem _Delim)
{	// get characters into string, discard delimiter
	return (getline(_STD move(_Istr), _Str, _Delim));
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	_STD basic_istream<_Elem, _Traits>& getline(
	_STD basic_istream<_Elem, _Traits>& _Istr,
	basic_string<_Elem, _Traits, _Alloc>& _Str)
{	// get characters into string, discard newline
	return (getline(_STD move(_Istr), _Str, _Istr.widen('\n')));
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	_STD basic_ostream<_Elem, _Traits>& operator<<(
	_STD basic_ostream<_Elem, _Traits>& _Ostr,
	const basic_string<_Elem, _Traits, _Alloc>& _Str)
{	// insert a string
	typedef _STD basic_ostream<_Elem, _Traits> _Myos;
	typedef basic_string<_Elem, _Traits, _Alloc> _Mystr;
	typedef typename _Mystr::size_type _Mysizt;

	_STD ios_base::iostate _State = _STD ios_base::goodbit;
	_Mysizt _Size = _Str.size();
	_Mysizt _Pad = _Ostr.width() <= 0 || (_Mysizt)_Ostr.width() <= _Size
		? 0 : (_Mysizt)_Ostr.width() - _Size;
	const typename _Myos::sentry _Ok(_Ostr);

	if (!_Ok)
		_State |= _STD ios_base::badbit;
	else
	{	// state okay, insert characters
		_TRY_IO_BEGIN
			if ((_Ostr.flags() & _STD ios_base::adjustfield) != _STD ios_base::left)
				for (; 0 < _Pad; --_Pad)	// pad on left
					if (_Traits::eq_int_type(_Traits::eof(),
						_Ostr.rdbuf()->sputc(_Ostr.fill())))
					{	// insertion failed, quit
						_State |= _STD ios_base::badbit;
						break;
					}

		if (_State == _STD ios_base::goodbit
			&& _Ostr.rdbuf()->sputn(_Str.c_str(), (streamsize)_Size)
			!= (streamsize)_Size)
			_State |= _STD ios_base::badbit;
		else
			for (; 0 < _Pad; --_Pad)	// pad on right
				if (_Traits::eq_int_type(_Traits::eof(),
					_Ostr.rdbuf()->sputc(_Ostr.fill())))
				{	// insertion failed, quit
					_State |= _STD ios_base::badbit;
					break;
				}
		_Ostr.width(0);
		_CATCH_IO_(_Ostr)
	}

	_Ostr.setstate(_State);
	return (_Ostr);
}

// sto* NARROW CONVERSIONS

#define _STRTO_LL	_strtoi64
#define _STRTO_ULL	_strtoui64
#define _STRTO_F	strtod
#define _STRTO_LD	strtod

#define _WCSTO_LL	_wcstoi64
#define _WCSTO_ULL	_wcstoui64
#define _WCSTO_F	wcstod
#define _WCSTO_LD	wcstod

inline int stoi(const string& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert string to int
	const char *_Ptr = _Str.c_str();
	char *_Eptr;
	errno = 0;
	long _Ans = _CSTD strtol(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_STD _Xinvalid_argument("invalid stoi argument");
	if (errno == ERANGE || _Ans < INT_MIN != INT_MAX < _Ans)
		_STD _Xout_of_range("stoi argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return ((int)_Ans);
}

inline long stol(const string& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert string to long
	const char *_Ptr = _Str.c_str();
	char *_Eptr;
	errno = 0;
	long _Ans = _CSTD strtol(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_STD _Xinvalid_argument("invalid stol argument");
	if (errno == ERANGE)
		_STD _Xout_of_range("stol argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline unsigned long stoul(const string& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert string to unsigned long
	const char *_Ptr = _Str.c_str();
	char *_Eptr;
	errno = 0;
	unsigned long _Ans = _CSTD strtoul(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_STD _Xinvalid_argument("invalid stoul argument");
	if (errno == ERANGE)
		_STD _Xout_of_range("stoul argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline _Longlong stoll(const string& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert string to long long
	const char *_Ptr = _Str.c_str();
	char *_Eptr;
	errno = 0;
	_Longlong _Ans = _CSTD _STRTO_LL(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_STD _Xinvalid_argument("invalid stoll argument");
	if (errno == ERANGE)
		_STD _Xout_of_range("stoll argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline _ULonglong stoull(const string& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert string to unsigned long long
	const char *_Ptr = _Str.c_str();
	errno = 0;
	char *_Eptr;
	_ULonglong _Ans = _CSTD _STRTO_ULL(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_STD _Xinvalid_argument("invalid stoull argument");
	if (errno == ERANGE)
		_STD _Xout_of_range("stoull argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline float stof(const string& _Str, size_t *_Idx = 0)
{	// convert string to float
	const char *_Ptr = _Str.c_str();
	errno = 0;
	char *_Eptr;
	float _Ans = (float)_CSTD _STRTO_F(_Ptr, &_Eptr);

	if (_Ptr == _Eptr)
		_STD _Xinvalid_argument("invalid stof argument");
	if (errno == ERANGE)
		_STD _Xout_of_range("stof argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline double stod(const string& _Str, size_t *_Idx = 0)
{	// convert string to double
	const char *_Ptr = _Str.c_str();
	errno = 0;
	char *_Eptr;
	double _Ans = _CSTD strtod(_Ptr, &_Eptr);

	if (_Ptr == _Eptr)
		_STD _Xinvalid_argument("invalid stod argument");
	if (errno == ERANGE)
		_STD _Xout_of_range("stod argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline long double stold(const string& _Str, size_t *_Idx = 0)
{	// convert string to long double
	const char *_Ptr = _Str.c_str();
	errno = 0;
	char *_Eptr;
	long double _Ans = _CSTD _STRTO_LD(_Ptr, &_Eptr);

	if (_Ptr == _Eptr)
		_STD _Xinvalid_argument("invalid stold argument");
	if (errno == ERANGE)
		_STD _Xout_of_range("stold argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

// sto* WIDE CONVERSIONS
inline int stoi(const wstring& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert wstring to int
	const wchar_t *_Ptr = _Str.c_str();
	wchar_t *_Eptr;
	errno = 0;
	long _Ans = _CSTD wcstol(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_STD _Xinvalid_argument("invalid stoi argument");
	if (errno == ERANGE || _Ans < INT_MIN != INT_MAX < _Ans)
		_STD _Xout_of_range("stoi argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return ((int)_Ans);
}

inline long stol(const wstring& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert wstring to long
	const wchar_t *_Ptr = _Str.c_str();
	wchar_t *_Eptr;
	errno = 0;
	long _Ans = _CSTD wcstol(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_STD _Xinvalid_argument("invalid stol argument");
	if (errno == ERANGE)
		_STD _Xout_of_range("stol argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline unsigned long stoul(const wstring& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert wstring to unsigned long
	const wchar_t *_Ptr = _Str.c_str();
	wchar_t *_Eptr;
	errno = 0;
	unsigned long _Ans = _CSTD wcstoul(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_STD _Xinvalid_argument("invalid stoul argument");
	if (errno == ERANGE)
		_STD _Xout_of_range("stoul argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline _Longlong stoll(const wstring& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert wstring to long long
	const wchar_t *_Ptr = _Str.c_str();
	wchar_t *_Eptr;
	errno = 0;
	_Longlong _Ans = _CSTD _WCSTO_LL(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_STD _Xinvalid_argument("invalid stoll argument");
	if (errno == ERANGE)
		_STD _Xout_of_range("stoll argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline _ULonglong stoull(const wstring& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert wstring to unsigned long long
	const wchar_t *_Ptr = _Str.c_str();
	errno = 0;
	wchar_t *_Eptr;
	_ULonglong _Ans = _CSTD _WCSTO_ULL(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_STD _Xinvalid_argument("invalid stoull argument");
	if (errno == ERANGE)
		_STD _Xout_of_range("stoull argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline float stof(const wstring& _Str, size_t *_Idx = 0)
{	// convert wstring to float
	const wchar_t *_Ptr = _Str.c_str();
	errno = 0;
	wchar_t *_Eptr;
	float _Ans = (float)_CSTD _WCSTO_F(_Ptr, &_Eptr);

	if (_Ptr == _Eptr)
		_STD _Xinvalid_argument("invalid stof argument");
	if (errno == ERANGE)
		_STD _Xout_of_range("stof argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline double stod(const wstring& _Str, size_t *_Idx = 0)
{	// convert wstring to double
	const wchar_t *_Ptr = _Str.c_str();
	errno = 0;
	wchar_t *_Eptr;
	double _Ans = _CSTD wcstod(_Ptr, &_Eptr);

	if (_Ptr == _Eptr)
		_STD _Xinvalid_argument("invalid stod argument");
	if (errno == ERANGE)
		_STD _Xout_of_range("stod argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline long double stold(const wstring& _Str, size_t *_Idx = 0)
{	// convert wstring to long double
	const wchar_t *_Ptr = _Str.c_str();
	errno = 0;
	wchar_t *_Eptr;
	long double _Ans = _CSTD _WCSTO_LD(_Ptr, &_Eptr);

	if (_Ptr == _Eptr)
		_STD _Xinvalid_argument("invalid stold argument");
	if (errno == ERANGE)
		_STD _Xout_of_range("stold argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

// to_string NARROW CONVERSIONS

#define _LLFMT	"%I64"

#define _TOSTRING(buf, fmt, val)	\
	sprintf_s(buf, sizeof (buf), fmt, val)

inline string to_string(int _Val)
{	// convert int to string
	char _Buf[2 * _MAX_INT_DIG];

	_CSTD _TOSTRING(_Buf, "%d", _Val);
	return (string(_Buf));
}

inline string to_string(unsigned int _Val)
{	// convert unsigned int to string
	char _Buf[2 * _MAX_INT_DIG];

	_CSTD _TOSTRING(_Buf, "%u", _Val);
	return (string(_Buf));
}

inline string to_string(long _Val)
{	// convert long to string
	char _Buf[2 * _MAX_INT_DIG];

	_CSTD _TOSTRING(_Buf, "%ld", _Val);
	return (string(_Buf));
}

inline string to_string(unsigned long _Val)
{	// convert unsigned long to string
	char _Buf[2 * _MAX_INT_DIG];

	_CSTD _TOSTRING(_Buf, "%lu", _Val);
	return (string(_Buf));
}

inline string to_string(_Longlong _Val)
{	// convert long long to string
	char _Buf[2 * _MAX_INT_DIG];

	_CSTD _TOSTRING(_Buf, _LLFMT "d", _Val);
	return (string(_Buf));
}

inline string to_string(_ULonglong _Val)
{	// convert unsigned long long to string
	char _Buf[2 * _MAX_INT_DIG];

	_CSTD _TOSTRING(_Buf, _LLFMT "u", _Val);
	return (string(_Buf));
}

inline string to_string(long double _Val)
{	// convert long double to string
	typedef _STD back_insert_iterator<string> _Iter;
	typedef _STD num_put<char, _Iter> _Nput;
	const _Nput& _Nput_fac = _STD use_facet<_Nput>(_STD locale());
	_STD ostream _Ios((_STD streambuf *)0);
	string _Str;

	_Ios.setf(_STD ios_base::fixed);
	_Nput_fac.put(_Iter(_Str), _Ios, ' ', _Val);
	return (_Str);
}

inline string to_string(double _Val)
{	// convert double to string
	return (to_string((long double)_Val));
}

inline string to_string(float _Val)
{	// convert float to string
	return (to_string((long double)_Val));
}

// to_wstring WIDE CONVERSIONS

#define _WLLFMT	L"%I64"

#define _TOWSTRING(buf, fmt, val)	\
	swprintf_s(buf, sizeof (buf) / sizeof (wchar_t), fmt, val)

inline wstring to_wstring(int _Val)
{	// convert int to wstring
	wchar_t _Buf[2 * _MAX_INT_DIG];

	_CSTD _TOWSTRING(_Buf, L"%d", _Val);
	return (wstring(_Buf));
}

inline wstring to_wstring(unsigned int _Val)
{	// convert unsigned int to wstring
	wchar_t _Buf[2 * _MAX_INT_DIG];

	_CSTD _TOWSTRING(_Buf, L"%u", _Val);
	return (wstring(_Buf));
}

inline wstring to_wstring(long _Val)
{	// convert long to wstring
	wchar_t _Buf[2 * _MAX_INT_DIG];

	_CSTD _TOWSTRING(_Buf, L"%ld", _Val);
	return (wstring(_Buf));
}

inline wstring to_wstring(unsigned long _Val)
{	// convert unsigned long to wstring
	wchar_t _Buf[2 * _MAX_INT_DIG];

	_CSTD _TOWSTRING(_Buf, L"%lu", _Val);
	return (wstring(_Buf));
}

inline wstring to_wstring(_Longlong _Val)
{	// convert long long to wstring
	wchar_t _Buf[2 * _MAX_INT_DIG];

	_CSTD _TOWSTRING(_Buf, _WLLFMT L"d", _Val);
	return (wstring(_Buf));
}

inline wstring to_wstring(_ULonglong _Val)
{	// convert unsigned long long to wstring
	wchar_t _Buf[2 * _MAX_INT_DIG];

	_CSTD _TOWSTRING(_Buf, _WLLFMT L"u", _Val);
	return (wstring(_Buf));
}

inline wstring to_wstring(long double _Val)
{	// convert long double to wstring
	typedef _STD back_insert_iterator<wstring> _Iter;
	typedef _STD num_put<wchar_t, _Iter> _Nput;
	const _Nput& _Nput_fac = _STD use_facet<_Nput>(_STD locale());
	_STD ostream _Ios((_STD streambuf *)0);
	wstring _Str;

	_Ios.setf(_STD ios_base::fixed);
	_Nput_fac.put(_Iter(_Str), _Ios, L' ', _Val);
	return (_Str);
}

inline wstring to_wstring(double _Val)
{	// convert double to wstring
	return (to_wstring((long double)_Val));
}

inline wstring to_wstring(float _Val)
{	// convert float to wstring
	return (to_wstring((long double)_Val));
}

template<class _Elem, class _Traits, class _Alloc>
_STD basic_string<_Elem, _Traits, _Alloc> to_std(const __RSTD__ basic_string<_Elem, _Traits, _Alloc>& v){
	_STD basic_string<_Elem, _Traits, _Alloc> res(v.begin(), v.end());
	return res;
}

template<class _Elem, class _Traits, class _Alloc>
__RSTD__ basic_string<_Elem, _Traits, _Alloc> from_std(const _STD basic_string<_Elem, _Traits, _Alloc>& v){
	__RSTD__ basic_string<_Elem, _Traits, _Alloc> res(v.begin(), v.end());
	return res;
}

_STD_END

#pragma pop_macro("new")
#pragma warning(pop)
#pragma pack(pop)
#endif /* RC_INVOKED */
