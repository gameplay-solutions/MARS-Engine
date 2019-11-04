#pragma once

#include "Actor.h"

/*
 *	A Info is an actor that can't be rendered. That's pretty much it.
 *	This is used for data only types of classes such as state managers.
 *	
 *	The only real difference between Info's and Entities is the fact Info inherits
 *	from Actor, so it can be replicated.
 **/

inline namespace GAMEFRAMEWORK
{
	class Info : public Actor {};
}