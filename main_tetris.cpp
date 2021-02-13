#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "button.h"
#include "game.h"
#include "token.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace sf;
using namespace std;

// Cette struct est utilisee pour gerer les donnees des scores dans le fichier TXT
struct statistique
{
	vector<string> _name;
	vector<int> _score;
};

// Permet de faire la configuration necessaire pour faire fonctionner du Text en SFML
void printText(Text& text, string message, Font& font, const char* police,
	int posX, int posY, int taille, const Color& color, int style);

// Cette fonction lit les donnees du fichier texte de score et le stock dans la struct
void readScore(statistique stats[1]);

// Cette fonction sert a inserer le joueur qui vient de finir une partie a l'interieur du classement si il est dans les 10 meilleurs
void insertPlayer(statistique stats[1], string userNow, int scoreNow);
// Permet d'ecrire le nouveau classement dans le fichier, a ecrire apres chaque partie
void writeScore(statistique stats[1]);

// Cette fonction permet d'afficher le classement dans la fenetre statistique lorsqu'elle est ouverte
void printRanking(statistique stats[1], RenderWindow& window, Font& font);

void getUserName(statistique stats[1], Event& event, RenderWindow& window, int score, Text& playerText, string& playerInput, button redo);

int main()
{

	srand(time((nullptr)));

	statistique stats[1];			// Declaration de la structure
	readScore(stats);				// Lecture des classements a l'ouverture

	RenderWindow menu(VideoMode(800, 600), "Menu", Style::Titlebar | Style::Close);			// Fait l'ouverture de la fenetre de Menu

	

	Event event;					// Event pour le Menu
	RectangleShape imgBackg;		//Declare un rectangle pour faire afficher l'image de fond

	imgBackg.setSize(Vector2f(800, 600));	// Declare la taille de l'image de fond
	imgBackg.setFillColor(Color::White);	// Met une couleur de base qui va etre ecrasee par l'image

	// Assigne une texture sur l'image de fond, si n'arrive pas a charger l'image, ferme le programme
	Texture textureImgBackg;
	if (!textureImgBackg.loadFromFile("ressources/mainmenu.jpg"))
	{
		return 1;
	}
	imgBackg.setTexture(&textureImgBackg);


	Font font;				// Declaration du font necessaire pour tous les textes
	Text score;
	Text level;
	Text gameOver;
	Text lineCount;

	// Instanciation de 3 nouveaux boutons, le bouton play, le bouton classement et le bouton pour quitter
	button play(75, 40, 400 - 35, 300 - 45, Color::Transparent);				// Sert a acceder a l'ecran pour jouer
	button classement(133, 40, 400 - 65, 300 + 15, Color::Transparent);			// Sert a acceder a l'ecran du classement
	button quitter(78, 40, 400 - 40, 300 + 75, Color::Transparent);				// Sert a quitter le jeu


	// Declare le nom des 3 boutons avec les parametres necessaires pour Text (taille, position, couleur, style, police)
	play.setName("Play", font, "ressources/arial.ttf", 400, 300 - 30, 24, Color::White, Text::Regular);

	classement.setName("Classement", font, "ressources/arial.ttf", 400, 300 + 30, 24, Color::White, Text::Regular);

	quitter.setName("Quitter", font, "ressources/arial.ttf", 400, 300 + 90, 24, Color::White, Text::Regular);

	Music music;
	if (!music.openFromFile("ressources/Tetris.ogg"))		// Initialise la musique
	{
		return -1; // Si erreur
	}

	music.setVolume(10.f);			// Fait jouer la musique, place le volume a 10 et place la musique en boucle infinie jusqu'a ce que le jeu ferme
	music.setLoop(true);
	music.play();

	//Tant que la fenetre menu est ouverte
	while (menu.isOpen())
	{
		while (menu.pollEvent(event))
		{
			// Ferme le programme si on clique sur le X de la fenetre
			if (event.type == Event::Closed)
			{
				menu.close();
			}
			// Event qui suit le mouvement de la souris
			else if (event.type == Event::MouseMoved)
			{
				// Si la souris passe par dessus le bouton Play, change le style
				if (play.getPosition(event.mouseMove.x, event.mouseMove.y))
				{

					play.setColorAndStyle(Color::Blue, Text::Bold);
				}
				// Si la souris passe par dessus le bouton Classement, change le style
				else if (classement.getPosition(event.mouseMove.x, event.mouseMove.y))
				{

					classement.setColorAndStyle(Color::Blue, Text::Bold);
				}
				// Si la souris passe par dessus le bouton Quitter, change le style
				else if (quitter.getPosition(event.mouseMove.x, event.mouseMove.y))
				{

					quitter.setColorAndStyle(Color::Blue, Text::Bold);
				}
				// Quand la souris sort d'un bouton, retourne le style au style original
				else
				{
					play.setColorAndStyle(Color::White, Text::Regular);
					classement.setColorAndStyle(Color::White, Text::Regular);
					quitter.setColorAndStyle(Color::White, Text::Regular);

				}
			}
			//Event qui suit les clics de la souris
			else if (event.type == Event::MouseButtonPressed)
			{
				// Event qui suit seulement le clic gauche de la souris
				if (event.mouseButton.button == Mouse::Left)
				{
					// Si un clic est fait sur le bouton Play, ouvre la fenetre pour jouer
					if (play.getPosition(event.mouseButton.x, event.mouseButton.y))
					{
						game tetrisGame;
						Event eventTetris;
						Clock clock;
						Time time;

						RenderWindow windowTetris(VideoMode(800, 600), "Tetris", Style::Titlebar | Style::Close);

						RectangleShape fondEcran;

						fondEcran.setSize(Vector2f(800, 600));	// Declare la taille de l'image de fond
						fondEcran.setFillColor(Color::White);
						
						Texture imageFond;
						if (!imageFond.loadFromFile("ressources/backgroundTetris.jpg"))
						{
							return 1;
						}
						fondEcran.setTexture(&imageFond);

						RectangleShape contour;
						contour.setOutlineColor(Color::Black);
						contour.setOutlineThickness(5);
						contour.setFillColor(Color::Transparent);
						contour.setPosition(Vector2f(250, 290));
						contour.setSize(Vector2f(300, 50));

						string playerInput;
						Text playerText;

						Text RedoText;
						Font font;

						button redo(185, 40, 310, 400, Color::Transparent);

						redo.setName("Retour au menu", font, "ressources/arial.ttf", 400, 400 + 15, 24, Color::Black, Text::Regular);

						tetrisGame.init();

						while (windowTetris.isOpen())
						{
							while (!tetrisGame.isGameOver())
							{
								while (windowTetris.pollEvent(eventTetris))
								{
									tetrisGame.inputKey();
								}

								tetrisGame.play();

								printText(score, tetrisGame.getScore(), font, "ressources/Arial.ttf", 123, 75, 24, Color::Black, Text::Regular);
								printText(level, tetrisGame.getLevel(), font, "ressources/Arial.ttf", 123, 135, 24, Color::Black, Text::Regular);

								windowTetris.clear();
								windowTetris.draw(fondEcran);
								tetrisGame.drawGame(windowTetris);
								windowTetris.draw(score);
								windowTetris.draw(level);
								windowTetris.display();
							}
							while (windowTetris.pollEvent(eventTetris))
							{
								if (event.type == Event::MouseMoved)
								{ 
									if (redo.getPosition(event.mouseMove.x, event.mouseMove.y))
									{
										redo.setColorAndStyle(Color::Black, Text::Bold);
									}
									else
									{
										redo.setColorAndStyle(Color::Black, Text::Regular);
									}
								}

								getUserName(stats, eventTetris, windowTetris, tetrisGame.getScoreInt(), playerText, playerInput, redo);
							}
							printText(gameOver, "Vous avez perdu!\nVotre score : " + tetrisGame.getScore(), font, "ressources/Arial.ttf", 800 / 2, 160, 48, Color::Black, Text::Regular);
							printText(lineCount, "Vous avez pulvérisé " + tetrisGame.getLineCount() + " lignes!", font, "ressources/Arial.ttf", 800 / 2, 240, 48, Color::Black, Text::Regular);
							printText(playerText, playerInput, font, "ressources/arial.ttf", 400, 300, 40, Color::Black, Text::Bold);
							windowTetris.clear(Color::White);
							windowTetris.draw(gameOver);
							windowTetris.draw(lineCount);
							windowTetris.draw(playerText);
							windowTetris.draw(contour);
							redo.print(windowTetris);
							windowTetris.display();
						}
					}
					// Si un clic est fait sur le bouton Classement, ouvre la fenetre des classements
					else if (classement.getPosition(event.mouseButton.x, event.mouseButton.y))
					{
						Event eventStats;		// Initialise les Event pour le classement
						// Fait la creation de la fenêtre pour le classement
						RenderWindow windowClassement(VideoMode(800, 600), "Classement", Style::Titlebar | Style::Close);
						RectangleShape imgBackgStats;		// Initialise un rectangle pour ajouter l'image de fond

						imgBackgStats.setSize(Vector2f(800, 600));
						imgBackgStats.setFillColor(Color::White);

						Texture textureImgBackgStats;
						if (!textureImgBackgStats.loadFromFile("ressources/MenuStats.jpg"))  // Fait l'implementation de l'image de fond
						{
							return 1;
						}
						imgBackgStats.setTexture(&textureImgBackgStats);

						windowClassement.draw(imgBackgStats);		// Affiche l'image de fond

						// Cette fonction permet d'afficher le classement
						printRanking(stats, windowClassement, font);

						windowClassement.display();	//Affiche le tout
						// Tant que la fenetre de classement est ouverte
						while (windowClassement.isOpen())
						{
							while (windowClassement.pollEvent(eventStats))
							{

								if (eventStats.type == Event::KeyPressed)		// Ferme la fenetre si on appuie sur Escape
								{
									switch (eventStats.key.code)
									{
									case Keyboard::Escape:
										windowClassement.close();
									}
								}
								else if (eventStats.type == Event::Closed)		// Ferme la fenêtre si on clique sur le X
								{
									windowClassement.close();
								}

							}
						}

					}
					// Si on clique sur le bouton quitter, ferme le programme
					else if (quitter.getPosition(event.mouseButton.x, event.mouseButton.y))
					{
						menu.close();
					}

				}

			}


		}
		menu.clear();
		menu.draw(imgBackg);		// Affiche l'image de fond du menu
		play.print(menu);			// Affiche le bouton Play
		classement.print(menu);		// Affiche le bouton classement
		quitter.print(menu);		// Affiche le bouton quitter
		menu.display();
	}
	return 0;
}


// Permet de faire la configuration necessaire pour faire fonctionner Text en SFML
void printText(Text& text, string message, Font& font, const char* police,
	int posX, int posY, int taille, const Color& color, int style)
{

	font.loadFromFile(police);

	text.setFont(font);									// Assigne la police a utiliser (elle doit avoir ete chargee)
	text.setString(message);							// Assigne le texte a afficher
	text.setCharacterSize(taille);						// Assigne la taille (en pixels)
	text.setFillColor(color);							// Assigne la couleur du texte
	text.setStyle(style);								// Assigne le style du texte
	text.setPosition(posX, posY);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);

}

// Cette fonction lit les donnees du fichier texte de score et le stock dans la struct
void readScore(statistique stats[1])
{

	ifstream rFile;
	string name;
	int scoreTemp;

	rFile.open("Scores.txt");	// Ouvre le fichier
	if (!rFile.is_open())
	{
		exit;
	}
	int j = 0;		// Compteur pour l'ordre du classement

	// Tant que ce n'est pas a la fin du fichier
	while (!rFile.eof())
	{
		rFile >> name >> scoreTemp;
		stats->_name.insert(stats->_name.begin() + j, name);		// Ajoute le nom et le score
		stats->_score.insert(stats->_score.begin() + j, scoreTemp);
		j++;
	}

	rFile.close();				// Ferme le fichier

}


// Cette fonction sert a inserer le joueur qui vient de finir une partie a l'interieur du classement si il est dans le top 10
void insertPlayer(statistique stats[1], string userNow, int scoreNow)
{
	for (int i = 0; i < 10; i++)
	{
		// Si le score du joueur est plus grand ou egal, inserer avant et sortir de la boucle
		if (stats[0]._score.at(i) <= scoreNow)
		{
			stats->_name.insert(stats->_name.begin() + i, userNow);
			stats->_score.insert(stats->_score.begin() + i, scoreNow);
			break;
		}
	}
	// S'il y a plus de 10 personnes dans le classement, supprimer la derniere
	if (stats->_name.size() > 10)
	{
		stats->_name.pop_back();
		stats->_score.pop_back();
	}
}


// Permet d'ecrire le nouveau classement dans le fichier, a ecrire apres chaque partie
void writeScore(statistique stats[1])
{
	ofstream wFile;
	wFile.open("Scores.txt");		// Ouvre le fichier pour ecrire
	if (!wFile.is_open())
	{
		exit;
	}
	for (int i = 0; i < 10; i++)
	{
		wFile << stats[0]._name.at(i) << " " << stats[0]._score.at(i) << endl;		// Ecrit le classement dans le fichier
	}

	wFile.close();		// Ferme le fichier
}

// Cette fonction permet d'afficher le classement dans la fenetre statistique lorsqu'elle est ouverte
void printRanking(statistique stats[1], RenderWindow& window, Font& font)
{
	readScore(stats);		// Retourne chercher le classement, car il peut avoir ete modifie si on a joue
	Text classement;		// Text pour le titre 
	printText(classement, "Classement", font, "ressources/arial.ttf", 400, 20, 40, Color::White, Text::Bold);

	Text textStats;			// Texte pour le nom
	Text score;				// Texte pour le score
	int y = 0;				// Compteur pour l'Esapce entre les nom

	for (int i = 0; i < 10; i++)
	{

		// Assigne le texte pour le nom du i
		printText(textStats, stats[0]._name.at(i), font, "ressources/arial.ttf", 325, (125 + y), 24, Color::White, Text::Regular);
		// Assigne le texte pour le score du i
		printText(score, to_string(stats[0]._score.at(i)), font, "ressources/arial.ttf", 475, (125 + y), 24, Color::White, Text::Regular);
		y += 35;		// Incremente l'espace

		window.draw(textStats);		// Affiche le nom
		window.draw(score);			// Affiche le score
	}
	window.draw(classement);		// Affiche le titre
}

void getUserName(statistique stats[1], Event& event, RenderWindow& window, int score, Text& playerText, string& playerInput, button redo)
{

	if (event.type == Event::TextEntered)
	{
		if (event.text.unicode == '\b')
		{
			if (playerInput.size() != 0)
			{
				playerInput.erase(playerInput.size() - 1, 1);
				playerInput.size();
			}
		}
		else if (playerInput.size() <= 10)
		{
			playerInput += event.text.unicode;
		}
		playerText.setString(playerInput);
	}

	else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		if (redo.getPosition(event.mouseButton.x, event.mouseButton.y))
		{
			if (playerInput.size() > 0)
			{
				insertPlayer(stats, playerInput, score);
				writeScore(stats);
			}
			window.close();
		}
	}
}
