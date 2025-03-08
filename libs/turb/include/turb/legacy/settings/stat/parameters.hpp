// 
// Header file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#pragma once

#include <ostream>
#include <string_view>
#include <span>

#include "core/common/types.hpp"
#include "turb/legacy/settings/enums/forcing_type.hpp"
#include "turb/legacy/settings/enums/drag_type.hpp"

namespace vortex::turb::legacy::settings::stat
{

class Parameters
{
public:
    Parameters() noexcept = default;
    Parameters( i32 N, i32 N_subdomain, i32 Nt_max, real dt, real rnu, real t_init, bool is_flow_generated, u64 deterministic_seed, i32 input_velo_index, ForcingType forcing_type, real deterministic_forcing_k_1, real deterministic_forcing_k_2, u64 stochastic_seed, i32 stats_output_interval, i32 spectrum_output_interval, bool is_stats_output_extended, real rho_part, real rho_fluid, real eta_k_init, real tau_k_init, real shell_thickness, real epsilon_env, real nu_fluid, real gravity, bool is_part_generated, bool is_part_overlapping, bool is_part_hdi_enabled, real part_hdi_trunc_enabled, i32 N_part, DragType drag_type, real a ) noexcept;
public:
    [[nodiscard]] constexpr i32 N() const noexcept
    {
        return m_N;
    }
    [[nodiscard]] constexpr i32 N_subdomain() const noexcept
    {
        return m_N_subdomain;
    }
    [[nodiscard]] constexpr i32 Nt_max() const noexcept
    {
        return m_Nt_max;
    }
    [[nodiscard]] constexpr real dt() const noexcept
    {
        return m_dt;
    }
    [[nodiscard]] constexpr real rnu() const noexcept
    {
        return m_rnu;
    }
    [[nodiscard]] constexpr real t_init() const noexcept
    {
        return m_t_init;
    }
    [[nodiscard]] constexpr bool is_flow_generated() const noexcept
    {
        return m_is_flow_generated;
    }
    [[nodiscard]] constexpr u64 deterministic_seed() const noexcept
    {
        return m_deterministic_seed;
    }
    [[nodiscard]] constexpr i32 input_velo_index() const noexcept
    {
        return m_input_velo_index;
    }
    [[nodiscard]] constexpr ForcingType forcing_type() const noexcept
    {
        return m_forcing_type;
    }
    [[nodiscard]] constexpr real deterministic_forcing_k_1() const noexcept
    {
        return m_deterministic_forcing_k_1;
    }
    [[nodiscard]] constexpr real deterministic_forcing_k_2() const noexcept
    {
        return m_deterministic_forcing_k_2;
    }
    [[nodiscard]] constexpr u64 stochastic_seed() const noexcept
    {
        return m_stochastic_seed;
    }
    [[nodiscard]] constexpr i32 stats_output_interval() const noexcept
    {
        return m_stats_output_interval;
    }
    [[nodiscard]] constexpr i32 spectrum_output_interval() const noexcept
    {
        return m_spectrum_output_interval;
    }
    [[nodiscard]] constexpr bool is_stats_output_extended() const noexcept
    {
        return m_is_stats_output_extended;
    }
    [[nodiscard]] constexpr real rho_part() const noexcept
    {
        return m_rho_part;
    }
    [[nodiscard]] constexpr real rho_fluid() const noexcept
    {
        return m_rho_fluid;
    }
    [[nodiscard]] constexpr real eta_k_init() const noexcept
    {
        return m_eta_k_init;
    }
    [[nodiscard]] constexpr real tau_k_init() const noexcept
    {
        return m_tau_k_init;
    }
    [[nodiscard]] constexpr real shell_thickness() const noexcept
    {
        return m_shell_thickness;
    }
    [[nodiscard]] constexpr real epsilon_env() const noexcept
    {
        return m_epsilon_env;
    }
    [[nodiscard]] constexpr real nu_fluid() const noexcept
    {
        return m_nu_fluid;
    }
    [[nodiscard]] constexpr real gravity() const noexcept
    {
        return m_gravity;
    }
    [[nodiscard]] constexpr bool is_part_generated() const noexcept
    {
        return m_is_part_generated;
    }
    [[nodiscard]] constexpr bool is_part_overlapping() const noexcept
    {
        return m_is_part_overlapping;
    }
    [[nodiscard]] constexpr bool is_part_hdi_enabled() const noexcept
    {
        return m_is_part_hdi_enabled;
    }
    [[nodiscard]] constexpr real part_hdi_trunc_enabled() const noexcept
    {
        return m_part_hdi_trunc_enabled;
    }
    [[nodiscard]] constexpr i32 N_part() const noexcept
    {
        return m_N_part;
    }
    [[nodiscard]] constexpr DragType drag_type() const noexcept
    {
        return m_drag_type;
    }
    [[nodiscard]] constexpr real a() const noexcept
    {
        return m_a;
    }

    [[nodiscard]] consteval bool has_extra_data() const noexcept
    {
        return false;
    }
    [[nodiscard]] constexpr std::size_t extra_data_size() const noexcept
    {
        return 0ull;
    }

    [[nodiscard]] std::string to_string() const;
    std::ostream& stringify( std::ostream& os, int indent_size, int indent_level ) const;

    friend std::ostream& operator<<( std::ostream& os, Parameters const& s );

private:
    i32 m_N = 8;
    i32 m_N_subdomain = 1;
    i32 m_Nt_max = 1;
    real m_dt = 0.001;
    real m_rnu = real{};
    real m_t_init = real{};
    bool m_is_flow_generated = true;
    u64 m_deterministic_seed = u64{};
    i32 m_input_velo_index = i32{};
    ForcingType m_forcing_type = ForcingType::Deterministic;
    real m_deterministic_forcing_k_1 = 1.0;
    real m_deterministic_forcing_k_2 = 1.0;
    u64 m_stochastic_seed = u64{};
    i32 m_stats_output_interval = i32{};
    i32 m_spectrum_output_interval = i32{};
    bool m_is_stats_output_extended = bool{};
    real m_rho_part = real{};
    real m_rho_fluid = real{};
    real m_eta_k_init = 1.0;
    real m_tau_k_init = 1.0;
    real m_shell_thickness = 1.0;
    real m_epsilon_env = real{};
    real m_nu_fluid = real{};
    real m_gravity = real{};
    bool m_is_part_generated = bool{};
    bool m_is_part_overlapping = bool{};
    bool m_is_part_hdi_enabled = bool{};
    real m_part_hdi_trunc_enabled = real{};
    i32 m_N_part = i32{};
    DragType m_drag_type = DragType::Stokes;
    real m_a = real{};
}; // end of class Parameters

} // end of namespace vortex::turb::legacy::settings::stat
