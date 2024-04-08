set(USE_MODULE_MPI ON) # ???
find_package(MPI REQUIRED)

find_package(FFTW3 REQUIRED)

find_package(RapidJSON REQUIRED)

if(BUILD_TESTING)
    find_package(Catch2 REQUIRED)
endif()
