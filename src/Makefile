main: main.o Song.o Songs.o myexception.o
	g++ main.o Song.o Songs.o myexception.o -o main 

main.o: main.cpp
	g++ -c main.cpp

Song.o: Song.cpp
	g++ -c Song.cpp

Songs.o: Songs.cpp
	g++ -c Songs.cpp

myexception.o: myexception.cpp
	g++ -c myexception.cpp

clean:
	rm *.o