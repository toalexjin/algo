/**
 * Key Traits.
 *
 * Copyright (C) 2015 Alex Jin. All rights reserved.
 */

#pragma once

#include <string>

namespace algo {

	// Key traits, used by hash_table_t, etc.
	template <class Key>
	class key_traits_t {
	public:
		static size_t hash(const Key& key) {
			return (size_t)key;
		}

		static bool equal(const Key& key1, const Key& key2) {
			return key1 == key2;
		}
	};


	template <class Char, class CharTraits, class Allocator>
	class key_traits_t<std::basic_string<Char, CharTraits, Allocator>> {
	public:
		static size_t hash(const std::basic_string<Char, CharTraits, Allocator>& key) {
			size_t value = 0;

			for (auto it = key.c_str(); *it != 0; ++it) {
				value += (size_t)(*it);
			}

			return value;
		}

		static bool equal(const std::basic_string<Char, CharTraits, Allocator>& key1,
			const std::basic_string<Char, CharTraits, Allocator>& key2) {
			return key1 == key2;
		}
	};

} // namespace algo

