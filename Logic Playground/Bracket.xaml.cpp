#include "pch.h"
#include "Bracket.xaml.h"
#if __has_include("Bracket.g.cpp")
#include "Bracket.g.cpp"
#endif

namespace winrt::Logic_Playground::implementation
{
	bool Bracket::ChainClick() const
	{
		return chain_click;
	}

	void Bracket::ChainClick(bool CR _chain_click)
	{
		chain_click = _chain_click;
	}

	void Bracket::ChainCheck()
	{
		chain_click = true;
		Child().IsChecked(true);
	}

	void Bracket::ChainUncheck()
	{
		chain_click = true;
		Child().IsChecked(false);
	}

	void Bracket::Link(BracketP CR _left, BracketP CR _right)
	{
		{
			const ToggleButton left = _left.Child();
			const TextBlock content = RegularCode(L"(");
			content.Foreground(ThemeGreenYellow);
			left.Content(content);
			left.Checked([wl = weak_ref(_left), wr = weak_ref(_right)](IInspectable CR, RoutedEventArgs CR)
				{
					if (wl.get().ChainClick())
						wl.get().ChainClick(false);
					else
						wr.get().ChainCheck();
				});
			left.Unchecked([wl = weak_ref(_left), wr = weak_ref(_right)](IInspectable CR, RoutedEventArgs CR)
				{
					if (wl.get().ChainClick())
						wl.get().ChainClick(false);
					else
						wr.get().ChainUncheck();
				});
		}
		{
			const ToggleButton right = _right.Child();
			const TextBlock content = RegularCode(L")");
			content.Foreground(ThemeGreenYellow);
			right.Content(content);
			right.Checked([wl = weak_ref(_left), wr = weak_ref(_right)](IInspectable CR, RoutedEventArgs CR)
				{
					if (wr.get().ChainClick())
						wr.get().ChainClick(false);
					else
						wl.get().ChainCheck();
				});
			right.Unchecked([wl = weak_ref(_left), wr = weak_ref(_right)](IInspectable CR, RoutedEventArgs CR)
				{
					if (wr.get().ChainClick())
						wr.get().ChainClick(false);
					else
						wl.get().ChainUncheck();
				});
		}
	}
}
