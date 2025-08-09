#pragma once

#include "LinkedMap.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct LinkedMap : LinkedMapT<LinkedMap>
	{
		[[nodiscard]] LinkedMapP Parent() const;
		void Parent(LinkedMapP CR _parent);
		void Insert(hstring CR _key, UIElement CR _value);
		void Remove(hstring CR _key);
		[[nodiscard]] UIElement Lookup(hstring CR _key) const;
		[[nodiscard]] IVectorView<UIElement> WithPrefix(hstring CR _prefix) const;
		[[nodiscard]] bool InCurrent(hstring CR _key) const;

	private:
		LinkedMapP parent = nullptr;
		struct Trie
		{
			constexpr static size_t SIZE = 0x10000;
			UIElement value = nullptr;
			unordered_set<UIElement> with_prefix;
			array<Trie*, SIZE> children;
			Trie* parent;

			~Trie();
		} trie;
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct LinkedMap : LinkedMapT<LinkedMap, implementation::LinkedMap>
	{
	};
}
