#include "ball.h"

Ball::Ball(int radius,int points, sf::Vector2f pos, int speed, sf::Color color) : speed(speed), velocity(speed, speed), body(radius, points), Shape(body)
{
	body.setOrigin(radius, radius);
	body.setPosition(pos);
	body.setFillColor(color);		
}
Ball::~Ball()
{}

bool
Ball::interact(sf::Shape & body)
{
	if(&this->body == &body) return false; // if it is the same body return false by default
	
	float deltaX = this->body.getPosition().x - body.getPosition().x;
	float deltaY = this->body.getPosition().y - body.getPosition().y;
	//
	float intersectX = abs(deltaX) - (this->body.getOrigin().x + body.getOrigin().x);
	float intersectY = abs(deltaY) - (this->body.getOrigin().y + body.getOrigin().y);
	//	
	if(intersectX < 0.0f && intersectY < 0.0f)
	{	
		if(intersectX > intersectY)				// X_AXIS
		{
			if(deltaX > 0.0f)
				velocity.x = speed;		// LEFT_C
			else
				velocity.x = -speed;		// RIGHT_C
		}
		else									// Y_AXIS
		{
			if(deltaY > 0.0f)
				velocity.y = speed;		// DOWN_C
			else
				velocity.y = -speed;		// TOP_C
		}
		return true;
	}
	return false;
}

void
Ball::update()
{
	body.move(velocity);
}

void
Ball::draw(sf::RenderWindow & window) const
{
	window.draw(body);
}