//------------------------------------------------------------------------------
// Name of this file : variables.h
// Author : Jean Anquetil
// Date : 08/01/2025
//------------------------------------------------------------------------------

#include <iostream>
#include <map>
#include <memory>
#include <string>

//------------------------------------------------------------------------------

namespace globals{

extern std::map<std::string, int> entitiesCor;

namespace graphic {

extern std::map<std::string, int> pipelinesCor;
extern std::map<std::string, int> frameBuffersCor;

}; // namespace graphic
}; // namespace globals

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------