// 
// Source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include "turb/legacy/settings/stat/execution_settings_conversion.hpp"

#include <cstring>


namespace vortex::turb::legacy::settings
{

[[nodiscard]] stat::ExecutionSettings to_static( ExecutionSettings const& s, [[maybe_unused]] core::settings::StaticSettingsDataStorage& data_storage )
{
    s.validate();
    return to_static_unchecked( s, data_storage );
}

[[nodiscard]] stat::ExecutionSettings to_static_unchecked( ExecutionSettings const& s, [[maybe_unused]] core::settings::StaticSettingsDataStorage& data_storage )
{
    auto heap_data_p = data_storage.allocate( s.extra_data_size() );
    return to_static_unchecked( s, data_storage, &heap_data_p );
}

[[nodiscard]] stat::ExecutionSettings to_static_unchecked( ExecutionSettings const& s, [[maybe_unused]] core::settings::StaticSettingsDataStorage& data_storage, [[maybe_unused]] void ** data_offset_pp )
{
    auto job_name = s.job_name();
    auto job_name_data_p = static_cast< char * >( *data_offset_pp );
    auto job_name_size = job_name.size();
    if ( job_name_size == 0ull )
        job_name_data_p[ 0 ] = '\0';
    else
        std::memcpy( *data_offset_pp, job_name.data(), job_name_size + 1ull );
    *data_offset_pp = static_cast< void * >( & ( static_cast< char * >( job_name_data_p )[ job_name_size + 1ull ] ) );
    
    auto grant_no = s.grant_no();
    auto grant_no_data_p = static_cast< char * >( *data_offset_pp );
    auto grant_no_size = grant_no.size();
    if ( grant_no_size == 0ull )
        grant_no_data_p[ 0 ] = '\0';
    else
        std::memcpy( *data_offset_pp, grant_no.data(), grant_no_size + 1ull );
    *data_offset_pp = static_cast< void * >( & ( static_cast< char * >( grant_no_data_p )[ grant_no_size + 1ull ] ) );
    
    return stat::ExecutionSettings{ std::string_view{ job_name_data_p, job_name_size }, std::string_view{ grant_no_data_p, grant_no_size }, s.cpu_node_count(), s.wct_limit(), s.process_count(), s.is_node_overcommit_enabled() };
}

} // end of namespace vortex::turb::legacy::settings
