#pragma once

#include "ExpressionContainer.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct ExpressionContainer : ExpressionContainerT<ExpressionContainer>
	{
		void Text(param::hstring CR _text);
		[[nodiscard]] UIElementCollection Items();

		void ShowCopy(IInspectable CR, RightTappedRoutedEventArgs CR);

	private:
		hstring text;
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct ExpressionContainer : ExpressionContainerT<ExpressionContainer, implementation::ExpressionContainer>
	{
	};
}
