#pragma once

#include "coordinate.h"

namespace Boggle
{
	class visitation_guard
	{
	public:
		bool has_visited(const coordinate& c) const;
		void visit(const coordinate& c);
	private:
		std::uint16_t m_visited = 0;
	};
}