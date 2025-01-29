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
        os << std::setw( indent_size * indent_level ) << "" << "test_cases:";
        auto const& test_cases_arr = test_cases();
        
        if ( test_cases_arr.empty() )
        {
            os << " <empty>\n";
        }
        else
        {
            os << '\n';
            for (auto const& el : test_cases_arr)
            {
                os << std::setw( indent_size * ( indent_level + 1 ) ) << "" << "- \n";
                el.stringify( os, indent_size, indent_level + 2, display_all );
            }
        }
    }
    if ( display_all || has_test_stages_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "test_stages:";
        auto const& test_stages_arr = test_stages();
        
        if ( test_stages_arr.empty() )
        {
            os << " <empty>\n";
        }
        else
        {
            os << '\n';
            for (auto const& el : test_stages_arr)
            {
                os << std::setw( indent_size * ( indent_level + 1 ) ) << "" << "- \n";
                el.stringify( os, indent_size, indent_level + 2, display_all );
            }
        }
    }
    
    return os;
}

std::ostream& operator<<( std::ostream& os, TestFixture const& s )
{
    return s.stringify( os, 2, 0, os.flags() & std::ios_base::boolalpha );
}

bool operator==( TestFixture const& lhs, TestFixture const& rhs )
{
    return lhs.is_empty()
        ? rhs.is_empty()
        : ( !rhs.is_empty() && *lhs.data() == *rhs.data() );
}

// "name" property

[[nodiscard]] std::string_view TestFixture::name() const
{
    if ( is_empty() ) return default_name();
    auto it = data()->find( "name" );
    if ( it == data()->end() || it->is_null() ) return default_name();
    return std::string_view{ it->template get_ref<std::string const&>() };
}

[[nodiscard]] bool TestFixture::has_name_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "name" );
    return it != data()->end() && !it->is_null();
}

void TestFixture::reset_name()
{
    if ( is_empty() ) return;
    data()->erase( "name" );
}

void TestFixture::set_name( std::string const& name )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"name\". Object is empty." };
    data()->operator[]( "name" ) = name;
}
void TestFixture::set_name( std::string && name )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"name\". Object is empty." };
    data()->operator[]( "name" ) = name;
}

// "root_path" property

[[nodiscard]] std::string_view TestFixture::root_path() const
{
    if ( is_empty() ) return default_root_path();
    auto it = data()->find( "root_path" );
    if ( it == data()->end() || it->is_null() ) return default_root_path();
    return std::string_view{ it->template get_ref<std::string const&>() };
}

[[nodiscard]] bool TestFixture::has_root_path_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "root_path" );
    return it != data()->end() && !it->is_null();
}

void TestFixture::reset_root_path()
{
    if ( is_empty() ) return;
    data()->erase( "root_path" );
}

void TestFixture::set_root_path( std::string const& root_path )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"root_path\". Object is empty." };
    data()->operator[]( "root_path" ) = root_path;
}
void TestFixture::set_root_path( std::string && root_path )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"root_path\". Object is empty." };
    data()->operator[]( "root_path" ) = root_path;
}

// "default_settings" property

[[nodiscard]] core::settings::json::AnySettings TestFixture::default_settings() const
{
    if ( is_empty() ) return default_default_settings();
    auto it = data()->find( "default_settings" );
    if ( it == data()->end() || it->is_null() ) return default_default_settings();
    return core::settings::json::AnySettings{ &( *it ) };
}

[[nodiscard]] bool TestFixture::has_default_settings_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "default_settings" );
    return it != data()->end() && !it->is_null();
}

void TestFixture::reset_default_settings()
{
    if ( is_empty() ) return;
    data()->erase( "default_settings" );
}

void TestFixture::set_default_settings( core::settings::json::AnySettings default_settings )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"default_settings\". Object is empty." };
    if ( default_settings.is_empty() )
    {
        reset_default_settings();
    }
    else
    {
        data()->operator[]( "default_settings" ) = *( default_settings.data() );
    }
}

// "test_cases" property

[[nodiscard]] std::vector< runner::config::TestCase > TestFixture::test_cases() const
{
    if ( is_empty() ) return default_test_cases();
    auto it = data()->find( "test_cases" );
    if ( it == data()->end() || it->is_null() ) return default_test_cases();
    
    auto result = std::vector< runner::config::TestCase >{};
    result.reserve( it->size() );
    
    auto value_mapping = []( auto& value )
    {
        return runner::config::TestCase{ &value };
    };
    
    std::transform( it->begin(), it->end(), std::back_inserter( result ), value_mapping );
    return result;
}

[[nodiscard]] bool TestFixture::has_test_cases_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "test_cases" );
    return it != data()->end() && !it->is_null();
}

void TestFixture::reset_test_cases()
{
    if ( is_empty() ) return;
    data()->erase( "test_cases" );
}

void TestFixture::set_test_cases( std::vector< runner::config::TestCase > const& test_cases )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"test_cases\". Object is empty." };
    data()->operator[]( "test_cases" ) = nlohmann::json::array();
    auto& test_cases_arr =  data()->operator[]( "test_cases" );
    for ( auto el : test_cases )
    {
        test_cases_arr.emplace_back( *( el.data() ) );
    }
}
void TestFixture::set_test_cases( std::vector< runner::config::TestCase > && test_cases )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"test_cases\". Object is empty." };
    data()->operator[]( "test_cases" ) = nlohmann::json::array();
    auto& test_cases_arr =  data()->operator[]( "test_cases" );
    for ( auto el : test_cases )
    {
        test_cases_arr.emplace_back( *( el.data() ) );
    }
}
void TestFixture::set_test_cases( std::initializer_list< runner::config::TestCase > test_cases )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"test_cases\". Object is empty." };
    data()->operator[]( "test_cases" ) = nlohmann::json::array();
    auto& test_cases_arr =  data()->operator[]( "test_cases" );
    for ( auto el : test_cases )
    {
        test_cases_arr.emplace_back( *( el.data() ) );
    }
}

[[nodiscard]] bool TestFixture::are_test_cases_empty() const noexcept
{
    if ( is_empty() ) return true;
    return data()->at( "test_cases" ).empty();
}

[[nodiscard]] std::size_t TestFixture::test_cases_count() const noexcept
{
    if ( is_empty() ) return 0ull;
    return data()->at( "test_cases" ).size();
}

void TestFixture::clear_test_cases()
{
    if ( is_empty() ) return;
    auto it = data()->find( "test_cases" );
    if ( it == data()->end() || it->is_null() )
    {
        data()->operator[]( "test_cases" ) = nlohmann::json::array();
    }
    else
    {
        it->clear();
    }
}

[[nodiscard]] runner::config::TestCase TestFixture::test_case_at( std::size_t index ) const
{
    if ( is_empty() ) throw std::runtime_error{ "Item cannot be accessed. Parent object is empty." };
    auto it = data()->find( "test_cases" );
    if ( it == data()->end() || it->is_null() ) return default_test_cases().at( index );
    auto& json_value = data()->at( "test_cases" ).at( index );
    return runner::config::TestCase{ &json_value };
}

void TestFixture::add_test_case( runner::config::TestCase test_case )
{
    if ( is_empty() ) throw std::runtime_error{ "Item cannot be added. Parent object is empty." };
    auto it = data()->find( "test_cases" );
    if ( it == data()->end() || it->is_null() )
    {
        if ( test_case.is_empty() ) return;
        data()->operator[]( "test_cases" ) = { *( test_case.data() ) };
    }
    else
    {
        if ( test_case.is_empty() ) return;
        it->emplace_back( *( test_case.data() ) );
    }
}

void TestFixture::remove_test_case_at( std::size_t index )
{
    if ( is_empty() ) return;
    auto it = data()->find( "test_cases" );
    if ( it == data()->end() || it->is_null() ) return;
    it->erase( index );
}


// "test_stages" property

[[nodiscard]] std::vector< runner::config::TestStage > TestFixture::test_stages() const
{
    if ( is_empty() ) return default_test_stages();
    auto it = data()->find( "test_stages" );
    if ( it == data()->end() || it->is_null() ) return default_test_stages();
    
    auto result = std::vector< runner::config::TestStage >{};
    result.reserve( it->size() );
    
    auto value_mapping = []( auto& value )
    {
        return runner::config::TestStage{ &value };
    };
    
    std::transform( it->begin(), it->end(), std::back_inserter( result ), value_mapping );
    return result;
}

[[nodiscard]] bool TestFixture::has_test_stages_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "test_stages" );
    return it != data()->end() && !it->is_null();
}

void TestFixture::reset_test_stages()
{
    if ( is_empty() ) return;
    data()->erase( "test_stages" );
}

void TestFixture::set_test_stages( std::vector< runner::config::TestStage > const& test_stages )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"test_stages\". Object is empty." };
    data()->operator[]( "test_stages" ) = nlohmann::json::array();
    auto& test_stages_arr =  data()->operator[]( "test_stages" );
    for ( auto el : test_stages )
    {
        test_stages_arr.emplace_back( *( el.data() ) );
    }
}
void TestFixture::set_test_stages( std::vector< runner::config::TestStage > && test_stages )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"test_stages\". Object is empty." };
    data()->operator[]( "test_stages" ) = nlohmann::json::array();
    auto& test_stages_arr =  data()->operator[]( "test_stages" );
    for ( auto el : test_stages )
    {
        test_stages_arr.emplace_back( *( el.data() ) );
    }
}
void TestFixture::set_test_stages( std::initializer_list< runner::config::TestStage > test_stages )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"test_stages\". Object is empty." };
    data()->operator[]( "test_stages" ) = nlohmann::json::array();
    auto& test_stages_arr =  data()->operator[]( "test_stages" );
    for ( auto el : test_stages )
    {
        test_stages_arr.emplace_back( *( el.data() ) );
    }
}

[[nodiscard]] bool TestFixture::are_test_stages_empty() const noexcept
{
    if ( is_empty() ) return true;
    return data()->at( "test_stages" ).empty();
}

[[nodiscard]] std::size_t TestFixture::test_stages_count() const noexcept
{
    if ( is_empty() ) return 0ull;
    return data()->at( "test_stages" ).size();
}

void TestFixture::clear_test_stages()
{
    if ( is_empty() ) return;
    auto it = data()->find( "test_stages" );
    if ( it == data()->end() || it->is_null() )
    {
        data()->operator[]( "test_stages" ) = nlohmann::json::array();
    }
    else
    {
        it->clear();
    }
}

[[nodiscard]] runner::config::TestStage TestFixture::test_stage_at( std::size_t index ) const
{
    if ( is_empty() ) throw std::runtime_error{ "Item cannot be accessed. Parent object is empty." };
    auto it = data()->find( "test_stages" );
    if ( it == data()->end() || it->is_null() ) return default_test_stages().at( index );
    auto& json_value = data()->at( "test_stages" ).at( index );
    return runner::config::TestStage{ &json_value };
}

void TestFixture::add_test_stage( runner::config::TestStage test_stage )
{
    if ( is_empty() ) throw std::runtime_error{ "Item cannot be added. Parent object is empty." };
    auto it = data()->find( "test_stages" );
    if ( it == data()->end() || it->is_null() )
    {
        if ( test_stage.is_empty() ) return;
        data()->operator[]( "test_stages" ) = { *( test_stage.data() ) };
    }
    else
    {
        if ( test_stage.is_empty() ) return;
        it->emplace_back( *( test_stage.data() ) );
    }
}

void TestFixture::remove_test_stage_at( std::size_t index )
{
    if ( is_empty() ) return;
    auto it = data()->find( "test_stages" );
    if ( it == data()->end() || it->is_null() ) return;
    it->erase( index );
}



} // end of namespace vortex::runner::config
