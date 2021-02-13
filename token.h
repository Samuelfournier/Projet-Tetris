/*
 * Fichier: token.h
 * Auteur: Haoge Li
 * Date de creation: 10-05-2020
 * Description: Tous les elements de l'objet // token //
*/

#ifndef TOKEN_H
#define TOKEN_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include <conio.h>

using namespace std;
using namespace sf;

class token
{
	struct block
	{
		bool active;
		int dim;
		RectangleShape pos;
	};

	block _token[4][4];

	public:

		bool getActive(int i, int j)const;

		RectangleShape getPos(int i, int j)const;

		Color getColor(int i, int j)const;

		Vector2f getPosXY(int i, int j)const;

		int getPosX(int i, int j)const;
		int getPosY(int i, int j)const;

		void setColor(Color color);

		void setPosXY(Vector2f pos);
		void setPosXY(int x, int y, int w, int h);

		void setPosX(int x, int w);
		void setPosY(int y, int h);

		void initializeToken(int shape, int dim, int x, int y, int w, int h);

		void moveTokenDown();
		void moveTokenUp();
		void moveTokenLeft();
		void moveTokenRight();
		void rotateTokenCWise();
		void rotateTokenCCWise();

		void drawToken(RenderWindow& window)const;
};

#endif // !TOKEN_H
