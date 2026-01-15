#pragma once

#include <audioviz/Base.hpp>
#include <audioviz/fft/FrequencyAnalyzer.hpp>
#include <audioviz/fft/MultiChannelAudioAnalyzer.hpp>

#define capture_time(label, code)            \
	if (timing_text_enabled())               \
	{                                        \
		sf::Clock _clock;                    \
		code;                                \
		capture_elapsed_time(label, _clock); \
	}                                        \
	else                                     \
		code;

namespace luaviz
{

struct Base : public audioviz::Base
{
	audioviz::Media &media;
	const int num_channels{media.audio_channels()};

	void perform_fft(audioviz::FrequencyAnalyzer &fa, audioviz::MultiChannelAudioAnalyzer &ma)
	{
		capture_time("fft", ma.execute_fft(fa, media.audio_buffer().first(fa.get_fft_size() * num_channels)));
	}

	Base(const sf::Vector2u size, audioviz::Media &media)
		: audioviz::Base{size},
		  media{media}
	{
	}
};

} // namespace luaviz
