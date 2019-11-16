#pragma once

#include <irrKlang.h>

namespace Defiant {
	class AudioContext {
	public:
		static void Init();

		static irrklang::ISoundEngine* engine;
	};
}