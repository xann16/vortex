// 
// Header file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#pragma once

#include <string_view>
#include <span>

#include "core/common/types.hpp"
#include "core/settings/static_settings_data_storage.hpp"
#include "turb/legacy/settings/parameters.hpp"
#include "turb/legacy/settings/stat/parameters.hpp"
#include "turb/legacy/settings/enums/forcing_type.hpp"
#include "turb/legacy/settings/enums/drag_type.hpp"

namespace vortex::turb::legacy::settings
{

[[nodiscard]] stat::Parameters to_static( Parameters const& s, [[maybe_unused]] core::settings::StaticSettingsDataStorage& data_storage );
[[nodiscard]] stat::Parameters to_static( Parameters const& s, [[maybe_unused]] core::settings::StaticSettingsDataStorage& data_storage, [[maybe_unused]] void ** data_offset_pp );

} // end of namespace vortex::turb::legacy::settings
