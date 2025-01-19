// 
// Source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include "turb/legacy/settings/providers/json_settings_provider.hpp"

namespace vortex::turb::legacy::settings::providers
{

[[nodiscard]] Settings JsonSettingsProvider::get_settings( std::string const& key )
{
    return get<Settings>(key);
}

[[nodiscard]] Settings JsonSettingsProvider::get_settings( std::string const& key, std::ifstream& is )
{
    return get<Settings>(key, is);
}

[[nodiscard]] Settings JsonSettingsProvider::get_settings( std::string const& key, std::filestream::path const& path )
{
    return get<Settings>(key, path);
}

[[nodiscard]] Settings JsonSettingsProvider::get_settings( std::filestream::path const& path )
{
    return get<Settings>(path);
}

} // end of namespace vortex::turb::legacy::settings::providers
