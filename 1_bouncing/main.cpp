#include <SFML/Graphics.hpp>

int
main(int argc, char ** argv)
{
   	sf::RenderWindow window(sf::VideoMode(720, 480), "CPSE2_1", sf::Style::Close);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
	sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(720, 480));

	int speed = 3;
	sf::Vector2f ballVelocity(speed,speed);
	sf::CircleShape ball(20, 60);
	ball.setOrigin(ball.getRadius(), ball.getRadius());
	ball.setPosition(sf::Vector2f(60,60));
	ball.setFillColor(sf::Color::White);

	std::vector<sf::RectangleShape *> C_O;
	//
	float wallX = window.getSize().x;
	float wallY = window.getSize().y;
	float size = 20;
	//
	sf::RectangleShape wall0(sf::Vector2f(wallX, size)); 
	wall0.setOrigin(wallX/2, size/2);
	wall0.setPosition( wallX/2, size/2 );
	wall0.setFillColor(sf::Color::Green);
	C_O.push_back(&wall0);
	//
	sf::RectangleShape wall1(sf::Vector2f(wallX, size)); 
	wall1.setOrigin(wallX/2, size/2);
	wall1.setPosition( wallX/2, wallY-size/2 );
	wall1.setFillColor(sf::Color::Red);
	C_O.push_back(&wall1);

	sf::RectangleShape wall2(sf::Vector2f(size, wallY));
	wall2.setOrigin(size/2, wallY/2);
	wall2.setPosition(size/2, wallY/2);
	wall2.setFillColor(sf::Color::Yellow);
	C_O.push_back(&wall2);
	//
	sf::RectangleShape wall3(sf::Vector2f(size, wallY));
	wall3.setOrigin(size/2, wallY/2);
	wall3.setPosition(wallX-size/2, wallY/2);
	wall3.setFillColor(sf::Color::Blue);
	C_O.push_back(&wall3);

	sf::RectangleShape cursor(sf::Vector2f(40,40)); cursor.setFillColor(sf::Color::Black); cursor.setFillColor(sf::Color::Magenta);
	cursor.setOrigin(cursor.getSize().x / 2, cursor.getSize().y / 2);
	cursor.setOutlineThickness(1);
	cursor.setOutlineColor(sf::Color::Magenta);
	cursor.setFillColor(sf::Color::Transparent);
	C_O.push_back(&cursor);
	
	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
		cursor.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
		for(unsigned int i = 0; i < C_O.size(); ++i)
		{
			float deltaX = ball.getPosition().x - C_O[i]->getPosition().x;
			float deltaY = ball.getPosition().y - C_O[i]->getPosition().y;
			//
			float intersectX = abs(deltaX) - (ball.getOrigin().x + C_O[i]->getOrigin().x);
			float intersectY = abs(deltaY) - (ball.getOrigin().y + C_O[i]->getOrigin().y);
			//
			if(intersectX < 0.0f && intersectY < 0.0f)
			{	
				if(intersectX > intersectY)			// X_AXIS
				{
					if(deltaX > 0.0f)
						ballVelocity.x = speed;		// LEFT_C
					else
						ballVelocity.x = -speed;	// RIGHT_C
				}
				else								// Y_AXIS
				{
					if(deltaY > 0.0f)
						ballVelocity.y = speed;		// DOWN_C
					else
						ballVelocity.y = -speed;	// TOP_C
				}
				break;
			}
		}
		ball.move(ballVelocity);
		window.clear(sf::Color::Black);
		for(unsigned int i = 0; i < C_O.size(); ++i)
		window.draw(*C_O[i]);
		window.draw(ball);
		window.display();
	}
}