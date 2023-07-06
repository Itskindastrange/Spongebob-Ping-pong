#include<iostream>
#include<SFML/Graphics.hpp>
#include"confidential.h"
#include<SFML/Audio.hpp>
float clip(float n, float lower, float upper)
{
	n = (n > lower) * n + !(n > lower) * lower;
	return (n < upper) * n + !(n < upper) * upper;
}
bool collision(sf::RectangleShape r, sf::CircleShape c)
{
	float closex = clip(c.getPosition().x, r.getPosition().x, r.getPosition().x + r.getSize().x);
	float closey = clip(c.getPosition().y, r.getPosition().y, r.getPosition().y + r.getSize().y);
	float distx = c.getPosition().x - closex;
	float disty = c.getPosition().y - closey;
	int distsq = (distx) * (distx)+(disty) * (disty);
	if (distsq < c.getRadius() * c.getRadius() && closey == c.getPosition().y)
	{
		return 1;
	}
	else if (distsq < c.getRadius() * c.getRadius() && closex != c.getPosition().x && closey != c.getPosition().y)
	{
		return 1;
	}
	else if (distsq < c.getRadius() * c.getRadius() && closex == c.getPosition().x)
	{
		return 1;
	}
}
bool check(int pos)
{
	return (pos >= 902 && pos <= 1097);
}
void autobot(sf::CircleShape c,  _graphical_ball_interface_::_ball *&b, sf::RenderWindow& win,sf::RectangleShape s,_graphical_paddle_interface_::_paddle*p)
{
	if (check(c.getPosition().x))
	{
		s.move(b->_get_ball_shape()->getPosition().x, s.getPosition().y);
		win.draw(s);
		/*if (collision(*p->racket, c))
		{
			b->speedy = -b->speedy;
		}*/
	}
}
int main()
{
	bool running = false;
	bool bot = false;
	sf::VideoMode* _vid = new sf::VideoMode(WIN_POS_X, WIN_POS_Y);
	sf::RenderWindow* _window = new sf::RenderWindow(*_vid, "Pong Game", sf::Style::Close);
	sf::Event* e = new sf::Event;
	sf::SoundBuffer _hitplay1, _hitlplay2;
	sf::Sound h1, h2;
	_hitplay1.loadFromFile("hitplay1.wav");
	_hitlplay2.loadFromFile("hitplay2.wav");
	h1.setBuffer(_hitplay1);
	h2.setBuffer(_hitlplay2);
	_window->setFramerateLimit(60);
		_graphical_ball_interface_::_ball* mainball;
		mainball = new _graphical_ball_interface_::_ball;
		mainball->_init_ball_(_window, sf::Color::Red);
		// background
		sf::Sprite bg; sf::Texture* background = new sf::Texture; background->loadFromFile("background.jpg");
		bg.setTexture(*background);
		sf::Sprite bg1; sf::Texture* background1 = new sf::Texture; background1->loadFromFile("island.jpg");
		bg1.setTexture(*background1);
		bg1.setPosition(0, 701);
		// create main table
		_graphical_table_interface_::_table* maintable;
		maintable = new _graphical_table_interface_::_table;
		maintable->_init_meme_();
		// start game loop
		// player 1 spongebob
		sf::Sprite bob; sf::Texture* spongeBob = new sf::Texture;
		spongeBob->loadFromFile("bob.png");
		bob.setTexture(*spongeBob);
		// player 2 patrick
		sf::Sprite pat; sf::Texture* patrick = new sf::Texture;
		patrick->loadFromFile("pat.png");
		pat.setTexture(*patrick);
		// down paddle
		_graphical_paddle_interface_::_paddle* _lower_paddle_;
		_lower_paddle_ = new _graphical_paddle_interface_::_paddle;
		_lower_paddle_->_init_meme_();
		_lower_paddle_->racket->setPosition(WIN_POS_X / 2 - 100.f, WIN_POS_Y / 2 + 250.f);
		bob.setPosition(_lower_paddle_->_get_paddle_shape()->getPosition().x,
			_lower_paddle_->_get_paddle_shape()->getPosition().y);
		// upper paddle
		_graphical_paddle_interface_::_paddle* _upper_paddle_;
		_upper_paddle_ = new _graphical_paddle_interface_::_paddle;
		_upper_paddle_->_init_meme_();
		_upper_paddle_->racket->setPosition(WIN_POS_X / 2, WIN_POS_Y / 2 - 50.f);
		pat.setPosition(_upper_paddle_->_get_paddle_shape()->getPosition().x, _upper_paddle_->_get_paddle_shape()->getPosition().y - 100.f);
		bool playsel = false;
		bool playvscomp = false;
	do// main game loop
	{
		do// pollevent loop
		{
			switch (e->type)
			{
			case sf::Event::Closed: // break if close if clicked
				_window->close();
			default:
				break;
			}	
		} 
		while (_window->pollEvent(*e));
		if (e->type == sf::Event::MouseMoved)
		{
			int posx = (int)e->mouseMove.x;
			int posy = (int)e->mouseMove.y;
			if (posx >= 665 && posx <= 809 && posy >= 458 && posy <= 536)
			{
				playsel = true;
			}
			else playsel = false;
			if (posx >= 663 && posx <= 960 && posy >= 561 && posy <= 638)
			{
				bot = true;
				playvscomp = true;
			}
			else playvscomp = false;
		}
			if (e->type == sf::Event::MouseButtonPressed)
			{
				if (e->mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "mouse x: " << e->mouseButton.x << std::endl;
					std::cout << "mouse y: " << e->mouseButton.y << std::endl;
				}
				if (playsel)running = true;
				if (playvscomp)running = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				_lower_paddle_->racket->move(-10.f, 0);
				bob.setPosition(_lower_paddle_->_get_paddle_shape()->getPosition().x,
					_lower_paddle_->_get_paddle_shape()->getPosition().y);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				_lower_paddle_->racket->move(10.f, 0);
				bob.setPosition(_lower_paddle_->_get_paddle_shape()->getPosition().x,
					_lower_paddle_->_get_paddle_shape()->getPosition().y);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				_upper_paddle_->racket->move(-10.f, 0);
				pat.setPosition(_upper_paddle_->_get_paddle_shape()->getPosition().x,
					_upper_paddle_->_get_paddle_shape()->getPosition().y - 100.f);

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				_upper_paddle_->racket->move(10.f, 0);
				pat.setPosition(_upper_paddle_->_get_paddle_shape()->getPosition().x,
					_upper_paddle_->_get_paddle_shape()->getPosition().y - 100.f);
			}
			if (collision(*_lower_paddle_->racket, *mainball->_get_ball_shape()) == 1)
			{
				h1.play();
				mainball->_get_ball_shape()->setPosition(mainball->_get_ball_shape()->getPosition().x,
					mainball->_get_ball_shape()->getPosition().y - 10.f);
				mainball->speedy = -mainball->speedy;
			}
			if (collision(*_upper_paddle_->racket, *mainball->_get_ball_shape()) == 1)
			{
				h2.play();
				mainball->_get_ball_shape()->setPosition(mainball->_get_ball_shape()->getPosition().x,
					mainball->_get_ball_shape()->getPosition().y + 10.f);
				mainball->speedy = -mainball->speedy;
			}
			if (!running)
			{
				sf::Texture* background = new sf::Texture;
				background->loadFromFile("bg.png");
				sf::Sprite newbg; newbg.setTexture(*background);
				sf::Text Play, PvC, Exit; sf::Font f; f.loadFromFile("font.ttf");
				Play.setFont(f);
				Play.setCharacterSize(80);
				Play.setOutlineColor(sf::Color::Black);
				Play.setOutlineThickness(10);
				Play.setFillColor(sf::Color::White);
				Play.setString("Play");
				Play.setPosition(WIN_POS_X / 2-300.f, WIN_POS_Y / 2-100.f);

				PvC.setFont(f);
				PvC.setCharacterSize(80);
				PvC.setOutlineColor(sf::Color::Black);
				PvC.setOutlineThickness(10);
				PvC.setFillColor(sf::Color::White);
				PvC.setString("Play Vs Comp");
				PvC.setPosition(WIN_POS_X / 2 - 300.f, WIN_POS_Y / 2);
				if (playsel)
				{
					Play.setFillColor(sf::Color::Red);
				}else Play.setFillColor(sf::Color::White);
				if (playvscomp)
				{
					PvC.setFillColor(sf::Color::Red);
				}
				else PvC.setFillColor(sf::Color::White);
				//-------------------------
				


				_window->draw(newbg);
				_window->draw(Play);
				_window->draw(PvC);
			}
			if (running)
			{
				if (bot) { autobot(*mainball->_get_ball_shape(), mainball, *_window,*_upper_paddle_->_get_paddle_shape(), _upper_paddle_); }
				_window->draw(bg);
				_window->draw(bg1);
				_window->draw(pat);
				maintable->_create_surface_table_pong_(_window);
				mainball->_steady_move_ball_auto(*_window);
				_window->draw(bob);
				_lower_paddle_->_create_paddle_pong_(_window);
				_upper_paddle_->_create_paddle_pong_(_window);
				_window->draw(*_lower_paddle_->_get_paddle_shape());
				_window->draw(*_upper_paddle_->_get_paddle_shape());
			}
		 _window->display();
	}
	while (_window->isOpen());
}
