#!/bin/bash

g++-8 -c main.cpp && 
g++-8 main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system &&
./sfml-app
