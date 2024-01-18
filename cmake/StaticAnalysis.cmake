set(CPPCHECK_BASE
    cppcheck
    --enable=style,performance,warning,portability
    --inline-suppr
    --suppress=missingIncludeSystem
    --suppress=unusedFunction
    --suppress=cppcheckError
    --suppress=internalAstError
    --suppress=unmatchedSuppression
    --suppress=passedByValue
    --suppress=syntaxError
    --suppress=preprocessorErrorDirective
    --inconclusive)

set(CLANG_TIDY_BASE
    clang-tidy --extra-arg-before=-Wno-unknown-warning-option
    --extra-arg-before=-Wno-ignored-optimization-argument
    --extra-arg-before=-Wno-unused-command-line-argument)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(CMAKE_CXX_CPPCHECK ${CPPCHECK_BASE} --platform=win64)
  set(CMAKE_CXX_CLANG_TIDY
      ${CLANG_TIDY_BASE} --extra-arg-before=--driver-mode=cl
      --extra-arg-before=/EHsc)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  set(CMAKE_CXX_CPPCHECK ${CPPCHECK_BASE} --platform=unix64)
  set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_BASE} --extra-arg-before=-fexceptions)
endif()
