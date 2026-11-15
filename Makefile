CXX ?= g++
CPPFLAGS += -Iinclude $(shell pkg-config --cflags libmariadb openssl)
CXXFLAGS ?= -std=c++14 -O2 -g -Wall -Wextra -Wpedantic
LDLIBS += -pthread $(shell pkg-config --libs libmariadb openssl)
SOURCES := $(filter-out src/main.cpp,$(wildcard src/*.cpp))
OBJECTS := $(patsubst src/%.cpp,build/%.o,$(SOURCES))
TESTS := $(wildcard tests/test_*.cpp)
.PHONY: all test integration check clean
all: bin/webserve
build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@
bin/webserve: $(OBJECTS) build/main.o
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@
bin/unit_tests: $(OBJECTS) $(TESTS) tests/unit_main.cpp
	@mkdir -p bin
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(OBJECTS) $(TESTS) tests/unit_main.cpp $(LDLIBS) -o $@
test: bin/unit_tests
	./bin/unit_tests
integration: all
	python3 tests/integration.py
check: test integration
clean:
	rm -rf build bin
-include $(wildcard build/*.d)
