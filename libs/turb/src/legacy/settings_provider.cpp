/*

#include "turbpp/core/Settings/Legacy/LegacySettingsProvider.h"

#include <fstream>
#include <sstream>
#include <string>

#include <string>

namespace turb
{

  Settings LegacySettingsProvider::load( std::filesystem::path const &basePath )
  {
    auto result = Settings{};

    result.params() = loadParameters( basePath / "code" / "parameter.d" );
    result.metadata() = loadMetadata( basePath, result.params() );
    result.exec() = loadExecutionSettings( basePath / "code" / "RUN" );

    return result;
  }

  Parameters
  LegacySettingsProvider::loadParameters( std::filesystem::path const &path,
                                          bool isExtended )
  {
    auto p = Parameters{};
    auto ifs = std::ifstream{ path };

    readGridSize( ifs, p.N, isExtended );
    readProcCount( ifs, p.N_subdomain, isExtended );
    readInteger( ifs, p.Nt_max );
    readReal( ifs, p.dt );
    readReal( ifs, p.rnu );
    readReal( ifs, p.t_init );
    readBoolean( ifs, p.isFlowGenerated );
    if ( isExtended )
    {
      readInteger( ifs, p.deterministicSeed );
      readInteger( ifs, p.inputVeloIndex );
    }
    else
    {
      readInteger( ifs, p.inputVeloIndex );
      readInteger( ifs, p.deterministicSeed );
    }
    readForcingType( ifs, p.forcingType );
    readDeterministicForce( ifs, p.deterministicForcing_k_1,
                            p.deterministicForcing_k_2 );
    readInteger( ifs, p.stochasticSeed );
    readInteger( ifs, p.statsOutputInterval );
    readInteger( ifs, p.spectrumOutputInterval );
    readBoolean( ifs, p.isStatsOutputExtended );
    readReal( ifs, p.rho_part );
    readReal( ifs, p.rho_fluid );
    readKolmogorovParams( ifs, p.eta_k_init, p.tau_k_init, isExtended );
    readReal( ifs, p.shellThickness );
    readReal( ifs, p.epsilon_env );
    readReal( ifs, p.nu_fluid );
    readReal( ifs, p.gravity );
    readBoolean( ifs, p.isPartGenerated );
    readBoolean( ifs, p.isPartOverlapping );
    readBoolean( ifs, p.isPartHdiEnabled );
    readReal( ifs, p.partHdiTruncRadius );
    readInteger( ifs, p.N_part );
    readDragType( ifs, p.dragType );
    readPartSetCount( ifs );
    readReal( ifs, p.a );

    p.isPartOverlapping = !p.isPartOverlapping;

    return p;
  }

  Metadata
  LegacySettingsProvider::loadMetadata( std::filesystem::path const &basePath,
                                        Parameters const &p )
  {
    auto isNew = isPathNew( basePath );
    auto result = Metadata{};

    auto codePath = basePath / "code";

    parseTurbCode( codePath / "turb.f90", result, p, isNew );
    extractGravityMode( codePath / "partlib.f90", result, p.gravity != 0.0 );
    extractPerfFlags( basePath, result, isNew );
    // parseNameAndValidate( basePath, result, isNew );

    return result;
  }

  ExecutionSettings LegacySettingsProvider::loadExecutionSettings(
    std::filesystem::path const &path )
  {
    auto e = ExecutionSettings{};
    auto ifs = std::ifstream{ path };

    auto line = std::string{};
    while ( std::getline( ifs, line ) )
    {
      if ( line.find( "srun" ) == std::string::npos )
      {
        parseRunBatchOption( line, e );
      }
      else
      {
        parseSrunCommandLine( line, e );
      }
    }

    return e;
  }



  void
  LegacySettingsProvider::saveParameters( std::filesystem::path const &path,
                                          Parameters const &p, bool isExtended )
  {
    auto ofs = std::ofstream{ path };

    writeGridSize( ofs, p.N, isExtended );
    writeProcCount( ofs, p.N_subdomain, isExtended );
    writeInteger( ofs, p.Nt_max,
                  isExtended ? "Number of time steps"
                             : "total number of time steps" );
    writeReal( ofs, p.dt, "dt" );
    writeReal( ofs, p.rnu, "rnu" );
    writeReal( ofs, p.t_init, isExtended ? "initial time" : "Initial time" );
    writeBoolean( ofs, p.isFlowGenerated,
                  isExtended ? "new flow?" : "New flow ?", isExtended );
    if ( isExtended )
    {
      writeInteger( ofs, p.deterministicSeed,
                    "Seed for initial flow in case of deterministic forcing" );
      writeInteger( ofs, p.inputVeloIndex, "Velocity start point" );
    }
    else
    {
      writeInteger( ofs, p.inputVeloIndex, "idp - velocity start point" );
      writeInteger( ofs, p.deterministicSeed,
                    "Seed for initial flow in case of deterministic forcing" );
    }
    writeForcingType( ofs, p.forcingType, isExtended );
    writeDeterministicForce( ofs, p.deterministicForcing_k_1,
                             p.deterministicForcing_k_2, isExtended );
    writeInteger( ofs, p.stochasticSeed,
                  "Seeding for stochastic forcing scheme" );
    writeInteger( ofs, p.statsOutputInterval,
                  isExtended
                    ? "Save turbulence statistics every Y time steps, Y="
                    : "save turbulence statistics every Y time steps, Y = " );
    writeInteger( ofs, p.spectrumOutputInterval,
                  isExtended ? "Save spectrum every X time steps, X="
                             : "save spectrum every X time steps, X=" );
    writeBoolean( ofs, p.isStatsOutputExtended,
                  "Want divergence velocity and other statistics?",
                  isExtended );
    writeReal( ofs, p.rho_part,
               isExtended ? "water density [g/cm3]" : "rho_water [g/cm3]" );
    writeReal( ofs, p.rho_fluid,
               isExtended ? "air density [g/cm3]" : "rho_air [g/cm3]" );
    writeKolmogorovParams( ofs, p.eta_k_init, p.tau_k_init, isExtended );
    writeReal( ofs, p.shellThickness,
               isExtended ? "shell thickness in %" : "shell thickness" );
    writeReal( ofs, p.epsilon_env, "energy dissipation rate [cm2/s3]" );
    writeReal( ofs, p.nu_fluid, "air viscosity [cm2/s]" );
    writeReal( ofs, p.gravity, "gravity[cm / s2]" );
    writeBoolean( ofs, p.isPartGenerated,
                  isExtended
                    ? "New particles?"
                    : "Generate new particles? If .FALSE., read from disc.",
                  isExtended );
    writeBoolean( ofs, !p.isPartOverlapping,
                  isExtended ? "nonoverlapping particles ?"
                             : "Nonoverlapping particles?",
                  isExtended );
    writeBoolean( ofs, p.isPartHdiEnabled,
                  isExtended ? "HDI included ?" : "HDI included?", isExtended );
    writeReal( ofs, p.partHdiTruncRadius,
               isExtended ? "HDI truncation radius ?"
                          : "HDI truncation radius (r/a)?" );
    writeInteger( ofs, p.N_part,
                  isExtended ? "Total number of particles?"
                             : "Total number of particles, npart=" );
    writeDragType( ofs, p.dragType );
    writePartSetCount( ofs, isExtended );
    writeReal( ofs, p.a, "particle radii in [um]" );
  }

  void LegacySettingsProvider::saveMetadata( std::filesystem::path const &path,
                                             Metadata const &m )
  {
    auto ofs = std::ofstream{ path };

    writeSimulationMethod( ofs, m.simMethod );
    writeParticleMode( ofs, m.particleMode );
    writeGravityDirection( ofs, m.gravityMode );
    writeTwcKernelType( ofs, m.particleTwcKernelType );
    writeInteger( ofs, m.k_filter,
                  "Filtering wavenumber threshold (fDNS-only):" );
    writeReal( ofs, m.C_K, "Subgrid-scale model C_K parameter (LES-only)" );
    writeReal( ofs, m.superpartFactor, "Superparticle factor, M =" );
    writeString( ofs, m.srcFlowPath,
                 "Full path for flow data source directory:" );
    writeString( ofs, m.srcPartPath,
                 "Full path for particle data source directory:" );
    writeInteger(
      ofs, m.partOutputDelay,
      "No. of iterations after which particle statistics are gathered:" );
    writeBoolean( ofs, m.isPerfPartDistEnabled,
                  "Is gathering particle distribution in subdomains enabled?" );
    writeBoolean( ofs, m.isPerfSimpleEnabled,
                  "Is gathering of simple timings enabled?" );
    writeBoolean( ofs, m.isPerfFullProfileEnabled,
                  "Is gathering of full profile data enabled?" );
    writeInteger(
      ofs, m.perfFullStart,
      "Iteeration at which gathering of full profile data starts:" );
    writeInteger( ofs, m.perfFullEnd,
                  "Iteeration at which gathering of full profile data stops:" );
    writeInteger( ofs, m.partPerfInterval,
                  "Particle distribution data gathered every every X steps:" );
  }


  void LegacySettingsProvider::saveExecutionSettings(
    std::filesystem::path const &path, ExecutionSettings const &e )
  {
    auto ofs = std::ofstream{ path };

    ofs << "#!/bin/tcsh\n"
        << "#SBATCH --job-name " << e.jobName << '\n'
        << "#SBATCH --output=\"output\"\n"
        << "#SBATCH --error \"error\"\n"
        << "#SBATCH --account \"" << e.grantNo << "\"\n"
        << "#SBATCH --nodes " << e.cpuNodeCount << '\n'
        << "#SBATCH --time ";
    writeWctDurationInMinutes( ofs, e.wctLimit );
    ofs << "\n\n"
        << "srun -n " << e.processCount
        << ( e.isNodeOvercommitEnabled ? " --overcommit " : " " ) << "./turb\n";
  }



  std::istream &LegacySettingsProvider::readInteger( std::istream &is,
                                                     int &outputValue )
  {
    skipLine( is ) >> outputValue;
    return skipLine( is );
  }

  std::istream &LegacySettingsProvider::readReal( std::istream &is,
                                                  double &outputValue )
  {
    skipLine( is ) >> outputValue;
    return skipLine( is );
  }

  std::istream &LegacySettingsProvider::readBoolean( std::istream &is,
                                                     bool &outputValue )
  {
    auto c = char{};
    skipLine( is ) >> c;
    if ( c == '.' )
    {
      is >> c;
    }
    outputValue = c == 't' || c == 'T';
    return skipLine( is );
  }

  std::istream &LegacySettingsProvider::readGridSize( std::istream &is,
                                                      int &outputValue,
                                                      bool isExtended )
  {
    if ( isExtended )
    {
      skipLine( is );
    }

    auto nx = 0;
    auto ny = 0;
    auto nz = 0;

    is >> nx >> ny >> nz;
    if ( !( nx == ny && ny == nz ) )
    {
      throw std::runtime_error{
        "Grid sizes have to be equal in all dimensions."
      };
    }
    outputValue = nx;
    return skipLine( is );
  }

  std::istream &LegacySettingsProvider::readProcCount( std::istream &is,
                                                       int &outputValue,
                                                       bool isExtended )
  {
    skipLine( is );

    auto npx = 0;
    is >> npx;
    if ( isExtended )
    {
      auto npy = 0;
      is >> npy;
      if ( npx != npy )
      {
        throw std::runtime_error{
          "Processor counts have to be equal in all dimensions."
        };
      }
    }
    outputValue = npx;
    return skipLine( is );
  }

  std::istream &LegacySettingsProvider::readDeterministicForce(
    std::istream &is, double &outputValue_k1, double &outputValue_k2 )
  {
    skipLine( is ) >> outputValue_k1 >> outputValue_k2;
    return skipLine( is );
  }

  std::istream &LegacySettingsProvider::readKolmogorovParams(
    std::istream &is, double &outputValue_eta, double &outputValue_tau,
    bool isExtended )
  {
    skipLine( is ) >> outputValue_eta;
    if ( !isExtended )
    {
      is.ignore( std::numeric_limits< std::streamsize >::max(), ' ' );
    }
    is >> outputValue_tau;
    return skipLine( is );
  }

  std::istream &
  LegacySettingsProvider::readForcingType( std::istream &is,
                                           ForcingType &outputValue )
  {
    auto numValue = 0;
    skipLine( is ) >> numValue;
    if ( numValue < 1 || numValue > 2 )
    {
      throw std::runtime_error{
        "Unsupported forcing type numeric identifer. Must be 1 - "
        "deterministic; or 2 - stochastic."
      };
    }
    outputValue =
      numValue == 1 ? ForcingType::Detemininistic : ForcingType::Stochastic;
    return skipLine( is );
  }

  std::istream &LegacySettingsProvider::readDragType( std::istream &is,
                                                      DragType &outputValue )
  {
    auto numValue = 0;
    skipLine( is ) >> numValue;
    if ( numValue < 0 || numValue > 1 )
    {
      throw std::runtime_error{ "Unsupported drag type numeric identifer. Must "
                                "be 0 - Stokes; or 1 - nonlinear." };
    }
    outputValue = numValue == 0 ? DragType::Stokes : DragType::Nonlinear;
    return skipLine( is );
  }

  std::istream &LegacySettingsProvider::readPartSetCount( std::istream &is )
  {
    auto setCount = 0;
    skipLine( is ) >> setCount;
    if ( setCount != 1 )
    {
      throw std::runtime_error{
        "Unsupported number of particle sets. Must be 1."
      };
    }
    return skipLine( is );
  }



  std::ostream &LegacySettingsProvider::writeInteger( std::ostream &os,
                                                      int inputValue,
                                                      char const *description )
  {
    return os << description << '\n' << inputValue << '\n';
  }

  std::ostream &
  LegacySettingsProvider::writeReal( std::ostream &os, double inputValue,
                                     char const *description,
                                     [[maybe_unused]] bool isExtended )
  {
    return os << description << '\n' << inputValue << '\n';
  }

  std::ostream &LegacySettingsProvider::writeBoolean( std::ostream &os,
                                                      bool inputValue,
                                                      char const *description,
                                                      bool isExtended )
  {
    return os << description << '\n'
              << ( isExtended ? ( inputValue ? "T" : "F" )
                              : ( inputValue ? ".TRUE." : ".FALSE." ) )
              << '\n';
  }

  std::ostream &LegacySettingsProvider::writeString(
    std::ostream &os, std::string const &inputValue, char const *description )
  {
    return os << description << '\n' << inputValue << '\n';
  }



  std::ostream &LegacySettingsProvider::writeGridSize( std::ostream &os,
                                                       int inputValue,
                                                       bool isExtended )
  {
    if ( isExtended )
    {
      os << "nx, ny, nz\n";
    }
    return os << inputValue << ' ' << inputValue << ' ' << inputValue << '\n';
  }

  std::ostream &LegacySettingsProvider::writeProcCount( std::ostream &os,
                                                        int inputValue,
                                                        bool isExtended )
  {
    os << ( isExtended
              ? "Number of processors along Y-array and Z-array direction\n"
              : "number of processors along Y-array direction\n" )
       << inputValue;
    if ( isExtended )
    {
      os << ' ' << inputValue;
    }
    return os << '\n';
  }

  std::ostream &LegacySettingsProvider::writeDeterministicForce(
    std::ostream &os, double inputValue_k1, double inputValue_k2,
    bool isExtended )
  {
    return os << ( isExtended ? "Force for deterministic forcing scheme\n"
                              : "Force in case of deterministic forcing\n" )
              << inputValue_k1 << ( isExtended ? ' ' : '\n' ) << inputValue_k2
              << '\n';
  }

  std::ostream &LegacySettingsProvider::writeKolmogorovParams(
    std::ostream &os, double inputValue_eta, double inputValue_tau,
    bool isExtended )
  {
    return os << "DNS kolmogorov parameters: eta,time\n"
              << inputValue_eta << ( isExtended ? " " : ", " ) << inputValue_tau
              << '\n';
  }

  std::ostream &LegacySettingsProvider::writeForcingType(
    std::ostream &os, ForcingType inputValue, bool isExtended )
  {
    return os << ( isExtended
                     ? "Forcing scheme: 1 deterministic, 2 stochastic\n"
                     : "forcing scheme: 1 deterministic, 2 stochastic\n" )
              << ( inputValue == ForcingType::Detemininistic ? 1 : 2 ) << '\n';
  }

  std::ostream &LegacySettingsProvider::writeDragType( std::ostream &os,
                                                       DragType inputValue )
  {
    return os << "drag 0-Stokes 1-nonlinear\n"
              << ( inputValue == DragType::Stokes ? 0 : 1 ) << '\n';
  }

  std::ostream &LegacySettingsProvider::writePartSetCount( std::ostream &os,
                                                           bool isExtended )
  {
    return os << "number of particle sets" << ( isExtended ? ' ' : '?' )
              << "\n1\n";
  }

  std::ostream &
  LegacySettingsProvider::writeSimulationMethod( std::ostream &os,
                                                 SimMethod simMethod )
  {
    const auto simMethodId =
      simMethod == SimMethod::DNS ? 0 : ( simMethod == SimMethod::LES ? 1 : 2 );
    return writeInteger( os, simMethodId,
                         "Simulation method (0 - DNS, 1 - LES, 2 - fDNS):" );
  }

  std::ostream &
  LegacySettingsProvider::writeParticleMode( std::ostream &os,
                                             ParticleMode partMode )
  {
    return writeBoolean( os, partMode == ParticleMode::TWC,
                         "Is two-way momentum coupling enabled:" );
  }

  std::ostream &
  LegacySettingsProvider::writeGravityDirection( std::ostream &os,
                                                 GravityMode gravMode )
  {
    return writeBoolean( os, gravMode == GravityMode::Horizontal,
                         "Is gravity direction horizontal (i.e. orthogonal to "
                         "subdomain partition axis):" );
  }

  std::ostream &LegacySettingsProvider::writeTwcKernelType(
    std::ostream &os, ParticleTwcKernelType twcKernelType )
  {
    const auto twcKernelTypeId =
      twcKernelType == ParticleTwcKernelType::PNN ? 0 : 1;
    return writeInteger( os, twcKernelTypeId,
                         "TWC kernel type (TWC-only; 0 - PNN, 1 - PIC):" );
  }


  void LegacySettingsProvider::parseSrunCommandLine( std::string const &line,
                                                     ExecutionSettings &e )
  {
    auto iss = std::istringstream{ line };
    auto token = std::string{};
    auto wasPreviousTokenN = false;

    while ( std::getline( iss, token, ' ' ) )
    {
      if ( wasPreviousTokenN )
      {
        char *strend_p = nullptr;
        e.processCount = static_cast< int >(
          std::strtol( token.c_str(), &strend_p, NUMERIC_BASE ) );
        wasPreviousTokenN = false;
        continue;
      }

      if ( token == "-n" )
      {
        wasPreviousTokenN = true;
      }
      else if ( token == "--overcommit" )
      {
        e.isNodeOvercommitEnabled = true;
      }
    }
  }

  void LegacySettingsProvider::parseRunBatchOption( std::string &line,
                                                    ExecutionSettings &e )
  {
    if ( line.length() < MIN_SBATCH_LINE_LENGTH || line[ 0 ] != '#' )
    {
      return;
    }
    for ( auto &c : line )
    {
      if ( c == '"' || c == '=' )
      {
        c = ' ';
      }

      auto token = std::string{};
      auto iss = std::istringstream{ line };

      iss >> token;
      if ( token != "#SBATCH" )
      {
        return;
      }

      iss >> token;
      if ( token == "--job-name" )
      {
        iss >> e.jobName;
      }
      else if ( token == "--account" )
      {
        iss >> e.grantNo;
      }
      else if ( token == "--nodes" )
      {
        iss >> e.cpuNodeCount;
      }
      else if ( token == "--time" )
      {
        iss >> token;
        e.wctLimit = parseWctDurationToMinutes( token );
      }
    }
  }

  double
  LegacySettingsProvider::parseWctDurationToMinutes( std::string const &token )
  {
    auto result = double{ 0 };
    auto dashPos = token.find( '-' );
    if ( dashPos != std::string::npos )
    {
      auto daysStr = token.substr( 0, dashPos );
      char *strend_p = nullptr;
      result += static_cast< double >(
                  std::strtol( daysStr.c_str(), &strend_p, NUMERIC_BASE ) ) *
                MINUTES_PER_DAY;
    }
    else
    {
      dashPos = 0;
    }

    auto hhmmss = token.substr( dashPos );
    result +=
      ( ( NUMERIC_BASE * ( hhmmss[ 0 ] - '0' ) ) + ( hhmmss[ 1 ] - '0' ) ) *
      MINUTES_PER_HOUR;
    result +=
      ( ( NUMERIC_BASE * ( hhmmss[ 3 ] - '0' ) ) + ( hhmmss[ 4 ] - '0' ) );
    result += ( ( NUMERIC_BASE * ( hhmmss[ SIX ] - '0' ) ) +
                ( hhmmss[ SEVEN ] - '0' ) ) *
              MINUTES_PER_SECOND;

    return result;
  }

  void LegacySettingsProvider::writeWctDurationInMinutes( std::ostream &os,
                                                          double d )
  {
    auto minutes = static_cast< int >( d );
    auto seconds = static_cast< int >(
      ( d - static_cast< double >( minutes ) ) / MINUTES_PER_SECOND );

    auto days = minutes / MINUTES_PER_DAY;
    if ( days > 0 )
    {
      os << days << '-';
    }
    minutes -= static_cast< int >( days * MINUTES_PER_DAY );

    auto hours = minutes / MINUTES_PER_HOUR;
    if ( hours < NUMERIC_BASE )
    {
      os << '0';
    }
    os << hours << ':';
    minutes -= static_cast< int >( hours * MINUTES_PER_HOUR );

    if ( minutes < NUMERIC_BASE )
    {
      os << '0';
    }
    os << minutes << ':';

    if ( seconds < NUMERIC_BASE )
    {
      os << '0';
    }
    os << seconds;
  }


  void LegacySettingsProvider::parseTurbCode( std::filesystem::path const &path,
                                              Metadata &m, Parameters const &p,
                                              bool isNew )
  {
    auto isSimTypeSet = false;
    auto isPartModeSet = false;

    auto ifs = std::ifstream{ path };
    auto line = std::string{};

    while ( std::getline( ifs, line ) )
    {
      auto isDone = false;
      trimStart( line );
      if ( line.empty() )
      {
        continue;
      }

      switch ( line[ 0 ] )
      {
      case 'f':
        isDone = parseTurbFnsCutoff( line, m, isSimTypeSet );
        break;
      case 'C':
        isDone = parseTurbSgsModelParameter( line, m );
        if ( !isDone )
        {
          isDone = parseTurbTwcKernelType( line, m, isPartModeSet, isNew );
        }
        break;
      case 'i':
        isDone = parseTurbPartMode( line, m, isPartModeSet, isNew );
        if ( !isDone )
        {
          isDone = parseTurbPartPerfProfileRange( line, m, isNew );
        }
        if ( !isDone )
        {
          isDone = parseTurbPartPerfPartInterval( line, m, isNew );
        }
        break;
      case 's':
        isDone = parseTurbSuperpartFactor( line, m );
        break;
      case 'v':
        isDone = parseTurbSrcFlowPath( line, m, p.isFlowGenerated );
        break;
      case 'p':
        isDone = parseTurbSrcPartPath( line, m, p.isPartGenerated );
        break;
      case 'I':
        isDone = parseTurbPartOutputDelay( line, m );
        break;
      default:
        break;
      }

      if ( !isDone )
      {
        checkTurbForLesIdentifier( line, m, isSimTypeSet );
      }
    }

    if ( !isPartModeSet )
    {
      m.particleMode = ParticleMode::OWC;
    }
    if ( p.N_part == 0 )
    {
      m.particleMode = ParticleMode::None;
    }
  }

  void
  LegacySettingsProvider::extractGravityMode( std::filesystem::path const &path,
                                              Metadata &m, bool hasGravity )
  {
    if ( !hasGravity )
    {
      m.gravityMode = GravityMode::None;
      return;
    }

    constexpr char const *vIdentifier = "if ( ic .eq. 1 ) unitv = 1.0";
    constexpr char const *hIdentifier = "if ( ic .eq. 2 ) unitv = 1.0";
    constexpr auto idLen = 28ul;

    auto ifs = std::ifstream{ path };
    auto line = std::string{};

    while ( std::getline( ifs, line ) )
    {
      trimStart( line );
      if ( line.length() < idLen || line[ 0 ] != 'i' )
      {
        continue;
      }

      auto identifierPart = line.substr( 0, idLen );
      if ( identifierPart == vIdentifier )
      {
        m.gravityMode = GravityMode::Vertical;
        return;
      }
      if ( identifierPart == hIdentifier )
      {
        m.gravityMode = GravityMode::Horizontal;
        return;
      }
    }

    throw std::runtime_error{
      "No valid gravity identifier was founf in 'partlib.f90'."
    };
  }

  void
  LegacySettingsProvider::extractPerfFlags( std::filesystem::path const &path,
                                            Metadata &m, bool isNew )
  {
    if ( !isNew )
    {
      return;
    }

    m.isPerfSimpleEnabled =
      std::filesystem::exists( path / "stat" / "perf_simple.dat" );
    m.isPerfPartDistEnabled =
      std::filesystem::exists( path / "stat" / "perf_part_dist.dat" );
    m.isPerfFullProfileEnabled =
      std::filesystem::exists( path / "perf" / "pfman.0000" );
  }

  // void LegacySettingsProvider::parseNameAndValidateForOld(
  //  std::filesystem::path const &path, Metadata &m )
  //{
  // TODO: path/name validation skipped for now
  //}

  // void LegacySettingsProvider::parseNameAndValidateForNew(
  //  std::filesystem::path const &path, Metadata &m )
  //{
  // TODO: path/name validation skipped for now
  //}



  bool LegacySettingsProvider::parseTurbFnsCutoff( std::string const &line,
                                                   Metadata &m,
                                                   bool &isSimTypeSet )
  {
    if ( !startsWith( line, "filter_velo_cutoff =", FILTER_PREFIX_LENGTH ) )
    {
      return false;
    }

    if ( isSimTypeSet )
    {
      throw std::runtime_error{ "Sim Type already set." };
    }

    m.simMethod = SimMethod::FNS;
    isSimTypeSet = true;

    m.k_filter = getLastInteger( line );

    return true;
  }

  bool LegacySettingsProvider::checkTurbForLesIdentifier(
    std::string const &line, Metadata &m, bool &isSimTypeSet )
  {
    auto iss = std::istringstream{ line };
    auto token = std::string{};
    while ( std::getline( iss, token, ':' ) )
    {
    }

    if ( token.find( "rnuef" ) == std::string::npos )
    {
      return false;
    }

    // if (isSimTypeSet) throw std::runtime_error{ "Sim Type already set." };

    m.simMethod = SimMethod::LES;
    isSimTypeSet = true;

    return true;
  }

  bool
  LegacySettingsProvider::parseTurbSgsModelParameter( std::string const &line,
                                                      Metadata &m )
  {
    if ( !startsWith( line, "C_K", 3ul ) )
    {
      return false;
    }
    if ( m.simMethod != SimMethod::LES )
    {
      throw std::runtime_error{ "'C_K' parameter set for non-LES simulation." };
    }

    auto iss = std::istringstream{ line };
    skipLine( iss, '=' );
    iss >> m.C_K;

    return true;
  }

  bool LegacySettingsProvider::parseTurbTwcKernelType( std::string const &line,
                                                       Metadata &m,
                                                       bool &isPartModeSet,
                                                       bool isNew )
  {
    if ( isNew || !startsWith( line, "CALL PNN", CALL_PNN_PREFIX_LENGTH ) )
    {
      return false;
    }
    if ( isPartModeSet && m.particleMode == ParticleMode::TWC )
    {
      throw std::runtime_error{ "Inconsistent particle mode." };
    }

    m.particleMode = ParticleMode::TWC;
    isPartModeSet = true;

    return true;
  }

  bool LegacySettingsProvider::parseTurbPartMode( std::string const &line,
                                                  Metadata &m,
                                                  bool &isPartModeSet,
                                                  bool isNew )
  {
    if ( !isNew ||
         !startsWith( line, "if (.TRUE.) then", IF_TRUE_PREFIX_LENGTH ) )
    {
      return false;
    }
    if ( isPartModeSet && m.particleMode == ParticleMode::TWC )
    {
      throw std::runtime_error{ "Inconsistent particle mode." };
    }

    m.particleMode = ParticleMode::TWC;
    isPartModeSet = true;

    return true;
  }

  bool
  LegacySettingsProvider::parseTurbSuperpartFactor( std::string const &line,
                                                    Metadata &m )
  {
    if ( !startsWith( line, "superpart_factor = ", SUPERPART_PREFIX_LENGTH ) )
    {
      return false;
    }
    m.superpartFactor = getLastDouble( line );
    return true;
  }

  bool LegacySettingsProvider::parseTurbSrcFlowPath( std::string const &line,
                                                     Metadata &m,
                                                     bool isFlowGenerated )
  {
    if ( isFlowGenerated ||
         !startsWith( line, "velo_omp", VELO_OMP_PREFIX_LENGTH ) )
    {
      return false;
    }
    auto srcPath = getLastString( line );
    m.srcFlowPath = srcPath.substr( 1, srcPath.length() - 2 );

    return true;
  }

  bool LegacySettingsProvider::parseTurbSrcPartPath( std::string const &line,
                                                     Metadata &m,
                                                     bool isPartGenerated )
  {
    if ( isPartGenerated ||
         !startsWith( line, "part_in", PART_IN_PREFIX_LENGTH ) )
    {
      return false;
    }
    auto srcPath = getLastString( line );
    m.srcPartPath = srcPath.substr( 1, srcPath.length() - 2 );

    return true;
  }

  bool
  LegacySettingsProvider::parseTurbPartOutputDelay( std::string const &line,
                                                    Metadata &m )
  {
    if ( !startsWith( line, "IF (jstep .gt.", IF_JSTEP_PREFIX_LENGTH ) )
    {
      return false;
    }

    auto iss = std::istringstream{ line };
    auto token = std::string{};
    auto result = 0;
    char *strend_p = nullptr;

    // sth wrong here
    while ( result != 0 && std::getline( iss, token, ' ' ) )
    {
      if ( token[ token.length() - 1 ] == ')' )
      {
        token = token.substr( 0, token.length() - 1 );
      }
      result = static_cast< int >(
        std::strtol( token.c_str(), &strend_p, NUMERIC_BASE ) );
    }

    m.partPerfInterval = result;

    return true;
  }

  bool LegacySettingsProvider::parseTurbPartPerfProfileRange(
    std::string const &line, Metadata &m, bool isNew )
  {
    if ( !isNew ||
         !startsWith( line, "if (jstep .ge.", IF_JSTEP_PREFIX_LENGTH ) )
    {
      return false;
    }

    auto isNextStart = false;
    auto isNextEnd = false;
    auto start = 0;
    auto end = 0;
    auto iss = std::istringstream{ line };
    auto token = std::string{};
    char *strend_p = nullptr;

    while ( std::getline( iss, token, ' ' ) )
    {
      if ( isNextStart )
      {
        start = static_cast< int >(
          std::strtol( token.c_str(), &strend_p, NUMERIC_BASE ) );
        isNextStart = false;
      }
      else if ( isNextEnd )
      {
        auto trimmedToken = token.substr( 0, token.length() - 1 );
        end = static_cast< int >(
          std::strtol( trimmedToken.c_str(), &strend_p, NUMERIC_BASE ) );
        isNextEnd = false;
      }
      else if ( token == ".ge." )
      {
        isNextStart = true;
      }
      else if ( token == ".lt." )
      {
        isNextEnd = true;
      }
    }

    m.perfFullStart = start;
    m.perfFullEnd = end;

    return true;
  }

  bool LegacySettingsProvider::parseTurbPartPerfPartInterval(
    std::string const &line, Metadata &m, bool isNew )
  {
    if ( !isNew ||
         !startsWith( line, "if (mod(jstep,", IF_JSTEP_PREFIX_LENGTH ) )
    {
      return false;
    }

    auto iss = std::istringstream{ line };
    auto token = std::string{};
    char *strend_p = nullptr;

    skipLine( iss, ',' );
    std::getline( iss, token, ')' );
    m.partPerfInterval = static_cast< int >(
      std::strtol( token.c_str(), &strend_p, NUMERIC_BASE ) );

    return true;
  }
}  // namespace turb

*/