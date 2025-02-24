#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include "core/common/types.hpp"

namespace vortex::core::settings
{

class StaticSettingsDataStorage
{
public:
    StaticSettingsDataStorage() noexcept = default;

    StaticSettingsDataStorage( StaticSettingsDataStorage const& ) = delete;
    StaticSettingsDataStorage& operator=( StaticSettingsDataStorage const& ) = delete;
    StaticSettingsDataStorage( StaticSettingsDataStorage && ) = delete;
    StaticSettingsDataStorage& operator=( StaticSettingsDataStorage && ) = delete;

    ~StaticSettingsDataStorage() noexcept = default;

public:
    void * allocate( std::size_t byte_count );
    void deallocate( void * data_p );
    void clear() { m_allocs.clear(); }

private:
    std::unordered_map< std::uintptr_t, std::vector< byte > > m_allocs;
};

}
