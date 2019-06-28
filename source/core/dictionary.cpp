#include "pch.h"
#include "dictionary.h"

using namespace Boggle;
using string_type = Config::string_type;

dictionary::dictionary() 
	: m_words(4096)
{

}

bool dictionary::load(std::string_view filename)
{
	std::ifstream file;
	file.open(filename.data());
	if (!file.is_open()) {
		return false;
	} 

	while (!file.eof() && !file.bad()) {
		char buffer[17];
		file.getline(buffer, 17);
		m_words.insert(string_type(buffer));
	}
	return !file.bad();
}

bool dictionary::contains(const Boggle::string& word) const
{
	return m_words.count(word) != 0;
}