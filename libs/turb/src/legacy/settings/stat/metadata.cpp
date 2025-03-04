// 
// Source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include "turb/legacy/settings/stat/metadata.hpp"

#include <iomanip>
#include <sstream>

namespace vortex::turb::legacy::settings::stat
{

[[nodiscard]] std::string Metadata::to_string() const
{
    auto oss = std::ostringstream{};
    oss << *this;
    return oss.str();
}

std::ostream& Metadata::stringify( std::ostream& os, int indent_size, int indent_level ) const
{
        os << std::setw( indent_size * indent_level ) << "" << "sim_method: " << to_c_str( sim_method() ) << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "particle_mode: " << to_c_str( particle_mode() ) << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "gravity_type: " << to_c_str( gravity_type() ) << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "particle_kernel_type: " << to_c_str( particle_kernel_type() ) << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "k_filter: " << k_filter() << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "C_K: " << C_K() << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "target_Phi: " << target_Phi() << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "superpart_factor: " << superpart_factor() << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "src_flow_path: " << src_flow_path() << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "src_part_path: " << src_part_path() << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "part_output_delay: " << part_output_delay() << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "is_perf_full_profile_enabled: " << ( is_perf_full_profile_enabled() ? "true" : "false" ) << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "is_perf_simple_enabled: " << ( is_perf_simple_enabled() ? "true" : "false" ) << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "is_perf_part_dist_enabled: " << ( is_perf_part_dist_enabled() ? "true" : "false" ) << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "perf_full_start: " << perf_full_start() << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "perf_full_end: " << perf_full_end() << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "part_perf_interval: " << part_perf_interval() << '\n';
    
    return os;
}

std::ostream& operator<<( std::ostream& os, Metadata const& s )
{
    return s.stringify( os, 2, 0 );
}

} // end of namespace vortex::turb::legacy::settings::stat
