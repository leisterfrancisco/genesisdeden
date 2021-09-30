cmake_minimum_required(VERSION 3.16)
project(genesisdeden)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(clsdk REQUIRED)


add_executable(genesisdeden src/genesisdeden.cpp)
target_link_libraries(genesisdeden eosio-contract-simple-malloc)


add_executable(genesisdeden-abigen src/genesisdeden.cpp)
target_link_libraries(genesisdeden-abigen eosio-contract-abigen)
add_custom_command(TARGET genesisdeden-abigen POST_BUILD
    COMMAND cltester genesisdeden-abigen.wasm >genesisdeden.abi
)


execute_process(COMMAND ln -sf ${clsdk_DIR} ${CMAKE_CURRENT_BINARY_DIR}/clsdk)
execute_process(COMMAND ln -sf ${WASI_SDK_PREFIX} ${CMAKE_CURRENT_BINARY_DIR}/wasi-sdk)


set(CMAKE_EXPORT_COMPILE_COMMANDS on)