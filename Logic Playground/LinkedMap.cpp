#include "pch.h"
#include "LinkedMap.h"
#if __has_include("LinkedMap.g.cpp")
#include "LinkedMap.g.cpp"
#endif

namespace winrt::Logic_Playground::implementation
{
	LinkedMapP LinkedMap::Parent() const
	{
		return parent;
	}

	void LinkedMap::Parent(LinkedMapP CR _parent)
	{
		parent = _parent;
	}

	void LinkedMap::Insert(hstring CR _key, UIElement CR _value)
	{
		Trie* current = &trie;
		for (wchar_t CR c : _key)
			if (Trie*& next = current->children[c])
				current = next;
			else
				current = next = new Trie{ nullptr, {}, {}, current };
		for (current->value = _value; current; current = current->parent)
			current->with_prefix.insert(_value);
	}

	void LinkedMap::Remove(hstring CR _key)
	{
		Trie* current = &trie;
		for (wchar_t CR c : _key)
			current = current->children[c];
		const UIElement to_remove = current->value;
		for (current->value = nullptr; current; current = current->parent)
			current->with_prefix.erase(to_remove);
	}

	UIElement LinkedMap::Lookup(hstring CR _key) const
	{
		const Trie* current = &trie;
		for (wchar_t CR c : _key)
			if (!((current = current->children[c])))
				goto next;
		if (current->value)
			return current->value;
	next:
		if (parent)
			return parent.Lookup(_key);
		return nullptr;
	}

	IVectorView<UIElement> LinkedMap::WithPrefix(hstring CR _prefix) const
	{
		const IVector result = single_threaded_vector<UIElement>();
		const Trie* current = &trie;
		for (wchar_t CR c : _prefix)
			if (!((current = current->children[c])))
				goto next;
		for (UIElement CR element : current->with_prefix)
			result.Append(element);
	next:
		if (parent)
			for (UIElement CR element : parent.WithPrefix(_prefix))
				result.Append(element);
		return result.GetView();
	}

	bool LinkedMap::InCurrent(hstring const& _key) const
	{
		const Trie* current = &trie;
		for (wchar_t CR c : _key)
			if (!((current = current->children[c])))
				return false;
		return static_cast<bool>(current->value);
	}

	LinkedMap::Trie::~Trie()
	{
		for (const Trie* CR child : children)
			delete child;
	}
}
