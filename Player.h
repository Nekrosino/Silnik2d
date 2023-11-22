#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
using namespace sf;
//Klasa gracza
class Player
{	
private:
	float position_x=400; //pozycja gracza w osi x
	float position_y=400; //pozycja gracza w osi y
	float speed = 0.0f;
	float maxSpeedPlus=10;
	float maxSpeedMinus=maxSpeedPlus*-1;
	float jump = 0.0f;
	bool jumpStatus;
	RectangleShape collisionBox;
	RectangleShape playerShape;
	Sprite playerSprite;
	Texture playerTexture;
public:

	void moveLeft(); //funkcja poruszania gracza w lewo
	void moveRight(); //funkcja poruszania gracza w prawo
	void moveUp(bool isJumping);
	void drawPlayer(RenderWindow& window);
	void updatePlayer();
	void collision();
};


#endif