#!/bin/bash

make re && \
g++ tests/main.cpp -o test.file -L. -ltree -lpthread && \
./test.file && rm test.file