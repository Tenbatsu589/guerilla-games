#pragma once

#include "boggle_string.h"

namespace Boggle
{
namespace Config
{
	// So we can easily do A/B testing 
#ifdef USE_STD_STRING
	using string_type = std::string;
#else
	using string_type = Boggle::string;
#endif //USE_STD_STRING
}
};