// 
// Header file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#pragma once

#include <nlohmann/json.hpp>

#include "turb/legacy/settings/enums/drag_type.hpp"

namespace vortex::turb::legacy::settings
{

NLOHMANN_JSON_SERIALIZE_ENUM( DragType,
{
    { DragType::Stokes, "stokes" },
    { DragType::Nonlinear, "nonlinear" },
})

} // end of namespace vortex::turb::legacy::settings
