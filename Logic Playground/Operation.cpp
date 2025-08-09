#include "pch.h"
#include "Operation.h"
#if __has_include("Operation.g.cpp")
#include "Operation.g.cpp"
#endif

namespace winrt::Logic_Playground::implementation
{
	Operation::Operation(OperationCategory CR _category) :category(_category)
	{
	}

	OperationCategory Operation::Category() const
	{
		return category;
	}

	IVector<hstring> Operation::Contents() const
	{
		return contents;
	}
}
