cmake_minimum_required(VERSION 3.1...3.23)
project(ink_edit)

## Find CGAL
find_package(CGAL REQUIRED COMPONENTS Core)
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

if (WIN32)
    find_package(GLEW CONFIG REQUIRED)
    find_package(metis CONFIG REQUIRED)
    find_package(BLAS REQUIRED)
    find_package(LAPACK REQUIRED)
    find_package(TBB CONFIG REQUIRED)
    find_package(suitesparse CONFIG REQUIRED)

    set( SUITESPARSE_LIBRARIES
            ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES}
        SuiteSparse::amd
        SuiteSparse::camd
        SuiteSparse::colamd
        SuiteSparse::ccolamd
        SuiteSparse::cholmod
        SuiteSparse::spqr 
        TBB::tbb TBB::tbbmalloc TBB::tbbmalloc_proxy )
    set (GLEW_LIBRARIES GLEW::GLEW)
    STRING(REGEX REPLACE "\\\\" "/" TEMPO_P $ENV{userprofile}/Desktop/CCVT_data)
    set(TEMPO_PATH ${CMAKE_BINARY_DIR}/CCVT_data CACHE STRING "shaders data result storage dir" )

else ()
    set( SUITESPARSE_LIBRARIES
        ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES}
        amd camd colamd ccolamd cholmod spqr tbb )
    set (GLEW_LIBRARIES GLEW)
    set(TEMPO_PATH ${CMAKE_BINARY_DIR}/CCVT_data/ CACHE STRING "shaders data result storage dir" )
endif()

set(SRCS main_ccvt_cgal.cpp
    # matrix
    matrix/sparse_array.cpp
    matrix/sparse_matrix.cpp
    #imgui
    imgui/imgui_impl_opengl3.cpp
    imgui/imgui_impl_glfw.cpp
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp
    #implot
    imgui/implot.cpp
    imgui/implot_items.cpp
    imgui/implot_demo.cpp
    # ccvt
    ccvt_assign.cpp
    ccvt_energy.cpp
    ccvt_histogram.cpp
    ccvt_init.cpp
    ccvt_io.cpp
    ccvt_optimizer.cpp
    ccvt_sites.cpp
    ccvt_application.cpp)

add_executable(${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PRIVATE -DTEMPO_PATH=std::string\(\"${TEMPO_PATH}/\"\) )

target_sources(${PROJECT_NAME} PRIVATE ${SRCS} main_ccvt_cgal.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE 
        /usr/include/suitesparse
        /usr/local/include/suitesparse)

target_link_directories(${PROJECT_NAME} PRIVATE /usr/local/lib/)

target_link_libraries(${PROJECT_NAME} PRIVATE
    CGAL::CGAL
    ${SUITESPARSE_LIBRARIES}
    glfw
    OpenGL::GL
    OpenGL::GLU
    ${GLEW_LIBRARIES} )



target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

#cgal_add_compilation_test(${PROJECT_NAME})

# nice vs solution
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

set(CMAKE_CONFIGURATION_TYPES "Release;Debug" CACHE STRING "" FORCE)
set(default_build_type "Release")
set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)

file(MAKE_DIRECTORY "${TEMPO_PATH}" RESULT errmkd)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION "${TEMPO_PATH}")
file(MAKE_DIRECTORY "${TEMPO_PATH}/results" RESULT errmkd)
