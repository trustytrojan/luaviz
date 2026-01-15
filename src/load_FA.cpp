#include "audioviz/fft/FrequencyAnalyzer.hpp"
#include "table.hpp"

using namespace audioviz;

namespace luaviz
{

void table::load_FA()
{
	using FA = FrequencyAnalyzer;
	// clang-format off
	new_enum("WindowFunction",
		"NONE", nullptr,
		"HANNING", FA::WindowFunction::Hanning,
		"HAMMING", FA::WindowFunction::Hamming,
		"BLACKMAN", FA::WindowFunction::Blackman
	);

	new_usertype<FA>("FrequencyAnalyzer",
		"new", sol::constructors<FA(int)>(),
		"set_fft_size", &FA::set_fft_size,
		"set_window_func", &FA::set_window_func
	);
	// clang-format on
}

} // namespace luaviz
