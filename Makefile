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
  TASK_NAMBER := $(word 2, $(MAKECMDGOALS))
  SOURCES = $(wildcard tasks/$(TASK_NAMBER)/*.cpp)
  HEADERS = $(wildcard tasks/$(TASK_NAMBER)/*.hpp)
  TESTS = $(wildcard tests/$(TASK_NAMBER)/*.cpp)
  $(eval $(TASK_NAMBER):;@:)
endif


# Run tests
run:
	$(CXX) $(SOURCES) $(TESTS) $(STD) $(TEST_FLAGS) $(SAN)
	./a.out
	rm ./a.out

clean:
	rm *.o
	rm *.out