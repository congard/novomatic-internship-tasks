cmake_minimum_required(VERSION 3.27)
project(t2_ticket_machine)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

macro(add_dep name git_repo git_tag)
    FetchContent_Declare(${name}
            GIT_REPOSITORY ${git_repo}
            GIT_TAG ${git_tag})

    FetchContent_GetProperties(${name})

    if (NOT ${name}_POPULATED)
        FetchContent_Populate(${name})
        add_subdirectory(${${name}_SOURCE_DIR} ${${name}_BINARY_DIR} EXCLUDE_FROM_ALL)
    endif()
endmacro()

add_dep(ftxui https://github.com/ArthurSonzogni/ftxui v5.0.0)
add_dep(tulz https://github.com/congard/tulz.git 90144b140abc87a88ecdc79863599623bb23fe4c)

set(TMC_LIB_SOURCES
        include/core/model/Ticket.h
        src/core/hardware/CoinAcceptor.cpp
        include/core/hardware/CoinAcceptor.h
        include/core/model/CoinValue.h
        include/core/provider/TicketProvider.h
        include/core/model/IssuedTicket.h
        include/core/hardware/TicketPrinter.h
        include/core/hardware/HardwareError.h
        src/core/hardware/HardwareInterface.cpp
        include/core/hardware/HardwareInterface.h
        src/core/TicketMachine.cpp
        include/core/TicketMachine.h
        include/core/hardware/HardwareResult.h
        include/core/algorithm/ChangeCalculator.h
        src/core/algorithm/GreedyChangeCalculator.cpp
        include/core/algorithm/GreedyChangeCalculator.h
        include/core/model/CoinDesc.h)

set(TMC_DEMO_LIB_SOURCES
        src/demo/algorithm/DemoChangeCalculator.cpp
        include/demo/algorithm/DemoChangeCalculator.h
        src/demo/hardware/DemoCoinAcceptor.cpp
        include/demo/hardware/DemoCoinAcceptor.h
        src/demo/hardware/DemoTicketPrinter.cpp
        include/demo/hardware/DemoTicketPrinter.h
        src/demo/provider/DemoTicketProvider.cpp
        include/demo/provider/DemoTicketProvider.h
        src/demo/DemoTicketMachine.cpp
        include/demo/DemoTicketMachine.h)

add_library(tmc ${TMC_LIB_SOURCES})
add_library(tmc_demo ${TMC_DEMO_LIB_SOURCES})

target_include_directories(tmc PUBLIC ${tulz_SOURCE_DIR}/include)
target_include_directories(tmc PUBLIC include/core)
target_link_libraries(tmc tulz)

target_include_directories(tmc_demo PUBLIC include/demo)
target_link_libraries(tmc_demo tmc)

add_executable(cli src/cli/cli.cpp
        src/cli/Application.cpp
        src/cli/Application.h
        src/cli/Page.cpp
        src/cli/Page.h
        src/cli/MainPage.cpp
        src/cli/MainPage.h
        src/cli/TicketPage.cpp
        src/cli/TicketPage.h)

target_include_directories(cli PUBLIC ${ftxui_SOURCE_DIR}/include)
target_link_libraries(cli tmc_demo component)
