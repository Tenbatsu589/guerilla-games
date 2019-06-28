#include "pch.h"
#include "board.h"

using namespace Boggle;

bool board::load(std::string_view filename)
{
	
	std::ifstream file;
	file.open(filename.data());
	if (!file.is_open()) {
		return false;
	}

	for (auto target = std::begin(m_data); target != std::end(m_data); ++target) {
		file >> *target;
		*target = static_cast<char>(std::tolower(*target));
	}
	return !file.bad();
}