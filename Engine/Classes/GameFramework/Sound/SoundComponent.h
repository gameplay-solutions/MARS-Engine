#pragma once

#include "..\Core\Asset.h"

/*
 *	Can stop, play, scrub, and clear sound buffers
 *
 *	- An Asset that contains a list of sounds
 *	- Can be used by a actor to control sounds
 **/
inline namespace GAMEFRAMEWORK
{
	class SoundComponent : public Asset {};
}