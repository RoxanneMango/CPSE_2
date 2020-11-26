.PHONY : all run clean play linux

INCLUDE = -I../../SFML-2.5.1/include
LIB = -L../../SFML-2.5.1/lib -L../LSFML-2.5.1/bin
LIBS = 	-lsfml-graphics -lsfml-window -lsfml-system
EXEC = main

all:
	@echo "Making object files. . ."
	@g++ -c *.cpp $(INCLUDE) -std=c++11
	@echo "Doing stuff with object files. . ."
	@g++ *.o -o $(EXEC) $(LIB) $(LIBS) -static
	@./$(EXEC)

clean: 
	@echo "Removing object files again. . ."
	@del *.o
	@del *.exe

play:
	@$(EXEC)
	
linux:
	@echo "Making object files. . ."
	@g++ -c *.cpp $(INCLUDE) -std=c++11
	@echo "Doing stuff with object files. . ."
	@g++ *.o -o $(EXEC) $(LIB) $(LIBS)
	@echo "Removing object files again. . ."
	@rm *.o