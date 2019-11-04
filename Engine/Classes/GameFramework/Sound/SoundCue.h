#pragma once
#include "..\Core\Asset.h"

/*
 *	- Contains a reference to a single sound file on disk.
 *	- Can keep the file loaded to avoid lag spikes and multiple loads
 **/
inline namespace GAMEFRAMEWORK
{
	class SoundCue : Asset {};
}