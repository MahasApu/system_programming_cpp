.PHONY: clean

CXX = clang++
# FILE := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
# $(eval $(FILE):;@:)
# FILE := $(FILE)/$(FILE)

ASAN := -fsanitize=address
UBSAN := -fsanitize=undefined
SAN := -fsanitize=undefined,address
TEST_FLAGS := -lgtest -lgmock -pthread

# ifeq (test,$(firstword $(MAKECMDGOALS)))
#   # use the rest as arguments for "run"
#   TEST_NUMBER := $(word 2, $(MAKECMDGOALS))
#   TEST_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
#   TEST_RUN := $(foreach arg, $(TEST_ARGS), $(arg).cpp)
#   TEST_OUT := $(foreach arg, $(TEST_ARGS), $(arg).o)

#   # ...and turn them into do-nothing targets
#   $(eval $(TEST_ARGS):;@:)
# endif

use-clang: 
	$(CXX) tasks/$(FILE).cpp -o tasks/$(FILE).out
	./tasks/$(FILE).out

use-asan:
	$(CXX) tasks/$(FILE).cpp -o tasks/$(FILE).out $(ASAN)
	./tasks/$(FILE).out

use-ubsan:
	$(CXX) tasks/$(FILE).cpp -o tasks/$(FILE).out $(UBSAN)
	./tasks/$(FILE).out

use-san:
	$(CXX) tasks/$(FILE).cpp -o tasks/$(FILE).out $(SAN)
	./tasks/$(FILE).out

run-tests:
	$(CXX) tests/$(FILE).cpp -o tests/$(FILE).out $(TEST_FLAGS)
	./tests/$(FILE).out

test-1:
	$(CXX) -c tasks/first/AVLTree.cpp  $(SAN) -o tests/first/AVLTree.o 
	$(CXX) -c tests/first/first.cpp $(SAN) -o tests/first/first.o
	$(CXX) tests/first/AVLTree.o tests/first/first.o -o tests/first/result.out $(TEST_FLAGS) $(SAN)
	./tests/first/result.out

test-2:
	$(CXX) -c tasks/second/Line.cpp  $(SAN) -o tests/second/Line.o 
	$(CXX) -c tests/second/second.cpp $(SAN) -o tests/second/second.o
	$(CXX) tests/second/Line.o tests/second/second.o -o tests/second/result.out $(TEST_FLAGS) $(SAN)
	./tests/second/result.out

clean:
