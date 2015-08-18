/**
 * Hash table.
 *
 * Copyright (C) 2015 Alex Jin. All rights reserved.
 */

#pragma once

#include <memory>
#include <utility>


template <class Key>
class hash_t {
};

template <>
class hash_t<int> {
public:
	int operator()(const int& key) const {
		return key;
	}
};


namespace details {
	template <class Key, class T>
	struct node_t {
		node_t* m_prev;
		node_t* m_next;
		typedef std::pair<const Key, T> m_value;
	};

	template <class Key, class T>
	class iterator_t {
	private:
		typedef node_t<Key, T>* node_ptr_t;

	public:
		typedef iterator_t<Key, T> self_type;
		typedef std::pair<const Key, T> value_type;

	public:
		iterator_t() : m_array(0), m_array_size(0), m_current(0), m_index(0) {
		}

		iterator_t(const self_type& it) {
			*this = it;
		}

		iterator_t(node_ptr_t* array, size_t array_size, node_ptr_t current, size_t index)
			: m_array(array), m_array_size(array_size), m_current(current), m_index(index) {
		}

		value_type& operator*() const {
			return m_current->m_value;
		}
		
		self_type& operator++() {
			if (m_current->m_next != 0) {
				m_current = m_current->m_next;
				return *this;
			}

			for (auto i = m_index + 1; i < m_impl->m_hash_size; ++i) {
				if (m_impl->m_array[i] != 0) {
					m_index = i;
					m_current = m_array[i];
					return *this;
				}
			}

			m_current = 0;
			m_index = 0;

			return *this;
		}

		self_type operator++(int) {
			constexpr self_type old(*this);
			this->operator++();
			return old;
		}

		self_type& operator=(const self_type& it) {
			if (this != &it) {
				this.m_impl = it.m_impl;
				this.m_current = it.m_current;
				this.m_index = it.m_index;
			}

			return *this;
		}

		bool operator==(const self_type& it) {
			if (m_current == it.m_current) {
				return true;
			}

			return false;
		}

		bool operator!=(const self_type& it) {
			return !this->operator==(it);
		}

	private:
		node_ptr_t* m_array;
		size_t m_array_size;
		node_ptr_t m_current;
		size_t m_index;
	};
}


template <class Key, class T, class Hash = hash_t<Key>>
class hash_table_t {
public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef std::pair<const Key, T> value_type;
	typedef size_t size_type;

	class iterator;
	class const_iterator;

private:
	typedef details::node_t<Key, T>* node_ptr_t;

public:
	hash_table_t() {
		this->init_i(256);
	}

	explicit hash_table_t(size_t array_size) {
		this->init_i(array_size);
	}

	size_t size() {
		return this->m_size;
	}

	bool empty() {
		return this->m_size == 0;
	}

	void clear();

	iterator_t<Key, T> find(const Key& key);
	std::pair<iterator_t<Key, T>, bool> insert(const Key& key, const T& value);
	size_t erase(const Key& key);

	iterator begin();
	iterator end();

	mapped_type& operator[](const key_type& key);

private:
	void init_i(size_t hash_size);
	std::pair<node_ptr_t, size_t> find_i(const Key& key);

private:
	node_ptr_t* m_array;
	size_t m_array_size;
	size_t m_size;
};


template <class Key, class T>
inline void hash_table_t::clear() {
	for (size_t i = 0; i < m_array_size; ++i) {
		for (auto current = m_array[i]; current != 0;) {
			auto deleted = current;
			current = current->next;
			delete deleted;
		}
	}

	memset(m_array, 0, sizeof(typename hash_table_t::node_ptr_t) * m_array_size);
	this.m_size = 0;
}


template <class Key, class T>
inline typename hash_table_t<Key, T>::iterator hash_table_t::find(const Key& key) {
	const auto found(this->find_i(key));

	return iterator(this->m_array, this->m_array_size, found.first, found.second);
}

template <class Key, class T>
inline std::pair<typename hash_table_t<Key, T>::iterator, bool> hash_table_t::insert(const Key& key, const T& value) {

}

template <class Key, class T>
inline size_t hash_table_t::erase(const Key& key) {
	constexpr auto found(this->find_i(key));

	if (found.first != 0) {
		found.first.prev.next = found.first.next;
		delete found;
		this->m_size--;
		return 1;
	}

	return 0;
}

template <class Key, class T>
inline typename hash_table_t<Key, T>::iterator hash_table_t::begin() {

}

template <class Key, class T>
inline typename hash_table_t<Key, T>::iterator hash_table_t::end() {
	return iterator(this->m_array, this->m_array_size, 0, 0);
}

template <class Key, class T>
inline T& hash_table_t::operator[](const key_type& key) {
	const auto it( this->insert(key, T()).first );

	return (*it).second;
}

template <class Key, class T>
inline void hash_table_t::init_i(size_t array_size) {
	this->m_array_size = array_size;
	this->m_array = new node_ptr_t[array_size];
	memset(this->m_array, 0, sizeof(node_ptr_t) * array_size);
	this->m_size = 0;
}

template <class Key, class T>
inline std::pair<typename hash_table_t<Key, T>::node_ptr_t, size_t> hash_table_t::find_i(const Key& key) {

}
