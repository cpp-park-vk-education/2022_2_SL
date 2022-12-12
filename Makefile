
SRCS = $(wildcard src/*.cpp)
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic -O3

all:
	$(foreach src, $(SRCS), $(CC) $(CFLAGS) $(src) -o $(basename $(src)).o;)
