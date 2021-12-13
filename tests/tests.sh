#!/bin/bash

make re && \
g++ tests/main.cpp -o test.file -L. -ltree -lpthread -lboost_chrono && \
./test.file && rm test.file