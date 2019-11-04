#pragma once

/**
 * Not for engine use.
 * This header is here to act as a single monolithic include for
 * all games or applications developed with MARS.
 * This include will cover the basics of all that MARS has to offer to a game project
 * without allowing access to core engine systems that shouldn't be accessed outside
 * of the engine's own Application.
 **/

/*||===================================================================*/
/*|| Low-Level Includes                                                             
/*||===================================================================*/

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

#include "Core/EngineCore.h"
#include "Application/Application.h"
#include "Core/Asserts.h"
#include "Core/Events/Event.h"
#include "MARS.h"

#include "Types/CoreTypes.hpp"
#include "Types/Array.hpp"
#include "Types/Map.hpp"
#include "Types/Pair.hpp"
#include "Types/SmartPointer.hpp"
#include "Types/Stack.hpp"
#include "Types/String.hpp"

// #include "Math/CoreMath.hpp"
// #include "Math/Quat.hpp"
// #include "Math/Rotator.hpp"
// #include "Math/Transform.hpp"
// #include "Math/Vector.h"
// #include "Math/Vector2.hpp"
// #include "Math/Vector3.hpp

/*||===================================================================*/
/*|| Commonly Used Headers                                                             
/*||===================================================================*/
#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Layers/Layer.h"
#include "Core/Layers/GameLayer.h"
#include "Input/Keys.h"
#include "Utility/Logging.h"
#include "Utility/Tick.h"

// @TODO(Chrisr): This include needs to be platform based. Probably a MHT thing
#include "Platform/Windows/Windows_Input.h"

