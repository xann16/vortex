// 
// Source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include "turb/legacy/settings/metadata.hpp"

#include <iomanip>
#include <sstream>

#include <nlohmann/json.hpp>

#include "turb/legacy/settings/enums/sim_method_json_integration.hpp"
#include "turb/legacy/settings/enums/particle_mode_json_integration.hpp"
#include "turb/legacy/settings/enums/gravity_mode_json_integration.hpp"
#include "turb/legacy/settings/enums/particle_twc_kernel_type_json_integration.hpp"

namespace vortex::turb::legacy::settings
{

Metadata::Metadata( nlohmann::json * data_p )
:   m_data_p( data_p )
{
    // add initial validation
}

Metadata& Metadata::merge( nlohmann::json * other_data_p )
{
    if (!is_empty() && other_data_p != nullptr)
    {
        data()->merge_patch( *other_data_p );
    }
    return *this;
}

[[nodiscard]] std::string Metadata::to_string() const
{
    auto oss = std::ostringstream{};
    oss << *this;
    return oss.str();
}

std::ostream& Metadata::stringify( std::ostream& os, int indent_size, int indent_level, bool display_all ) const
{
    if ( !display_all && ( is_empty() || data()->empty() ) )
    {
        os << "<empty>\n"; 
        return os;
    }
    
    if ( display_all || has_sim_method_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "sim_method: " << to_c_str( sim_method() ) << '\n';
    }
    if ( display_all || has_particle_mode_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "particle_mode: " << to_c_str( particle_mode() ) << '\n';
    }
    if ( display_all || has_gravity_type_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "gravity_type: " << to_c_str( gravity_type() ) << '\n';
    }
    if ( display_all || has_particle_kernel_type_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "particle_kernel_type: " << to_c_str( particle_kernel_type() ) << '\n';
    }
    if ( display_all || has_k_filter_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "k_filter: " << k_filter() << '\n';
    }
    if ( display_all || has_C_K_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "C_K: " << C_K() << '\n';
    }
    if ( display_all || has_target_Phi_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "target_Phi: " << target_Phi() << '\n';
    }
    if ( display_all || has_superpart_factor_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "superpart_factor: " << superpart_factor() << '\n';
    }
    if ( display_all || has_src_flow_path_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "src_flow_path: " << src_flow_path() << '\n';
    }
    if ( display_all || has_src_part_path_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "src_part_path: " << src_part_path() << '\n';
    }
    if ( display_all || has_part_output_delay_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "part_output_delay: " << part_output_delay() << '\n';
    }
    if ( display_all || has_is_perf_full_profile_enabled_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "is_perf_full_profile_enabled: " << ( is_perf_full_profile_enabled() ? "true" : "false" ) << '\n';
    }
    if ( display_all || has_is_perf_simple_enabled_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "is_perf_simple_enabled: " << ( is_perf_simple_enabled() ? "true" : "false" ) << '\n';
    }
    if ( display_all || has_is_perf_part_dist_enabled_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "is_perf_part_dist_enabled: " << ( is_perf_part_dist_enabled() ? "true" : "false" ) << '\n';
    }
    if ( display_all || has_perf_full_start_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "perf_full_start: " << perf_full_start() << '\n';
    }
    if ( display_all || has_perf_full_end_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "perf_full_end: " << perf_full_end() << '\n';
    }
    if ( display_all || has_part_perf_interval_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "part_perf_interval: " << part_perf_interval() << '\n';
    }
    
    return os;
}

std::ostream& operator<<( std::ostream& os, Metadata const& s )
{
    return s.stringify( os, 2, 0, os.flags() & std::ios_base::boolalpha );
}

// "sim_method" property

[[nodiscard]] SimMethod Metadata::sim_method() const
{
    if ( is_empty() ) return default_sim_method();
    auto it = m_data_p->find( "sim_method" );
    if ( it == m_data_p->end() || it->is_null() ) return default_sim_method();
    return it->template get<SimMethod>();
}

[[nodiscard]] bool Metadata::has_sim_method_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "sim_method" );
    return it != m_data_p->end() && !it->is_null();
}

// "particle_mode" property

[[nodiscard]] ParticleMode Metadata::particle_mode() const
{
    if ( is_empty() ) return default_particle_mode();
    auto it = m_data_p->find( "particle_mode" );
    if ( it == m_data_p->end() || it->is_null() ) return default_particle_mode();
    return it->template get<ParticleMode>();
}

[[nodiscard]] bool Metadata::has_particle_mode_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "particle_mode" );
    return it != m_data_p->end() && !it->is_null();
}

// "gravity_type" property

[[nodiscard]] GravityMode Metadata::gravity_type() const
{
    if ( is_empty() ) return default_gravity_type();
    auto it = m_data_p->find( "gravity_type" );
    if ( it == m_data_p->end() || it->is_null() ) return default_gravity_type();
    return it->template get<GravityMode>();
}

[[nodiscard]] bool Metadata::has_gravity_type_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "gravity_type" );
    return it != m_data_p->end() && !it->is_null();
}

// "particle_kernel_type" property

[[nodiscard]] ParticleTwcKernelType Metadata::particle_kernel_type() const
{
    if ( is_empty() ) return default_particle_kernel_type();
    auto it = m_data_p->find( "particle_kernel_type" );
    if ( it == m_data_p->end() || it->is_null() ) return default_particle_kernel_type();
    return it->template get<ParticleTwcKernelType>();
}

[[nodiscard]] bool Metadata::has_particle_kernel_type_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "particle_kernel_type" );
    return it != m_data_p->end() && !it->is_null();
}

// "k_filter" property

[[nodiscard]] i32 Metadata::k_filter() const
{
    if ( is_empty() ) return default_k_filter();
    auto it = m_data_p->find( "k_filter" );
    if ( it == m_data_p->end() || it->is_null() ) return default_k_filter();
    return it->template get<i32>();
}

[[nodiscard]] bool Metadata::has_k_filter_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "k_filter" );
    return it != m_data_p->end() && !it->is_null();
}

// "C_K" property

[[nodiscard]] real Metadata::C_K() const
{
    if ( is_empty() ) return default_C_K();
    auto it = m_data_p->find( "C_K" );
    if ( it == m_data_p->end() || it->is_null() ) return default_C_K();
    return it->template get<real>();
}

[[nodiscard]] bool Metadata::has_C_K_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "C_K" );
    return it != m_data_p->end() && !it->is_null();
}

// "target_Phi" property

[[nodiscard]] real Metadata::target_Phi() const
{
    if ( is_empty() ) return default_target_Phi();
    auto it = m_data_p->find( "target_Phi" );
    if ( it == m_data_p->end() || it->is_null() ) return default_target_Phi();
    return it->template get<real>();
}

[[nodiscard]] bool Metadata::has_target_Phi_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "target_Phi" );
    return it != m_data_p->end() && !it->is_null();
}

// "superpart_factor" property

[[nodiscard]] real Metadata::superpart_factor() const
{
    if ( is_empty() ) return default_superpart_factor();
    auto it = m_data_p->find( "superpart_factor" );
    if ( it == m_data_p->end() || it->is_null() ) return default_superpart_factor();
    return it->template get<real>();
}

[[nodiscard]] bool Metadata::has_superpart_factor_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "superpart_factor" );
    return it != m_data_p->end() && !it->is_null();
}

// "src_flow_path" property

[[nodiscard]] std::string_view Metadata::src_flow_path() const
{
    if ( is_empty() ) return default_src_flow_path();
    auto it = m_data_p->find( "src_flow_path" );
    if ( it == m_data_p->end() || it->is_null() ) return default_src_flow_path();
    return std::string_view{ it->template get_ref<std::string const&>() };
}

[[nodiscard]] bool Metadata::has_src_flow_path_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "src_flow_path" );
    return it != m_data_p->end() && !it->is_null();
}

// "src_part_path" property

[[nodiscard]] std::string_view Metadata::src_part_path() const
{
    if ( is_empty() ) return default_src_part_path();
    auto it = m_data_p->find( "src_part_path" );
    if ( it == m_data_p->end() || it->is_null() ) return default_src_part_path();
    return std::string_view{ it->template get_ref<std::string const&>() };
}

[[nodiscard]] bool Metadata::has_src_part_path_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "src_part_path" );
    return it != m_data_p->end() && !it->is_null();
}

// "part_output_delay" property

[[nodiscard]] i32 Metadata::part_output_delay() const
{
    if ( is_empty() ) return default_part_output_delay();
    auto it = m_data_p->find( "part_output_delay" );
    if ( it == m_data_p->end() || it->is_null() ) return default_part_output_delay();
    return it->template get<i32>();
}

[[nodiscard]] bool Metadata::has_part_output_delay_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "part_output_delay" );
    return it != m_data_p->end() && !it->is_null();
}

// "is_perf_full_profile_enabled" property

[[nodiscard]] bool Metadata::is_perf_full_profile_enabled() const
{
    if ( is_empty() ) return default_is_perf_full_profile_enabled();
    auto it = m_data_p->find( "is_perf_full_profile_enabled" );
    if ( it == m_data_p->end() || it->is_null() ) return default_is_perf_full_profile_enabled();
    return it->template get<bool>();
}

[[nodiscard]] bool Metadata::has_is_perf_full_profile_enabled_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "is_perf_full_profile_enabled" );
    return it != m_data_p->end() && !it->is_null();
}

// "is_perf_simple_enabled" property

[[nodiscard]] bool Metadata::is_perf_simple_enabled() const
{
    if ( is_empty() ) return default_is_perf_simple_enabled();
    auto it = m_data_p->find( "is_perf_simple_enabled" );
    if ( it == m_data_p->end() || it->is_null() ) return default_is_perf_simple_enabled();
    return it->template get<bool>();
}

[[nodiscard]] bool Metadata::has_is_perf_simple_enabled_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "is_perf_simple_enabled" );
    return it != m_data_p->end() && !it->is_null();
}

// "is_perf_part_dist_enabled" property

[[nodiscard]] bool Metadata::is_perf_part_dist_enabled() const
{
    if ( is_empty() ) return default_is_perf_part_dist_enabled();
    auto it = m_data_p->find( "is_perf_part_dist_enabled" );
    if ( it == m_data_p->end() || it->is_null() ) return default_is_perf_part_dist_enabled();
    return it->template get<bool>();
}

[[nodiscard]] bool Metadata::has_is_perf_part_dist_enabled_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "is_perf_part_dist_enabled" );
    return it != m_data_p->end() && !it->is_null();
}

// "perf_full_start" property

[[nodiscard]] i32 Metadata::perf_full_start() const
{
    if ( is_empty() ) return default_perf_full_start();
    auto it = m_data_p->find( "perf_full_start" );
    if ( it == m_data_p->end() || it->is_null() ) return default_perf_full_start();
    return it->template get<i32>();
}

[[nodiscard]] bool Metadata::has_perf_full_start_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "perf_full_start" );
    return it != m_data_p->end() && !it->is_null();
}

// "perf_full_end" property

[[nodiscard]] i32 Metadata::perf_full_end() const
{
    if ( is_empty() ) return default_perf_full_end();
    auto it = m_data_p->find( "perf_full_end" );
    if ( it == m_data_p->end() || it->is_null() ) return default_perf_full_end();
    return it->template get<i32>();
}

[[nodiscard]] bool Metadata::has_perf_full_end_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "perf_full_end" );
    return it != m_data_p->end() && !it->is_null();
}

// "part_perf_interval" property

[[nodiscard]] i32 Metadata::part_perf_interval() const
{
    if ( is_empty() ) return default_part_perf_interval();
    auto it = m_data_p->find( "part_perf_interval" );
    if ( it == m_data_p->end() || it->is_null() ) return default_part_perf_interval();
    return it->template get<i32>();
}

[[nodiscard]] bool Metadata::has_part_perf_interval_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "part_perf_interval" );
    return it != m_data_p->end() && !it->is_null();
}


} // end of namespace vortex::turb::legacy::settings
