#pragma once
/*
@author zhp
@date 2017/2/27 6:37
@purpose for queue release
*/
#ifndef RC_INVOKED
#include <algorithm>
#include "RDeque.h"
#include "RVector.h"

#pragma pack(push,_CRT_PACKING)
#pragma warning(push,3)
#pragma push_macro("new")
#undef new
__RSTD_BEGIN_
// TEMPLATE CLASS queue
template<class _Ty,
class _Container = __RSTD__ deque<_Ty> >
class queue
{	// FIFO queue implemented with a container
public:
	typedef queue<_Ty, _Container> _Myt;
	typedef _Container container_type;
	typedef typename _Container::value_type value_type;
	typedef typename _Container::size_type size_type;
	typedef typename _Container::reference reference;
	typedef typename _Container::const_reference const_reference;

	queue()
		: c()
	{	// construct with empty container
	}

	queue(const _Myt& _Right)
		: c(_Right.c)
	{	// construct by copying _Right container
	}

	explicit queue(const _Container& _Cont)
		: c(_Cont)
	{	// construct by copying specified container
	}

	_Myt& operator=(const _Myt& _Right)
	{	// assign by copying _Right
		c = _Right.c;
		return (*this);
	}


	template<class _Alloc,
	class = typename _STD enable_if<_STD uses_allocator<_Container, _Alloc>::value,
		void>::type>
		explicit queue(const _Alloc& _Al)
		: c(_Al)
	{	// construct with empty container, allocator
	}

	template<class _Alloc,
	class = typename _STD enable_if<_STD uses_allocator<_Container, _Alloc>::value,
		void>::type>
		queue(const _Container& _Cont, const _Alloc& _Al)
		: c(_Cont, _Al)
	{	// construct by copying specified container, allocator
	}

	template<class _Alloc,
	class = typename _STD enable_if<_STD uses_allocator<_Container, _Alloc>::value,
		void>::type>
		queue(const _Myt& _Right, const _Alloc& _Al)
		: c(_Right.c, _Al)
	{	// construct by copying _Right container, allocator
	}

	queue(_Myt&& _Right)
		_NOEXCEPT_OP(_STD is_nothrow_move_constructible<_Container>::value)
		: c(_STD move(_Right.c))
	{	// construct by moving _Right
	}

	explicit queue(_Container&& _Cont)
		: c(_STD move(_Cont))
	{	// construct by moving specified container
	}

	template<class _Alloc,
	class = typename _STD enable_if<_STD uses_allocator<_Container, _Alloc>::value,
		void>::type>
		queue(_Container&& _Cont, const _Alloc& _Al)
		: c(_STD move(_Cont), _Al)
	{	// construct by moving specified container, allocator
	}

	template<class _Alloc,
	class = typename _STD enable_if<_STD uses_allocator<_Container, _Alloc>::value,
		void>::type>
		queue(_Myt&& _Right, const _Alloc& _Al)
		: c(_STD move(_Right.c), _Al)
	{	// construct by moving _Right container, allocator
	}

	_Myt& operator=(_Myt&& _Right)
		_NOEXCEPT_OP(_STD is_nothrow_move_assignable<_Container>::value)
	{	// assign by moving _Right
		c = _STD move(_Right.c);
		return (*this);
	}

	void push(value_type&& _Val)
	{	// insert element at beginning
		c.push_back(_STD move(_Val));
	}

	template<class... _Valty>
	void emplace(_Valty&&... _Val)
	{	// insert element at beginning
		c.emplace_back(_STD forward<_Valty>(_Val)...);
	}


	bool empty() const
	{	// test if queue is empty
		return (c.empty());
	}

	size_type size() const
	{	// return length of queue
		return (c.size());
	}

	reference front()
	{	// return first element of mutable queue
		return (c.front());
	}

	const_reference front() const
	{	// return first element of nonmutable queue
		return (c.front());
	}

	reference back()
	{	// return last element of mutable queue
		return (c.back());
	}

	const_reference back() const
	{	// return last element of nonmutable queue
		return (c.back());
	}

	void push(const value_type& _Val)
	{	// insert element at beginning
		c.push_back(_Val);
	}

	void pop()
	{	// erase element at end
		c.pop_front();
	}

	const _Container& _Get_container() const
	{	// get reference to container
		return (c);
	}

	void swap(_Myt& _Right)
		_NOEXCEPT_OP(_NOEXCEPT_OP(_Swap_adl(c, _Right.c)))
	{	// exchange contents with _Right
		_Swap_adl(c, _Right.c);
	}

protected:
	_Container c;	// the underlying container
};

template<class _Ty,
class _Container> inline
	bool operator==(const queue<_Ty, _Container>& _Left,
	const queue<_Ty, _Container>& _Right)
{	// test for queue equality
	return (_Left._Get_container() == _Right._Get_container());
}

template<class _Ty,
class _Container> inline
	bool operator!=(const queue<_Ty, _Container>& _Left,
	const queue<_Ty, _Container>& _Right)
{	// test for queue inequality
	return (!(_Left == _Right));
}

template<class _Ty,
class _Container> inline
	bool operator<(const queue<_Ty, _Container>& _Left,
	const queue<_Ty, _Container>& _Right)
{	// test if _Left < _Right for queues
	return (_Left._Get_container() < _Right._Get_container());
}

template<class _Ty,
class _Container> inline
	bool operator>(const queue<_Ty, _Container>& _Left,
	const queue<_Ty, _Container>& _Right)
{	// test if _Left > _Right for queues
	return (_Right < _Left);
}

template<class _Ty,
class _Container> inline
	bool operator<=(const queue<_Ty, _Container>& _Left,
	const queue<_Ty, _Container>& _Right)
{	// test if _Left <= _Right for queues
	return (!(_Right < _Left));
}

template<class _Ty,
class _Container> inline
	bool operator>=(const queue<_Ty, _Container>& _Left,
	const queue<_Ty, _Container>& _Right)
{	// test if _Left >= _Right for queues
	return (!(_Left < _Right));
}

// TEMPLATE CLASS priority_queue
template<class _Ty,
class _Container = __RSTD__ vector<_Ty>,
class _Pr = _STD less<typename _Container::value_type> >
class priority_queue
{	// priority queue implemented with a _Container
public:
	typedef priority_queue<_Ty, _Container, _Pr> _Myt;
	typedef _Container container_type;
	typedef typename _Container::value_type value_type;
	typedef typename _Container::size_type size_type;
	typedef typename _Container::reference reference;
	typedef typename _Container::const_reference const_reference;

	priority_queue()
		: c(), comp()
	{	// construct with empty container, default comparator
	}

	priority_queue(const _Myt& _Right)
		: c(_Right.c), comp(_Right.comp)
	{	// construct by copying _Right
	}

	explicit priority_queue(const _Pr& _Pred)
		: c(), comp(_Pred)
	{	// construct with empty container, specified comparator
	}

	priority_queue(const _Pr& _Pred, const _Container& _Cont)
		: c(_Cont), comp(_Pred)
	{	// construct by copying specified container, comparator
		make_heap(c.begin(), c.end(), comp);
	}

	template<class _InIt>
	priority_queue(_InIt _First, _InIt _Last)
		: c(_First, _Last), comp()
	{	// construct by copying [_First, _Last), default comparator
		make_heap(c.begin(), c.end(), comp);
	}

	template<class _InIt>
	priority_queue(_InIt _First, _InIt _Last, const _Pr& _Pred)
		: c(_First, _Last), comp(_Pred)
	{	// construct by copying [_First, _Last), specified comparator
		make_heap(c.begin(), c.end(), comp);
	}

	template<class _InIt>
	priority_queue(_InIt _First, _InIt _Last, const _Pr& _Pred,
		const _Container& _Cont)
		: c(_Cont), comp(_Pred)
	{	// construct by copying [_First, _Last), container, and comparator
		c.insert(c.end(), _First, _Last);
		make_heap(c.begin(), c.end(), comp);
	}

	_Myt& operator=(const _Myt& _Right)
	{	// assign by copying _Right
		c = _Right.c;
		comp = _Right.comp;
		return (*this);
	}


	template<class _Alloc,
	class = typename _STD enable_if<_STD uses_allocator<_Container, _Alloc>::value,
		void>::type>
		explicit priority_queue(const _Alloc& _Al)
		: c(_Al)
	{	// construct with empty container, allocator
	}

	template<class _Alloc,
	class = typename _STD enable_if<_STD uses_allocator<_Container, _Alloc>::value,
		void>::type>
		priority_queue(const _Pr& _Pred, const _Alloc& _Al)
		: c(_Al), comp(_Pred)
	{	// construct with empty container, comparator, allocator
	}

	template<class _Alloc,
	class = typename _STD enable_if<_STD uses_allocator<_Container, _Alloc>::value,
		void>::type>
		priority_queue(const _Pr& _Pred, const _Container& _Cont,
		const _Alloc& _Al)
		: c(_Cont, _Al), comp(_Pred)
	{	// construct by copying specified container, comparator, allocator
		make_heap(c.begin(), c.end(), comp);
	}

	template<class _Alloc,
	class = typename _STD enable_if<_STD uses_allocator<_Container, _Alloc>::value,
		void>::type>
		priority_queue(const _Myt& _Right, const _Alloc& _Al)
		: c(_Right.c, _Al), comp(_Right.comp)
	{	// construct by copying _Right, allocator
	}

	priority_queue(_Myt&& _Right)
		_NOEXCEPT_OP(_STD is_nothrow_move_constructible<_Container>::value
		&& _STD is_nothrow_move_constructible<_Pr>::value)
		: c(_STD move(_Right.c)), comp(_STD move(_Right.comp))
	{	// construct by moving _Right
	}

	priority_queue(const _Pr& _Pred, _Container&& _Cont)
		: c(_STD move(_Cont)), comp(_Pred)
	{	// construct by moving specified container, comparator
		make_heap(c.begin(), c.end(), comp);
	}

	template<class _InIt>
	priority_queue(_InIt _First, _InIt _Last, const _Pr& _Pred,
		_Container&& _Cont)
		: c(_STD move(_Cont)), comp(_Pred)
	{	// construct by copying [_First, _Last), moving container
		c.insert(c.end(), _First, _Last);
		make_heap(c.begin(), c.end(), comp);
	}

	template<class _Alloc,
	class = typename _STD enable_if<_STD uses_allocator<_Container, _Alloc>::value,
		void>::type>
		priority_queue(const _Pr& _Pred, _Container&& _Cont,
		const _Alloc& _Al)
		: c(_STD move(_Cont), _Al), comp(_Pred)
	{	// construct by moving specified container, comparator, allocator
		make_heap(c.begin(), c.end(), comp);
	}

	template<class _Alloc,
	class = typename _STD enable_if<_STD uses_allocator<_Container, _Alloc>::value,
		void>::type>
		priority_queue(_Myt&& _Right, const _Alloc& _Al)
		: c(_STD move(_Right.c), _Al), comp(_STD move(_Right.comp))
	{	// construct by moving _Right, allocator
	}

	_Myt& operator=(_Myt&& _Right)
		_NOEXCEPT_OP(_STD is_nothrow_move_assignable<_Container>::value
		&& _STD is_nothrow_move_assignable<_Pr>::value)
	{	// assign by moving _Right
		c = _STD move(_Right.c);
		comp = _STD move(_Right.comp);
		return (*this);
	}

	void push(value_type&& _Val)
	{	// insert element at beginning
		c.push_back(_STD move(_Val));
		push_heap(c.begin(), c.end(), comp);
	}

	template<class... _Valty>
	void emplace(_Valty&&... _Val)
	{	// insert element at beginning
		c.emplace_back(_STD forward<_Valty>(_Val)...);
		push_heap(c.begin(), c.end(), comp);
	}


	bool empty() const
	{	// test if queue is empty
		return (c.empty());
	}

	size_type size() const
	{	// return length of queue
		return (c.size());
	}

	const_reference top() const
	{	// return highest-priority element
		return (c.front());
	}

	reference top()
	{	// return mutable highest-priority element (retained)
		return (c.front());
	}

	void push(const value_type& _Val)
	{	// insert value in priority order
		c.push_back(_Val);
		push_heap(c.begin(), c.end(), comp);
	}

	void pop()
	{	// erase highest-priority element
		pop_heap(c.begin(), c.end(), comp);
		c.pop_back();
	}

	void swap(_Myt& _Right)
		_NOEXCEPT_OP(_NOEXCEPT_OP(_Swap_adl(c, _Right.c))
		&& _NOEXCEPT_OP(_Swap_adl(comp, _Right.comp)))
	{	// exchange contents with _Right
		_Swap_adl(c, _Right.c);
		_Swap_adl(comp, _Right.comp);
	}

protected:
	_Container c;	// the underlying container
	_Pr comp;	// the comparator functor
};

_STD_END

_STD_BEGIN

template<class _Ty,
class _Container,
class _Alloc>
struct _STD uses_allocator<__RSTD__ queue<_Ty, _Container>, _Alloc>
	: _STD uses_allocator<_Container, _Alloc>
{	// true_type if container allocator enabled
};

template<class _Ty,
class _Container,
class _Pr,
class _Alloc>
struct _STD uses_allocator<__RSTD__ priority_queue<_Ty, _Container, _Pr>, _Alloc>
	: _STD uses_allocator<_Container, _Alloc>
{	// true_type if container allocator enabled
};

// priority_queue TEMPLATE FUNCTIONS
template<class _Ty,
class _Container,
class _Pr> inline
	void swap(__RSTD__ priority_queue<_Ty, _Container, _Pr>& _Left,
	__RSTD__ priority_queue<_Ty, _Container, _Pr>& _Right)
	_NOEXCEPT_OP(_NOEXCEPT_OP(_Left.swap(_Right)))
{	// swap _Left and _Right queues
	_Left.swap(_Right);
}

// queue TEMPLATE FUNCTIONS
template<class _Ty,
class _Container> inline
	void swap(__RSTD__ queue<_Ty, _Container>& _Left,
	__RSTD__ queue<_Ty, _Container>& _Right)
	_NOEXCEPT_OP(_NOEXCEPT_OP(_Left.swap(_Right)))
{	// swap _Left and _Right queues
	_Left.swap(_Right);
}
_STD_END

#pragma pop_macro("new")
#pragma warning(pop)
#pragma pack(pop)
#endif /* RC_INVOKED */
