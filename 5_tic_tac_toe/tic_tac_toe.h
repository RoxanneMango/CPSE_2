#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include "stdio.h"

#include <vector>
#include <string>

/* * * * * * * * * * *
*
*	Tic-tac-toe board
*
*	 O | X | X 
*	---|---|---
*	 X | O | X
*	---|---|---
*	 X | O | O
*
* * * * * * * * * * */

typedef struct Command
{
	bool isPlayer1;
	unsigned int pos;
} Command;

class TicTacToe
{
protected:
	static constexpr unsigned int WIDTH = 12;
	static constexpr unsigned int HEIGHT = 5;

	unsigned int numOfUndos = 0;
	unsigned int maxNumOfUndos = 1;
	
	char input;
	char player1;
	char player2;

	bool error = false;
	bool isEnd = false;
	bool isWinner = false;
	bool player1Turn = true;
	bool isKeyPressed = false;

	std::string board = {"   |   |   \n---|---|---\n   |   |   \n---|---|---\n   |   |   \n"};
	std::string topText = {"Controls:\ntop row: 1,2,3; mid row: 4, 5, 6; bottom row: 7,8,9; quit: q; undo: u;\n"};
	std::string errorText;
	std::string bottomText;
	
	std::vector<Command> commandList;
	
	virtual void getInput()
	{
		isKeyPressed = true;
		input = getchar();
		for(int c; (c = getchar()) != EOF && c != '\n';);
	}
	
	bool isWon()
	{
		// Check if there are enough turns to have a winner
		if(commandList.size() > 4)
		{
			// Recreate the board and populate it with values that are not '1' or '0'; doesn't really matter which number
			// in this case it's the number 3.
			// manually filled in since memset() would require the #include'sion of <cstring> or "string.h" and it feels
			// unnecessary to include it solely for that
			int board[3 * 3] = {3,3,3,3,3,3,3,3,3};
			
			// player1Turn gets flipped before the isWon calculation; this flips it back
			int turn = 1 - player1Turn;
			
			// populate dummy board with the turns from commandList
			for(unsigned int i = 0; i < commandList.size(); ++i)
			{
				unsigned int x = ( (commandList[i].pos % WIDTH - 1) / 3 );
				unsigned int y = (commandList[i].pos / WIDTH) ? (commandList[i].pos / WIDTH) / 2 : 0;
				board[(y * 3) + x] = commandList[i].isPlayer1;
			}

			// set initial win condition to true
			bool isSame = true;
			
			// check for horizontal wins
			for(unsigned int y = 0; y < 3; ++y)
			{
				// new row, new chances
				isSame = true;
				for(unsigned int x = 0; (x < 3) && isSame; ++x)
				{
					// if the pattern is broken, go back to previous loop to start over
					// else keep counting and if there's 3 in a row, return true
					if(board[(y * 3) + x] != turn) isSame = false;
					else if(x >= 2) return true;
				}
			}
			// vertical
			for(unsigned int x = 0; x < 3; ++x)
			{
				isSame = true;
				for(unsigned int y = 0; (y < 3) && isSame; ++y)
				{
					if(board[(y * 3) + x] != turn) isSame = false;
					else if(y >= 2) return true;
				}
			}
			// check for three in a row diagonally
			// Too smol brain for fancy for loop construction; quick 'n dirty logic sausage monstrosity...
			if((board[4] == turn) && (((board[0] == turn) && (board[8] == turn)) || ((board[2] == turn) && (board[6] == turn))))
			{
				return true;
			}
		}
		return false;
	}
	
public:
	bool isRunning = true;

	TicTacToe(char p1, char p2) : player1(p1), player2(p2), bottomText("player " + std::to_string(2-player1Turn) + " (" + (player1Turn ? player1 : player2) + ") input: ")
	{}
	virtual ~TicTacToe()
	{}
	
	void handleInput()
	{
		// skip this function if the game is already over; avoid stalling due to getchar() waiting for input
		if(isEnd || (commandList.size() >= 9)) return;
		
		getInput();
		
		// only handle input if there is input
		if(isKeyPressed)
		{
			try
			{	
				// reset error flag
				error = false;
				
				// quit
				if(input == 'q')
				{
					isRunning = false;
					return;
				}
				
				// undo
				if(input == 'u')
				{
					if( (commandList.size() > 0) && (numOfUndos < maxNumOfUndos) )
					{
						commandList.pop_back();
						numOfUndos++;
						
						// flip player turn back to previous player
						player1Turn = player1Turn ? 0 : 1;
					}
					else
					{
						throw "could not undo";
					}
					return;
				}
				
				// convert char input to decimal number
				input = input - '0';
				if((input < 1) || (input > 9)) throw "invalid input";
				
				// calculate the position within the board
				unsigned int x = ((input-1)%3);
				unsigned int y = input <= 3 ? 0 : input <= 6 ? 2 : 4;
				unsigned int pos = (y * WIDTH) + (x + (x * 3) + 1);
				
				// only touch it if it's not empty
				if(commandList.size() > 0)
				{
					// check if the space is already occupied, if so, throw an error message which will be displayed
					// to the user
					for(unsigned int i = 0; i < commandList.size(); ++i)
					{
						if(commandList[i].pos == pos) throw "space is already occupied";
					}
				}
				// if the move is valid (no invalid input or occupied spaces), push a new Command to the commandList
				// and reset the number of undos
				commandList.push_back(Command{player1Turn, pos});
				numOfUndos = 0;
			}
			catch(const char * exception)
			{
				// an error occured: set error flag to true and populate errorText with the error that was thrown
				error = true;
				errorText.assign(std::string(exception) + " . . .\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
			}
		}
	}
	
	virtual void update()
	{
		// once the last cycle has been done to draw the final state of the board, the game will stop by setting
		// isRunning to false and returning
		if(isEnd)
		{
			isRunning = false;
			return;
		}
		
		// only update if something changed (a key was pressed)
		if(isKeyPressed)
		{
			// Build the board based on the moves saved in commandList
			board.assign("   |   |   \n---|---|---\n   |   |   \n---|---|---\n   |   |   \n");
			for(unsigned int i = 0; i < commandList.size(); ++i)
			{
				board[commandList[i].pos] = commandList[i].isPlayer1 ? player1 : player2;
			}
			
			// flip player turn if the turn was valid and wasn't an undo
			if(isRunning && !error && input != 'u')
			{	
				player1Turn = player1Turn ? false : true;
			}

			bottomText.assign("player " + std::to_string(2-player1Turn) + " (" + (player1Turn ? player1 : player2) + ") input: ");
			if((isWinner = isWon()) || commandList.size() >= 9)
			{
				if(isWinner)
				{
					bottomText.assign("player " + std::to_string(player1Turn+1) + " has won!");
				}
				else
				{
					bottomText.assign("game ended in a tie!");
				}
				// flag signifies the end but allows for one more cycle of drawing the board in text mode
				// game would end prematurely if isRunning was set to false here directly.
				isEnd = true;
			}
			isKeyPressed = false;
		}
	}
	
	virtual void draw()
	{
		printf("\n%s%s%s%s", error ? errorText.c_str() : "", topText.c_str(), board.c_str(), bottomText.c_str());
	}
	
	virtual void clear()
	{
		printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	}
};

#endif // TIC_TAC_TOE_H