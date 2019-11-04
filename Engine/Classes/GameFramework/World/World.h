#pragma once
#include "..\Core\Asset.h"

/*
 *	The world maintains all of the levels in a single map.
 *	
 *	- Contains a list of levels to load
 *	- Is not owned
 *	- Can not be rendered
 *	- Can not be spawned
 **/

inline namespace GAMEFRAMEWORK
{
	class World : Asset {};
}