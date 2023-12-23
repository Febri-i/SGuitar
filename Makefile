build: out/Chord.o out/main.o
	g++ ./out/main.o ./out/Chord.o -o ./out/chordshuffle
	@echo successfully build chordshuffle.

install:
	@mv ./out/chordshuffle $(PREFIX)/bin

out/main.o: src/main.cpp
	@mkdir -p out
	g++ -c -I./includes ./src/main.cpp -o ./out/main.o

out/Chord.o: src/Chord.cpp
	@mkdir -p out
	g++ -c -I./includes src/Chord.cpp -o ./out/Chord.o

clean: 
	@if [ -d "./out" ]; then rm ./out/*; fi
