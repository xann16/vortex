// 
// Header file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#pragma once
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <cstring>
#include <string>

namespace vortex::turb::legacy::settings
{

enum class SimMethod
{
    Dns,
    Les,
    Fdns
};

[[nodiscard]] inline char const * to_c_str( SimMethod value ) noexcept
{
    switch( value )
    {
    case SimMethod::Dns:
        return "dns";
    case SimMethod::Les:
        return "les";
    case SimMethod::Fdns:
        return "fdns";
    default:
        return "unknown";
    }
}

[[nodiscard]] inline std::string to_string( SimMethod value ) noexcept
{
    return std::string{ to_c_str( value ) };
}

[[nodiscard]] inline SimMethod to_sim_method( char const * str ) noexcept
{
    if ( std::strcmp( str, "les" ) == 0 )
    {
        return SimMethod::Les;
    }
    if ( std::strcmp( str, "fdns" ) == 0 )
    {
        return SimMethod::Fdns;
    }
    return SimMethod::Dns;
}

[[nodiscard]] inline SimMethod to_sim_method( std::string const& str ) noexcept
{
    return to_sim_method( str.c_str() );
}

} // end of namespace vortex::turb::legacy::settings

#pragma clang diagnostic pop
