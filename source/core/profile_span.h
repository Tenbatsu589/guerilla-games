#pragma once

namespace Boggle
{
	template<typename output>
	class profile_span
	{
	public:
		profile_span(const char* const name);
		~profile_span();
		using clock = std::chrono::high_resolution_clock;
	private:
		const char* const m_name;
		clock::time_point m_start = clock::now();
		output m_output;
	};

	template<typename output>
	profile_span<output>::profile_span(const char* const name)
		: m_name(name)
	{

	}

	template<typename output>
	profile_span<output>::~profile_span()
	{
		m_output(m_name, clock::now() - m_start);
	}

	struct to_console
	{
		template<typename duration>
		void operator()(const char* const name, duration d) const {
			std::cout << name << ":" << std::chrono::duration_cast<std::chrono::milliseconds>(d).count() << " ms \n";
		}
	};

	using console_profile_span = profile_span< to_console >;
}