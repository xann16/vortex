// 
// Header file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#pragma once

#include <nlohmann/json.hpp>

#include "turb/legacy/settings/enums/gravity_mode.hpp"

namespace vortex::turb::legacy::settings
{

NLOHMANN_JSON_SERIALIZE_ENUM( GravityMode,
{
    { GravityMode::None, "none" },
    { GravityMode::Vertical, "vertical" },
    { GravityMode::Horizontal, "horizontal" },
})

} // end of namespace vortex::turb::legacy::settings
