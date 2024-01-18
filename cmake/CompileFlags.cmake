function(apply_compilation_flags target)
  if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(
      ${target}
      PRIVATE /utf-8
              /diagnostics:caret
              /fp:fast
              /W4
              /WX
              /w14242
              /w14254
              /w14263
              /w14265
              /w14287
              /w14296
              /w14311
              /w14545
              /w14546
              /w14547
              /w14549
              /w14555
              /w14619
              /w14640
              /w14826
              /w14905
              /w14906
              /w14928
              /permissive-
              /volatile:iso
              /Zc:inline
              /Zc:preprocessor
              /Zc:enumTypes
              /Zc:lambda
              /Zc:__cplusplus
              /Zc:externConstexpr
              /Zc:throwingNew
              /EHsc)
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set(CLANG_GNU_SHARED
        -ffp-contract=off
        -Wall
        -Wextra
        -Werror
        -Wshadow
        -Wnon-virtual-dtor
        -pedantic
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wmisleading-indentation
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2
        -Wimplicit-fallthrough)
    set(GNU_ONLY -Wduplicated-cond -Wduplicated-branches -Wlogical-op
                 -Wuseless-cast)

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
      target_compile_options(${target} PRIVATE ${CLANG_GNU_SHARED})
    else()
      target_compile_options(${target} PRIVATE ${CLANG_GNU_SHARED} ${GNU_ONLY})
    endif()

  else()
    message(WARNING "Unsupported compiler detected, skipping compilation flags")
  endif()
endfunction()
