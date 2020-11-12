#ifndef BALL_H
#define BALL_H

#include "shape.h"

class Ball : public Shape
{
public:
	sf::Vector2f velocity;
	sf::CircleShape body;
	int speed;

	Ball(int radius, int points, sf::Vector2f pos, int speed, sf::Color color);
	~Ball();
	
	bool interact(sf::Shape & body) override;
	void update() override;
	void draw(sf::RenderWindow & window) const override;
};

#endif // BALL_H