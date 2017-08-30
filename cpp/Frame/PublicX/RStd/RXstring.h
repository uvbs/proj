#pragma once
/*
@author zhp
@date 2017/2/27 5:52
@purpose for xstring release
*/
#ifndef RC_INVOKED
#include "RXutility.h"
#include <xmemory0>

#pragma pack(push,_CRT_PACKING)
#pragma warning(push,3)
#pragma push_macro("new")
#undef new

__RSTD_BEGIN_
#pragma warning(disable: 4127)

#pragma warning(disable: 4251)

template<class _Elem,
class _Traits = _STD char_traits<_Elem>,
class _Ax = _STD allocator<_Elem> >
class basic_string;

#define _STRING_ITER_BASE(it)			(it)._Ptr
#define _STRING_CONST_ITERATOR(ptr)	const_iterator(ptr, this)
#define _STRING_ITERATOR(ptr)			iterator(ptr, this)

// TEMPLATE CLASS _String_const_iterator
template<class _Mystr>
class _String_const_iterator
	: public _STD _Iterator012<_STD random_access_iterator_tag,
	typename _Mystr::value_type,
	typename _Mystr::difference_type,
	typename _Mystr::const_pointer,
	typename _Mystr::const_reference,
	_Iterator_base>
{	// iterator for nonmutable string
public:
	typedef _String_const_iterator<_Mystr> _Myiter;
	typedef _STD random_access_iterator_tag iterator_category;

	typedef typename _Mystr::value_type value_type;
	typedef typename _Mystr::difference_type difference_type;
	typedef typename _Mystr::const_pointer pointer;
	typedef typename _Mystr::const_reference reference;

	_String_const_iterator()
	{	// construct with null pointer
		this->_Ptr = 0;
	}

	_String_const_iterator(pointer _Parg, const _Container_base *_Pstring)
	{	// construct with pointer _Parg
		this->_Adopt(_Pstring);
		this->_Ptr = _Parg;
	}

	typedef pointer _Unchecked_type;

	_Myiter& _Rechecked(_Unchecked_type _Right)
	{	// reset from unchecked iterator
		this->_Ptr = _Right;
		return (*this);
	}

	_Unchecked_type _Unchecked() const
	{	// make an unchecked iterator
		return (_Unchecked_type(this->_Ptr));
	}

	reference operator*() const
	{	// return designated object
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (this->_Getcont() == 0
			|| this->_Ptr == 0
			|| this->_Ptr < ((_Mystr *)this->_Getcont())->_Myptr()
			|| ((_Mystr *)this->_Getcont())->_Myptr()
			+ ((_Mystr *)this->_Getcont())->_Mysize <= this->_Ptr)
		{	// report error
			_DEBUG_ERROR("string iterator not dereferencable");
			_SCL_SECURE_OUT_OF_RANGE;
		}

#elif __RSTD_ITERATOR_DEBUG_LEVEL__ == 1
		_SCL_SECURE_VALIDATE(this->_Getcont() != 0 && this->_Ptr != 0);
		_SCL_SECURE_VALIDATE_RANGE(
			((_Mystr *)this->_Getcont())->_Myptr() <= this->_Ptr
			&& this->_Ptr < ((_Mystr *)this->_Getcont())->_Myptr()
			+ ((_Mystr *)this->_Getcont())->_Mysize);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ */

		_Analysis_assume_(this->_Ptr != 0);

		return (*this->_Ptr);
	}

	pointer operator->() const
	{	// return pointer to class object
		return (_STD pointer_traits<pointer>::pointer_to(**this));
	}

	_Myiter& operator++()
	{	// preincrement
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (this->_Getcont() == 0
			|| this->_Ptr == 0
			|| ((_Mystr *)this->_Getcont())->_Myptr()
			+ ((_Mystr *)this->_Getcont())->_Mysize <= this->_Ptr)
		{	// report error
			_DEBUG_ERROR("string iterator not incrementable");
			_SCL_SECURE_OUT_OF_RANGE;
		}

#elif __RSTD_ITERATOR_DEBUG_LEVEL__ == 1
		_SCL_SECURE_VALIDATE(this->_Getcont() != 0 && this->_Ptr != 0);
		_SCL_SECURE_VALIDATE_RANGE(
			this->_Ptr < ((_Mystr *)this->_Getcont())->_Myptr()
			+ ((_Mystr *)this->_Getcont())->_Mysize);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ */

		++this->_Ptr;
		return (*this);
	}

	_Myiter operator++(int)
	{	// postincrement
		_Myiter _Tmp = *this;
		++*this;
		return (_Tmp);
	}

	_Myiter& operator--()
	{	// predecrement
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (this->_Getcont() == 0
			|| this->_Ptr == 0
			|| this->_Ptr <= ((_Mystr *)this->_Getcont())->_Myptr())
		{	// report error
			_DEBUG_ERROR("string iterator not decrementable");
			_SCL_SECURE_OUT_OF_RANGE;
		}

#elif __RSTD_ITERATOR_DEBUG_LEVEL__ == 1
		_SCL_SECURE_VALIDATE(this->_Getcont() != 0 && this->_Ptr != 0);
		_SCL_SECURE_VALIDATE_RANGE(
			((_Mystr *)this->_Getcont())->_Myptr() < this->_Ptr);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ */

		--this->_Ptr;
		return (*this);
	}

	_Myiter operator--(int)
	{	// postdecrement
		_Myiter _Tmp = *this;
		--*this;
		return (_Tmp);
	}

	_Myiter& operator+=(difference_type _Off)
	{	// increment by integer
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (this->_Getcont() == 0
			|| this->_Ptr == 0
			|| this->_Ptr + _Off < ((_Mystr *)this->_Getcont())->_Myptr()
			|| ((_Mystr *)this->_Getcont())->_Myptr()
			+ ((_Mystr *)this->_Getcont())->_Mysize < this->_Ptr + _Off)
		{	// report error
			_DEBUG_ERROR("string iterator + offset out of range");
			_SCL_SECURE_OUT_OF_RANGE;
		}

#elif __RSTD_ITERATOR_DEBUG_LEVEL__ == 1
		_SCL_SECURE_VALIDATE(this->_Getcont() != 0 && this->_Ptr != 0);
		_SCL_SECURE_VALIDATE_RANGE(
			((_Mystr *)this->_Getcont())->_Myptr() <= this->_Ptr + _Off
			&& this->_Ptr + _Off <= ((_Mystr *)this->_Getcont())->_Myptr()
			+ ((_Mystr *)this->_Getcont())->_Mysize);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ */

		_Ptr += _Off;
		return (*this);
	}

	_Myiter operator+(difference_type _Off) const
	{	// return this + integer
		_Myiter _Tmp = *this;
		return (_Tmp += _Off);
	}

	_Myiter& operator-=(difference_type _Off)
	{	// decrement by integer
		return (*this += -_Off);
	}

	_Myiter operator-(difference_type _Off) const
	{	// return this - integer
		_Myiter _Tmp = *this;
		return (_Tmp -= _Off);
	}

	difference_type operator-(const _Myiter& _Right) const
	{	// return difference of iterators
		_Compat(_Right);
		return (this->_Ptr - _Right._Ptr);
	}

	reference operator[](difference_type _Off) const
	{	// subscript
		return (*(*this + _Off));
	}

	bool operator==(const _Myiter& _Right) const
	{	// test for iterator equality
		_Compat(_Right);
		return (this->_Ptr == _Right._Ptr);
	}

	bool operator!=(const _Myiter& _Right) const
	{	// test for iterator inequality
		return (!(*this == _Right));
	}

	bool operator<(const _Myiter& _Right) const
	{	// test if this < _Right
		_Compat(_Right);
		return (this->_Ptr < _Right._Ptr);
	}

	bool operator>(const _Myiter& _Right) const
	{	// test if this > _Right
		return (_Right < *this);
	}

	bool operator<=(const _Myiter& _Right) const
	{	// test if this <= _Right
		return (!(_Right < *this));
	}

	bool operator>=(const _Myiter& _Right) const
	{	// test if this >= _Right
		return (!(*this < _Right));
	}

#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
	void _Compat(const _Myiter& _Right) const
	{	// test for compatible iterator pair
		if (this->_Getcont() == 0
			|| this->_Getcont() != _Right._Getcont())
		{	// report error
			_DEBUG_ERROR("string iterators incompatible");
			_SCL_SECURE_INVALID_ARGUMENT;
		}
	}

#elif __RSTD_ITERATOR_DEBUG_LEVEL__ == 1
	void _Compat(const _Myiter& _Right) const
	{	// test for compatible iterator pair
		_SCL_SECURE_VALIDATE(this->_Getcont() != 0);
		_SCL_SECURE_VALIDATE_RANGE(this->_Getcont() == _Right._Getcont());
	}

#else /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 0 */
	void _Compat(const _Myiter&) const
	{	// test for compatible iterator pair
	}
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ */

	pointer _Ptr;	// pointer to element in string
};

template<class _Mystr> inline
typename _String_const_iterator<_Mystr>::_Unchecked_type
_Unchecked(_String_const_iterator<_Mystr> _Iter)
{	// convert to unchecked
	return (_Iter._Unchecked());
}

template<class _Mystr> inline
_String_const_iterator<_Mystr>
_Rechecked(_String_const_iterator<_Mystr>& _Iter,
typename _String_const_iterator<_Mystr>
::_Unchecked_type _Right)
{	// convert to checked
	return (_Iter._Rechecked(_Right));
}

template<class _Mystr> inline
_String_const_iterator<_Mystr> operator+(
typename _String_const_iterator<_Mystr>
::difference_type _Off,
_String_const_iterator<_Mystr> _Next)
{	// add offset to iterator
	return (_Next += _Off);
}

// TEMPLATE CLASS _String_iterator
template<class _Mystr>
class _String_iterator
	: public _String_const_iterator<_Mystr>
{	// iterator for mutable string
public:
	typedef _String_iterator<_Mystr> _Myiter;
	typedef _String_const_iterator<_Mystr> _Mybase;
	typedef _STD random_access_iterator_tag iterator_category;

	typedef typename _Mystr::value_type value_type;
	typedef typename _Mystr::difference_type difference_type;
	typedef typename _Mystr::pointer pointer;
	typedef typename _Mystr::reference reference;

	_String_iterator()
	{	// construct with null string pointer
	}

	_String_iterator(pointer _Parg, const _Container_base *_Pstring)
		: _Mybase(_Parg, _Pstring)
	{	// construct with pointer _Parg
	}

	typedef pointer _Unchecked_type;

	_Myiter& _Rechecked(_Unchecked_type _Right)
	{	// reset from unchecked iterator
		this->_Ptr = _Right;
		return (*this);
	}

	_Unchecked_type _Unchecked() const
	{	// make an unchecked iterator
		return (_Unchecked_type(this->_Ptr));
	}

	reference operator*() const
	{	// return designated object
		return ((reference)**(_Mybase *)this);
	}

	pointer operator->() const
	{	// return pointer to class object
		return (_STD pointer_traits<pointer>::pointer_to(**this));
	}

	_Myiter& operator++()
	{	// preincrement
		++*(_Mybase *)this;
		return (*this);
	}

	_Myiter operator++(int)
	{	// postincrement
		_Myiter _Tmp = *this;
		++*this;
		return (_Tmp);
	}

	_Myiter& operator--()
	{	// predecrement
		--*(_Mybase *)this;
		return (*this);
	}

	_Myiter operator--(int)
	{	// postdecrement
		_Myiter _Tmp = *this;
		--*this;
		return (_Tmp);
	}

	_Myiter& operator+=(difference_type _Off)
	{	// increment by integer
		*(_Mybase *)this += _Off;
		return (*this);
	}

	_Myiter operator+(difference_type _Off) const
	{	// return this + integer
		_Myiter _Tmp = *this;
		return (_Tmp += _Off);
	}

	_Myiter& operator-=(difference_type _Off)
	{	// decrement by integer
		return (*this += -_Off);
	}

	_Myiter operator-(difference_type _Off) const
	{	// return this - integer
		_Myiter _Tmp = *this;
		return (_Tmp -= _Off);
	}

	difference_type operator-(const _Mybase& _Right) const
	{	// return difference of iterators
		return ((_Mybase)*this - _Right);
	}

	reference operator[](difference_type _Off) const
	{	// subscript
		return (*(*this + _Off));
	}
};

template<class _Mystr> inline
typename _String_iterator<_Mystr>::_Unchecked_type
_Unchecked(_String_iterator<_Mystr> _Iter)
{	// convert to unchecked
	return (_Iter._Unchecked());
}

template<class _Mystr> inline
_String_iterator<_Mystr>
_Rechecked(_String_iterator<_Mystr>& _Iter,
typename _String_iterator<_Mystr>
::_Unchecked_type _Right)
{	// convert to checked
	return (_Iter._Rechecked(_Right));
}

template<class _Mystr> inline
_String_iterator<_Mystr> operator+(
typename _String_iterator<_Mystr>
::difference_type _Off,
_String_iterator<_Mystr> _Next)
{	// add offset to iterator
	return (_Next += _Off);
}

// basic_string TYPE WRAPPERS
template<class _Value_type,
class _Size_type,
class _Difference_type,
class _Pointer,
class _Const_pointer,
class _Reference,
class _Const_reference>
struct _String_iter_types
{	// wraps types needed by iterators
	typedef _Value_type value_type;
	typedef _Size_type size_type;
	typedef _Difference_type difference_type;
	typedef _Pointer pointer;
	typedef _Const_pointer const_pointer;
	typedef _Reference reference;
	typedef _Const_reference const_reference;
};

template<class _Ty,
class _Alloc0>
struct _String_base_types
{	// types needed for a container base
	typedef _Alloc0 _Alloc;
	typedef _String_base_types<_Ty, _Alloc> _Myt;

	typedef _STD _Wrap_alloc<_Alloc> _Alty0;
	typedef typename _Alty0::template rebind<_Ty>::other _Alty;


	typedef typename _Alty::pointer _Tptr;
	typedef typename _Alty::template rebind<_Tptr>::other _Alpty;

	typedef typename _STD _If<_STD _Is_simple_alloc<_Alty>::value,
		_STD _Simple_types<typename _Alty::value_type>,
		_String_iter_types<typename _Alty::value_type,
		typename _Alty::size_type,
		typename _Alty::difference_type,
		typename _Alty::pointer,
		typename _Alty::const_pointer,
		typename _Alty::reference,
		typename _Alty::const_reference> >::type
		_Val_types;
};

// TEMPLATE CLASS _String_val
template<class _Val_types>
class _String_val
	: public _Container_base
{	// base class for basic_string to hold data
public:
	typedef _String_val<_Val_types> _Myt;

	typedef typename _Val_types::value_type value_type;
	typedef typename _Val_types::size_type size_type;
	typedef typename _Val_types::difference_type difference_type;
	typedef typename _Val_types::pointer pointer;
	typedef typename _Val_types::const_pointer const_pointer;
	typedef typename _Val_types::reference reference;
	typedef typename _Val_types::const_reference const_reference;

	typedef _String_iterator<_Myt> iterator;
	typedef _String_const_iterator<_Myt> const_iterator;

	_String_val()
	{	// initialize values
		_Mysize = 0;
		_Myres = 0;
	}

	enum
	{	// length of internal buffer, [1, 16]
		_BUF_SIZE = 16 / sizeof(value_type) < 1 ? 1
		: 16 / sizeof(value_type)
	};
	enum
	{	// roundup mask for allocated buffers, [0, 15]
		_ALLOC_MASK = sizeof(value_type) <= 1 ? 15
		: sizeof(value_type) <= 2 ? 7
		: sizeof(value_type) <= 4 ? 3
		: sizeof(value_type) <= 8 ? 1 : 0
	};

	value_type *_Myptr()
	{	// determine current pointer to buffer for mutable string
		return (this->_BUF_SIZE <= this->_Myres
			? _STD addressof(*this->_Bx._Ptr)
			: this->_Bx._Buf);
	}

	const value_type *_Myptr() const
	{	// determine current pointer to buffer for nonmutable string
		return (this->_BUF_SIZE <= this->_Myres
			? _STD addressof(*this->_Bx._Ptr)
			: this->_Bx._Buf);
	}

	union _Bxty
	{	// storage for small buffer or pointer to larger one
		value_type _Buf[_BUF_SIZE];
		pointer _Ptr;
		char _Alias[_BUF_SIZE];	// to permit aliasing
	} _Bx;

	size_type _Mysize;	// current length of string
	size_type _Myres;	// current storage reserved for string
};

// TEMPLATE CLASS _String_alloc
template<bool _Al_has_storage,
class _Alloc_types>
class _String_alloc
	: public _String_val<typename _Alloc_types::_Val_types>
{	// base class for basic_string to hold allocator with storage
public:
	typename _Alloc_types::_Alty _Alval;	// allocator object

	typedef _String_alloc<_Al_has_storage, _Alloc_types> _Myt;
	typedef typename _Alloc_types::_Alloc _Alloc;
	typedef typename _Alloc_types::_Alty _Alty;

#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 0
	_String_alloc(const _Alloc& _Al = _Alloc())
		: _Alval(_Al)
	{	// construct allocator from _Al
	}

	void _Change_alloc(const _Alty& _Al)
	{	// replace old allocator
		this->_Alval = _Al;
	}

	void _Swap_alloc(_Myt& _Right)
	{	// swap allocators
		_Swap_adl(this->_Alval, _Right._Alval);
	}

#else /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 0 */
	_String_alloc(const _Alloc& _Al = _Alloc())
		: _Alval(_Al)
	{	// construct allocator from _Al
		_Alloc_proxy();
	}

	~_String_alloc() _NOEXCEPT
	{	// destroy the object
		_Free_proxy();
	}

		void _Change_alloc(const _Alty& _Al)
	{	// replace old allocator
		_Free_proxy();
		this->_Alval = _Al;
		_Alloc_proxy();
	}

	void _Swap_alloc(_Myt& _Right)
	{	// swap allocators
		_Swap_adl(this->_Alval, _Right._Alval);
		_Swap_adl(this->_Myproxy, _Right._Myproxy);
	}

	void _Alloc_proxy()
	{	// construct proxy from _Alval
		typename _Alloc::template rebind<_Container_proxy>::other
			_Alproxy(this->_Alval);
		this->_Myproxy = _Alproxy.allocate(1);
		_Alproxy.construct(this->_Myproxy, _Container_proxy());
		this->_Myproxy->_Mycont = this;
	}

	void _Free_proxy()
	{	// destroy proxy
		typename _Alloc::template rebind<_Container_proxy>::other
			_Alproxy(this->_Alval);
		this->_Orphan_all();
		_Alproxy.destroy(this->_Myproxy);
		_Alproxy.deallocate(this->_Myproxy, 1);
		this->_Myproxy = 0;
	}
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 0 */

	_Alty& _Getal()
	{	// get reference to allocator
		return (this->_Alval);
	}

	const _Alty& _Getal() const
	{	// get reference to allocator
		return (this->_Alval);
	}
};

template<class _Alloc_types>
class _String_alloc<false, _Alloc_types>
	: public _String_val<typename _Alloc_types::_Val_types>
{	// base class for basic_string to hold allocator with no storage
public:
	typedef _String_alloc<false, _Alloc_types> _Myt;
	typedef typename _Alloc_types::_Alloc _Alloc;

	typedef typename _Alloc_types::_Alty _Alty;

#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 0
	_String_alloc(const _Alloc& = _Alloc())
	{	// construct allocator from _Al
	}

	void _Change_alloc(const _Alty&)
	{	// replace old allocator
	}

	void _Swap_alloc(_Myt&)
	{	// swap allocators
	}

#else /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 0 */
	_String_alloc(const _Alloc& = _Alloc())
	{	// construct allocator from _Al
		_Alloc_proxy();
	}

	~_String_alloc() _NOEXCEPT
	{	// destroy the object
		_Free_proxy();
	}

		void _Change_alloc(const _Alty&)
	{	// replace old allocator
	}

	void _Swap_alloc(_Myt& _Right)
	{	// swap allocators
		_Swap_adl(this->_Myproxy, _Right._Myproxy);
	}

	void _Alloc_proxy()
	{	// construct proxy from _Alval
		typename _Alloc::template rebind<_Container_proxy>::other
			_Alproxy;
		this->_Myproxy = _Alproxy.allocate(1);
		_Alproxy.construct(this->_Myproxy, _Container_proxy());
		this->_Myproxy->_Mycont = this;
	}

	void _Free_proxy()
	{	// destroy proxy
		typename _Alloc::template rebind<_Container_proxy>::other
			_Alproxy;
		this->_Orphan_all();
		_Alproxy.destroy(this->_Myproxy);
		_Alproxy.deallocate(this->_Myproxy, 1);
		this->_Myproxy = 0;
	}
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 0 */

	_Alty _Getal() const
	{	// get reference to allocator
		return (_Alty());
	}
};

// TEMPLATE CLASS basic_string
template<class _Elem,
class _Traits,
class _Alloc>
class basic_string
	: public _String_alloc<!_STD is_empty<_Alloc>::value,
	_String_base_types<_Elem, _Alloc> >
{	// null-terminated transparent array of elements
public:
	typedef basic_string<_Elem, _Traits, _Alloc> _Myt;
	typedef _String_alloc<!_STD is_empty<_Alloc>::value,
		_String_base_types<_Elem, _Alloc> > _Mybase;
	typedef _Traits traits_type;
	typedef _Alloc allocator_type;

	typedef typename _Mybase::_Alty _Alty;

	typedef typename _Mybase::value_type value_type;
	typedef typename _Mybase::size_type size_type;
	typedef typename _Mybase::difference_type difference_type;
	typedef typename _Mybase::pointer pointer;
	typedef typename _Mybase::const_pointer const_pointer;
	typedef typename _Mybase::reference reference;
	typedef typename _Mybase::const_reference const_reference;

	typedef typename _Mybase::iterator iterator;
	typedef typename _Mybase::const_iterator const_iterator;

	typedef _STD reverse_iterator<iterator> reverse_iterator;
	typedef _STD reverse_iterator<const_iterator> const_reverse_iterator;

	basic_string(const _Myt& _Right)

		: _Mybase(_Right._Getal().select_on_container_copy_construction())


	{	// construct by copying _Right
		_Tidy();
		assign(_Right, 0, npos);
	}

	basic_string(const _Myt& _Right, const _Alloc& _Al)
		: _Mybase(_Al)
	{	// construct by copying with allocator
		_Tidy();
		assign(_Right, 0, npos);
	}

	basic_string()
		: _Mybase()
	{	// construct empty string
		_Tidy();
	}

	explicit basic_string(const _Alloc& _Al)
		: _Mybase(_Al)
	{	// construct empty string with allocator
		_Tidy();
	}

	basic_string(const _Myt& _Right, size_type _Roff,
		size_type _Count = npos)
		: _Mybase(_Right._Getal())
	{	// construct from _Right [_Roff, _Roff + _Count)
		_Tidy();
		assign(_Right, _Roff, _Count);
	}

	basic_string(const _Myt& _Right, size_type _Roff, size_type _Count,
		const _Alloc& _Al)
		: _Mybase(_Al)
	{	// construct from _Right [_Roff, _Roff + _Count) with allocator
		_Tidy();
		assign(_Right, _Roff, _Count);
	}

	basic_string(const _Elem *_Ptr, size_type _Count)
		: _Mybase()
	{	// construct from [_Ptr, _Ptr + _Count)
		_Tidy();
		assign(_Ptr, _Count);
	}

	basic_string(const _Elem *_Ptr, size_type _Count, const _Alloc& _Al)
		: _Mybase(_Al)
	{	// construct from [_Ptr, _Ptr + _Count) with allocator
		_Tidy();
		assign(_Ptr, _Count);
	}

	basic_string(const _Elem *_Ptr)
		: _Mybase()
	{	// construct from [_Ptr, <null>)
		_Tidy();
		assign(_Ptr);
	}

	basic_string(const _Elem *_Ptr, const _Alloc& _Al)
		: _Mybase(_Al)
	{	// construct from [_Ptr, <null>) with allocator
		_Tidy();
		assign(_Ptr);
	}

	basic_string(size_type _Count, _Elem _Ch)
		: _Mybase()
	{	// construct from _Count * _Ch
		_Tidy();
		assign(_Count, _Ch);
	}

	basic_string(size_type _Count, _Elem _Ch, const _Alloc& _Al)
		: _Mybase(_Al)
	{	// construct from _Count * _Ch with allocator
		_Tidy();
		assign(_Count, _Ch);
	}

	template<class _Iter,
	class = typename _STD enable_if<_STD _Is_iterator<_Iter>::value,
		void>::type>
		basic_string(_Iter _First, _Iter _Last)
		: _Mybase()
	{	// construct from [_First, _Last)
		_Tidy();
		_Construct(_First, _Last, _Iter_cat(_First));
	}

	template<class _Iter,
	class = typename _STD enable_if<_STD _Is_iterator<_Iter>::value,
		void>::type>
		basic_string(_Iter _First, _Iter _Last, const _Alloc& _Al)
		: _Mybase(_Al)
	{	// construct from [_First, _Last) with allocator
		_Tidy();
		_Construct(_First, _Last, _Iter_cat(_First));
	}

	template<class _Iter>
	void _Construct(_Iter _First,
		_Iter _Last, _STD input_iterator_tag)
	{	// initialize from [_First, _Last), input iterators
		_TRY_BEGIN
			for (; _First != _Last; ++_First)
				append((size_type)1, (_Elem)*_First);
		_CATCH_ALL
			_Tidy(true);
		_RERAISE;
		_CATCH_END
	}

	template<class _Iter>
	void _Construct(_Iter _First,
		_Iter _Last, _STD forward_iterator_tag)
	{	// initialize from [_First, _Last), forward iterators
		_DEBUG_RANGE(_First, _Last);
		size_type _Count = 0;
		_Distance(_First, _Last, _Count);
		reserve(_Count);

		_TRY_BEGIN
			for (; _First != _Last; ++_First)
				append((size_type)1, (_Elem)*_First);
		_CATCH_ALL
			_Tidy(true);
		_RERAISE;
		_CATCH_END
	}

	basic_string(const_pointer _First, const_pointer _Last)
		: _Mybase()
	{	// construct from [_First, _Last), const pointers
		_DEBUG_RANGE(_First, _Last);
		_Tidy();
		if (_First != _Last)
			assign(&*_First, _Last - _First);
	}

	basic_string(const_pointer _First, const_pointer _Last,
		const _Alloc& _Al)
		: _Mybase(_Al)
	{	// construct from [_First, _Last), const pointers
		_DEBUG_RANGE(_First, _Last);
		_Tidy();
		if (_First != _Last)
			assign(&*_First, _Last - _First);
	}

	basic_string(const_iterator _First, const_iterator _Last)
		: _Mybase()
	{	// construct from [_First, _Last), const_iterators
		_DEBUG_RANGE(_First, _Last);
		_Tidy();
		if (_First != _Last)
			assign(&*_First, _Last - _First);
	}

	basic_string(_Myt&& _Right) _NOEXCEPT
		: _Mybase(_Right._Getal())
	{	// construct by moving _Right
		_Tidy();
		_Assign_rv(_STD forward<_Myt>(_Right));
	}

	basic_string(_Myt&& _Right, const _Alloc& _Al)
		: _Mybase(_Al)
	{	// construct by moving _Right, allocator
		if (this->_Getal() != _Right._Getal())
			assign(_Right.begin(), _Right.end());
		else
			_Assign_rv(_STD forward<_Myt>(_Right));
	}

	_Myt& operator=(_Myt&& _Right) _NOEXCEPT
	{	// assign by moving _Right
		if (this != &_Right)
		{	// different, assign it
			_Tidy(true);

			if (_Alty::propagate_on_container_move_assignment::value
				&& this->_Getal() != _Right._Getal())
				this->_Change_alloc(_Right._Getal());

			if (this->_Getal() != _Right._Getal())
				assign(_Right.begin(), _Right.end());
			else
				_Assign_rv(_STD forward<_Myt>(_Right));
		}
		return (*this);
	}

		_Myt& assign(_Myt&& _Right) _NOEXCEPT
	{	// assign by moving _Right
		if (this == &_Right)
		;
		else if (get_allocator() != _Right.get_allocator()
			&& this->_BUF_SIZE <= _Right._Myres)
			*this = _Right;
		else
		{	// not same, clear this and steal from _Right
			_Tidy(true);
			_Assign_rv(_STD forward<_Myt>(_Right));
		}
		return (*this);
	}

		void _Assign_rv(_Myt&& _Right)
	{	// assign by moving _Right
		if (_Right._Myres < this->_BUF_SIZE)
			_Traits::move(this->_Bx._Buf, _Right._Bx._Buf,
			_Right._Mysize + 1);
		else
		{	// copy pointer
			this->_Getal().construct(&this->_Bx._Ptr, _Right._Bx._Ptr);
			_Right._Bx._Ptr = pointer();
		}
		this->_Mysize = _Right._Mysize;
		this->_Myres = _Right._Myres;
		_Right._Tidy();
	}

	basic_string(_XSTD initializer_list<_Elem> _Ilist,
		const _Alloc& _Al = allocator_type())
		: _Mybase(_Al)
	{	// construct from initializer_list
		_Tidy();
		assign(_Ilist.begin(), _Ilist.end());
	}

	_Myt& operator=(_XSTD initializer_list<_Elem> _Ilist)
	{	// assign initializer_list
		return (assign(_Ilist.begin(), _Ilist.end()));
	}

	_Myt& operator+=(_XSTD initializer_list<_Elem> _Ilist)
	{	// append initializer_list
		return (append(_Ilist.begin(), _Ilist.end()));
	}

	_Myt& assign(_XSTD initializer_list<_Elem> _Ilist)
	{	// assign initializer_list
		return (assign(_Ilist.begin(), _Ilist.end()));
	}

	_Myt& append(_XSTD initializer_list<_Elem> _Ilist)
	{	// append initializer_list
		return (append(_Ilist.begin(), _Ilist.end()));
	}

	iterator insert(const_iterator _Where,
		_XSTD initializer_list<_Elem> _Ilist)
	{	// insert initializer_list
		return (insert(_Where, _Ilist.begin(), _Ilist.end()));
	}

	_Myt& replace(const_iterator _First, const_iterator _Last,
		_XSTD initializer_list<_Elem> _Ilist)
	{	// replace with initializer_list
		return (replace(_First, _Last, _Ilist.begin(), _Ilist.end()));
	}

	~basic_string() _NOEXCEPT
	{	// destroy the string
		_Tidy(true);
	}

	_PGLOBAL static const size_type npos;	// bad/missing length/position

	_Myt& operator=(const _Myt& _Right)
	{	// assign _Right
		if (this != &_Right)
		{	// different, assign it
			if (this->_Getal() != _Right._Getal()
				&& _Alty::propagate_on_container_copy_assignment::value)
			{	// change allocator before copying
				_Tidy(true);
				this->_Change_alloc(_Right._Getal());
			}

			assign(_Right);
		}
		return (*this);
	}

	_Myt& operator=(const _Elem *_Ptr)
	{	// assign [_Ptr, <null>)
		return (assign(_Ptr));
	}

	_Myt& operator=(_Elem _Ch)
	{	// assign 1 * _Ch
		return (assign(1, _Ch));
	}

	_Myt& operator+=(const _Myt& _Right)
	{	// append _Right
		return (append(_Right));
	}

	_Myt& operator+=(const _Elem *_Ptr)
	{	// append [_Ptr, <null>)
		return (append(_Ptr));
	}

	_Myt& operator+=(_Elem _Ch)
	{	// append 1 * _Ch
		return (append((size_type)1, _Ch));
	}

	_Myt& append(const _Myt& _Right)
	{	// append _Right
		return (append(_Right, 0, npos));
	}

	_Myt& append(const _Myt& _Right,
		size_type _Roff, size_type _Count)
	{	// append _Right [_Roff, _Roff + _Count)
		if (_Right.size() < _Roff)
			_Xran();	// _Roff off end
		size_type _Num = _Right.size() - _Roff;
		if (_Num < _Count)
			_Count = _Num;	// trim _Count to size
		if (npos - this->_Mysize <= _Count)
			_Xlen();	// result too long

		if (0 < _Count && _Grow(_Num = this->_Mysize + _Count))
		{	// make room and append new stuff
			_Traits::copy(this->_Myptr() + this->_Mysize,
				_Right._Myptr() + _Roff, _Count);
			_Eos(_Num);
		}
		return (*this);
	}

	_Myt& append(const _Elem *_Ptr, size_type _Count)
	{	// append [_Ptr, _Ptr + _Count)
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (_Count != 0)
			_DEBUG_POINTER(_Ptr);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		if (_Inside(_Ptr))
			return (append(*this,
			_Ptr - this->_Myptr(), _Count));	// substring
		if (npos - this->_Mysize <= _Count)
			_Xlen();	// result too long

		size_type _Num;
		if (0 < _Count && _Grow(_Num = this->_Mysize + _Count))
		{	// make room and append new stuff
			_Traits::copy(this->_Myptr() + this->_Mysize, _Ptr, _Count);
			_Eos(_Num);
		}
		return (*this);
	}

	_Myt& append(const _Elem *_Ptr)
	{	// append [_Ptr, <null>)
		_DEBUG_POINTER(_Ptr);
		return (append(_Ptr, _Traits::length(_Ptr)));
	}

	_Myt& append(size_type _Count, _Elem _Ch)
	{	// append _Count * _Ch
		if (npos - this->_Mysize <= _Count)
			_Xlen();	// result too long

		size_type _Num;
		if (0 < _Count && _Grow(_Num = this->_Mysize + _Count))
		{	// make room and append new stuff using assign
			_Chassign(this->_Mysize, _Count, _Ch);
			_Eos(_Num);
		}
		return (*this);
	}

	template<class _Iter>
	typename _STD enable_if<_STD _Is_iterator<_Iter>::value,
		_Myt&>::type
		append(_Iter _First, _Iter _Last)
	{	// append [_First, _Last), input iterators
		return (replace(end(), end(), _First, _Last));
	}

	_Myt& append(const_pointer _First, const_pointer _Last)
	{	// append [_First, _Last), const pointers
		return (replace(end(), end(), _First, _Last));
	}

	_Myt& append(const_iterator _First, const_iterator _Last)
	{	// append [_First, _Last), const_iterators
		return (replace(end(), end(), _First, _Last));
	}

	_Myt& assign(const _Myt& _Right)
	{	// assign _Right
		return (assign(_Right, 0, npos));
	}

	_Myt& assign(const _Myt& _Right,
		size_type _Roff, size_type _Count)
	{	// assign _Right [_Roff, _Roff + _Count)
		if (_Right.size() < _Roff)
			_Xran();	// _Roff off end
		size_type _Num = _Right.size() - _Roff;
		if (_Count < _Num)
			_Num = _Count;	// trim _Num to size

		if (this == &_Right)
			erase((size_type)(_Roff + _Num)), erase(0, _Roff);	// substring
		else if (_Grow(_Num))
		{	// make room and assign new stuff
			_Traits::copy(this->_Myptr(),
				_Right._Myptr() + _Roff, _Num);
			_Eos(_Num);
		}
		return (*this);
	}

	_Myt& assign(const _Elem *_Ptr, size_type _Count)
	{	// assign [_Ptr, _Ptr + _Count)
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (_Count != 0)
			_DEBUG_POINTER(_Ptr);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		if (_Inside(_Ptr))
			return (assign(*this,
			_Ptr - this->_Myptr(), _Count));	// substring

		if (_Grow(_Count))
		{	// make room and assign new stuff
			_Traits::copy(this->_Myptr(), _Ptr, _Count);
			_Eos(_Count);
		}
		return (*this);
	}

	_Myt& assign(const _Elem *_Ptr)
	{	// assign [_Ptr, <null>)
		_DEBUG_POINTER(_Ptr);
		return (assign(_Ptr, _Traits::length(_Ptr)));
	}

	_Myt& assign(size_type _Count, _Elem _Ch)
	{	// assign _Count * _Ch
		if (_Count == npos)
			_Xlen();	// result too long

		if (_Grow(_Count))
		{	// make room and assign new stuff
			_Chassign(0, _Count, _Ch);
			_Eos(_Count);
		}
		return (*this);
	}

	template<class _Iter>
	typename _STD enable_if<_STD _Is_iterator<_Iter>::value,
		_Myt&>::type
		assign(_Iter _First, _Iter _Last)
	{	// assign [_First, _Last), input iterators
		return (replace(begin(), end(), _First, _Last));
	}

	_Myt& assign(const_pointer _First, const_pointer _Last)
	{	// assign [_First, _Last), const pointers
		return (replace(begin(), end(), _First, _Last));
	}

	_Myt& assign(const_iterator _First, const_iterator _Last)
	{	// assign [_First, _Last), const_iterators
		return (replace(begin(), end(), _First, _Last));
	}

	_Myt& insert(size_type _Off, const _Myt& _Right)
	{	// insert _Right at _Off
		return (insert(_Off, _Right, 0, npos));
	}

	_Myt& insert(size_type _Off,
		const _Myt& _Right, size_type _Roff, size_type _Count)
	{	// insert _Right [_Roff, _Roff + _Count) at _Off
		if (this->_Mysize < _Off || _Right.size() < _Roff)
			_Xran();	// _Off or _Roff off end
		size_type _Num = _Right.size() - _Roff;
		if (_Num < _Count)
			_Count = _Num;	// trim _Count to size
		if (npos - this->_Mysize <= _Count)
			_Xlen();	// result too long

		if (0 < _Count && _Grow(_Num = this->_Mysize + _Count))
		{	// make room and insert new stuff
			_Traits::move(this->_Myptr() + _Off + _Count,
				this->_Myptr() + _Off,
				this->_Mysize - _Off);	// empty out hole
			if (this == &_Right)
				_Traits::move(this->_Myptr() + _Off,
				this->_Myptr() + (_Off < _Roff ? _Roff + _Count : _Roff),
				_Count);	// substring
			else
				_Traits::copy(this->_Myptr() + _Off,
				_Right._Myptr() + _Roff, _Count);	// fill hole
			_Eos(_Num);
		}
		return (*this);
	}

	_Myt& insert(size_type _Off,
		const _Elem *_Ptr, size_type _Count)
	{	// insert [_Ptr, _Ptr + _Count) at _Off
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (_Count != 0)
			_DEBUG_POINTER(_Ptr);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		if (_Inside(_Ptr))
			return (insert(_Off, *this,
			_Ptr - this->_Myptr(), _Count));	// substring
		if (this->_Mysize < _Off)
			_Xran();	// _Off off end
		if (npos - this->_Mysize <= _Count)
			_Xlen();	// result too long
		size_type _Num;
		if (0 < _Count && _Grow(_Num = this->_Mysize + _Count))
		{	// make room and insert new stuff
			_Traits::move(this->_Myptr() + _Off + _Count,
				this->_Myptr() + _Off,
				this->_Mysize - _Off);	// empty out hole
			_Traits::copy(this->_Myptr() + _Off, _Ptr, _Count);	// fill hole
			_Eos(_Num);
		}
		return (*this);
	}

	_Myt& insert(size_type _Off, const _Elem *_Ptr)
	{	// insert [_Ptr, <null>) at _Off
		_DEBUG_POINTER(_Ptr);
		return (insert(_Off, _Ptr, _Traits::length(_Ptr)));
	}

	_Myt& insert(size_type _Off,
		size_type _Count, _Elem _Ch)
	{	// insert _Count * _Ch at _Off
		if (this->_Mysize < _Off)
			_Xran();	// _Off off end
		if (npos - this->_Mysize <= _Count)
			_Xlen();	// result too long
		size_type _Num;
		if (0 < _Count && _Grow(_Num = this->_Mysize + _Count))
		{	// make room and insert new stuff
			_Traits::move(this->_Myptr() + _Off + _Count,
				this->_Myptr() + _Off,
				this->_Mysize - _Off);	// empty out hole
			_Chassign(_Off, _Count, _Ch);	// fill hole
			_Eos(_Num);
		}
		return (*this);
	}

	iterator insert(const_iterator _Where)
	{	// insert <null> at _Where
		return (insert(_Where, _Elem()));
	}

	iterator insert(const_iterator _Where, _Elem _Ch)
	{	// insert _Ch at _Where
		size_type _Off = _Pdif(_Where, begin());
		insert(_Off, 1, _Ch);
		return (begin() + _Off);
	}

	iterator insert(const_iterator _Where, size_type _Count, _Elem _Ch)
	{	// insert _Count * _Elem at _Where
		size_type _Off = _Pdif(_Where, begin());
		insert(_Off, _Count, _Ch);
		return (begin() + _Off);
	}

	template<class _Iter>
	typename _STD enable_if<_STD _Is_iterator<_Iter>::value,
		iterator>::type
		insert(const_iterator _Where, _Iter _First, _Iter _Last)
	{	// insert [_First, _Last) at _Where, input iterators
		size_type _Off = _Pdif(_Where, begin());
		replace(_Where, _Where, _First, _Last);
		return (begin() + _Off);
	}

	iterator insert(const_iterator _Where,
		const_pointer _First, const_pointer _Last)
	{	// insert [_First, _Last) at _Where, const pointers
		size_type _Off = _Pdif(_Where, begin());
		replace(_Where, _Where, _First, _Last);
		return (begin() + _Off);
	}

	iterator insert(const_iterator _Where,
		const_iterator _First, const_iterator _Last)
	{	// insert [_First, _Last) at _Where, const_iterators
		size_type _Off = _Pdif(_Where, begin());
		replace(_Where, _Where, _First, _Last);
		return (begin() + _Off);
	}

	_Myt& erase(size_type _Off = 0)
	{	// erase elements [_Off, ...)
		if (this->_Mysize < _Off)
			_Xran();	// _Off off end
		_Eos(_Off);
		return (*this);
	}

	_Myt& erase(size_type _Off, size_type _Count)
	{	// erase elements [_Off, _Off + _Count)
		if (this->_Mysize < _Off)
			_Xran();	// _Off off end
		if (this->_Mysize - _Off <= _Count)
			_Eos(_Off);	// erase elements [_Off, ...)
		else if (0 < _Count)
		{	// move elements down
			value_type *_Ptr = this->_Myptr() + _Off;
			size_type _Newsize = this->_Mysize - _Count;
			_Traits::move(_Ptr, _Ptr + _Count, _Newsize - _Off);
			_Eos(_Newsize);
		}
		return (*this);
	}

	iterator erase(const_iterator _Where)
	{	// erase element at _Where
		size_type _Count = _Pdif(_Where, begin());
		erase(_Count, 1);
		return (_STRING_ITERATOR(this->_Myptr() + _Count));
	}

	iterator erase(const_iterator _First, const_iterator _Last)
	{	// erase substring [_First, _Last)
		_DEBUG_RANGE(_First, _Last);
		size_type _Count = _Pdif(_First, begin());
		erase(_Count, _Pdif(_Last, _First));
		return (_STRING_ITERATOR(this->_Myptr() + _Count));
	}

	void clear() _NOEXCEPT
	{	// erase all
		_Eos(0);
	}

		_Myt& replace(size_type _Off, size_type _N0, const _Myt& _Right)
	{	// replace [_Off, _Off + _N0) with _Right
		return (replace(_Off, _N0, _Right, 0, npos));
	}

	_Myt& replace(size_type _Off,
		size_type _N0, const _Myt& _Right, size_type _Roff, size_type _Count)
	{	// replace [_Off, _Off + _N0) with _Right [_Roff, _Roff + _Count)
		if (this->_Mysize < _Off || _Right.size() < _Roff)
			_Xran();	// _Off or _Roff off end
		if (this->_Mysize - _Off < _N0)
			_N0 = this->_Mysize - _Off;	// trim _N0 to size
		size_type _Num = _Right.size() - _Roff;
		if (_Num < _Count)
			_Count = _Num;	// trim _Count to size
		if (npos - _Count <= this->_Mysize - _N0)
			_Xlen();	// result too long

		size_type _Nm = this->_Mysize - _N0 - _Off;	// length of kept tail
		size_type _Newsize = this->_Mysize + _Count - _N0;
		if (this->_Mysize < _Newsize)
			_Grow(_Newsize);

		if (this != &_Right)
		{	// no overlap, just move down and copy in new stuff
			_Traits::move(this->_Myptr() + _Off + _Count,
				this->_Myptr() + _Off + _N0, _Nm);	// empty hole
			_Traits::copy(this->_Myptr() + _Off,
				_Right._Myptr() + _Roff, _Count);	// fill hole
		}
		else if (_Count <= _N0)
		{	// hole doesn't get larger, just copy in substring
			_Traits::move(this->_Myptr() + _Off,
				this->_Myptr() + _Roff, _Count);	// fill hole
			_Traits::move(this->_Myptr() + _Off + _Count,
				this->_Myptr() + _Off + _N0, _Nm);	// move tail down
		}
		else if (_Roff <= _Off)
		{	// hole gets larger, substring begins before hole
			_Traits::move(this->_Myptr() + _Off + _Count,
				this->_Myptr() + _Off + _N0, _Nm);	// move tail down
			_Traits::move(this->_Myptr() + _Off,
				this->_Myptr() + _Roff, _Count);	// fill hole
		}
		else if (_Off + _N0 <= _Roff)
		{	// hole gets larger, substring begins after hole
			_Traits::move(this->_Myptr() + _Off + _Count,
				this->_Myptr() + _Off + _N0, _Nm);	// move tail down
			_Traits::move(this->_Myptr() + _Off,
				this->_Myptr() + (_Roff + _Count - _N0),
				_Count);	// fill hole
		}
		else
		{	// hole gets larger, substring begins in hole
			_Traits::move(this->_Myptr() + _Off,
				this->_Myptr() + _Roff, _N0);	// fill old hole
			_Traits::move(this->_Myptr() + _Off + _Count,
				this->_Myptr() + _Off + _N0, _Nm);	// move tail down
			_Traits::move(this->_Myptr() + _Off + _N0,
				this->_Myptr() + _Roff + _Count,
				_Count - _N0);	// fill rest of new hole
		}

		_Eos(_Newsize);
		return (*this);
	}

	_Myt& replace(size_type _Off,
		size_type _N0, const _Elem *_Ptr, size_type _Count)
	{	// replace [_Off, _Off + _N0) with [_Ptr, _Ptr + _Count)
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (_Count != 0)
			_DEBUG_POINTER(_Ptr);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		if (_Inside(_Ptr))
			return (replace(_Off, _N0, *this,
			_Ptr - this->_Myptr(),
			_Count));	// substring, replace carefully
		if (this->_Mysize < _Off)
			_Xran();	// _Off off end
		if (this->_Mysize - _Off < _N0)
			_N0 = this->_Mysize - _Off;	// trim _N0 to size
		if (npos - _Count <= this->_Mysize - _N0)
			_Xlen();	// result too long
		size_type _Nm = this->_Mysize - _N0 - _Off;

		if (_Count < _N0)
			_Traits::move(this->_Myptr() + _Off + _Count,
			this->_Myptr() + _Off + _N0,
			_Nm);	// smaller hole, move tail up
		size_type _Num;
		if ((0 < _Count || 0 < _N0)
			&& _Grow(_Num = this->_Mysize + _Count - _N0))
		{	// make room and rearrange
			if (_N0 < _Count)
				_Traits::move(this->_Myptr() + _Off + _Count,
				this->_Myptr() + _Off + _N0, _Nm);	// move tail down
			_Traits::copy(this->_Myptr() + _Off, _Ptr, _Count);	// fill hole
			_Eos(_Num);
		}
		return (*this);
	}

	_Myt& replace(size_type _Off, size_type _N0, const _Elem *_Ptr)
	{	// replace [_Off, _Off + _N0) with [_Ptr, <null>)
		_DEBUG_POINTER(_Ptr);
		return (replace(_Off, _N0, _Ptr, _Traits::length(_Ptr)));
	}

	_Myt& replace(size_type _Off,
		size_type _N0, size_type _Count, _Elem _Ch)
	{	// replace [_Off, _Off + _N0) with _Count * _Ch
		if (this->_Mysize < _Off)
			_Xran();	// _Off off end
		if (this->_Mysize - _Off < _N0)
			_N0 = this->_Mysize - _Off;	// trim _N0 to size
		if (npos - _Count <= this->_Mysize - _N0)
			_Xlen();	// result too long
		size_type _Nm = this->_Mysize - _N0 - _Off;

		if (_Count < _N0)
			_Traits::move(this->_Myptr() + _Off + _Count,
			this->_Myptr() + _Off + _N0,
			_Nm);	// smaller hole, move tail up
		size_type _Num;
		if ((0 < _Count || 0 < _N0)
			&& _Grow(_Num = this->_Mysize + _Count - _N0))
		{	// make room and rearrange
			if (_N0 < _Count)
				_Traits::move(this->_Myptr() + _Off + _Count,
				this->_Myptr() + _Off + _N0, _Nm);	// move tail down
			_Chassign(_Off, _Count, _Ch);	// fill hole
			_Eos(_Num);
		}
		return (*this);
	}

	_Myt& replace(const_iterator _First, const_iterator _Last,
		const _Myt& _Right)
	{	// replace [_First, _Last) with _Right
		return (replace(
			_Pdif(_First, begin()), _Pdif(_Last, _First), _Right));
	}

	_Myt& replace(const_iterator _First, const_iterator _Last,
		const _Elem *_Ptr, size_type _Count)
	{	// replace [_First, _Last) with [_Ptr, _Ptr + _Count)
		return (replace(
			_Pdif(_First, begin()), _Pdif(_Last, _First), _Ptr, _Count));
	}

	_Myt& replace(const_iterator _First, const_iterator _Last,
		const _Elem *_Ptr)
	{	// replace [_First, _Last) with [_Ptr, <null>)
		return (replace(
			_Pdif(_First, begin()), _Pdif(_Last, _First), _Ptr));
	}

	_Myt& replace(const_iterator _First, const_iterator _Last,
		size_type _Count, _Elem _Ch)
	{	// replace [_First, _Last) with _Count * _Ch
		return (replace(
			_Pdif(_First, begin()), _Pdif(_Last, _First), _Count, _Ch));
	}

	template<class _Iter>
	typename _STD enable_if<_STD _Is_iterator<_Iter>::value,
		_Myt&>::type
		replace(const_iterator _First, const_iterator _Last,
		_Iter _First2, _Iter _Last2)
	{	// replace [_First, _Last) with [_First2, _Last2), input iterators
		_Myt _Right(_First2, _Last2);
		replace(_First, _Last, _Right);
		return (*this);
	}

	_Myt& replace(const_iterator _First, const_iterator _Last,
		const_pointer _First2, const_pointer _Last2)
	{	// replace [_First, _Last) with [_First2, _Last2), const pointers
		if (_First2 == _Last2)
			erase(_Pdif(_First, begin()), _Pdif(_Last, _First));
		else
			replace(_Pdif(_First, begin()), _Pdif(_Last, _First),
			&*_First2, _Last2 - _First2);
		return (*this);
	}

	_Myt& replace(const_iterator _First, const_iterator _Last,
		pointer _First2, pointer _Last2)
	{	// replace [_First, _Last) with [_First2, _Last2), const pointers
		if (_First2 == _Last2)
			erase(_Pdif(_First, begin()), _Pdif(_Last, _First));
		else
			replace(_Pdif(_First, begin()), _Pdif(_Last, _First),
			&*_First2, _Last2 - _First2);
		return (*this);
	}

	_Myt& replace(const_iterator _First, const_iterator _Last,
		const_iterator _First2, const_iterator _Last2)
	{	// replace [_First, _Last) with [_First2, _Last2), const_iterators
		if (_First2 == _Last2)
			erase(_Pdif(_First, begin()), _Pdif(_Last, _First));
		else
			replace(_Pdif(_First, begin()), _Pdif(_Last, _First),
			&*_First2, _Last2 - _First2);
		return (*this);
	}

	_Myt& replace(const_iterator _First, const_iterator _Last,
		iterator _First2, iterator _Last2)
	{	// replace [_First, _Last) with [_First2, _Last2), const_iterators
		if (_First2 == _Last2)
			erase(_Pdif(_First, begin()), _Pdif(_Last, _First));
		else
			replace(_Pdif(_First, begin()), _Pdif(_Last, _First),
			&*_First2, _Last2 - _First2);
		return (*this);
	}

	iterator begin() _NOEXCEPT
	{	// return iterator for beginning of mutable sequence
		return (_STRING_ITERATOR(this->_Myptr()));
	}

		const_iterator begin() const _NOEXCEPT
	{	// return iterator for beginning of nonmutable sequence
		return (_STRING_CONST_ITERATOR(this->_Myptr()));
	}

		iterator end() _NOEXCEPT
	{	// return iterator for end of mutable sequence
		return (_STRING_ITERATOR(this->_Myptr() + this->_Mysize));
	}

		const_iterator end() const _NOEXCEPT
	{	// return iterator for end of nonmutable sequence
		return (_STRING_CONST_ITERATOR(this->_Myptr() + this->_Mysize));
	}

		reverse_iterator rbegin() _NOEXCEPT
	{	// return iterator for beginning of reversed mutable sequence
		return (reverse_iterator(end()));
	}

		const_reverse_iterator rbegin() const _NOEXCEPT
	{	// return iterator for beginning of reversed nonmutable sequence
		return (const_reverse_iterator(end()));
	}

		reverse_iterator rend() _NOEXCEPT
	{	// return iterator for end of reversed mutable sequence
		return (reverse_iterator(begin()));
	}

		const_reverse_iterator rend() const _NOEXCEPT
	{	// return iterator for end of reversed nonmutable sequence
		return (const_reverse_iterator(begin()));
	}

		const_iterator cbegin() const _NOEXCEPT
	{	// return iterator for beginning of nonmutable sequence
		return (((const _Myt *)this)->begin());
	}

		const_iterator cend() const _NOEXCEPT
	{	// return iterator for end of nonmutable sequence
		return (((const _Myt *)this)->end());
	}

		const_reverse_iterator crbegin() const _NOEXCEPT
	{	// return iterator for beginning of reversed nonmutable sequence
		return (((const _Myt *)this)->rbegin());
	}

		const_reverse_iterator crend() const _NOEXCEPT
	{	// return iterator for end of reversed nonmutable sequence
		return (((const _Myt *)this)->rend());
	}

		void shrink_to_fit()
	{	// reduce capacity
		if ((size() | this->_ALLOC_MASK) < capacity())
		{	// worth shrinking, do it
			_Myt _Tmp(*this);
			swap(_Tmp);
		}
	}

	reference at(size_type _Off)
	{	// subscript mutable sequence with checking
		if (this->_Mysize <= _Off)
			_Xran();	// _Off off end
		return (this->_Myptr()[_Off]);
	}

	const_reference at(size_type _Off) const
	{	// subscript nonmutable sequence with checking
		if (this->_Mysize <= _Off)
			_Xran();	// _Off off end
		return (this->_Myptr()[_Off]);
	}

	reference operator[](size_type _Off)
	{	// subscript mutable sequence
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (this->_Mysize < _Off)	// sic
			_DEBUG_ERROR("string subscript out of range");

#elif __RSTD_ITERATOR_DEBUG_LEVEL__ == 1
		_SCL_SECURE_VALIDATE_RANGE(_Off <= this->_Mysize);	// sic
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		return (this->_Myptr()[_Off]);
	}

	const_reference operator[](size_type _Off) const
	{	// subscript nonmutable sequence
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (this->_Mysize < _Off)	// sic
			_DEBUG_ERROR("string subscript out of range");

#elif __RSTD_ITERATOR_DEBUG_LEVEL__ == 1
		_SCL_SECURE_VALIDATE_RANGE(_Off <= this->_Mysize);	// sic
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		return (this->_Myptr()[_Off]);
	}

	void push_back(_Elem _Ch)
	{	// insert element at end
		insert(end(), _Ch);
	}

	void pop_back()
	{	// erase element at end
		erase(this->_Mysize - 1);	// throws if _Mysize == 0
	}

	reference front()
	{	// return first element of mutable sequence
		return (*begin());
	}

	const_reference front() const
	{	// return first element of nonmutable sequence
		return (*begin());
	}

	reference back()
	{	// return last element of mutable sequence
		return (*(end() - 1));
	}

	const_reference back() const
	{	// return last element of nonmutable sequence
		return (*(end() - 1));
	}

	const _Elem *c_str() const _NOEXCEPT
	{	// return pointer to null-terminated nonmutable array
		return (this->_Myptr());
	}

		const _Elem *data() const _NOEXCEPT
	{	// return pointer to nonmutable array
		return (c_str());
	}

		size_type length() const _NOEXCEPT
	{	// return length of sequence
		return (this->_Mysize);
	}

		size_type size() const _NOEXCEPT
	{	// return length of sequence
		return (this->_Mysize);
	}

		size_type max_size() const _NOEXCEPT
	{	// return maximum possible length of sequence
		size_type _Num = this->_Getal().max_size();
		return (_Num <= 1 ? 1 : _Num - 1);
	}

		void resize(size_type _Newsize)
	{	// determine new length, padding with null elements as needed
		resize(_Newsize, _Elem());
	}

	void resize(size_type _Newsize, _Elem _Ch)
	{	// determine new length, padding with _Ch elements as needed
		if (_Newsize <= this->_Mysize)
			_Eos(_Newsize);
		else
			append(_Newsize - this->_Mysize, _Ch);
	}

	size_type capacity() const _NOEXCEPT
	{	// return current length of allocated storage
		return (this->_Myres);
	}

		void reserve(size_type _Newcap = 0)
	{	// determine new minimum length of allocated storage
		if (this->_Mysize <= _Newcap && this->_Myres != _Newcap)
		{	// change reservation
			size_type _Size = this->_Mysize;
			if (_Grow(_Newcap, true))
				_Eos(_Size);
		}
	}

	bool empty() const _NOEXCEPT
	{	// test if sequence is empty
		return (this->_Mysize == 0);
	}

		_SCL_INSECURE_DEPRECATE

		size_type copy(_Elem *_Ptr,
		size_type _Count, size_type _Off = 0) const
	{	// copy [_Off, _Off + _Count) to [_Ptr, _Ptr + _Count)
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (_Count != 0)
			_DEBUG_POINTER(_Ptr);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		if (this->_Mysize < _Off)
			_Xran();	// _Off off end
		if (this->_Mysize - _Off < _Count)
			_Count = this->_Mysize - _Off;
		_Traits::copy(_Ptr, this->_Myptr() + _Off, _Count);
		return (_Count);
	}

	size_type _Copy_s(_Elem *_Dest, size_type _Dest_size,
		size_type _Count, size_type _Off = 0) const
	{	// copy [_Off, _Off + _Count) to [_Dest, _Dest + _Count)
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (_Count != 0)
			_DEBUG_POINTER(_Dest);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		if (this->_Mysize < _Off)
			_Xran();	// _Off off end
		if (this->_Mysize - _Off < _Count)
			_Count = this->_Mysize - _Off;
		_Traits::_Copy_s(_Dest, _Dest_size, this->_Myptr() + _Off, _Count);
		return (_Count);
	}

	void _Swap_bx(_Myt& _Right)
	{	// exchange _Bx with _Right._Bx
		if (this->_BUF_SIZE <= this->_Myres)
			if (this->_BUF_SIZE <= _Right._Myres)
				_Swap_adl(this->_Bx._Ptr, _Right._Bx._Ptr);
			else
			{	// swap large with small
				pointer _Ptr = this->_Bx._Ptr;
				this->_Getal().destroy(&this->_Bx._Ptr);
				_Traits::copy(this->_Bx._Buf,
					_Right._Bx._Buf, _Right._Mysize + 1);
				this->_Getal().construct(&_Right._Bx._Ptr, _Ptr);
			}
		else
			if (_Right._Myres < this->_BUF_SIZE)
				_STD swap(this->_Bx._Buf, _Right._Bx._Buf);
			else
			{	// swap small with large
				pointer _Ptr = _Right._Bx._Ptr;
				this->_Getal().destroy(&_Right._Bx._Ptr);
				_Traits::copy(_Right._Bx._Buf,
					this->_Bx._Buf, this->_Mysize + 1);
				this->_Getal().construct(&this->_Bx._Ptr, _Ptr);
			}
	}

	void swap(_Myt& _Right)
	{	// exchange contents with _Right
		if (this == &_Right)
			;	// same object, do nothing
		else if (this->_Getal() == _Right._Getal())
		{	// same allocator, swap control information
			this->_Swap_all(_Right);
			_Swap_bx(_Right);
			_STD swap(this->_Mysize, _Right._Mysize);
			_STD swap(this->_Myres, _Right._Myres);
		}

		else if (_Alty::propagate_on_container_swap::value)
		{	// swap allocators and control information
			this->_Swap_alloc(_Right);
			_Swap_bx(_Right);
			_STD swap(this->_Bx, _Right._Bx);	// pointer bitwise copyable?
			_STD swap(this->_Mysize, _Right._Mysize);
			_STD swap(this->_Myres, _Right._Myres);
		}

		else
		{	// different allocator, do multiple assigns
			_Myt _Tmp = *this;

			*this = _Right;
			_Right = _Tmp;
		}
	}

	size_type find(const _Myt& _Right, size_type _Off = 0) const _NOEXCEPT
	{	// look for _Right beginning at or after _Off
		return (find(_Right._Myptr(), _Off, _Right.size()));
	}

		size_type find(const _Elem *_Ptr,
		size_type _Off, size_type _Count) const
	{	// look for [_Ptr, _Ptr + _Count) beginning at or after _Off
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (_Count != 0)
			_DEBUG_POINTER(_Ptr);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		if (_Count == 0 && _Off <= this->_Mysize)
			return (_Off);	// null string always matches (if inside string)

		size_type _Nm;
		if (_Off < this->_Mysize && _Count <= (_Nm = this->_Mysize - _Off))
		{	// room for match, look for it
			const _Elem *_Uptr, *_Vptr;
			for (_Nm -= _Count - 1, _Vptr = this->_Myptr() + _Off;
				(_Uptr = _Traits::find(_Vptr, _Nm, *_Ptr)) != 0;
				_Nm -= _Uptr - _Vptr + 1, _Vptr = _Uptr + 1)
				if (_Traits::compare(_Uptr, _Ptr, _Count) == 0)
					return (_Uptr - this->_Myptr());	// found a match
		}

		return (npos);	// no match
	}

	size_type find(const _Elem *_Ptr, size_type _Off = 0) const
	{	// look for [_Ptr, <null>) beginning at or after _Off
		_DEBUG_POINTER(_Ptr);
		return (find(_Ptr, _Off, _Traits::length(_Ptr)));
	}

	size_type find(_Elem _Ch, size_type _Off = 0) const
	{	// look for _Ch at or after _Off
		return (find((const _Elem *)&_Ch, _Off, 1));
	}

	size_type rfind(const _Myt& _Right, size_type _Off = npos) const _NOEXCEPT
	{	// look for _Right beginning before _Off
		return (rfind(_Right._Myptr(), _Off, _Right.size()));
	}

		size_type rfind(const _Elem *_Ptr,
		size_type _Off, size_type _Count) const
	{	// look for [_Ptr, _Ptr + _Count) beginning before _Off
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (_Count != 0)
			_DEBUG_POINTER(_Ptr);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		if (_Count == 0)
			return (_Off < this->_Mysize ? _Off
			: this->_Mysize);	// null always matches
		if (_Count <= this->_Mysize)
		{	// room for match, look for it
			const _Elem *_Uptr = this->_Myptr() +
				(_Off < this->_Mysize - _Count ? _Off
				: this->_Mysize - _Count);
			for (;; --_Uptr)
				if (_Traits::eq(*_Uptr, *_Ptr)
					&& _Traits::compare(_Uptr, _Ptr, _Count) == 0)
					return (_Uptr - this->_Myptr());	// found a match
				else if (_Uptr == this->_Myptr())
					break;	// at beginning, no more chance for match
		}

		return (npos);	// no match
	}

	size_type rfind(const _Elem *_Ptr, size_type _Off = npos) const
	{	// look for [_Ptr, <null>) beginning before _Off
		_DEBUG_POINTER(_Ptr);
		return (rfind(_Ptr, _Off, _Traits::length(_Ptr)));
	}

	size_type rfind(_Elem _Ch, size_type _Off = npos) const
	{	// look for _Ch before _Off
		return (rfind((const _Elem *)&_Ch, _Off, 1));
	}

	size_type find_first_of(const _Myt& _Right,
		size_type _Off = 0) const _NOEXCEPT
	{	// look for one of _Right at or after _Off
		return (find_first_of(_Right._Myptr(), _Off, _Right.size()));
	}

		size_type find_first_of(const _Elem *_Ptr,
		size_type _Off, size_type _Count) const
	{	// look for one of [_Ptr, _Ptr + _Count) at or after _Off
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (_Count != 0)
			_DEBUG_POINTER(_Ptr);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		if (0 < _Count && _Off < this->_Mysize)
		{	// room for match, look for it
			const _Elem *const _Vptr = this->_Myptr() + this->_Mysize;
			for (const _Elem *_Uptr = this->_Myptr() + _Off;
				_Uptr < _Vptr; ++_Uptr)
				if (_Traits::find(_Ptr, _Count, *_Uptr) != 0)
					return (_Uptr - this->_Myptr());	// found a match
		}

		return (npos);	// no match
	}

	size_type find_first_of(const _Elem *_Ptr,
		size_type _Off = 0) const
	{	// look for one of [_Ptr, <null>) at or after _Off
		_DEBUG_POINTER(_Ptr);
		return (find_first_of(_Ptr, _Off, _Traits::length(_Ptr)));
	}

	size_type find_first_of(_Elem _Ch,
		size_type _Off = 0) const
	{	// look for _Ch at or after _Off
		return (find((const _Elem *)&_Ch, _Off, 1));
	}

	size_type find_last_of(const _Myt& _Right,
		size_type _Off = npos) const _NOEXCEPT
	{	// look for one of _Right before _Off
		return (find_last_of(_Right._Myptr(), _Off, _Right.size()));
	}

		size_type find_last_of(const _Elem *_Ptr,
		size_type _Off, size_type _Count) const
	{	// look for one of [_Ptr, _Ptr + _Count) before _Off
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (_Count != 0)
			_DEBUG_POINTER(_Ptr);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		if (0 < _Count && 0 < this->_Mysize)
		{	// worth searching, do it
			const _Elem *_Uptr = this->_Myptr()
				+ (_Off < this->_Mysize ? _Off : this->_Mysize - 1);
			for (;; --_Uptr)
				if (_Traits::find(_Ptr, _Count, *_Uptr) != 0)
					return (_Uptr - this->_Myptr());	// found a match
				else if (_Uptr == this->_Myptr())
					break;	// at beginning, no more chance for match
		}

		return (npos);	// no match
	}

	size_type find_last_of(const _Elem *_Ptr,
		size_type _Off = npos) const
	{	// look for one of [_Ptr, <null>) before _Off
		_DEBUG_POINTER(_Ptr);
		return (find_last_of(_Ptr, _Off, _Traits::length(_Ptr)));
	}

	size_type find_last_of(_Elem _Ch,
		size_type _Off = npos) const
	{	// look for _Ch before _Off
		return (rfind((const _Elem *)&_Ch, _Off, 1));
	}

	size_type find_first_not_of(const _Myt& _Right,
		size_type _Off = 0) const _NOEXCEPT
	{	// look for none of _Right at or after _Off
		return (find_first_not_of(_Right._Myptr(), _Off,
		_Right.size()));
	}

		size_type find_first_not_of(const _Elem *_Ptr,
		size_type _Off, size_type _Count) const
	{	// look for none of [_Ptr, _Ptr + _Count) at or after _Off
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (_Count != 0)
			_DEBUG_POINTER(_Ptr);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		if (_Off < this->_Mysize)
		{	// room for match, look for it
			const _Elem *const _Vptr = this->_Myptr() + this->_Mysize;
			for (const _Elem *_Uptr = this->_Myptr() + _Off;
				_Uptr < _Vptr; ++_Uptr)
				if (_Traits::find(_Ptr, _Count, *_Uptr) == 0)
					return (_Uptr - this->_Myptr());
		}
		return (npos);
	}

	size_type find_first_not_of(const _Elem *_Ptr,
		size_type _Off = 0) const
	{	// look for one of [_Ptr, <null>) at or after _Off
		_DEBUG_POINTER(_Ptr);
		return (find_first_not_of(_Ptr, _Off, _Traits::length(_Ptr)));
	}

	size_type find_first_not_of(_Elem _Ch,
		size_type _Off = 0) const
	{	// look for non _Ch at or after _Off
		return (find_first_not_of((const _Elem *)&_Ch, _Off, 1));
	}

	size_type find_last_not_of(const _Myt& _Right,
		size_type _Off = npos) const _NOEXCEPT
	{	// look for none of _Right before _Off
		return (find_last_not_of(_Right._Myptr(), _Off, _Right.size()));
	}

		size_type find_last_not_of(const _Elem *_Ptr,
		size_type _Off, size_type _Count) const
	{	// look for none of [_Ptr, _Ptr + _Count) before _Off
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (_Count != 0)
			_DEBUG_POINTER(_Ptr);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		if (0 < this->_Mysize)
		{	// worth searching, do it
			const _Elem *_Uptr = this->_Myptr()
				+ (_Off < this->_Mysize ? _Off : this->_Mysize - 1);
			for (;; --_Uptr)
				if (_Traits::find(_Ptr, _Count, *_Uptr) == 0)
					return (_Uptr - this->_Myptr());
				else if (_Uptr == this->_Myptr())
					break;
		}
		return (npos);
	}

	size_type find_last_not_of(const _Elem *_Ptr,
		size_type _Off = npos) const
	{	// look for none of [_Ptr, <null>) before _Off
		_DEBUG_POINTER(_Ptr);
		return (find_last_not_of(_Ptr, _Off, _Traits::length(_Ptr)));
	}

	size_type find_last_not_of(_Elem _Ch,
		size_type _Off = npos) const
	{	// look for non _Ch before _Off
		return (find_last_not_of((const _Elem *)&_Ch, _Off, 1));
	}

	_Myt substr(size_type _Off = 0, size_type _Count = npos) const
	{	// return [_Off, _Off + _Count) as new string
		return (_Myt(*this, _Off, _Count, get_allocator()));
	}

	int compare(const _Myt& _Right) const _NOEXCEPT
	{	// compare [0, _Mysize) with _Right
		return (compare(0, this->_Mysize, _Right._Myptr(), _Right.size()));
	}

		int compare(size_type _Off, size_type _N0,
		const _Myt& _Right) const
	{	// compare [_Off, _Off + _N0) with _Right
		return (compare(_Off, _N0, _Right, 0, npos));
	}

	int compare(size_type _Off,
		size_type _N0, const _Myt& _Right,
		size_type _Roff, size_type _Count) const
	{	// compare [_Off, _Off + _N0) with _Right [_Roff, _Roff + _Count)
		if (_Right.size() < _Roff)
			_Xran();	// _Off off end
		if (_Right._Mysize - _Roff < _Count)
			_Count = _Right._Mysize - _Roff;	// trim _Count to size
		return (compare(_Off, _N0, _Right._Myptr() + _Roff, _Count));
	}

	int compare(const _Elem *_Ptr) const
	{	// compare [0, _Mysize) with [_Ptr, <null>)
		_DEBUG_POINTER(_Ptr);
		return (compare(0, this->_Mysize, _Ptr, _Traits::length(_Ptr)));
	}

	int compare(size_type _Off, size_type _N0, const _Elem *_Ptr) const
	{	// compare [_Off, _Off + _N0) with [_Ptr, <null>)
		_DEBUG_POINTER(_Ptr);
		return (compare(_Off, _N0, _Ptr, _Traits::length(_Ptr)));
	}

	int compare(size_type _Off,
		size_type _N0, const _Elem *_Ptr, size_type _Count) const
	{	// compare [_Off, _Off + _N0) with [_Ptr, _Ptr + _Count)
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (_Count != 0)
			_DEBUG_POINTER(_Ptr);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		if (this->_Mysize < _Off)
			_Xran();	// _Off off end
		if (this->_Mysize - _Off < _N0)
			_N0 = this->_Mysize - _Off;	// trim _N0 to size

		size_type _Ans = _Traits::compare(this->_Myptr() + _Off, _Ptr,
			_N0 < _Count ? _N0 : _Count);
		return (_Ans != 0 ? (int)_Ans : _N0 < _Count ? -1
			: _N0 == _Count ? 0 : +1);
	}

	allocator_type get_allocator() const _NOEXCEPT
	{	// return allocator object for values
		return (this->_Getal());
	}

		void _Chassign(size_type _Off, size_type _Count, _Elem _Ch)
	{	// assign _Count copies of _Ch beginning at _Off
		if (_Count == 1)
			_Traits::assign(*(this->_Myptr() + _Off), _Ch);
		else
			_Traits::assign(this->_Myptr() + _Off, _Count, _Ch);
	}

	void _Copy(size_type _Newsize, size_type _Oldlen)
	{	// copy _Oldlen elements to newly allocated buffer
		size_type _Newres = _Newsize | this->_ALLOC_MASK;
		if (max_size() < _Newres)
			_Newres = _Newsize;	// undo roundup if too big
		else if (this->_Myres / 2 <= _Newres / 3)
			;
		else if (this->_Myres <= max_size() - this->_Myres / 2)
			_Newres = this->_Myres
			+ this->_Myres / 2;	// grow exponentially if possible
		else
			_Newres = max_size();	// settle for max_size()

		_Elem *_Ptr;
		_TRY_BEGIN
			_Ptr = this->_Getal().allocate(_Newres + 1);
		_CATCH_ALL
			_Newres = _Newsize;	// allocation failed, undo roundup and retry
		_TRY_BEGIN
			_Ptr = this->_Getal().allocate(_Newres + 1);
		_CATCH_ALL
			_Tidy(true);	// failed again, discard storage and reraise
		_RERAISE;
		_CATCH_END
			_CATCH_END

			if (0 < _Oldlen)
				_Traits::copy(_Ptr, this->_Myptr(),
				_Oldlen);	// copy existing elements
		_Tidy(true);
		this->_Getal().construct(&this->_Bx._Ptr, _Ptr);
		this->_Myres = _Newres;
		_Eos(_Oldlen);
	}

	void _Eos(size_type _Newsize)
	{	// set new length and null terminator
		_Traits::assign(this->_Myptr()[this->_Mysize = _Newsize], _Elem());
	}

	bool _Grow(size_type _Newsize,
		bool _Trim = false)
	{	// ensure buffer is big enough, trim to size if _Trim is true
		if (max_size() < _Newsize)
			_Xlen();	// result too long
		if (this->_Myres < _Newsize)
			_Copy(_Newsize, this->_Mysize);	// reallocate to grow
		else if (_Trim && _Newsize < this->_BUF_SIZE)
			_Tidy(true,	// copy and deallocate if trimming to small string
			_Newsize < this->_Mysize ? _Newsize : this->_Mysize);
		else if (_Newsize == 0)
			_Eos(0);	// new size is zero, just null terminate
		return (0 < _Newsize);	// return true only if more work to do
	}

	bool _Inside(const _Elem *_Ptr)
	{	// test if _Ptr points inside string
		if (_Ptr == 0 || _Ptr < this->_Myptr()
			|| this->_Myptr() + this->_Mysize <= _Ptr)
			return (false);	// don't ask
		else
			return (true);
	}

	static size_type _Pdif(const_iterator _P2,
		const_iterator _P1)
	{	// compute safe iterator difference
		return (_STRING_ITER_BASE(_P2) == 0 ? 0 : _P2 - _P1);
	}

	void _Tidy(bool _Built = false,
		size_type _Newsize = 0)
	{	// initialize buffer, deallocating any storage
		if (!_Built)
			;
		else if (this->_BUF_SIZE <= this->_Myres)
		{	// copy any leftovers to small buffer and deallocate
			pointer _Ptr = this->_Bx._Ptr;
			this->_Getal().destroy(&this->_Bx._Ptr);
			if (0 < _Newsize)
				_Traits::copy(this->_Bx._Buf,
				_STD addressof(*_Ptr), _Newsize);
			this->_Getal().deallocate(_Ptr, this->_Myres + 1);
		}
		this->_Myres = this->_BUF_SIZE - 1;
		_Eos(_Newsize);
	}

	__declspec(noreturn) void _Xlen() const
	{	// report a length_error
		_STD _Xlength_error("string too long");
	}

	__declspec(noreturn) void _Xran() const
	{	// report an out_of_range error
		_STD _Xout_of_range("invalid string position");
	}
};

// STATIC npos OBJECT
template<class _Elem,
class _Traits,
class _Alloc>
	_PGLOBAL const typename basic_string<_Elem, _Traits, _Alloc>::size_type
	basic_string<_Elem, _Traits, _Alloc>::npos =
	(typename basic_string<_Elem, _Traits, _Alloc>::size_type)(-1);

template<class _Elem,
class _Traits,
class _Alloc> inline
	basic_string<_Elem, _Traits, _Alloc> operator+(
	const basic_string<_Elem, _Traits, _Alloc>& _Left,
	const basic_string<_Elem, _Traits, _Alloc>& _Right)
{	// return string + string
	basic_string<_Elem, _Traits, _Alloc> _Ans;
	_Ans.reserve(_Left.size() + _Right.size());
	_Ans += _Left;
	_Ans += _Right;
	return (_Ans);
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	basic_string<_Elem, _Traits, _Alloc> operator+(
	const _Elem *_Left,
	const basic_string<_Elem, _Traits, _Alloc>& _Right)
{	// return NTCS + string
	basic_string<_Elem, _Traits, _Alloc> _Ans;
	_Ans.reserve(_Traits::length(_Left) + _Right.size());
	_Ans += _Left;
	_Ans += _Right;
	return (_Ans);
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	basic_string<_Elem, _Traits, _Alloc> operator+(
	const _Elem _Left,
	const basic_string<_Elem, _Traits, _Alloc>& _Right)
{	// return character + string
	basic_string<_Elem, _Traits, _Alloc> _Ans;
	_Ans.reserve(1 + _Right.size());
	_Ans += _Left;
	_Ans += _Right;
	return (_Ans);
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	basic_string<_Elem, _Traits, _Alloc> operator+(
	const basic_string<_Elem, _Traits, _Alloc>& _Left,
	const _Elem *_Right)
{	// return string + NTCS
	basic_string<_Elem, _Traits, _Alloc> _Ans;
	_Ans.reserve(_Left.size() + _Traits::length(_Right));
	_Ans += _Left;
	_Ans += _Right;
	return (_Ans);
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	basic_string<_Elem, _Traits, _Alloc> operator+(
	const basic_string<_Elem, _Traits, _Alloc>& _Left,
	const _Elem _Right)
{	// return string + character
	basic_string<_Elem, _Traits, _Alloc> _Ans;
	_Ans.reserve(_Left.size() + 1);
	_Ans += _Left;
	_Ans += _Right;
	return (_Ans);
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	basic_string<_Elem, _Traits, _Alloc> operator+(
	const basic_string<_Elem, _Traits, _Alloc>& _Left,
	basic_string<_Elem, _Traits, _Alloc>&& _Right)
{	// return string + string
	return (_STD move(_Right.insert(0, _Left)));
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	basic_string<_Elem, _Traits, _Alloc> operator+(
	basic_string<_Elem, _Traits, _Alloc>&& _Left,
	const basic_string<_Elem, _Traits, _Alloc>& _Right)
{	// return string + string
	return (_STD move(_Left.append(_Right)));
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	basic_string<_Elem, _Traits, _Alloc> operator+(
	basic_string<_Elem, _Traits, _Alloc>&& _Left,
	basic_string<_Elem, _Traits, _Alloc>&& _Right)
{	// return string + string
	if (_Right.size() <= _Left.capacity() - _Left.size()
		|| _Right.capacity() - _Right.size() < _Left.size())
		return (_STD move(_Left.append(_Right)));
	else
		return (_STD move(_Right.insert(0, _Left)));
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	basic_string<_Elem, _Traits, _Alloc> operator+(
	const _Elem *_Left,
	basic_string<_Elem, _Traits, _Alloc>&& _Right)
{	// return NTCS + string
	return (_STD move(_Right.insert(0, _Left)));
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	basic_string<_Elem, _Traits, _Alloc> operator+(
	const _Elem _Left,
	basic_string<_Elem, _Traits, _Alloc>&& _Right)
{	// return character + string
	return (_STD move(_Right.insert(0, 1, _Left)));
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	basic_string<_Elem, _Traits, _Alloc> operator+(
	basic_string<_Elem, _Traits, _Alloc>&& _Left,
	const _Elem *_Right)
{	// return string + NTCS
	return (_STD move(_Left.append(_Right)));
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	basic_string<_Elem, _Traits, _Alloc> operator+(
	basic_string<_Elem, _Traits, _Alloc>&& _Left,
	const _Elem _Right)
{	// return string + character
	return (_STD move(_Left.append(1, _Right)));
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	bool operator==(
	const basic_string<_Elem, _Traits, _Alloc>& _Left,
	const basic_string<_Elem, _Traits, _Alloc>& _Right)
{	// test for string equality
	return (_Left.compare(_Right) == 0);
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	bool operator==(
	const _Elem * _Left,
	const basic_string<_Elem, _Traits, _Alloc>& _Right)
{	// test for NTCS vs. string equality
	return (_Right.compare(_Left) == 0);
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	bool operator==(
	const basic_string<_Elem, _Traits, _Alloc>& _Left,
	const _Elem *_Right)
{	// test for string vs. NTCS equality
	return (_Left.compare(_Right) == 0);
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	bool operator!=(
	const basic_string<_Elem, _Traits, _Alloc>& _Left,
	const basic_string<_Elem, _Traits, _Alloc>& _Right)
{	// test for string inequality
	return (!(_Left == _Right));
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	bool operator!=(
	const _Elem *_Left,
	const basic_string<_Elem, _Traits, _Alloc>& _Right)
{	// test for NTCS vs. string inequality
	return (!(_Left == _Right));
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	bool operator!=(
	const basic_string<_Elem, _Traits, _Alloc>& _Left,
	const _Elem *_Right)
{	// test for string vs. NTCS inequality
	return (!(_Left == _Right));
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	bool operator<(
	const basic_string<_Elem, _Traits, _Alloc>& _Left,
	const basic_string<_Elem, _Traits, _Alloc>& _Right)
{	// test if string < string
	return (_Left.compare(_Right) < 0);
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	bool operator<(
	const _Elem * _Left,
	const basic_string<_Elem, _Traits, _Alloc>& _Right)
{	// test if NTCS < string
	return (_Right.compare(_Left) > 0);
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	bool operator<(
	const basic_string<_Elem, _Traits, _Alloc>& _Left,
	const _Elem *_Right)
{	// test if string < NTCS
	return (_Left.compare(_Right) < 0);
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	bool operator>(
	const basic_string<_Elem, _Traits, _Alloc>& _Left,
	const basic_string<_Elem, _Traits, _Alloc>& _Right)
{	// test if string > string
	return (_Right < _Left);
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	bool operator>(
	const _Elem * _Left,
	const basic_string<_Elem, _Traits, _Alloc>& _Right)
{	// test if NTCS > string
	return (_Right < _Left);
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	bool operator>(
	const basic_string<_Elem, _Traits, _Alloc>& _Left,
	const _Elem *_Right)
{	// test if string > NTCS
	return (_Right < _Left);
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	bool operator<=(
	const basic_string<_Elem, _Traits, _Alloc>& _Left,
	const basic_string<_Elem, _Traits, _Alloc>& _Right)
{	// test if string <= string
	return (!(_Right < _Left));
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	bool operator<=(
	const _Elem * _Left,
	const basic_string<_Elem, _Traits, _Alloc>& _Right)
{	// test if NTCS <= string
	return (!(_Right < _Left));
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	bool operator<=(
	const basic_string<_Elem, _Traits, _Alloc>& _Left,
	const _Elem *_Right)
{	// test if string <= NTCS
	return (!(_Right < _Left));
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	bool operator>=(
	const basic_string<_Elem, _Traits, _Alloc>& _Left,
	const basic_string<_Elem, _Traits, _Alloc>& _Right)
{	// test if string >= string
	return (!(_Left < _Right));
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	bool operator>=(
	const _Elem * _Left,
	const basic_string<_Elem, _Traits, _Alloc>& _Right)
{	// test if NTCS >= string
	return (!(_Left < _Right));
}

template<class _Elem,
class _Traits,
class _Alloc> inline
	bool operator>=(
	const basic_string<_Elem, _Traits, _Alloc>& _Left,
	const _Elem *_Right)
{	// test if string >= NTCS
	return (!(_Left < _Right));
}

typedef basic_string<char, _STD char_traits<char>, _STD allocator<char> >
string;
typedef basic_string<wchar_t, _STD char_traits<wchar_t>, _STD allocator<wchar_t> >
wstring;

typedef basic_string<char16_t, _STD char_traits<char16_t>, _STD allocator<char16_t> >
u16string;
typedef basic_string<char32_t, _STD char_traits<char32_t>, _STD allocator<char32_t> >
u32string;
_STD_END

_STD_BEGIN

// TEMPLATE STRUCT SPECIALIZATION hash
template<class _Elem,
class _Traits,
class _Alloc>
struct hash<__RSTD__ basic_string<_Elem, _Traits, _Alloc> >
	: public _STD unary_function<__RSTD__ basic_string<_Elem, _Traits, _Alloc>, size_t>
{	// hash functor for basic_string
	typedef __RSTD__ basic_string<_Elem, _Traits, _Alloc> _Kty;

	size_t operator()(const _Kty& _Keyval) const
	{	// hash _Keyval to size_t value by pseudorandomizing transform
		return (_Hash_seq((const unsigned char *)_Keyval.c_str(),
			_Keyval.size() * sizeof(_Elem)));
	}
};

template<class _Elem,
class _Traits,
class _Alloc> inline
	void swap(__RSTD__ basic_string<_Elem, _Traits, _Alloc>& _Left,
	__RSTD__ basic_string<_Elem, _Traits, _Alloc>& _Right)
{	// swap _Left and _Right strings
	_Left.swap(_Right);
}
_STD_END

#pragma pop_macro("new")
#pragma warning(pop)
#pragma pack(pop)
#endif /* RC_INVOKED */
