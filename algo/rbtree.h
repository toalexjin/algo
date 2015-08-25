/**
 * Red-Black Tree.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#pragma once

#include <assert.h>
#include <functional>
#include <iterator>


namespace algo {


// Red-Black Tree internal implementation
namespace rbtree__ {

	// Tree node.
	template <class T>
	struct node_t {
		typedef node_t<T> self_type;
		typedef T value_type;

		node_t() : m_parent(0), m_left(0), m_right(0), m_value(value), m_black(false) {
		}

		self_type* m_parent;
		self_type* m_left;
		self_type* m_right;
		T m_value;
		bool m_black;
	};

	// Internal data container.
	template <class T>
	struct ctner_t {
		typedef ctner_t<T> self_type;
		typedef T value_type;

		ctner_t() : m_root(0), m_size(0) {
		}

		~ctner_t() {
			this->clear();
		}

		void clear() {
			// TO-DO

			this->m_size = 0;
		}

		self_type& swap(self_type& another) {
			if (this != &another) {
				auto tmp(*this);
				*this = another;
				another = tmp;
			}

			return *this;
		}

		node_t<T>* m_root;
		size_t m_size;
	};

	// Iterator implementation.
	template <class T, class Pointer, class Reference, class CtnerPointer, class NodePointer>
	class iterator_t : public std::iterator<
			std::bidirectional_iterator_tag,
			T, std::ptrdiff_t, Pointer, Reference> {
	private:
		typedef iterator_t<T, Pointer, Reference, CtnerPointer, NodePointer> self_type;

	public:
		iterator_t() : m_ctner(0), m_current(0) {
		}

		iterator_t(const self_type& it) {
			*this = it;
		}

		iterator_t(CtnerPointer ctner, NodePointer current)
			: m_ctner(ctner), m_current(current) {
		}

		Reference operator*() const {
			assert(m_ctner != 0);
			assert(m_current != 0);

			return m_current->m_value;
		}

		Pointer operator->() const {
			assert(m_ctner != 0);
			assert(m_current != 0);

			return &m_current->m_value;
		}

		self_type& operator++() {
			assert(m_ctner != 0);
			assert(m_current != 0);

			// TO-DO
			return *this;
		}

		self_type operator++(int) {
			const self_type old(*this);
			this->operator++();
			return old;
		}

		self_type& operator--() {
			assert(m_ctner != 0);

			// TO-DO
			return *this;
		}

		self_type operator--(int) {
			const self_type old(*this);
			this->operator--();
			return old;
		}

		self_type& operator=(const self_type& it) {
			if (this != &it) {
				this->m_ctner = it.m_ctner;
				this->m_current = it.m_current;
			}

			return *this;
		}

		bool operator==(const self_type& it) {
			if (this->m_ctner == it.m_ctner
				&& this->m_current == it.m_current) {
				return true;
			}

			return false;
		}

		bool operator!=(const self_type& it) {
			return !this->operator==(it);
		}

		CtnerPointer get_ctner_ptr__() const {
			return this->m_ctner;
		}

		NodePointer get_node_ptr__() const {
			return this->m_current;
		}

	private:
		CtnerPointer m_ctner;
		NodePointer m_current;
	};

	enum find_result_t {
		// There is no root node, the new value
		// could be added as root node.
		find_result_null_root,

		// The value was not found, could be 
		// added to the left leaf of parent node.
		find_result_left,

		// The value was not found, could be
		// added to the right leaf of parent node.
		find_result_right,

		// The value was found.
		find_result_yes
	};

	// Finding result.
	template <class T>
	struct find_t {
		find_t() : m_node_ptr(0), m_result(find_result_null_root) {}

		node_t<T>* m_node_ptr;
		find_result_t m_result;
	};

} // namespace rbtree__


/**
 * Red-Black Tree.
 */
template <class T, class Compare = std::less<T>>
class rbtree {
private:
	typedef rbtree<T, Compare> self_type;
	typedef rbtree__::node_t<T>* node_ptr_t;
	typedef const rbtree__::node_t<T>* const_node_ptr_t;

public:
	typedef Compare key_compare;
	typedef Compare value_compare;
	typedef T key_type;
	typedef T value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;

	typedef rbtree__::iterator_t<value_type, pointer, reference,
		rbtree__::ctner_t<value_type>*, node_ptr_t> iterator;
	typedef rbtree__::iterator_t<value_type, const_pointer, const_reference,
		const rbtree__::ctner_t<value_type>*, const_node_ptr_t> const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> reverse_const_iterator;

public:
	rbtree() {}

	explicit rbtree(const Compare& less) : m_less(less) {
	}

	virtual ~rbtree() {
	}

	size_t size() const {
		return this->m_ctner.m_size;
	}

	size_t max_size() const {
		return size_t(-1);
	}

	bool empty() const {
		return this->m_ctner.m_size == 0;
	}

	void clear() {
		this->m_ctner.clear();
	}

	key_compare key_comp() const {
		return this->m_less;
	}

	value_compare value_comp() const {
		this this->m_less;
	}

	iterator find(const T& value);
	const_iterator find(const T& value) const;

	template <class Iterator>
	void insert(Iterator first, Iterator last) {
		for (auto it = first; it != last; ++it) {
			this->insert(*it);
		}
	}
	std::pair<iterator, bool> insert(const T& value);

	void erase(iterator it);
	void erase(iterator first, iterator last);
	size_t erase(const T& value);

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	reverse_iterator rbegin();
	reverse_iterator rend();
	reverse_const_iterator rbegin() const;
	reverse_const_iterator rend() const;

	self_type& operator=(const self_type& another);
	self_type& swap(self_type& another);

private:
	rbtree__::find_t<T> find_i(const T& value) const;
	void erase_i(node_ptr_t node);

private:
	rbtree__::ctner_t<value_type> m_ctner;
	key_compare m_less;
};


template <class T, class Compare>
inline typename rbtree<T, Compare>::iterator rbtree<T, Compare>::find(const T& value) {
	auto found(this->find_i(value));

	return iterator(&this->m_ctner,
		found.m_result == rbtree__::find_result_yes ? found.m_node_ptr : 0);
}

template <class T, class Compare>
inline typename rbtree<T, Compare>::const_iterator rbtree<T, Compare>::find(const T& value) const {
	auto found(this->find_i(value));

	return const_iterator(&this->m_ctner,
		found.m_result == rbtree__::find_result_yes ? found.m_node_ptr : 0);
}

template <class T, class Compare>
inline std::pair<typename rbtree<T, Compare>::iterator, bool> rbtree<T, Compare>::insert(const T& value) {
	auto found(this->find_i(value));

	if (found.m_result == rbtree__::find_result_yes) {
		return std::pair<typename rbtree<T, Compare>::iterator, bool>(
			iterator(&this->m_ctner, found.m_node_ptr), false);
	}

	// TO-DO
	return std::pair<typename rbtree<T, Compare>::iterator, bool>(
			iterator(&this->m_ctner, 0), true);
}

template <class T, class Compare>
inline typename rbtree<T, Compare>::iterator rbtree<T, Compare>::erase(
	typename rbtree<T, Compare>::iterator it) {
	if (it.get_ctner_ptr__() == &this->m_ctner) {
		// Same container.
		assert(it != this->end());
		this->erase_i(it.get_node_ptr__());
	}
	else {
		// Different container.
		this->erase(*it);
	}
}

template <class T, class Compare>
inline typename rbtree<T, Compare>::iterator rbtree<T, Compare>::erase(
	typename rbtree<T, Compare>::iterator first,
	typename rbtree<T, Compare>::iterator last) {
	for (auto it = first; it != last;) {
		this->erase(it++);
	}
}

template <class T, class Compare>
inline size_t rbtree<T, Compare>::erase(const T& value) {
	const auto found(this->find_i(value));

	if (found.m_result != rbtree__::find_result_yes) {
		return 0;
	}

	this->erase_i(found.m_node_ptr);
	return 1;
}

template <class T, class Compare>
inline typename rbtree<T, Compare>::iterator rbtree<T, Compare>::begin() {
	if (this->m_ctner.m_root == 0) {
		return this->end();
	}

	auto ptr(this->m_ctner.m_root);
	while (ptr->m_left != 0) {
		ptr = ptr->m_left;
	}

	return iterator(&this->m_ctner, ptr);
}

template <class T, class Compare>
inline typename rbtree<T, Compare>::iterator rbtree<T, Compare>::end() {
	return iterator(&this->m_ctner, 0);
}

template <class T, class Compare>
inline typename rbtree<T, Compare>::const_iterator rbtree<T, Compare>::begin() const {
	if (this->m_ctner.m_root == 0) {
		return this->end();
	}

	auto ptr(this->m_ctner.m_root);
	while (ptr->m_left != 0) {
		ptr = ptr->m_left;
	}

	return const_iterator(&this->m_ctner, ptr);
}

template <class T, class Compare>
inline typename rbtree<T, Compare>::const_iterator rbtree<T, Compare>::end() const {
	return const_iterator(&this->m_ctner, 0);
}

template <class T, class Compare>
inline typename rbtree<T, Compare>::reverse_iterator rbtree<T, Compare>::rbegin() {
	return reverse_iterator(this->end());
}

template <class T, class Compare>
inline typename rbtree<T, Compare>::reverse_iterator rbtree<T, Compare>::rend() {
	return reverse_iterator(this->begin());
}

template <class T, class Compare>
inline typename rbtree<T, Compare>::reverse_const_iterator rbtree<T, Compare>::rbegin() const {
	return reverse_const_iterator(this->end());
}

template <class T, class Compare>
inline typename rbtree<T, Compare>::reverse_const_iterator rbtree<T, Compare>::rend() const {
	return reverse_const_iterator(this->begin());
}

template <class T, class Compare>
inline typename rbtree<T, Compare>::self_type& rbtree<T, Compare>::operator=(
	const typename rbtree<T, Compare>::self_type& another) {
	if (this != &another) {
		// Remove all old data.
		this->clear();

		// Copy key-compare & new data.
		this->m_less = another.m_less;
		this->insert(another.begin(), another.end());
	}

	return *this;
}

template <class T, class Compare>
inline typename rbtree<T, Compare>::self_type& rbtree<T, Compare>::swap(
	typename rbtree<T, Compare>::self_type& another) {
	if (this != &another) {
		// Swap data.
		this->m_ctner.swap(&another.m_ctner);
		
		// Swap key-compare.
		auto tmp(this->m_less);
		this->m_less = another.m_less;
		another.m_less = tmp;
	}

	return *this;
}

template <class T, class Compare>
inline rbtree__::find_t<T> rbtree<T, Compare>::find_i(const T& value) const {
	rbtree__::find_t<T> result;

	auto ptr = node_ptr_t(this->m_ctner.m_root);
	while (ptr != 0) {
		result.m_node_ptr = ptr;

		if (this->m_less(value, ptr->m_value)) {
			result.m_result = rbtree__::find_result_left;
			ptr = ptr->m_left;
		}
		else if (this->m_less(ptr->m_value, value)) {
			result.m_result = rbtree__::find_result_right;
			ptr = ptr->m_right;
		}
		else {
			result.m_result = rbtree__::find_result_yes;
			break;
		}
	}

	return result;
}

template <class T, class Compare>
inline void rbtree<T, Compare>::erase_i(typename rbtree<T, Compare>::node_ptr_t node) {
	// TO-DO.
}

} // namespace algo

