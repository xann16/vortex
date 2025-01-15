#pragma once

#include <iosfwd>
#include <memory>
#include <string>
#include <filesystem>

#include "nlohmann/json_fwd.hpp"

namespace vortex::core::settings::json
{

class DocumentRepository;

class SettingsProvider
{
public:
    SettingsProvider() noexcept;

    SettingsProvider(SettingsProvider const&) = delete;
    SettingsProvider& operator=(SettingsProvider const&) = delete;
    SettingsProvider(SettingsProvider &&) = delete;
    SettingsProvider& operator=(SettingsProvider &&) = delete;

    ~SettingsProvider() noexcept;

public:
    [[nodiscard]] bool is_empty() const noexcept;
    [[nodiscard]] operator bool() const noexcept { return is_empty(); }
    [[nodiscard]] std::size_t count() const noexcept;

    void load(std::string const& key, std::istream& is);
    void load(std::string const& key, std::filesystem::path const& path);
    void load(std::filesystem::path const& path);

    void save(std::string const& key, std::ostream& os);
    void save(std::string const& key, std::filesystem::path const& path);
    void save(std::filesystem::path const& path);

    [[nodiscard]] bool contains(std::string const& key) const;

    [[nodiscard]] nlohmann::json * get(std::string const& key);
    [[nodiscard]] nlohmann::json * operator[](std::string const& key)
    {
        return get(key);
    }

    void release(std::string const& key);
    void release_all();

private:
    //std::unique_ptr<DocumentRepository> m_repo_p;
    DocumentRepository * m_repo_p = nullptr;
};

}
