#include "core/settings/json/any_settings.hpp"

#include <sstream>

#include <nlohmann/json.hpp>

namespace vortex::core::settings::json
{

AnySettings& AnySettings::merge(nlohmann::json * other_data_p)
{
    if (!is_empty() && other_data_p != nullptr)
    {
        m_data_p->merge_patch( *other_data_p );
    }
    return *this;
}

[[nodiscard]] std::string AnySettings::to_string() const
{
    if (is_empty())
    {
        return std::string{};
    }

    auto oss = std::ostringstream{};
    oss << *this;
    return oss.str();
}

std::ostream& operator<<( std::ostream& os, AnySettings const& settings )
{
    if (!settings.is_empty())
    {
        os << std::setw( 2 ) << *(settings.data()) << std::endl;
    }
    return os;
}

}
