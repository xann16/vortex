#pragma once

#include <ostream>

#include <nlohmann/json_fwd.hpp>

namespace vortex::core::settings::json
{

class AnySettings
{
public:
    AnySettings() noexcept = default;
    explicit AnySettings(nlohmann::json * data_p) : m_data_p( data_p ) {}

public:
    [[nodiscard]] bool is_empty() const noexcept { return data() == nullptr; }
    [[nodiscard]] nlohmann::json * data() const noexcept { return m_data_p; }

    AnySettings& merge(nlohmann::json * other_data_p);
    AnySettings& merge(AnySettings const& other)
    {
        return merge(other.data());
    }

    [[nodiscard]] std::string to_string() const;
    std::ostream& stringify( std::ostream& os, int indent_size, int indent_level, bool display_all ) const;

    friend std::ostream& operator<<( std::ostream& os, AnySettings const& settings );

private:
    nlohmann::json * m_data_p = nullptr;
};

}
