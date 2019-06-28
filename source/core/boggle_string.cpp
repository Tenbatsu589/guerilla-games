#include "pch.h"
#include "boggle_string.h"

using namespace Boggle;

string::string()
	: m_data()
	, m_size(0)
{
	validate();
}

string::string(const string& src)
	: m_data(src.m_data)
	, m_size(src.m_size)
{
	null_terminate();
	validate();
}

string& string::operator=(const string& src)
{
	std::copy_n(src.cbegin(), src.m_size, m_data.begin());
	m_size = src.m_size;
	null_terminate();
	validate();
	return *this;
}

bool string::operator==(const string& src) const
{
	if (m_size != src.m_size)
		return false;
	return std::equal(cbegin(), cend(), src.cbegin());
}

bool string::operator!=(const string& src) const
{
	return !((*this) == src);
}

bool string::operator<(const string& src) const
{
	return std::lexicographical_compare(cbegin(), cend(), src.cbegin(), src.cend());
}

void string::push_back(char c)
{
	assert(m_size < max_size);
	*(end()) = c;
	m_size++;
	validate();
}

void string::pop_back()
{
	*(end() - 1) = 0;
	m_size--;
	validate();
}

void string::null_terminate()
{
	if (m_size != max_size)
		*(end()) = 0;
}

