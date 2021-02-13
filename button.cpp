#include "button.h"

button::button()
{
}
// Constructeur par defaut qui set la taille, la position et la couleur
button::button(int sizeX, int sizeY, int posX, int posY, const Color& color)
{
	_button.setSize(Vector2f(sizeX, sizeY));
	_button.setFillColor(color);
	_button.setPosition(posX, posY);
}
// Setter qui set la taille, la position et la couleur
void button::setButton(int sizeX, int sizeY, int posX, int posY, const Color& color)
{
	_button.setSize(Vector2f(sizeX, sizeY));
	_button.setFillColor(color);
	_button.setPosition(posX, posY);
}

// Permet de set le nom, et tous les attributs necessaire à faire fonctionner un Text en SFML
void button::setName(string message, Font& font, const char* police,
	int posX, int posY, int taille, const Color& color, int style)
{
	font.loadFromFile(police);
	_name.setFont(font);								// Assigne la police a utiliser (elle doit avoir ete chargee)
	_name.setString(message);							// Assigne le texte a afficher
	_name.setCharacterSize(taille);						// Assigne la taille (en pixels)
	_name.setFillColor(color);							// Assigne la couleur du texte
	_name.setStyle(style);								// Assigne le style du texte
	_name.setPosition(posX, posY);
	_name.setOrigin(_name.getLocalBounds().width / 2, _name.getLocalBounds().height / 2);
}

// Permet de changer seulement la couleur et le style, utilisation lorsque la souris passe par dessus.
void button::setColorAndStyle(const Color& color, int style)
{
	_name.setFillColor(color);							// Assigne la couleur du texte
	_name.setStyle(style);								// Assigne le style du texte
}

// Retoune vrai si la position (x,y) est a l'interieur du bouton, ou faux si n'est pas a l'intérieur
bool button::getPosition(int x, int y) {
	if (x >= _button.getPosition().x && x <= (_button.getPosition().x + _button.getSize().x)
		&& y >= _button.getPosition().y && y <= (_button.getPosition().y + _button.getSize().y))
		return true;
	else
		return false;
}
// Permet de print le boutton sur la fenetre desiree
void button::print(RenderWindow& window)
{
	window.draw(_button);
	window.draw(_name);
}
