/**
 * Red-Black Tree.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#pragma once

#include <assert.h>
#include <functional>
#include <iterator>
#include <initializer_list>


namespace algo {


// Red-Black Tree internal implementation
namespace rbtree__ {

	// Tree node.
	template <class T>
	struct node_t {
		typedef node_t<T> self_type;
		typedef T value_type;

		explicit node_t(const T& value) : m_parent(0), m_left(0), m_right(0), m_value(value), m_black(false) {
		}

		self_type* m_parent;
		self_type* m_left;
		self_type* m_right;
		T m_value;
		bool m_black;
	};

	enum find_result_t {
		// There is no root node, the new value
		// could be added as root node.
		find_result_no_root,

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
		find_t() : m_node_ptr(0), m_result(find_result_no_root) {}

		node_t<T>* m_node_ptr;
		find_result_t m_result;
	};

	// Internal data container.
	template <class T, class Compare>
	class ctner_t {
	public:
		typedef ctner_t<T, Compare> self_type;
		typedef T value_type;

	public:
		ctner_t() : m_root(0), m_smallest(0), m_biggest(0), m_size(0) {
		}

		explicit ctner_t(const Compare& less)
			: m_root(0), m_smallest(0), m_biggest(0), m_size(0), m_less(less) {
		}

		~ctner_t() {
			this->clear();
		}

		size_t size() const {
			assert(this->is_valid());

			return this->m_size;
		}

		Compare key_compare() const {
			assert(this->is_valid());

			return this->m_less;
		}

		void clear() {
			assert(this->is_valid());

			if (m_root == 0) {
				return;
			}

			this->clear_i(m_root);
			m_root = 0;
			m_smallest = 0;
			m_biggest = 0;
			this->m_size = 0;
		}

		node_t<T>* get_smallest() const {
			return this->m_smallest;
		}

		node_t<T>* get_biggest() const {
			return this->m_biggest;
		}

		static node_t<T>* get_smallest_i(const node_t<T>* node_ptr) {
			if (node_ptr == 0) {
				return 0;
			}

			auto ptr = node_ptr;
			while (ptr->m_left != 0) {
				ptr = ptr->m_left;
			}

			return (node_t<T>*)ptr;
		}

		static node_t<T>* get_biggest_i(const node_t<T>* node_ptr) {
			if (node_ptr == 0) {
				return 0;
			}

			auto ptr = node_ptr;
			while (ptr->m_right != 0) {
				ptr = ptr->m_right;
			}

			return (node_t<T>*)ptr;
		}

		static node_t<T>* next(const node_t<T>* node_ptr) {
			assert(node_ptr != 0);

			const node_t<T>* result_ptr = 0;

			if (node_ptr->m_right != 0) {
				result_ptr = node_ptr->m_right;
				while (result_ptr->m_left != 0) {
					result_ptr = result_ptr->m_left;
				}
			}
			else {
				auto child = node_ptr;
				auto parent = child->m_parent;

				while (parent != 0 && parent->m_right == child) {
					child = parent;
					parent = parent->m_parent;
				}

				result_ptr = parent;
			}

			return (node_t<T>*)result_ptr;
		}

		static node_t<T>* prev(const node_t<T>* node_ptr) {
			const node_t<T>* result_ptr = 0;

			if (node_ptr->m_left != 0) {
				result_ptr = node_ptr->m_left;
				while (result_ptr->m_right != 0) {
					result_ptr = result_ptr->m_right;
				}
			}
			else {
				auto child = node_ptr;
				auto parent = child->m_parent;

				while (parent != 0 && parent->m_left == child) {
					child = parent;
					parent = parent->m_parent;
				}

				result_ptr = parent;
			}

			return (node_t<T>*) result_ptr;
		}

		std::pair<node_t<T>*, bool> insert(const T& value) {
			assert(this->is_valid());

			const auto found(this->find(value));

			// The key already exists.
			if (found.m_result == find_result_yes) {
				return std::pair<node_t<T>*, bool>(found.m_node_ptr, false);
			}

			// Create a new node.
			auto new_ptr = new node_t<T>(value);
			if (found.m_result == find_result_no_root) {
				this->m_root = new_ptr;
				this->m_smallest = new_ptr;
				this->m_biggest = new_ptr;
			}
			else if (found.m_result == find_result_left) {
				found.m_node_ptr->m_left = new_ptr;
				new_ptr->m_parent = found.m_node_ptr;

				// If the new node is left child of the current smallest node,
				// then the new node becomes the new smallest node.
				if (this->m_smallest == found.m_node_ptr) {
					this->m_smallest = new_ptr;
				}
			}
			else {
				found.m_node_ptr->m_right = new_ptr;
				new_ptr->m_parent = found.m_node_ptr;

				// If the new node is right child of the current biggest node,
				// then the new node becomes the new biggest node.
				if (this->m_biggest == found.m_node_ptr) {
					this->m_biggest = new_ptr;
				}
			}

			this->m_size++;

			// TO-DO: Rotate.

			return std::pair<node_t<T>*, bool>(new_ptr, true);
		}

		find_t<T> find(const T& value) const {
			assert(this->is_valid());

			find_t<T> result;

			auto ptr = (node_t<T>*) m_root;
			while (ptr != 0) {
				result.m_node_ptr = ptr;

				if (this->m_less(value, ptr->m_value)) {
					result.m_result = find_result_left;
					ptr = ptr->m_left;
				}
				else if (this->m_less(ptr->m_value, value)) {
					result.m_result = find_result_right;
					ptr = ptr->m_right;
				}
				else {
					result.m_result = find_result_yes;
					break;
				}
			}

			return result;
		}

		void replace_subtree(node_t<T>* node_old, node_t<T>* node_new) {
			if (this->m_root == node_old) {
				this->m_root = node_new;
			}
			else if (node_old == node_old->m_parent->m_left) {
				node_old->m_parent->m_left = node_new;
			}
			else {
				node_old->m_parent->m_right = node_new;
			}

			if (node_new != 0) {
				node_new->m_parent = node_old->m_parent;
			}
		}

		void erase(node_t<T>* node_ptr) {
			assert(this->is_valid());

			// Update smallest & biggest node pointers first.
			if (this->m_size == 1) {
				this->m_smallest = 0;
				this->m_biggest = 0;
			}
			else {
				if (this->m_smallest == node_ptr) {
					this->m_smallest = this->next(node_ptr);
				}

				if (this->m_biggest == node_ptr) {
					this->m_biggest = this->prev(node_ptr);
				}
			}

			if (node_ptr->m_left == 0) {
				this->replace_subtree(node_ptr, node_ptr->m_right);
			}
			else if (node_ptr->m_right == 0) {
				this->replace_subtree(node_ptr, node_ptr->m_left);
			}
			else {
				node_t<T>* next_ptr = this->get_smallest_i(node_ptr->m_right);

				if (next_ptr->m_parent != node_ptr) {
					this->replace_subtree(next_ptr, next_ptr->m_right);
					next_ptr->m_right = node_ptr->m_right;
					next_ptr->m_right->m_parent = next_ptr;
				}

				this->replace_subtree(node_ptr, next_ptr);
				next_ptr->m_left = node_ptr->m_left;
				next_ptr->m_left->m_parent = next_ptr;
			}

			this->m_size--;

			// TO-DO: Rotate.
		}

		void assign(self_type& another) {
			assert(this->is_valid());
			assert(another.is_valid());

			if (this != &another) {
				// Delete old data.
				this->clear();

				// Copy key-compare.
				this->m_less = another.m_less;

				// Copy nodes one by one.
				if (another.m_root != 0) {
					this->copy_i(&m_root, another.m_root);
				}
				this->m_size = another.m_size;

				// Get smallest and biggest nodes again.
				this->m_smallest = this->get_smallest_i(this->m_root);
				this->m_biggest = this->get_biggest_i(this->m_root);
			}
		}

	private:
		// Disable copy contructor & operator=().
		ctner_t(const self_type&);
		self_type& operator=(const self_type&);

		void clear_i(node_t<T>* node_ptr) {
			if (node_ptr->m_left != 0) {
				this->clear_i(node_ptr->m_left);
			}

			if (node_ptr->m_right != 0) {
				this->clear_i(node_ptr->m_right);
			}

			delete node_ptr;
		}

		void copy_i(node_t<T>** pptr, const node_t<T>* another) {
			*pptr = new node_t<T>(another->m_value);

			if (another->m_left != 0) {
				this->copy_i(&((*pptr)->m_left), another->m_left);
				(*pptr)->m_left->m_parent = *pptr;
			}

			if (another->m_right != 0) {
				this->copy_i(&((*pptr)->m_right), another->m_right);
				(*pptr)->m_right->m_parent = *pptr;
			}
		}

	#ifndef NDEBUG
		bool is_valid() const {
			if (this->m_smallest != this->get_smallest_i(m_root)
				|| this->m_biggest != this->get_biggest_i(m_root)) {
				return false;
			}

			return true;
		}
	#endif

	private:
		node_t<T>* m_root;
		node_t<T>* m_smallest;
		node_t<T>* m_biggest;
		size_t m_size;
		Compare m_less;
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

		explicit iterator_t(CtnerPointer ctner)
			: m_ctner(ctner), m_current(0) {
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
			m_current = this->m_ctner->next(m_current);
			return *this;
		}

		self_type operator++(int) {
			const self_type old(*this);
			this->operator++();
			return old;
		}

		self_type& operator--() {
			assert(m_ctner != 0);
			
			if (this->m_current == 0) {
				this->m_current = this->m_ctner->get_biggest();
			}
			else {
				this->m_current = this->m_ctner->prev(this->m_current);
			}

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

} // namespace rbtree__


/**
 * Red-Black Tree.
 */
template <class T, class Compare = std::less<T>>
class rbtree_t {
private:
	typedef rbtree_t<T, Compare> self_type;
	typedef rbtree__::node_t<T>* node_ptr_t;
	typedef const rbtree__::node_t<T>* const_node_ptr_t;
	typedef rbtree__::ctner_t<T, Compare> ctner_type;

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

	typedef rbtree__::iterator_t<value_type, pointer,
		reference, ctner_type*, node_ptr_t> iterator;
	typedef rbtree__::iterator_t<value_type, const_pointer,
		const_reference, const ctner_type*, const_node_ptr_t> const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> reverse_const_iterator;

public:
	rbtree_t() : rbtree_t(Compare()){
	}

	explicit rbtree_t(const Compare& less) {
		m_ctner = new ctner_type(less);
	}

	rbtree_t(const self_type& another) {
		m_ctner = new ctner_type();
		*this = another;
	}

	rbtree_t(std::initializer_list<T> list, const Compare& less = Compare())
		: rbtree_t(less) {
		this->insert(list);
	}

	virtual ~rbtree_t() {
		delete m_ctner;
		m_ctner = 0;
	}

	size_t size() const {
		return this->m_ctner->size();
	}

	size_t max_size() const {
		return size_t(-1);
	}

	bool empty() const {
		return this->size() == 0;
	}

	void clear() {
		this->m_ctner->clear();
	}

	key_compare key_comp() const {
		return this->m_ctner->key_compare();
	}

	value_compare value_comp() const {
		return this->key_comp();
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
	void insert(std::initializer_list<T> list);

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
	self_type& operator=(std::initializer_list<T> list);
	self_type& swap(self_type& another);

private:
	rbtree__::ctner_t<T, Compare>* m_ctner;
};


template <class T, class Compare>
inline typename rbtree_t<T, Compare>::iterator rbtree_t<T, Compare>::find(const T& value) {
	const auto found(this->m_ctner->find(value));

	if (found.m_result == rbtree__::find_result_yes) {
		return iterator(this->m_ctner, found.m_node_ptr);
	}
	else {
		return iterator(this->m_ctner);
	}
}

template <class T, class Compare>
inline typename rbtree_t<T, Compare>::const_iterator rbtree_t<T, Compare>::find(const T& value) const {
	const auto found(this->m_ctner->find(value));

	if (found.m_result == rbtree__::find_result_yes) {
		return const_iterator(this->m_ctner, found.m_node_ptr);
	}
	else {
		return const_iterator(this->m_ctner);
	}
}

template <class T, class Compare>
inline std::pair<typename rbtree_t<T, Compare>::iterator, bool> rbtree_t<T, Compare>::insert(const T& value) {
	auto result = this->m_ctner->insert(value);

	return std::pair<typename rbtree_t<T, Compare>::iterator, bool>(
		iterator(this->m_ctner, result.first), result.second);
}

template <class T, class Compare>
inline void rbtree_t<T, Compare>::insert(std::initializer_list<T> list) {
	for (auto it = list.begin(); it != list.end(); ++it) {
		this->insert(*it);
	}
}

template <class T, class Compare>
inline void rbtree_t<T, Compare>::erase(typename rbtree_t<T, Compare>::iterator it) {
	if (it.get_ctner_ptr__() == this->m_ctner) {
		// Same container.
		assert(it != this->end());
		this->m_ctner->erase(it.get_node_ptr__());
	}
	else {
		// Different container.
		this->erase(*it);
	}
}

template <class T, class Compare>
inline void rbtree_t<T, Compare>::erase(
	typename rbtree_t<T, Compare>::iterator first,
	typename rbtree_t<T, Compare>::iterator last) {
	for (auto it = first; it != last;) {
		this->erase(it++);
	}
}

template <class T, class Compare>
inline size_t rbtree_t<T, Compare>::erase(const T& value) {
	const auto found(this->m_ctner->find(value));

	if (found.m_result != rbtree__::find_result_yes) {
		return 0;
	}

	this->m_ctner->erase(found.m_node_ptr);
	return 1;
}

template <class T, class Compare>
inline typename rbtree_t<T, Compare>::iterator rbtree_t<T, Compare>::begin() {
	return iterator(this->m_ctner, this->m_ctner->get_smallest());
}

template <class T, class Compare>
inline typename rbtree_t<T, Compare>::iterator rbtree_t<T, Compare>::end() {
	return iterator(this->m_ctner);
}

template <class T, class Compare>
inline typename rbtree_t<T, Compare>::const_iterator rbtree_t<T, Compare>::begin() const {
	return const_iterator(this->m_ctner, this->m_ctner->get_smallest());
}

template <class T, class Compare>
inline typename rbtree_t<T, Compare>::const_iterator rbtree_t<T, Compare>::end() const {
	return const_iterator(this->m_ctner);
}

template <class T, class Compare>
inline typename rbtree_t<T, Compare>::reverse_iterator rbtree_t<T, Compare>::rbegin() {
	return reverse_iterator(this->end());
}

template <class T, class Compare>
inline typename rbtree_t<T, Compare>::reverse_iterator rbtree_t<T, Compare>::rend() {
	return reverse_iterator(this->begin());
}

template <class T, class Compare>
inline typename rbtree_t<T, Compare>::reverse_const_iterator rbtree_t<T, Compare>::rbegin() const {
	return reverse_const_iterator(this->end());
}

template <class T, class Compare>
inline typename rbtree_t<T, Compare>::reverse_const_iterator rbtree_t<T, Compare>::rend() const {
	return reverse_const_iterator(this->begin());
}

template <class T, class Compare>
inline typename rbtree_t<T, Compare>::self_type& rbtree_t<T, Compare>::operator=(
	const typename rbtree_t<T, Compare>::self_type& another) {
	this->m_ctner->assign(*(another.m_ctner));
	return *this;
}

template <class T, class Compare>
inline typename rbtree_t<T, Compare>::self_type& rbtree_t<T, Compare>::operator=(std::initializer_list<T> list) {
	this->clear();
	this->insert(list);
	return *this;
}

template <class T, class Compare>
inline typename rbtree_t<T, Compare>::self_type& rbtree_t<T, Compare>::swap(
	typename rbtree_t<T, Compare>::self_type& another) {
	if (this != &another) {
		auto tmp(this->m_ctner);
		this->m_ctner = another.m_ctner;
		another.m_ctner = tmp;
	}

	return *this;
}

} // namespace algo


namespace std {

// Override std::swap() to offer better performance.
template <class T, class Compare>
inline void swap(algo::rbtree_t<T, Compare>& v1, algo::rbtree_t<T, Compare>& v2) {
	v1.swap(v2);
}

}
