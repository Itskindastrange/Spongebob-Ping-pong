#pragma once
#include "confidential.h"
_graphical_ball_interface_::_ball::_ball()
{
	// blank default cojnstructor
}
void _graphical_ball_interface_::_ball::_init_ball_(sf::RenderWindow *&wins,sf::Color _ball_color)
{	
	this->_radius_of_ball = 10;// const radius of ball
	this->speedx = 3;     // velocity x of ball
	this->speedy = 5;     // velocity y of ball
	this->posx = 50;
	this->posy = WIN_POS_Y / 3;
	this->_ball_shape = new sf::CircleShape(this->_radius_of_ball); // dynamically create a ball with radius
	_ball_shape->setFillColor(_ball_color);
	_ball_shape->setPosition(this->posx,this->posy);
	wins->draw(*this->_ball_shape);
}
void _graphical_ball_interface_::_ball::_steady_move_ball_auto(sf::RenderWindow &window)
{
	this->posx += speedx;
	this->posy += speedy;
	if (this->posy < 550) 
	{
		this->posy = 550;
		this->speedy = 5;
		this->speedy *= 1;
	}
	if (this->posx < 902)
	{
		this->posx = 902;
		this->speedx *= -1;
	}
	if (this->posx > 1097)
	{
		this->posx = 1097;
		this->speedx *= -1;
	}
	if (this->posy >= 847)
	{
		this->posy = 847;
		this->speedy = 5;
		this->speedy *= -1;
	}
	this->_ball_shape->setPosition(this->posx, this->posy);
	window.draw(*this->_ball_shape);
}
void _graphical_ball_interface_::_ball::_draw_to_win_event(sf::RenderWindow*& _win)
{
	_win->draw(*this->_ball_shape);
}
sf::CircleShape* _graphical_ball_interface_::_ball::_get_ball_shape()
{
	return this->_ball_shape;
}
_graphical_table_interface_::_table::_table()
{
	// empty default constructor
}
void _graphical_table_interface_::_table::_init_meme_()
{
	this->_convex_shape = new sf::ConvexShape;
}
void _graphical_table_interface_::_table::_create_surface_table_pong_(sf::RenderWindow*& _window)
{
	_convex_shape->setPointCount(4);
	_convex_shape->setPoint(0, sf::Vector2f(900, 550));
	_convex_shape->setPoint(1, sf::Vector2f(1100, 550));
	_convex_shape->setPoint(2, sf::Vector2f(1200, 850));
	_convex_shape->setPoint(3, sf::Vector2f(800, 850));
	//_convex_shape->setFillColor(sf::Color::Black);
	sf::Texture* wood = new sf::Texture; wood->loadFromFile("wood.jpeg");
	wood->setRepeated(true);
	_convex_shape->setTexture(wood, false);
	_convex_shape->setOutlineThickness(10);
	_convex_shape->setOutlineColor(sf::Color::White);
	_window->draw(*this->_convex_shape);
}

_graphical_paddle_interface_::_paddle::_paddle()
{
	// empty default constructor
}

void _graphical_paddle_interface_::_paddle::_init_meme_()
{
	this->racket = new sf::RectangleShape;
	sf::Texture* _paddletexture = new sf::Texture;
	_paddletexture->loadFromFile("paddle.png");
	this->racket->setTexture(_paddletexture, false);
}

void _graphical_paddle_interface_::_paddle::_create_paddle_pong_(sf::RenderWindow*& _window)
{
	racket->setSize(sf::Vector2f(90, 90));
}

sf::RectangleShape* _graphical_paddle_interface_::_paddle::_get_paddle_shape()
{
	return this->racket;
}
