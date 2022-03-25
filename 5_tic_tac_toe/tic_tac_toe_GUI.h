#ifndef TIC_TAC_TOE_GUI
#define TIC_TAC_TOE_GUI

#include <SFML/Graphics.hpp>

#include "tic_tac_toe.h"

class TicTacToeGUI : public TicTacToe
{
private:
	sf::RenderWindow window;
	sf::View view;
	sf::Event event;
	
	sf::Font font;
	
	sf::Text board_sf;
	sf::Text topText_sf;
	sf::Text errorText_sf;
	sf::Text bottomText_sf;

	virtual void getInput() override
	{
		// set initial input to 0
		input = 0;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
			if(event.type == sf::Event::TextEntered)
			{
				// check if input falls within the ASCII range
				if (event.text.unicode < 128)
				{
					input = event.text.unicode;
				}
				if(isEnd)
				{
					isRunning = false;
				}
				isKeyPressed = true;
			}
		}
	}
	
public:
	TicTacToeGUI(char p1, char p2) : 
		window(sf::VideoMode(720, 480), "CPSE2_5", sf::Style::Close), 
		view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(720, 480)),
		TicTacToe(p1, p2),
		board_sf(board, font, 16),
		topText_sf(topText, font, 16),
		errorText_sf(errorText, font, 16),
		bottomText_sf(bottomText, font, 16)
	{
		window.setFramerateLimit(60);
		
		// if the font could not be loaded, just exit with error code -1
		if(!font.loadFromFile("Consolas.ttf")) exit(-1);
		
		// position the text fields
		topText_sf.setPosition(sf::Vector2f(0,0));
		board_sf.setPosition(sf::Vector2f(0, 3*16));
		bottomText_sf.setPosition(sf::Vector2f(0, 10*16));
		errorText_sf.setPosition(sf::Vector2f(0, 12*16));
	}
	virtual ~TicTacToeGUI()
	{}

	virtual void update() override
	{
		// if its the end, handle last input; getInput() will set isRunning to false, thus, ending the game.
		// this is to prevent the game from immediately exiting after the game ended, to allow the player(s)
		// to see the final score
		if(isEnd)
		{
			getInput();
		}
		else
		{
			// only update if something changed
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

				bottomText_sf.setString("player " + std::to_string(2 - player1Turn) + " (" + std::string(1, player1Turn ? player1 : player2) + ") input: ");
				if((isWinner = isWon()) || commandList.size() >= 9)
				{
					bottomText_sf.setString(isWinner ? std::string("player " + std::to_string(player1Turn+1) + " has won!") : std::string("game ended in a tie!"));
					isEnd = true;
					error = true;
					errorText.assign("press any key to exit . . .\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
				}
				board_sf.setString(board);
				errorText_sf.setString(errorText);				
				isKeyPressed = false;
			}
		}
		// if the window is no longer open, stop the game
		if(!window.isOpen()) isRunning = false;
	}
	
	virtual void draw() override
	{
		window.draw(topText_sf);
		window.draw(board_sf);
		window.draw(bottomText_sf);
		// only draw error text if an error occured
		if(error) window.draw(errorText_sf);
		window.display();
	}
	
	virtual void clear() override
	{
		window.clear(sf::Color::Black);
	}
};

#endif // TIC_TAC_TOE_GUI