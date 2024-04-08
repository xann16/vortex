# global compiler settings - TODO: redo into separate target to link against other targets
if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
  add_compile_options( -stdlib=libstdc++ )
endif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )

# still necessary ?
# add_compile_options( -pthread )
# set( CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -lpthread )

# prepare warning settings to be set for common target
# TODO: add options for MSVC
set( MY_CXX_WARNING_FLAGS -Wall -Wextra -Wconversion -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wcast-qual -Wunused -Woverloaded-virtual -Wno-noexcept-type -Wpedantic )
if ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
  set( MY_CXX_WARNING_FLAGS ${MY_CXX_WARNING_FLAGS} -Weverything -Wno-c++98-compat-pedantic  -Wno-c++98-compat -Wno-documentation -Wno-reserved-id-macro -Wno-switch-enum -Wno-weak-vtables -Wno-missing-prototypes -Wno-padded -Wno-missing-noreturn -Wno-exit-time-destructors -Wno-documentation-unknown-command -Wno-unused-template -Wno-undef -Wno-format-nonliteral -Wno-global-constructors)
else( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
  set( MY_CXX_WARNING_FLAGS ${MY_CXX_WARNING_FLAGS} -Wnoexcept )
endif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )

# option to treat warnings as errors
option( TREAT_COMPILER_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF )
if ( TREAT_COMPILER_WARNINGS_AS_ERRORS )
  set( MY_CXX_WARNING_FLAGS ${MY_CXX_WARNING_FLAGS} -Werror )
endif ( TREAT_COMPILER_WARNINGS_AS_ERRORS )

add_compile_options( ${MY_CXX_WARNING_FLAGS} )
