// 
// Header file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#pragma once

#include <nlohmann/json.hpp>

#include "runner/config/enums/parallel_strategy_type.hpp"

namespace vortex::runner::config
{

NLOHMANN_JSON_SERIALIZE_ENUM( ParallelStrategyType,
{
    { ParallelStrategyType::Mmx, "mmx" },
    { ParallelStrategyType::Mxx, "mxx" },
    { ParallelStrategyType::Xxx, "xxx" },
})

} // end of namespace vortex::runner::config
