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

#include "Core/EngineCore.h"
#include "Application/Application.h"
#include "MARS.h"

/*||===================================================================*/
/*|| Forward Declarations                                                             
/*||===================================================================*/



/*||===================================================================*/
/*|| Commonly Used Headers                                                             
/*||===================================================================*/
#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Utility/Logging.h"
#include "UserInterface/ImGuiLayer.h"
