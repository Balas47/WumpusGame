driver.out: driver.cpp playerClass.o caveClass.o
	g++ -Wall driver.cpp playerClass.o caveClass.o -o driver.out

playerClass.o: playerClass.h playerClass.cpp
	g++ -Wall playerClass.h playerClass.cpp -c

caveClass.o: caveClass.h caveClass.cpp
	g++ -Wall caveClass.h caveClass.cpp -c

clear:
	rm *~
	rm *.o
	rm *.gch
