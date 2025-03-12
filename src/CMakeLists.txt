set(SOURCE_FILE_LIST
    main.cpp
    app.cpp
    image_loader.cpp
    resource.rc)

set(HEADER_FILE_LIST
    "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/app.hpp"
    "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/image_loader.hpp"
    "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/resource.h")

add_executable(
    ${PROJECT_NAME}
    ${SOURCE_FILE_LIST}
    ${HEADER_FILE_LIST})

if(MSVC)
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}")
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/extern/SDL/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/extern/SDL_image/include")
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_image::SDL3_image)

if (WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM
    )
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3_image::SDL3_image> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM
    )
endif()