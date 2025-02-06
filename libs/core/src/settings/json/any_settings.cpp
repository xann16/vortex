#include "core/settings/json/any_settings.hpp"

#include <iomanip>
#include <sstream>

#include <nlohmann/json.hpp>

namespace vortex::core::settings::json
{

namespace
{
    void value_to_stream( nlohmann::json& value, std::ostream& os, int indent_size, int indent_level, bool display_all )
    {
        if ( value.is_object() )
        {
            os << '\n';
            auto inner = AnySettings( &value );
            inner.stringify( os, indent_size, indent_level + 1, display_all );
        }
        else if ( value.is_array() )
        {
            if ( value.empty() )
            {
                os << " <empty>\n";
            }
            else
            {
                os << '\n';
                ++indent_level;
                for ( auto& el : value )
                {
                    os << std::setw( indent_size * indent_level) << "" << "-";
                    value_to_stream( el, os, indent_size, indent_level, display_all );
                }
            }

        }
        else if ( value.is_string() )
        {
            os << ' ' << value.template get_ref<std::string const&>() << '\n';
        }
        else
        {
            os << ' ' << value << '\n';
        }

    }

    // reference - github for nlohmann::json - issue #1422
    nlohmann::json& strip_nulls( nlohmann::json& j, bool strip_empty_objects_and_arrays = false )
    {
        nlohmann::json j_bis = j;
        j.clear();

        for ( auto const& item : j_bis.items() )
        {
            const auto type = item.value().type();
            switch ( type )
            {
                case nlohmann::json::value_t::object:
                {
                    nlohmann::json j_sub = strip_nulls( item.value(), strip_empty_objects_and_arrays );
                    if ( !( strip_empty_objects_and_arrays && j_sub.empty() ) )
                    {
                        j[ item.key() ] = j_sub;
                    }
                    break;
                }
                case nlohmann::json::value_t::array:
                {
                    nlohmann::json j_sub = item.value();
                    j_sub.erase( std::remove_if( std::begin( j_sub ), std::end( j_sub ), []( auto const& val ) { return val.is_null(); }), std::end( j_sub ) );
                    for ( auto it = std::begin( j_sub ); it != std::end( j_sub ); ++it )
                    {
                        if ( it->is_object() ) strip_nulls( *it, strip_empty_objects_and_arrays );
                    }
                    if ( !( strip_empty_objects_and_arrays && j_sub.empty() ) )
                    {
                        j[ item.key() ] = j_sub;
                    }
                    break;
                }
                case nlohmann::json::value_t::null:
                    break;
                default:
                {
                    j[ item.key() ] = item.value();
                    break;
                }
            }
        }
        return j;
    }

}

AnySettings& AnySettings::update_with(nlohmann::json * other_data_p)
{
    if (!is_empty() && other_data_p != nullptr)
    {
        nlohmann::json other_copy = *other_data_p;
        m_data_p->merge_patch( strip_nulls( other_copy ) );
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
        value_to_stream( item.value(), os, indent_size, indent_level, display_all );
    }

    return os;
}

std::ostream& operator<<( std::ostream& os, AnySettings const& settings )
{
    return settings.stringify( os, 2, 0, os.flags() & std::ios_base::boolalpha );
}

bool operator==( AnySettings const& lhs, AnySettings const& rhs )
{
    return lhs.is_empty()
        ? rhs.is_empty()
        : ( !rhs.is_empty() && *lhs.data() == *rhs.data() );
}

}
