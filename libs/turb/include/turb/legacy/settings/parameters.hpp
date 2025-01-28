// 
// Header file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#pragma once

#include <ostream>

#include <nlohmann/json_fwd.hpp>

#include "core/common/types.hpp"
#include "core/settings/json/any_settings.hpp"
#include "turb/legacy/settings/enums/forcing_type.hpp"
#include "turb/legacy/settings/enums/drag_type.hpp"

namespace vortex::turb::legacy::settings
{

class Parameters
{
public:
    Parameters() noexcept = default;
    explicit Parameters( nlohmann::json * data_p );
    explicit Parameters( core::settings::json::AnySettings s )
    :   Parameters( s.data() )
    {}

public:

    [[nodiscard]] nlohmann::json * data() const noexcept
    {
        return m_data_p;
    }
    [[nodiscard]] bool is_empty() const noexcept
    {
        return data() == nullptr;
    }
    [[nodiscard]] core::settings::json::AnySettings as_any() const noexcept
    {
        return core::settings::json::AnySettings{ data() };
    }

    Parameters& merge( nlohmann::json * other_data_p );
    Parameters& merge( core::settings::json::AnySettings const& other )
    {
        return merge( other.data() );
    }
    Parameters& merge( Parameters const& other )
    {
        return merge( other.data() );
    }

    [[nodiscard]] std::string to_string() const;
    std::ostream& stringify( std::ostream& os, int indent_size, int indent_level, bool display_all ) const;

    friend std::ostream& operator<<( std::ostream& os, Parameters const& s );

    friend bool operator==( Parameters const& lhs, Parameters const& rhs );
    friend bool operator!=( Parameters const& lhs, Parameters const& rhs )
    {
        return !( lhs == rhs );
    }

    // "N" property
    [[nodiscard]] i32 N() const;
    [[nodiscard]] bool has_N_set() const noexcept;
    [[nodiscard]] constexpr i32 default_N() const noexcept
    {
        return i32{};
    }
    void reset_N();
    void set_N( i32 N );

    // "N_subdomain" property
    [[nodiscard]] i32 N_subdomain() const;
    [[nodiscard]] bool has_N_subdomain_set() const noexcept;
    [[nodiscard]] i32 default_N_subdomain() const noexcept
    {
        return N();
    }
    void reset_N_subdomain();
    void set_N_subdomain( i32 N_subdomain );

    // "Nt_max" property
    [[nodiscard]] i32 Nt_max() const;
    [[nodiscard]] bool has_Nt_max_set() const noexcept;
    [[nodiscard]] constexpr i32 default_Nt_max() const noexcept
    {
        return i32{};
    }
    void reset_Nt_max();
    void set_Nt_max( i32 Nt_max );

    // "dt" property
    [[nodiscard]] real dt() const;
    [[nodiscard]] bool has_dt_set() const noexcept;
    [[nodiscard]] constexpr real default_dt() const noexcept
    {
        return real{};
    }
    void reset_dt();
    void set_dt( real dt );

    // "rnu" property
    [[nodiscard]] real rnu() const;
    [[nodiscard]] bool has_rnu_set() const noexcept;
    [[nodiscard]] constexpr real default_rnu() const noexcept
    {
        return real{};
    }
    void reset_rnu();
    void set_rnu( real rnu );

    // "t_init" property
    [[nodiscard]] real t_init() const;
    [[nodiscard]] bool has_t_init_set() const noexcept;
    [[nodiscard]] constexpr real default_t_init() const noexcept
    {
        return real{};
    }
    void reset_t_init();
    void set_t_init( real t_init );

    // "is_flow_generated" property
    [[nodiscard]] bool is_flow_generated() const;
    [[nodiscard]] bool has_is_flow_generated_set() const noexcept;
    [[nodiscard]] constexpr bool default_is_flow_generated() const noexcept
    {
        return bool{};
    }
    void reset_is_flow_generated();
    void set_is_flow_generated( bool is_flow_generated );

    // "deterministic_seed" property
    [[nodiscard]] u64 deterministic_seed() const;
    [[nodiscard]] bool has_deterministic_seed_set() const noexcept;
    [[nodiscard]] constexpr u64 default_deterministic_seed() const noexcept
    {
        return u64{};
    }
    void reset_deterministic_seed();
    void set_deterministic_seed( u64 deterministic_seed );

    // "input_velo_index" property
    [[nodiscard]] i32 input_velo_index() const;
    [[nodiscard]] bool has_input_velo_index_set() const noexcept;
    [[nodiscard]] constexpr i32 default_input_velo_index() const noexcept
    {
        return i32{};
    }
    void reset_input_velo_index();
    void set_input_velo_index( i32 input_velo_index );

    // "forcing_type" property
    [[nodiscard]] ForcingType forcing_type() const;
    [[nodiscard]] bool has_forcing_type_set() const noexcept;
    [[nodiscard]] constexpr ForcingType default_forcing_type() const noexcept
    {
        return ForcingType::Deterministic;
    }
    void reset_forcing_type();
    void set_forcing_type( ForcingType forcing_type );

    // "deterministic_forcing_k_1" property
    [[nodiscard]] real deterministic_forcing_k_1() const;
    [[nodiscard]] bool has_deterministic_forcing_k_1_set() const noexcept;
    [[nodiscard]] constexpr real default_deterministic_forcing_k_1() const noexcept
    {
        return real{};
    }
    void reset_deterministic_forcing_k_1();
    void set_deterministic_forcing_k_1( real deterministic_forcing_k_1 );

    // "deterministic_forcing_k_2" property
    [[nodiscard]] real deterministic_forcing_k_2() const;
    [[nodiscard]] bool has_deterministic_forcing_k_2_set() const noexcept;
    [[nodiscard]] constexpr real default_deterministic_forcing_k_2() const noexcept
    {
        return real{};
    }
    void reset_deterministic_forcing_k_2();
    void set_deterministic_forcing_k_2( real deterministic_forcing_k_2 );

    // "stochastic_seed" property
    [[nodiscard]] u64 stochastic_seed() const;
    [[nodiscard]] bool has_stochastic_seed_set() const noexcept;
    [[nodiscard]] constexpr u64 default_stochastic_seed() const noexcept
    {
        return u64{};
    }
    void reset_stochastic_seed();
    void set_stochastic_seed( u64 stochastic_seed );

    // "stats_output_interval" property
    [[nodiscard]] i32 stats_output_interval() const;
    [[nodiscard]] bool has_stats_output_interval_set() const noexcept;
    [[nodiscard]] constexpr i32 default_stats_output_interval() const noexcept
    {
        return i32{};
    }
    void reset_stats_output_interval();
    void set_stats_output_interval( i32 stats_output_interval );

    // "spectrum_output_interval" property
    [[nodiscard]] i32 spectrum_output_interval() const;
    [[nodiscard]] bool has_spectrum_output_interval_set() const noexcept;
    [[nodiscard]] constexpr i32 default_spectrum_output_interval() const noexcept
    {
        return i32{};
    }
    void reset_spectrum_output_interval();
    void set_spectrum_output_interval( i32 spectrum_output_interval );

    // "is_stats_output_extended" property
    [[nodiscard]] bool is_stats_output_extended() const;
    [[nodiscard]] bool has_is_stats_output_extended_set() const noexcept;
    [[nodiscard]] constexpr bool default_is_stats_output_extended() const noexcept
    {
        return bool{};
    }
    void reset_is_stats_output_extended();
    void set_is_stats_output_extended( bool is_stats_output_extended );

    // "rho_part" property
    [[nodiscard]] real rho_part() const;
    [[nodiscard]] bool has_rho_part_set() const noexcept;
    [[nodiscard]] constexpr real default_rho_part() const noexcept
    {
        return real{};
    }
    void reset_rho_part();
    void set_rho_part( real rho_part );

    // "rho_fluid" property
    [[nodiscard]] real rho_fluid() const;
    [[nodiscard]] bool has_rho_fluid_set() const noexcept;
    [[nodiscard]] constexpr real default_rho_fluid() const noexcept
    {
        return real{};
    }
    void reset_rho_fluid();
    void set_rho_fluid( real rho_fluid );

    // "eta_k_init" property
    [[nodiscard]] real eta_k_init() const;
    [[nodiscard]] bool has_eta_k_init_set() const noexcept;
    [[nodiscard]] constexpr real default_eta_k_init() const noexcept
    {
        return real{};
    }
    void reset_eta_k_init();
    void set_eta_k_init( real eta_k_init );

    // "tau_k_init" property
    [[nodiscard]] real tau_k_init() const;
    [[nodiscard]] bool has_tau_k_init_set() const noexcept;
    [[nodiscard]] constexpr real default_tau_k_init() const noexcept
    {
        return real{};
    }
    void reset_tau_k_init();
    void set_tau_k_init( real tau_k_init );

    // "shell_thickness" property
    [[nodiscard]] real shell_thickness() const;
    [[nodiscard]] bool has_shell_thickness_set() const noexcept;
    [[nodiscard]] constexpr real default_shell_thickness() const noexcept
    {
        return real{};
    }
    void reset_shell_thickness();
    void set_shell_thickness( real shell_thickness );

    // "epsilon_env" property
    [[nodiscard]] real epsilon_env() const;
    [[nodiscard]] bool has_epsilon_env_set() const noexcept;
    [[nodiscard]] constexpr real default_epsilon_env() const noexcept
    {
        return real{};
    }
    void reset_epsilon_env();
    void set_epsilon_env( real epsilon_env );

    // "nu_fluid" property
    [[nodiscard]] real nu_fluid() const;
    [[nodiscard]] bool has_nu_fluid_set() const noexcept;
    [[nodiscard]] constexpr real default_nu_fluid() const noexcept
    {
        return real{};
    }
    void reset_nu_fluid();
    void set_nu_fluid( real nu_fluid );

    // "gravity" property
    [[nodiscard]] real gravity() const;
    [[nodiscard]] bool has_gravity_set() const noexcept;
    [[nodiscard]] constexpr real default_gravity() const noexcept
    {
        return real{};
    }
    void reset_gravity();
    void set_gravity( real gravity );

    // "is_part_generated" property
    [[nodiscard]] bool is_part_generated() const;
    [[nodiscard]] bool has_is_part_generated_set() const noexcept;
    [[nodiscard]] constexpr bool default_is_part_generated() const noexcept
    {
        return bool{};
    }
    void reset_is_part_generated();
    void set_is_part_generated( bool is_part_generated );

    // "is_part_overlapping" property
    [[nodiscard]] bool is_part_overlapping() const;
    [[nodiscard]] bool has_is_part_overlapping_set() const noexcept;
    [[nodiscard]] constexpr bool default_is_part_overlapping() const noexcept
    {
        return bool{};
    }
    void reset_is_part_overlapping();
    void set_is_part_overlapping( bool is_part_overlapping );

    // "is_part_hdi_enabled" property
    [[nodiscard]] bool is_part_hdi_enabled() const;
    [[nodiscard]] bool has_is_part_hdi_enabled_set() const noexcept;
    [[nodiscard]] constexpr bool default_is_part_hdi_enabled() const noexcept
    {
        return bool{};
    }
    void reset_is_part_hdi_enabled();
    void set_is_part_hdi_enabled( bool is_part_hdi_enabled );

    // "part_hdi_trunc_enabled" property
    [[nodiscard]] real part_hdi_trunc_enabled() const;
    [[nodiscard]] bool has_part_hdi_trunc_enabled_set() const noexcept;
    [[nodiscard]] constexpr real default_part_hdi_trunc_enabled() const noexcept
    {
        return real{};
    }
    void reset_part_hdi_trunc_enabled();
    void set_part_hdi_trunc_enabled( real part_hdi_trunc_enabled );

    // "N_part" property
    [[nodiscard]] i32 N_part() const;
    [[nodiscard]] bool has_N_part_set() const noexcept;
    [[nodiscard]] constexpr i32 default_N_part() const noexcept
    {
        return i32{};
    }
    void reset_N_part();
    void set_N_part( i32 N_part );

    // "drag_type" property
    [[nodiscard]] DragType drag_type() const;
    [[nodiscard]] bool has_drag_type_set() const noexcept;
    [[nodiscard]] constexpr DragType default_drag_type() const noexcept
    {
        return DragType::Stokes;
    }
    void reset_drag_type();
    void set_drag_type( DragType drag_type );

    // "a" property
    [[nodiscard]] real a() const;
    [[nodiscard]] bool has_a_set() const noexcept;
    [[nodiscard]] constexpr real default_a() const noexcept
    {
        return real{};
    }
    void reset_a();
    void set_a( real a );


private:
    nlohmann::json * m_data_p = nullptr;
}; // end of class Parameters

} // end of namespace vortex::turb::legacy::settings
