#include <SFML/Graphics.hpp>

#include "ball.h"
#include "rectangle.h"

int
main(int argc, char ** argv)
{
   	sf::RenderWindow window(sf::VideoMode(720, 480), "CPSE2_1", sf::Style::Close);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
	sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(720, 480));

	Ball ball(20, 60, sf::Vector2f(60,60), 3, sf::Color::White);
	//
	float size = 20;
	float wallX = window.getSize().x;
	float wallY = window.getSize().y;
	Rectangle wall0(sf::Vector2f(wallX, size), sf::Vector2f(wallX/2, size/2), sf::Color::Green);
	Rectangle wall1(sf::Vector2f(wallX, size), sf::Vector2f(wallX/2, wallY-size/2), sf::Color::Red);
	Rectangle wall2(sf::Vector2f(size, wallY), sf::Vector2f(size/2, wallY/2), sf::Color::Yellow);
	Rectangle wall3(sf::Vector2f(size, wallY), sf::Vector2f(wallX-size/2, wallY/2), sf::Color::Blue);
	Rectangle cursor(sf::Vector2f(40,40), sf::Vector2f(0,0), sf::Color::Magenta, true);
	//
	std::vector<Shape *> C_O;
	C_O.push_back(&wall0);
	C_O.push_back(&wall1);
	C_O.push_back(&wall2);
	C_O.push_back(&wall3);
	C_O.push_back(&cursor);
	
	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
		cursor.body.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
		for(unsigned int i = 0; i < C_O.size(); ++i)
		{
			float deltaX = ball.body.getPosition().x - C_O[i]->body.getPosition().x;
			float deltaY = ball.body.getPosition().y - C_O[i]->body.getPosition().y;
			//
			float intersectX = abs(deltaX) - (ball.body.getOrigin().x + C_O[i]->body.getOrigin().x);
			float intersectY = abs(deltaY) - (ball.body.getOrigin().y + C_O[i]->body.getOrigin().y);
			//
			if(intersectX < 0.0f && intersectY < 0.0f)
			{	
				if(intersectX > intersectY)				// X_AXIS
				{
					if(deltaX > 0.0f)
						ball.velocity.x = ball.speed;		// LEFT_C
					else
						ball.velocity.x = -ball.speed;		// RIGHT_C
				}
				else									// Y_AXIS
				{
					if(deltaY > 0.0f)
						ball.velocity.y = ball.speed;		// DOWN_C
					else
						ball.velocity.y = -ball.speed;		// TOP_C
				}
				break;
			}
		}
		ball.update();
		
		window.clear(sf::Color::Black);
		
		for(unsigned int i = 0; i < C_O.size(); ++i)
			C_O[i]->draw(window);
		ball.draw(window);
		
		window.display();
	}
	return 0;
}

// https://github.com/RoxanneMango/CPSE_2