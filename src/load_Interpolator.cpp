#include "audioviz/fft/Interpolator.hpp"
#include "table.hpp"

using namespace audioviz;

namespace luaviz
{

void table::load_Interpolator()
{
	using IP = Interpolator;

	// clang-format off
	new_enum("InterpolationType",
		"CSPLINE", IP::InterpolationType::CSPLINE,
		"CSPLINE_HERMITE", IP::InterpolationType::CSPLINE_HERMITE,
		"LINEAR", IP::InterpolationType::LINEAR
	);

	new_usertype<IP>("Interpolator",
		"set_interp_type", &IP::set_interp_type
	);
	// clang-format on
}

} // namespace luaviz
