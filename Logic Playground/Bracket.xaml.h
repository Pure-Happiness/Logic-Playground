#pragma once

#include "Bracket.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct Bracket : BracketT<Bracket>
	{
		using BracketP = Logic_Playground::Bracket;

		[[nodiscard]] bool ChainClick() const;
		void ChainClick(bool CR _chain_click);
		void ChainCheck();
		void ChainUncheck();
		static void Link(BracketP CR _left, BracketP CR _right);

	private:
		bool chain_click;
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct Bracket : BracketT<Bracket, implementation::Bracket>
	{
	};
}
