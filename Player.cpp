
#include "Player.h"

using namespace sf;


void Player::drawPlayer(RenderWindow& window) //Funkcja rysujaca gracza
{	

	if (!playerTexture.loadFromFile("textures/test.png"))
	{
		printf("error");
	}
	playerShape.setSize(Vector2f(100, 100));
	playerShape.setPosition(position_x, position_y);
	//playerShape.setFillColor(Color::Green);

	
	//playerSprite.setPosition(position_x, position_y);
	//playerSprite.setTexture(playerTexture);
	playerShape.setTexture(&playerTexture);
	int spriteWidth = playerShape.getGlobalBounds().width;
	int spriteHeight = playerShape.getGlobalBounds().height;

	collisionBox.setSize(Vector2f(spriteWidth, spriteHeight));
	collisionBox.setFillColor(Color::Transparent);  // Ustawienie przezroczystego koloru
	collisionBox.setOutlineColor(Color::Red);  // Ustawienie koloru obramowania na czerwony
	collisionBox.setOutlineThickness(1.0f);  // Ustawienie gruboœci obramowania
	
	//window.draw(playerShape);
	
	window.draw(playerShape);
	window.draw(collisionBox);
	
}
void Player::moveLeft() //Funkcja do poruszania postaci w lewo
{
	speed -= 1;
	
}

void Player::moveRight() //Funkcja do poruszania postaci w prawo
{
	speed += 1;
}

void Player::moveUp(bool isJumping)
{	
	if (isJumping==true && position_y >=400)
	{
		jump -= 1;
		jumpStatus = true;
	}

}



void Player::updatePlayer() //Funkcja akutalizujaca gracza
{
	position_x += speed; //pozycji x dodajemy predkosc aby otrzymac efekt przyspieszenia
	position_y += jump;
	collision();
	collisionBox.setPosition(position_x, position_y);
	if (speed > maxSpeedPlus) //ograniczenie predkosci gdy przekroczy wartosc dodatnia
	{
		speed = 5;
	}
	else if (speed < maxSpeedMinus) //ograniczenie predkosci gdy przekroczy wartosc ujemna
	{
		speed = -5;
	}

	if (speed > 0.0f) //przyspieszenie gdy predkosc wieksza od 0
	{
		speed -= 0.1f;
		if (speed < 0.0f)
			speed = 0.0f;

	}
	else if (speed < 0.0f) //przyspieszenie gdy predkosc mniejsza od 0
	{
		speed += 0.1f;
		if (speed > 0.0f)
			speed = 0.0f;
	}
	if (jumpStatus)
	{
		if (jump > 8)
		{
			jump = 5;
		}
		else if (jump < -5)
		{
			jump = -5;
		}

		if (jump > 0.0f)
		{
			jump -= 0.1f;
			if (jump < 0.0f)
				jump = 0.0f;
		}
		else if (jump < 0.0f)
		{
			jump += 0.1f;
			if (jump > 0.0f)
				jump = 0.0f;
		}
	}
	else
	{
		jump += 0.1f;
		if (position_y <= 400)
		{
			jump = 0.0f;
		}
	}

}



void Player::collision()
{
	if (position_x >= 700)
	{
		speed = maxSpeedMinus;
	}
	else if (position_x <= 0)
	{
		speed = maxSpeedPlus;
	}
}