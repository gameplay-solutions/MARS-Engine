#pragma once

#include "Layer.h"

/*
 *	The Game Layer is overridable, however not every game will need to touch it.
 *	It handles low-level gameplay code such as spawning the default Game class
 **/
inline namespace MARS {
	inline namespace GAMEFRAMEWORK {
		class GameLayer : public Layer
		{

		};
 } }