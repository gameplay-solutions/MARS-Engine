#pragma once
#include "..\Core\Entity.h"

/*
 *	A level is the visual representation of a Map. 
 *	It contains all of the art, lights, and post-process you'd expect.
 *	Multiple levels can exist in a single world, allowing for streaming.
 *	
 *	- Can be rendered
 *	- Can be spawned
 *	- Owned by the World
 *	- Can be loaded/streamed by an Actor and the World
 *	- The collision for a level is always loaded and handled by the server even if it's not being rendered
 *	- Loading/streaming is client side
 **/
inline namespace GAMEFRAMEWORK
{
	class Level : Entity {};
}