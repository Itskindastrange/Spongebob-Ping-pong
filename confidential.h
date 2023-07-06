#pragma once
#include<SFML/Graphics.hpp>
#define WIN_POS_X 1920
#define WIN_POS_Y 1080
namespace _graphical_ball_interface_
{
	class _ball
	{
		sf::CircleShape *_ball_shape;
		 float _radius_of_ball ;
	public:
		 int posx, posy;
		float speedx;
		float speedy;
		_ball();
		void _init_ball_(sf::RenderWindow*& wins,sf::Color _ball_color);
		void _steady_move_ball_auto(sf::RenderWindow& window);
		void _draw_to_win_event(sf::RenderWindow *&_win);
		sf::CircleShape* _get_ball_shape();
	};
}
namespace _graphical_table_interface_
{
	class _table
	{
		sf::ConvexShape* _convex_shape;
	public:
		_table();
		void _init_meme_();
		void _create_surface_table_pong_(sf::RenderWindow*&_window);
	};
}
namespace _graphical_paddle_interface_
{
	class _paddle
	{
	private:
	public:
		sf::RectangleShape* racket;
		int posx, posy;
		_paddle();
		void _init_meme_();
		void _create_paddle_pong_(sf::RenderWindow*& _window);
		sf::RectangleShape* _get_paddle_shape();
	};
	
}