if (WIN32)
add_compile_definitions(WINDOWS)
else()
add_compile_definitions(LINUX)
add_compile_options(-Wall -Wextra -Wpedantic)
endif()


add_compile_definitions(FMT_HEADER_ONLY)
set(PROJECT_SOURCES
        main.cpp
        MDDatatable.cpp
        
)
set(PROJECT_HEADERS 
        MDDatatable.h
       
        )



set(PROJECT_FORMS 
      

)

add_executable(QRScanner
    ${PROJECT_SOURCES} 
    ${PROJECT_HEADERS}
    ${PROJECT_FORMS}
)
target_link_libraries(QRScanner PRIVATE Qt6::Widgets)


set_target_properties(QRScanner PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)



