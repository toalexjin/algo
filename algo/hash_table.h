/**
 * Hash table.
 *
 * Copyright (C) 2015 Alex Jin. All rights reserved.
 */

#pragma once

#include <memory>
#include <utility>


template <class Key>
class hash_t
{
};

template <>
class hash_t<int>
{
public:
	int operator()(const int& key) const
	{
		return key;
	}
};


template <class Key, class T, class Hash = hash_t<Key>>
class hash_table_t
{
public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef std::pair<const Key, T> value_type;
	typedef size_t size_type;

	class iterator;
	class const_iterator;

public:
	iterator begin()
	{

	}

	iterator end()
	{

	}

	const_iterator begin() const
	{

	}

	const_iterator end() const
	{

	}

	std::pair<iterator, bool> insert(const key_type& key, const mapped_type& value)
	{

	}

	mapped_type& operator[](const key_type& key)
	{

	}

	const mapped_type& operator[](const key_type& key) const
	{

	}

	iterator find(const value_type& value)
	{

	}

	const_iterator find(const value_type& value) const
	{

	}
	
	size_type erase(const key_type& key)
	{

	}

	void erase(iterator it)
	{

	}

	void erase(iterator first, iterator last)
	{

	}

	size_type size()
	{

	}

	bool empty()
	{

	}

	void clear()
	{

	}
};

