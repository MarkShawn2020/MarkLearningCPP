add_library(templates MarkTemplates.cpp)

target_include_directories(templates
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )



