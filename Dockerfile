FROM leshiy1295/gcc_linters_valgrind_cmake_gtest

WORKDIR /code/

ADD ./src ./

ADD Makefile ./

WORKDIR /build

RUN make ../