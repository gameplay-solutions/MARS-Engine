#pragma once

#include "Asset.h"

/*
 *	A DataTable just holds a list of DataAssets and can be searched via tags. P simple
 *	
 *	- Can contain a number of DataAssets
 *	- Can search rows via a tag
 *	- Can Read/Write from game code
 *	- Can be loaded Async
 **/

inline namespace GAMEFRAMEWORK
{
	class DataTable : public Asset {};
}