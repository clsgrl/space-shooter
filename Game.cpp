#include "Game.h"

enum texture { PLAYER = 0, MISSILE, ENEMY01};

Game::Game(RenderWindow* window)
{
    this->window = window;
    //60 frame per seconds. The function Update() is called 60 times in a second
    this->window->setFramerateLimit(200);
    this->dtMultiplier = 60.f;

    //init font
    this->font.loadFromFile("Fonts/Dosis-Light.ttf");

    //Init textures;
    this->textures.push_back(Texture());
    this->textures[texture::PLAYER].loadFromFile("Textures/ship.png");
    this->textures.push_back(Texture());
    this->textures[texture::MISSILE].loadFromFile("Textures/Guns/missileTex01.png");
    this->textures.push_back(Texture());
    this->textures[texture::ENEMY01].loadFromFile("Textures/enemyFollow.png");
    //Init player

    this->players.push_back(Player(this->textures, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Space ));

    //TODO: make it configurable
    this->enemySpawnTimerMax = 100;
    this->enemySpawnTimer = this->enemySpawnTimerMax;

    this->InitUI();
}

Game::~Game()
{

}

void Game::Clear()
{
    window->clear();
}

void Game::InitUI()
{
    Text tempText;
    for(size_t i = 0; i < this->players.size(); i++)
    {
        tempText.setFont(font);
        tempText.setCharacterSize(12);
        tempText.setColor(Color::White);
        tempText.setString(std::to_string(i+1));

        this->followPlayerTexts.push_back(Text(tempText));

        tempText.setFont(font);
        tempText.setCharacterSize(14);
        tempText.setColor(Color::White);
        tempText.setString("Player 1");

        this->staticPlayerTexts.push_back(Text(tempText));
    }
}

void Game::UpdateUI()
{
    for(size_t i = 0; i < this->followPlayerTexts.size(); i++)
    {
        this->followPlayerTexts[i].setPosition(this->players[i].getPosition().x, this->players[i].getPosition().y - 20.f );
        this->followPlayerTexts[i].setString(std::to_string(i + 1) + "          " + this->players[i].getHpAsString());
        if (this->players[i].getHp() == 0)
            this->followPlayerTexts.erase(this->followPlayerTexts.begin() + i);
    }

    for(size_t i = 0; i < this->staticPlayerTexts.size(); i++)
    {
    }

}

//TODO: refactor this function
void Game::Update(const float& dt)
{
    //update timers
    if (this->enemySpawnTimer < this->enemySpawnTimerMax)
        this->enemySpawnTimer += 1.f * dt * dtMultiplier;

    //spawn enemies
    if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
    {
        this->enemies.push_back(Enemy(&this->textures[texture::ENEMY01],
          this->window->getSize(),
          sf::Vector2f(0.f, 0.f),
          sf::Vector2f(-1.f, 0.f),
          sf::Vector2f(0.1f, 0.1f),
          0, rand() % 3 + 1, 3, 1));
        this->enemySpawnTimer = 0;
    }

    sf::Vector2u windowSize = this->window->getSize();
    for (size_t i = 0; i < players.size(); i++)
    {
        this->window->getSize();
        players[i].Update(windowSize, dt);

        //bullets update
        for (size_t j = 0; j < this->players[i].getBullets().size(); j++)
        {
            this->players[i].getBullets()[j].Update(dt);

            //enemies collision check
            for (size_t k = 0; k < this->enemies.size(); k++)
            {
                if (this->players[i].getBullets()[j].getGlobalBounds().intersects(this->enemies[k].getGlobalBounds()))
                {
                    this->players[i].getBullets().erase(this->players[i].getBullets().begin() + j);

                    this->enemies.erase(this->enemies.begin() + k);
                    break;
                }
            }

            //windows bound check
            size_t bullets = players[i].getBullets().size();
            if (j < bullets) // this needs to be done because the bullet[j] might have been erased before when collided with an enemy
            {
                if (this->players[i].getBullets()[j].getPosition().x > this->window->getSize().x - 50)
                {
                    this->players[i].getBullets().erase(this->players[i].getBullets().begin() + j);
                    break;
                }
            }
            
            //enemies collision check
        }

        for (size_t k = 0; k < this->enemies.size(); k++)
        {
            if (this->enemies[k].getGlobalBounds().intersects(this->players[i].getGlobalBounds()))
            {
                this->enemies[k].BackOff();
                this->players[i].TakeDamage(1);
                if (this->players[i].getHp() == 0)
                {
                    this->players.erase(this->players.begin() + i);
                }
            }
        }
    }

    //enemies update
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        this->enemies[i].Update(dt);

        if (this->enemies[i].getPosition().x < 0 + this->enemies[i].getGlobalBounds().width)
        {
            this->enemies.erase(this->enemies.begin() + i);
            break;
        }
    }

    //UPDATE UI
    this->UpdateUI();
}

void Game::DrawUI()
{
    for(size_t i = 0; i < this->followPlayerTexts.size(); i++)
    {
        this->window->draw(this->followPlayerTexts[i]);
    }

    for(size_t i = 0; i < this->staticPlayerTexts.size(); i++)
    {
        this->window->draw(this->staticPlayerTexts[i]);
    }
}

void Game::Draw()
{
    window->clear();

    for (size_t i = 0; i < players.size(); i++)
    {
        this->players[i].Draw(*this->window);
    }

    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        this->enemies[i].Draw(*this->window);
    }

    this->DrawUI();

    window->display();
}
