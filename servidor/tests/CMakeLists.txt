#Se agregan las bibliotecas de Gmock y Gtest
set(GMock "${PROJECT_SOURCE_DIR}/bibliotecas/gmock/libgmock.a")
set(GTest "${PROJECT_SOURCE_DIR}/bibliotecas/gmock/gtest/libgtest.a")

#Incluyo la ruta de GMock y Gtest, para evitar en los archivos incluirla
include_directories("${PROJECT_SOURCE_DIR}/bibliotecas/gmock/include" "${PROJECT_SOURCE_DIR}/bibliotecas/gmock/gtest/include")

#Vincula el archivo de tests "mainTest.cpp" con el ejecutable
add_executable(tests mainTest)

#Se agregan las librerias de GTest y GMock
target_link_libraries(tests ${GTest})
target_link_libraries(tests ${GMock})
target_link_libraries(tests pthread rt snappy gflags z bz2)
