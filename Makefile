CXXFLAGS = -Isdl2/32bit/include/SDL2 -std=c++0x
LXXFLAGS = -Lsdl2/32bit/lib -lmingw32 -lSDL2main -lSDL2

main: main.o character.o game.o accessories.o map.o endscreen.o character.hpp game.hpp accessories.hpp map.hpp tile.hpp endscreen.hpp
	g++ main.o character.o game.o accessories.o map.o endscreen.o -o main $(LXXFLAGS)

main.o: main.cpp game.hpp
	g++ main.cpp -c $(CXXFLAGS)

character.o: character.cpp character.hpp
	g++ character.cpp -c $(CXXFLAGS)

game.o: game.cpp game.hpp endscreen.hpp
	g++ game.cpp -c $(CXXFLAGS)

accessories.o: accessories.cpp accessories.hpp
	g++ accessories.cpp -c $(CXXFLAGS)

map.o: map.cpp map.hpp
	g++ map.cpp -c $(CXXFLAGS)

endscreen.o: endscreen.cpp endscreen.hpp
	g++ endscreen.cpp -c $(CXXFLAGS)

run: main
	main