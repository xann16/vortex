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

namespace vortex::turb::legacy::settings
{

class ExecutionSettings
{
public:
    ExecutionSettings() noexcept = default;
    explicit ExecutionSettings( nlohmann::json * data_p );
    explicit ExecutionSettings( core::settings::json::AnySettings s )
    :   ExecutionSettings( s.data() )
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

    ExecutionSettings& merge( nlohmann::json * other_data_p );
    ExecutionSettings& merge( core::settings::json::AnySettings const& other )
    {
        return merge( other.data() );
    }
    ExecutionSettings& merge( ExecutionSettings const& other )
    {
        return merge( other.data() );
    }

    [[nodiscard]] std::string to_string() const;
    std::ostream& stringify( std::ostream& os, int indent_size, int indent_level, bool display_all ) const;

    friend std::ostream& operator<<( std::ostream& os, ExecutionSettings const& s );

    // "job_name" property
    [[nodiscard]] std::string_view job_name() const;
    [[nodiscard]] bool has_job_name_set() const noexcept;
    [[nodiscard]] constexpr std::string_view default_job_name() const noexcept
    {
        return std::string_view{};
    }

    // "grant_no" property
    [[nodiscard]] std::string_view grant_no() const;
    [[nodiscard]] bool has_grant_no_set() const noexcept;
    [[nodiscard]] constexpr std::string_view default_grant_no() const noexcept
    {
        return std::string_view{};
    }

    // "cpu_node_count" property
    [[nodiscard]] i32 cpu_node_count() const;
    [[nodiscard]] bool has_cpu_node_count_set() const noexcept;
    [[nodiscard]] constexpr i32 default_cpu_node_count() const noexcept
    {
        return 1;
    }

    // "wct_limit" property
    [[nodiscard]] f64 wct_limit() const;
    [[nodiscard]] bool has_wct_limit_set() const noexcept;
    [[nodiscard]] constexpr f64 default_wct_limit() const noexcept
    {
        return 60.0;
    }

    // "process_count" property
    [[nodiscard]] i32 process_count() const;
    [[nodiscard]] bool has_process_count_set() const noexcept;
    [[nodiscard]] constexpr i32 default_process_count() const noexcept
    {
        return 1;
    }

    // "is_node_overcommit_enabled" property
    [[nodiscard]] bool is_node_overcommit_enabled() const;
    [[nodiscard]] bool has_is_node_overcommit_enabled_set() const noexcept;
    [[nodiscard]] constexpr bool default_is_node_overcommit_enabled() const noexcept
    {
        return bool{};
    }


private:
    nlohmann::json * m_data_p = nullptr;
}; // end of class ExecutionSettings

} // end of namespace vortex::turb::legacy::settings
