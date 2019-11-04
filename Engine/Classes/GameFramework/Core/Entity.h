#pragma once

#include "Asset.h"

/*
 *	The Entity is the Class that comes directly after Asset.
 *	Most Gameplay Class and overrides will come from this Class
 *	
 *	- Entities can exist in the game world
 *	- They can NOT be rendered
 *	- They can only be owned by the client that spawned them.
 *	- An Entity can spawn another Entity in the game world
 *	- They can not be replicated
 **/

inline namespace GAMEFRAMEWORK
{
	class Entity : public Asset {};
}