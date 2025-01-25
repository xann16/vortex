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

namespace vortex::runner::config
{

class TestStage
{
public:
    TestStage() noexcept = default;
    explicit TestStage( nlohmann::json * data_p );
    explicit TestStage( core::settings::json::AnySettings s )
    :   TestStage( s.data() )
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

    TestStage& merge( nlohmann::json * other_data_p );
    TestStage& merge( core::settings::json::AnySettings const& other )
    {
        return merge( other.data() );
    }
    TestStage& merge( TestStage const& other )
    {
        return merge( other.data() );
    }

    [[nodiscard]] std::string to_string() const;
    std::ostream& stringify( std::ostream& os, int indent_size, int indent_level, bool display_all ) const;

    friend std::ostream& operator<<( std::ostream& os, TestStage const& s );

    // "name" property
    [[nodiscard]] std::string_view name() const;
    [[nodiscard]] bool has_name_set() const noexcept;
    [[nodiscard]] constexpr std::string_view default_name() const noexcept
    {
        return std::string_view{};
    }

    // "settings" property
    [[nodiscard]] core::settings::json::AnySettings settings() const;
    [[nodiscard]] bool has_settings_set() const noexcept;
    [[nodiscard]] constexpr core::settings::json::AnySettings default_settings() const noexcept
    {
        return core::settings::json::AnySettings{};;
    }


private:
    nlohmann::json * m_data_p = nullptr;
}; // end of class TestStage

} // end of namespace vortex::runner::config
