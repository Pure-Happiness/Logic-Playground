#pragma once

#include "Operation.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct Operation : OperationT<Operation>
	{
		explicit Operation(OperationCategory CR _category);
		[[nodiscard]] OperationCategory Category() const;
		[[nodiscard]] IVector<hstring> Contents() const;

	private:
		OperationCategory category;
		IVector<hstring> contents = single_threaded_vector<hstring>();
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct Operation : OperationT<Operation, implementation::Operation>
	{
	};
}
