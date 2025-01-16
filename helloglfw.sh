#!/bin/bash
clang++ helloglfw.cpp -std=c++11 -I/opt/homebrew/Cellar/glfw/3.4/include -L/opt/homebrew/Cellar/glfw/3.4/lib -lglfw -framework OpenGL -o helloglfw
