cmake_minimum_required(VERSION 3.10)
project(AirlineAPP VERSION 1.0 LANGUAGES CXX)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build type if not set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Enable folder support
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Ensure source directory exists
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src")
    message(FATAL_ERROR "Source directory 'src' not found!")
endif()

# List specific source files
set(SOURCES
    src/main.cpp
    src/person/Person.cpp
    src/person/User.cpp
    src/person/BookingAgent.cpp
    src/person/Administrator.cpp
    src/person/Passenger.cpp
    src/factory/ConcreteUserFactory.cpp
    src/utils/exceptions/Undefined_role_exception.cpp
    src/utils/IOStreamHelper.cpp
    src/APP.cpp
    src/utils/FileManager.cpp
    # functional_testing/fileManagerTest001.cpp
    src/utils/Date.cpp
    # functional_testing/dateTest.cpp
    src/manager/FlightManager.cpp
    src/flight/Flight.cpp
    src/person/CrewAttendant.cpp
    src/person/FlightAttendant.cpp
    src/person/Pilot.cpp
    src/utils/JSONFileManager.cpp
    src/manager/UserManager.cpp
    src/utils/exceptions/non_existing_user_exception.cpp
    src/utils/exceptions/wrong_password_exception.cpp
)

# List header files (optional, but can help IDEs index them)
set(HEADERS
    header/person/Person.hpp    
    header/person/User.hpp    
    header/person/BookingAgent.hpp
    header/person/Administrator.hpp
    header/person/Passenger.hpp
    header/factory/UserFactory.hpp
    header/factory/ConcreteUserFactory.hpp
    header/utils/Configs.hpp
    header/utils/exceptions/Undefined_role_exception.hpp
    header/utils/IOStreamHelper.hpp
    header/APP.hpp
    header/utils/FileManager.hpp
    header/utils/Date.hpp
    header/manager/FlightManager.hpp
    header/flight/Flight.hpp
    header/manager/IManager.hpp
    header/person/CrewAttendant.hpp
    header/person/FlightAttendant.hpp
    header/person/Pilot.hpp
    header/utils/JSONFileManager.hpp
    header/manager/UserManager.hpp
    header/utils/exceptions/non_existing_user_exception.hpp
    header/utils/exceptions/wrong_password_exception.hpp
)

# Create the executable from your sources
add_executable(AirlineAPP ${SOURCES} ${HEADERS})

# Set output directories
set_target_properties(AirlineAPP PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release"
)

# For MSVC (Visual Studio) users: add a few compiler flags
if(MSVC)
    target_compile_options(AirlineAPP PRIVATE
        /W3       # Lower warning level from W4 to W3
        /wd4244   # Disable specific warning about possible data loss
        # remove /WX if you don't want warnings to be errors
    )
endif()

# --------------------------
# Add and link libbcrypt
# --------------------------
# 1. Add the library subdirectory
add_subdirectory(external/libbcrypt)

# 2. Include the bcrypt headers
target_include_directories(AirlineAPP PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libbcrypt/include
)

# 3. Link the bcrypt library to AirlineAPP
target_link_libraries(AirlineAPP PRIVATE bcrypt)