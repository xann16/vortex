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

    TestStage& update_with( nlohmann::json * other_data_p );
    TestStage& update_with( core::settings::json::AnySettings const& other )
    {
        return update_with( other.data() );
    }
    TestStage& update_with( TestStage const& other )
    {
        return update_with( other.data() );
    }

    [[nodiscard]] consteval bool has_extra_data() const noexcept
    {
        return false;
    }
    [[nodiscard]] std::size_t extra_data_size() const
    {
        throw std::runtime_error{ "Unsupported operation for settings with abstract nested settings or arrays." };
    }

    [[nodiscard]] std::string to_string() const;
    std::ostream& stringify( std::ostream& os, int indent_size, int indent_level, bool display_all ) const;

    void validate() const;

    friend std::ostream& operator<<( std::ostream& os, TestStage const& s );

    friend bool operator==( TestStage const& lhs, TestStage const& rhs );
    friend bool operator!=( TestStage const& lhs, TestStage const& rhs )
    {
        return !( lhs == rhs );
    }

    // "name" property
    [[nodiscard]] std::string_view name() const;
    [[nodiscard]] bool has_name_set() const noexcept;
    [[nodiscard]] constexpr std::string_view default_name() const noexcept
    {
        return std::string_view{};
    }
    void reset_name();
    void set_name( std::string const& name );
    void set_name( std::string && name );
    void set_name( std::string_view name )
    {
        set_name( std::string{ name } );
    }
    void set_name( char const * name )
    {
        set_name( std::string{ name } );
    }

    // "settings" property
    [[nodiscard]] core::settings::json::AnySettings settings() const;
    [[nodiscard]] bool has_settings_set() const noexcept;
    [[nodiscard]] constexpr core::settings::json::AnySettings default_settings() const noexcept
    {
        return core::settings::json::AnySettings{};
    }
    void reset_settings();
    void set_settings( core::settings::json::AnySettings settings );


private:
    void pre_validate_all();
    static void pre_validate_name( [[maybe_unused]] std::string_view name );
    static void pre_validate_settings( [[maybe_unused]] core::settings::json::AnySettings settings );

private:
    nlohmann::json * m_data_p = nullptr;
}; // end of class TestStage

} // end of namespace vortex::runner::config
