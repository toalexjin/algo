
CPPFLAGS=-Wall -I. -std=c++11
LDFLAGS=-Wall

BINARY_NAME=testalgo
SOURCE_FILES=$(wildcard ./algo/*.cpp ./test/*.cpp)
OBJECT_FILES=$(patsubst %.cpp,%.o,$(SOURCE_FILES))


build: $(OBJECT_FILES)
	g++ $(LDFLAGS) -o $(BINARY_NAME) $^

%.o: %.cpp
	g++ $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(BINARY_NAME) $(OBJECT_FILES)

echo:
	@echo $(CPPFLAGS)
	@echo $(LDFLAGS)
	@echo $(BINARY_NAME)
	@echo $(SOURCE_FILES)
	@echo $(OBJECT_FILES)
