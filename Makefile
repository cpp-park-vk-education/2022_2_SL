TARGET = ./main.out
TST_TARGET = ./test.out
VALGRIND_LOG = "valgrind.log"

# XXX: Don't forget backslash at the end of any line except the last one
# Main
HDRS = \
	   ./include/
SRCS = \
	   ./src/main.cpp \
	   ./src/calculation.cpp

# Test
TST_HDRS = \
           ./include/

TST_SRCS = \
           ./src/calculation.cpp \
		   ./test/test.cpp

.PHONY: all check build test memtest testextra memtestextra rebuild clean

all: clean check build test memtest testextra memtestextra

check:
	./linters/run.sh

build: $(TARGET)

test: $(TST_TARGET)
	$(TST_TARGET)

memtest: $(TST_TARGET)
	./project/tests/memtest.sh ${TST_TARGET}

testextra: $(TST_TARGET)
	$(TST_TARGET) --with-extra

memtestextra: $(TST_TARGET)
	./project/tests/memtest.sh ${TST_TARGET} --with-extra

rebuild: clean build

$(TARGET): $(SRCS)
	$(CXX) -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(CXXFLAGS) $(SRCS)

$(TST_TARGET): $(TST_SRCS)
	$(CXX) -Wall -Wextra -Werror $(addprefix -I,$(TST_HDRS)) -o $(TST_TARGET) $(CXXFLAGS) $(TST_SRCS) -lgtest -pthread

clean:
	rm -f $(TARGET) $(TST_TARGET) ${VALGRIND_LOG}