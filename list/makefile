include ../rule.mk

main: main.o list.o
	$(CXX) -o $@ $^
sources = list.cpp main.cpp
include $(sources:.cpp=.dpp)

clean:
	rm -rf *.o
