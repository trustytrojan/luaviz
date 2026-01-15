#include "table.hpp"
#include <audioviz/fft/AudioAnalyzer.hpp>
#include <audioviz/fft/StereoAnalyzer.hpp>

using namespace audioviz;

namespace luaviz
{

void table::load_AA_SA()
{
	using AA = AudioAnalyzer;
	using MA = MultiChannelAudioAnalyzer;
	using SA = StereoAnalyzer;

	// clang-format off
	new_usertype<AA>("AudioAnalyzer",
		"new", sol::constructors<AA(int, int)>(),
		"compute_amplitudes", [](AA &self, FrequencyAnalyzer &fa) { self.compute_amplitudes(fa); }
	);

	new_usertype<MA>("MultiChannelAudioAnalyzer",
		"new", sol::constructors<MA(int, int, int)>()
	);

	new_usertype<SA>("StereoAnalyzer",
		sol::base_classes, sol::bases<MA>(),
		"new", sol::constructors<SA(int, int)>(),
		// explicit return type required otherwise sol makes a copy!
		"left", [](SA &s) -> AA & { return s.left(); },
		"right", [](SA &s) -> AA & { return s.right(); }
	);
	// clang-format on
}

} // namespace luaviz
