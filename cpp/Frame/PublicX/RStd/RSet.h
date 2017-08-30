#pragma once
/*
@author zhp
@date 2017/2/27 7:20
@purpose for set release
*/
#ifndef RC_INVOKED
#include "RXtree.h"
#include <set>

#pragma pack(push,_CRT_PACKING)
#pragma warning(push,3)
#pragma push_macro("new")
#undef new
__RSTD_BEGIN_
// TEMPLATE CLASS _Tset_traits
template<class _Kty,	// key/value type
class _Pr,	// comparator predicate type
class _Alloc,	// actual allocator type (should be value allocator)
	bool _Mfl>	// true if multiple equivalent keys are permitted
class _Tset_traits
{	// traits required to make _Tree behave like a set
public:
	typedef _Kty key_type;
	typedef _Kty value_type;
	typedef _Pr key_compare;
	typedef _Alloc allocator_type;

	enum
	{	// make multi parameter visible as an enumeration constant
		_Multi = _Mfl
	};

	typedef key_compare value_compare;

	static const _Kty& _Kfn(const value_type& _Val)
	{	// extract key from element value
		return (_Val);
	}
};

// TEMPLATE CLASS set
template<class _Kty,
class _Pr = _STD less<_Kty>,
class _Alloc = _STD allocator<_Kty> >
class set
	: public _Tree<_Tset_traits<_Kty, _Pr, _Alloc, false> >
{	// ordered red-black tree of key values, unique keys
public:
	typedef set<_Kty, _Pr, _Alloc> _Myt;
	typedef _Tree<_Tset_traits<_Kty, _Pr, _Alloc, false> > _Mybase;
	typedef _Kty key_type;
	typedef _Pr key_compare;
	typedef typename _Mybase::_Pairib _Pairib;
	typedef typename _Mybase::value_compare value_compare;
	typedef typename _Mybase::allocator_type allocator_type;
	typedef typename _Mybase::size_type size_type;
	typedef typename _Mybase::difference_type difference_type;
	typedef typename _Mybase::pointer pointer;
	typedef typename _Mybase::const_pointer const_pointer;
	typedef typename _Mybase::reference reference;
	typedef typename _Mybase::const_reference const_reference;
	typedef typename _Mybase::iterator iterator;
	typedef typename _Mybase::const_iterator const_iterator;
	typedef typename _Mybase::reverse_iterator reverse_iterator;
	typedef typename _Mybase::const_reverse_iterator
		const_reverse_iterator;
	typedef typename _Mybase::value_type value_type;

	set()
		: _Mybase(key_compare(), allocator_type())
	{	// construct empty set from defaults
	}

	explicit set(const allocator_type& _Al)
		: _Mybase(key_compare(), _Al)
	{	// construct empty set from defaults, allocator
	}

	set(const _Myt& _Right)

		: _Mybase(_Right,
		_Right._Getal().select_on_container_copy_construction())


	{	// construct set by copying _Right
	}

	set(const _Myt& _Right, const allocator_type& _Al)
		: _Mybase(_Right, _Al)
	{	// construct set by copying _Right, allocator
	}

	explicit set(const key_compare& _Pred)
		: _Mybase(_Pred, allocator_type())
	{	// construct empty set from comparator
	}

	set(const key_compare& _Pred, const allocator_type& _Al)
		: _Mybase(_Pred, _Al)
	{	// construct empty set from comparator and allocator
	}

	template<class _Iter>
	set(_Iter _First, _Iter _Last)
		: _Mybase(key_compare(), allocator_type())
	{	// construct set from [_First, _Last), defaults
		this->insert(_First, _Last);
	}

	template<class _Iter>
	set(_Iter _First, _Iter _Last,
		const key_compare& _Pred)
		: _Mybase(_Pred, allocator_type())
	{	// construct set from [_First, _Last), comparator
		this->insert(_First, _Last);
	}

	template<class _Iter>
	set(_Iter _First, _Iter _Last,
		const key_compare& _Pred, const allocator_type& _Al)
		: _Mybase(_Pred, _Al)
	{	// construct set from [_First, _Last), defaults, and allocator
		this->insert(_First, _Last);
	}

	_Myt& operator=(const _Myt& _Right)
	{	// assign by copying _Right
		_Mybase::operator=(_Right);
		return (*this);
	}

	set(_Myt&& _Right)
		: _Mybase(_STD move(_Right))
	{	// construct set by moving _Right
	}

	set(_Myt&& _Right, const allocator_type& _Al)
		: _Mybase(_STD move(_Right), _Al)
	{	// construct set by moving _Right, allocator
	}

	_Myt& operator=(_Myt&& _Right)
	{	// assign by moving _Right
		_Mybase::operator=(_STD move(_Right));
		return (*this);
	}

	_Pairib insert(value_type&& _Val)
	{	// insert a key value
		return (_Mybase::insert(_STD forward<value_type>(_Val)));
	}

	iterator insert(const_iterator _Where, value_type&& _Val)
	{	// insert a key value, with hint
		return (_Mybase::insert(_Where, _STD forward<value_type>(_Val)));
	}

	void swap(_Myt& _Right)
	{	// exchange contents with non-movable _Right
		_Mybase::swap(_Right);
	}

	set(_XSTD initializer_list<value_type> _Ilist)
		: _Mybase(key_compare(), allocator_type())
	{	// construct from initializer_list, defaults
		this->insert(_Ilist.begin(), _Ilist.end());
	}

	set(_XSTD initializer_list<value_type> _Ilist,
		const key_compare& _Pred)
		: _Mybase(_Pred, allocator_type())
	{	// construct from initializer_list, comparator
		this->insert(_Ilist.begin(), _Ilist.end());
	}

	set(_XSTD initializer_list<value_type> _Ilist,
		const key_compare& _Pred, const allocator_type& _Al)
		: _Mybase(_Pred, _Al)
	{	// construct from initializer_list, comparator, and allocator
		this->insert(_Ilist.begin(), _Ilist.end());
	}

	_Myt& operator=(_XSTD initializer_list<value_type> _Ilist)
	{	// assign initializer_list
		this->clear();
		this->insert(_Ilist.begin(), _Ilist.end());
		return (*this);
	}

	void insert(_XSTD initializer_list<value_type> _Ilist)
	{	// insert initializer_list
		this->insert(_Ilist.begin(), _Ilist.end());
	}

	_Pairib insert(const value_type& _Val)
	{	// insert a key value
		return (_Mybase::insert(_Val));
	}

	iterator insert(const_iterator _Where, const value_type& _Val)
	{	// insert a key value, with hint
		return (_Mybase::insert(_Where, _Val));
	}

	template<class _Iter>
	void insert(_Iter _First, _Iter _Last)
	{	// insert [_First, _Last)
		_DEBUG_RANGE(_First, _Last);
		for (; _First != _Last; ++_First)

			this->emplace(*_First);
	}
};

// TEMPLATE CLASS multiset
template<class _Kty,
class _Pr = _STD less<_Kty>,
class _Alloc = _STD allocator<_Kty> >
class multiset
	: public _Tree<_Tset_traits<_Kty, _Pr, _Alloc, true> >
{	// ordered red-black tree of key values, non-unique keys
public:
	typedef multiset<_Kty, _Pr, _Alloc> _Myt;
	typedef _Tree<_Tset_traits<_Kty, _Pr, _Alloc, true> > _Mybase;
	typedef _Kty key_type;
	typedef _Pr key_compare;
	typedef typename _Mybase::value_compare value_compare;
	typedef typename _Mybase::allocator_type allocator_type;
	typedef typename _Mybase::size_type size_type;
	typedef typename _Mybase::difference_type difference_type;
	typedef typename _Mybase::pointer pointer;
	typedef typename _Mybase::const_pointer const_pointer;
	typedef typename _Mybase::reference reference;
	typedef typename _Mybase::const_reference const_reference;
	typedef typename _Mybase::iterator iterator;
	typedef typename _Mybase::const_iterator const_iterator;
	typedef typename _Mybase::reverse_iterator reverse_iterator;
	typedef typename _Mybase::const_reverse_iterator
		const_reverse_iterator;
	typedef typename _Mybase::value_type value_type;

	multiset()
		: _Mybase(key_compare(), allocator_type())
	{	// construct empty set from defaults
	}

	explicit multiset(const allocator_type& _Al)
		: _Mybase(key_compare(), _Al)
	{	// construct empty set from defaults, allocator
	}

	multiset(const _Myt& _Right)

		: _Mybase(_Right,
		_Right._Getal().select_on_container_copy_construction())


	{	// construct set by copying _Right
	}

	multiset(const _Myt& _Right, const allocator_type& _Al)
		: _Mybase(_Right, _Al)
	{	// construct set by copying _Right, allocator
	}

	explicit multiset(const key_compare& _Pred)
		: _Mybase(_Pred, allocator_type())
	{	// construct empty set from comparator
	}

	multiset(const key_compare& _Pred, const allocator_type& _Al)
		: _Mybase(_Pred, _Al)
	{	// construct empty set from comparator and allocator
	}

	template<class _Iter>
	multiset(_Iter _First, _Iter _Last)
		: _Mybase(key_compare(), allocator_type())
	{	// construct set from [_First, _Last)
		this->insert(_First, _Last);
	}

	template<class _Iter>
	multiset(_Iter _First, _Iter _Last,
		const key_compare& _Pred)
		: _Mybase(_Pred, allocator_type())
	{	// construct set from [_First, _Last), comparator
		this->insert(_First, _Last);
	}

	template<class _Iter>
	multiset(_Iter _First, _Iter _Last,
		const key_compare& _Pred, const allocator_type& _Al)
		: _Mybase(_Pred, _Al)
	{	// construct set from [_First, _Last), comparator, and allocator
		this->insert(_First, _Last);
	}

	_Myt& operator=(const _Myt& _Right)
	{	// assign by copying _Right
		_Mybase::operator=(_Right);
		return (*this);
	}

	multiset(_Myt&& _Right)
		: _Mybase(_STD move(_Right))
	{	// construct set by moving _Right
	}

	multiset(_Myt&& _Right, const allocator_type& _Al)
		: _Mybase(_STD move(_Right), _Al)
	{	// construct set by moving _Right
	}

	_Myt& operator=(_Myt&& _Right)
	{	// assign by moving _Right
		_Mybase::operator=(_STD move(_Right));
		return (*this);
	}

	iterator insert(value_type&& _Val)
	{	// insert a key value
		return (_Mybase::insert(_STD forward<value_type>(_Val)).first);
	}

	iterator insert(const_iterator _Where, value_type&& _Val)
	{	// insert a key value, with hint
		return (_Mybase::insert(_Where, _STD forward<value_type>(_Val)));
	}

	template<class... _Valty>
	iterator emplace(_Valty&&... _Val)
	{	// try to insert value_type(_Val...), favoring right side
		return (_Mybase::emplace(_STD forward<_Valty>(_Val)...).first);
	}


	void swap(_Myt& _Right)
	{	// exchange contents with non-movable _Right
		_Mybase::swap(_Right);
	}

	multiset(_XSTD initializer_list<value_type> _Ilist)
		: _Mybase(key_compare(), allocator_type())
	{	// construct from initializer_list, defaults
		this->insert(_Ilist.begin(), _Ilist.end());
	}

	multiset(_XSTD initializer_list<value_type> _Ilist,
		const key_compare& _Pred)
		: _Mybase(_Pred, allocator_type())
	{	// construct from initializer_list, comparator
		this->insert(_Ilist.begin(), _Ilist.end());
	}

	multiset(_XSTD initializer_list<value_type> _Ilist,
		const key_compare& _Pred, const allocator_type& _Al)
		: _Mybase(_Pred, _Al)
	{	// construct from initializer_list, comparator, and allocator
		this->insert(_Ilist.begin(), _Ilist.end());
	}

	_Myt& operator=(_XSTD initializer_list<value_type> _Ilist)
	{	// assign initializer_list
		this->clear();
		this->insert(_Ilist.begin(), _Ilist.end());
		return (*this);
	}

	void insert(_XSTD initializer_list<value_type> _Ilist)
	{	// insert initializer_list
		this->insert(_Ilist.begin(), _Ilist.end());
	}

	iterator insert(const value_type& _Val)
	{	// insert a key value
		return (_Mybase::insert(_Val).first);
	}

	iterator insert(const_iterator _Where, const value_type& _Val)
	{	// insert a key value, with hint
		return (_Mybase::insert(_Where, _Val));
	}

	template<class _Iter>
	void insert(_Iter _First, _Iter _Last)
	{	// insert [_First, _Last)
		_DEBUG_RANGE(_First, _Last);
		for (; _First != _Last; ++_First)

			this->emplace(*_First);
	}
};

template<class _Kty, class _Ty, class _Alloc>
_STD set<_Kty, _Ty, _Alloc> to_std(const __RSTD__ set<_Kty, _Ty, _Alloc>& v){
	_STD set<_Kty, _Ty, _Alloc> res;
	for (auto& va : v)
	{
		res.insert(va);
	}
	return res;
}

template<class _Kty, class _Ty, class _Alloc>
__RSTD__ set<_Kty, _Ty, _Alloc> from_std(const _STD set<_Kty, _Ty, _Alloc>& v){
	__RSTD__ set<_Kty, _Ty, _Alloc> res;
	for (auto& va : v)
	{
		res.insert(va);
	}
	return res;
}

template<class _Kty, class _Ty, class _Alloc>
_STD multiset<_Kty, _Ty, _Alloc> to_std(const __RSTD__ multiset<_Kty, _Ty, _Alloc>& v){
	_STD multiset<_Kty, _Ty, _Alloc> res;
	for (auto& va : v)
	{
		res.insert(va);
	}
	return res;
}

template<class _Kty, class _Ty, class _Alloc>
__RSTD__ multiset<_Kty, _Ty, _Alloc> from_std(const _STD multiset<_Kty, _Ty, _Alloc>& v){
	__RSTD__ multiset<_Kty, _Ty, _Alloc> res;
	for (auto& va : v)
	{
		res.insert(va);
	}
	return res;
}

_STD_END

_STD_BEGIN
template<class _Kty,
class _Pr,
class _Alloc> inline
	void swap(__RSTD__ multiset<_Kty, _Pr, _Alloc>& _Left,
	__RSTD__ multiset<_Kty, _Pr, _Alloc>& _Right)
{	// swap _Left and _Right multisets
	_Left.swap(_Right);
}

template<class _Kty,
class _Pr,
class _Alloc> inline
	void swap(__RSTD__ set<_Kty, _Pr, _Alloc>& _Left,
	__RSTD__ set<_Kty, _Pr, _Alloc>& _Right)
{	// swap _Left and _Right sets
	_Left.swap(_Right);
}
_STD_END

#pragma pop_macro("new")
#pragma warning(pop)
#pragma pack(pop)
#endif /* RC_INVOKED */
