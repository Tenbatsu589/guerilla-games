#include "pch.h"
#include "visitation_guard.h"

using namespace Boggle;

bool visitation_guard::has_visited(const coordinate& coord) const
{
	coordinate::size_type index = coord.index();
	std::uint16_t mask = 1 << index;
	return (m_visited & mask) != 0;
}

void visitation_guard::visit(const coordinate& coord)
{
	coordinate::size_type index = coord.index();
	std::uint16_t mask = 1 << index;
	m_visited |= mask;
}