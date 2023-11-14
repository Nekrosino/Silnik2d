
#include "Player.h"

using namespace sf;


void Player::drawPlayer(RenderWindow& window) //Funkcja rysujaca gracza
{
	playerShape.setSize(Vector2f(50, 50));
	playerShape.setPosition(position_x, position_y);
	playerShape.setFillColor(Color::Green);
	window.draw(playerShape);
}
void Player::moveLeft() //Funkcja do poruszania postaci w lewo
{
	speed -= 1;
	
}

void Player::moveRight() //Funkcja do poruszania postaci w prawo
{
	speed += 1;
}

void Player::moveUp()
{
	jump -= 1;
}



void Player::updatePlayer() //Funkcja akutalizujaca gracza
{
	position_x += speed; //pozycji x dodajemy predkosc aby otrzymac efekt przyspieszenia
	position_y += jump;
	collision();
	if (speed > maxSpeedPlus) //ograniczenie predkosci gdy przekroczy wartosc dodatnia
	{
		speed = 5;
	}
	else if (speed < maxSpeedMinus) //ograniczenie predkosci gdy przekroczy wartosc ujemna
	{
		speed = -5;
	}

	if (speed > 0.0f ) //przyspieszenie gdy predkosc wieksza od 0
	{
		speed -= 0.1f;
		if (speed < 0.0f)
			speed = 0.0f;
		
	}
	else if (speed < 0.0f) //przyspieszenie gdy predkosc mniejsza od 0
	{
		speed += 0.1f;
		if (speed > 0.0f )
			speed = 0.0f;
	}
	if (jump > 8)
	{
		jump = 5;
	}
	else if (jump < -5)
	{
		jump = -5;
	}
	if (jump > 0.0f) //przyspieszenie gdy predkosc wieksza od 0
	{
		jump -= 0.1f;
		if (jump < 0.0f)
			jump = 0.0f;

	}
	else if (jump < 0.0f) //przyspieszenie gdy predkosc mniejsza od 0
	{
		jump += 0.1f;
		if (jump > 0.0f)
			jump = 0.0f;

	}
	if (position_y < 500)
	{
		jump += 0.6f;
	}
	else if (position_y >= 500)
	{
		jump == 0.0f;
		position_y = 500;
	}
	else if (position_y >= 600)
	{
		jump == 0.0f;
	}

}

void Player::collision()
{
	if (position_x >= 750)
	{
		speed = maxSpeedMinus;
	}
	else if (position_x <= 0)
	{
		speed = maxSpeedPlus;
	}
}