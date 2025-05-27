
function(create_library target_name)
    set(multiArgs FILES FLAGS LIBS DEFS)
    cmake_parse_arguments(TARGET "" "" "${multiArgs}" ${ARGN})
    if (NOT DEFINED TARGET_FILES)
        message(ERROR "NOT DEFINED TARGET_FILES")
        return()
    endif()
    add_library(
        ${target_name}
        ${TARGET_FILES}
    )

    set_target_properties(${target_name} PROPERTIES OUTPUT_NAME ${target_name} PREFIX "")

    if(DEFINED TARGET_FLAGS)
        target_compile_options(${target_name} PRIVATE ${TARGET_FLAGS})
    endif()
    if (DEFINED TARGET_LIBS)
        target_link_libraries(${target_name} ${TARGET_LIBS})
    endif()
    if (DEFINED TARGET_DEFS)
        target_compile_definitions(${target_name} PRIVATE ${TARGET_DEFS})
    endif()

endfunction(create_library)

function(create_target target_name)
    set(multiArgs FILES FLAGS LIBS DEFS)
    cmake_parse_arguments(TARGET "" "NAME"
                          "${multiArgs}" ${ARGN} )
    message(
        "
        target_name: ${target_name}
        TARGET_FILES: ${TARGET_FILES}
        TARGET_FLAGS: ${TARGET_FLAGS}
        TARGET_LIBS: ${TARGET_LIBS}
        TARGET_DEFS: ${TARGET_DEFS}
        "
    )

    if (NOT DEFINED TARGET_FILES)
        message(ERROR "NOT DEFINED TARGET_FILES")
        return()
    endif()

    add_executable(${target_name} ${TARGET_FILES})
    if(DEFINED TARGET_FLAGS)
        target_compile_options(${target_name} PRIVATE ${TARGET_FLAGS})
    endif()
    if (DEFINED TARGET_LIBS)
        target_link_libraries(${target_name} ${TARGET_LIBS})
    endif()
    if (DEFINED TARGET_DEFS)
        target_compile_definitions(${target_name} PRIVATE ${TARGET_DEFS})
    endif()
endfunction()