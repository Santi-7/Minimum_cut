set(SOURCE_FILES
        Product.cpp
        Edge.cpp
        KargerGraph.cpp
        ProductsPack.cpp
        RandomNumberEngine.cpp)

set(HEADER_FILES
        Product.hpp
        Edge.hpp
        KargerGraph.hpp
        ProductsPack.hpp
        RandomNumberEngine.hpp)

add_library(src STATIC ${HEADER_FILES} ${SOURCE_FILES})