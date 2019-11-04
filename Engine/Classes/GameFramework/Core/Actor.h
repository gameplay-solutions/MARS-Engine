#pragma once

#include "Entity.h"

/*
 *	Actors are what will make up most of the game world.
 *	An Actor can be anything from a tree that explodes when a rock is thrown at it
 *	to a chest that can drop loot.
 *	
 *	Actors are the ONLY class in the framework capable of replicating! If you need
 *	network features, you must have Actor in your class inheritance tree
 *	
 *	- Actors can be rendered as they contain a renderable mesh object by default. (If you don't need it to render, use an Entity or a Info if you need networking)
 *	- Can respond to the physics engine and receive trace channels
 *	- Can own and spawn other Actors
 *	- Can be attached to other Actors
 *	- Can Replicate
 **/

inline namespace GAMEFRAMEWORK
{
	class Actor : public Entity { };
}