.PHONY: clean

CXX = clang++
STD = -std=c++20

# FILE := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
# $(eval $(FILE):;@:)
# FILE := $(FILE)/$(FILE)

ASAN := -fsanitize=address
UBSAN := -fsanitize=undefined
SAN := -fsanitize=undefined,address
TEST_FLAGS := -lgtest -lgmock -pthread

ifeq (test,$(firstword $(MAKECMDGOALS)))
  TEST_NUMBER := $(word 2, $(MAKECMDGOALS))
  TEST_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  TEST_RUN := $(foreach arg, $(TEST_ARGS), $(arg).cpp)
  TEST_OUT := $(foreach arg, $(TEST_ARGS), $(arg).o)
  $(eval $(TEST_ARGS):;@:)
endif

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
	$(CXX) -c tasks/first/AVLTree.cpp  $(SAN) -o tests/first/AVLTree.o $(STD)
	$(CXX) -c tasks/first/Node.cpp  $(SAN) -o tests/first/Node.o $(STD)
	$(CXX) -c tests/first/first.cpp $(SAN) -o tests/first/first.o $(STD)
	$(CXX) tests/first/Node.o tests/first/AVLTree.o tests/first/first.o -o tests/first/result.out $(TEST_FLAGS) $(SAN)
	./tests/first/result.out
	rm tests/first/*.o tests/first/*.out

test-2:
	$(CXX) -c tasks/second/Line.cpp  $(SAN) -o tests/second/Line.o $(STD)
	$(CXX) -c tests/second/second.cpp $(SAN) -o tests/second/second.o $(STD)
	$(CXX) tests/second/Line.o tests/second/second.o -o tests/second/result.out $(TEST_FLAGS) $(SAN)
	./tests/second/result.out
	rm tests/second/*.o tests/second/*.out 


test-5:
	$(CXX) tests/fifth/fifth.cpp $(SAN) -o tests/fifth/result.out $(STD) $(TEST_FLAGS) $(SAN)
	./tests/fifth/result.out 
	rm tests/fifth/*.out 


test-6:
	$(CXX) tasks/sixth/SquareMatrix.cpp tests/sixth/sixth.cpp $(SAN) -o tests/sixth/result.out $(STD) $(TEST_FLAGS) $(SAN)
	./tests/sixth/result.out 
	rm tests/sixth/*.out 

test:
	echo $(TEST_NUMBER)
	echo $(TEST_ARGS)
	echo $(TEST_OUT)


clean:
