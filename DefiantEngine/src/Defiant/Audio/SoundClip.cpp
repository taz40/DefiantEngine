#include <depch.h>
#include "SoundClip.h"

namespace Defiant {
	SoundClip::SoundClip(const char* path) 
		:m_Path(path) {
		engine = irrklang::createIrrKlangDevice();
	}

	SoundClip::~SoundClip() {
		
	}

	void SoundClip::Play(bool loop) {
		engine->play2D(m_Path, loop);
	}

	bool SoundClip::isPlaying() {
		return engine->isCurrentlyPlaying(m_Path);
	}

	void SoundClip::Stop() {
		engine->stopAllSounds();
	}
}