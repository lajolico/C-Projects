#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <sstream>


/*
PURPOSE: Header file for our Game Manager
*/

class Game
{
public:
	
	//public functions
	const bool isRunning() const;
	void update();
	void render();

	//Instaniate the constructor and destructor
	Game();
	~Game();

private:
	//Private vars
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;

	//Resources
	sf::Font font;
	sf::Text text;

	//mouse logic and objects
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	bool mouseHeld;


	//game logic vars
	unsigned collected;
	int maxNumOfRain;
	float rainSpeed;
	float spawnTimer;
	float spawnTimerMax;
	float radius;
	bool isDeleted;
	int enemyType;
	

	//Game Objects
	std::vector <sf::CircleShape> rainDrops;
	sf::CircleShape rainDrop;
	sf::Vector2f movement;

	//Private functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();

	void updatePollEvents();
	void setRain();
	void updateRain();
	void updateMousePosition();
	void updateText();


	void renderRain(sf::RenderTarget& Target);
	void renderText(sf::RenderTarget& Target);

};
