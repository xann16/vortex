// 
// Header file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#pragma once

#include <nlohmann/json_fwd.hpp>

namespace vortex::runner::config
{

class TestStage
{
public:
    explicit TestStage( nlohmann::json * data_p );

private:
    nlohmann::json * m_data_p = nullptr;
}; // end of class TestStage

} // end of namespace vortex::runner::config
