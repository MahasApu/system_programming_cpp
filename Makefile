.PHONY: clean

CXX = clang++
FILE := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
$(eval $(FILE):;@:)
FILE := $(FILE)/$(FILE)

use-clang: 
	$(CXX) tasks/$(FILE).cpp -o tasks/$(FILE).out
	./tasks/$(FILE).out

use-asan:
	$(CXX) tasks/$(FILE).cpp -o tasks/$(FILE).out -fsanitize=address
	./tasks/$(FILE).out

use-ubsan:
	$(CXX) tasks/$(FILE).cpp -o tasks/$(FILE).out -fsanitize=undefined
	./tasks/$(FILE).out

use-san:
	$(CXX) tasks/$(FILE).cpp -o tasks/$(FILE).out -fsanitize=undefined,address
	./tasks/$(FILE).out

run-tests:
	$(CXX) tests/$(FILE).cpp -o tests/$(FILE).out -lgtest -lgmock -pthread
	./tests/$(FILE).out

clean:
