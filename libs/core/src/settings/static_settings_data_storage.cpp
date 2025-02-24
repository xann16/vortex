#include "core/settings/static_settings_data_storage.hpp"

namespace vortex::core::settings
{
    void * StaticSettingsDataStorage::allocate( std::size_t byte_count )
    {
        auto data_storage = std::vector< byte >{};
        data_storage.resize( byte_count );
        const auto data_p = data_storage.data();
        const auto key = reinterpret_cast< std::uintptr_t >( data_p );

        // NOTE: key uniqueness guaranteed by underlying (system) allocator
        m_allocs.emplace( key, std::move( data_storage ) );

        return static_cast< void * >( data_p );
    }

    void StaticSettingsDataStorage::deallocate( void * data_p )
    {
        m_allocs.erase( reinterpret_cast< std::uintptr_t >( data_p ) );
    }

};
