#pragma once
/*
@author zhp
@date 2017/2/27 7:06
@purpose for bitset release
*/
#ifndef RC_INVOKED
#include "RString.h"
#include <iosfwd>
#include <bitset>

#pragma pack(push,_CRT_PACKING)
#pragma warning(push,3)
#pragma push_macro("new")
#undef new

#pragma warning(disable: 4127)

#pragma warning(disable: 6294)

__RSTD_BEGIN_
// TEMPLATE CLASS bitset
template<size_t _Bits>
class bitset
{	// store fixed-length sequence of Boolean elements
public:
	enum : size_t { _EEN_BITS = _Bits };	// helper for expression evaluator
	typedef typename _STD _If<_Bits <= 32, _Uint32t, _ULonglong>::type _Ty;


	typedef bool element_type;	// retained

	// CLASS reference
	class reference
	{	// proxy for an element
		friend class bitset<_Bits>;

	public:
		~reference() _NOEXCEPT
		{	// destroy the object
		}

		reference& operator=(bool _Val) _NOEXCEPT
		{	// assign Boolean to element
			_Pbitset->set(_Mypos, _Val);
			return (*this);
		}

			reference& operator=(const reference& _Bitref) _NOEXCEPT
		{	// assign reference to element
			_Pbitset->set(_Mypos, bool(_Bitref));
			return (*this);
		}

			reference& flip() _NOEXCEPT
		{	// complement stored element
			_Pbitset->flip(_Mypos);
			return (*this);
		}

			bool operator~() const _NOEXCEPT
		{	// return complemented element
			return (!_Pbitset->test(_Mypos));
		}

			operator bool() const _NOEXCEPT
		{	// return element
			return (_Pbitset->test(_Mypos));
		}

	private:
		reference() _NOEXCEPT
			: _Pbitset(0), _Mypos(0)
		{	// default construct
		}

		reference(bitset<_Bits>& _Bitset, size_t _Pos)
			: _Pbitset(&_Bitset), _Mypos(_Pos)
		{	// construct from bitset reference and position
		}

		bitset<_Bits> *_Pbitset;	// pointer to the bitset
		size_t _Mypos;	// position of element in bitset
	};

	bool at(size_t _Pos) const	// retained
	{	// subscript nonmutable sequence with checking
		return (test(_Pos));
	}

	reference at(size_t _Pos)	// retained
	{	// subscript mutable sequence with checking
		return (reference(*this, _Pos));
	}

	bool operator[](size_t _Pos) const
	{	// subscript nonmutable sequence
		return (test(_Pos));
	}

	reference operator[](size_t _Pos)
	{	// subscript mutable sequence
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (_Bits <= _Pos)
			_DEBUG_ERROR("bitset index outside range");

#elif __RSTD_ITERATOR_DEBUG_LEVEL__ == 1
		_SCL_SECURE_VALIDATE_RANGE(_Pos < _Bits);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		return (reference(*this, _Pos));
	}

	bitset() _NOEXCEPT
	{	// construct with all false values
		_Tidy();
	}

		bitset(_ULonglong _Val) _NOEXCEPT


	{	// construct from bits in unsigned long
		_Tidy();
		for (size_t _Pos = 0; _Val != 0 && _Pos < _Bits; _Val >>= 1, ++_Pos)
			if (_Val & 1)
				set(_Pos);
	}

#define _BITSET_SIZE_TYPE	\
	typename basic_string<_Elem, _Tr, _Alloc>::size_type

		template<class _Elem,
	class _Tr,
	class _Alloc>
		explicit bitset(const basic_string<_Elem, _Tr, _Alloc>& _Str,
		_BITSET_SIZE_TYPE _Pos = 0,
		_BITSET_SIZE_TYPE _Count = basic_string<_Elem, _Tr, _Alloc>::npos,
		_Elem _E0 = (_Elem)'0',
		_Elem _E1 = (_Elem)'1')
	{	// construct from [_Pos, _Pos + _Count) elements in string
		_Construct(_Str, _Pos, _Count, _E0, _E1);
	}

	template<class _Elem>
	explicit bitset(const _Elem *_Ptr,
		typename basic_string<_Elem>::size_type _Count =
		basic_string<_Elem>::npos,
		_Elem _E0 = (_Elem)'0',
		_Elem _E1 = (_Elem)'1')
	{	// initialize from NTBS
		_Construct(
			_Count == basic_string<_Elem>::npos
			? basic_string<_Elem>(_Ptr)
			: basic_string<_Elem>(_Ptr, _Count),
			0, _Count, _E0, _E1);
	}

	template<class _Elem,
	class _Tr,
	class _Alloc>
		void _Construct(
		const basic_string<_Elem, _Tr, _Alloc>& _Str,
		_BITSET_SIZE_TYPE _Pos,
		_BITSET_SIZE_TYPE _Count,
		_Elem _E0,
		_Elem _E1)
	{	// initialize from [_Pos, _Pos + _Count) elements in string
		typename basic_string<_Elem, _Tr, _Alloc>::size_type _Num;
		if (_Str.size() < _Pos)
			_Xran();	// _Pos off end
		if (_Str.size() - _Pos < _Count)
			_Count = _Str.size() - _Pos;	// trim _Count to size
		if (_Bits < _Count)
			_Count = _Bits;	// trim _Count to length of bitset
		_Tidy();

		for (_Pos += _Count, _Num = 0; _Num < _Count; ++_Num)
			if (_Str[--_Pos] == _E1)
				set(_Num);
			else if (_Str[_Pos] != _E0)
				_Xinv();
	}

	bitset<_Bits>& operator&=(const bitset<_Bits>& _Right) _NOEXCEPT
	{	// AND in _Right
		for (ptrdiff_t _Wpos = _Words; 0 <= _Wpos; --_Wpos)
		_Array[_Wpos] &= _Right._Getword(_Wpos);
		return (*this);
	}

		bitset<_Bits>& operator|=(const bitset<_Bits>& _Right) _NOEXCEPT
	{	// OR in _Right
		for (ptrdiff_t _Wpos = _Words; 0 <= _Wpos; --_Wpos)
		_Array[_Wpos] |= _Right._Getword(_Wpos);
		return (*this);
	}

		bitset<_Bits>& operator^=(const bitset<_Bits>& _Right) _NOEXCEPT
	{	// XOR in _Right
		for (ptrdiff_t _Wpos = _Words; 0 <= _Wpos; --_Wpos)
		_Array[_Wpos] ^= _Right._Getword(_Wpos);
		return (*this);
	}

		bitset<_Bits>& operator<<=(size_t _Pos) _NOEXCEPT
	{	// shift left by _Pos
		const ptrdiff_t _Wordshift = (ptrdiff_t)(_Pos / _Bitsperword);
		if (_Wordshift != 0)
			for (ptrdiff_t _Wpos = _Words; 0 <= _Wpos; --_Wpos)
				_Array[_Wpos] = _Wordshift <= _Wpos	// shift by words
				? _Array[_Wpos - _Wordshift] : (_Ty)0;

		if ((_Pos %= _Bitsperword) != 0)
		{	// 0 < _Pos < _Bitsperword, shift by bits
			for (ptrdiff_t _Wpos = _Words; 0 < _Wpos; --_Wpos)
				_Array[_Wpos] = (_Ty)((_Array[_Wpos] << _Pos)
				| (_Array[_Wpos - 1] >> (_Bitsperword - _Pos)));
			_Array[0] <<= _Pos;
		}
		_Trim();
		return (*this);
	}

		bitset<_Bits>& operator>>=(size_t _Pos) _NOEXCEPT
	{	// shift right by _Pos, first by words then by bits
		const ptrdiff_t _Wordshift = (ptrdiff_t)(_Pos / _Bitsperword);
		if (_Wordshift != 0)
			for (ptrdiff_t _Wpos = 0; _Wpos <= _Words; ++_Wpos)
				_Array[_Wpos] = _Wordshift <= _Words - _Wpos
				? _Array[_Wpos + _Wordshift] : (_Ty)0;

		if ((_Pos %= _Bitsperword) != 0)
		{	// 0 < _Pos < _Bitsperword, shift by bits
			for (ptrdiff_t _Wpos = 0; _Wpos < _Words; ++_Wpos)
				_Array[_Wpos] = (_Ty)((_Array[_Wpos] >> _Pos)
				| (_Array[_Wpos + 1] << (_Bitsperword - _Pos)));
			_Array[_Words] >>= _Pos;
		}
		return (*this);
	}

		bitset<_Bits>& set() _NOEXCEPT
	{	// set all bits true
		_Tidy((_Ty)~0);
		return (*this);
	}

		bitset<_Bits>& set(size_t _Pos,
		bool _Val = true)
	{	// set bit at _Pos to _Val
		if (_Bits <= _Pos)
			_Xran();	// _Pos off end
		if (_Val)
			_Array[_Pos / _Bitsperword] |= (_Ty)1 << _Pos % _Bitsperword;
		else
			_Array[_Pos / _Bitsperword] &= ~((_Ty)1 << _Pos % _Bitsperword);
		return (*this);
	}

	bitset<_Bits>& reset() _NOEXCEPT
	{	// set all bits false
		_Tidy();
		return (*this);
	}

		bitset<_Bits>& reset(size_t _Pos)
	{	// set bit at _Pos to false
		return (set(_Pos, false));
	}

	bitset<_Bits> operator~() const _NOEXCEPT
	{	// flip all bits
		return (bitset<_Bits>(*this).flip());
	}

		bitset<_Bits>& flip() _NOEXCEPT
	{	// flip all bits
		for (ptrdiff_t _Wpos = _Words; 0 <= _Wpos; --_Wpos)
		_Array[_Wpos] = (_Ty)~_Array[_Wpos];

		_Trim();
		return (*this);
	}

		bitset<_Bits>& flip(size_t _Pos)
	{	// flip bit at _Pos
		if (_Bits <= _Pos)
			_Xran();	// _Pos off end
		_Array[_Pos / _Bitsperword] ^= (_Ty)1 << _Pos % _Bitsperword;
		return (*this);
	}

	unsigned long to_ulong() const _NOEXCEPT
	{	// convert bitset to unsigned long
		_ULonglong _Val = to_ullong();
		unsigned long _Ans = (unsigned long)_Val;
		if (_Ans != _Val)
			_Xoflo();
		return (_Ans);
	}

		_ULonglong to_ullong() const _NOEXCEPT
	{	// convert bitset to unsigned long long
		static_assert(sizeof(_ULonglong) % sizeof(_Ty) == 0,
		"unsigned long long not multiple of _Ty");

		ptrdiff_t _Wpos = _Words;
		for (; (ptrdiff_t)(sizeof(_ULonglong) / sizeof(_Ty)) <= _Wpos;
			--_Wpos)
			if (_Array[_Wpos] != 0)
				_Xoflo();	// fail if any high-order words are nonzero

		_ULonglong _Val = _Array[_Wpos];
		for (; 0 <= --_Wpos;)
			_Val = ((_Val << (_Bitsperword - 1)) << 1) | _Array[_Wpos];
		return (_Val);
	}

		template<class _Elem,
	class _Tr,
	class _Alloc>
		basic_string<_Elem, _Tr, _Alloc>
		to_string(_Elem _E0 = (_Elem)'0',
		_Elem _E1 = (_Elem)'1') const
	{	// convert bitset to string
		basic_string<_Elem, _Tr, _Alloc> _Str;
		typename basic_string<_Elem, _Tr, _Alloc>::size_type _Pos;
		_Str.reserve(_Bits);

		for (_Pos = _Bits; 0 < _Pos;)
			if (test(--_Pos))
				_Str += _E1;
			else
				_Str += _E0;
		return (_Str);
	}

	template<class _Elem,
	class _Tr>
		basic_string<_Elem, _Tr, _STD allocator<_Elem> >
		to_string(_Elem _E0 = (_Elem)'0',
		_Elem _E1 = (_Elem)'1') const
	{	// convert bitset to string
		return (to_string<_Elem, _Tr, _STD allocator<_Elem> >(_E0, _E1));
	}

	template<class _Elem>
	basic_string<_Elem, _STD char_traits<_Elem>, _STD allocator<_Elem> >
		to_string(_Elem _E0 = (_Elem)'0',
		_Elem _E1 = (_Elem)'1') const
	{	// convert bitset to string
		return (to_string<_Elem, _STD char_traits<_Elem>,
			_STD allocator<_Elem> >(_E0, _E1));
	}

	string to_string(char _E0 = '0', char _E1 = '1') const
	{	// convert bitset to string
		return (to_string<char, _STD char_traits<char>, _STD allocator<char> >(
			_E0, _E1));
	}

	size_t count() const _NOEXCEPT
	{	// count number of set bits
		const char *const _Bitsperbyte =
		"\0\1\1\2\1\2\2\3\1\2\2\3\2\3\3\4"
		"\1\2\2\3\2\3\3\4\2\3\3\4\3\4\4\5"
		"\1\2\2\3\2\3\3\4\2\3\3\4\3\4\4\5"
		"\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
		"\1\2\2\3\2\3\3\4\2\3\3\4\3\4\4\5"
		"\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
		"\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
		"\3\4\4\5\4\5\5\6\4\5\5\6\5\6\6\7"
		"\1\2\2\3\2\3\3\4\2\3\3\4\3\4\4\5"
		"\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
		"\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
		"\3\4\4\5\4\5\5\6\4\5\5\6\5\6\6\7"
		"\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
		"\3\4\4\5\4\5\5\6\4\5\5\6\5\6\6\7"
		"\3\4\4\5\4\5\5\6\4\5\5\6\5\6\6\7"
		"\4\5\5\6\5\6\6\7\5\6\6\7\6\7\7\x8";
		const unsigned char *_Ptr =
			(const unsigned char *)(const void *)_Array;
		const unsigned char *const _End = _Ptr + sizeof(_Array);
		size_t _Val = 0;
		for (; _Ptr != _End; ++_Ptr)
			_Val += _Bitsperbyte[*_Ptr];
		return (_Val);
	}

		size_t size() const _NOEXCEPT
	{	// return size of bitset
		return (_Bits);
	}

		size_t hash() const
	{	// hash bits to size_t value by pseudorandomizing transform
		return (_Hash_seq((const unsigned char *)_Array,
			sizeof(_Array)));
	}

	bool operator==(const bitset<_Bits>& _Right) const _NOEXCEPT
	{	// test for bitset equality
		for (ptrdiff_t _Wpos = _Words; 0 <= _Wpos; --_Wpos)
		if (_Array[_Wpos] != _Right._Getword(_Wpos))
			return (false);
		return (true);
	}

		bool operator!=(const bitset<_Bits>& _Right) const _NOEXCEPT
	{	// test for bitset inequality
		return (!(*this == _Right));
	}

		bool test(size_t _Pos) const
	{	// test if bit at _Pos is set
		if (_Bits <= _Pos)
			_Xran();	// _Pos off end
		return ((_Array[_Pos / _Bitsperword]
			& ((_Ty)1 << _Pos % _Bitsperword)) != 0);
	}

	bool any() const _NOEXCEPT
	{	// test if any bits are set
		for (ptrdiff_t _Wpos = _Words; 0 <= _Wpos; --_Wpos)
		if (_Array[_Wpos] != 0)
			return (true);
		return (false);
	}

		bool none() const _NOEXCEPT
	{	// test if no bits are set
		return (!any());
	}

		bool all() const _NOEXCEPT
	{	// test if all bits set
		return (count() == size());
	}

		bitset<_Bits> operator<<(size_t _Pos) const _NOEXCEPT
	{	// return bitset shifted left by _Pos
		return (bitset<_Bits>(*this) <<= _Pos);
	}

		bitset<_Bits> operator>>(size_t _Pos) const _NOEXCEPT
	{	// return bitset shifted right by _Pos
		return (bitset<_Bits>(*this) >>= _Pos);
	}

		_Ty _Getword(size_t _Wpos) const
	{	// get word at _Wpos
		return (_Array[_Wpos]);
	}

private:
	enum : ptrdiff_t

	{	// parameters for packing bits into words
		_Bitsperword = (ptrdiff_t)(CHAR_BIT * sizeof(_Ty)),
		_Words = (ptrdiff_t)(_Bits == 0
		? 0 : (_Bits - 1) / _Bitsperword)
	};	// NB: number of words - 1

	void _Tidy(_Ty _Wordval = 0)
	{	// set all words to _Wordval
		for (ptrdiff_t _Wpos = _Words; 0 <= _Wpos; --_Wpos)
			_Array[_Wpos] = _Wordval;
		if (_Wordval != 0)
			_Trim();
	}

	void _Trim()
	{	// clear any trailing bits in last word
		_Trim_if(_STD integral_constant<bool, _Bits % _Bitsperword != 0>());
	}

	void _Trim_if(_STD true_type)
	{	// bits to trim, remove them
		_Array[_Words] &= ((_Ty)1 << _Bits % _Bitsperword) - 1;
	}

	void _Trim_if(_STD false_type)
	{	// no bits to trim, do nothing
	}

	__declspec(noreturn) void _Xinv() const
	{	// report invalid string element in bitset conversion
		_Xinvalid_argument("invalid bitset<N> char");
	}

	__declspec(noreturn) void _Xoflo() const
	{	// report converted value too big to represent
		_Xoverflow_error("bitset<N> overflow");
	}

	__declspec(noreturn) void _Xran() const
	{	// report bit index out of range
		_STD _Xout_of_range("invalid bitset<N> position");
	}

	_Ty _Array[_Words + 1];	// the set of bits
};

// bitset TEMPLATE FUNCTIONS
template<size_t _Bits> inline
bitset<_Bits> operator&(const bitset<_Bits>& _Left,
const bitset<_Bits>& _Right) _NOEXCEPT
{	// return bitset _Left AND _Right
	bitset<_Bits> _Ans = _Left;
	return (_Ans &= _Right);
}

template<size_t _Bits> inline
bitset<_Bits> operator|(const bitset<_Bits>& _Left,
const bitset<_Bits>& _Right) _NOEXCEPT
{	// return bitset _Left OR _Right
	bitset<_Bits> _Ans = _Left;
	return (_Ans |= _Right);
}

template<size_t _Bits> inline
bitset<_Bits> operator^(const bitset<_Bits>& _Left,
const bitset<_Bits>& _Right) _NOEXCEPT
{	// return bitset _Left XOR _Right
	bitset<_Bits> _Ans = _Left;
	return (_Ans ^= _Right);
}

template<class _Elem,
class _Tr,
	size_t _Bits> inline
	_STD basic_ostream<_Elem, _Tr>& operator<<(
	_STD basic_ostream<_Elem, _Tr>& _Ostr, const bitset<_Bits>& _Right)
{	// insert bitset as a string
	const ctype<_Elem>& _Ctype_fac = _USE(_Ostr.getloc(), ctype<_Elem>);
	const _Elem _E0 = _Ctype_fac.widen('0');
	const _Elem _E1 = _Ctype_fac.widen('1');

	return (_Ostr
		<< _Right.template to_string<_Elem, _Tr, _STD allocator<_Elem> >(
		_E0, _E1));
}

// TEMPLATE operator>>
template<class _Elem,
class _Tr,
	size_t _Bits> inline
	_STD basic_istream<_Elem, _Tr>& operator>>(
	_STD basic_istream<_Elem, _Tr>& _Istr, bitset<_Bits>& _Right)
{	// extract bitset as a string
	const ctype<_Elem>& _Ctype_fac = _USE(_Istr.getloc(), ctype<_Elem>);
	const _Elem _E0 = _Ctype_fac.widen('0');
	const _Elem _E1 = _Ctype_fac.widen('1');
	_STD ios_base::iostate _State = _STD ios_base::goodbit;
	bool _Changed = false;
	string _Str;
	const typename _STD basic_istream<_Elem, _Tr>::sentry _Ok(_Istr);

	if (_Ok)
	{	// valid stream, extract elements
		_TRY_IO_BEGIN
			typename _Tr::int_type _Meta = _Istr.rdbuf()->sgetc();
		for (size_t _Count = _Right.size(); 0 < _Count;
			_Meta = _Istr.rdbuf()->snextc(), --_Count)
		{	// test _Meta
			_Elem _Char;
			if (_Tr::eq_int_type(_Tr::eof(), _Meta))
			{	// end of file, quit
				_State |= _STD ios_base::eofbit;
				break;
			}
			else if ((_Char = _Tr::to_char_type(_Meta)) != _E0
				&& _Char != _E1)
				break;	// invalid element
			else if (_Str.max_size() <= _Str.size())
			{	// no room in string, give up (unlikely)
				_State |= _STD ios_base::failbit;
				break;
			}
			else
			{	// valid, append '0' or '1'
				if (_Char == _E1)
					_Str.append(1, '1');
				else
					_Str.append(1, '0');
				_Changed = true;
			}
		}
		_CATCH_IO_(_Istr)
	}

	if (!_Changed)
		_State |= _STD ios_base::failbit;
	_Istr.setstate(_State);
	_Right = bitset<_Bits>(_Str);	// convert string and store
	return (_Istr);
}

template<size_t _Bits>
_STD bitset<_Bits> to_std(const __RSTD__ bitset<_Bits>& v){
	_STD bitset<_Bits> res;
	for (auto i = 0; i != _Bits; ++i)
	{
		if (v.test(i))
			res.set(i);
	}
	return res;
}

template<size_t _Bits>
__RSTD__ bitset<_Bits> from_std(const _STD bitset<_Bits>& v){
	__RSTD__ bitset<_Bits> res;
	for (auto i = 0; i != _Bits; ++i)
	{
		if (v.test(i))
			res.set(i);
	}
	return res;
}

_STD_END

_STD_BEGIN
// TEMPLATE STRUCT SPECIALIZATION hash
template<size_t _Bits>
struct hash<__RSTD__ bitset<_Bits> >
	: public unary_function<__RSTD__ bitset<_Bits>, size_t>
{	// hash functor for bitset<_Bits>
	typedef __RSTD__ bitset<_Bits> _Kty;

	size_t operator()(const _Kty& _Keyval) const
	{	// hash _Keyval to size_t value by pseudorandomizing transform
		return (_Keyval.hash());
	}
};
_STD_END

#pragma pop_macro("new")
#pragma warning(pop)
#pragma pack(pop)
#endif /* RC_INVOKED */
