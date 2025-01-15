set(USE_MODULE_MPI ON) # ??? - for modern Fortran ???
find_package(MPI REQUIRED)

find_package(FFTW3 REQUIRED)

find_package(nlohmann_json REQUIRED)

if(BUILD_TESTING)
    find_package(Catch2 REQUIRED)
endif()
