#include <SFML/Graphics.hpp>

#include "ball.h"
#include "rectangle.h"
#include "action.h"

int
main(int argc, char ** argv)
{
   	sf::RenderWindow window(sf::VideoMode(720, 480), "CPSE2_1", sf::Style::Close);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
	sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(720, 480));

	float size = 20;
	float wallX = window.getSize().x;
	float wallY = window.getSize().y;
	Rectangle wall0(sf::Vector2f(wallX, size), sf::Vector2f(wallX/2, size/2), sf::Color::Green);
	Rectangle wall1(sf::Vector2f(wallX, size), sf::Vector2f(wallX/2, wallY-size/2), sf::Color::Red);
	Rectangle wall2(sf::Vector2f(size, wallY), sf::Vector2f(size/2, wallY/2), sf::Color::Yellow);
	Rectangle wall3(sf::Vector2f(size, wallY), sf::Vector2f(wallX-size/2, wallY/2), sf::Color::Blue);
	//
	Rectangle cursor(sf::Vector2f(40,40), sf::Vector2f(0,0), sf::Color::Magenta, true);
	Ball ball(20, 60, sf::Vector2f(60,60), 3, sf::Color::White);

	std::vector<Shape *> shapes = {&wall0, &wall1, &wall2, &wall3, &cursor, &ball};
	
	Action actions[] =
	{
		Action( [&]()
		{
			for(Shape * shape : shapes)
			{
				if(ball.interact(shape->body))
				{
					break;
				}
			}
		}),
		Action( [&]()
		{
			for(Shape * shape : shapes)
			{
				shape->update();
			}
		}),
		Action( sf::Keyboard::A, [&](){ ball.velocity.x = -ball.speed; }),
		Action( sf::Keyboard::D, [&](){ ball.velocity.x = ball.speed; }),
		Action( sf::Keyboard::W, [&](){ ball.velocity.y = -ball.speed; }),
		Action( sf::Keyboard::S, [&](){ ball.velocity.y = ball.speed; }),
		Action( sf::Mouse::Right, [&](){ ball.body.setPosition( (sf::Vector2f)sf::Mouse::getPosition( window )); })
	};
	
	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
		
		for( Action & action : actions )
		{
			action();
		}
		
		cursor.body.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));

		window.clear(sf::Color::Black);
		for(Shape * shape : shapes)
		{
			shape->draw(window);
		}
		window.display();
	}
	return 0;
}