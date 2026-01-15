#include "audioviz/fft/BinPacker.hpp"
#include "table.hpp"

using namespace audioviz;

namespace luaviz
{

void table::load_BinPacker()
{
	using BP = BinPacker;

	// clang-format off
	new_enum("FrequencyScale",
		"LINEAR", BP::Scale::LINEAR,
		"LOG", BP::Scale::LOG,
		"NTH_ROOT", BP::Scale::NTH_ROOT
	);

	new_enum("AccumulationMethod",
		"SUM", BP::AccumulationMethod::SUM,
		"MAX", BP::AccumulationMethod::MAX
	);

	new_usertype<BP>("BinPacker",
		"set_accum_method", &BP::set_accum_method,
		"set_scale", &BP::set_scale,
		"set_nth_root", &BP::set_nth_root
	);
	// clang-format on
}

} // namespace luaviz
