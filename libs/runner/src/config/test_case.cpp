// 
// Source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include "runner/config/test_case.hpp"

#include <iomanip>
#include <sstream>

#include <nlohmann/json.hpp>

#include "runner/config/enums/parallel_strategy_type_json_integration.hpp"

namespace vortex::runner::config
{

TestCase::TestCase( nlohmann::json * data_p )
:   m_data_p( data_p )
{
    pre_validate_all();
}

TestCase& TestCase::update_with( nlohmann::json * other_data_p )
{
    if (!is_empty() && other_data_p != nullptr)
    {
        as_any().update_with( other_data_p );
        pre_validate_all();
    }
    return *this;
}

[[nodiscard]] std::string TestCase::to_string() const
{
    auto oss = std::ostringstream{};
    oss << *this;
    return oss.str();
}

std::ostream& TestCase::stringify( std::ostream& os, int indent_size, int indent_level, bool display_all ) const
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
    if ( display_all || has_template_name_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "template_name: " << template_name() << '\n';
    }
    if ( display_all || has_settings_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "settings:\n";
        settings().stringify( os, indent_size, indent_level + 1, display_all );
    }
    if ( display_all || has_parallel_strategy_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "parallel_strategy: " << to_c_str( parallel_strategy() ) << '\n';
    }
    if ( display_all || has_stages_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "stages:";
        auto const& stages_arr = stages();
        
        if ( stages_arr.empty() )
        {
            os << " <empty>\n";
        }
        else
        {
            os << '\n';
            for (auto const& el : stages_arr)
            {
                os << std::setw( indent_size * ( indent_level + 1 ) ) << "" << "-  " << el << '\n';
            }
        }
    }
    if ( display_all || has_process_count_set() )
    {
        os << std::setw( indent_size * indent_level ) << "" << "process_count: " << process_count() << '\n';
    }
    
    return os;
}

void TestCase::validate()
{
    if ( !has_name_set() )
    {
        throw std::runtime_error{ "Validation failed for property 'name': Required property is not specified." };
    }
    
}

void TestCase::pre_validate_all()
{
    if ( is_empty() ) return;
    
    if ( has_name_set() )
    {
        pre_validate_name( name() );
    }
    if ( has_template_name_set() )
    {
        pre_validate_template_name( template_name() );
    }
    if ( has_settings_set() )
    {
        pre_validate_settings( settings() );
    }
    if ( has_parallel_strategy_set() )
    {
        pre_validate_parallel_strategy( parallel_strategy() );
    }
    if ( has_stages_set() )
    {
        pre_validate_stages( stages() );
    }
    if ( has_process_count_set() )
    {
        pre_validate_process_count( process_count() );
    }
}

std::ostream& operator<<( std::ostream& os, TestCase const& s )
{
    return s.stringify( os, 2, 0, os.flags() & std::ios_base::boolalpha );
}

bool operator==( TestCase const& lhs, TestCase const& rhs )
{
    return lhs.is_empty()
        ? rhs.is_empty()
        : ( !rhs.is_empty() && *lhs.data() == *rhs.data() );
}

// "name" property

[[nodiscard]] std::string_view TestCase::name() const
{
    if ( is_empty() ) return default_name();
    auto it = data()->find( "name" );
    if ( it == data()->end() || it->is_null() ) return default_name();
    return std::string_view{ it->template get_ref<std::string const&>() };
}

[[nodiscard]] bool TestCase::has_name_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "name" );
    return it != data()->end() && !it->is_null();
}

void TestCase::reset_name()
{
    throw std::runtime_error{ "Property 'name' is required. It cannot be reset." };
}

void TestCase::set_name( std::string const& name )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"name\". Object is empty." };
    data()->operator[]( "name" ) = name;
}
void TestCase::set_name( std::string && name )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"name\". Object is empty." };
    data()->operator[]( "name" ) = name;
}

void TestCase::pre_validate_name( [[maybe_unused]] std::string_view name )
{
    if ( name.empty() )
    {
        throw std::runtime_error{ "Validation failed for property 'name': Value is empty." };
    }
    
}

// "template_name" property

[[nodiscard]] std::string_view TestCase::template_name() const
{
    if ( is_empty() ) return default_template_name();
    auto it = data()->find( "template_name" );
    if ( it == data()->end() || it->is_null() ) return default_template_name();
    return std::string_view{ it->template get_ref<std::string const&>() };
}

[[nodiscard]] bool TestCase::has_template_name_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "template_name" );
    return it != data()->end() && !it->is_null();
}

void TestCase::reset_template_name()
{
    if ( is_empty() ) return;
    data()->erase( "template_name" );
}

void TestCase::set_template_name( std::string const& template_name )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"template_name\". Object is empty." };
    data()->operator[]( "template_name" ) = template_name;
}
void TestCase::set_template_name( std::string && template_name )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"template_name\". Object is empty." };
    data()->operator[]( "template_name" ) = template_name;
}

void TestCase::pre_validate_template_name( [[maybe_unused]] std::string_view template_name )
{
    if ( template_name.empty() )
    {
        throw std::runtime_error{ "Validation failed for property 'template_name': Value is empty." };
    }
    
}

// "settings" property

[[nodiscard]] core::settings::json::AnySettings TestCase::settings() const
{
    if ( is_empty() ) return default_settings();
    auto it = data()->find( "settings" );
    if ( it == data()->end() || it->is_null() ) return default_settings();
    return core::settings::json::AnySettings{ &( *it ) };
}

[[nodiscard]] bool TestCase::has_settings_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "settings" );
    return it != data()->end() && !it->is_null();
}

void TestCase::reset_settings()
{
    if ( is_empty() ) return;
    data()->erase( "settings" );
}

void TestCase::set_settings( core::settings::json::AnySettings settings )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"settings\". Object is empty." };
    if ( settings.is_empty() )
    {
        reset_settings();
    }
    else
    {
        data()->operator[]( "settings" ) = *( settings.data() );
    }
}

void TestCase::pre_validate_settings( [[maybe_unused]] core::settings::json::AnySettings settings )
{}

// "parallel_strategy" property

[[nodiscard]] ParallelStrategyType TestCase::parallel_strategy() const
{
    if ( is_empty() ) return default_parallel_strategy();
    auto it = data()->find( "parallel_strategy" );
    if ( it == data()->end() || it->is_null() ) return default_parallel_strategy();
    return it->template get< ParallelStrategyType >();
}

[[nodiscard]] bool TestCase::has_parallel_strategy_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "parallel_strategy" );
    return it != data()->end() && !it->is_null();
}

void TestCase::reset_parallel_strategy()
{
    if ( is_empty() ) return;
    data()->erase( "parallel_strategy" );
}

void TestCase::set_parallel_strategy( ParallelStrategyType parallel_strategy )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"parallel_strategy\". Object is empty." };
    data()->operator[]( "parallel_strategy" ) = parallel_strategy;
}

void TestCase::pre_validate_parallel_strategy( [[maybe_unused]] ParallelStrategyType parallel_strategy )
{}

// "stages" property

[[nodiscard]] std::vector< std::string > TestCase::stages() const
{
    if ( is_empty() ) return default_stages();
    auto it = data()->find( "stages" );
    if ( it == data()->end() || it->is_null() ) return default_stages();
    
    auto result = std::vector< std::string >{};
    result.reserve( it->size() );
    
    auto value_mapping = []( auto& value )
    {
        return  value.template get< std::string >();
    };
    
    std::transform( it->begin(), it->end(), std::back_inserter( result ), value_mapping );
    return result;
}

[[nodiscard]] bool TestCase::has_stages_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "stages" );
    return it != data()->end() && !it->is_null();
}

void TestCase::reset_stages()
{
    if ( is_empty() ) return;
    data()->erase( "stages" );
}

void TestCase::set_stages( std::vector< std::string > const& stages )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"stages\". Object is empty." };
    data()->operator[]( "stages" ) = stages;
}
void TestCase::set_stages( std::vector< std::string > && stages )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"stages\". Object is empty." };
    data()->operator[]( "stages" ) = stages;
}
void TestCase::set_stages( std::initializer_list< std::string > stages )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"stages\". Object is empty." };
    data()->operator[]( "stages" ) = stages;
}

[[nodiscard]] bool TestCase::are_stages_empty() const noexcept
{
    if ( is_empty() ) return true;
    return data()->at( "stages" ).empty();
}

[[nodiscard]] std::size_t TestCase::stages_count() const noexcept
{
    if ( is_empty() ) return 0ull;
    return data()->at( "stages" ).size();
}

void TestCase::clear_stages()
{
    if ( is_empty() ) return;
    auto it = data()->find( "stages" );
    if ( it == data()->end() || it->is_null() )
    {
        data()->operator[]( "stages" ) = nlohmann::json::array();
    }
    else
    {
        it->clear();
    }
}

[[nodiscard]] std::string_view TestCase::stage_at( std::size_t index ) const
{
    if ( is_empty() ) throw std::runtime_error{ "Item cannot be accessed. Parent object is empty." };
    auto it = data()->find( "stages" );
    if ( it == data()->end() || it->is_null() ) return default_stages().at( index );
    auto& json_value = data()->at( "stages" ).at( index );
    return std::string_view{ json_value.template get_ref<std::string const&>() };
}

void TestCase::add_stage( std::string const& stage )
{
    if ( is_empty() ) throw std::runtime_error{ "Item cannot be added. Parent object is empty." };
    auto it = data()->find( "stages" );
    if ( it == data()->end() || it->is_null() )
    {
        data()->operator[]( "stages" ) = nullptr;
    }
    data()->operator[]( "stages" ).emplace_back( stage );
}
void TestCase::add_stage( std::string && stage )
{
    if ( is_empty() ) throw std::runtime_error{ "Item cannot be added. Parent object is empty." };
    auto it = data()->find( "stages" );
    if ( it == data()->end() || it->is_null() )
    {
        data()->operator[]( "stages" ) = nullptr;
    }
    data()->operator[]( "stages" ).emplace_back( stage );
}

void TestCase::remove_stage_at( std::size_t index )
{
    if ( is_empty() ) return;
    auto it = data()->find( "stages" );
    if ( it == data()->end() || it->is_null() ) return;
    it->erase( index );
}

void TestCase::remove_stage( std::string const& stage )
{
    if ( is_empty() ) return;
    auto it = data()->find( "stages" );
    if ( it == data()->end() || it->is_null() ) return;
    
    for ( auto arr_it = it->begin(); arr_it != it->end(); arr_it++ )
    {
        if (*arr_it == stage)
        {
            it->erase( arr_it );
            return;
        }
    }
}

void TestCase::remove_stage( std::string && stage )
{
    if ( is_empty() ) return;
    auto it = data()->find( "stages" );
    if ( it == data()->end() || it->is_null() ) return;
    
    for ( auto arr_it = it->begin(); arr_it != it->end(); arr_it++ )
    {
        if (*arr_it == stage)
        {
            it->erase( arr_it );
            return;
        }
    }
}


void TestCase::pre_validate_stages( [[maybe_unused]] std::vector< std::string > const& stages )
{}

void TestCase::pre_validate_stage( [[maybe_unused]] std::string_view stage )
{}

// "process_count" property

[[nodiscard]] i32 TestCase::process_count() const
{
    if ( is_empty() ) return default_process_count();
    auto it = data()->find( "process_count" );
    if ( it == data()->end() || it->is_null() ) return default_process_count();
    return it->template get< i32 >();
}

[[nodiscard]] bool TestCase::has_process_count_set() const noexcept
{
    if ( is_empty() ) return false;
    auto it = data()->find( "process_count" );
    return it != data()->end() && !it->is_null();
}

void TestCase::reset_process_count()
{
    if ( is_empty() ) return;
    data()->erase( "process_count" );
}

void TestCase::set_process_count( i32 process_count )
{
    if ( is_empty() ) throw std::runtime_error{ "Cannot set value for property \"process_count\". Object is empty." };
    data()->operator[]( "process_count" ) = process_count;
}

void TestCase::pre_validate_process_count( [[maybe_unused]] i32 process_count )
{
    auto value = process_count;
    if ( value < 1 )
    {
        throw std::runtime_error{ "Validation failed for property 'process_count': Value is not within required range." };
    }
    
}


} // end of namespace vortex::runner::config
