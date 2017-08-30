#pragma once
/*
@author zhp
@date 2017/2/27 6:17
@purpose for deque release
*/
#ifndef RC_INVOKED
#include "RXutility.h"
#include <xmemory>
#include <stdexcept>
#include <deque>

#pragma pack(push,_CRT_PACKING)
#pragma warning(push,3)
#pragma push_macro("new")
#undef new

#pragma warning(disable: 4127)

__RSTD_BEGIN_
// DEQUE PARAMETERS
#define _DEQUEMAPSIZ	8	/* minimum map size, at least 1 */
#define _DEQUESIZ	(sizeof (value_type) <= 1 ? 16 \
	: sizeof (value_type) <= 2 ? 8 \
	: sizeof (value_type) <= 4 ? 4 \
	: sizeof (value_type) <= 8 ? 2 \
	: 1)	/* elements per block (a power of 2) */

// TEMPLATE CLASS _Deque_unchecked_const_iterator
template<class _Mydeque>
class _Deque_unchecked_const_iterator

{	// iterator for nonmutable deque
public:
	typedef _Deque_unchecked_const_iterator<_Mydeque> _Myiter;
	typedef _STD random_access_iterator_tag iterator_category;

	typedef typename _Mydeque::value_type value_type;
	typedef typename _Mydeque::size_type size_type;
	typedef typename _Mydeque::difference_type difference_type;
	typedef typename _Mydeque::const_pointer pointer;
	typedef typename _Mydeque::const_reference reference;

	_Deque_unchecked_const_iterator()
	{	// construct with null pointer
		_Mycont = 0;
		_Myoff = 0;
	}

	_Deque_unchecked_const_iterator(size_type _Off,
		const _Container_base12 *_Pdeque)
	{	// construct with offset _Off
		_Mycont = (_Mydeque *)_Pdeque;
		_Myoff = _Off;
	}

	reference operator*() const
	{	// return designated object
		size_type _Block = _Mycont->_Getblock(_Myoff);
		size_type _Off = _Myoff % _DEQUESIZ;
		return (_Mycont->_Map[_Block][_Off]);
	}

	pointer operator->() const
	{	// return pointer to class object
		return (_STD pointer_traits<pointer>::pointer_to(**this));
	}

	_Myiter& operator++()
	{	// preincrement
		++_Myoff;
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
		--_Myoff;
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
		_Myoff += _Off;
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
		return (_Right._Myoff <= _Myoff
			? _Myoff - _Right._Myoff
			: -(difference_type)(_Right._Myoff - _Myoff));
	}

	reference operator[](difference_type _Off) const
	{	// subscript
		return (*(*this + _Off));
	}

	bool operator==(const _Myiter& _Right) const
	{	// test for iterator equality
		return (_Myoff == _Right._Myoff);
	}

	bool operator!=(const _Myiter& _Right) const
	{	// test for iterator inequality
		return (!(*this == _Right));
	}

	bool operator<(const _Myiter& _Right) const
	{	// test if this < _Right
		return (_Myoff < _Right._Myoff);
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

	const _Container_base12 *_Getcont() const
	{	// get container pointer
		return (_Mycont);
	}

	const _Mydeque *_Mycont;	// pointer to deque
	size_type _Myoff;	// offset of element in deque
};

template<class _Mydeque> inline
_Deque_unchecked_const_iterator<_Mydeque> operator+(
typename _Deque_unchecked_const_iterator<_Mydeque>
::difference_type _Off,
_Deque_unchecked_const_iterator<_Mydeque> _Next)
{	// add offset to iterator
	return (_Next += _Off);
}

// TEMPLATE CLASS _Deque_unchecked_iterator
template<class _Mydeque>
class _Deque_unchecked_iterator
	: public _Deque_unchecked_const_iterator<_Mydeque>
{	// iterator for mutable deque
public:
	typedef _Deque_unchecked_iterator<_Mydeque> _Myiter;
	typedef _Deque_unchecked_const_iterator<_Mydeque> _Mybase;
	typedef _STD random_access_iterator_tag iterator_category;

	typedef typename _Mydeque::value_type value_type;
	typedef typename _Mydeque::size_type size_type;
	typedef typename _Mydeque::difference_type difference_type;
	typedef typename _Mydeque::pointer pointer;
	typedef typename _Mydeque::reference reference;

	_Deque_unchecked_iterator()
	{	// construct with null pointer
	}

	_Deque_unchecked_iterator(size_type _Off,
		const _Container_base12 *_Pdeque)
		: _Mybase(_Off, _Pdeque)
	{	// construct with offset _Off
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
		return (*(_Mybase *)this - _Right);
	}

	reference operator[](difference_type _Off) const
	{	// subscript
		return (*(*this + _Off));
	}
};

template<class _Mydeque> inline
_Deque_unchecked_iterator<_Mydeque> operator+(
typename _Deque_unchecked_iterator<_Mydeque>
::difference_type _Off,
_Deque_unchecked_iterator<_Mydeque> _Next)
{	// add offset to iterator
	return (_Next += _Off);
}

// TEMPLATE CLASS _Deque_const_iterator
template<class _Mydeque>
class _Deque_const_iterator
	: public _STD _Iterator_base12
{	// iterator for nonmutable deque
public:
	typedef _Deque_const_iterator<_Mydeque> _Myiter;
	typedef _STD random_access_iterator_tag iterator_category;

	typedef typename _Mydeque::value_type value_type;
	typedef typename _Mydeque::size_type size_type;
	typedef typename _Mydeque::difference_type difference_type;
	typedef typename _Mydeque::const_pointer pointer;
	typedef typename _Mydeque::const_reference reference;

	typedef _Mydeque _Mydeque_t;	// helper for expression evaluator
	enum { _EEN_DS = _DEQUESIZ };	// helper for expression evaluator
	_Deque_const_iterator()
	{	// construct with null pointer
		_Setcont(0);
		_Myoff = 0;
	}

	_Deque_const_iterator(size_type _Off, const _Container_base12 *_Pdeque)
	{	// construct with offset _Off in *_Pdeque
		_Setcont((_Mydeque *)_Pdeque);
		_Myoff = _Off;
	}

	typedef _Deque_unchecked_const_iterator<_Mydeque> _Unchecked_type;

	_Myiter& _Rechecked(_Unchecked_type _Right)
	{	// reset from unchecked iterator
		this->_Myoff = _Right._Myoff;
		return (*this);
	}

	_Unchecked_type _Unchecked() const
	{	// make an unchecked iterator
		return (_Unchecked_type(_Myoff, this->_Getcont()));
	}

	reference operator*() const
	{	// return designated object
		_Mydeque *_Mycont = ((_Mydeque *)this->_Getcont());

#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (_Mycont == 0
			|| this->_Myoff < _Mycont->_Myoff
			|| _Mycont->_Myoff + _Mycont->_Mysize <= this->_Myoff)
		{	// report error
			_DEBUG_ERROR("deque iterator not dereferencable");
			_SCL_SECURE_OUT_OF_RANGE;
		}

#elif __RSTD_ITERATOR_DEBUG_LEVEL__ == 1
		_SCL_SECURE_VALIDATE(_Mycont != 0);
		_SCL_SECURE_VALIDATE_RANGE(_Mycont->_Myoff <= this->_Myoff
			&& this->_Myoff < _Mycont->_Myoff + _Mycont->_Mysize);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ */

		_Analysis_assume_(_Mycont != 0);

		size_type _Block = _Mycont->_Getblock(_Myoff);
		size_type _Off = _Myoff % _DEQUESIZ;
		return (_Mycont->_Map[_Block][_Off]);
	}

	pointer operator->() const
	{	// return pointer to class object
		return (_STD pointer_traits<pointer>::pointer_to(**this));
	}

	_Myiter& operator++()
	{	// preincrement
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		_Mydeque *_Mycont = ((_Mydeque *)this->_Getcont());
		if (_Mycont == 0
			|| _Mycont->_Myoff + _Mycont->_Mysize <= this->_Myoff)
		{	// report error
			_DEBUG_ERROR("deque iterator not incrementable");
			_SCL_SECURE_OUT_OF_RANGE;
		}

#elif __RSTD_ITERATOR_DEBUG_LEVEL__ == 1
		_Mydeque *_Mycont = ((_Mydeque *)this->_Getcont());
		_SCL_SECURE_VALIDATE(_Mycont != 0);
		_SCL_SECURE_VALIDATE_RANGE(
			this->_Myoff < _Mycont->_Myoff + _Mycont->_Mysize);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ */

		++_Myoff;
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
		_Mydeque *_Mycont = ((_Mydeque *)this->_Getcont());
		if (_Mycont == 0
			|| this->_Myoff <= _Mycont->_Myoff)
		{	// report error
			_DEBUG_ERROR("deque iterator not decrementable");
			_SCL_SECURE_OUT_OF_RANGE;
		}

#elif __RSTD_ITERATOR_DEBUG_LEVEL__ == 1
		_Mydeque *_Mycont = ((_Mydeque *)this->_Getcont());
		_SCL_SECURE_VALIDATE(_Mycont != 0);
		_SCL_SECURE_VALIDATE_RANGE(_Mycont->_Myoff < this->_Myoff);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ */

		--_Myoff;
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
		_Mydeque *_Mycont = ((_Mydeque *)this->_Getcont());
		if (_Mycont == 0
			|| this->_Myoff + _Off < _Mycont->_Myoff
			|| _Mycont->_Myoff + _Mycont->_Mysize < this->_Myoff + _Off)
		{	// report error
			_DEBUG_ERROR("deque iterator + offset out of range");
			_SCL_SECURE_OUT_OF_RANGE;
		}

#elif __RSTD_ITERATOR_DEBUG_LEVEL__ == 1
		_Mydeque *_Mycont = ((_Mydeque *)this->_Getcont());
		_SCL_SECURE_VALIDATE(_Mycont != 0);
		_SCL_SECURE_VALIDATE_RANGE(_Mycont->_Myoff <= this->_Myoff + _Off
			&& this->_Myoff + _Off <= _Mycont->_Myoff + _Mycont->_Mysize);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ */

		_Myoff += _Off;
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
		return (_Right._Myoff <= this->_Myoff
			? this->_Myoff - _Right._Myoff
			: -(difference_type)(_Right._Myoff - this->_Myoff));
	}

	reference operator[](difference_type _Off) const
	{	// subscript
		return (*(*this + _Off));
	}

	bool operator==(const _Myiter& _Right) const
	{	// test for iterator equality
		_Compat(_Right);
		return (this->_Myoff == _Right._Myoff);
	}

	bool operator!=(const _Myiter& _Right) const
	{	// test for iterator inequality
		return (!(*this == _Right));
	}

	bool operator<(const _Myiter& _Right) const
	{	// test if this < _Right
		_Compat(_Right);
		return (this->_Myoff < _Right._Myoff);
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
		_Mydeque *_Mycont = ((_Mydeque *)this->_Getcont());
		if (_Mycont == 0
			|| _Mycont != _Right._Getcont())
		{	// report error
			_DEBUG_ERROR("deque iterators incompatible");
			_SCL_SECURE_INVALID_ARGUMENT;
		}
	}

	void _Setcont(const _Mydeque *_Pdeque)
	{	// set container pointer
		this->_Adopt(_Pdeque);
	}

#elif __RSTD_ITERATOR_DEBUG_LEVEL__ == 1
	void _Compat(const _Myiter& _Right) const
	{	// test for compatible iterator pair
		_Mydeque *_Mycont = ((_Mydeque *)this->_Getcont());
		_SCL_SECURE_VALIDATE(_Mycont != 0);
		_SCL_SECURE_VALIDATE_RANGE(_Mycont == _Right._Getcont());
	}

	void _Setcont(const _Mydeque *_Pdeque)
	{	// set container pointer
		this->_Adopt(_Pdeque);
	}

#else /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 0 */
	void _Compat(const _Myiter&) const
	{	// test for compatible iterator pair
	}

	void _Setcont(const _Mydeque *_Pdeque)
	{	// set container pointer
		this->_Adopt(_Pdeque);
	}
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ */

	size_type _Myoff;	// offset of element in deque
};

template<class _Mydeque> inline
typename _Deque_const_iterator<_Mydeque>::_Unchecked_type
_Unchecked(_Deque_const_iterator<_Mydeque> _Iter)
{	// convert to unchecked
	return (_Iter._Unchecked());
}

template<class _Mydeque> inline
_Deque_const_iterator<_Mydeque>&
_Rechecked(_Deque_const_iterator<_Mydeque>& _Iter,
typename _Deque_const_iterator<_Mydeque>
::_Unchecked_type _Right)
{	// convert to checked
	return (_Iter._Rechecked(_Right));
}

template<class _Mydeque> inline
_Deque_const_iterator<_Mydeque> operator+(
typename _Deque_const_iterator<_Mydeque>::difference_type _Off,
_Deque_const_iterator<_Mydeque> _Next)
{	// add offset to iterator
	return (_Next += _Off);
}

// TEMPLATE CLASS _Deque_iterator
template<class _Mydeque>
class _Deque_iterator
	: public _Deque_const_iterator<_Mydeque>
{	// iterator for mutable deque
public:
	typedef _Deque_iterator<_Mydeque> _Myiter;
	typedef _Deque_const_iterator<_Mydeque> _Mybase;
	typedef _Deque_unchecked_iterator<_Mydeque> _Deque_unchecked_type;
	typedef _STD random_access_iterator_tag iterator_category;

	typedef typename _Mydeque::value_type value_type;
	typedef typename _Mydeque::size_type size_type;
	typedef typename _Mydeque::difference_type difference_type;
	typedef typename _Mydeque::pointer pointer;
	typedef typename _Mydeque::reference reference;

	_Deque_iterator()
	{	// construct with null deque pointer
	}

	_Deque_iterator(size_type _Off, const _Container_base12 *_Pdeque)
		: _Mybase(_Off, _Pdeque)
	{	// construct with offset _Off in *_Pdeque
	}

	typedef _Deque_unchecked_iterator<_Mydeque> _Unchecked_type;

	_Myiter& _Rechecked(_Unchecked_type _Right)
	{	// reset from unchecked iterator
		this->_Myoff = _Right._Myoff;
		return (*this);
	}

	_Unchecked_type _Unchecked() const
	{	// make an unchecked iterator
		return (_Unchecked_type(this->_Myoff, this->_Getcont()));
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
		this->_Myoff += _Off;
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
		return (*(_Mybase *)this - _Right);
	}

	reference operator[](difference_type _Off) const
	{	// subscript
		return (*(*this + _Off));
	}
};

template<class _Mydeque> inline
typename _Deque_iterator<_Mydeque>::_Unchecked_type
_Unchecked(_Deque_iterator<_Mydeque> _Iter)
{	// convert to unchecked
	return (_Iter._Unchecked());
}

template<class _Mydeque> inline
_Deque_iterator<_Mydeque>&
_Rechecked(_Deque_iterator<_Mydeque>& _Iter,
typename _Deque_iterator<_Mydeque>
::_Unchecked_type _Right)
{	// convert to checked
	return (_Iter._Rechecked(_Right));
}

template<class _Mydeque> inline
_Deque_iterator<_Mydeque> operator+(
typename _Deque_iterator<_Mydeque>::difference_type _Off,
_Deque_iterator<_Mydeque> _Next)
{	// add offset to iterator
	return (_Next += _Off);
}

// deque TYPE WRAPPERS
template<class _Value_type,
class _Size_type,
class _Difference_type,
class _Pointer,
class _Const_pointer,
class _Reference,
class _Const_reference,
class _Mapptr_type>
struct _Deque_iter_types
{	// wraps types needed by iterators
	typedef _Value_type value_type;
	typedef _Size_type size_type;
	typedef _Difference_type difference_type;
	typedef _Pointer pointer;
	typedef _Const_pointer const_pointer;
	typedef _Reference reference;
	typedef _Const_reference const_reference;
	typedef _Mapptr_type _Mapptr;
};

template<class _Ty>
struct _Deque_simple_types
	: public _STD _Simple_types<_Ty>
{	// wraps types needed by iterators
	typedef _Ty **_Mapptr;
};

template<class _Ty,
class _Alloc0>
struct _Deque_base_types
{	// types needed for a container base
	typedef _Alloc0 _Alloc;
	typedef _Deque_base_types<_Ty, _Alloc> _Myt;

	typedef _STD _Wrap_alloc<_Alloc> _Alty0;
	typedef typename _Alty0::template rebind<_Ty>::other _Alty;


	typedef typename _Alty::pointer _Tptr;
	typedef typename _Alty::template rebind<_Tptr>::other _Alpty;
	typedef typename _Alpty::pointer _Mapptr;

	typedef typename _STD _If<_STD _Is_simple_alloc<_Alty>::value,
		_Deque_simple_types<typename _Alty::value_type>,
		_Deque_iter_types<typename _Alty::value_type,
		typename _Alty::size_type,
		typename _Alty::difference_type,
		typename _Alty::pointer,
		typename _Alty::const_pointer,
		typename _Alty::reference,
		typename _Alty::const_reference,
		_Mapptr> >::type
		_Val_types;
};

// TEMPLATE CLASS _Deque_val
template<class _Val_types>
class _Deque_val
	: public _Container_base12
{	// base class for deque to hold data
public:
	typedef _Deque_val<_Val_types> _Myt;

	typedef typename _Val_types::value_type value_type;
	typedef typename _Val_types::size_type size_type;
	typedef typename _Val_types::difference_type difference_type;
	typedef typename _Val_types::pointer pointer;
	typedef typename _Val_types::const_pointer const_pointer;
	typedef typename _Val_types::reference reference;
	typedef typename _Val_types::const_reference const_reference;
	typedef typename _Val_types::_Mapptr _Mapptr;

	typedef _Deque_iterator<_Myt> iterator;
	typedef _Deque_const_iterator<_Myt> const_iterator;

	_Deque_val()
	{	// initialize values
		_Map = _Mapptr();
		_Mapsize = 0;
		_Myoff = 0;
		_Mysize = 0;
	}

	size_type _Getblock(size_type _Off) const
	{	// determine block from offset
		// NB: _Mapsize and _DEQUESIZ are guaranteed to be powers of 2
		return ((_Off / _DEQUESIZ) & (this->_Mapsize - 1));
	}

	_Mapptr _Map;		// pointer to array of pointers to blocks
	size_type _Mapsize;	// size of map array, zero or 2^N
	size_type _Myoff;	// offset of initial element
	size_type _Mysize;	// current length of sequence
};

// TEMPLATE CLASS _Deque_alloc
template<bool _Al_has_storage,
class _Alloc_types>
class _Deque_alloc
	: public _Deque_val<typename _Alloc_types::_Val_types>
{	// base class for deque to hold allocator with storage
public:
	typename _Alloc_types::_Alty _Alval;	// allocator object

	typedef _Deque_alloc<_Al_has_storage, _Alloc_types> _Myt;
	typedef typename _Alloc_types::_Alloc _Alloc;
	typedef typename _Alloc_types::_Alty _Alty;

	typedef typename _Alloc_types::_Alpty _Alpty;

	_Deque_alloc(const _Alloc& _Al = _Alloc())
		: _Alval(_Al)
	{	// construct allocators from _Al
		_Alloc_proxy();
	}

	~_Deque_alloc() _NOEXCEPT
	{	// destroy proxy
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
		typename _Alty::template rebind<_Container_proxy>::other
			_Alproxy(this->_Alval);
		this->_Myproxy = _Alproxy.allocate(1);
		_Alproxy.construct(this->_Myproxy, _Container_proxy());
		this->_Myproxy->_Mycont = this;
	}

	void _Free_proxy()
	{	// destroy proxy
		typename _Alty::template rebind<_Container_proxy>::other
			_Alproxy(this->_Alval);
		this->_Orphan_all();
		_Alproxy.destroy(this->_Myproxy);
		_Alproxy.deallocate(this->_Myproxy, 1);
		this->_Myproxy = 0;
	}

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
class _Deque_alloc<false, _Alloc_types>
	: public _Deque_val<typename _Alloc_types::_Val_types>
{	// base class for deque to hold allocator with no storage
public:
	typedef _Deque_alloc<false, _Alloc_types> _Myt;
	typedef typename _Alloc_types::_Alloc _Alloc;

	typedef typename _Alloc_types::_Alty _Alty;

	typedef typename _Alloc_types::_Alpty _Alpty;

	_Deque_alloc(const _Alloc& = _Alloc())
	{	// construct allocators from _Al
		_Alloc_proxy();
	}

	~_Deque_alloc() _NOEXCEPT
	{	// destroy proxy
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
		typename _Alty::template rebind<_Container_proxy>::other
			_Alproxy;
		this->_Myproxy = _Alproxy.allocate(1);
		_Alproxy.construct(this->_Myproxy, _Container_proxy());
		this->_Myproxy->_Mycont = this;
	}

	void _Free_proxy()
	{	// destroy proxy
		typename _Alty::template rebind<_Container_proxy>::other
			_Alproxy;
		this->_Orphan_all();
		_Alproxy.destroy(this->_Myproxy);
		_Alproxy.deallocate(this->_Myproxy, 1);
		this->_Myproxy = 0;
	}

	_Alty _Getal() const
	{	// get reference to allocator
		return (_Alty());
	}
};

// TEMPLATE CLASS deque
template<class _Ty,
class _Alloc = _STD allocator<_Ty> >
class deque
	: public _Deque_alloc<!_STD is_empty<_Alloc>::value,
	_Deque_base_types<_Ty, _Alloc> >
{	// circular queue of pointers to blocks
public:
	typedef deque<_Ty, _Alloc> _Myt;
	typedef _Deque_alloc<!_STD is_empty<_Alloc>::value,
		_Deque_base_types<_Ty, _Alloc> > _Mybase;
	typedef _Alloc allocator_type;

	typedef typename _Mybase::_Alty _Alty;
	typedef typename _Mybase::_Alpty _Alpty;
	typedef typename _Mybase::_Mapptr _Mapptr;

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

	static const int _EEM_DS = _DEQUESIZ;
	enum { _EEN_DS = _DEQUESIZ };	// helper for expression evaluator
	deque()
		: _Mybase()
	{	// construct empty deque
	}

	explicit deque(const _Alloc& _Al)
		: _Mybase(_Al)
	{	// construct empty deque with allocator
	}

	explicit deque(size_type _Count)
		: _Mybase()
	{	// construct from _Count * value_type()
		resize(_Count);
	}

	deque(size_type _Count, const value_type& _Val)
		: _Mybase()
	{	// construct from _Count * _Val
		_Construct_n(_Count, _Val);
	}

	deque(size_type _Count, const value_type& _Val, const _Alloc& _Al)
		: _Mybase(_Al)
	{	// construct from _Count * _Val with allocator
		_Construct_n(_Count, _Val);
	}

	deque(const _Myt& _Right)

		: _Mybase(_Right._Getal().select_on_container_copy_construction())


	{	// construct by copying _Right
		_Construct(_Right.begin(), _Right.end());
	}

	deque(const _Myt& _Right, const _Alloc& _Al)
		: _Mybase(_Al)
	{	// construct by copying _Right
		_Construct(_Right.begin(), _Right.end());
	}

	template<class _Iter,
	class = typename _STD enable_if<_STD _Is_iterator<_Iter>::value,
		void>::type>
		deque(_Iter _First, _Iter _Last)
		: _Mybase()
	{	// construct from [_First, _Last)
		_Construct(_First, _Last);
	}

	template<class _Iter,
	class = typename _STD enable_if<_STD _Is_iterator<_Iter>::value,
		void>::type>
		deque(_Iter _First, _Iter _Last, const _Alloc& _Al)
		: _Mybase(_Al)
	{	// construct from [_First, _Last) with allocator
		_Construct(_First, _Last);
	}

	template<class _Iter>
	void _Construct(_Iter _First, _Iter _Last)
	{	// initialize from [_First, _Last), input iterators
		_TRY_BEGIN

			for (; _First != _Last; ++_First)
				emplace_back(*_First);

		_CATCH_ALL
			_Tidy();
		_RERAISE;
		_CATCH_END
	}

	void _Construct_n(size_type _Count, const value_type& _Val)
	{	// construct from _Count * _Val
		_TRY_BEGIN
			for (; 0 < _Count; --_Count)
				push_back(_Val);
		_CATCH_ALL
			_Tidy();
		_RERAISE;
		_CATCH_END
	}

#define _PUSH_FRONT_BEGIN \
	if (this->_Myoff % _DEQUESIZ == 0 \
		&& this->_Mapsize <= (this->_Mysize + _DEQUESIZ) / _DEQUESIZ) \
		_Growmap(1); \
	this->_Myoff &= this->_Mapsize * _DEQUESIZ - 1; \
	size_type _Newoff = this->_Myoff != 0 ? this->_Myoff \
		: this->_Mapsize * _DEQUESIZ; \
	size_type _Block = this->_Getblock(--_Newoff); \
	if (this->_Map[_Block] == pointer()) \
		this->_Map[_Block] = this->_Getal().allocate(_DEQUESIZ)

#define _PUSH_FRONT_END \
	this->_Myoff = _Newoff; \
	++this->_Mysize

#define _PUSH_BACK_BEGIN \
	if ((this->_Myoff + this->_Mysize) % _DEQUESIZ == 0 \
		&& this->_Mapsize <= (this->_Mysize + _DEQUESIZ) / _DEQUESIZ) \
		_Growmap(1); \
	this->_Myoff &= this->_Mapsize * _DEQUESIZ - 1; \
	size_type _Newoff = this->_Myoff + this->_Mysize; \
	size_type _Block = this->_Getblock(_Newoff); \
	if (this->_Map[_Block] == pointer()) \
		this->_Map[_Block] = this->_Getal().allocate(_DEQUESIZ)

#define _PUSH_BACK_END \
	++this->_Mysize

	deque(_Myt&& _Right)
		: _Mybase(_Right._Getal())
	{	// construct by moving _Right
		_Assign_rv(_STD forward<_Myt>(_Right), _STD true_type());
	}

	deque(_Myt&& _Right, const _Alloc& _Al)
		: _Mybase(_Al)
	{	// construct by moving _Right
		_Assign_rv(_STD forward<_Myt>(_Right));
	}

	_Myt& operator=(_Myt&& _Right)
	{	// assign by moving _Right
		if (this != &_Right)
		{	// different, assign it
			_Tidy();
			if (_Alty::propagate_on_container_move_assignment::value
				&& this->_Getal() != _Right._Getal())
				this->_Change_alloc(_Right._Getal());
			_Assign_rv(_STD forward<_Myt>(_Right));
		}
		return (*this);
	}

	void _Assign_rv(_Myt&& _Right, _STD true_type)
	{	// move from _Right, stealing its contents
		this->_Swap_all((_Myt&)_Right);
		this->_Map = _Right._Map;
		this->_Mapsize = _Right._Mapsize;
		this->_Myoff = _Right._Myoff;
		this->_Mysize = _Right._Mysize;

		_Right._Map = _Mapptr();
		_Right._Mapsize = 0;
		_Right._Myoff = 0;
		_Right._Mysize = 0;
	}

	void _Assign_rv(_Myt&& _Right, _STD false_type)
	{	// move from _Right, possibly moving its contents
		if (get_allocator() == _Right.get_allocator())
			_Assign_rv(_STD forward<_Myt>(_Right), _STD true_type());
		else
			_Construct(_STD make_move_iterator(_Right.begin()),
			_STD make_move_iterator(_Right.end()));
	}

	void _Assign_rv(_Myt&& _Right)
	{	// assign by moving _Right
		_Assign_rv(_STD forward<_Myt>(_Right),
			typename _Alty::propagate_on_container_move_assignment());
	}


	void push_front(value_type&& _Val)
	{	// insert element at beginning
		this->_Orphan_all();
		_PUSH_FRONT_BEGIN;
		this->_Getal().construct(
			this->_Map[_Block] + _Newoff % _DEQUESIZ,
			_STD forward<value_type>(_Val));
		_PUSH_FRONT_END;
	}

	void push_back(value_type&& _Val)
	{	// insert element at end
		this->_Orphan_all();
		_PUSH_BACK_BEGIN;
		this->_Getal().construct(
			this->_Map[_Block] + _Newoff % _DEQUESIZ,
			_STD forward<value_type>(_Val));
		_PUSH_BACK_END;
	}

	iterator insert(const_iterator _Where, _Ty&& _Val)
	{	// insert _Val at _Where
		return (emplace(_Where, _STD move(_Val)));
	}

	template<class... _Valty>
	void emplace_front(_Valty&&... _Val)
	{	// insert element at beginning
		this->_Orphan_all();
		_PUSH_FRONT_BEGIN;
		this->_Getal().construct(
			this->_Map[_Block] + _Newoff % _DEQUESIZ,
			_STD forward<_Valty>(_Val)...);
		_PUSH_FRONT_END;
	}

	template<class... _Valty>
	void emplace_back(_Valty&&... _Val)
	{	// insert element at end
		this->_Orphan_all();
		_PUSH_BACK_BEGIN;
		this->_Getal().construct(
			this->_Map[_Block] + _Newoff % _DEQUESIZ,
			_STD forward<_Valty>(_Val)...);
		_PUSH_BACK_END;
	}

	template<class... _Valty>
	iterator emplace(const_iterator _Where, _Valty&&... _Val)
	{	// insert element at _Where
		size_type _Off = _Where - begin();

#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (this->_Mysize < _Off)
			_DEBUG_ERROR("deque emplace iterator outside range");
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		if (_Off <= this->_Mysize / 2)
		{	// closer to front, push to front then rotate
			emplace_front(_STD forward<_Valty>(_Val)...);
			_STD rotate(begin(), begin() + 1, begin() + 1 + _Off);
		}
		else
		{	// closer to back, push to back then rotate
			emplace_back(_STD forward<_Valty>(_Val)...);
			_STD rotate(begin() + _Off, end() - 1, end());
		}
		return (begin() + _Off);
	}


	deque(_XSTD initializer_list<value_type> _Ilist,
		const _Alloc& _Al = allocator_type())
		: _Mybase(_Al)
	{	// construct from initializer_list
		insert(begin(), _Ilist.begin(), _Ilist.end());
	}

	_Myt& operator=(_XSTD initializer_list<value_type> _Ilist)
	{	// assign initializer_list
		assign(_Ilist.begin(), _Ilist.end());
		return (*this);
	}

	void assign(_XSTD initializer_list<value_type> _Ilist)
	{	// assign initializer_list
		assign(_Ilist.begin(), _Ilist.end());
	}

	iterator insert(const_iterator _Where,
		_XSTD initializer_list<value_type> _Ilist)
	{	// insert initializer_list
		return (insert(_Where, _Ilist.begin(), _Ilist.end()));
	}

	~deque() _NOEXCEPT
	{	// destroy the deque
		_Tidy();
	}

		_Myt& operator=(const _Myt& _Right)
	{	// assign _Right
		if (this != &_Right)
		{	// different, assign it
			if (this->_Getal() != _Right._Getal()
				&& _Alty::propagate_on_container_copy_assignment::value)
			{	// change allocator before copying
				_Tidy();
				this->_Change_alloc(_Right._Getal());
			}

			this->_Orphan_all();

			if (_Right._Mysize == 0)
				clear();
			else if (_Right._Mysize <= this->_Mysize)
			{	// enough elements, copy new and destroy old
				iterator _Mid = _STD copy(_Right.begin(), _Right.end(),
					begin());
				erase(_Mid, end());
			}
			else
			{	// new sequence longer, copy and construct new
				const_iterator _Mid = _Right.begin() + this->_Mysize;
				_STD copy(_Right.begin(), _Mid, begin());
				insert(end(), _Mid, _Right.end());
			}
		}
		return (*this);
	}

	iterator begin() _NOEXCEPT
	{	// return iterator for beginning of mutable sequence
		return (iterator(this->_Myoff, this));
	}

		const_iterator begin() const _NOEXCEPT
	{	// return iterator for beginning of nonmutable sequence
		return (const_iterator(this->_Myoff, this));
	}

		iterator end() _NOEXCEPT
	{	// return iterator for end of mutable sequence
		return (iterator(this->_Myoff + this->_Mysize, this));
	}

		const_iterator end() const _NOEXCEPT
	{	// return iterator for end of nonmutable sequence
		return (const_iterator(this->_Myoff + this->_Mysize, this));
	}

		iterator _Make_iter(const_iterator _Where) const
	{	// make iterator from const_iterator
		return (iterator(_Where._Myoff, this));
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
		size_type _Oldcapacity = _DEQUESIZ * this->_Mapsize;
		size_type _Newcapacity = _Oldcapacity / 2;

		if (_Newcapacity < _DEQUESIZ * _DEQUEMAPSIZ)
			_Newcapacity = _DEQUESIZ * _DEQUEMAPSIZ;

		if ((empty() && 0 < this->_Mapsize)
			|| (!empty()
			&& size() <= _Newcapacity
			&& _Newcapacity < _Oldcapacity))
		{	// worth shrinking, do it
			_Myt _Tmp(_STD make_move_iterator(begin()),
				_STD make_move_iterator(end()));
			swap(_Tmp);
		}
	}

	void resize(size_type _Newsize)
	{	// determine new length, padding as needed
		while (this->_Mysize < _Newsize)
			emplace_back();

		while (_Newsize < this->_Mysize)
			pop_back();
	}

	void resize(size_type _Newsize, const value_type& _Val)
	{	// determine new length, padding with _Val elements as needed
		while (this->_Mysize < _Newsize)
			push_back(_Val);
		while (_Newsize < this->_Mysize)
			pop_back();
	}

	size_type size() const _NOEXCEPT
	{	// return length of sequence
		return (this->_Mysize);
	}

		size_type max_size() const _NOEXCEPT
	{	// return maximum possible length of sequence
		return (this->_Getal().max_size());
	}

		bool empty() const _NOEXCEPT
	{	// test if sequence is empty
		return (this->_Mysize == 0);
	}

		allocator_type get_allocator() const _NOEXCEPT
	{	// return allocator object for values
		return (this->_Getal());
	}

		const_reference at(size_type _Pos) const
	{	// subscript nonmutable sequence with checking
		if (this->_Mysize <= _Pos)
			_Xran();
		return (*(begin() + _Pos));
	}

	reference at(size_type _Pos)
	{	// subscript mutable sequence with checking
		if (this->_Mysize <= _Pos)
			_Xran();
		return (*(begin() + _Pos));
	}

	const_reference operator[](size_type _Pos) const
	{	// subscript nonmutable sequence
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (this->_Mysize <= _Pos)
			_DEBUG_ERROR("deque subscript out of range");
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		return (*(begin() + _Pos));
	}

	reference operator[](size_type _Pos)
	{	// subscript mutable sequence
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (this->_Mysize <= _Pos)
			_DEBUG_ERROR("deque subscript out of range");
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		return (*(begin() + _Pos));
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

	void push_front(const value_type& _Val)
	{	// insert element at beginning
		this->_Orphan_all();
		_PUSH_FRONT_BEGIN;
		this->_Getal().construct(
			this->_Map[_Block] + _Newoff % _DEQUESIZ, _Val);
		_PUSH_FRONT_END;
	}

	void pop_front()
	{	// erase element at beginning
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (empty())
			_DEBUG_ERROR("deque empty before pop");
		else
		{	// something to erase, do it
			_Orphan_off(this->_Myoff);
			size_type _Block = this->_Getblock(this->_Myoff);
			this->_Getal().destroy(
				this->_Map[_Block] + this->_Myoff % _DEQUESIZ);
			if (--this->_Mysize == 0)
				this->_Myoff = 0;
			else
				++this->_Myoff;
		}

#else /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */
		size_type _Block = this->_Getblock(this->_Myoff);
		this->_Getal().destroy(
			this->_Map[_Block] + this->_Myoff % _DEQUESIZ);
		if (--this->_Mysize == 0)
			this->_Myoff = 0;
		else
			++this->_Myoff;
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */
	}

	void push_back(const value_type& _Val)
	{	// insert element at end
		this->_Orphan_all();
		_PUSH_BACK_BEGIN;
		this->_Getal().construct(
			this->_Map[_Block] + _Newoff % _DEQUESIZ, _Val);
		_PUSH_BACK_END;
	}

	void pop_back()
	{	// erase element at end
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (empty())
			_DEBUG_ERROR("deque empty before pop");
		else
		{	// something to erase, do it
			size_type _Newoff = this->_Myoff + this->_Mysize - 1;
			_Orphan_off(_Newoff);
			size_type _Block = this->_Getblock(_Newoff);
			this->_Getal().destroy(
				this->_Map[_Block] + _Newoff % _DEQUESIZ);
			if (--this->_Mysize == 0)
				this->_Myoff = 0;
		}

#else /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */
		size_type _Newoff = this->_Myoff + this->_Mysize - 1;
		size_type _Block = this->_Getblock(_Newoff);
		this->_Getal().destroy(
			this->_Map[_Block] + _Newoff % _DEQUESIZ);
		if (--this->_Mysize == 0)
			this->_Myoff = 0;
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */
	}

	template<class _Iter>
	typename _STD enable_if<_STD _Is_iterator<_Iter>::value,
		void>::type
		assign(_Iter _First, _Iter _Last)
	{	// assign [_First, _Last), input iterators
		clear();

		for (; _First != _Last; ++_First)
			emplace_back(*_First);
	}

	void assign(size_type _Count, const value_type& _Val)
	{	// assign _Count * _Val
		erase(begin(), end());
		_Insert_n(begin(), _Count, _Val);
	}

	iterator insert(const_iterator _Where,
		const value_type& _Val)
	{	// insert _Val at _Where
		size_type _Off = _Where - begin();

#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (this->_Mysize < _Off)
			_DEBUG_ERROR("deque insert iterator outside range");
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		if (_Off <= this->_Mysize / 2)
		{	// closer to front, push to front then copy
			push_front(_Val);
			_STD rotate(begin(), begin() + 1, begin() + 1 + _Off);
		}
		else
		{	// closer to back, push to back then copy
			push_back(_Val);
			_STD rotate(begin() + _Off, end() - 1, end());
		}
		return (begin() + _Off);
	}

	iterator insert(const_iterator _Where, size_type _Count,
		const value_type& _Val)
	{	// insert _Count * _Val at _Where
		size_type _Off = _Where - begin();
		_Insert_n(_Where, _Count, _Val);
		return (begin() + _Off);
	}

	template<class _Iter>
	typename _STD enable_if<_STD _Is_iterator<_Iter>::value,
		iterator>::type
		insert(const_iterator _Where, _Iter _First, _Iter _Last)
	{	// insert [_First, _Last) at _Where, input iterators
		size_type _Off = _Where - begin();

#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (this->_Mysize < _Off)
			_DEBUG_ERROR("deque insert iterator outside range");
		_DEBUG_RANGE(_First, _Last);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		size_type _Oldsize = this->_Mysize;

		if (_First == _Last)
			;
		else if (_Off <= this->_Mysize / 2)
		{	// closer to front, push to front then rotate
			_TRY_BEGIN
				for (; _First != _Last; ++_First)
					push_front(*_First);	// prepend flipped

			_CATCH_ALL
				for (; _Oldsize < this->_Mysize;)
					pop_front();	// restore old size, at least
			_RERAISE;
			_CATCH_END

				size_type _Num = this->_Mysize - _Oldsize;
			_STD reverse(begin(), begin() + _Num);	// flip new stuff in place
			_STD rotate(begin(), begin() + _Num, begin() + _Num + _Off);
		}
		else
		{	// closer to back
			_TRY_BEGIN
				for (; _First != _Last; ++_First)
					push_back(*_First);	// append

			_CATCH_ALL
				for (; _Oldsize < this->_Mysize;)
					pop_back();	// restore old size, at least
			_RERAISE;
			_CATCH_END

				_STD rotate(begin() + _Off, begin() + _Oldsize, end());
		}
		return (begin() + _Off);
	}

	iterator erase(const_iterator _Where)
	{	// erase element at _Where
		return (erase(_Where, _Where + 1));
	}

	iterator erase(const_iterator _First_arg,
		const_iterator _Last_arg)
	{	// erase [_First, _Last)
		iterator _First = _Make_iter(_First_arg);
		iterator _Last = _Make_iter(_Last_arg);

#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (_Last < _First
			|| _First < begin() || end() < _Last)
			_DEBUG_ERROR("deque erase iterator outside range");
		_DEBUG_RANGE(_First, _Last);

		size_type _Off = _First - begin();
		size_type _Count = _Last - _First;
		bool _Moved = 0 < _Off && _Off + _Count < this->_Mysize;

#else /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */
		size_type _Off = _First - begin();
		size_type _Count = _Last - _First;
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		if (_Off < (size_type)(end() - _Last))
		{	// closer to front
			_Move_backward(begin(), _First, _Last);	// copy over hole
			for (; 0 < _Count; --_Count)
				pop_front();	// pop copied elements
		}
		else
		{	// closer to back
			_Move(_Last, end(), _First);	// copy over hole
			for (; 0 < _Count; --_Count)
				pop_back();	// pop copied elements
		}

#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (_Moved)
			this->_Orphan_all();
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		return (begin() + _Off);
	}

	void clear() _NOEXCEPT
	{	// erase all
		_Tidy();
	}

		void swap(_Myt& _Right)
	{	// exchange contents with _Right
		if (this == &_Right)
			;	// same object, do nothing
		else if (this->_Getal() == _Right._Getal())
		{	// same allocator, swap control information
			this->_Swap_all(_Right);
			_Swap_adl(this->_Map, _Right._Map);
			_STD swap(this->_Mapsize, _Right._Mapsize);
			_STD swap(this->_Myoff, _Right._Myoff);
			_STD swap(this->_Mysize, _Right._Mysize);
		}

		else if (_Alty::propagate_on_container_swap::value)
		{	// swap allocators and control information
			this->_Swap_alloc(_Right);
			_Swap_adl(this->_Map, _Right._Map);
			_STD swap(this->_Mapsize, _Right._Mapsize);
			_STD swap(this->_Myoff, _Right._Myoff);
			_STD swap(this->_Mysize, _Right._Mysize);
		}
		else
		{	// containers are incompatible
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
			_DEBUG_ERROR("deque containers incompatible for swap");

#else /* ITERATOR_DEBUG_LEVEL == 2 */
			_XSTD terminate();
#endif /* ITERATOR_DEBUG_LEVEL == 2 */
		}

	}

protected:
	void _Insert_n(const_iterator _Where,
		size_type _Count, const value_type& _Val)
	{	// insert _Count * _Val at _Where
		iterator _Mid;
		size_type _Num;
		size_type _Off = _Where - begin();
		size_type _Rem = this->_Mysize - _Off;
		size_type _Oldsize = this->_Mysize;

#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (this->_Mysize < _Off)
			_DEBUG_ERROR("deque insert iterator outside range");
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		if (_Off < _Rem)
		{	// closer to front
			_TRY_BEGIN
				if (_Off < _Count)
				{	// insert longer than prefix
					for (_Num = _Count - _Off; 0 < _Num; --_Num)
						push_front(_Val);	// push excess values
					for (_Num = _Off; 0 < _Num; --_Num)
						push_front(begin()[_Count - 1]);	// push prefix

					_Mid = begin() + _Count;
					_STD fill(_Mid, _Mid + _Off,
						_Val);	// fill in rest of values
				}
				else
				{	// insert not longer than prefix
					for (_Num = _Count; 0 < _Num; --_Num)
						push_front(begin()[_Count - 1]);	// push part of prefix

					_Mid = begin() + _Count;
					value_type _Tmp = _Val;	// in case _Val is in sequence
					_Move(_Mid + _Count, _Mid + _Off,
						_Mid);	// copy rest of prefix
					_STD fill(begin() + _Off, _Mid + _Off,
						_Tmp);	// fill in values
				}
			_CATCH_ALL
				for (; _Oldsize < this->_Mysize;)
					pop_front();	// restore old size, at least
			_RERAISE;
			_CATCH_END
		}
		else
		{		// closer to back
			_TRY_BEGIN
				if (_Rem < _Count)
				{	// insert longer than suffix
					for (_Num = _Count - _Rem; 0 < _Num; --_Num)
						push_back(_Val);	// push excess values
					for (_Num = 0; _Num < _Rem; ++_Num)
						push_back(begin()[_Off + _Num]);	// push suffix

					_Mid = begin() + _Off;
					_STD fill(_Mid, _Mid + _Rem,
						_Val);	// fill in rest of values
				}
				else
				{	// insert not longer than prefix
					for (_Num = 0; _Num < _Count; ++_Num)
						push_back(begin()[_Off + _Rem
						- _Count + _Num]);	// push part of prefix

					_Mid = begin() + _Off;
					value_type _Tmp = _Val;	// in case _Val is in sequence
					_Move_backward(_Mid, _Mid + _Rem - _Count,
						_Mid + _Rem);	// copy rest of prefix
					_STD fill(_Mid, _Mid + _Count,
						_Tmp);	// fill in values
				}
			_CATCH_ALL
				for (; _Oldsize < this->_Mysize;)
					pop_back();	// restore old size, at least
			_RERAISE;
			_CATCH_END
		}
	}

	__declspec(noreturn) void _Xlen() const
	{	// report a length_error
		_STD _Xlength_error("deque<T> too long");
	}

	__declspec(noreturn) void _Xran() const
	{	// report an out_of_range error
		_STD _Xout_of_range("invalid deque<T> subscript");
	}

	void _Growmap(size_type _Count)
	{	// grow map by at least _Count pointers, _Mapsize a power of 2
		static_assert(1 < _DEQUEMAPSIZ,
			"The _Xlen() test should always be performed.");

		typedef typename _Alpty::pointer _Blockptr;
		_Alpty _Almap(this->_Getal());
		size_type _Newsize = 0 < this->_Mapsize ? this->_Mapsize : 1;
		while (_Newsize - this->_Mapsize < _Count || _Newsize < _DEQUEMAPSIZ)
		{	// scale _Newsize to 2^N >= _Mapsize + _Count
			if (max_size() / _DEQUESIZ - _Newsize < _Newsize)
				_Xlen();	// result too long
			_Newsize *= 2;
		}
		_Count = _Newsize - this->_Mapsize;

		size_type _Myboff = this->_Myoff / _DEQUESIZ;
		_Mapptr _Newmap = _Almap.allocate(this->_Mapsize + _Count);
		_Mapptr _Myptr = _Newmap + _Myboff;

		_Myptr = _Uninitialized_copy(this->_Map + _Myboff,
			this->_Map + this->_Mapsize,
			_Myptr, _Almap);	// copy initial to end
		if (_Myboff <= _Count)
		{	// increment greater than offset of initial block
			_Myptr = _Uninitialized_copy(this->_Map,
				this->_Map + _Myboff,
				_Myptr, _Almap);	// copy rest of old
			_Uninitialized_default_fill_n(_Myptr, _Count - _Myboff,
				_Almap);	// clear suffix of new
			_Uninitialized_default_fill_n(_Newmap, _Myboff,
				_Almap);	// clear prefix of new
		}
		else
		{	// increment not greater than offset of initial block
			_Uninitialized_copy(this->_Map,
				this->_Map + _Count,
				_Myptr, _Almap);	// copy more old
			_Myptr = _Uninitialized_copy(this->_Map + _Count,
				this->_Map + _Myboff,
				_Newmap, _Almap);	// copy rest of old
			_Uninitialized_default_fill_n(_Myptr, _Count,
				_Almap);	// clear rest to initial block
		}

		_Destroy_range(this->_Map + _Myboff, this->_Map + this->_Mapsize,
			_Almap);
		if (this->_Map != _Mapptr())
			_Almap.deallocate(this->_Map,
			this->_Mapsize);	// free storage for old

		this->_Map = _Newmap;	// point at new
		this->_Mapsize += _Count;
	}

	void _Tidy()
	{	// free all storage
		_Alpty _Almap(this->_Getal());
		while (!empty())
			pop_back();
		for (size_type _Block = this->_Mapsize; 0 < _Block;)
		{	// free storage for a block and destroy pointer
			if (this->_Map[--_Block] != pointer())
			{	// free block and destroy its pointer
				this->_Getal().deallocate(this->_Map[_Block], _DEQUESIZ);
				this->_Getal().destroy(&this->_Map[_Block]);
			}
		}

		if (this->_Map != _Mapptr())
			_Almap.deallocate(this->_Map,
			this->_Mapsize);	// free storage for map
		this->_Mapsize = 0;
		this->_Map = _Mapptr();
	}

#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
	void _Orphan_off(size_type _Offlo) const
	{	// orphan iterators with specified offset(s)
		size_type _Offhigh = this->_Myoff + this->_Mysize <= _Offlo + 1
			? (size_type)(-1) : _Offlo;
		if (_Offlo == this->_Myoff)
			_Offlo = 0;

		_Lockit _Lock(_LOCK_DEBUG);
		const_iterator **_Pnext = (const_iterator **)this->_Getpfirst();
		if (_Pnext != 0)
			while (*_Pnext != 0)
				if ((*_Pnext)->_Myoff < _Offlo
					|| _Offhigh < (*_Pnext)->_Myoff)
					_Pnext = (const_iterator **)(*_Pnext)->_Getpnext();
				else
				{	// orphan the iterator
					(*_Pnext)->_Clrcont();
					*_Pnext = *(const_iterator **)(*_Pnext)->_Getpnext();
				}
	}
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */
};

// deque TEMPLATE OPERATORS

template<class _Ty,
class _Alloc> inline
	bool operator==(const deque<_Ty, _Alloc>& _Left,
	const deque<_Ty, _Alloc>& _Right)
{	// test for deque equality
	return (_Left.size() == _Right.size()
		&& equal(_Left.begin(), _Left.end(), _Right.begin()));
}

template<class _Ty,
class _Alloc> inline
	bool operator!=(const deque<_Ty, _Alloc>& _Left,
	const deque<_Ty, _Alloc>& _Right)
{	// test for deque inequality
	return (!(_Left == _Right));
}

template<class _Ty,
class _Alloc> inline
	bool operator<(const deque<_Ty, _Alloc>& _Left,
	const deque<_Ty, _Alloc>& _Right)
{	// test if _Left < _Right for deques
	return (lexicographical_compare(_Left.begin(), _Left.end(),
		_Right.begin(), _Right.end()));
}

template<class _Ty,
class _Alloc> inline
	bool operator<=(const deque<_Ty, _Alloc>& _Left,
	const deque<_Ty, _Alloc>& _Right)
{	// test if _Left <= _Right for deques
	return (!(_Right < _Left));
}

template<class _Ty,
class _Alloc> inline
	bool operator>(const deque<_Ty, _Alloc>& _Left,
	const deque<_Ty, _Alloc>& _Right)
{	// test if _Left > _Right for deques
	return (_Right < _Left);
}

template<class _Ty,
class _Alloc> inline
	bool operator>=(const deque<_Ty, _Alloc>& _Left,
	const deque<_Ty, _Alloc>& _Right)
{	// test if _Left >= _Right for deques
	return (!(_Left < _Right));
}

template<class _Ty, class _Alloc>
_STD deque<_Ty, _Alloc> to_std(const __RSTD__ deque<_Ty, _Alloc>& v){
	_STD deque<_Ty, _Alloc> res;
	for (auto& va : v)
	{
		res.push_back(va);
	}
	return res;
}

template<class _Ty, class _Alloc>
__RSTD__ deque<_Ty, _Alloc> from_std(const _STD deque<_Ty, _Alloc>& v){
	__RSTD__ deque<_Ty, _Alloc> res;
	for (auto& va : v)
	{
		res.push_back(va);
	}
	return res;
}

_STD_END

_STD_BEGIN
template<class _Ty,
class _Alloc> inline
	void swap(__RSTD__ deque<_Ty, _Alloc>& _Left, __RSTD__ deque<_Ty, _Alloc>& _Right)
{	// swap _Left and _Right deques
	_Left.swap(_Right);
}
_STD_END

#pragma pop_macro("new")
#pragma warning(pop)
#pragma pack(pop)
#endif /* RC_INVOKED */