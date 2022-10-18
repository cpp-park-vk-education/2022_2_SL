TARGET = ./main.out
TST_TARGET = ./test.out

HDRS = \
	   ./include/
SRCS = \
	   ./src/main.cpp \
	   ./src/calculation.cpp
	   
TST_HDRS = \
           ./include/

TST_SRCS = \
           ./src/calculation.cpp \
		   ./test/test.cpp

.PHONY: all build test rebuild clean

all: clean format build test 

lint:
	clang-tidy $(SRCS) $(HDRS) -format-style='{BasedOnStyle: google}' -checks='-*,readability-*,modernize-*,-modernize-use-trailing-return-type,performance-*,cppcoreguidelines-*,clang-analyzer-*,bugprone-*,misc-*,-bugprone-easily-swappable-parameters' -- -std=c++17 -I$(HDRS)

format:
	clang-format -style=google -i $(SRCS) $(HDRS)*.hpp

build: $(TARGET)

test: $(TST_TARGET)
	$(TST_TARGET)

rebuild: clean build

$(TARGET): $(SRCS)
	$(CXX) -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(CXXFLAGS) $(SRCS)

$(TST_TARGET): $(TST_SRCS)
	$(CXX) -Wall -Wextra -Werror $(addprefix -I,$(TST_HDRS)) -o $(TST_TARGET) $(CXXFLAGS) $(TST_SRCS) -lgtest -pthread

clean:
	rm -f $(TARGET) $(TST_TARGET)
