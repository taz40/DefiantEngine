#pragma once
#include <string>
#include <irrKlang.h>

namespace Defiant {
	class SoundClip {
	public:
		SoundClip(const char* path);
		~SoundClip();

		void Play(bool loop = false);
		bool isPlaying();
		void Stop();

	private:
		const char* m_Path;
		irrklang::ISoundEngine* engine;
	};
}