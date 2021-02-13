#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;
class button
{
private :
	RectangleShape _button;
	Text _name;

public :

	button();
	button(int sizeX, int sizeY, int posX, int posY, const Color& color);
	void setButton(int sizeX, int sizeY, int posX, int posY, const Color& color);
	void setName(string message, Font& font, const char* police,
		int posX, int posY, int taille, const Color& color, int style);
	void setColorAndStyle(const Color& color, int style);
	bool getPosition(int x, int y);
	void print(RenderWindow& window);
};


