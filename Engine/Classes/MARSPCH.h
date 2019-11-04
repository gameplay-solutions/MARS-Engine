#pragma once

#ifndef USE_STL
#define USE_STL
#endif
#ifndef USE_GAMEFRAMEWORK
#define USE_GAMEFRAMEWORK
#endif

/*
 *	STL includes. TEMP
 **/
 #ifdef USE_STL
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iomanip>
#include <stdio.h>
#endif
// ^^^^^^
// eventually we need to implement our custom data types so we can stop including the STL everywhere

/**
 * MARS Data Types and Containers
 */
#include "Types/String.hpp"
#include "Types/Array.hpp"
#include "Types/CoreTypes.hpp"
#include "Types/Stack.hpp"
#include "Types/Map.hpp"
#include "Types/Pair.hpp"
#include "Types/SmartPointer.hpp"

/*
 *	Core MARS Classes
 **/
#include "Core/Asserts.h"
#include "Core/Events/Event.h"
#include "fmt/format.h"
#include "Utility/Logging.h"
#include "Math/CoreMath.hpp" // @HACK
/*
 *	MARS Math Lib
 **/
#ifdef USE_MARS_MATH

#include "Math/Quat.hpp"
#include "Math/Rotator.hpp"
#include "Math/Transform.hpp"
#include "Math/Vector.h"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#else
#pragma warning(push)
#pragma warning(disable:4201)
#include "glm/glm.hpp"
#pragma warning(pop)
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/vector_relational.hpp"
#include "glm/matrix.hpp"
#include "glm/mat2x2.hpp"
#include "glm/mat2x3.hpp"
#include "glm/mat2x4.hpp"
#include "glm/mat3x2.hpp"
#include "glm/mat3x3.hpp"
#include "glm/mat3x4.hpp"
#include "glm/mat4x2.hpp"
#include "glm/mat4x3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/integer.hpp"
#include "glm/gtc/matrix_transform.hpp"
#endif

/*
 *	MARS GameFramework
 **/
#ifdef USE_GAMEFRAMEWORK
#include "GameFramework/Game.h"
#include "GameFramework/Core/Asset.h"
#include "GameFramework/Core/Entity.h"
#include "GameFramework/Core/Actor.h"
#include "GameFramework/Core/Info.h"
#include "GameFramework/Core/GameState.h"
#include "GameFramework/Core/DataAsset.hpp"
#include "GameFramework/Core/DataTable.hpp"
#include "GameFramework/Player/Controller.h"
#include "GameFramework/Player/Pawn.h"
#include "GameFramework/Sound/Sound.h"
#include "GameFramework/Sound/SoundCue.h"
#include "GameFramework/Sound/SoundComponent.h"
#include "GameFramework/World/World.h"
#include "GameFramework/World/Level.h"
#endif