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

    SettingsProvider( SettingsProvider const& ) = delete;
    SettingsProvider& operator=( SettingsProvider const& ) = delete;
    SettingsProvider( SettingsProvider && ) = delete;
    SettingsProvider& operator=( SettingsProvider && ) = delete;

protected:
    ~SettingsProvider() noexcept;

public:
    [[nodiscard]] bool is_empty() const noexcept;
    [[nodiscard]] operator bool() const noexcept { return is_empty(); }
    [[nodiscard]] std::size_t count() const noexcept;

    void add( std::filesystem::path const& key, nlohmann::json * obj_p );
    void add_and_save( std::filesystem::path const& key, nlohmann::json * obj_p );
    void add_and_save( std::filesystem::path const& key, nlohmann::json * obj_p, std::ostream& os );

    void load( std::filesystem::path const& key, std::istream& is );
    void load( std::filesystem::path const& key );

    void save( std::filesystem::path const& key, std::ostream& os );
    void save( std::filesystem::path const& key );

    [[nodiscard]] bool contains( std::filesystem::path const& key ) const;

    void release( std::filesystem::path const& key );
    void release_all();

protected:
    [[nodiscard]] nlohmann::json * get_object_pointer( std::filesystem::path const& key );

    template < typename T >
    [[nodiscard]] T get( std::filesystem::path const& key, nlohmann::json * obj_p )
    {
        if ( !contains( key ) )
        {
            add( key, obj_p );
        }
        return T{ get_object_pointer( key ) };
    }

    template < typename T >
    [[nodiscard]] T get( std::filesystem::path const& key, std::istream& is )
    {
        if ( !contains( key ) )
        {
            load( key, is );
        }
        return T{ get_object_pointer( key ) };
    }

    template < typename T >
    [[nodiscard]] T get( std::filesystem::path const& key )
    {
        if ( !contains( key ) )
        {
            load( key );
        }
        return T{ get_object_pointer( key ) };
    }

private:
    DocumentRepository * m_repo_p = nullptr;
};

}
