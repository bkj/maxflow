all :
	mkdir -p bin
	make ffa
	make pr

ffa : ffa.cpp
	g++ -std=c++11 -o bin/ffa $^

pr : pr.cpp
	g++ -std=c++11 -o bin/pr $^

clean :
	rm -rf bin
