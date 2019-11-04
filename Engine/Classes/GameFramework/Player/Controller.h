#pragma once

#include "..\Core\Actor.h"

/*
 *	A Controller is given to each client that joins the game. 
 *	It is used to handle input and give the game code a place to store
 *	player specific data and information. Such as inventories etc.
 *	
 *	- Can control a single Pawn
 *	- Is Owned by the client
 *	- Holds onto player data even if the pawn is destroyed
 *	- Handles Input
 *	- Can supply the Pawn with input callbacks
 **/
inline namespace GAMEFRAMEWORK
{
	class Controller : public Actor {};
}