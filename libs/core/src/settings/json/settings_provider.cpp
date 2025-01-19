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
    : m_repo_p(new DocumentRepository())
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

void SettingsProvider::load(std::string const& key, std::istream& is)
{
    m_repo_p->load( key, is );
}

void SettingsProvider::load(std::string const& key, std::filesystem::path const& path)
{
    auto ifs = std::ifstream{ path };
    load( key, ifs );
}

void SettingsProvider::load(std::filesystem::path const& path)
{
    load( path.string(), path );
}

void SettingsProvider::save(std::string const& key, std::ostream& os)
{
    m_repo_p->save( key, os );
}

void SettingsProvider::save(std::string const& key, std::filesystem::path const& path)
{
    auto ofs = std::ofstream{ path };
    save( key, ofs );
}

void SettingsProvider::save(std::filesystem::path const& path)
{
    save( path.string(), path );
}

[[nodiscard]] bool SettingsProvider::contains(std::string const& key) const
{
    return m_repo_p->contains(key);
}

[[nodiscard]] nlohmann::json * SettingsProvider::get_object_pointer(std::string const& key)
{
    return &(m_repo_p->get(key));
}

void SettingsProvider::release(std::string const& key)
{
    m_repo_p->release(key);
}

void SettingsProvider::release_all()
{
    m_repo_p->clear();
}

}
