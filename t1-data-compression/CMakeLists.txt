cmake_minimum_required(VERSION 3.27)
project(t1_data_compression)

set(CMAKE_CXX_STANDARD 20)

# only headers but still declare them as
# library  since you can never know when
# `cpp`s will be added
set(DC_LIB_SOURCES
        include/Data.h
        include/Array2D.h
        include/CompressedData.h
        include/DataCompressor.h)

add_library(dc ${DC_LIB_SOURCES})
set_target_properties(dc PROPERTIES LINKER_LANGUAGE CXX)
