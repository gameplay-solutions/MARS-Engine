#pragma once

#include "Asset.h"

/*
 *	This is used to hold a collection of data. Such as an item in an inventory
 *
 *	- Can contain a number of data types
 *	- Can be loaded async by Entities
 *	- Is NOT instanced. Only one of these exist per-client
 *	- Game code can read/write to this DA
 *	- Can not be replicated
 **/
inline namespace
{
	class DataAsset : Asset {};
}