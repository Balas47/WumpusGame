driver.out: driver.cpp playerClass.o caveClass.o gameDriver.o
	g++ -Wall driver.cpp playerClass.o caveClass.o gameDriver.o -o driver.out

playerClass.o: playerClass.h playerClass.cpp
	g++ -Wall playerClass.h playerClass.cpp -c

caveClass.o: caveClass.h caveClass.cpp
	g++ -Wall caveClass.h caveClass.cpp -c

gameDriver.o: gameDriver.h gameDriver.cpp
	g++ -Wall gameDriver.h gameDriver.cpp -c

clear:
	rm *.o
	rm *.gch
	rm *~
git:
	git add .
	git rm -f *.out
	git rm -f *.gch
