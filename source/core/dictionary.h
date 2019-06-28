
#pragma once

// Dictionary:
//  The dictionary file is an ASCII text file that lists acceptable words.  Each word is
//  new line separated.  Words are in alphabetical order and all lowercase, utilizing
//  only letters 'a' to 'z'.

namespace Boggle 
{
	class dictionary
	{
	public:
		dictionary();
		dictionary(const dictionary& src) = delete;
		dictionary(dictionary&&) = default;
		dictionary& operator=(const dictionary&) = delete;
		dictionary& operator=(dictionary&&) = default;

		bool load(std::string_view filename);
		bool contains(const Boggle::string& word) const;
	private:
		using container = std::unordered_set<Boggle::Config::string_type, Boggle::string_hash>;
		container m_words;
	};
}