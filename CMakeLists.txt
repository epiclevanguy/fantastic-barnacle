cmake_minimum_required(VERSION 2.6)

set(SOURCES src/gl.cpp  src/graph0.cpp src/naurng.c src/nausparse.c src/nautil.c src/graph1.cpp  src/gtools.c  src/gu.cpp src/main.cpp src/naugraph.c src/nautinv.c src/naututil.c src/nauty.c src/schreier.c)

add_executable(test ${SOURCES})

