#include "core/settings/json/any_settings.hpp"

#include <iomanip>
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
    auto oss = std::ostringstream{};
    oss << *this;
    return oss.str();
}

std::ostream& AnySettings::stringify( std::ostream& os, int indent_size, int indent_level, bool display_all ) const
{
    if (is_empty() || data()->empty())
    {
        os << "<empty>\n";
        return os;
    }

    for (auto const& item : data()->items())
    {
        if ( !display_all && item.value().is_null() ) continue;

        os << std::setw( indent_size * indent_level) << "" << item.key() << ':';
        if (item.value().is_object())
        {
            auto inner = AnySettings( &item.value() );
            os << '\n';
            inner.stringify( os, indent_size, indent_level + 1, display_all );
        }
        else if( item.value().is_string() )
        {
            os << ' ' << item.value().template get_ref<std::string const&>() << '\n';
        }
        else
        {
            os << ' ' << item.value() << '\n';
        }
    }

    return os;
}

std::ostream& operator<<( std::ostream& os, AnySettings const& settings )
{
    return settings.stringify( os, 2, 0, os.flags() & std::ios_base::boolalpha );
}

}
