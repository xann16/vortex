#pragma once

/*


#include <filesystem>
#include <istream>
#include <numeric>
#include <ostream>

#include "turbpp/core/Settings/Legacy/ExecutionSettings.h"
#include "turbpp/core/Settings/Legacy/Metadata.h"
#include "turbpp/core/Settings/Legacy/Parameters.h"
#include "turbpp/core/Settings/Legacy/Settings.h"

namespace turb
{
  class LegacySettingsProvider
  {
  public:
    static Settings load( std::filesystem::path const &basePath );

    static Parameters loadParameters( std::filesystem::path const &path,
                                      bool isExtended = false );
    static Metadata loadMetadata( std::filesystem::path const &basePath,
                                  Parameters const &p );
    static ExecutionSettings
    loadExecutionSettings( std::filesystem::path const &path );

    static void saveParameters( std::filesystem::path const &path,
                                Parameters const &p, bool isExtended = false );
    static void saveMetadata( std::filesystem::path const &path,
                              Metadata const &m );
    static void saveExecutionSettings( std::filesystem::path const &path,
                                       ExecutionSettings const &e );

  private:
    // parameter items read/write
    static std::istream &readInteger( std::istream &is, int &outputValue );
    static std::istream &readReal( std::istream &is, double &outputValue );
    static std::istream &readBoolean( std::istream &is, bool &outputValue );

    static std::istream &readGridSize( std::istream &is, int &outputValue,
                                       bool isExtended = false );
    static std::istream &readProcCount( std::istream &is, int &outputValue,
                                        bool isExtended = false );
    static std::istream &readDeterministicForce( std::istream &is,
                                                 double &outputValue_k1,
                                                 double &outputValue_k2 );
    static std::istream &readKolmogorovParams( std::istream &is,
                                               double &outputValue_eta,
                                               double &outputValue_tau,
                                               bool isExtended = false );
    static std::istream &readForcingType( std::istream &is,
                                          ForcingType &outputValue );
    static std::istream &readDragType( std::istream &is,
                                       DragType &outputValue );
    static std::istream &readPartSetCount( std::istream &is );


    static std::ostream &writeInteger( std::ostream &os, int inputValue,
                                       char const *description );
    static std::ostream &writeReal( std::ostream &os, double inputValue,
                                    char const *description,
                                    [[maybe_unused]] bool isExtended = false );
    static std::ostream &writeBoolean( std::ostream &os, bool inputValue,
                                       char const *description,
                                       bool isExtended = false );
    static std::ostream &writeString( std::ostream &os,
                                      std::string const &inputValue,
                                      char const *description );

    static std::ostream &writeGridSize( std::ostream &os, int inputValue,
                                        bool isExtended = false );
    static std::ostream &writeProcCount( std::ostream &os, int inputValue,
                                         bool isExtended = false );
    static std::ostream &writeDeterministicForce( std::ostream &os,
                                                  double inputValue_k1,
                                                  double inputValue_k2,
                                                  bool isExtended = false );
    static std::ostream &writeKolmogorovParams( std::ostream &os,
                                                double inputValue_eta,
                                                double inputValue_tau,
                                                bool isExtended = false );
    static std::ostream &writeForcingType( std::ostream &os,
                                           ForcingType inputValue,
                                           bool isExtended = false );
    static std::ostream &writeDragType( std::ostream &os, DragType inputValue );
    static std::ostream &writePartSetCount( std::ostream &os,
                                            bool isExtended = false );
    static std::ostream &writeSimulationMethod( std::ostream &os,
                                                SimMethod simMethod );
    static std::ostream &writeParticleMode( std::ostream &os,
                                            ParticleMode partMode );
    static std::ostream &writeGravityDirection( std::ostream &os,
                                                GravityMode gravMode );
    static std::ostream &
    writeTwcKernelType( std::ostream &os, ParticleTwcKernelType twcKernelType );


    static void parseSrunCommandLine( std::string const &line,
                                      ExecutionSettings &e );
    static void parseRunBatchOption( std::string &line, ExecutionSettings &e );

    static double parseWctDurationToMinutes( std::string const &token );
    static void writeWctDurationInMinutes( std::ostream &os, double d );

    static void parseTurbCode( std::filesystem::path const &path, Metadata &m,
                               Parameters const &p, bool isNew );
    static void extractGravityMode( std::filesystem::path const &path,
                                    Metadata &m, bool hasGravity );
    static void extractPerfFlags( std::filesystem::path const &path,
                                  Metadata &m, bool isNew );
    // static void parseNameAndValidate( std::filesystem::path const &path,
    //                                  Metadata &m, bool isNew )
    //{
    //  if ( isNew )
    //  {
    //    parseNameAndValidateForNew( path, m );
    //  }
    //  else
    //  {
    //    parseNameAndValidateForOld( path, m );
    //  }
    //}

    // static void parseNameAndValidateForOld( std::filesystem::path const
    // &path,
    //                                        Metadata &m );
    // static void parseNameAndValidateForNew( std::filesystem::path const
    // &path,
    //                                        Metadata &m );

    static std::istream &skipLine( std::istream &is, char endChar = '\n' )
    {
      return is.ignore( std::numeric_limits< std::streamsize >::max(),
                        is.widen( endChar ) );
    }

    static bool isPathNew( std::filesystem::path const &path )
    {
      for ( auto const &part : path )
      {
        if ( part == "bis" )
        {
          return true;
        }
      }
      return false;
    }

    static void trimStart( std::string &str )
    {
      str.erase( str.begin(),
                 std::find_if( str.begin(), str.end(),
                               []( auto c ) { return !std::isspace( c ); } ) );
    }

    static bool startsWith( std::string const &str, const char *prefix,
                            std::size_t prefixLength )
    {
      if ( str.length() < prefixLength )
      {
        return false;
      }
      return str.substr( 0, prefixLength ) == prefix;
    }

    static std::string getLastString( std::string const &line )
    {
      auto iss = std::istringstream{ line };
      auto token = std::string{};
      while ( std::getline( iss, token, ' ' ) )
      {
      }
      return token;
    }

    static int getLastInteger( std::string const &line )
    {
      auto lastString = getLastString( line );
      char *strend_p = nullptr;
      return static_cast< int >(
        std::strtol( lastString.c_str(), &strend_p, NUMERIC_BASE ) );
    }

    static double getLastDouble( std::string const &line )
    {
      auto lastString = getLastString( line );
      char *strend_p = nullptr;
      return std::strtod( lastString.c_str(), &strend_p );
    }


    static bool parseTurbFnsCutoff( std::string const &line, Metadata &m,
                                    bool &isSimTypeSet );
    static bool checkTurbForLesIdentifier( std::string const &line, Metadata &m,
                                           bool &isSimTypeSet );
    static bool parseTurbSgsModelParameter( std::string const &line,
                                            Metadata &m );
    static bool parseTurbTwcKernelType( std::string const &line, Metadata &m,
                                        bool &isPartModeSet, bool isNew );
    static bool parseTurbPartMode( std::string const &line, Metadata &m,
                                   bool &isPartModeSet, bool isNew );
    static bool parseTurbSuperpartFactor( std::string const &line,
                                          Metadata &m );
    static bool parseTurbSrcFlowPath( std::string const &line, Metadata &m,
                                      bool isFlowGenerated );
    static bool parseTurbSrcPartPath( std::string const &line, Metadata &m,
                                      bool isPartGenerated );
    static bool parseTurbPartOutputDelay( std::string const &line,
                                          Metadata &m );
    static bool parseTurbPartPerfProfileRange( std::string const &line,
                                               Metadata &m, bool isNew );
    static bool parseTurbPartPerfPartInterval( std::string const &line,
                                               Metadata &m, bool isNew );

    static const int NUMERIC_BASE = 10;
    static const int MIN_SBATCH_LINE_LENGTH = 8;
    static const int SIX = 6;
    static const int SEVEN = 7;

    static const unsigned long FILTER_PREFIX_LENGTH = 20ul;
    static const unsigned long CALL_PNN_PREFIX_LENGTH = 8ul;
    static const unsigned long VELO_OMP_PREFIX_LENGTH = 8ul;
    static const unsigned long IF_TRUE_PREFIX_LENGTH = 16ul;
    static const unsigned long SUPERPART_PREFIX_LENGTH = 19ul;
    static const unsigned long PART_IN_PREFIX_LENGTH = 7ul;
    static const unsigned long IF_JSTEP_PREFIX_LENGTH = 14ul;

    constexpr static const double MINUTES_PER_DAY = 1440.0;
    constexpr static const double MINUTES_PER_HOUR = 60.0;
    constexpr static const double MINUTES_PER_SECOND = 1.0 / 60.0;
  };
}  // namespace turb

*/