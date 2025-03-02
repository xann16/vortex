// 
// Source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include "turb/legacy/settings/stat/parameters.hpp"

#include <iomanip>
#include <sstream>

namespace vortex::turb::legacy::settings::stat
{

[[nodiscard]] std::string Parameters::to_string() const
{
    auto oss = std::ostringstream{};
    oss << *this;
    return oss.str();
}

std::ostream& Parameters::stringify( std::ostream& os, int indent_size, int indent_level ) const
{
        os << std::setw( indent_size * indent_level ) << "" << "N: " << N << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "N_subdomain: " << N_subdomain << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "Nt_max: " << Nt_max << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "dt: " << dt << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "rnu: " << rnu << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "t_init: " << t_init << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "is_flow_generated: " << ( is_flow_generated ? "true" : "false" ) << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "deterministic_seed: " << deterministic_seed << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "input_velo_index: " << input_velo_index << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "forcing_type: " << to_c_str( forcing_type ) << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "deterministic_forcing_k_1: " << deterministic_forcing_k_1 << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "deterministic_forcing_k_2: " << deterministic_forcing_k_2 << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "stochastic_seed: " << stochastic_seed << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "stats_output_interval: " << stats_output_interval << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "spectrum_output_interval: " << spectrum_output_interval << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "is_stats_output_extended: " << ( is_stats_output_extended ? "true" : "false" ) << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "rho_part: " << rho_part << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "rho_fluid: " << rho_fluid << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "eta_k_init: " << eta_k_init << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "tau_k_init: " << tau_k_init << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "shell_thickness: " << shell_thickness << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "epsilon_env: " << epsilon_env << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "nu_fluid: " << nu_fluid << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "gravity: " << gravity << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "is_part_generated: " << ( is_part_generated ? "true" : "false" ) << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "is_part_overlapping: " << ( is_part_overlapping ? "true" : "false" ) << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "is_part_hdi_enabled: " << ( is_part_hdi_enabled ? "true" : "false" ) << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "part_hdi_trunc_enabled: " << part_hdi_trunc_enabled << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "N_part: " << N_part << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "drag_type: " << to_c_str( drag_type ) << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "a: " << a << '\n';
    
    return os;
}

std::ostream& operator<<( std::ostream& os, Parameters const& s )
{
    return s.stringify( os, 2, 0 );
}

} // end of namespace vortex::turb::legacy::settings::stat
