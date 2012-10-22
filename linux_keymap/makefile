keymap: keymap.o
	g++ -o $@ $<
keymap.o: keymap.cpp
	g++ -c $<
clean:
	rm -rf *.o keymap
