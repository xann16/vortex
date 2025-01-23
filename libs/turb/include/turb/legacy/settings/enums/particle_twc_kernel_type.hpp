// 
// Header file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#pragma once

#include <cstring>
#include <string>

namespace vortex::turb::legacy::settings
{

enum class ParticleTwcKernelType
{
    Pnn,
    Pic
};

[[nodiscard]] inline char const * to_c_str( ParticleTwcKernelType value ) noexcept
{
    switch( value )
    {
    case ParticleTwcKernelType::Pnn:
        return "pnn";
    case ParticleTwcKernelType::Pic:
        return "pic";
    }
        return "unknown";
}

[[nodiscard]] inline std::string to_string( ParticleTwcKernelType value ) noexcept
{
    return std::string{ to_c_str( value ) };
}

[[nodiscard]] inline ParticleTwcKernelType to_particle_twc_kernel_type( char const * str ) noexcept
{
    if ( std::strcmp( str, "pic" ) == 0 )
    {
        return ParticleTwcKernelType::Pic;
    }
    return ParticleTwcKernelType::Pnn;
}

[[nodiscard]] inline ParticleTwcKernelType to_particle_twc_kernel_type( std::string const& str ) noexcept
{
    return to_particle_twc_kernel_type( str.c_str() );
}

} // end of namespace vortex::turb::legacy::settings
