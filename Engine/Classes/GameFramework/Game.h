#pragma once

#include "Core\Info.h"

/*
 *	The game is a must override class for any game. It controls how the game is actually played.
 *	
 *	- A base class every game should override
 *	- Only spawns on the server
 *	- Contains rules for how the game should be played. Ex.: Lives, respawns, teams etc
 *	- Spawns the player controllers and handles player login
 **/

inline namespace GAMEFRAMEWORK
{
	class Game : Info {};
}