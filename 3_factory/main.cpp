#include <stdio.h>

#include <vector>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "line.h"
#include "action.h"
#include "cursor.h"
#include "circle.h"
#include "picture.h"
#include "triangle.h"
#include "rectangle.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * * * * * */

// Color struct containing name in string format and a sf::Color equivalent
typedef struct Color
{
	std::string name;
	sf::Color color;
} Color;

// a key-value entry object
typedef struct KeyValue
{
	std::string key;
	std::string value;
} KeyValue;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * * * * * */

// function declarations (definition at the bottom of main())
Color getColor(std::string & name);
Color getColor(sf::Color color);
Shape * shapeFactory(std::vector<KeyValue> & order);
void load(const char * PATH, std::vector<std::vector<KeyValue>> & orderList);
void save(const char * PATH, std::vector<Shape *> & shapes);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * * * * * */

int
main(int argc, char ** argv)
{
	// colission object which acts as cursor, to offer a wider surface to interact with other objects
	Cursor cursor(sf::Vector2f(30,30), sf::Color::Transparent, sf::Color::Magenta, sf::Color::White);

	// define the orderList and feed it to the load function, which will populate it
	std::vector<std::vector<KeyValue>> orderList;
	load("orders.txt", orderList);

	// define list of shapes and populate it by systematically feeding orders from the orderList into the
	// shapeFactory function, which creates Shape objects
	std::vector<Shape *> shapes;
	for(std::vector<KeyValue> & order : orderList)
	{
		shapes.push_back(shapeFactory(order));
	}

	// push the cursor colission object to the list of shapes; it is always last in the list
	shapes.push_back(&cursor);

	// setup the render window, etc ...
	sf::RenderWindow window(sf::VideoMode(720, 480), "CPSE2_3", sf::Style::Close);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
	sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(720, 480));

	// push actions to array of actions
	Action actions[] =
	{
		Action( [&]()
		{
			// update position of cursor colission object so its the same as the actual mouse position
			cursor.body.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
		}),
		Action( sf::Mouse::Right, [&]()
		{
			// attempt to interact with a Shape object. If it collides with the cursor object, interaction will take place
			for(Shape * shape : shapes)
			{
				shape->interact(cursor.body);
			}
		}),
		Action( sf::Keyboard::A, [&]()
		{
			// move shape left if the shape is selected
			for(Shape * shape : shapes)
			{
				if(shape->isSelected)
				{
					shape->velocity.x = -shape->speed;
				}
			}
		}),
		Action( sf::Keyboard::D, [&]()
		{
			// move shape right if the shape is selected
			for(Shape * shape : shapes)
			{
				if(shape->isSelected)
				{
					shape->velocity.x = shape->speed;
				}
			}
		}),
		Action( sf::Keyboard::W, [&]()
		{
			// move shape up if the shape is selected
			for(Shape * shape : shapes)
			{
				if(shape->isSelected)
				{
					shape->velocity.y = -shape->speed;
				}
			}
		}),
		Action( sf::Keyboard::S, [&]()
		{
			// move shape down if the shape is selected
			for(Shape * shape : shapes)
			{
				if(shape->isSelected)
				{
					shape->velocity.y = shape->speed;
				}
			}
		}),
		Action( [&]()
		{
			// update all shapes
			for(Shape * shape : shapes)
			{
				shape->update();
			}
		})
	};
	
	// handle events
	sf::Event event;
	while (window.isOpen())
	{
		// check input events
		while (window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		// perform all actions in actions array
		for( Action & action : actions )
		{
			action();
		}

		// clear the window and, then, draw all shapes to window and display them
		window.clear(sf::Color::Black);
		for(Shape * shape : shapes)
		{
			shape->draw(window);
		}
		window.display();
	}
	
	// once the game closes (gracefully), save shape configurations to save file and return 0
	save("orders.txt", shapes);

	return 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * * * * * */

// build Color structure based on color name in string format
Color
getColor(std::string & name)
{
	if(name == "black")		return Color{"black", sf::Color::Black};
	if(name == "white")		return Color{"white", sf::Color::White};
	if(name == "red")		return Color{"red", sf::Color::Red};
	if(name == "green")		return Color{"green", sf::Color::Green};
	if(name == "blue")		return Color{"blue", sf::Color::Blue};
	if(name == "yellow")	return Color{"yellow", sf::Color::Yellow};
	if(name == "magenta")	return Color{"magenta", sf::Color::Magenta};
	if(name == "cyan")		return Color{"cyan", sf::Color::Cyan};
	if(name == "transparent") return Color{"transparent", sf::Color::Transparent};

	printf("Could not match color (%s) to any colors in the list ...", name.c_str());

	// program cannot recover from this
	exit(-5);
}

// build Color structure based on sf::Color
Color
getColor(sf::Color color)
{
	if(color == sf::Color::Black)	return Color{"black", sf::Color::Black};
	if(color == sf::Color::White)	return Color{"white", sf::Color::White};
	if(color == sf::Color::Red)		return Color{"red", sf::Color::Red};
	if(color == sf::Color::Green)	return Color{"green", sf::Color::Green};
	if(color == sf::Color::Blue)	return Color{"blue", sf::Color::Blue};
	if(color == sf::Color::Yellow)	return Color{"yellow", sf::Color::Yellow};
	if(color == sf::Color::Magenta)	return Color{"magenta", sf::Color::Magenta};
	if(color == sf::Color::Cyan)	return Color{"cyan", sf::Color::Cyan};
	if(color == sf::Color::Transparent)	return Color{"transparent", sf::Color::Transparent};
	
	printf("Could not match sf::Color to any colors in the list ...");
	
	// program cannot recover from this
	exit(-6);
}

// build a Shape object with the attributes in order
Shape *
shapeFactory(std::vector<KeyValue> & order)
{
	try
	{
		// if the order is empty, too small, or too large, throw an error
		if(order.size() == 0)
		{
			throw "empty order";
		}
		else if(order.size() < 8)
		{
			throw "incomplete order";
		}
		else if(order.size() > 9)
		{
			throw "too many arguments inside order";
		}
		
		// extract shape name
		std::string shape = order[0].value;
		
		// check if its a known shape
		if(shape != "circle" && shape != "triangle" && shape != "rectangle" && shape != "line" && shape != "picture")
		{
			throw "unknown shape";
		}
		
		// half of the shapes have one extra argument. The offset will fill the 'gap' when instead of 8, there
		// are 9 key-value pairs
		bool offset = order.size() > 8 ? true : false;
		
		// define common arguments shared across all shapes		
		unsigned int posX = strtol(order[1].value.c_str(), NULL, 10);
		unsigned int posY = strtol(order[2].value.c_str(), NULL, 10);
		// pictures have a texture instead of a fillcolor
		sf::Color outlineColor = getColor(order[5 + offset].value).color;
		sf::Color selectColor = getColor(order[6 + offset].value).color;
		//
		int speed = strtol(order[7 + offset].value.c_str(), NULL, 10);
		
		// build objects according to id / name / type
		if(shape == "circle" || shape == "triangle")
		{
			// only circle and triangle shapes have a radius
			unsigned int radius = strtol(order[3].value.c_str(), NULL, 10);
			sf::Color fillColor = getColor(order[4 + offset].value).color;
			
			if(shape == "circle")
			{
				return new Circle(
					sf::Vector2f(posX, posY), radius,
					fillColor, outlineColor, selectColor,
					speed
				);
			}
			else
			{
				return new Triangle(
					sf::Vector2f(posX, posY), radius,
					fillColor, outlineColor, selectColor,
					speed
				);
			}
		}
		else if(shape == "rectangle" || shape == "picture")
		{
			unsigned int sizeX = strtol(order[3].value.c_str(), NULL, 10);
			unsigned int sizeY = strtol(order[4].value.c_str(), NULL, 10);
			
			if(shape == "rectangle")
			{
				sf::Color fillColor = getColor(order[5].value).color;
				
				return new Rectangle(
					sf::Vector2f(posX, posY), sf::Vector2f(sizeX, sizeY),
					fillColor, outlineColor, selectColor,
					speed
				);
			}
			else
			{
				// get PATH to load texture from
				std::string PATH = order[5].value;
				
				return new Picture(
					sf::Vector2f(posX, posY), sf::Vector2f(sizeX, sizeY),
					PATH.c_str(), outlineColor, selectColor,
					speed
				);
			}
		}
		else
		{
			unsigned int length = strtol(order[3].value.c_str(), NULL, 10);
			unsigned int rotation = strtol(order[4].value.c_str(), NULL, 10);
			sf::Color fillColor = getColor(order[5].value).color;
			
			return new Line(
				sf::Vector2f(posX, posY), length, rotation,
				fillColor, outlineColor, selectColor,
				speed
			);
		}
	}
	catch(const char * error)
	{
		printf("an error occured while building shape (%s) ... (%s)", order[0].value.c_str(), error);
		exit(-2);
	}
	catch( ... )
	{
		printf("an error occured while building shape (%s)", order[0].value.c_str());
		exit(-22);
	}
	exit(-222);
}

// load shape attributes from savefile
void
load(const char * PATH, std::vector<std::vector<KeyValue>> & orderList)
{
	// keep track of the line number while parsing for user feedback if something goes wrong
	unsigned int lineNumber = 0;
	try
	{
		// declare file stream
		std::ifstream ifs;
		// open file stream; if the fs could not be opened, an exception will be thrown
		ifs.open(PATH, std::ifstream::in);
		// check whether the file was actually opened. if not, throw an error
		if(!ifs.is_open())
		{
			throw "file failed to open";
		}

		bool isKey = true;
		bool isOrder = false;

		std::string key;
		std::string value;
		std::vector<KeyValue> order;
		
		char ch;
		
		// keep parsing until the end of file (EOF) is reached
		while(ifs.good())
		{
			ifs.get(ch);
			// don't use character if EOF was read
			if(ifs.eof())
			{
				continue;
			}
				
			if(ch == '\n')
			{
				lineNumber += 1;
			}
			else if(ch == '}' && isOrder) // signifies end of order
			{
				// check if order is valid
				if(order.size() > 0)
				{
					// push order to the orderList, and erase order for reuse
					orderList.push_back(order);
					order.erase(order.begin(), order.end());
					
					// order begins with a key
					isKey = true;
				}
				else
				{
					throw "order was malformed ...";
				}
				
				isOrder = false;
			}
			else if(ch == '{') // signifies begin of order
			{
				isOrder = true;
			}
			else if(isOrder)
			{
				if(ch == ':') // key-value divider
				{
					// what follows will be a value
					isKey = false;
				}
				else if(ch == ';') // end of key-value pair
				{
					// what follows will be a key
					isKey = true;
					
					// check if key and value are valid
					if(key.size()>0 && value.size()>0)
					{
						// push key-value pair to the order
						order.push_back({key, value});
						key.clear();
						value.clear();
					}
					else
					{
						throw "key-value pair was malformed ...";
					}
				}
				// check for whitespaces and opening curly brace
				else if(ch != ' ' && ch != '\t' && ch != '\'' && ch != '\"')
				{
					// if it's a key, add the letter to key, otherwise add it to value
					if(isKey)
					{
						key += ch;
					}
					else
					{
						value += ch;
					}
				}
			}
		}
		
		// close file stream again
		ifs.close();
	}
	catch(const char * error)
	{
		printf("Something went wrong while parsing file (%s) on line (%d) ... (%s)", PATH, lineNumber, error);
 
		// exit with error code -1 since the program cannot recover from a parsing error
		exit(-1);
	}
	catch( ... )
	{
		// if for some reason another exception occured which wasn't thrown by this function, exit with -111
		exit(-11);
	}
}

// save shape attributes to savefile
void
save(const char * PATH, std::vector<Shape *> & shapes)
{
	try
	{
		// pop off the cursor object so it doesn't get saved to the savefile
		shapes.pop_back();
		
		// start numbering the orders at 1
		unsigned int orderNum = 1;
		
		std::ofstream ofs;
		// open filestream and cycle through all the Shapes in the shapes vector
		ofs.open(PATH, std::ifstream::out);
		// check if file was opened. if not, throw an error
		if(!ofs.is_open())
		{
			throw "file failed to open";
		}
		
		for( Shape *& shape : shapes)
		{
			// print common attributes to file
			ofs << "order " << orderNum++ << " {\n";
			ofs << "\tshape: " << shape->name << ";\n";
			ofs << "\tpos_x: " << std::to_string((int)shape->body.getPosition().x) << ";\n";
			ofs << "\tpos_y: " << std::to_string((int)shape->body.getPosition().y) << ";\n";
			
			// print shape-specific size attributes
			if(shape->name == "circle" || shape->name == "triangle")
			{
				ofs << "\tradius: " << std::to_string(shape->radius) << ";\n";
			}
			else if(shape->name == "line")
			{
				ofs << "\tlength: " << std::to_string((int)shape->size.x) << ";\n";
				ofs << "\trotation: " << std::to_string((int)shape->body.getRotation()) << ";\n";
			}
			else
			{
				ofs << "\tsize_x: " << std::to_string((int)shape->size.x) << ";\n";
				ofs << "\tsize_y: " << std::to_string((int)shape->size.y) << ";\n";
			}
			
			// print either a texture or fill color
			if(shape->name == "picture")
			{
				ofs << "\ttexture: \"" << shape->PATH << "\";\n";
			}
			else
			{
				ofs << "\tfill_color: " << getColor(shape->fillColor).name << ";\n";		
			}
			
			// print remaining common attributes
			ofs << "\toutline_color: " << getColor(shape->outlineColor).name << ";\n";
			ofs << "\tselect_color: " << getColor(shape->selectColor).name << ";\n";			
			ofs << "\tspeed: " << std::to_string(shape->speed) << ";\n";
			ofs << "}\n";
		}
		ofs.close();
	}
	catch(const char * error)
	{
		// if for some reason an error occurs, don't overwrite savefile with corrupted data
		printf("could not open file (%s) ... (%s)\n", PATH, error);
		exit(-3);
	}
	catch( ... )
	{
		printf("an error occured while saving to file (%s)", PATH);
		exit(-33);
	}
}