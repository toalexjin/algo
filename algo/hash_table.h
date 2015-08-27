/**
 * Hash table.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#pragma once

#include "algo/key_traits.h"
#include <string.h>
#include <assert.h>
#include <utility>


namespace algo {

// Internal implementation.
namespace hash_table__ {
	template <class Key, class T>
	struct node_t {
		node_t(const Key& key, const T& value)
			: m_prev(0), m_next(0), m_value(key, value) {
		}

		node_t* m_prev;
		node_t* m_next;
		std::pair<const Key, T> m_value;
	};

	template <class Key, class T, class KeyTraits>
	struct ctner_t {
		struct link_t {
			node_t<Key, T>* m_first;
			node_t<Key, T>* m_last;
		};

		ctner_t() : m_array(0), m_array_size(0), m_size(0) {
		}

		void reset(size_t array_size) {
			this->destroy();

			m_array_size = array_size;
			m_array = new link_t[m_array_size];
			memset(m_array, 0, sizeof(m_array[0]) * m_array_size);
			m_size = 0;
		}

		~ctner_t() {
			this->destroy();
		}

		void destroy() {
			this->clear();
			delete[] m_array;
			m_array = 0;
			m_array_size = 0;
		}

		void clear() {
			for (size_t i = 0; i < m_array_size; ++i) {
				for (auto current = m_array[i].m_first; current != 0;) {
					auto deleted = current;
					current = current->m_next;
					delete deleted;
				}
			}

			memset(m_array, 0, sizeof(m_array[0]) * m_array_size);
			m_size = 0;
		}

		link_t* m_array;
		size_t m_array_size;
		size_t m_size;
		KeyTraits m_key_traits;
	};


	template <class Key, class T, class Pointer, class Reference, class CtnerPointer, class NodePointer>
	class iterator_t : public std::iterator<
			std::bidirectional_iterator_tag,
			std::pair<const Key, T>, std::ptrdiff_t, Pointer, Reference> {
	private:
		typedef iterator_t<Key, T, Pointer, Reference, CtnerPointer, NodePointer> self_type;

	public:
		iterator_t() : m_ctner(0), m_current(0), m_index(0) {
		}

		iterator_t(const self_type& it) {
			*this = it;
		}

		iterator_t(CtnerPointer ctner, NodePointer current, int index)
			: m_ctner(ctner), m_current(current), m_index(index) {
		}

		Reference operator*() const {
			assert(m_ctner != 0);
			assert(m_current != 0);
			assert(m_index >= 0 && m_index < (int)m_ctner->m_array_size);

			return m_current->m_value;
		}

		Pointer operator->() const {
			assert(m_ctner != 0);
			assert(m_current != 0);
			assert(m_index >= 0 && m_index < (int)m_ctner->m_array_size);

			return &m_current->m_value;
		}

		self_type& operator++() {
			assert(m_ctner != 0);
			assert(m_current != 0);
			assert(m_index >= 0 && m_index < (int) m_ctner->m_array_size);

			if (m_current != 0 && m_current->m_next != 0) {
				m_current = m_current->m_next;
				return *this;
			}

			for (int i = m_index + 1; i < (int)m_ctner->m_array_size; ++i) {
				if (m_ctner->m_array[i].m_first != 0) {
					m_current = m_ctner->m_array[i].m_first;
					m_index = i;
					return *this;
				}
			}

			m_current = 0;
			m_index = (int)m_ctner->m_array_size;

			return *this;
		}

		self_type operator++(int) {
			const self_type old(*this);
			this->operator++();
			return old;
		}

		self_type& operator--() {
			assert(m_ctner != 0);
			assert(m_index >= 0 && m_index <= (int)m_ctner->m_array_size);

			if (m_current != 0 && m_current->m_prev != 0) {
				m_current = m_current->m_prev;
				return *this;
			}

			for (int i = m_index - 1; i >= 0; --i) {
				if (m_ctner->m_array[i].m_last != 0) {
					m_current = m_ctner->m_array[i].m_last;
					m_index = i;
					return *this;
				}
			}

			// Should not run here.
			assert(false);

			m_current = 0;
			m_index = (int)-1;

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
				this->m_index = it.m_index;
			}

			return *this;
		}

		bool operator==(const self_type& it) {
			if (this->m_ctner == it.m_ctner
				&& this->m_current == it.m_current
				&& this->m_index == it.m_index) {
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
		int m_index;
	};

	template <class Key, class T>
	struct find_t {
		find_t() : m_node_ptr(0), m_index(0) {
		}

		find_t(node_t<Key, T>* node_ptr, size_t index) : m_node_ptr(node_ptr), m_index(index) {
		}

		node_t<Key, T>* m_node_ptr;
		size_t m_index;
	};
}


// Hash table.
template <class Key, class T, class KeyTraits = key_traits_t<Key>>
class hash_table_t {
private:
	typedef hash_table_t<Key, T, KeyTraits> self_type;
	typedef hash_table__::node_t<Key, T>* node_ptr_t;
	typedef const hash_table__::node_t<Key, T>* const_node_ptr_t;
	typedef hash_table__::ctner_t<Key, T, KeyTraits> ctner_type;

public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef std::pair<const Key, T> value_type;
	typedef KeyTraits key_traits;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef hash_table__::iterator_t<Key, T, pointer, reference,
		ctner_type*, node_ptr_t> iterator;
	typedef hash_table__::iterator_t<Key, T, const_pointer, const_reference,
		const ctner_type*, const_node_ptr_t> const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> reverse_const_iterator;

public:
	hash_table_t() {
		this->m_ctner = new ctner_type();
		this->m_ctner->reset(256);
	}

	hash_table_t(const self_type& another) {
		this->m_ctner = new ctner_type();
		*this = another;
	}

	explicit hash_table_t(size_t array_size) {
		assert(array_size > 0);
		this->m_ctner = new ctner_type();
		this->m_ctner->reset(array_size);
	}

	explicit hash_table_t(const KeyTraits& key_traits, size_t array_size = 256) {
		assert(array_size > 0);
		this->m_ctner = new ctner_type();
		this->m_ctner->reset(array_size);
		this->m_ctner->m_key_traits = key_traits;
	}

	virtual ~hash_table_t() {
		delete this->m_ctner;
		this->m_ctner = 0;
	}

	size_t size() const {
		return this->m_ctner->m_size;
	}

	bool empty() const {
		return this->size() == 0;
	}

	key_traits key_comp() const {
		return this->m_ctner->m_key_traits;
	}

	void clear();

	iterator find(const Key& key);
	const_iterator find(const Key& key) const;

	std::pair<iterator, bool> insert(const Key& key, const T& value);
	size_t erase(const Key& key);
	mapped_type& operator[](const key_type& key);

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
	hash_table__::find_t<Key, T> find_i(const Key& key) const;

private:
	ctner_type* m_ctner;
};


template <class Key, class T, class KeyTraits>
inline void hash_table_t<Key, T, KeyTraits>::clear() {
	this->m_ctner->clear();
}

template <class Key, class T, class KeyTraits>
inline typename hash_table_t<Key, T, KeyTraits>::iterator hash_table_t<Key, T, KeyTraits>::find(const Key& key) {
	const auto found(this->find_i(key));

	return iterator(this->m_ctner, found.m_node_ptr, (int)found.m_index);
}

template <class Key, class T, class KeyTraits>
inline typename hash_table_t<Key, T, KeyTraits>::const_iterator hash_table_t<Key, T, KeyTraits>::find(const Key& key) const {
	const auto found(this->find_i(key));

	return const_iterator(this->m_ctner, found.m_node_ptr, (int)found.m_index);
}

template <class Key, class T, class KeyTraits>
inline std::pair<typename hash_table_t<Key, T, KeyTraits>::iterator, bool> hash_table_t<Key, T, KeyTraits>::insert(const Key& key, const T& value) {
	const auto index = this->m_ctner->m_key_traits.hash(key) % m_ctner->m_array_size;

	for (auto ptr = m_ctner->m_array[index].m_first; ptr != 0; ptr = ptr->m_next) {
		if (this->m_ctner->m_key_traits.equal(ptr->m_value.first, key)) {
			return std::pair<typename hash_table_t<Key, T, KeyTraits>::iterator, bool>(iterator(m_ctner, ptr, (int)index), false);
		}
	}

	auto new_ptr = new hash_table__::node_t<Key, T>(key, value);

	if (m_ctner->m_array[index].m_first == 0) {
		m_ctner->m_array[index].m_first = new_ptr;
		m_ctner->m_array[index].m_last = new_ptr;
	}
	else {
		m_ctner->m_array[index].m_last->m_next = new_ptr;
		new_ptr->m_prev = m_ctner->m_array[index].m_last;
		m_ctner->m_array[index].m_last = new_ptr;
	}

	m_ctner->m_size++;
	return std::pair<typename hash_table_t<Key, T, KeyTraits>::iterator, bool>(iterator(m_ctner, new_ptr, (int)index), true);
}

template <class Key, class T, class KeyTraits>
inline size_t hash_table_t<Key, T, KeyTraits>::erase(const Key& key) {
	const auto found(this->find_i(key));

	if (found.m_node_ptr == 0) {
		return 0;
	}

	if (found.m_node_ptr->m_prev != 0) {
		found.m_node_ptr->m_prev->m_next = found.m_node_ptr->m_next;
	}

	if (found.m_node_ptr->m_next != 0) {
		found.m_node_ptr->m_next->m_prev = found.m_node_ptr->m_prev;
	}

	if (m_ctner->m_array[found.m_index].m_first == found.m_node_ptr) {
		m_ctner->m_array[found.m_index].m_first = found.m_node_ptr->m_next;
	}

	if (m_ctner->m_array[found.m_index].m_last == found.m_node_ptr) {
		m_ctner->m_array[found.m_index].m_last = found.m_node_ptr->m_prev;
	}

	delete found.m_node_ptr;
	this->m_ctner->m_size--;

	return 1;
}

template <class Key, class T, class KeyTraits>
inline typename hash_table_t<Key, T, KeyTraits>::iterator hash_table_t<Key, T, KeyTraits>::begin() {
	for (int i = 0; i < (int) this->m_ctner->m_array_size; ++i) {
		if (m_ctner->m_array[i].m_first != 0) {
			return iterator(m_ctner, m_ctner->m_array[i].m_first, i);
		}
	}

	return this->end();
}

template <class Key, class T, class KeyTraits>
inline typename hash_table_t<Key, T, KeyTraits>::iterator hash_table_t<Key, T, KeyTraits>::end() {
	return iterator(m_ctner, 0, (int)m_ctner->m_array_size);
}

template <class Key, class T, class KeyTraits>
inline typename hash_table_t<Key, T, KeyTraits>::const_iterator hash_table_t<Key, T, KeyTraits>::begin() const {
	for (int i = 0; i < (int) this->m_ctner->m_array_size; ++i) {
		if (m_ctner->m_array[i].m_first != 0) {
			return const_iterator(m_ctner, m_ctner->m_array[i].m_first, i);
		}
	}

	return this->end();
}

template <class Key, class T, class KeyTraits>
inline typename hash_table_t<Key, T, KeyTraits>::const_iterator hash_table_t<Key, T, KeyTraits>::end() const {
	return const_iterator(m_ctner, 0, (int)m_ctner->m_array_size);
}

template <class Key, class T, class KeyTraits>
inline typename hash_table_t<Key, T, KeyTraits>::reverse_iterator hash_table_t<Key, T, KeyTraits>::rbegin() {
	return reverse_iterator(this->end());
}

template <class Key, class T, class KeyTraits>
inline typename hash_table_t<Key, T, KeyTraits>::reverse_iterator hash_table_t<Key, T, KeyTraits>::rend() {
	return reverse_iterator(this->begin());
}

template <class Key, class T, class KeyTraits>
inline typename hash_table_t<Key, T, KeyTraits>::reverse_const_iterator hash_table_t<Key, T, KeyTraits>::rbegin() const {
	return reverse_const_iterator(this->end());
}

template <class Key, class T, class KeyTraits>
inline typename hash_table_t<Key, T, KeyTraits>::reverse_const_iterator hash_table_t<Key, T, KeyTraits>::rend() const {
	return reverse_const_iterator(this->begin());
}

template <class Key, class T, class KeyTraits>
inline typename hash_table_t<Key, T, KeyTraits>::self_type& hash_table_t<Key, T, KeyTraits>::operator=(
	const typename hash_table_t<Key, T, KeyTraits>::self_type& another) {

	if (this != &another) {
		this->m_ctner->reset(another.m_ctner->m_array_size);
		for (const_iterator it = another.begin(); it != another.end(); ++it) {
			this->insert(it->first, it->second);
		}
	}

	return *this;
}

template <class Key, class T, class KeyTraits>
inline typename hash_table_t<Key, T, KeyTraits>::self_type& hash_table_t<Key, T, KeyTraits>::swap(
	typename hash_table_t<Key, T, KeyTraits>::self_type& another) {

	if (this != &another) {
		auto tmp(this->m_ctner);
		this->m_ctner = another.m_ctner;
		another.m_ctner = tmp;
	}

	return *this;
}

template <class Key, class T, class KeyTraits>
inline T& hash_table_t<Key, T, KeyTraits>::operator[](const key_type& key) {
	const auto found(this->find_i(key));
	if (found.m_node_ptr != 0) {
		return found.m_node_ptr->m_value.second;
	}

	const auto it(this->insert(key, T()).first);
	return (*it).second;
}

template <class Key, class T, class KeyTraits>
inline hash_table__::find_t<Key, T> hash_table_t<Key, T, KeyTraits>::find_i(const Key& key) const {
	const auto index = this->m_ctner->m_key_traits.hash(key) % m_ctner->m_array_size;

	for (auto ptr = m_ctner->m_array[index].m_first; ptr != 0; ptr = ptr->m_next) {
		if (this->m_ctner->m_key_traits.equal(ptr->m_value.first, key)) {
			return hash_table__::find_t<Key, T>((node_ptr_t) ptr, index);
		}
	}

	return hash_table__::find_t<Key, T>(0, m_ctner->m_array_size);
}

} // namespace algo


namespace std {

// Override std::swap() to offer better performance.
template <class Key, class T, class KeyTraits>
inline void swap(algo::hash_table_t<Key, T, KeyTraits>& v1, algo::hash_table_t<Key, T, KeyTraits>& v2) {
	v1.swap(v2);
}

}
