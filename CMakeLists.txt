cmake_minimum_required(VERSION 2.6)

set(SOURCES src/graph0.cpp src/gtools.c src/naugraph.c src/nautinv.c src/naututil.c src/nauty.c src/schreier.c  src/graph1.cpp src/main.cpp src/naurng.c src/nausparse.c src/nautil.c)

add_executable(test ${SOURCES})
