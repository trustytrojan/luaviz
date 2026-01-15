#include "audioviz/ParticleSystem.hpp"
#include <table.hpp>

using namespace audioviz;

namespace luaviz
{

void table::load_particle_systems()
{
	using CPS = ParticleSystem<sf::CircleShape>;
	using UO = CPS::UpdateOptions;

	// clang-format off
	new_usertype<UO>("ParticleSystemUpdateOptions",
		"calm_factor", sol::property(&UO::calm_factor),
		"multiplier", sol::property(&UO::multiplier),
		"displacement_func", sol::property(&UO::displacement_func),
		"weight_func", sol::property(&UO::weight_func)
	);

	new_usertype<CPS>("CircleParticleSystem",
		sol::base_classes, sol::bases<sf::Drawable>(),
		"new", sol::factories([](const sol::table &rect, const int particle_count, int framerate)
		{
			return CPS(table_to_intrect(rect), particle_count, framerate);
		}),
		"set_rect", &CPS::set_rect,
		"set_particle_count", &CPS::set_particle_count,
		"update", sol::overload(
			static_cast<void(CPS::*)(AudioAnalyzer &, const CPS::UpdateOptions &)>(&CPS::update),
			static_cast<void(CPS::*)(MultiChannelAudioAnalyzer &, const CPS::UpdateOptions &)>(&CPS::update),
			[](CPS &self, MultiChannelAudioAnalyzer &ma) { self.update(ma); },
			[](CPS &self, AudioAnalyzer &aa) { self.update(aa); }
		),
		"set_particle_textures", &CPS::set_particle_textures,
		"set_debug_rect", &CPS::set_debug_rect,
		"set_color", sol::overload(
			&CPS::set_color,
			[](CPS &self, const sol::table &color) { self.set_color(table_to_color(color)); }
		)
	);
	// clang-format on
}

} // namespace luaviz
