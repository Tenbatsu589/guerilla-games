#include "pch.h"
#include "coordinate.h"

using namespace Boggle;

coordinate::coordinate()
{
	m_data.joined = 0;
}

coordinate::coordinate(size_type x, size_type y)
{
	m_data.seperated.X = x;
	m_data.seperated.Y = y;
}

coordinate::coordinate(size_type index)
{
	m_data.seperated.X = index % s_dimension;
	m_data.seperated.Y = index / s_dimension;
}
