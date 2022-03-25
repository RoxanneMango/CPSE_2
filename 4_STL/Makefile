.PHONY : all clean play

INCLUDE =
LIB = 
EXEC = main

all:
	@echo "Making object files. . ."
	@g++ -c *.cpp $(INCLUDE) -std=c++17
	@echo "Doing stuff with object files. . ."
	@g++ *.o -o $(EXEC) $(LIB)
	@./$(EXEC)

clean: 
	@echo "Removing object files again. . ."
	@del *.o
	@del *.exe

play:
	@$(EXEC)