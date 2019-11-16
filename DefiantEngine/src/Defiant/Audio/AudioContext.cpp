#include <depch.h>
#include "AudioContext.h"

namespace Defiant {
	irrklang::ISoundEngine* AudioContext::engine;

	void AudioContext::Init() {
		engine = irrklang::createIrrKlangDevice();
	}
}