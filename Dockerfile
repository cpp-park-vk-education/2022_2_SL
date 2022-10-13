FROM leshiy1295/gcc_linters_valgrind_cmake_gtest

WORKDIR /code/

COPY src ./src

COPY test ./test

COPY include ./include

COPY Makefile .

RUN make

