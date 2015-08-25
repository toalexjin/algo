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

	// Red-Black Tree node.
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


	template <class T>
	struct ctner_t {
		typedef ctner_t<T> self_type;
		typedef T value_type;

		ctner_t() : m_root(0), m_size(0) {
		}

		node_t<T>* m_root;
		size_t m_size;
	};


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

	private:
		CtnerPointer m_ctner;
		NodePointer m_current;
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

	enum found_result_t {
		// The value was found.
		found_result_yes,

		// The value was not found, should be added to left leaf.
		found_result_left,

		// The value was not found, should be added to right leaf.
		found_result_right
	};

	struct found_t {
		node_ptr_t m_node_ptr;
		found_result_t m_result;
	};

public:
	typedef Compare key_compare;
	typedef Compare value_compare;
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

	bool empty() const {
		return this->m_ctner.m_size == 0;
	}

	void clear();

	iterator find(const T& value);
	const_iterator find(const T& value) const;

	std::pair<iterator, bool> insert(const T& value);
	size_t erase(const T& value);
	T& operator[](const T& value);

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
	found_t find_i(const T& value) const;

private:
	rbtree__::ctner_t<value_type> m_ctner;
	key_compare m_less;
};


template <class T, class Compare = std::less<T>>
inline typename rbtree<T, Compare>::found_t rbtree<T, Compare>::find_i(const T& value) {
	found_t result;
}

} // namespace algo

