/*
 * Fichier: token.cpp
 * Auteur: Haoge Li
 * Date de creation: 10-05-2020
 * Description: Toutes les methodes de l'objet // token //
*/

#include "token.h"

/*
  Accesseur retournant l'etat d'activation d'une tuile de la piece (4 lignes * 4 colonnes)
*/
bool token::getActive(int i, int j)const
{
    assert(i >= 0 && i < 4);
    assert(j >= 0 && j < 4);

    return _token[i][j].active;
}

/*
  Accesseur retournant les informations d'une tuile de la piece (4 lignes * 4 colonnes)
*/
RectangleShape token::getPos(int i, int j)const
{
    return _token[i][j].pos;
}

/*
  Accesseur retournant la couleur d'une tuile de la piece (4 lignes * 4 colonnes)
*/
Color token::getColor(int i, int j)const
{
    return _token[i][j].pos.getFillColor();
}

/*
  Accesseur retournant la position Vector2f d'une tuile de la piece (4 lignes * 4 colonnes)
*/
Vector2f token::getPosXY(int i, int j)const
{
    assert(i >= 0 && i < 4);
    assert(j >= 0 && j < 4);

    return _token[i][j].pos.getPosition();
}

/*
  Accesseur retournant la position horizontale d'une d'une tuile de la piece (4 lignes * 4 colonnes)
*/
int token::getPosX(int i, int j)const
{
    assert(i >= 0 && i < 4);
    assert(j >= 0 && j < 4);

    return _token[i][j].pos.getPosition().x;
}

/*
  Accesseur retournant la position verticale d'une tuile de la piece (4 lignes * 4 colonnes)
*/
int token::getPosY(int i, int j)const
{
    assert(i >= 0 && i < 4);
    assert(j >= 0 && j < 4);

    return _token[i][j].pos.getPosition().y;
}

/*
  Mutateur modifiant la couleur de la piece voulue
*/
void token::setColor(Color color)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            _token[i][j].pos.setFillColor(color);
        }
    }
}

/*
  Mutateur modifiant la position de la piece voulue (avec une position Vector2f)
*/
void token::setPosXY(Vector2f pos)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // On ecrase l'ancienne position par la nouvelle
            _token[i][j].pos.setPosition(pos.x, pos.y);
        }
    }
}

/*
  Mutateur modifiant la position de la piece voulue (de X cases horizontales et de Y cases verticales)
*/
void token::setPosXY(int x, int y, int w, int h)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // ( bordure_gauche + X * cote * tuile , bordure_haut + Y * cote * tuile )
            _token[i][j].pos.setPosition(w + (x * _token[i][j].dim) + (_token[i][j].dim * j), h + (y * _token[i][j].dim) + (_token[i][j].dim * i));
        }
    }
}

/*
  Mutateur modifiant la position horizontale de la piece voulue (de X cases horizontales)
*/
void token::setPosX(int x, int w)
{
    assert(x >= 0);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // ( bordure_gauche + X * cote * tuile, hauteur )
            _token[i][j].pos.setPosition(w + (x * _token[i][j].dim) + (_token[i][j].dim * j), _token[i][j].pos.getPosition().y);
        }
    }
}

/*
  Mutateur modifiant la position verticale de la piece voulue (de Y cases verticales)
*/
void token::setPosY(int y, int h)
{
    assert(y >= 0);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // ( largeur, bordure_haut + Y * cote * tuile )
            _token[i][j].pos.setPosition(_token[i][j].pos.getPosition().x, h + (y * _token[i][j].dim) + (_token[i][j].dim * i));
        }
    }
}

/*
  Methode pour initialiser une piece
*/
void token::initializeToken(int shape, int dim, int x, int y, int w, int h)
{
    // Desactivation et initialisation des coordonnees de toutes les tuiles
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            _token[i][j].active = false;
            _token[i][j].dim = dim;
            // [dim - 2] pour creer une bordure invisible qui ne cache pas la grille de jeu
            _token[i][j].pos.setSize(Vector2f(_token[i][j].dim - 2, _token[i][j].dim - 2));
            _token[i][j].pos.setPosition(Vector2f(w + (x * dim) + (_token[i][j].dim * j), h + (y * dim) + (_token[i][j].dim * i)));
            _token[i][j].pos.setFillColor(Color::Transparent);
        }
    }
    // Activation des coordonnees des tuiles a dessiner selon la forme generee
    switch (shape)
    {
        // I
        case 0:
            _token[1][0].active = true;
            _token[1][0].pos.setFillColor(Color::Cyan);
            _token[1][1].active = true;
            _token[1][1].pos.setFillColor(Color::Cyan);
            _token[1][2].active = true;
            _token[1][2].pos.setFillColor(Color::Cyan);
            _token[1][3].active = true;
            _token[1][3].pos.setFillColor(Color::Cyan);
            break;
        // O
        case 1:
            _token[1][1].active = true;
            _token[1][1].pos.setFillColor(Color::Yellow);
            _token[1][2].active = true;
            _token[1][2].pos.setFillColor(Color::Yellow);
            _token[2][1].active = true;
            _token[2][1].pos.setFillColor(Color::Yellow);
            _token[2][2].active = true;
            _token[2][2].pos.setFillColor(Color::Yellow);
            break;
        // T
        case 2:
            _token[1][1].active = true;
            _token[1][1].pos.setFillColor(Color::Magenta);
            _token[2][0].active = true;
            _token[2][0].pos.setFillColor(Color::Magenta);
            _token[2][1].active = true;
            _token[2][1].pos.setFillColor(Color::Magenta);
            _token[2][2].active = true;
            _token[2][2].pos.setFillColor(Color::Magenta);
            break;
        // L
        case 3:
            _token[1][0].active = true;
            _token[1][0].pos.setFillColor(Color::Blue);
            _token[2][0].active = true;
            _token[2][0].pos.setFillColor(Color::Blue);
            _token[2][1].active = true;
            _token[2][1].pos.setFillColor(Color::Blue);
            _token[2][2].active = true;
            _token[2][2].pos.setFillColor(Color::Blue);
            break;
        // J
        case 4:
            _token[1][2].active = true;
            _token[1][2].pos.setFillColor(Color::White);
            _token[2][0].active = true;
            _token[2][0].pos.setFillColor(Color::White);
            _token[2][1].active = true;
            _token[2][1].pos.setFillColor(Color::White);
            _token[2][2].active = true;
            _token[2][2].pos.setFillColor(Color::White);
            break;
        // S
        case 5:
            _token[1][1].active = true;
            _token[1][1].pos.setFillColor(Color::Red);
            _token[1][2].active = true;
            _token[1][2].pos.setFillColor(Color::Red);
            _token[2][0].active = true;
            _token[2][0].pos.setFillColor(Color::Red);
            _token[2][1].active = true;
            _token[2][1].pos.setFillColor(Color::Red);
            break;
        // Z
        case 6:
            _token[1][0].active = true;
            _token[1][0].pos.setFillColor(Color::Green);
            _token[1][1].active = true;
            _token[1][1].pos.setFillColor(Color::Green);
            _token[2][1].active = true;
            _token[2][1].pos.setFillColor(Color::Green);
            _token[2][2].active = true;
            _token[2][2].pos.setFillColor(Color::Green);
            break;
        // Obstable-tuile
        case 7:
            // Couleur aleatoire
            Color color;
            switch (rand() % 7)
            {
                case 0:
                    color = Color::Cyan;
                    break;
                case 1:
                    color = Color::Yellow;
                    break;
                case 2:
                    color = Color::Magenta;
                    break;
                case 3:
                    color = Color::Blue;
                    break;
                case 4:
                    color = Color::White;
                    break;
                case 5:
                    color = Color::Red;
                    break;
                case 6:
                    color = Color::Green;
                    break;
            }
            // Creation de l'obstacle
            _token[0][0].active = true;
            _token[0][0].pos.setFillColor(color);
            break;
    }
}

/*
  Methode pour deplacer la piece d'une position vers le bas
*/
void token::moveTokenDown()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            _token[i][j].pos.setPosition(_token[i][j].pos.getPosition().x, _token[i][j].pos.getPosition().y + _token[i][j].dim);
        }
    }
}

/*
  Methode pour deplacer la piece d'une position vers le haut
*/
void token::moveTokenUp()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            _token[i][j].pos.setPosition(_token[i][j].pos.getPosition().x, _token[i][j].pos.getPosition().y - _token[i][j].dim);
        }
    }
}

/*
  Methode pour deplacer la piece d'une position vers la gauche
*/
void token::moveTokenLeft()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            _token[i][j].pos.setPosition(_token[i][j].pos.getPosition().x - _token[i][j].dim, _token[i][j].pos.getPosition().y);
        }
    }
}

/*
  Methode pour deplacer la piece d'une position vers la droite
*/
void token::moveTokenRight()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            _token[i][j].pos.setPosition(_token[i][j].pos.getPosition().x + _token[i][j].dim, _token[i][j].pos.getPosition().y);
        }
    }
}

/*
  Methode pour faire tourner la piece dans le sens horaire
*/
void token::rotateTokenCWise()
{
    block tmp[4][4];
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tmp[i][j].active = _token[i][j].active;
            tmp[i][j].pos = _token[i][j].pos;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            _token[i][j].active = tmp[3 - j][i].active;
            _token[i][j].pos.setFillColor(tmp[3 - j][i].pos.getFillColor());
            _token[i][j].pos.setOutlineColor(tmp[3 - j][i].pos.getOutlineColor());
        }
    }
}

/*
  Methode pour faire tourner la piece dans le sens anti-horaire
*/
void token::rotateTokenCCWise()
{
    block tmp[4][4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tmp[i][j].active = _token[i][j].active;
            tmp[i][j].pos = _token[i][j].pos;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            _token[i][j].active = tmp[j][3 - i].active;
            _token[i][j].pos.setFillColor(tmp[j][3 - i].pos.getFillColor());
            _token[i][j].pos.setOutlineColor(tmp[j][3 - i].pos.getOutlineColor());
        }
    }
}

/*
  Methode d'affichage de la piece
*/
void token::drawToken(RenderWindow& window)const
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            window.draw(_token[i][j].pos);
        }
    }
}
