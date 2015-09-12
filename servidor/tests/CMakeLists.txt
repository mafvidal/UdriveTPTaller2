#Se agregan las bibliotecas de Gmock y Gtest
set(GMock "${PROJECT_SOURCE_DIR}/bibliotecas/gmock/libgmock.a")
set(GTest "${PROJECT_SOURCE_DIR}/bibliotecas/gmock/gtest/libgtest.a")

#Agrego la clases programados por nosotros
set(Clases ${PROJECT_SOURCE_DIR}/clases)

#Incluyo la ruta de GMock y Gtest, para evitar en los archivos incluirla
include_directories("${PROJECT_SOURCE_DIR}/bibliotecas/gmock/include" "${PROJECT_SOURCE_DIR}/bibliotecas/gmock/gtest/include" ${Clases})

#Incluimos las clases
file(GLOB Clases_INC
	"${PROJECT_SOURCE_DIR}/clases/*.h"
	"${PROJECT_SOURCE_DIR}/clases/*.cpp"
)

#Vincula el archivo de tests "mainTest.cpp" con el ejecutable
add_executable(tests mainTest ${Clases_INC})

#Se agregan las librerias de GTest y GMock
target_link_libraries(tests ${GTest})
target_link_libraries(tests ${GMock})
target_link_libraries(tests rocksdb pthread rt snappy gflags z bz2)
