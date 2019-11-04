#pragma once

/*
 *	The Asset class is the lowest level class in the GameFramework.
 *	Everything inherits from this class because this class handles seralization
 *	Editor loading, saving, and creation.
 *	This class will also contain low-level reflected data provided by MHT.
 *	Things such as Super::, and NewObject<> are provided by this class
 **/

inline namespace GAMEFRAMEWORK
{
	class Asset {};
}