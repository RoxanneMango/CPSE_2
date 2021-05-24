#if defined(_WIN32) || defined(__LINUX__) || defined(__APPLE__)
	#include "tic_tac_toe_GUI.h"
	#define TicTacToe TicTacToeGUI
#else
	#include "tic_tac_toe.h"
#endif

int
main(int argc, char ** argv)
{
	TicTacToe ttt('X','O');	

	while(ttt.isRunning)
	{
		ttt.clear();
		ttt.draw();
		ttt.handleInput();
		ttt.update();
	}
	
	return 0;
}