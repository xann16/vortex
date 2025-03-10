// 
// Source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include "turb/legacy/settings/stat/execution_settings.hpp"

#include <iomanip>
#include <sstream>

namespace vortex::turb::legacy::settings::stat
{

ExecutionSettings::ExecutionSettings( std::string_view job_name, std::string_view grant_no, i32 cpu_node_count, f64 wct_limit, i32 process_count, bool is_node_overcommit_enabled ) noexcept
:   m_job_name( job_name )
,   m_grant_no( grant_no )
,   m_cpu_node_count( cpu_node_count )
,   m_wct_limit( wct_limit )
,   m_process_count( process_count )
,   m_is_node_overcommit_enabled( is_node_overcommit_enabled )
{}
[[nodiscard]] std::string ExecutionSettings::to_string() const
{
    auto oss = std::ostringstream{};
    oss << *this;
    return oss.str();
}

std::ostream& ExecutionSettings::stringify( std::ostream& os, int indent_size, int indent_level ) const
{
        os << std::setw( indent_size * indent_level ) << "" << "job_name: " << job_name() << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "grant_no: " << grant_no() << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "cpu_node_count: " << cpu_node_count() << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "wct_limit: " << wct_limit() << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "process_count: " << process_count() << '\n';
        os << std::setw( indent_size * indent_level ) << "" << "is_node_overcommit_enabled: " << ( is_node_overcommit_enabled() ? "true" : "false" ) << '\n';
    
    return os;
}

std::ostream& operator<<( std::ostream& os, ExecutionSettings const& s )
{
    return s.stringify( os, 2, 0 );
}

} // end of namespace vortex::turb::legacy::settings::stat
