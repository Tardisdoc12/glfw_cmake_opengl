//------------------------------------------------------------------------------
// Name of this file : variables.cpp
// Author : Jean Anquetil
// Date : 08/01/2025
//------------------------------------------------------------------------------

#include "../../file_h/globals/variables.h"

//------------------------------------------------------------------------------
namespace globals {

std::map<std::string, int> entitiesCor;
int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 800;

namespace graphic {

std::map<std::string, int> pipelinesCor;
std::map<std::string, int> frameBuffersCor;

} // namespace graphic
} // namespace globals
//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------