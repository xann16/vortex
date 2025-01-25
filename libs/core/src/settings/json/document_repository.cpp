#include "core/settings/json/document_repository.hpp"

#include <istream>
#include <ostream>
#include <utility>

#include "nlohmann/json.hpp"

namespace vortex::core::settings::json
{

void DocumentRepository::add( std::filesystem::path const& key, nlohmann::json * obj_p )
{
    if ( contains( key ) )
    {
        throw std::out_of_range{ "JSON Document Repository: Trying to insert duplicate key." };
    }
    m_docs.emplace(key, *obj_p);
}

void DocumentRepository::load( std::filesystem::path const& key, std::istream& is )
{
    if ( contains( key ) )
    {
        throw std::out_of_range{ "JSON Document Repository: Trying to insert duplicate key." };
    }
    m_docs.emplace( key, nlohmann::json::parse( is ) );
}

void DocumentRepository::save( std::filesystem::path const& key, std::ostream& os )
{
    auto doc = get( key );
    if ( output_indent() )
    {
        os << std::setw( static_cast< int >( output_indent() ) );
    }
    os << doc << std::endl;
}

}
