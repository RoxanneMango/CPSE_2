#include "ball.h"

Ball::Ball(int radius,int points, sf::Vector2f pos, int speed, sf::Color color) : speed(speed), velocity(speed, speed), body(radius, points), Shape(body)
{
	body.setOrigin(radius, radius);
	body.setPosition(pos);
	body.setFillColor(color);		
}
Ball::~Ball()
{}

void
Ball::update()
{
	body.move(velocity);
}

void
Ball::draw(sf::RenderWindow & window)
{
	window.draw(body);
}