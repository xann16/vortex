/*

#include "turbpp/core/Settings/Legacy/SimId.h"

#include <iomanip>
#include <sstream>

namespace turb
{
  void SimId::throwIfInvalid() const
  {
    if ( m_flowId != '\0' )
    {
      throw std::runtime_error{ "Invalid SimId: Flow ID must be defined" };
    }

    if ( !isFlowOnly() )
    {
      if ( m_partRadius <= 0 || m_partRadius > MAX_PART_RADIUS )
      {
        throw std::runtime_error{
          "Invalid SimId: Particle radius must be between 1 and 99."
        };
      }
      if ( m_partAmount <= 0 || m_partAmount > MAX_PART_AMOUNT )
      {
        throw std::runtime_error{
          "Invalid SimId: Particle amount must be between 1 and 9999."
        };
      }
      if ( m_superpartFactor <= 0 )
      {
        throw std::runtime_error{
          "Invalid SimId: Superparticle factor must be a positive integer."
        };
      }
    }
  }

  void SimId::initFromString( const char *id )
  {
    auto iss = std::istringstream{ id };
    auto token = std::string{};
    auto isBaseParsed = false;

    char *strend_p = nullptr;

    while ( std::getline( iss, token, '_' ) )
    {
      if ( !isBaseParsed )
      {
        initFromStringBasePart( token );
        isBaseParsed = true;
      }
      else if ( !token.empty() )
      {
        if ( token[ 0 ] == 'm' )
        {
          auto mStr = token.substr( 1 );
          m_superpartFactor = static_cast< int >(
            std::strtol( mStr.c_str(), &strend_p, NUMERIC_BASE ) );
        }
        else if ( token[ 0 ] == 'p' && token.length() > 1 )
        {
          if ( token[ 1 ] == 'n' )
          {
            auto pnStr = token.substr( 2 );
            m_adjustedNodeCount = static_cast< int >(
              std::strtol( pnStr.c_str(), &strend_p, NUMERIC_BASE ) );
          }
          else if ( token[ 1 ] == 's' )
          {
            auto psStr = token.substr( 2 );
            m_adjustedSubdomainSize = static_cast< int >(
              std::strtol( psStr.c_str(), &strend_p, NUMERIC_BASE ) );
          }
          else
          {
            throw std::runtime_error{
              std::string{ "Invalid SimId: Unrecognized extra part: '" } +
              token + '\''
            };
          }
        }
        else
        {
          throw std::runtime_error{
            std::string{ "Invalid SimId: Unrecognized extra part: '" } + token +
            '\''
          };
        }
      }
    }
  }

  void SimId::initFromStringBasePart( std::string const &base )
  {
    if ( base.length() < 4 )
    {
      throw std::runtime_error{ "Invalid SimId: SimId base part is too short "
                                "(must have at least 4 characters." };
    }

    m_flowId = base[ 0 ];

    switch ( base[ 1 ] )
    {
    case 'd':
      m_forcingType = ForcingType::Detemininistic;
      break;
    case 's':
      m_forcingType = ForcingType::Stochastic;
      break;
    default:
      throw std::runtime_error{
        "Invalid SimId: Unrecognized token for forcing type ( must be either d "
        "(deterministic) or s (stochastic)."
      };
    }

    switch ( base[ 2 ] )
    {
    case 'd':
      m_simMethod = SimMethod::DNS;
      break;
    case 'l':
      m_simMethod = SimMethod::LES;
      break;
    case 'f':
      m_simMethod = SimMethod::FNS;
      break;
    default:
      throw std::runtime_error{
        "Invalid SimId: Unrecognized token for simulation method ( must be "
        "either d (DNS), l (LES), or f (fDNS)."
      };
    }

    switch ( base[ 3 ] )
    {
    case 'f':
      m_partMode = ParticleMode::None;
      break;
    case 'o':
      m_partMode = ParticleMode::OWC;
      break;
    case 't':
      m_partMode = ParticleMode::TWC;
      break;
    default:
      throw std::runtime_error{
        "Invalid SimId: Unrecognized token for particle mode ( must be either "
        "f (flow-only), o (OWC), or t (TWC)."
      };
    }

    if ( isFlowOnly() && base.length() > 4 )
    {
      throw std::runtime_error{
        "Invalid SimId: SimId base part is too long (for flow only simulation "
        "it must be exactly 4 characters)."
      };
    }
    if ( !isFlowOnly() && base.length() != MAX_BASE_SIMID_LEN )
    {
      throw std::runtime_error{
        "Invalid SimId: SimId base part has invalid length (for simulations "
        "with particles it must be exactly 12 characters)."
      };
    }

    switch ( base[ 4 ] )
    {
    case 'n':
      m_gravityMode = GravityMode::None;
      break;
    case 'g':
      m_gravityMode = GravityMode::Vertical;
      break;
    case 'h':
      m_gravityMode = GravityMode::Horizontal;
      break;
    default:
      throw std::runtime_error{
        "Invalid SimId: Unrecognized token for gravity mode ( must be either n "
        "(no gravity), g (vertical), or h (horizontal)."
      };
    }

    auto radiusStr = base.substr( PART_RADIUS_STR_BEGIN, PART_RADIUS_STR_END );
    char *strend_p = nullptr;

    m_partRadius = static_cast< int >(
      std::strtol( radiusStr.c_str(), &strend_p, NUMERIC_BASE ) );

    switch ( base[ PART_RADIUS_STR_END ] )
    {
    case 'n':
      m_partAmountFormat = PartAmountFormat::Number;
      break;
    case 'p':
      m_partAmountFormat = PartAmountFormat::MassLoading;
      break;
    default:
      throw std::runtime_error{
        "Invalid SimId: Unrecognized token for particle amount format ( must "
        "be either n (number of particles times 100k) or p (by mass loading "
        "times 0.001)."
      };
    }

    auto npStr = base.substr( PART_AMOUNT_STR_BEGIN, PART_AMOUNT_STR_END );
    m_partAmount = static_cast< int >(
      std::strtol( npStr.c_str(), &strend_p, NUMERIC_BASE ) );
  }


  std::string SimId::toString() const
  {
    // if (m_isTemplate) return "<template>";

    auto oss = std::ostringstream{};

    oss << m_flowId
        << ( ( m_forcingType == ForcingType::Detemininistic ) ? 'd' : 's' )
        << ( ( ( m_simMethod == SimMethod::DNS ) ? 'd'
                                                 : ( isLES() ? 'l' : 'f' ) ) )
        << ( ( isFlowOnly() ? 'f' : ( isTWC() ? 't' : 'o' ) ) );

    if ( !isFlowOnly() )
    {
      oss << ( ( ( m_gravityMode == GravityMode::None )
                   ? 'n'
                   : ( ( m_gravityMode == GravityMode::Vertical ) ? 'g'
                                                                  : 'h' ) ) )
          << std::setfill( '0' ) << std::setw( 2 ) << m_partRadius
          << ( ( m_partAmountFormat == PartAmountFormat::Number ) ? 'n' : 'p' )
          << std::setfill( '0' ) << std::setw( 4 ) << m_partAmount;
    }

    if ( m_superpartFactor > 1 )
    {
      oss << "_m" << m_superpartFactor;
    }
    if ( m_adjustedNodeCount != 0 )
    {
      oss << "_pn" << m_adjustedNodeCount;
    }
    if ( m_adjustedSubdomainSize != 0 )
    {
      oss << "_ps" << m_adjustedSubdomainSize;
    }

    return oss.str();
  }
}  // namespace turb

*/
