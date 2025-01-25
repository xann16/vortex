#include "core/settings/json/settings_provider.hpp"

#include <fstream>
#include <memory>
#include <string>
#include <filesystem>

#include "nlohmann/json.hpp"

#include "core/settings/json/document_repository.hpp"

namespace vortex::core::settings::json
{

SettingsProvider::SettingsProvider() noexcept
    : m_repo_p( new DocumentRepository() )
{}

SettingsProvider::~SettingsProvider() noexcept
{
    delete m_repo_p;
}

[[nodiscard]] bool SettingsProvider::is_empty() const noexcept
{
    return m_repo_p->is_empty();
}

[[nodiscard]] std::size_t SettingsProvider::count() const noexcept
{
    return m_repo_p->count();
}

void SettingsProvider::add( std::filesystem::path const& key, nlohmann::json * obj_p )
{
    m_repo_p->add( key, obj_p );
}

void SettingsProvider::add_and_save( std::filesystem::path const& key, nlohmann::json * obj_p )
{
    add( key, obj_p );
    save( key );
}

void SettingsProvider::add_and_save( std::filesystem::path const& key, nlohmann::json * obj_p, std::ostream& os )
{
    add( key, obj_p );
    save( key, os );
}

void SettingsProvider::load( std::filesystem::path const& key, std::istream& is )
{
    m_repo_p->load( key, is );
}

void SettingsProvider::load( std::filesystem::path const& key )
{
    auto ifs = std::ifstream{ key };
    load( key, ifs );
}

void SettingsProvider::save( std::filesystem::path const& key, std::ostream& os )
{
    m_repo_p->save( key, os );
}

void SettingsProvider::save( std::filesystem::path const& key )
{
    auto ofs = std::ofstream{ key };
    save( key, ofs );
}

[[nodiscard]] bool SettingsProvider::contains(std::filesystem::path const& key) const
{
    return m_repo_p->contains( key );
}

[[nodiscard]] nlohmann::json * SettingsProvider::get_object_pointer( std::filesystem::path const& key )
{
    return &( m_repo_p->get( key ) );
}

void SettingsProvider::release( std::filesystem::path const& key )
{
    m_repo_p->release( key );
}

void SettingsProvider::release_all()
{
    m_repo_p->clear();
}

}
