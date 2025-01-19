#pragma once

#include <exception>
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

    void release(std::string const& key);
    void release_all();

protected:
    [[nodiscard]] nlohmann::json * get_object_pointer(std::string const& key);

    template <typename Settings>
    [[nodiscard]] Settings get_impl(std::string const& key)
    {
        return Settings{get_object_pointer(key)};
    }

    template <typename Settings>
    [[nodiscard]] Settings get(std::string const& key, std::istream& is)
    {
        if (!contains(key))
        {
            load(key, is);
        }
        return get_impl<Settings>(key);
    }

    template <typename Settings>
    [[nodiscard]] Settings get(std::string const& key, std::filesystem::path const& path)
    {
        if (!contains(key))
        {
            load(key, path);
        }
        return get_impl<Settings>(key);
    }

    template <typename Settings>
    [[nodiscard]] Settings get(std::filesystem::path const& path)
    {
        auto const& key = path.string();
        if (!contains(key))
        {
            load(key, path);
        }
        return get_impl<Settings>(key);
    }

    template <typename Settings>
    [[nodiscard]] Settings get(std::string const& key)
    {
        if (!contains(key))
        {
            throw std::out_of_range{"JSON Settings Provider: Key not found."};
        }
        return get_impl<Settings>(key);
    }

private:
    //std::unique_ptr<DocumentRepository> m_repo_p;
    DocumentRepository * m_repo_p = nullptr;
};

}
