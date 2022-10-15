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

all: clean build test 


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
