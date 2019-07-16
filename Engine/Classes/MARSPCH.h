#pragma once

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

#include "Types/String.hpp"
#include "Types/Array.hpp"
#include "Types/CoreTypes.h"
#include "Core/Asserts.h"
#include "fmt/format.h"
#include "Core/Events/Event.h"

// I don't like this circle include
#include "Utility/Logging.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include "glm/glm.hpp"
#pragma warning(pop)