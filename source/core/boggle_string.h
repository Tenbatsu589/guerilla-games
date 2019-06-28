#pragma once

namespace Boggle
{
#if defined(_DEBUG) || defined(ASSERTIONS_ENABLED)
#define ENABLE_BOGGLE_STRING_VALIDATION
#endif

// Specialized string class that does no heap allocation
class string
{
public:
	using size_type = std::uint8_t;
	static const size_type max_size = 30;
	using container = std::array<char, max_size>;
	using iterator = container::iterator;
	using const_iterator = container::const_iterator;

	string();
	string(const string&);

	template<size_t N>
	explicit string(const char(&src)[N]) 
		: m_data()
		, m_size(0)
	{
		// We can accomidate char[31];
		static_assert(N <= max_size + 1, "string too big");
		size_t src_len = std::strlen(src);
		std::copy_n(std::begin(src), src_len, begin());
		m_size = static_cast<size_type>(src_len);
		null_terminate();
		validate();
	}

	string& operator=(const string&);

#ifdef ENABLE_BOGGLE_STRING_VALIDATION
	~string() { validate(); }
#endif

	bool operator==(const string&) const;
	bool operator!=(const string&) const;
	bool operator<(const string&) const;

	template<typename ostream>
	ostream& operator << (ostream& output) const {
		for (const_iterator it = cbegin(); it != cend(); ++it)
			output << *it;
		return output;
	}

	void push_back(char c);
	void pop_back();

	iterator begin() { return m_data.begin(); }
	iterator end() { return begin() + m_size; }
	const_iterator cbegin() const { return m_data.cbegin(); }
	const_iterator cend() const { return cbegin() + m_size; }
	size_type size() const { return m_size; }

	size_t hash() const {
		const int* ptr = reinterpret_cast<const int*>(&m_data[0]);
		int value = *ptr;
		return std::hash<int>()(value);
	}
private:
	void null_terminate();
#ifdef ENABLE_BOGGLE_STRING_VALIDATION
	static const std::uint32_t s_header_magic = 0xfeedbabe;
	const std::uint32_t m_header = s_header_magic;
#endif
	std::array<char, max_size> m_data;
	size_type m_size = 0;
#ifdef ENABLE_BOGGLE_STRING_VALIDATION
	static const std::uint32_t m_footer_magic = 0xdeadbeef;
	const std::uint32_t m_footer = m_footer_magic;
	
#endif
	inline void validate() {
#ifdef ENABLE_BOGGLE_STRING_VALIDATION
		assert(m_header == s_header_magic);
		assert(m_footer == m_footer_magic);
#endif
	}
};

struct string_hash
{
	size_t operator()(const string& str) const {
		return str.hash();
	}
};
}

template<typename ostream>
ostream& operator <<(ostream& output, const Boggle::string& str) {
	return str.operator<<(output);
}