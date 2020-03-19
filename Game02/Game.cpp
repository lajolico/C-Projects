#include "Game.h"

/*
Purpose: 
*/

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
}

const bool Game::isRunning() const
{
	return this->window->isOpen();
}

//Boolean function that returns whether or not the window is open
void Game::updatePollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case (sf::Event::Closed):
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
				break;
			}
		}
	}
}

//init variables
void Game::initVariables()
{
	//init the window with something
	this->window = nullptr;


	//Rain 
	this->maxNumOfRain = 20;
	this->spawnTimerMax = 25.f;
	this->spawnTimer = 0.f;
	this->radius = 13.f;
	this->collected = 0;
	this->isDeleted = false;
	this->movement.x = 0.f;
	this->movement.y = 2.f;

	//Player
	this->mouseHeld = false; 

}

//Create the window 
void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 600;

	this->window = new sf::RenderWindow(this->videoMode, "Colored Rain", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}


void Game::initFonts()
{
	/*
		Load in the fonts required for our program
	*/
	if (!this->font.loadFromFile("Fonts/BebasNeue-Regular.ttf")) {
		std::cout << "Failed to load font" << std::endl;
	}
}

void Game::initText()
{
	/*
	Initialize our text and ui for our program	
	*/
	std::stringstream ss;

	ss << "Collected: " << this->collected;

	this->text.setFont(this->font);
	this->text.setCharacterSize(24);
	this->text.setFillColor(sf::Color::White);
	this->text.setPosition(sf::Vector2f(10.f, 10.f));
}




void Game::setRain()
{
	/*
		@return void
		
		-spawns rain onto the window
		-sets a random pos
		-sets the color
		-adds rain to the vector
	*/
	
	//Set a random position between window.width and at 0 window.height

	//Base on the random int derive a new enemy type
	this->enemyType = rand() % 5;

	float randomRadius = static_cast<float> ( 9 + rand() % 15);

	switch (enemyType) 
	{
	case 0: 
		this->rainDrop.setFillColor(sf::Color::Cyan);
		this->rainDrop.setRadius(randomRadius); 
		break;
	case 1: 
		this->rainDrop.setFillColor(sf::Color::White);
		this->rainDrop.setRadius(randomRadius);
		break;
	case 2:
		this->rainDrop.setFillColor(sf::Color::Magenta);
		this->rainDrop.setRadius(randomRadius);
		break;
	case 3:
		this->rainDrop.setFillColor(sf::Color::Yellow);
		this->rainDrop.setRadius(randomRadius);
		break;
	case 4:
		this->rainDrop.setFillColor(sf::Color::Green);
		this->rainDrop.setRadius(randomRadius);
		break;
	default:
		break;
	}

	this->rainDrop.setPosition(rand() % (this->window->getSize().x) - this->rainDrop.getRadius(), 0.f);

	this->rainDrops.push_back(this->rainDrop);

}



void Game::updateMousePosition()
{
	/*
	@return void
	Constantly check the position of the mouse in reference to the game window
	map the location of the mouse to mousePosView for accurate results
	*/
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Collected: " << this->collected;
	this->text.setString(ss.str());
}


void Game::updateRain()
{
	/*
		@return void
		Spawn counter and checker
		Removes rain drops at the edge of the screen
	*/

	if (static_cast<unsigned int>(this->rainDrops.size()) < static_cast<unsigned int>(this->maxNumOfRain)) {
		if (this->spawnTimer <= this->spawnTimerMax)
		{
			this->spawnTimer += 1.f;
		}
		else {
			this->setRain();
			this->spawnTimer = 0.f;
		}
	}

	//Iterating through the vector of rainDrops
	//Move the raindrop, check if it's in bounds of the mouse
	for (unsigned int i = 0, ilen = this->rainDrops.size(); i < ilen; ++i)
	{
		//Translate the raindrops
		this->rainDrops[i].move(this->movement);

		//Check if the raindrop is outside of the height of the window
		if (this->rainDrops[i].getPosition().y > this->window->getSize().y)
		{
			this->rainDrops.erase(this->rainDrops.begin() + i);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!this->mouseHeld)
		{
			this->mouseHeld = true;
			this->isDeleted = false;

			for (unsigned int r = 0, rlen = this->rainDrops.size(); r < rlen && !this->isDeleted; ++r) {

				if (this->rainDrops[r].getGlobalBounds().contains(this->mousePosView))
				{
					this->rainDrops.erase(this->rainDrops.begin() + r);
					this->isDeleted = true;
					this->collected++;
				}
			}
		}
	}
	else 
	{
		this->mouseHeld = false;
	}
}

void Game::update()
{
	/*
	@return void
	Is the game manager loop
	*/
	this->updatePollEvents();
	this->updateRain();
	this->updateText();
	this->updateMousePosition();
}

void Game::renderText(sf::RenderTarget& Target)
{
	this->window->draw(this->text);
}

void Game::renderRain(sf::RenderTarget& Target)
{
	/*
	Using a type reference of auto, loop through the vector of rainDrops
	Is a lot faster than a conventional for loop
	*/
	for (auto& r : this->rainDrops)
	{
		this->window->draw(r);
	}
}

void Game::render()
{
	/*
	Essentially render objects to the window
	*/
	this->window->clear();

	this->renderRain(*this->window);

	this->renderText(*this->window);

	this->window->display();
}

//Deconstructor, ensure now memory leaks
Game::~Game()
{
	delete this->window;
}