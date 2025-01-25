// 
// Source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include "runner/config/test_fixture.hpp"

#include <iomanip>
#include <sstream>

#include <nlohmann/json.hpp>


namespace vortex::runner::config
{

TestFixture::TestFixture( nlohmann::json * data_p )
:   m_data_p( data_p )
{
    // add initial validation
}

TestFixture& TestFixture::merge( nlohmann::json * other_data_p )
{
    if (!is_empty() && other_data_p != nullptr)
    {
        data()->merge_patch( *other_data_p );
    }
    return *this;
}

[[nodiscard]] std::string TestFixture::to_string() const
{
    auto oss = std::ostringstream{};
    oss << *this;
    return oss.str();
}

std::ostream& TestFixture::stringify( std::ostream& os, int indent_size, int indent_level, bool display_all ) const
{
    if ( !display_all && ( is_empty() || data()->empty() ) )
    {
        os << "<empty>\n"; 
        return os;
    }
    
    if ( display_all || has_name_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "name: " << name() << '\n';
    }
    if ( display_all || has_root_path_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "root_path: " << root_path() << '\n';
    }
    if ( display_all || has_default_settings_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "default_settings:\n";
        default_settings().stringify( os, indent_size, indent_level + 1, display_all );
    }
    if ( display_all || has_test_cases_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "test_cases:\n";
        test_cases().stringify( os, indent_size, indent_level + 1, display_all );
    }
    if ( display_all || has_test_stages_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "test_stages:\n";
        test_stages().stringify( os, indent_size, indent_level + 1, display_all );
    }
    
    return os;
}

std::ostream& operator<<( std::ostream& os, TestFixture const& s )
{
    return s.stringify( os, 2, 0, os.flags() & std::ios_base::boolalpha );
}

// "name" property

[[nodiscard]] std::string_view TestFixture::name() const
{
    if ( is_empty() ) return default_name();
    auto it = m_data_p->find( "name" );
    if ( it == m_data_p->end() || it->is_null() ) return default_name();
    return std::string_view{ it->template get_ref<std::string const&>() };
}

[[nodiscard]] bool TestFixture::has_name_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "name" );
    return it != m_data_p->end() && !it->is_null();
}

// "root_path" property

[[nodiscard]] std::string_view TestFixture::root_path() const
{
    if ( is_empty() ) return default_root_path();
    auto it = m_data_p->find( "root_path" );
    if ( it == m_data_p->end() || it->is_null() ) return default_root_path();
    return std::string_view{ it->template get_ref<std::string const&>() };
}

[[nodiscard]] bool TestFixture::has_root_path_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "root_path" );
    return it != m_data_p->end() && !it->is_null();
}

// "default_settings" property

[[nodiscard]] core::settings::json::AnySettings TestFixture::default_settings() const
{
    if ( is_empty() ) return default_default_settings();
    auto it = m_data_p->find( "default_settings" );
    if ( it == m_data_p->end() || it->is_null() ) return default_default_settings();
    return core::settings::json::AnySettings{ &( *it ) };
}

[[nodiscard]] bool TestFixture::has_default_settings_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "default_settings" );
    return it != m_data_p->end() && !it->is_null();
}

// "test_cases" property

[[nodiscard]] runner::config::TestCase TestFixture::test_cases() const
{
    if ( is_empty() ) return default_test_cases();
    auto it = m_data_p->find( "test_cases" );
    if ( it == m_data_p->end() || it->is_null() ) return default_test_cases();
    return runner::config::TestCase{ &( *it ) };
}

[[nodiscard]] bool TestFixture::has_test_cases_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "test_cases" );
    return it != m_data_p->end() && !it->is_null();
}

// "test_stages" property

[[nodiscard]] runner::config::TestStage TestFixture::test_stages() const
{
    if ( is_empty() ) return default_test_stages();
    auto it = m_data_p->find( "test_stages" );
    if ( it == m_data_p->end() || it->is_null() ) return default_test_stages();
    return runner::config::TestStage{ &( *it ) };
}

[[nodiscard]] bool TestFixture::has_test_stages_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "test_stages" );
    return it != m_data_p->end() && !it->is_null();
}


} // end of namespace vortex::runner::config
