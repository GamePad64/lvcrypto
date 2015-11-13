project(lvcrypto)

#============================================================================
# Compiler properties
#============================================================================

### Setting compiler properties
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

#============================================================================
# Third-party Libraries
#============================================================================

# Finding packages
find_package(CryptoPP REQUIRED)

# Adding targets
add_library(lvcrypto INTERFACE ${MAIN_SRCS} ${PROTO_SOURCES})
target_include_directories(lvcrypto INTERFACE "include")

# CryptoPP
target_include_directories(lvcrypto INTERFACE ${CRYPTOPP_INCLUDE_DIRS})
target_link_libraries(lvcrypto INTERFACE ${CRYPTOPP_LIBRARIES})
