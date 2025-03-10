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

enum class ParticleMode
{
    None,
    Owc,
    Twc
};

[[nodiscard]] inline char const * to_c_str( ParticleMode value ) noexcept
{
    switch( value )
    {
    case ParticleMode::None:
        return "none";
    case ParticleMode::Owc:
        return "owc";
    case ParticleMode::Twc:
        return "twc";
    default:
        return "unknown";
    }
}

[[nodiscard]] inline std::string to_string( ParticleMode value ) noexcept
{
    return std::string{ to_c_str( value ) };
}

[[nodiscard]] inline ParticleMode to_particle_mode( char const * str ) noexcept
{
    if ( std::strcmp( str, "owc" ) == 0 )
    {
        return ParticleMode::Owc;
    }
    if ( std::strcmp( str, "twc" ) == 0 )
    {
        return ParticleMode::Twc;
    }
    return ParticleMode::None;
}

[[nodiscard]] inline ParticleMode to_particle_mode( std::string const& str ) noexcept
{
    return to_particle_mode( str.c_str() );
}

} // end of namespace vortex::turb::legacy::settings

#pragma clang diagnostic pop
