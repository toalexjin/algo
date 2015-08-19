/**
 * Hash table.
 *
 * Copyright (C) 2015 Alex Jin. All rights reserved.
 */

#pragma once

#include <string.h>
#include <assert.h>
#include <string>
#include <utility>


template <class Key>
class hash_t {
};

template <>
class hash_t<int> {
public:
	size_t operator()(const int& key) const {
		return (size_t)key;
	}
};

template <>
class hash_t<std::string> {
public:
	size_t operator()(const std::string& key) const {
		size_t hash = 0;

		for (auto it = key.begin(); it != key.end(); ++it) {
			hash += (size_t)(*it);
		}

		return hash;
	}
};


namespace hash_table_internal {
	template <class Key, class T>
	struct node_t {
		node_t(const Key& key, const T& value)
			: m_prev(0), m_next(0), m_value(key, value) {
		}

		node_t* m_prev;
		node_t* m_next;
		std::pair<const Key, T> m_value;
	};

	template <class Key, class T>
	struct ctner_t {
		struct link_t {
			node_t<Key, T>* m_first;
			node_t<Key, T>* m_last;
		};

		explicit ctner_t(size_t array_size) {
			m_array_size = array_size;
			m_array = new link_t[m_array_size];
			memset(m_array, 0, sizeof(m_array[0]) * m_array_size);
			m_size = 0;
		}

		~ctner_t() {
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
	};

	template <class Key, class T>
	class iterator_t {
	private:
		typedef node_t<Key, T>* node_ptr_t;

	public:
		typedef iterator_t<Key, T> self_type;
		typedef std::pair<const Key, T> value_type;

	public:
		iterator_t() : m_ctner(0), m_current(0), m_index(0), m_reverse(false) {
		}

		iterator_t(const self_type& it) {
			*this = it;
		}

		iterator_t(ctner_t<Key, T>* ctner, node_ptr_t current, int index, bool reverse)
			: m_ctner(ctner), m_current(current), m_index(index), m_reverse(reverse) {
		}

		value_type& operator*() const {
			assert(m_current != 0);
			return m_current->m_value;
		}

		self_type& operator++() {
			if (m_reverse) {
				this->prev_i();
			}
			else {
				this->next_i();
			}
			return *this;
		}

		self_type operator++(int) {
			const self_type old(*this);
			this->operator++();
			return old;
		}

		self_type& operator--() {
			if (m_reverse) {
				this->next_i();
			}
			else {
				this->prev_i();
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
				this->m_index = it.m_index;
				this->m_reverse = it.m_reverse;
			}

			return *this;
		}

		bool operator==(const self_type& it) {
			return this->m_current == it.m_current;
		}

		bool operator!=(const self_type& it) {
			return !this->operator==(it);
		}

	private:
		void prev_i() {
			assert(m_ctner != 0);
			assert(m_index != -1);

			if (m_current != 0 && m_current->m_prev != 0) {
				m_current = m_current->m_prev;
				return;
			}

			for (int i = m_index - 1; i >= 0 && i < (int) m_ctner->m_array_size; --i) {
				if (m_ctner->m_array[i].m_last != 0) {
					m_index = i;
					m_current = m_ctner->m_array[i].m_last;
					return;
				}
			}

			m_current = 0;
			m_index = (int) -1;
		}

		void next_i() {
			assert(m_ctner != 0);
			assert(m_index != (int) m_ctner->m_array_size);

			if (m_current != 0 && m_current->m_next != 0) {
				m_current = m_current->m_next;
				return;
			}

			for (int i = m_index + 1; i >= 0 && i < (int) m_ctner->m_array_size; ++i) {
				if (m_ctner->m_array[i].m_first != 0) {
					m_index = i;
					m_current = m_ctner->m_array[i].m_first;
					return;
				}
			}

			m_current = 0;
			m_index = (int) m_ctner->m_array_size;
		}

	private:
		ctner_t<Key, T>* m_ctner;
		node_ptr_t m_current;
		int m_index;
		bool m_reverse;
	};
}


template <class Key, class T, class Hash>
class hash_table_t {
public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef std::pair<const Key, T> value_type;
	typedef size_t size_type;
	typedef hash_table_internal::iterator_t<Key, T> iterator;
	typedef iterator reverse_iterator;

private:
	typedef hash_table_internal::node_t<Key, T>* node_ptr_t;

	struct found_t {
		found_t() : m_node(0), m_index(0) {
		}

		found_t(node_ptr_t node, size_t index) : m_node(node), m_index(index) {
		}

		node_ptr_t m_node;
		size_t m_index;
	};

public:
	hash_table_t() : m_ctner(256) {
	}

	virtual ~hash_table_t() {
	}

	explicit hash_table_t(size_t array_size) : m_ctner(array_size) {
	}

	size_t size() {
		return this->m_ctner.m_size;
	}

	bool empty() {
		return this->m_ctner.m_size == 0;
	}

	void clear();

	iterator find(const Key& key);
	std::pair<iterator, bool> insert(const Key& key, const T& value);
	size_t erase(const Key& key);
	mapped_type& operator[](const key_type& key);

	iterator begin();
	iterator end();
	reverse_iterator rbegin();
	reverse_iterator rend();

private:
	found_t find_i(const Key& key);

private:
	hash_table_internal::ctner_t<Key, T> m_ctner;
	Hash m_hash;
};


template <class Key, class T, class Hash>
inline void hash_table_t<Key, T, Hash>::clear() {
	this->m_ctner.clear();
}


template <class Key, class T, class Hash>
inline typename hash_table_t<Key, T, Hash>::iterator hash_table_t<Key, T, Hash>::find(const Key& key) {
	const auto found(this->find_i(key));

	return iterator(&this->m_ctner, found.m_node, (int) found.m_index, false);
}

template <class Key, class T, class Hash>
inline std::pair<typename hash_table_t<Key, T, Hash>::iterator, bool> hash_table_t<Key, T, Hash>::insert(const Key& key, const T& value) {
	const auto index = this->m_hash(key) % m_ctner.m_array_size;

	for (auto ptr = m_ctner.m_array[index].m_first; ptr != 0; ptr = ptr->m_next) {
		if (ptr->m_value.first == key) {
			return std::pair<typename hash_table_t<Key, T, Hash>::iterator, bool>(iterator(&m_ctner, ptr, (int) index, false), false);
		}
	}

	auto new_ptr = new hash_table_internal::node_t<Key, T>(key, value);

	if (m_ctner.m_array[index].m_first == 0) {
		m_ctner.m_array[index].m_first = new_ptr;
		m_ctner.m_array[index].m_last = new_ptr;
	}
	else {
		m_ctner.m_array[index].m_last->m_next = new_ptr;
		new_ptr->m_prev = m_ctner.m_array[index].m_last;
		m_ctner.m_array[index].m_last = new_ptr;
	}

	m_ctner.m_size++;
	return std::pair<typename hash_table_t<Key, T, Hash>::iterator, bool>(iterator(&m_ctner, new_ptr, (int) index, false), true);
}

template <class Key, class T, class Hash>
inline size_t hash_table_t<Key, T, Hash>::erase(const Key& key) {
	const auto found(this->find_i(key));

	if (found.m_node != 0) {
		if (found.m_node->m_prev != 0) {
			found.m_node->m_prev->m_next = found.m_node->m_next;
		}

		if (found.m_node->m_next != 0) {
			found.m_node->m_next->m_prev = found.m_node->m_prev;
		}

		if (m_ctner.m_array[found.m_index].m_first == found.m_node) {
			m_ctner.m_array[found.m_index].m_first = found.m_node->m_next;
		}

		if (m_ctner.m_array[found.m_index].m_last == found.m_node) {
			m_ctner.m_array[found.m_index].m_last = found.m_node->m_prev;
		}
		
		delete found.m_node;
		this->m_ctner.m_size--;
		return 1;
	}

	return 0;
}

template <class Key, class T, class Hash>
inline typename hash_table_t<Key, T, Hash>::iterator hash_table_t<Key, T, Hash>::begin() {
	for (int i = 0; i < (int) this->m_ctner.m_array_size; ++i) {
		if (m_ctner.m_array[i].m_first != 0) {
			return iterator(&m_ctner, m_ctner.m_array[i].m_first, i, false);
		}
	}

	return this->end();
}

template <class Key, class T, class Hash>
inline typename hash_table_t<Key, T, Hash>::iterator hash_table_t<Key, T, Hash>::end() {
	return iterator(&m_ctner, 0, (int) m_ctner.m_array_size, false);
}

template <class Key, class T, class Hash>
inline typename hash_table_t<Key, T, Hash>::reverse_iterator hash_table_t<Key, T, Hash>::rbegin() {
	for (int i = (int) this->m_ctner.m_array_size - 1; i >= 0; --i) {
		if (m_ctner.m_array[i].m_last != 0) {
			return reverse_iterator(&m_ctner, m_ctner.m_array[i].m_last, i, true);
		}
	}

	return this->rend();
}

template <class Key, class T, class Hash>
inline typename hash_table_t<Key, T, Hash>::reverse_iterator hash_table_t<Key, T, Hash>::rend() {
	return reverse_iterator(&m_ctner, 0, -1, true);
}

template <class Key, class T, class Hash>
inline T& hash_table_t<Key, T, Hash>::operator[](const key_type& key) {
	const auto found(this->find_i(key));
	if (found.m_node != 0) {
		return found.m_node->m_value.second;
	}

	const auto it( this->insert(key, T()).first );
	return (*it).second;
}

template <class Key, class T, class Hash>
inline typename hash_table_t<Key, T, Hash>::found_t hash_table_t<Key, T, Hash>::find_i(const Key& key) {
	const auto index = this->m_hash(key) % m_ctner.m_array_size;

	for (auto ptr = m_ctner.m_array[index].m_first; ptr != 0; ptr = ptr->m_next) {
		if (ptr->m_value.first == key) {
			return found_t(ptr, index);
		}
	}

	return found_t();
}
