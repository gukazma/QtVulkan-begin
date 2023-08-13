function(compile_shader SHADERS TARGET_NAME SHADER_INCLUDE_FOLDER GENERATED_DIR GLSLANG_BIN)
    set(working_dir "${CMAKE_CURRENT_SOURCE_DIR}")
    add_custom_target(${TARGET_NAME})
    set(ALL_GENERATED_SPV_FILES "")
    set(ALL_GENERATED_CPP_FILES "")

    if(UNIX)
        execute_process(COMMAND chmod a+x ${GLSLANG_BIN})
    endif()

    foreach(SHADER ${SHADERS})
    # Prepare a header name and a global variable for this shader
        set_source_files_properties(${SHADER} PROPERTIES HEADER_FILE_ONLY TRUE)

        get_filename_component(SHADER_NAME ${SHADER} NAME)
        string(REPLACE "." "_" HEADER_NAME ${SHADER_NAME})
        string(TOUPPER ${HEADER_NAME} GLOBAL_SHADER_VAR)

        set(SPV_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_DIR}/spv/${SHADER_NAME}.spv")
        set(CPP_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_DIR}/cpp/Shader/${HEADER_NAME}.h")

        add_custom_command(
            TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${GLSLANG_BIN} -I${SHADER_INCLUDE_FOLDER} -V -e main -o ${SPV_FILE} ${SHADER}
            DEPENDS ${SHADER}
            WORKING_DIRECTORY "${working_dir}")

        list(APPEND ALL_GENERATED_SPV_FILES ${SPV_FILE})

        # generate cpp header
        string(REPLACE "\." "\_" VARNAME ${SHADER_NAME})
        add_custom_command(
            TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${GLSLANG_BIN} -I${SHADER_INCLUDE_FOLDER} -V --vn ${VARNAME} -e main  ${SHADER} -o ${CPP_FILE}
            DEPENDS ${SHADER}
            WORKING_DIRECTORY "${working_dir}")
        

        list(APPEND ALL_GENERATED_CPP_FILES ${CPP_FILE})

    endforeach()
    # add_custom_target(${TARGET_NAME}
    #     DEPENDS ${ALL_GENERATED_SPV_FILES} SOURCES ${SHADERS})

endfunction()