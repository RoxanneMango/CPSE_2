#include <stdio.h>
#include <cstring>

#include <SFML/Graphics.hpp>

#include "action.h"
#include "cursor.h"

#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include "line.h"
#include "picture.h"

void processOrders(const char * PATH, std::vector<std::vector<std::string>> & orderList);
void save(const char * PATH, std::vector<Shape *> & shapes);

Shape * shapeFactory(std::vector<std::string> s);

int
main(int argc, char ** argv)
{
	Cursor cursor(sf::Vector2f(30,30), sf::Color::Transparent, sf::Color::Magenta, sf::Color::White);

	std::vector<std::vector<std::string>> orderList;
	processOrders("orders.txt", orderList);

	std::vector<Shape *> shapes;
	for(std::vector<std::string> & order : orderList)
	{
		shapes.push_back(shapeFactory(order));
	}
	shapes.push_back(&cursor);

	sf::RenderWindow window(sf::VideoMode(720, 480), "CPSE2_1", sf::Style::Close);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
	sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(720, 480));

	Action actions[] =
	{
		Action( [&]()
		{
			cursor.body.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
		}),
		Action( sf::Mouse::Right, [&]()
		{
			for(Shape * shape : shapes)
			{
				shape->interact(cursor.body);
			}
		}),
		Action( [&]()
		{
			for(Shape * shape : shapes)
			{
				shape->update();
			}
		})
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

		window.clear(sf::Color::Black);
		for(Shape * shape : shapes)
		{
			shape->draw(window);
		}
		window.display();
	}
	
	save("orders.txt", shapes);
	
	return 0;
}

Shape *
shapeFactory(std::vector<std::string> s)
{
	if(s.size() == 0)
	{
		printf("Error : Empty order ...");
		goto error;
	}
	
	switch(atoi(&s[0][0]))
	{
		case 0: // Circle
		{
			if(s.size() < 17)
			{
				printf("Error : Not enough parameters for Circle shape ...");
				goto error;
			}
			return new Circle(
				sf::Vector2f(atoi(&s[1][0]),atoi(&s[2][0])), 
				atoi(&s[3][0]), 
				sf::Color(atoi(&s[4][0]),atoi(&s[5][0]),atoi(&s[6][0]),atoi(&s[7][0])), 
				sf::Color(atoi(&s[8][0]),atoi(&s[9][0]),atoi(&s[10][0]),atoi(&s[11][0])), 
				sf::Color(atoi(&s[12][0]),atoi(&s[13][0]),atoi(&s[14][0]),atoi(&s[15][0])), 
				atoi(&s[16][0]));
		}
		case 1: // Rectangle
		{
			if(s.size() < 18)
			{
				printf("Error : Not enough parameters for Rectangle shape ...");
				goto error;
			}
			return new Rectangle(
				sf::Vector2f(atoi(&s[1][0]),atoi(&s[2][0])), 
				sf::Vector2f(atoi(&s[3][0]),atoi(&s[4][0])),
				sf::Color(atoi(&s[5][0]),atoi(&s[6][0]),atoi(&s[7][0]),atoi(&s[8][0])), 
				sf::Color(atoi(&s[9][0]),atoi(&s[10][0]),atoi(&s[11][0]),atoi(&s[12][0])),
				sf::Color(atoi(&s[13][0]),atoi(&s[14][0]),atoi(&s[15][0]),atoi(&s[16][0])),
				atoi(&s[17][0]));
		}
		case 2: // Triangle
		{
			if(s.size() < 17)
			{
				printf("Error : Not enough parameters for Triangle shape ...");
				goto error;
			}
			return new Triangle(
				sf::Vector2f(atoi(&s[1][0]),atoi(&s[2][0])), 
				atoi(&s[3][0]), 
				sf::Color(atoi(&s[4][0]),atoi(&s[5][0]),atoi(&s[6][0]),atoi(&s[7][0])), 
				sf::Color(atoi(&s[8][0]),atoi(&s[9][0]),atoi(&s[10][0]),atoi(&s[11][0])), 
				sf::Color(atoi(&s[12][0]),atoi(&s[13][0]),atoi(&s[14][0]),atoi(&s[15][0])), 
				atoi(&s[16][0]));
		}
		case 3: // Line
		{
			if(s.size() < 18)
			{
				printf("Error : Not enough parameters for Line shape ...");
				goto error;
			}
			return new Line(
				sf::Vector2f(atoi(&s[1][0]), atoi(&s[2][0])), 
				atoi(&s[3][0]), 
				atoi(&s[4][0]), 
				sf::Color(atoi(&s[5][0]),atoi(&s[6][0]),atoi(&s[7][0]),atoi(&s[8][0])), 
				sf::Color(atoi(&s[9][0]),atoi(&s[10][0]),atoi(&s[11][0]),atoi(&s[12][0])), 
				sf::Color(atoi(&s[13][0]),atoi(&s[14][0]),atoi(&s[15][0]),atoi(&s[16][0])), 
				atoi(&s[17][0]));
		}
		case 4: // Picture
		{
			if(s.size() < 15)
			{
				printf("Error : Not enough parameters for Picture shape ...");
				goto error;
			}
			return new Picture(
			sf::Vector2f(atoi(&s[1][0]), atoi(&s[2][0])), 
			sf::Vector2f(atoi(&s[3][0]), atoi(&s[4][0])), 
			s[5],
			sf::Color(atoi(&s[6][0]),atoi(&s[7][0]),atoi(&s[8][0]),atoi(&s[9][0])), 
			sf::Color(atoi(&s[10][0]),atoi(&s[11][0]),atoi(&s[12][0]),atoi(&s[13][0])),
			atoi(&s[14][0]));
		}
		default:
		{
			printf("Error : Invalid shape ID ...");
			goto error;
		}
	}

error:
	if(s.size() > 0)
	{
		printf(" in order ");
		for(std::string value : s)
		{
			printf("%d ", atoi(&value[0]));
		}
		printf("...");
	}
	printf("\n");
	exit(-1);
}

void
processOrders(const char * PATH, std::vector<std::vector<std::string>> & orderList)
{	
	FILE * FP = NULL;
	if((FP = fopen(PATH, "r")) == NULL)
	{
		printf("Could not open file (%s)\n", PATH);
		exit(-1);
	}
	char buffer[32];
	memset(buffer, 0, 32);

	unsigned int index = 0;

	orderList.push_back(std::vector<std::string>());

	while (fscanf(FP, " %32s", buffer) == 1) {
		if(!strcmp(buffer, ";"))
		{
			orderList.push_back(std::vector<std::string>());
			index += 1;
			continue;
		}
		orderList[index].push_back(buffer);
		memset(buffer, 0, 32);
	}
	// remove extra element at the end:
	orderList.erase(orderList.begin() + index);
	
	fclose(FP);
}

void
save(const char * PATH, std::vector<Shape *> & shapes)
{
	FILE * FP = NULL;
	if((FP = fopen(PATH, "w")) == NULL)
	{
		printf("Could not save to file (%s) !\n", PATH);
		return;
	}
	for(Shape * shape : shapes)
	{
		if(shape->id >= 0)
		{
			fprintf(FP, "%s", &shape->getReceipt()[0]);
		}
	}
	fclose(FP);
}