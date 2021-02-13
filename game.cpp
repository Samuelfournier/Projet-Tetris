#include "game.h"
#include <string>
#include <conio.h>

using namespace sf;
using namespace std;

game::game()
{
	_score = _level = _lineCount = 0;
	_dropDelay = 300; // en millisecondes
    _dropDelaySoft = 50;
    posGrilleY = -90;
    posGrilleX = 221;
    posNextPieceX = 492;
    posNextPieceY = 30;
    dim = 30;
	_gameOver = false;
    _softDrop = false;
	_action = NONE;
}

game::~game()
{
    _score = _level = _lineCount = 0;
    _dropDelay = 300; // en millisecondes
    _dropDelaySoft = 50;
    posGrilleY = -90;
    posGrilleX = 221;
    posNextPieceX = 492;
    posNextPieceY = 30;
    dim = 30;
    _gameOver = false;
    _softDrop = false;
    _action = NONE;
}

void game::init()
{
    _score = _level = _lineCount = 0;
    _dropDelay = 300; // en millisecondes
    _dropDelaySoft = 50;
    posGrilleY = -90;
    posGrilleX = 221;
    posNextPieceX = 492;
    posNextPieceY = 30;
    dim = 30;
    _gameOver = false;
    _softDrop = false;
    _action = NONE;
    initGrille();
    initPiece();
    randPiece();
    randNextPiece();
}

void game::initPiece()
{
    for (int i = 0; i < 7; i++)
    {
        piece[i].initializeToken(i, dim, 4, 0, posGrilleX, posGrilleY);
        nextPiece[i].initializeToken(i, dim, 4, 0, posNextPieceX, posNextPieceY);
    }
    // Obstacle
    piece[7].initializeToken(7, dim, 4, 0, posGrilleX, posGrilleY);
}

void game::initGrille()
{
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            grille[i][j].pos.setPosition(Vector2f((221) + dim * j, dim * i - 90));
            grille[i][j].pos.setSize(Vector2f(dim - 2, dim - 2)); // dim - bordure
            grille[i][j].pos.setFillColor(Color::Transparent);
            if (i < 23)
            {
                grille[i][j].active = false; // toutes les cases de la grille sont vides par defaut
            }
            else
            {
                grille[23][j].active = true; // toutes les cases de la bordure du bas sont remplies
            }
        }
        grille[i][0].active = true;  // toutes les cases de la bordure de gauche sont remplies
        grille[i][11].active = true; // toutes les cases de la bordure de droite sont remplies
    }
}

void game::placePiece(int kind)
{
    for (int i = 1; i < 23; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                for (int l = 0; l < 4; l++)
                {
                    if (grille[i][j].pos.getPosition() == piece[kind].getPos(k, l).getPosition() && 
                        piece[kind].getActive(k, l) == true)
                    {
                        grille[i][j].pos.setFillColor(piece[kind].getPos(k, l).getFillColor());
                        grille[i][j].pos.setSize(piece[kind].getPos(k, l).getSize());
                        grille[i][j].active = true;
                    }
                }
            }
        }
    }
}

void game::inputKey() {
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        _action = LEFT;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        _action = RIGHT;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down))
    {
        _action = SOFT;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Space))
    {
        _action = HARD;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Up))
    {
        _action = ROTATEC;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Z))
    {
        _action = ROTATECC;
    }
}

void game::randPiece()
{
    _kind = rand() % 7;
}

void game::randNextPiece()
{
    _nextKind = rand() % 7;
}

/*
  Methode generant aleatoirement un obstacle sur la grille
*/
void game::randObstacle()
{
    bool free_tile = true;
    do
    {
        // Generation d'une position aleatoire
        int x = rand() % 10 + 1;
        int y = rand() % 22 + 4;

        // Initialiser l'obstacle
        piece[7].initializeToken(7, dim, x, y, posGrilleX, posGrilleY);

        // Verifier si l'emplacement est libre
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (piece[7].getActive(i, j) == true)
                {
                    free_tile = checkGrille(piece[7].getPos(i, j));
                }
            }
        }
    } while (free_tile == true);

    // Placer l'obstacle dans la grille
    placePiece(7);
}

string game::getScore()
{
    return to_string(_score);
}

int game::getScoreInt() {

    return _score;
}

string game::getLevel()
{
    return to_string(_level);
}

string game::getLineCount()
{
    return to_string(_lineCount);
}

void game::movePiece()
{
    switch (_action)
    {
        case LEFT:
            if (!ifCollisionGrille())
            {
                piece[_kind].moveTokenLeft();
            }
            break;

        case RIGHT:
            if (!ifCollisionGrille())
            {
                piece[_kind].moveTokenRight();
            }
            break;

        case SOFT:
            _softDrop = true;
            pointsForSoftDrops();
            break;

        case HARD:
            while (!ifCollisionGrille())
            {
                piece[_kind].moveTokenDown();
                pointsForHardDrops();
            }
            break;

        case ROTATEC:
            if (!ifCollisionGrille())
            {
                piece[_kind].rotateTokenCWise();
            }
            break;

        case ROTATECC:
            if (!ifCollisionGrille())
            {
                piece[_kind].rotateTokenCCWise();
            }
            break;
    }
}

void game::play()
{
    time = clock.getElapsedTime();
    pointsForLine();
    movePiece();

    if (ifCollisionGrille())
    {
        // Apres le niveau 4, des obstacles apparaissent...
        if (_level > 4)
        {
            randObstacle();
        }
        placePiece(_kind);
        _kind = _nextKind;
        piece[_kind].initializeToken(_kind, dim, 4, 0, posGrilleX, posGrilleY);
        randNextPiece();
        nextPiece[_nextKind].initializeToken(_nextKind, dim, 4, 0, posNextPieceX, posNextPieceY);
    }

    if (time.asMilliseconds() >= _dropDelay || time.asMilliseconds() >= _dropDelaySoft && _softDrop == true)
    {
        piece[_kind].moveTokenDown();
        clock.restart();
    }

    _softDrop = false;
    updateLevel();
}

/*
  Methode verifiant s'il y a une collision sur les tuiles actives recues
*/
bool game::checkGrille(RectangleShape piece)
{
    // On verifie chaque ligne
    for (int i = 0; i < 24; i++)
    {
        // On verifie chaque colonne
        for (int j = 0; j < 12; j++)
        {
            // Si active : position piece recue == position grille ?
            if (grille[i][j].active == true &&
                piece.getPosition().x == grille[i][j].pos.getPosition().x &&
                piece.getPosition().y == grille[i][j].pos.getPosition().y)
            {
                return true;
            }
        }
    }

    return false;
}

/*
 Methode comptant le nombre de lignes remplies et gerant leur destruction
*/
int game::checkLine()
{
    int lineTotal = 0;
    int lineCompletedCount = 0;

    // On verifie chaque ligne sauf la bordure en bas (sinon les pieces chutent a l'infini)
    for (int i = 3; i < 23; i++)
    {
        // On verifie chaque colonne sauf les bordures a gauche et a droite (sinon, les pieces peuvent sortir de la grille)
        for (int j = 1; j < 11; j++)
        {
            // Incrementer le nombre de colonnes actives sur la meme ligne
            if (grille[i][j].active == true)
            {
                lineTotal++;
            }
            // Si toute la ligne est active
            if (lineTotal == 10)
            {
                lineCompletedCount++;
                _lineCount++;
                for (int k = i; k > 3; k--)
                {
                    for (int l = 1; l < 11; l++)
                    {
                        // Copier la ligne precedente
                        if (grille[k - 1][l].active == true)
                        {
                            grille[k][l].pos.setFillColor(grille[k - 1][l].pos.getFillColor());
                            grille[k][l].active = true;
                        }
                        // Detruire la ligne courante
                        else
                        {
                            grille[k][l].active = false;
                            grille[k][l].pos.setFillColor(Color::Transparent);
                        }
                    }
                }
            }
        }
        // Reinitialisation du compteur de colonnes actives
        lineTotal = 0;
    }
    return lineCompletedCount;
}

void game::pointsForLine()
{
    int lineCount = checkLine();

    if (lineCount == 1)
    {
        _score += (40 * (_level + 1));
    }
    else if (lineCount == 2)
    {
        _score += (100 * (_level + 1));
    }
    else if (lineCount == 3)
    {
        _score += (300 * (_level + 1));
    }
    else if (lineCount == 4)
    {
        _score += (1200 * (_level + 1));
    }
}

void game::pointsForSoftDrops()
{
    if (_level == 0 || _level == 1)
    {
        _score += 1;
    }
    else if (_level == 2 || _level == 3)
    {
        _score += 2;
    }
    else if (_level == 4 || _level == 5)
    {
        _score += 3;
    }
    else if (_level == 6 || _level == 7)
    {
        _score += 4;
    }
    else if (_level >= 8)
    {
        _score += 5;
    }
}

void game::pointsForHardDrops()
{
    if (_level == 0 || _level == 1)
    {
        _score += 2;
    }
    else if (_level == 2 || _level == 3)
    {
        _score += 4;
    }
    else if (_level == 4 || _level == 5)
    {
        _score += 8;
    }
    else if (_level == 6 || _level == 7)
    {
        _score += 16;
    }
    else if (_level >= 8)
    {
        _score += 32;
    }
}

void game::updateLevel()
{
    if (_lineCount == (10 * (_level + 1)))
    {
        _level += 1;
        if (_level < 8) {
            _dropDelay -= 10;
        }
        else {
            _dropDelay = 200;
        }
    }
}

/*
  Methode verifiant s'il y a une collision horizontale
*/
bool game::ifCollisionGrille()
{
    // Piece temporairement deplacee a la position suivante
    token tmp = piece[_kind];

    // Gestion des mouvements horizontaux
    if (_action == LEFT)
    {
        tmp.moveTokenLeft();
    }
    else if (_action == RIGHT)
    {
        tmp.moveTokenRight();
    }
    // Gestion des rotations
    else if (_action == ROTATEC)
    {
        tmp.rotateTokenCWise();
    }
    else if (_action == ROTATECC)
    {
        tmp.rotateTokenCCWise();
    }
    // Si ce n'est pas un mouvement, on verifie la chute
    else
    {
        tmp.moveTokenDown();
    }
    // Reinitialisation de l'action en cours
    _action = NONE;

    // On verifie les tuiles de la piece deplacee du bas vers le haut
    for (int i = 3; i >= 0; i--)
    {
        for (int j = 0; j < 4; j++) 
        {
            // On verifie si au moins une tuile active de la position suivante correspond a une tuile active de la grille
            if (tmp.getActive(i, j) == true && checkGrille(tmp.getPos(i, j)))
            {
                return true;
            }
        }
    }

    return false;
}

/*
  Methode verifiant si la partie est finie
*/
bool game::isGameOver()
{
    // On verifie toutes les colonnes sauf les bordures a gauche et a droite
    for (int i = 1; i < 11; i++)
    {
        // Verifier si la premiere tuile ou une piece peut etre generee est active
        if (grille[1][i].active == true)
        {
            return true;
        }
    }
    return false;
}

/*
  Methode gerant l'affichage de la grille
*/
void game::drawGame(RenderWindow& tetrisWindow)
{
    // On n'affiche pas les tuiles hors-limites ni la bordure en bas
    for (int i = 3; i < 23; i++)
    {
        // On n'affiche pas les bordures a gauche et a droite
        for (int j = 1; j < 11; j++)
        {
            tetrisWindow.draw(grille[i][j].pos);
        }
    }
    nextPiece[_nextKind].drawToken(tetrisWindow);
    piece[_kind].drawToken(tetrisWindow);
    piece[7].drawToken(tetrisWindow);
}
