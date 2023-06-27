cmake_minimum_required(VERSION 3.10)

project(numerics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS})

set(INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/maths
    ${CMAKE_CURRENT_SOURCE_DIR}/include/maths/vectors_matrices
    ${CMAKE_CURRENT_SOURCE_DIR}/include/physics
    ${CMAKE_CURRENT_SOURCE_DIR}/include/physics/four_vectors_tensors)

set(SRC_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/maths
    ${CMAKE_CURRENT_SOURCE_DIR}/src/maths/vectors_matrices
    ${CMAKE_CURRENT_SOURCE_DIR}/src/physics
    ${CMAKE_CURRENT_SOURCE_DIR}/src/physics/four_vectors_tensors)

set(HEADERS
    include/maths/angle.hpp
    include/maths/numerics.hpp
    include/maths/derivative.hpp
    include/maths/linear_systems.hpp
    include/maths/function.hpp
    include/maths/vectors_matrices/row.hpp
    include/maths/vectors_matrices/unitvector.hpp
    include/maths/vectors_matrices/vector3.hpp
    include/maths/vectors_matrices/column.hpp
    include/maths/vectors_matrices/matrix.hpp
    include/physics/physics.hpp
    include/physics/four_vectors_tensors/vector4.hpp
    include/physics/four_vectors_tensors/fourmomentum.hpp
    include/physics/four_vectors_tensors/matrix4.hpp
    include/physics/physics_constants.hpp
)

SET(SOURCES
    src/maths/derivative.cpp
    src/maths/function.cpp
    src/maths/vectors_matrices/column.cpp
    src/maths/vectors_matrices/matrix.cpp
    src/maths/vectors_matrices/vector3.cpp
    src/maths/vectors_matrices/unitvector.cpp
    src/maths/vectors_matrices/row.cpp
    src/maths/numerics.cpp
    src/physics/four_vectors_tensors/fourmomentum.cpp
    src/physics/four_vectors_tensors/matrix4.cpp
    src/physics/four_vectors_tensors/vector4.cpp
    src/main.cpp
)

include_directories(${INCLUDE_DIR} ${SRC_DIR})

add_executable(physics src/main.cpp ${SOURCES} ${HEADERS})

target_compile_features(physics PRIVATE cxx_std_17)

target_include_directories(physics PRIVATE ${INCLUDE_DIR})

install(TARGETS physics
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
