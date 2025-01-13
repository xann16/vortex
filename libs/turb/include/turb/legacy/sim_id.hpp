/*

#pragma once

#include <string>

#include "turbpp/core/Settings/Legacy/Metadata.h"
#include "turbpp/core/Settings/Legacy/Parameters.h"

namespace turb
{
  enum class PartAmountFormat
  {
    Number,
    MassLoading
  };

  class SimId
  {
  public:
    SimId() = default;

    explicit SimId(
      char flowId = 'a', ForcingType forcingType = ForcingType::Detemininistic,
      SimMethod simMethod = SimMethod::DNS,
      ParticleMode partMode = ParticleMode::None,
      GravityMode gravityMode = GravityMode::None,
      int partRadius = DEFAULT_PART_RADIUS,
      PartAmountFormat partAmountFormat = PartAmountFormat::Number,
      int partAmount = DEFAULT_PART_AMOUNT, int superpartFactor = 1,
      int adjustedNodeCount = 0, int adjustedSubdomainSize = 0 ) :
      m_forcingType( forcingType ),
      m_simMethod( simMethod ),
      m_partMode( partMode ),
      m_gravityMode( gravityMode ),
      m_partAmountFormat( partAmountFormat ),
      m_partRadius( partRadius ),
      m_partAmount( partAmount ),
      m_superpartFactor( superpartFactor ),
      m_adjustedNodeCount( adjustedNodeCount ),
      m_adjustedSubdomainSize( adjustedSubdomainSize ),
      m_flowId( flowId )
    {
      throwIfInvalid();
    }

    SimId( const char *id )
    {
      initFromString( id );
      throwIfInvalid();
    }

    SimId( std::string const &id ) : SimId( id.c_str() ) {}

    [[nodiscard]] char flowId() const { return m_flowId; }
    [[nodiscard]] ForcingType forcingType() const { return m_forcingType; }
    [[nodiscard]] SimMethod simMethod() const { return m_simMethod; }
    [[nodiscard]] ParticleMode partMode() const { return m_partMode; }
    [[nodiscard]] GravityMode gravityMode() const { return m_gravityMode; }
    [[nodiscard]] PartAmountFormat partAmountFormat() const
    {
      return m_partAmountFormat;
    }
    [[nodiscard]] int partRadius() const { return m_partRadius; }
    [[nodiscard]] int partAmount() const { return m_partAmount; }

    [[nodiscard]] int superpartFactor() const { return m_superpartFactor; }
    [[nodiscard]] int adjustedNodeCount() const { return m_adjustedNodeCount; }
    [[nodiscard]] int adjustedSubdomainSize() const
    {
      return m_adjustedSubdomainSize;
    }

    [[nodiscard]] bool isLES() const { return m_simMethod == SimMethod::LES; }
    [[nodiscard]] bool isFlowOnly() const
    {
      return m_partMode == ParticleMode::None;
    }
    [[nodiscard]] bool isTWC() const { return m_partMode == ParticleMode::TWC; }
    [[nodiscard]] bool hasGravity() const
    {
      return m_gravityMode != GravityMode::None;
    }

    [[nodiscard]] int N_part() const
    {
      if ( isFlowOnly() )
      {
        return 0;
      }
      if ( m_partAmountFormat == PartAmountFormat::Number )
      {
        return m_partAmount * PART_AMOUNT_MULTIPLIER;
      }
      throw std::runtime_error{
        "Mass loading based particle count calculation not implemented."
      };
    }

    [[nodiscard]] int N_part_eff() const
    {
      return N_part() / m_superpartFactor;
    }
    [[nodiscard]] double targetMassLoading() const
    {
      if ( isFlowOnly() || m_partAmountFormat == PartAmountFormat::Number )
      {
        return 0.0;
      }
      return static_cast< double >( m_partAmount ) * PART_PHI_RATIO;
    }

    [[nodiscard]] std::string toString() const;

  private:
    void throwIfInvalid() const;
    void initFromString( const char *id );
    void initFromStringBasePart( std::string const &base );

    static const int DEFAULT_PART_RADIUS = 40;
    static const int MAX_PART_RADIUS = 99;
    static const int DEFAULT_PART_AMOUNT = 20;
    static const int MAX_PART_AMOUNT = 9999;
    static const int NUMERIC_BASE = 10;
    static const int PART_RADIUS_STR_BEGIN = 5;
    static const int PART_RADIUS_STR_END = 7;
    static const int PART_AMOUNT_STR_BEGIN = 8;
    static const int PART_AMOUNT_STR_END = 12;
    static const int MAX_BASE_SIMID_LEN = 12;
    static const int PART_AMOUNT_MULTIPLIER = 100000;
    constexpr static const float PART_PHI_RATIO = 0.001f;

    ForcingType m_forcingType = ForcingType::Detemininistic;
    SimMethod m_simMethod = SimMethod::DNS;
    ParticleMode m_partMode = ParticleMode::None;
    GravityMode m_gravityMode = GravityMode::None;
    PartAmountFormat m_partAmountFormat = PartAmountFormat::Number;

    int m_partRadius = DEFAULT_PART_RADIUS;
    int m_partAmount = DEFAULT_PART_AMOUNT;

    int m_superpartFactor = 1;
    int m_adjustedNodeCount = 0;
    int m_adjustedSubdomainSize = 0;

    char m_flowId = 'a';
  };
}  // namespace turb

*/