#pragma once
/*
@author zhp
@date 2017/2/27 7:22
@purpose for xtree release
*/
#ifndef RC_INVOKED
#include "RXutility.h"
#include <xmemory>
#include <stdexcept>

#pragma pack(push,_CRT_PACKING)
#pragma warning(push,3)
#pragma push_macro("new")
#undef new

#pragma warning(disable: 4127)
__RSTD_BEGIN_
// TEMPLATE CLASS _Tree_unchecked_const_iterator
template<class _Mytree,
class _Base = _Iterator_base0>
class _Tree_unchecked_const_iterator
	: public _STD _Iterator012<_STD bidirectional_iterator_tag,
	typename _Mytree::value_type,
	typename _Mytree::difference_type,
	typename _Mytree::const_pointer,
	typename _Mytree::const_reference,
	_Base>
{	// unchecked iterator for nonmutable tree
public:
	typedef _Tree_unchecked_const_iterator<_Mytree, _Base> _Myiter;
	typedef _STD bidirectional_iterator_tag iterator_category;

	typedef typename _Mytree::_Nodeptr _Nodeptr;
	typedef typename _Mytree::value_type value_type;
	typedef typename _Mytree::difference_type difference_type;
	typedef typename _Mytree::const_pointer pointer;
	typedef typename _Mytree::const_reference reference;

	_Tree_unchecked_const_iterator()
		: _Ptr(0)
	{	// construct with null node pointer
	}

	_Tree_unchecked_const_iterator(_Nodeptr _Pnode, const _Mytree *_Plist)
		: _Ptr(_Pnode)
	{	// construct with node pointer _Pnode
		this->_Adopt(_Plist);
	}

	reference operator*() const
	{	// return designated value
		return (_Mytree::_Myval(_Ptr));
	}

	pointer operator->() const
	{	// return pointer to class object
		return (_STD pointer_traits<pointer>::pointer_to(**this));
	}

	_Myiter& operator++()
	{	// preincrement
		if (_Mytree::_Isnil(_Ptr))
			;	// end() shouldn't be incremented, don't move
		else if (!_Mytree::_Isnil(_Mytree::_Right(_Ptr)))
			_Ptr = _Mytree::_Min(
			_Mytree::_Right(_Ptr));	// ==> smallest of right subtree
		else
		{	// climb looking for right subtree
			_Nodeptr _Pnode;
			while (!_Mytree::_Isnil(_Pnode = _Mytree::_Parent(_Ptr))
				&& _Ptr == _Mytree::_Right(_Pnode))
				_Ptr = _Pnode;	// ==> parent while right subtree
			_Ptr = _Pnode;	// ==> parent (head if end())
		}
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
		if (_Mytree::_Isnil(_Ptr))
			_Ptr = _Mytree::_Right(_Ptr);	// end() ==> rightmost
		else if (!_Mytree::_Isnil(_Mytree::_Left(_Ptr)))
			_Ptr = _Mytree::_Max(
			_Mytree::_Left(_Ptr));	// ==> largest of left subtree
		else
		{	// climb looking for left subtree
			_Nodeptr _Pnode;
			while (!_Mytree::_Isnil(_Pnode = _Mytree::_Parent(_Ptr))
				&& _Ptr == _Mytree::_Left(_Pnode))
				_Ptr = _Pnode;	// ==> parent while left subtree
			if (_Mytree::_Isnil(_Ptr))
				;	// begin() shouldn't be decremented, don't move
			else
				_Ptr = _Pnode;	// ==> parent if not head
		}
		return (*this);
	}

	_Myiter operator--(int)
	{	// postdecrement
		_Myiter _Tmp = *this;
		--*this;
		return (_Tmp);
	}

	bool operator==(const _Myiter& _Right) const
	{	// test for iterator equality
		return (_Ptr == _Right._Ptr);
	}

	bool operator!=(const _Myiter& _Right) const
	{	// test for iterator inequality
		return (!(*this == _Right));
	}

	_Nodeptr _Mynode() const
	{	// return node pointer
		return (_Ptr);
	}

	_Nodeptr _Ptr;	// pointer to node
};

// TEMPLATE CLASS _Tree_unchecked_iterator
template<class _Mytree>
class _Tree_unchecked_iterator
	: public _Tree_unchecked_const_iterator<_Mytree>
{	// unchecked iterator for mutable tree
public:
	typedef _Tree_unchecked_iterator<_Mytree> _Myiter;
	typedef _Tree_unchecked_const_iterator<_Mytree> _Mybase;
	typedef _STD bidirectional_iterator_tag iterator_category;

	typedef typename _Mytree::_Nodeptr _Nodeptr;
	typedef typename _Mytree::value_type value_type;
	typedef typename _Mytree::difference_type difference_type;
	typedef typename _Mytree::pointer pointer;
	typedef typename _Mytree::reference reference;

	_Tree_unchecked_iterator()
	{	// construct with null node
	}

	_Tree_unchecked_iterator(_Nodeptr _Pnode, const _Mytree *_Plist)
		: _Mybase(_Pnode, _Plist)
	{	// construct with node pointer _Pnode
	}

	reference operator*() const
	{	// return designated value
		return ((reference)**(_Mybase *)this);
	}

	pointer operator->() const
	{	// return pointer to class object
		return (_STD pointer_traits<pointer>::pointer_to(**this));
	}

	_Myiter& operator++()
	{	// preincrement
		++(*(_Mybase *)this);
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
		--(*(_Mybase *)this);
		return (*this);
	}

	_Myiter operator--(int)
	{	// postdecrement
		_Myiter _Tmp = *this;
		--*this;
		return (_Tmp);
	}
};

// TEMPLATE CLASS _Tree_const_iterator
template<class _Mytree>
class _Tree_const_iterator
	: public _Tree_unchecked_const_iterator<_Mytree, _Iterator_base>
{	// iterator for nonmutable tree
public:
	typedef _Tree_const_iterator<_Mytree> _Myiter;
	typedef _Tree_unchecked_const_iterator<_Mytree, _Iterator_base> _Mybase;
	typedef _STD bidirectional_iterator_tag iterator_category;

	typedef typename _Mytree::_Nodeptr _Nodeptr;
	typedef typename _Mytree::value_type value_type;
	typedef typename _Mytree::difference_type difference_type;
	typedef typename _Mytree::const_pointer pointer;
	typedef typename _Mytree::const_reference reference;

	_Tree_const_iterator()
		: _Mybase()
	{	// construct with null node pointer
	}

	_Tree_const_iterator(_Nodeptr _Pnode, const _Mytree *_Plist)
		: _Mybase(_Pnode, _Plist)
	{	// construct with node pointer _Pnode
	}

	typedef _Tree_unchecked_const_iterator<_Mytree> _Unchecked_type;

	_Myiter& _Rechecked(_Unchecked_type _Right)
	{	// reset from unchecked iterator
		this->_Ptr = _Right._Ptr;
		return (*this);
	}

	_Unchecked_type _Unchecked() const
	{	// make an unchecked iterator
		return (_Unchecked_type(this->_Ptr, (_Mytree *)this->_Getcont()));
	}

	reference operator*() const
	{	// return designated value
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (this->_Getcont() == 0
			|| this->_Ptr == 0
			|| this->_Ptr == ((_Mytree *)this->_Getcont())->_Myhead)
		{	// report error
			_DEBUG_ERROR("map/set iterator not dereferencable");
			_SCL_SECURE_OUT_OF_RANGE;
		}

#elif __RSTD_ITERATOR_DEBUG_LEVEL__ == 1
		_SCL_SECURE_VALIDATE(this->_Getcont() != 0 && this->_Ptr != 0);
		_SCL_SECURE_VALIDATE_RANGE(this->_Ptr !=
			((_Mytree *)this->_Getcont())->_Myhead);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ */

		return (_Mytree::_Myval(this->_Ptr));
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
			|| _Mytree::_Isnil(this->_Ptr))
		{	// report error
			_DEBUG_ERROR("map/set iterator not incrementable");
			_SCL_SECURE_OUT_OF_RANGE;
		}

#elif __RSTD_ITERATOR_DEBUG_LEVEL__ == 1
		_SCL_SECURE_VALIDATE(this->_Getcont() != 0 && this->_Ptr != 0);
		_SCL_SECURE_VALIDATE_RANGE(!_Mytree::_Isnil(this->_Ptr));
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ */

		++(*(_Mybase *)this);
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
			|| this->_Ptr == 0)
		{	// report error
			_DEBUG_ERROR("map/set iterator not decrementable");
			_SCL_SECURE_OUT_OF_RANGE;
		}

		_Nodeptr _Ptrsav = this->_Ptr;
		--(*(_Mybase *)this);
		if (_Ptrsav == this->_Ptr)
		{	// report error
			_DEBUG_ERROR("map/set iterator not decrementable");
			_SCL_SECURE_OUT_OF_RANGE;
		}

#elif __RSTD_ITERATOR_DEBUG_LEVEL__ == 1
		_SCL_SECURE_VALIDATE(this->_Getcont() != 0 && this->_Ptr != 0);

		_Nodeptr _Ptrsav = this->_Ptr;
		--(*(_Mybase *)this);
		_SCL_SECURE_VALIDATE(_Ptrsav != this->_Ptr);

#else /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 0 */
		--(*(_Mybase *)this);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ */

		return (*this);
	}

	_Myiter operator--(int)
	{	// postdecrement
		_Myiter _Tmp = *this;
		--*this;
		return (_Tmp);
	}

	bool operator==(const _Myiter& _Right) const
	{	// test for iterator equality
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (this->_Getcont() == 0
			|| this->_Getcont() != _Right._Getcont())
		{	// report error
			_DEBUG_ERROR("map/set iterators incompatible");
			_SCL_SECURE_INVALID_ARGUMENT;
		}

#elif __RSTD_ITERATOR_DEBUG_LEVEL__ == 1
		_SCL_SECURE_VALIDATE(this->_Getcont() != 0
			&& this->_Getcont() == _Right._Getcont());
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ */

		return (this->_Ptr == _Right._Ptr);
	}

	bool operator!=(const _Myiter& _Right) const
	{	// test for iterator inequality
		return (!(*this == _Right));
	}
};

template<class _Mytree> inline
typename _Tree_const_iterator<_Mytree>::_Unchecked_type
_Unchecked(_Tree_const_iterator<_Mytree> _Iter)
{	// convert to unchecked
	return (_Iter._Unchecked());
}

template<class _Mytree> inline
_Tree_const_iterator<_Mytree>&
_Rechecked(_Tree_const_iterator<_Mytree>& _Iter,
typename _Tree_const_iterator<_Mytree>
::_Unchecked_type _Right)
{	// convert to checked
	return (_Iter._Rechecked(_Right));
}

// TEMPLATE CLASS _Tree_iterator
template<class _Mytree>
class _Tree_iterator
	: public _Tree_const_iterator<_Mytree>
{	// iterator for mutable tree
public:
	typedef _Tree_iterator<_Mytree> _Myiter;
	typedef _Tree_const_iterator<_Mytree> _Mybase;
	typedef _STD bidirectional_iterator_tag iterator_category;

	typedef typename _Mytree::_Nodeptr _Nodeptr;
	typedef typename _Mytree::value_type value_type;
	typedef typename _Mytree::difference_type difference_type;

	typedef typename _Mytree::pointer pointer;
	typedef typename _Mytree::reference reference;

	_Tree_iterator()
	{	// construct with null node
	}

	_Tree_iterator(_Nodeptr _Pnode, const _Mytree *_Plist)
		: _Mybase(_Pnode, _Plist)
	{	// construct with node pointer _Pnode
	}

	typedef _Tree_unchecked_iterator<_Mytree> _Unchecked_type;

	_Myiter& _Rechecked(_Unchecked_type _Right)
	{	// reset from unchecked iterator
		this->_Ptr = _Right._Ptr;
		return (*this);
	}

	_Unchecked_type _Unchecked() const
	{	// make an unchecked iterator
		return (_Unchecked_type(this->_Ptr, (_Mytree *)this->_Getcont()));
	}

	reference operator*() const
	{	// return designated value
		return ((reference)**(_Mybase *)this);
	}

	pointer operator->() const
	{	// return pointer to class object
		return (_STD pointer_traits<pointer>::pointer_to(**this));
	}

	_Myiter& operator++()
	{	// preincrement
		++(*(_Mybase *)this);
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
		--(*(_Mybase *)this);
		return (*this);
	}

	_Myiter operator--(int)
	{	// postdecrement
		_Myiter _Tmp = *this;
		--*this;
		return (_Tmp);
	}
};

template<class _Mytree> inline
typename _Tree_iterator<_Mytree>::_Unchecked_type
_Unchecked(_Tree_iterator<_Mytree> _Iter)
{	// convert to unchecked
	return (_Iter._Unchecked());
}

template<class _Mytree> inline
_Tree_iterator<_Mytree>&
_Rechecked(_Tree_iterator<_Mytree>& _Iter,
typename _Tree_iterator<_Mytree>
::_Unchecked_type _Right)
{	// convert to checked
	return (_Iter._Rechecked(_Right));
}

// tree TYPE WRAPPERS
template<class _Value_type,
class _Size_type,
class _Difference_type,
class _Pointer,
class _Const_pointer,
class _Reference,
class _Const_reference,
class _Nodeptr_type>
struct _Tree_iter_types
{	// wraps types needed by iterators
	typedef _Value_type value_type;
	typedef _Size_type size_type;
	typedef _Difference_type difference_type;
	typedef _Pointer pointer;
	typedef _Const_pointer const_pointer;
	typedef _Reference reference;
	typedef _Const_reference const_reference;
	typedef _Nodeptr_type _Nodeptr;
};

template<class _Value_type,
class _Voidptr>
struct _Tree_node
{	// tree node
	_Voidptr _Left;	// left subtree, or smallest element if head
	_Voidptr _Parent;	// parent, or root of tree if head
	_Voidptr _Right;	// right subtree, or largest element if head
	char _Color;	// _Red or _Black, _Black if head
	char _Isnil;	// true only if head (also nil) node
	_Value_type _Myval;	// the stored value, unused if head

private:
	_Tree_node& operator=(const _Tree_node&);
};

template<class _Value_type>
struct _Tree_node<_Value_type, void *>
{	// tree node
	typedef _Tree_node<_Value_type, void *> *_Nodeptr;
	_Nodeptr _Left;	// left subtree, or smallest element if head
	_Nodeptr _Parent;	// parent, or root of tree if head
	_Nodeptr _Right;	// right subtree, or largest element if head
	char _Color;	// _Red or _Black, _Black if head
	char _Isnil;	// true only if head (also nil) node
	_Value_type _Myval;	// the stored value, unused if head

private:
	_Tree_node& operator=(const _Tree_node&);
};

template<class _Ty>
struct _Tree_simple_types
	: public _STD _Simple_types<_Ty>
{	// wraps types needed by iterators
	typedef _Tree_node<_Ty, void *> _Node;
	typedef _Node *_Nodeptr;
};

template<class _Ty,
class _Alloc0>
struct _Tree_base_types
{	// types needed for a container base
	typedef _Alloc0 _Alloc;
	typedef _Tree_base_types<_Ty, _Alloc> _Myt;

	typedef _STD _Wrap_alloc<_Alloc> _Alty0;
	typedef typename _Alty0::template rebind<_Ty>::other _Alty;


	typedef typename _STD _Get_voidptr<_Alty, typename _Alty::pointer>::type
		_Voidptr;
	typedef _Tree_node<typename _Alty::value_type,
		_Voidptr> _Node;

	typedef typename _Alty::template rebind<_Node>::other _Alnod_type;
	typedef typename _Alnod_type::pointer _Nodeptr;
	typedef _Nodeptr& _Nodepref;

	typedef typename _STD _If<_STD _Is_simple_alloc<_Alty>::value,
		_Tree_simple_types<typename _Alty::value_type>,
		_Tree_iter_types<typename _Alty::value_type,
		typename _Alty::size_type,
		typename _Alty::difference_type,
		typename _Alty::pointer,
		typename _Alty::const_pointer,
		typename _Alty::reference,
		typename _Alty::const_reference,
		_Nodeptr> >::type
		_Val_types;
};

// TEMPLATE CLASS _Tree_val
template<class _Val_types>
class _Tree_val
	: public _Container_base
{	// base class for tree to hold data
public:
	typedef _Tree_val<_Val_types> _Myt;

	typedef typename _Val_types::_Nodeptr _Nodeptr;
	typedef _Nodeptr& _Nodepref;

	typedef typename _Val_types::value_type value_type;
	typedef typename _Val_types::size_type size_type;
	typedef typename _Val_types::difference_type difference_type;
	typedef typename _Val_types::pointer pointer;
	typedef typename _Val_types::const_pointer const_pointer;
	typedef typename _Val_types::reference reference;
	typedef typename _Val_types::const_reference const_reference;

	typedef _Tree_const_iterator<_Myt> const_iterator;
	typedef _Tree_iterator<_Myt> iterator;

	_Tree_val()
	{	// initialize data
		this->_Myhead = 0;
		this->_Mysize = 0;
	}

	enum _Redbl
	{	// colors for link to parent
		_Red, _Black
	};

	static char& _Color(_Nodeptr _Pnode)
	{	// return reference to color in node
		return ((char&)_Pnode->_Color);
	}

	static char& _Isnil(_Nodeptr _Pnode)
	{	// return reference to nil flag in node
		return ((char&)_Pnode->_Isnil);
	}

	static _Nodepref _Left(_Nodeptr _Pnode)
	{	// return reference to left pointer in node
		return ((_Nodepref)_Pnode->_Left);
	}

	static _Nodepref _Parent(_Nodeptr _Pnode)
	{	// return reference to parent pointer in node
		return ((_Nodepref)_Pnode->_Parent);
	}

	static _Nodepref _Right(_Nodeptr _Pnode)
	{	// return reference to right pointer in node
		return ((_Nodepref)_Pnode->_Right);
	}

	static reference _Myval(_Nodeptr _Pnode)
	{	// return reference to value in node
		return ((reference)_Pnode->_Myval);
	}

	static _Nodeptr _Max(_Nodeptr _Pnode)
	{	// return rightmost node in subtree at _Pnode
		while (!_Isnil(_Right(_Pnode)))
			_Pnode = _Right(_Pnode);
		return (_Pnode);
	}

	static _Nodeptr _Min(_Nodeptr _Pnode)
	{	// return leftmost node in subtree at _Pnode
		while (!_Isnil(_Left(_Pnode)))
			_Pnode = _Left(_Pnode);
		return (_Pnode);
	}

	_Nodeptr _Myhead;	// pointer to head node
	size_type _Mysize;	// number of elements
};

// TEMPLATE CLASS _Tree_alloc
template<bool _Al_has_storage,
class _Alloc_types>
class _Tree_alloc
	: public _Tree_val<typename _Alloc_types::_Val_types>
{	// base class for tree to hold allocator with storage
public:
	typename _Alloc_types::_Alnod_type _Alnod;	// allocator object

	typedef _Tree_alloc<_Al_has_storage, _Alloc_types> _Myt;
	typedef typename _Alloc_types::_Alloc _Alloc;
	typedef typename _Alloc_types::_Alnod_type _Alty;
	typedef typename _Alloc_types::_Node _Node;
	typedef typename _Alloc_types::_Nodeptr _Nodeptr;

#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 0
	_Tree_alloc(const _Alloc& _Al = _Alloc())
		: _Alnod(_Al)
	{	// construct head node, allocator from _Al
		this->_Myhead = _Buyheadnode();
	}

	~_Tree_alloc() _NOEXCEPT
	{	// destroy head node
		_Freeheadnode(this->_Myhead);
	}

		void _Change_alloc(const _Alty& _Al)
	{	// replace old allocator
		this->_Alnod = _Al;
	}

	void _Swap_alloc(_Myt& _Right)
	{	// swap allocators
		_STD _Swap_adl(this->_Alnod, _Right._Alnod);
	}

#else /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 0 */
	_Tree_alloc(const _Alloc& _Al = _Alloc())
		: _Alnod(_Al)
	{	// construct allocators from _Al
		this->_Myhead = _Buyheadnode();
		_TRY_BEGIN
			_Alloc_proxy();
		_CATCH_ALL
			_Freeheadnode(this->_Myhead);
		_RERAISE;
		_CATCH_END
	}

	~_Tree_alloc() _NOEXCEPT
	{	// destroy proxy
		_Freeheadnode(this->_Myhead);
		_Free_proxy();
	}

		void _Change_alloc(const _Alty& _Al)
	{	// replace old allocator
		_Free_proxy();
		this->_Alnod = _Al;
		_Alloc_proxy();
	}

	void _Swap_alloc(_Myt& _Right)
	{	// swap allocators
		_STD _Swap_adl(this->_Alnod, _Right._Alnod);
		_STD _Swap_adl(this->_Myproxy, _Right._Myproxy);
	}

	void _Alloc_proxy()
	{	// construct proxy from _Alnod
		typename _Alty::template rebind<_Container_proxy>::other
			_Alproxy(this->_Alnod);
		this->_Myproxy = _Alproxy.allocate(1);
		_Alproxy.construct(this->_Myproxy, _Container_proxy());
		this->_Myproxy->_Mycont = this;
	}

	void _Free_proxy()
	{	// destroy proxy
		typename _Alty::template rebind<_Container_proxy>::other
			_Alproxy(this->_Alnod);
		this->_Orphan_all();
		_Alproxy.destroy(this->_Myproxy);
		_Alproxy.deallocate(this->_Myproxy, 1);
		this->_Myproxy = 0;
	}
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 0 */

	_Nodeptr _Buyheadnode()
	{	// get head node using current allocator
		_Nodeptr _Pnode = this->_Alnod.allocate(1);

		_TRY_BEGIN
			this->_Alnod.construct(
			_STD addressof(this->_Left(_Pnode)), _Pnode);
		this->_Alnod.construct(
			_STD addressof(this->_Parent(_Pnode)), _Pnode);
		this->_Alnod.construct(
			_STD addressof(this->_Right(_Pnode)), _Pnode);
		_CATCH_ALL
			this->_Alnod.deallocate(_Pnode, 1);
		_RERAISE;
		_CATCH_END

			this->_Color(_Pnode) = this->_Black;
		this->_Isnil(_Pnode) = true;
		return (_Pnode);
	}

	void _Freeheadnode(_Nodeptr _Pnode)
	{	// free head node using current allocator
		this->_Alnod.destroy(
			_STD addressof(this->_Left(_Pnode)));
		this->_Alnod.destroy(
			_STD addressof(this->_Parent(_Pnode)));
		this->_Alnod.destroy(
			_STD addressof(this->_Right(_Pnode)));
		this->_Alnod.deallocate(_Pnode, 1);
	}

	_Alty& _Getal()
	{	// get reference to allocator
		return (this->_Alnod);
	}

	const _Alty& _Getal() const
	{	// get reference to allocator
		return (this->_Alnod);
	}
};

// TEMPLATE CLASS _Tree_alloc
template<class _Alloc_types>
class _Tree_alloc<false, _Alloc_types>
	: public _Tree_val<typename _Alloc_types::_Val_types>
{	// base class for tree to hold allocator with no storage
public:
	typedef _Tree_alloc<false, _Alloc_types> _Myt;
	typedef _Tree_val<typename _Alloc_types::_Val_types> _Mybase;
	typedef typename _Alloc_types::_Alloc _Alloc;
	typedef typename _Alloc_types::_Alnod_type _Alty;
	typedef typename _Alloc_types::_Node _Node;
	typedef typename _Alloc_types::_Nodeptr _Nodeptr;

#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 0
	_Tree_alloc(const _Alloc& = _Alloc())
	{	// construct head node, allocator from _Al
		this->_Myhead = _Buyheadnode();
	}

	~_Tree_alloc() _NOEXCEPT
	{	// destroy head node
		_Freeheadnode(this->_Myhead);
	}

		void _Change_alloc(const _Alty&)
	{	// replace old allocator
	}

	void _Swap_alloc(_Myt&)
	{	// swap allocators
	}

#else /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 0 */
	_Tree_alloc(const _Alloc& = _Alloc())
	{	// construct allocators from _Al
		this->_Myhead = _Buyheadnode();
		_TRY_BEGIN
			_Alloc_proxy();
		_CATCH_ALL
			_Freeheadnode(this->_Myhead);
		_RERAISE;
		_CATCH_END
	}

	~_Tree_alloc() _NOEXCEPT
	{	// destroy proxy
		_Freeheadnode(this->_Myhead);
		_Free_proxy();
	}

		void _Change_alloc(const _Alty&)
	{	// replace old allocator
	}

	void _Swap_alloc(_Myt&)
	{	// swap allocators
	}

	void _Alloc_proxy()
	{	// construct proxy from _Alnod
		typename _Alty::template rebind<_Container_proxy>::other
			_Alproxy(_Getal());
		this->_Myproxy = _Alproxy.allocate(1);
		_Alproxy.construct(this->_Myproxy, _Container_proxy());
		this->_Myproxy->_Mycont = this;
	}

	void _Free_proxy()
	{	// destroy proxy
		typename _Alty::template rebind<_Container_proxy>::other
			_Alproxy(_Getal());
		this->_Orphan_all();
		_Alproxy.destroy(this->_Myproxy);
		_Alproxy.deallocate(this->_Myproxy, 1);
		this->_Myproxy = 0;
	}
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 0 */

	_Nodeptr _Buyheadnode()
	{	// get head node using current allocator
		_Nodeptr _Pnode = this->_Getal().allocate(1);

		_TRY_BEGIN
			this->_Getal().construct(
			_STD addressof(this->_Left(_Pnode)), _Pnode);
		this->_Getal().construct(
			_STD addressof(this->_Parent(_Pnode)), _Pnode);
		this->_Getal().construct(
			_STD addressof(this->_Right(_Pnode)), _Pnode);
		_CATCH_ALL
			this->_Getal().deallocate(_Pnode, 1);
		_RERAISE;
		_CATCH_END

			this->_Color(_Pnode) = this->_Black;
		this->_Isnil(_Pnode) = true;
		return (_Pnode);
	}

	void _Freeheadnode(_Nodeptr _Pnode)
	{	// free head node using current allocator
		this->_Getal().destroy(
			_STD addressof(this->_Left(_Pnode)));
		this->_Getal().destroy(
			_STD addressof(this->_Parent(_Pnode)));
		this->_Getal().destroy(
			_STD addressof(this->_Right(_Pnode)));
		this->_Getal().deallocate(_Pnode, 1);
	}

	_Alty _Getal() const
	{	// get allocator
		return (_Alty());
	}
};

// TEMPLATE CLASS _Tree_buy
template<class _Ty,
class _Alloc>
class _Tree_buy
	: public _Tree_alloc<!_STD is_empty<_Alloc>::value,
	_Tree_base_types<_Ty, _Alloc> >
{	// base class for tree to hold buynode/freenode functions
public:
	typedef _Tree_alloc<!_STD is_empty<_Alloc>::value,
		_Tree_base_types<_Ty, _Alloc> > _Mybase;
	typedef typename _Mybase::_Alty _Alty;
	typedef typename _Mybase::_Nodeptr _Nodeptr;
	typedef typename _Mybase::value_type value_type;

	_Tree_buy(const _Alloc& _Al = _Alloc())
		: _Mybase(_Al)
	{	// construct from allocator
	}

	_Nodeptr _Buynode0()
	{	// allocate a non-value node
		_Nodeptr _Pnode = this->_Getal().allocate(1);

		_TRY_BEGIN
			this->_Getal().construct(
			_STD addressof(this->_Left(_Pnode)), this->_Myhead);
		this->_Getal().construct(
			_STD addressof(this->_Parent(_Pnode)), this->_Myhead);
		this->_Getal().construct(
			_STD addressof(this->_Right(_Pnode)), this->_Myhead);
		_CATCH_ALL
			this->_Getal().deallocate(_Pnode, 1);
		_RERAISE;
		_CATCH_END

			return (_Pnode);
	}

	void _Freenode0(_Nodeptr _Pnode)
	{	// free non-value node using current allocator
		this->_Getal().destroy(
			_STD addressof(this->_Left(_Pnode)));
		this->_Getal().destroy(
			_STD addressof(this->_Parent(_Pnode)));
		this->_Getal().destroy(
			_STD addressof(this->_Right(_Pnode)));
		this->_Getal().deallocate(_Pnode, 1);
	}

	template<class... _Valty>
	_Nodeptr _Buynode(_Valty&&... _Val)
	{	// allocate a node with defaults and set links and value
		_Nodeptr _Pnode = _Buynode0();

		this->_Color(_Pnode) = this->_Red;
		this->_Isnil(_Pnode) = false;

		_TRY_BEGIN
			this->_Getal().construct(
			_STD addressof(this->_Myval(_Pnode)),
			_STD forward<_Valty>(_Val)...);
		_CATCH_ALL
			_Freenode0(_Pnode);
		_RERAISE;
		_CATCH_END

			return (_Pnode);
	}

};

// TEMPLATE CLASS _Tree_comp
template<bool _Pr_has_storage,
class _Traits>
class _Tree_comp
	: public _Tree_buy<typename _Traits::value_type,
	typename _Traits::allocator_type>
{	// base class for _Tree to hold ordering predicate with storage
public:
	typedef _Tree_comp<_Pr_has_storage, _Traits> _Myt;
	typedef _Tree_buy<typename _Traits::value_type,
		typename _Traits::allocator_type> _Mybase;

	typedef typename _Traits::allocator_type allocator_type;
	typedef typename _Traits::key_compare key_compare;

	_Tree_comp(const key_compare& _Parg, const allocator_type& _Al)
		: _Mybase(_Al), comp(_Parg)
	{	// construct ordering predicate
	}

	key_compare& _Getcomp()
	{	// get reference to ordering predicate
		return (comp);
	}

	const key_compare& _Getcomp() const
	{	// get reference to ordering predicate
		return (comp);
	}

	void _Setcomp(const key_compare& _Right)
	{	// copy ordering predicate
		comp = _Right;
	}

	void _Swapcomp(key_compare& _Right)
	{	// swap ordering predicate
		_STD _Swap_adl(comp, _Right);
	}

	key_compare comp;
};

template<class _Traits>
class _Tree_comp<false, _Traits>
	: public _Tree_buy<typename _Traits::value_type,
	typename _Traits::allocator_type>
{	// base class for _Tree to hold ordering predicate with no storage
public:
	typedef _Tree_comp<false, _Traits> _Myt;
	typedef _Tree_buy<typename _Traits::value_type,
		typename _Traits::allocator_type> _Mybase;

	typedef typename _Traits::allocator_type allocator_type;
	typedef typename _Traits::key_compare key_compare;

	_Tree_comp(const key_compare&, const allocator_type& _Al)
		: _Mybase(_Al)
	{	// construct ordering predicate
	}

	key_compare _Getcomp() const
	{	// get ordering predicate
		return (key_compare());
	}

	void _Setcomp(const key_compare&)
	{	// copy ordering predicate
	}

	void _Swapcomp(const key_compare&)
	{	// swap ordering predicate
	}
};

// TEMPLATE CLASS _Tree
template<class _Traits>
class _Tree
	: public _Tree_comp<
	!_STD is_empty<typename _Traits::key_compare>::value, _Traits>
{	// ordered red-black tree for [multi_]{map set}
public:
	typedef _Tree<_Traits> _Myt;
	typedef _Tree_comp<
		!_STD is_empty<typename _Traits::key_compare>::value, _Traits> _Mybase;

	typedef typename _Traits::key_type key_type;
	typedef typename _Traits::value_compare value_compare;
	enum
	{	// get multi parameter
		_Multi = _Traits::_Multi
	};

	typedef typename _Mybase::_Node _Node;
	typedef typename _Mybase::_Nodeptr _Nodeptr;
	typedef typename _Mybase::_Alty _Alty;

	typedef typename _Mybase::key_compare key_compare;
	typedef typename _Mybase::allocator_type allocator_type;

	typedef typename _Mybase::value_type value_type;
	typedef typename _Mybase::size_type size_type;
	typedef typename _Mybase::difference_type difference_type;
	typedef typename _Mybase::pointer pointer;
	typedef typename _Mybase::const_pointer const_pointer;
	typedef typename _Mybase::reference reference;
	typedef typename _Mybase::const_reference const_reference;

	typedef typename _Mybase::const_iterator const_iterator;
	typedef typename _STD _If<_STD is_same<key_type, value_type>::value,
		typename _Mybase::const_iterator,
		typename _Mybase::iterator>::type iterator;

	typedef _STD reverse_iterator<iterator> reverse_iterator;
	typedef _STD reverse_iterator<const_iterator> const_reverse_iterator;

	typedef _STD pair<iterator, bool> _Pairib;
	typedef _STD pair<iterator, iterator> _Pairii;
	typedef _STD pair<const_iterator, const_iterator> _Paircc;

	_Tree(const key_compare& _Parg,
		const allocator_type& _Al)
		: _Mybase(_Parg, _Al)
	{	// construct empty tree
	}

	_Tree(const value_type *_First, const value_type *_Last,
		const key_compare& _Parg, const allocator_type& _Al)
		: _Mybase(_Parg, _Al)
	{	// construct tree from [_First, _Last) array
		_TRY_BEGIN
			insert(_First, _Last);
		_CATCH_ALL
			_Tidy();
		_RERAISE;
		_CATCH_END
	}

	_Tree(const _Myt& _Right, const allocator_type& _Al)
		: _Mybase(_Right.key_comp(), _Al)
	{	// construct tree by copying _Right, allocator
		_TRY_BEGIN
			_Copy(_Right, _STD false_type());
		_CATCH_ALL
			_Tidy();
		_RERAISE;
		_CATCH_END
	}

	_Tree(_Myt&& _Right)
		: _Mybase(_Right.key_comp(), _Right._Getal())
	{	// construct tree by moving _Right
		_Assign_rv(_STD forward<_Myt>(_Right), _STD true_type());
	}

	_Tree(_Myt&& _Right, const allocator_type& _Al)
		: _Mybase(_Right.key_comp(), _Al)
	{	// construct tree by moving _Right, allocator
		_Assign_rv(_STD forward<_Myt>(_Right));
	}

	_Myt& operator=(_Myt&& _Right)
	{	// assign by moving _Right
		if (this != &_Right)
		{	// different, move it
			clear();
			if (_Alty::propagate_on_container_move_assignment::value
				&& this->_Getal() != _Right._Getal())
				this->_Change_alloc(_Right._Getal());

			_Assign_rv(_STD forward<_Myt>(_Right));
		}
		return (*this);
	}

	void _Assign_rv(_Myt&& _Right, _STD true_type)
	{	// move from _Right, stealing its contents
		this->_Swap_all(_Right);
		this->_Swapcomp(_Right._Getcomp());
		_STD _Swap_adl(this->_Myhead, _Right._Myhead);
		_STD swap(this->_Mysize, _Right._Mysize);
	}

	void _Assign_rv(_Myt&& _Right, _STD false_type)
	{	// move from _Right, possibly moving its contents
		if (get_allocator() == _Right.get_allocator())
			_Assign_rv(_STD forward<_Myt>(_Right), _STD true_type());
		else
			_Copy(_Right, _STD true_type());
	}

	void _Assign_rv(_Myt&& _Right)
	{	// assign by moving _Right
		_Assign_rv(_STD forward<_Myt>(_Right),
			typename _Alty::propagate_on_container_move_assignment());
	}


	_Pairib insert(value_type&& _Val)
	{	// try to insert node with value _Val, favoring right side
		return (_Insert_nohint(false,
			_STD forward<value_type>(_Val), _STD _Nil_obj));
	}

	iterator insert(const_iterator _Where, value_type&& _Val)
	{	// try to insert node with value _Val using _Where as a hint
		return (_Insert_hint(_Where,
			_STD forward<value_type>(_Val), _STD _Nil_obj));
	}

	template<class _Valty>
	typename _STD enable_if<_STD is_convertible<_Valty, value_type>::value,
		_Pairib>::type
		insert(_Valty&& _Val)
	{	// try to insert node with value _Val, favoring right side
		_Nodeptr _Newnode = this->_Buynode(_STD forward<_Valty>(_Val));
		return (_Insert_nohint(false,
			this->_Myval(_Newnode), _Newnode));
	}

	template<class _Valty>
	typename _STD enable_if<_STD is_convertible<_Valty, value_type>::value,
		iterator>::type
		insert(const_iterator _Where, _Valty&& _Val)
	{	// try to insert node with value _Val using _Where as a hint
		_Nodeptr _Newnode = this->_Buynode(_STD forward<_Valty>(_Val));
		return (_Insert_hint(_Where,
			this->_Myval(_Newnode), _Newnode));
	}

	template<class... _Valty>
	_Pairib emplace(_Valty&&... _Val)
	{	// try to insert value_type(_Val...), favoring right side
		_Nodeptr _Newnode = this->_Buynode(_STD forward<_Valty>(_Val)...);
		return (_Insert_nohint(false,
			this->_Myval(_Newnode), _Newnode));
	}

	template<class... _Valty>
	iterator emplace_hint(const_iterator _Where, _Valty&&... _Val)
	{	// insert value_type(_Val...) at _Where
		_Nodeptr _Newnode = this->_Buynode(_STD forward<_Valty>(_Val)...);
		return (_Insert_hint(_Where,
			this->_Myval(_Newnode), _Newnode));
	}


	~_Tree() _NOEXCEPT
	{	// destroy tree
		_Tidy();
	}

		_Myt& operator=(const _Myt& _Right)
	{	// replace contents from _Right
		if (this != &_Right)
		{	// different, assign it
			clear();
			if (this->_Getal() != _Right._Getal()
				&& _Alty::propagate_on_container_copy_assignment::value)
				this->_Change_alloc(_Right._Getal());

			this->_Setcomp(_Right._Getcomp());
			_Copy(_Right, _STD false_type());
		}
		return (*this);
	}

	iterator begin() _NOEXCEPT
	{	// return iterator for beginning of mutable sequence
		return (iterator(_Lmost(), this));
	}

		const_iterator begin() const _NOEXCEPT
	{	// return iterator for beginning of nonmutable sequence
		return (const_iterator(_Lmost(), this));
	}

		iterator end() _NOEXCEPT
	{	// return iterator for end of mutable sequence
		return (iterator(this->_Myhead, this));
	}

		const_iterator end() const _NOEXCEPT
	{	// return iterator for end of nonmutable sequence
		return (const_iterator(this->_Myhead, this));
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

		size_type size() const _NOEXCEPT
	{	// return length of sequence
		return (this->_Mysize);
	}

		size_type max_size() const _NOEXCEPT
	{	// return maximum possible length of sequence
		return (this->_Getal().max_size());
	}

		bool empty() const _NOEXCEPT
	{	// return true only if sequence is empty
		return (size() == 0);
	}

		allocator_type get_allocator() const _NOEXCEPT
	{	// return allocator object for values
		return (this->_Getal());
	}

		key_compare key_comp() const
	{	// return object for comparing keys
		return (this->_Getcomp());
	}

	value_compare value_comp() const
	{	// return object for comparing values
		return (value_compare(key_comp()));
	}

	_Pairib insert(const value_type& _Val)
	{	// try to insert node with value _Val, favoring right side
		return (_Insert_nohint(false,
			_Val, _STD _Nil_obj));
	}

	iterator insert(const_iterator _Where,
		const value_type& _Val)
	{	// try to insert node with value _Val using _Where as a hint
		return (_Insert_hint(_Where,
			_Val, _STD _Nil_obj));
	}

	template<class _Iter>
	void insert(_Iter _First, _Iter _Last)
	{	// insert [_First, _Last) one at a time
		_DEBUG_RANGE(_First, _Last);
		for (; _First != _Last; ++_First)

			emplace_hint(end(), *_First);
	}

	void insert(_XSTD initializer_list<value_type> _Ilist)
	{	// insert initializer_list
		insert(_Ilist.begin(), _Ilist.end());
	}

	iterator erase(const_iterator _Where)
	{	// erase element at _Where
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		if (_Where._Getcont() != this || this->_Isnil(_Where._Mynode()))
			_DEBUG_ERROR("map/set erase iterator outside range");
		_Nodeptr _Erasednode = _Where._Mynode();	// node to erase
		++_Where;	// save successor iterator for return
		_Orphan_ptr(*this, _Erasednode);

#else /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */
		_Nodeptr _Erasednode = _Where._Mynode();	// node to erase
		++_Where;	// save successor iterator for return
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		_Nodeptr _Fixnode;	// the node to recolor as needed
		_Nodeptr _Fixnodeparent;	// parent of _Fixnode (which may be nil)
		_Nodeptr _Pnode = _Erasednode;

		if (this->_Isnil(this->_Left(_Pnode)))
			_Fixnode = this->_Right(_Pnode);	// stitch up right subtree
		else if (this->_Isnil(this->_Right(_Pnode)))
			_Fixnode = this->_Left(_Pnode);	// stitch up left subtree
		else
		{	// two subtrees, must lift successor node to replace erased
			_Pnode = _Where._Mynode();	// _Pnode is successor node
			_Fixnode = this->_Right(_Pnode);	// _Fixnode is only subtree
		}

		if (_Pnode == _Erasednode)
		{	// at most one subtree, relink it
			_Fixnodeparent = this->_Parent(_Erasednode);
			if (!this->_Isnil(_Fixnode))
				this->_Parent(_Fixnode) = _Fixnodeparent;	// link up

			if (_Root() == _Erasednode)
				_Root() = _Fixnode;	// link down from root
			else if (this->_Left(_Fixnodeparent) == _Erasednode)
				this->_Left(_Fixnodeparent) = _Fixnode;	// link down to left
			else
				this->_Right(_Fixnodeparent) =
				_Fixnode;	// link down to right

			if (_Lmost() == _Erasednode)
				_Lmost() = this->_Isnil(_Fixnode)
				? _Fixnodeparent	// smallest is parent of erased node
				: this->_Min(_Fixnode);	// smallest in relinked subtree

			if (_Rmost() == _Erasednode)
				_Rmost() = this->_Isnil(_Fixnode)
				? _Fixnodeparent	// largest is parent of erased node
				: this->_Max(_Fixnode);	// largest in relinked subtree
		}
		else
		{	// erased has two subtrees, _Pnode is successor to erased
			this->_Parent(this->_Left(_Erasednode)) =
				_Pnode;	// link left up
			this->_Left(_Pnode) =
				this->_Left(_Erasednode);	// link successor down

			if (_Pnode == this->_Right(_Erasednode))
				_Fixnodeparent = _Pnode;	// successor is next to erased
			else
			{	// successor further down, link in place of erased
				_Fixnodeparent =
					this->_Parent(_Pnode);	// parent is successor's
				if (!this->_Isnil(_Fixnode))
					this->_Parent(_Fixnode) = _Fixnodeparent;	// link fix up
				this->_Left(_Fixnodeparent) = _Fixnode;	// link fix down
				this->_Right(_Pnode) =
					this->_Right(_Erasednode);	// link next down
				this->_Parent(this->_Right(_Erasednode)) =
					_Pnode;	// right up
			}

			if (_Root() == _Erasednode)
				_Root() = _Pnode;	// link down from root
			else if (this->_Left(this->_Parent(_Erasednode)) == _Erasednode)
				this->_Left(this->_Parent(_Erasednode)) =
				_Pnode;	// link down to left
			else
				this->_Right(this->_Parent(_Erasednode)) =
				_Pnode;	// link down to right

			this->_Parent(_Pnode) =
				this->_Parent(_Erasednode);	// link successor up
			_STD swap(this->_Color(_Pnode),
				this->_Color(_Erasednode));	// recolor it
		}

		if (this->_Color(_Erasednode) == this->_Black)
		{	// erasing black link, must recolor/rebalance tree
			for (; _Fixnode != _Root()
				&& this->_Color(_Fixnode) == this->_Black;
				_Fixnodeparent = this->_Parent(_Fixnode))
				if (_Fixnode == this->_Left(_Fixnodeparent))
				{	// fixup left subtree
					_Pnode = this->_Right(_Fixnodeparent);
					if (this->_Color(_Pnode) == this->_Red)
					{	// rotate red up from right subtree
						this->_Color(_Pnode) = this->_Black;
						this->_Color(_Fixnodeparent) = this->_Red;
						_Lrotate(_Fixnodeparent);
						_Pnode = this->_Right(_Fixnodeparent);
					}

					if (this->_Isnil(_Pnode))
						_Fixnode = _Fixnodeparent;	// shouldn't happen
					else if (this->_Color(this->_Left(_Pnode)) == this->_Black
						&& this->_Color(this->_Right(_Pnode)) == this->_Black)
					{	// redden right subtree with black children
						this->_Color(_Pnode) = this->_Red;
						_Fixnode = _Fixnodeparent;
					}
					else
					{	// must rearrange right subtree
						if (this->_Color(this->_Right(_Pnode))
							== this->_Black)
						{	// rotate red up from left sub-subtree
							this->_Color(this->_Left(_Pnode)) = this->_Black;
							this->_Color(_Pnode) = this->_Red;
							_Rrotate(_Pnode);
							_Pnode = this->_Right(_Fixnodeparent);
						}

						this->_Color(_Pnode) = this->_Color(_Fixnodeparent);
						this->_Color(_Fixnodeparent) = this->_Black;
						this->_Color(this->_Right(_Pnode)) = this->_Black;
						_Lrotate(_Fixnodeparent);
						break;	// tree now recolored/rebalanced
					}
				}
				else
				{	// fixup right subtree
					_Pnode = this->_Left(_Fixnodeparent);
					if (this->_Color(_Pnode) == this->_Red)
					{	// rotate red up from left subtree
						this->_Color(_Pnode) = this->_Black;
						this->_Color(_Fixnodeparent) = this->_Red;
						_Rrotate(_Fixnodeparent);
						_Pnode = this->_Left(_Fixnodeparent);
					}

					if (this->_Isnil(_Pnode))
						_Fixnode = _Fixnodeparent;	// shouldn't happen
					else if (this->_Color(this->_Right(_Pnode)) ==
						this->_Black
						&& this->_Color(this->_Left(_Pnode)) == this->_Black)
					{	// redden left subtree with black children
						this->_Color(_Pnode) = this->_Red;
						_Fixnode = _Fixnodeparent;
					}
					else
					{	// must rearrange left subtree
						if (this->_Color(this->_Left(_Pnode)) == this->_Black)
						{	// rotate red up from right sub-subtree
							this->_Color(this->_Right(_Pnode)) = this->_Black;
							this->_Color(_Pnode) = this->_Red;
							_Lrotate(_Pnode);
							_Pnode = this->_Left(_Fixnodeparent);
						}

						this->_Color(_Pnode) = this->_Color(_Fixnodeparent);
						this->_Color(_Fixnodeparent) = this->_Black;
						this->_Color(this->_Left(_Pnode)) = this->_Black;
						_Rrotate(_Fixnodeparent);
						break;	// tree now recolored/rebalanced
					}
				}

			this->_Color(_Fixnode) = this->_Black;	// stopping node is black
		}

		this->_Getal().destroy(
			_STD addressof(this->_Myval(_Erasednode)));	// delete erased node

		this->_Getal().deallocate(_Erasednode, 1);

		if (0 < this->_Mysize)
			--this->_Mysize;

		return (iterator(_Where._Ptr, this));	// return successor iterator
	}

	iterator erase(const_iterator _First, const_iterator _Last)
	{	// erase [_First, _Last)
		if (_First == begin() && _Last == end())
		{	// erase all
			clear();
			return (begin());
		}
		else
		{	// partial erase, one at a time
			while (_First != _Last)
				erase(_First++);
			return (iterator(_First._Ptr, this));
		}
	}

	size_type erase(const key_type& _Keyval)
	{	// erase and count all that match _Keyval
		_Pairii _Where = equal_range(_Keyval);
		size_type _Num = 0;
		_Distance(_Where.first, _Where.second, _Num);
		erase(_Where.first, _Where.second);
		return (_Num);
	}

	void clear() _NOEXCEPT
	{	// erase all
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
		this->_Orphan_ptr(*this, 0);
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		_Erase(_Root());
		_Root() = this->_Myhead;
		_Lmost() = this->_Myhead;
		_Rmost() = this->_Myhead;
		this->_Mysize = 0;
	}

		iterator find(const key_type& _Keyval)
	{	// find an element in mutable sequence that matches _Keyval
		iterator _Where = lower_bound(_Keyval);
		return (_Where == end()
			|| _DEBUG_LT_PRED(this->_Getcomp(),
			_Keyval, this->_Key(_Where._Mynode()))
			? end() : _Where);
	}

	const_iterator find(const key_type& _Keyval) const
	{	// find an element in nonmutable sequence that matches _Keyval
		const_iterator _Where = lower_bound(_Keyval);
		return (_Where == end()
			|| _DEBUG_LT_PRED(this->_Getcomp(),
			_Keyval, this->_Key(_Where._Mynode()))
			? end() : _Where);
	}

	size_type count(const key_type& _Keyval) const
	{	// count all elements that match _Keyval
		_Paircc _Ans = equal_range(_Keyval);
		size_type _Num = 0;
		_Distance(_Ans.first, _Ans.second, _Num);
		return (_Num);
	}

	iterator lower_bound(const key_type& _Keyval)
	{	// find leftmost node not less than _Keyval in mutable tree
		return (iterator(_Lbound(_Keyval), this));
	}

	const_iterator lower_bound(const key_type& _Keyval) const
	{	// find leftmost node not less than _Keyval in nonmutable tree
		return (const_iterator(_Lbound(_Keyval), this));
	}

	iterator upper_bound(const key_type& _Keyval)
	{	// find leftmost node greater than _Keyval in mutable tree
		return (iterator(_Ubound(_Keyval), this));
	}

	const_iterator upper_bound(const key_type& _Keyval) const
	{	// find leftmost node greater than _Keyval in nonmutable tree
		return (const_iterator(_Ubound(_Keyval), this));
	}

	_Pairii equal_range(const key_type& _Keyval)
	{	// find range equivalent to _Keyval in mutable tree
		return (_Eqrange(_Keyval));
	}

	_Paircc equal_range(const key_type& _Keyval) const
	{	// find range equivalent to _Keyval in nonmutable tree
		return (_Eqrange(_Keyval));
	}

	void swap(_Myt& _Right)
	{	// exchange contents with _Right
		if (this == &_Right)
			;	// same object, do nothing
		else if (this->_Getal() == _Right._Getal())
		{	// same allocator, swap control information
			this->_Swap_all(_Right);
			this->_Swapcomp(_Right._Getcomp());
			_STD _Swap_adl(this->_Myhead, _Right._Myhead);
			_STD swap(this->_Mysize, _Right._Mysize);
		}

		else if (_Alty::propagate_on_container_swap::value)
		{	// swap allocators and control information
			this->_Swap_alloc(_Right);
			this->_Swapcomp(_Right._Getcomp());
			_STD _Swap_adl(this->_Myhead, _Right._Myhead);
			_STD swap(this->_Mysize, _Right._Mysize);
		}

		else
		{	// containers are incompatible
#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
			_DEBUG_ERROR("map/set containers incompatible for swap");

#else /* ITERATOR_DEBUG_LEVEL == 2 */
			_XSTD terminate();
#endif /* ITERATOR_DEBUG_LEVEL == 2 */
		}
	}

protected:
	template<class _Valty>
	_Nodeptr _Buynode_if_nil(_Nodeptr _Node, _Valty&&)
	{	// node exists, just return it
		return (_Node);
	}

	template<class _Valty>
	_Nodeptr _Buynode_if_nil(_STD _Nil, _Valty&& _Val)
	{	// node doesn't exist, make it
		return (this->_Buynode(_STD forward<_Valty>(_Val)));
	}

	void _Destroy_if_not_nil(_Nodeptr _Newnode)
	{	// node exists, destroy it
		this->_Getal().destroy(
			_STD addressof(this->_Myval(_Newnode)));

		this->_Getal().deallocate(_Newnode, 1);
	}

	void _Destroy_if_not_nil(_STD _Nil)
	{	// node doesn't exist, do nothing
	}

	template<class _Valty,
	class _Nodety>
		iterator _Insert_hint(const_iterator _Where,
		_Valty&& _Val, _Nodety _Newnode)
	{	// try to insert node using _Where as a hint
		const_iterator _Next;
		bool _Leftish = false;	// assume nearest point is end of sequence

		_TRY_BEGIN

#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
			if (_Where._Getcont() != this)
				_DEBUG_ERROR("map/set insert iterator outside range");
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

		if (size() == 0)
			return (_Insert_at(true, this->_Myhead,
			_STD forward<_Valty>(_Val), _Newnode));	// empty tree
		else if (this->_Multi)
		{	// insert even if duplicate
			if (_Where == begin())
			{	// insert at beginning if before first element
				if (!_DEBUG_LT_PRED(this->_Getcomp(),
					this->_Key(_Where._Mynode()), this->_Kfn(_Val)))
					return (_Insert_at(true, _Where._Mynode(),
					_STD forward<_Valty>(_Val), _Newnode));
				_Leftish = true;	// nearest point is beginning of sequence
			}
			else if (_Where == end())
			{	// insert at end if after last element
				if (!_DEBUG_LT_PRED(this->_Getcomp(),
					this->_Kfn(_Val), this->_Key(_Rmost())))
					return (_Insert_at(false, _Rmost(),
					_STD forward<_Valty>(_Val), _Newnode));
			}
			else if (!_DEBUG_LT_PRED(this->_Getcomp(),
				this->_Key(_Where._Mynode()), this->_Kfn(_Val))
				&& !_DEBUG_LT_PRED(this->_Getcomp(),
				this->_Kfn(_Val),
				this->_Key((--(_Next = _Where))._Mynode())))
			{	// insert before _Where
				if (this->_Isnil(this->_Right(_Next._Mynode())))
					return (_Insert_at(false, _Next._Mynode(),
					_STD forward<_Valty>(_Val), _Newnode));
				else
					return (_Insert_at(true, _Where._Mynode(),
					_STD forward<_Valty>(_Val), _Newnode));
			}
			else if (!_DEBUG_LT_PRED(this->_Getcomp(),
				this->_Kfn(_Val), this->_Key(_Where._Mynode()))
				&& (++(_Next = _Where) == end()
				|| !_DEBUG_LT_PRED(this->_Getcomp(),
				this->_Key(_Next._Mynode()), this->_Kfn(_Val))))
			{	// insert after _Where
				if (this->_Isnil(this->_Right(_Where._Mynode())))
					return (_Insert_at(false, _Where._Mynode(),
					_STD forward<_Valty>(_Val), _Newnode));
				else
					return (_Insert_at(true, _Next._Mynode(),
					_STD forward<_Valty>(_Val), _Newnode));
			}
			else
				_Leftish = true;	// nearest point is beginning of sequence
		}
		else
		{	// insert only if unique
			if (_Where == begin())
			{	// insert at beginning if before first element
				if (_DEBUG_LT_PRED(this->_Getcomp(),
					this->_Kfn(_Val), this->_Key(_Where._Mynode())))
					return (_Insert_at(true, _Where._Mynode(),
					_STD forward<_Valty>(_Val), _Newnode));
			}
			else if (_Where == end())
			{	// insert at end if after last element
				if (_DEBUG_LT_PRED(this->_Getcomp(),
					this->_Key(_Rmost()), this->_Kfn(_Val)))
					return (_Insert_at(false, _Rmost(),
					_STD forward<_Valty>(_Val), _Newnode));
			}
			else if (_DEBUG_LT_PRED(this->_Getcomp(),
				this->_Kfn(_Val), this->_Key(_Where._Mynode()))
				&& _DEBUG_LT_PRED(this->_Getcomp(),
				this->_Key((--(_Next = _Where))._Mynode()),
				this->_Kfn(_Val)))
			{	// insert before _Where
				if (this->_Isnil(this->_Right(_Next._Mynode())))
					return (_Insert_at(false, _Next._Mynode(),
					_STD forward<_Valty>(_Val), _Newnode));
				else
					return (_Insert_at(true, _Where._Mynode(),
					_STD forward<_Valty>(_Val), _Newnode));
			}
			else if (_DEBUG_LT_PRED(this->_Getcomp(),
				this->_Key(_Where._Mynode()), this->_Kfn(_Val))
				&& (++(_Next = _Where) == end()
				|| _DEBUG_LT_PRED(this->_Getcomp(),
				this->_Kfn(_Val), this->_Key(_Next._Mynode()))))
			{	// insert after _Where
				if (this->_Isnil(this->_Right(_Where._Mynode())))
					return (_Insert_at(false, _Where._Mynode(),
					_STD forward<_Valty>(_Val), _Newnode));
				else
					return (_Insert_at(true, _Next._Mynode(),
					_STD forward<_Valty>(_Val), _Newnode));
			}
		}
		_CATCH_ALL
			_Destroy_if_not_nil(_Newnode);
		_RERAISE;
		_CATCH_END

			return (_Insert_nohint(_Leftish,
			_STD forward<_Valty>(_Val), _Newnode).first);
	}

	template<class _Valty,
	class _Nodety>
		_Pairib _Insert_nohint(bool _Leftish,
		_Valty&& _Val, _Nodety _Newnode)
	{	// try to insert node, on left if _Leftish
		_TRY_BEGIN
			_Nodeptr _Trynode = _Root();
		_Nodeptr _Wherenode = this->_Myhead;
		bool _Addleft = true;	// add to left of head if tree empty

		while (!this->_Isnil(_Trynode))
		{	// look for leaf to insert before (_Addleft) or after
			_Wherenode = _Trynode;
			if (_Leftish)
				_Addleft = !_DEBUG_LT_PRED(this->_Getcomp(),
				this->_Key(_Trynode),
				this->_Kfn(_Val));	// favor left end
			else
				_Addleft = _DEBUG_LT_PRED(this->_Getcomp(),
				this->_Kfn(_Val),
				this->_Key(_Trynode));	// favor right end
			_Trynode = _Addleft ? this->_Left(_Trynode)
				: this->_Right(_Trynode);
		}

		if (this->_Multi)
			return (_Pairib(_Insert_at(_Addleft, _Wherenode,
			_STD forward<_Valty>(_Val), _Newnode), true));
		else
		{	// insert only if unique
			iterator _Where = iterator(_Wherenode, this);
			if (!_Addleft)
				;	// need to test if insert after is okay
			else if (_Where == begin())
				return (_Pairib(_Insert_at(true, _Wherenode,
				_STD forward<_Valty>(_Val), _Newnode), true));
			else
				--_Where;	// need to test if insert before is okay

			if (_DEBUG_LT_PRED(this->_Getcomp(),
				this->_Key(_Where._Mynode()),
				this->_Kfn(_Val)))
				return (_Pairib(_Insert_at(_Addleft, _Wherenode,
				_STD forward<_Valty>(_Val), _Newnode), true));
			else
			{	// duplicate, don't insert
				_Destroy_if_not_nil(_Newnode);
				return (_Pairib(_Where, false));
			}
		}
		_CATCH_ALL
			_Destroy_if_not_nil(_Newnode);
		_RERAISE;
		_CATCH_END
	}

	template<class _Valty,
	class _Nodety>
		iterator _Insert_at(bool _Addleft, _Nodeptr _Wherenode,
		_Valty&& _Val, _Nodety _Node)
	{	// add node with value next to _Wherenode, to left if _Addleft
		if (max_size() - 1 <= this->_Mysize)
		{	// tree would get too big, fail
			_Destroy_if_not_nil(_Node);
			_STD _Xlength_error("map/set<T> too long");
		}
		_Nodeptr _Newnode = _Buynode_if_nil(_Node,
			_STD forward<_Valty>(_Val));

		++this->_Mysize;
		_Newnode->_Parent = _Wherenode;

		if (_Wherenode == this->_Myhead)
		{	// first node in tree, just set head values
			_Root() = _Newnode;
			_Lmost() = _Newnode;
			_Rmost() = _Newnode;
		}
		else if (_Addleft)
		{	// add to left of _Wherenode
			this->_Left(_Wherenode) = _Newnode;
			if (_Wherenode == _Lmost())
				_Lmost() = _Newnode;
		}
		else
		{	// add to right of _Wherenode
			this->_Right(_Wherenode) = _Newnode;
			if (_Wherenode == _Rmost())
				_Rmost() = _Newnode;
		}

		for (_Nodeptr _Pnode = _Newnode;
			this->_Color(this->_Parent(_Pnode)) == this->_Red;)
			if (this->_Parent(_Pnode)
				== this->_Left(this->_Parent(this->_Parent(_Pnode))))
			{	// fixup red-red in left subtree
				_Wherenode =
					this->_Right(this->_Parent(this->_Parent(_Pnode)));
				if (this->_Color(_Wherenode) == this->_Red)
				{	// parent has two red children, blacken both
					this->_Color(this->_Parent(_Pnode)) = this->_Black;
					this->_Color(_Wherenode) = this->_Black;
					this->_Color(this->_Parent(this->_Parent(_Pnode)))
						= this->_Red;
					_Pnode = this->_Parent(this->_Parent(_Pnode));
				}
				else
				{	// parent has red and black children
					if (_Pnode == this->_Right(this->_Parent(_Pnode)))
					{	// rotate right child to left
						_Pnode = this->_Parent(_Pnode);
						_Lrotate(_Pnode);
					}
					this->_Color(this->_Parent(_Pnode)) =
						this->_Black;	// propagate red up
					this->_Color(this->_Parent(this->_Parent(_Pnode))) =
						this->_Red;
					_Rrotate(this->_Parent(this->_Parent(_Pnode)));
				}
			}
			else
			{	// fixup red-red in right subtree
				_Wherenode =
					this->_Left(this->_Parent(this->_Parent(_Pnode)));
				if (this->_Color(_Wherenode) == this->_Red)
				{	// parent has two red children, blacken both
					this->_Color(this->_Parent(_Pnode)) = this->_Black;
					this->_Color(_Wherenode) = this->_Black;
					this->_Color(this->_Parent(this->_Parent(_Pnode))) =
						this->_Red;
					_Pnode = this->_Parent(this->_Parent(_Pnode));
				}
				else
				{	// parent has red and black children
					if (_Pnode == this->_Left(this->_Parent(_Pnode)))
					{	// rotate left child to right
						_Pnode = this->_Parent(_Pnode);
						_Rrotate(_Pnode);
					}
					this->_Color(this->_Parent(_Pnode)) =
						this->_Black;	// propagate red up
					this->_Color(this->_Parent(this->_Parent(_Pnode))) =
						this->_Red;
					_Lrotate(this->_Parent(this->_Parent(_Pnode)));
				}
			}

		this->_Color(_Root()) = this->_Black;	// root is always black
		return (iterator(_Newnode, this));
	}

	template<class _Moveit>
	void _Copy(const _Myt& _Right,
		_Moveit _Movefl)
	{	// copy or move entire tree from _Right
		_Root() = _Copy_nodes(_Right._Root(), this->_Myhead, _Movefl);
		this->_Mysize = _Right.size();
		if (!this->_Isnil(_Root()))
		{	// nonempty tree, look for new smallest and largest
			_Lmost() = this->_Min(_Root());
			_Rmost() = this->_Max(_Root());
		}
		else
		{	// empty tree, just tidy head pointers
			_Lmost() = this->_Myhead;
			_Rmost() = this->_Myhead;
		}
	}

	template<class _Want_to_move,
	class _Can_move,
	class _Is_set,
	class _Dummy>
		_Nodeptr _Copy_or_move(_Nodeptr _Rootnode, _Want_to_move,
		_Can_move, _Is_set, _Dummy)
	{	// copy to new node -- nonmovable
		return (this->_Buynode(this->_Myval(_Rootnode)));
	}

	template<class _Dummy>
	_Nodeptr _Copy_or_move(_Nodeptr _Rootnode, _STD true_type,
		_STD true_type, _STD true_type, _Dummy)
	{	// move to new node -- movable, set
		return (this->_Buynode(
			_STD forward<value_type>(this->_Myval(_Rootnode))));
	}

	template<class _Dummy>
	_Nodeptr _Copy_or_move(_Nodeptr _Rootnode, _STD true_type,
		_STD true_type, _STD false_type, _Dummy)
	{	// move to new node -- movable, map
		return (this->_Buynode(
			_STD forward<key_type>(const_cast<key_type&>(
			this->_Myval(_Rootnode).first)),
			_STD forward<typename value_type::second_type>(this->_Myval(
			_Rootnode).second)));
	}

	template<class _Moveit>
	_Nodeptr _Copy_nodes(_Nodeptr _Rootnode, _Nodeptr _Wherenode,
		_Moveit _Movefl)
	{	// copy entire subtree, recursively
		_Nodeptr _Newroot = this->_Myhead;	// point at nil node

		if (!this->_Isnil(_Rootnode))
		{	// copy or move a node, then any subtrees
			_Nodeptr _Pnode = _Copy_or_move(_Rootnode, _Movefl,
				typename is_move_constructible<value_type>::type(),
				typename _STD is_same<key_type, value_type>::type(), 0);
			_Pnode->_Parent = _Wherenode;
			_Pnode->_Color = this->_Color(_Rootnode);
			if (this->_Isnil(_Newroot))
				_Newroot = _Pnode;	// memorize new root

			_TRY_BEGIN
				this->_Left(_Pnode) =
				_Copy_nodes(this->_Left(_Rootnode), _Pnode, _Movefl);
			this->_Right(_Pnode) =
				_Copy_nodes(this->_Right(_Rootnode), _Pnode, _Movefl);
			_CATCH_ALL
				_Erase(_Newroot);	// subtree copy failed, bail out
			_RERAISE;
			_CATCH_END
		}

		return (_Newroot);	// return newly constructed tree
	}

	_Paircc _Eqrange(const key_type& _Keyval) const
	{	// find leftmost node not less than _Keyval
		_Nodeptr _Pnode = _Root();
		_Nodeptr _Lonode = this->_Myhead;	// end() if search fails
		_Nodeptr _Hinode = this->_Myhead;	// end() if search fails

		while (!this->_Isnil(_Pnode))
			if (_DEBUG_LT_PRED(this->_Getcomp(), this->_Key(_Pnode), _Keyval))
				_Pnode = this->_Right(_Pnode);	// descend right subtree
			else
			{	// _Pnode not less than _Keyval, remember it
				if (this->_Isnil(_Hinode)
					&& _DEBUG_LT_PRED(this->_Getcomp(), _Keyval,
					this->_Key(_Pnode)))
					_Hinode = _Pnode;	// _Pnode greater, remember it
				_Lonode = _Pnode;
				_Pnode = this->_Left(_Pnode);	// descend left subtree
			}

		_Pnode = this->_Isnil(_Hinode) ? _Root()
			: this->_Left(_Hinode);	// continue scan for upper bound
		while (!this->_Isnil(_Pnode))
			if (_DEBUG_LT_PRED(this->_Getcomp(), _Keyval, this->_Key(_Pnode)))
			{	// _Pnode greater than _Keyval, remember it
				_Hinode = _Pnode;
				_Pnode = this->_Left(_Pnode);	// descend left subtree
			}
			else
				_Pnode = this->_Right(_Pnode);	// descend right subtree

		const_iterator _First = const_iterator(_Lonode, this);
		const_iterator _Last = const_iterator(_Hinode, this);
		return (_Paircc(_First, _Last));
	}

	_Pairii _Eqrange(const key_type& _Keyval)
	{	// find leftmost node not less than _Keyval
		_Nodeptr _Pnode = _Root();
		_Nodeptr _Lonode = this->_Myhead;	// end() if search fails
		_Nodeptr _Hinode = this->_Myhead;	// end() if search fails

		while (!this->_Isnil(_Pnode))
			if (_DEBUG_LT_PRED(this->_Getcomp(), this->_Key(_Pnode), _Keyval))
				_Pnode = this->_Right(_Pnode);	// descend right subtree
			else
			{	// _Pnode not less than _Keyval, remember it
				if (this->_Isnil(_Hinode)
					&& _DEBUG_LT_PRED(this->_Getcomp(), _Keyval,
					this->_Key(_Pnode)))
					_Hinode = _Pnode;	// _Pnode greater, remember it
				_Lonode = _Pnode;
				_Pnode = this->_Left(_Pnode);	// descend left subtree
			}

		_Pnode = this->_Isnil(_Hinode) ? _Root()
			: this->_Left(_Hinode);	// continue scan for upper bound
		while (!this->_Isnil(_Pnode))
			if (_DEBUG_LT_PRED(this->_Getcomp(), _Keyval, this->_Key(_Pnode)))
			{	// _Pnode greater than _Keyval, remember it
				_Hinode = _Pnode;
				_Pnode = this->_Left(_Pnode);	// descend left subtree
			}
			else
				_Pnode = this->_Right(_Pnode);	// descend right subtree

		iterator _First = iterator(_Lonode, this);
		iterator _Last = iterator(_Hinode, this);
		return (_Pairii(_First, _Last));
	}

	void _Erase(_Nodeptr _Rootnode)
	{	// free entire subtree, recursively
		for (_Nodeptr _Pnode = _Rootnode;
			!this->_Isnil(_Pnode); _Rootnode = _Pnode)
		{	// free subtrees, then node
			_Erase(this->_Right(_Pnode));
			_Pnode = this->_Left(_Pnode);
			this->_Getal().destroy(
				_STD addressof(this->_Myval(_Rootnode)));

			this->_Getal().deallocate(_Rootnode, 1);
		}
	}

	_Nodeptr _Lbound(const key_type& _Keyval) const
	{	// find leftmost node not less than _Keyval
		_Nodeptr _Pnode = _Root();
		_Nodeptr _Wherenode = this->_Myhead;	// end() if search fails

		while (!this->_Isnil(_Pnode))
			if (_DEBUG_LT_PRED(this->_Getcomp(), this->_Key(_Pnode), _Keyval))
				_Pnode = this->_Right(_Pnode);	// descend right subtree
			else
			{	// _Pnode not less than _Keyval, remember it
				_Wherenode = _Pnode;
				_Pnode = this->_Left(_Pnode);	// descend left subtree
			}

		return (_Wherenode);	// return best remembered candidate
	}

	_Nodeptr _Lbound(const key_type& _Keyval)
	{	// find leftmost node not less than _Keyval
		_Nodeptr _Pnode = _Root();
		_Nodeptr _Wherenode = this->_Myhead;	// end() if search fails

		while (!this->_Isnil(_Pnode))
			if (_DEBUG_LT_PRED(this->_Getcomp(), this->_Key(_Pnode), _Keyval))
				_Pnode = this->_Right(_Pnode);	// descend right subtree
			else
			{	// _Pnode not less than _Keyval, remember it
				_Wherenode = _Pnode;
				_Pnode = this->_Left(_Pnode);	// descend left subtree
			}

		return (_Wherenode);	// return best remembered candidate
	}

	_Nodeptr& _Lmost() const
	{	// return leftmost node in nonmutable tree
		return (this->_Left(this->_Myhead));
	}

	void _Lrotate(_Nodeptr _Wherenode)
	{	// promote right node to root of subtree
		_Nodeptr _Pnode = this->_Right(_Wherenode);
		this->_Right(_Wherenode) = this->_Left(_Pnode);

		if (!this->_Isnil(this->_Left(_Pnode)))
			this->_Parent(this->_Left(_Pnode)) = _Wherenode;
		this->_Parent(_Pnode) = this->_Parent(_Wherenode);

		if (_Wherenode == _Root())
			_Root() = _Pnode;
		else if (_Wherenode == this->_Left(this->_Parent(_Wherenode)))
			this->_Left(this->_Parent(_Wherenode)) = _Pnode;
		else
			this->_Right(this->_Parent(_Wherenode)) = _Pnode;

		this->_Left(_Pnode) = _Wherenode;
		this->_Parent(_Wherenode) = _Pnode;
	}

	_Nodeptr& _Rmost() const
	{	// return rightmost node in nonmutable tree
		return (this->_Right(this->_Myhead));
	}

	_Nodeptr& _Root() const
	{	// return root of nonmutable tree
		return (this->_Parent(this->_Myhead));
	}

	void _Rrotate(_Nodeptr _Wherenode)
	{	// promote left node to root of subtree
		_Nodeptr _Pnode = this->_Left(_Wherenode);
		this->_Left(_Wherenode) = this->_Right(_Pnode);

		if (!this->_Isnil(this->_Right(_Pnode)))
			this->_Parent(this->_Right(_Pnode)) = _Wherenode;
		this->_Parent(_Pnode) = this->_Parent(_Wherenode);

		if (_Wherenode == _Root())
			_Root() = _Pnode;
		else if (_Wherenode == this->_Right(this->_Parent(_Wherenode)))
			this->_Right(this->_Parent(_Wherenode)) = _Pnode;
		else
			this->_Left(this->_Parent(_Wherenode)) = _Pnode;

		this->_Right(_Pnode) = _Wherenode;
		this->_Parent(_Wherenode) = _Pnode;
	}

	_Nodeptr _Ubound(const key_type& _Keyval) const
	{	// find leftmost node greater than _Keyval
		_Nodeptr _Pnode = _Root();
		_Nodeptr _Wherenode = this->_Myhead;	// end() if search fails

		while (!this->_Isnil(_Pnode))
			if (_DEBUG_LT_PRED(this->_Getcomp(), _Keyval, this->_Key(_Pnode)))
			{	// _Pnode greater than _Keyval, remember it
				_Wherenode = _Pnode;
				_Pnode = this->_Left(_Pnode);	// descend left subtree
			}
			else
				_Pnode = this->_Right(_Pnode);	// descend right subtree

		return (_Wherenode);	// return best remembered candidate
	}

	_Nodeptr _Ubound(const key_type& _Keyval)
	{	// find leftmost node greater than _Keyval
		_Nodeptr _Pnode = _Root();
		_Nodeptr _Wherenode = this->_Myhead;	// end() if search fails

		while (!this->_Isnil(_Pnode))
			if (_DEBUG_LT_PRED(this->_Getcomp(), _Keyval, this->_Key(_Pnode)))
			{	// _Pnode greater than _Keyval, remember it
				_Wherenode = _Pnode;
				_Pnode = this->_Left(_Pnode);	// descend left subtree
			}
			else
				_Pnode = this->_Right(_Pnode);	// descend right subtree

		return (_Wherenode);	// return best remembered candidate
	}

#if __RSTD_ITERATOR_DEBUG_LEVEL__ == 2
	void _Orphan_ptr(_Myt& _Cont, _Nodeptr _Ptr) const
	{	// orphan iterators with specified node pointers
		_Lockit _Lock(_LOCK_DEBUG);
		const_iterator **_Pnext = (const_iterator **)_Cont._Getpfirst();
		if (_Pnext != 0)
			while (*_Pnext != 0)
				if ((*_Pnext)->_Ptr == this->_Myhead
					|| _Ptr != 0 && (*_Pnext)->_Ptr != _Ptr)
					_Pnext = (const_iterator **)(*_Pnext)->_Getpnext();
				else
				{	// orphan the iterator
					(*_Pnext)->_Clrcont();
					*_Pnext = *(const_iterator **)(*_Pnext)->_Getpnext();
				}
	}
#endif /* __RSTD_ITERATOR_DEBUG_LEVEL__ == 2 */

	void _Tidy()
	{	// free all storage
		erase(begin(), end());
	}

	const key_type& _Kfn(const value_type& _Val) const
	{	// get key from value
		return (_Traits::_Kfn(_Val));
	}

	const key_type& _Key(_Nodeptr _Pnode) const
	{	// return reference to key in node
		return ((const key_type&)this->_Kfn(this->_Myval(_Pnode)));
	}
};

// _Tree TEMPLATE OPERATORS
template<class _Traits> inline
bool operator==(const _Tree<_Traits>& _Left, const _Tree<_Traits>& _Right)
{	// test for _Tree equality
	return (_Left.size() == _Right.size()
		&& equal(_Left.begin(), _Left.end(), _Right.begin()));
}

template<class _Traits> inline
bool operator!=(const _Tree<_Traits>& _Left, const _Tree<_Traits>& _Right)
{	// test for _Tree inequality
	return (!(_Left == _Right));
}

template<class _Traits> inline
bool operator<(const _Tree<_Traits>& _Left, const _Tree<_Traits>& _Right)
{	// test if _Less < _Right for _Trees
	return (lexicographical_compare(_Left.begin(), _Left.end(),
		_Right.begin(), _Right.end()));
}

template<class _Traits> inline
bool operator>(const _Tree<_Traits>& _Left, const _Tree<_Traits>& _Right)
{	// test if _Less > _Right for _Trees
	return (_Right < _Left);
}

template<class _Traits> inline
bool operator<=(const _Tree<_Traits>& _Left, const _Tree<_Traits>& _Right)
{	// test if _Less <= _Right for _Trees
	return (!(_Right < _Left));
}

template<class _Traits> inline
bool operator>=(const _Tree<_Traits>& _Left, const _Tree<_Traits>& _Right)
{	// test if _Less >= _Right for _Trees
	return (!(_Left < _Right));
}
_STD_END

#pragma pop_macro("new")
#pragma warning(pop)
#pragma pack(pop)
#endif /* RC_INVOKED */
