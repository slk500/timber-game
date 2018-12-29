#!/bin/bash

g++-6 -c main.cpp && 
g++-6 main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system &&
./sfml-app
