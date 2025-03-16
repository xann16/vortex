// 
// Source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include "turb/legacy/settings/stat/metadata_conversion.hpp"

#include <cstring>


namespace vortex::turb::legacy::settings
{

[[nodiscard]] stat::Metadata to_static( Metadata const& s, [[maybe_unused]] core::settings::StaticSettingsDataStorage& data_storage )
{
    s.validate();
    return to_static_unchecked( s, data_storage );
}

[[nodiscard]] stat::Metadata to_static_unchecked( Metadata const& s, [[maybe_unused]] core::settings::StaticSettingsDataStorage& data_storage )
{
    auto heap_data_p = data_storage.allocate( s.extra_data_size() );
    return to_static_unchecked( s, data_storage, &heap_data_p );
}

[[nodiscard]] stat::Metadata to_static_unchecked( Metadata const& s, [[maybe_unused]] core::settings::StaticSettingsDataStorage& data_storage, [[maybe_unused]] void ** data_offset_pp )
{
    auto src_flow_path = s.src_flow_path();
    auto src_flow_path_data_p = static_cast< char * >( *data_offset_pp );
    auto src_flow_path_size = src_flow_path.size();
    if ( src_flow_path_size == 0ull )
        src_flow_path_data_p[ 0 ] = '\0';
    else
        std::memcpy( *data_offset_pp, src_flow_path.data(), src_flow_path_size + 1ull );
    *data_offset_pp = static_cast< void * >( & ( static_cast< char * >( src_flow_path_data_p )[ src_flow_path_size + 1ull ] ) );
    
    auto src_part_path = s.src_part_path();
    auto src_part_path_data_p = static_cast< char * >( *data_offset_pp );
    auto src_part_path_size = src_part_path.size();
    if ( src_part_path_size == 0ull )
        src_part_path_data_p[ 0 ] = '\0';
    else
        std::memcpy( *data_offset_pp, src_part_path.data(), src_part_path_size + 1ull );
    *data_offset_pp = static_cast< void * >( & ( static_cast< char * >( src_part_path_data_p )[ src_part_path_size + 1ull ] ) );
    
    return stat::Metadata{ s.sim_method(), s.particle_mode(), s.gravity_type(), s.particle_kernel_type(), s.k_filter(), s.C_K(), s.target_Phi(), s.superpart_factor(), std::string_view{ src_flow_path_data_p, src_flow_path_size }, std::string_view{ src_part_path_data_p, src_part_path_size }, s.part_output_delay(), s.is_perf_full_profile_enabled(), s.is_perf_simple_enabled(), s.is_perf_part_dist_enabled(), s.perf_full_start(), s.perf_full_end(), s.part_perf_interval() };
}

} // end of namespace vortex::turb::legacy::settings
