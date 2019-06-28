#pragma once

#include "pch.h"

namespace Boggle
{
	class coordinate
	{
	public:
		using size_type = std::int16_t;
		coordinate();
		coordinate(size_type x, size_type y);
		coordinate(size_type index);
		inline size_type index() const { return Y() * s_dimension + X(); }

		template<typename FUNC>
		friend void iterate_neighbors(const coordinate& c, FUNC&& func);

		inline bool operator==(const coordinate& cmp) const { return m_data.joined == cmp.m_data.joined; }
		inline bool operator!=(const coordinate& cmp) const { return !(*this == cmp); }

		inline size_type X() const { return m_data.seperated.X; }
		inline size_type Y() const { return m_data.seperated.Y; }
		constexpr static std::uint8_t s_dimension = 4;
	private:
		struct cartesian {
			size_type X;
			size_type Y;
		};

		using combined_size_type = std::int32_t;
		union data
		{
			cartesian seperated;
			combined_size_type joined;
		} m_data;
	};

	template<typename FUNC>
	void iterate_neighbors(const coordinate& c, FUNC&& func)
	{
		coordinate::size_type min_x = std::max<coordinate::size_type>(c.X() - 1, 0);
		coordinate::size_type min_y = std::max<coordinate::size_type>(c.Y() - 1, 0);
		coordinate::size_type max_x = std::min<coordinate::size_type>(c.X() + 1, coordinate::s_dimension);
		coordinate::size_type max_y = std::min<coordinate::size_type>(c.Y() + 1, coordinate::s_dimension);

		for (coordinate::size_type y = min_y; y <= max_y; y++) {
			for (coordinate::size_type x = min_x; x <= max_x; x++) {
				coordinate neighbor(x, y);
				if (neighbor != c)
					func(neighbor);
			}
		}
	}
}