run: compile execute clean


compile:
	g++ -std=c++20 -O3 -stdlib=libc++ -o executable main.cpp Packet.cpp

execute:
	./executable

clean: 
	rm executable


.PHONY: clean