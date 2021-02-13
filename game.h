#pragma once
#include <SFML/Graphics.hpp>
#include "token.h"

using namespace std;

// Cette struct est utilisee pour gerer chaque emplacement de la grille (savoir si l'emplacement est vide ou non)

class game
{
	struct block
	{
		bool active;
		int dim;
		RectangleShape pos;
	};

private:

	token piece[8];
	token nextPiece[7];
	block grille[24][12];

	bool _gameOver;
	bool collision;
	bool _softDrop;

	int _level;
	int _score;
	int _lineCount;

	int posGrilleY;
	int posGrilleX;
	int posNextPieceX;
	int posNextPieceY;
	int dim;

	int _kind;
	int _nextKind;
	int _action;
	int _dropDelay;
	int _dropDelaySoft;

	Clock clock;
	Time time;
	enum action {LEFT, RIGHT, SOFT, HARD, ROTATEC, ROTATECC, NONE};

public:

	game();
	~game();

	void init();
	void initPiece();
	void initGrille();

	void placePiece(int kind);
	void inputKey();
	void randPiece();
	void randNextPiece();
	void randObstacle();

	string getScore();
	int getScoreInt();
	string getLevel();
	string getLineCount();

	void movePiece();

	void play();
	bool checkGrille(RectangleShape piece);
	int checkLine();

	void pointsForLine();
	void pointsForSoftDrops();
	void pointsForHardDrops();
	void updateLevel();

	bool ifCollisionGrille();
	bool isGameOver();

	void drawGame(RenderWindow& tetrisWindow);
};



