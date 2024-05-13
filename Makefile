.PHONY: clean

# Build tools and options
CXX = clang++
STD = -std=c++20
ASAN := -fsanitize=address
UBSAN := -fsanitize=undefined
SAN := -fsanitize=undefined,address
TEST_FLAGS := -lgtest -lgmock -pthread


# Sources and headers
ifeq (run,$(firstword $(MAKECMDGOALS)))
  TASK_NUMBER := $(word 2, $(MAKECMDGOALS))
  SOURCES = $(wildcard tasks/$(TASK_NUMBER)/*.cpp tasks/$(TASK_NUMBER)/*/*.cpp tasks/$(TASK_NUMBER)/*/*/*.cpp) 
  HEADERS = $(wildcard tasks/$(TASK_NUMBER)/*.hpp)
  TESTS = $(wildcard tests/$(TASK_NUMBER)/*.cpp)
  $(eval $(TASK_NUMBER):;@:)
endif


# Run tests
run:
	$(CXX) $(SOURCES) $(TESTS) $(STD) $(TEST_FLAGS) $(SAN)
	./a.out
	rm ./a.out

clean:
	rm *.o
	rm *.out