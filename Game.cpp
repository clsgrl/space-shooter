#include "Game.h"

Game::Game(RenderWindow* window)
{
    this->window = window;
    this->window->setFramerateLimit(60);

    //init font
    this->font.loadFromFile("Fonts/Dosis-Light.ttf");

    //Init textures;
    this->playerTexture.loadFromFile("Textures/ship.png");
    this->bulletTexture.loadFromFile("Textures/Guns/missileTex01.png");
    this->gunTexture01.loadFromFile("Textures/Guns/gun01.png");
    //Init player

    players.push_back(Player(&playerTexture, &bulletTexture, &gunTexture01, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Space ));

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
    }

    for(size_t i = 0; i < this->staticPlayerTexts.size(); i++)
    {
    }

}

void Game::Update()
{
    sf::Vector2u windowSize = this->window->getSize();
    for (size_t i = 0; i < players.size(); i++)
    {
        this->window->getSize();
        players[i].Update(windowSize);

        //bullets update
        for (size_t j = 0; j < this->players[i].getBullets().size(); j++)
        {
            this->players[i].getBullets()[j].Update();

            //windows bound check
            if (this->players[i].getBullets()[j].getPosition().x > this->window->getSize().x - 50)
            {
                this->players[i].getBullets().erase(this->players[i].getBullets().begin() + j);
                //std::cout << "erased bullets" << j << "\n";
                break;
            }

        }

        //enemies collision check
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

    this->DrawUI();

    window->display();
}
