// 
// Header file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#pragma once

#include <nlohmann/json_fwd.hpp>

#include "core/common/types.hpp"
#include "turb/legacy/settings/enums/forcing_type.hpp"
#include "turb/legacy/settings/enums/drag_type.hpp"

namespace vortex::turb::legacy::settings
{

class Parameters
{
public:
    explicit Parameters( nlohmann::json * data_p );

public:
    // "N" property
    [[nodiscard]] i32 N() const;
    [[nodiscard]] constexpr i32 default_N() const noexcept
    {
        return i32{};
    }

    // "N_subdomain" property
    [[nodiscard]] i32 N_subdomain() const;
    [[nodiscard]] i32 default_N_subdomain() const noexcept
    {
        return N();
    }

    // "Nt_max" property
    [[nodiscard]] i32 Nt_max() const;
    [[nodiscard]] constexpr i32 default_Nt_max() const noexcept
    {
        return i32{};
    }

    // "dt" property
    [[nodiscard]] real dt() const;
    [[nodiscard]] constexpr real default_dt() const noexcept
    {
        return real{};
    }

    // "rnu" property
    [[nodiscard]] real rnu() const;
    [[nodiscard]] constexpr real default_rnu() const noexcept
    {
        return real{};
    }

    // "t_init" property
    [[nodiscard]] real t_init() const;
    [[nodiscard]] constexpr real default_t_init() const noexcept
    {
        return real{};
    }

    // "is_flow_generated" property
    [[nodiscard]] bool is_flow_generated() const;
    [[nodiscard]] constexpr bool default_is_flow_generated() const noexcept
    {
        return bool{};
    }

    // "deterministic_seed" property
    [[nodiscard]] u64 deterministic_seed() const;
    [[nodiscard]] constexpr u64 default_deterministic_seed() const noexcept
    {
        return u64{};
    }

    // "input_velo_index" property
    [[nodiscard]] i32 input_velo_index() const;
    [[nodiscard]] constexpr i32 default_input_velo_index() const noexcept
    {
        return i32{};
    }

    // "forcing_type" property
    [[nodiscard]] ForcingType forcing_type() const;
    [[nodiscard]] constexpr ForcingType default_forcing_type() const noexcept
    {
        return ForcingType::Deterministic;
    }

    // "deterministic_forcing_k_1" property
    [[nodiscard]] real deterministic_forcing_k_1() const;
    [[nodiscard]] constexpr real default_deterministic_forcing_k_1() const noexcept
    {
        return real{};
    }

    // "deterministic_forcing_k_2" property
    [[nodiscard]] real deterministic_forcing_k_2() const;
    [[nodiscard]] constexpr real default_deterministic_forcing_k_2() const noexcept
    {
        return real{};
    }

    // "stochastic_seed" property
    [[nodiscard]] u64 stochastic_seed() const;
    [[nodiscard]] constexpr u64 default_stochastic_seed() const noexcept
    {
        return u64{};
    }

    // "stats_output_interval" property
    [[nodiscard]] i32 stats_output_interval() const;
    [[nodiscard]] constexpr i32 default_stats_output_interval() const noexcept
    {
        return i32{};
    }

    // "spectrum_output_interval" property
    [[nodiscard]] i32 spectrum_output_interval() const;
    [[nodiscard]] constexpr i32 default_spectrum_output_interval() const noexcept
    {
        return i32{};
    }

    // "is_stats_output_extended" property
    [[nodiscard]] bool is_stats_output_extended() const;
    [[nodiscard]] constexpr bool default_is_stats_output_extended() const noexcept
    {
        return bool{};
    }

    // "rho_part" property
    [[nodiscard]] real rho_part() const;
    [[nodiscard]] constexpr real default_rho_part() const noexcept
    {
        return real{};
    }

    // "rho_fluid" property
    [[nodiscard]] real rho_fluid() const;
    [[nodiscard]] constexpr real default_rho_fluid() const noexcept
    {
        return real{};
    }

    // "eta_k_init" property
    [[nodiscard]] real eta_k_init() const;
    [[nodiscard]] constexpr real default_eta_k_init() const noexcept
    {
        return real{};
    }

    // "tau_k_init" property
    [[nodiscard]] real tau_k_init() const;
    [[nodiscard]] constexpr real default_tau_k_init() const noexcept
    {
        return real{};
    }

    // "shell_thickness" property
    [[nodiscard]] real shell_thickness() const;
    [[nodiscard]] constexpr real default_shell_thickness() const noexcept
    {
        return real{};
    }

    // "epsilon_env" property
    [[nodiscard]] real epsilon_env() const;
    [[nodiscard]] constexpr real default_epsilon_env() const noexcept
    {
        return real{};
    }

    // "nu_fluid" property
    [[nodiscard]] real nu_fluid() const;
    [[nodiscard]] constexpr real default_nu_fluid() const noexcept
    {
        return real{};
    }

    // "gravity" property
    [[nodiscard]] real gravity() const;
    [[nodiscard]] constexpr real default_gravity() const noexcept
    {
        return real{};
    }

    // "is_part_generated" property
    [[nodiscard]] bool is_part_generated() const;
    [[nodiscard]] constexpr bool default_is_part_generated() const noexcept
    {
        return bool{};
    }

    // "is_part_overlapping" property
    [[nodiscard]] bool is_part_overlapping() const;
    [[nodiscard]] constexpr bool default_is_part_overlapping() const noexcept
    {
        return bool{};
    }

    // "is_part_hdi_enabled" property
    [[nodiscard]] bool is_part_hdi_enabled() const;
    [[nodiscard]] constexpr bool default_is_part_hdi_enabled() const noexcept
    {
        return bool{};
    }

    // "part_hdi_trunc_enabled" property
    [[nodiscard]] real part_hdi_trunc_enabled() const;
    [[nodiscard]] constexpr real default_part_hdi_trunc_enabled() const noexcept
    {
        return real{};
    }

    // "N_part" property
    [[nodiscard]] i32 N_part() const;
    [[nodiscard]] constexpr i32 default_N_part() const noexcept
    {
        return i32{};
    }

    // "drag_type" property
    [[nodiscard]] DragType drag_type() const;
    [[nodiscard]] constexpr DragType default_drag_type() const noexcept
    {
        return DragType::Stokes;
    }

    // "a" property
    [[nodiscard]] real a() const;
    [[nodiscard]] constexpr real default_a() const noexcept
    {
        return real{};
    }


private:
    nlohmann::json * m_data_p = nullptr;
}; // end of class Parameters

} // end of namespace vortex::turb::legacy::settings
