#include "Player.h"
#include <iostream>

unsigned Player::playerNr = 0;

enum controls { UP = 0, DOWN, LEFT, RIGHT, SHOOT };

Player::Player(std::vector<Texture>& textures, Keyboard::Key UP, Keyboard::Key DOWN, Keyboard::Key LEFT, Keyboard::Key RIGHT, Keyboard::Key SHOOT)
    : level(1), exp(0), expNext(100), hp(10), hpMax(10), damage(1), damageMax(2), score(0)
{
    this->bulletTexture = &textures[1];
    this->sprite.setTexture(textures[0]);
    this->sprite.setScale(0.12f, 0.12f);

    this->shootTimerMax = 25;
    this->shootTimer = this->shootTimerMax;

    this->damageTimerMax = 10;
    this->damageTimer = this->damageTimerMax;

    this->controlsKey[controls::UP] = UP;
    this->controlsKey[controls::DOWN] = DOWN;
    this->controlsKey[controls::LEFT] = LEFT;
    this->controlsKey[controls::RIGHT] = RIGHT;
    this->controlsKey[controls::SHOOT] = SHOOT;

    this->stabilizerForce = 0.3f;
    this->maxVelocity = 20.f;
    this->acceleration = 1.f;

    Player::playerNr++;
    this->playerNumber = Player::playerNr;

    std::cout << "player position: " << this->sprite.getPosition().x << " " << this->sprite.getPosition().y << "\n";
}

Player::~Player()
{
    //dtor
}

void Player::UpdateAccessories()
{
    this->mainGunSprite.setPosition(
        this->playerCenter.x,
        this->playerCenter.y);

    // std::cout << "gun position " << this->mainGunSprite.getPosition().x << " " << this->mainGunSprite.getPosition().y << "\n";

}

void Player::MovementMouse()
{
    //this should be changed with getPosition(window) to get the local position of the mouse inside the window.
    sf::Vector2i localPosition = sf::Mouse::getPosition();

    this->sprite.move(localPosition.x, localPosition.y);

    //update position
    this->playerCenter.x = this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2;
    this->playerCenter.y = this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2;

}

void Player::MovementJoystick()
{
    float x = sf::Joystick::getAxisPosition(0.f, sf::Joystick::X);
    float y = sf::Joystick::getAxisPosition(0.f, sf::Joystick::Y);

    if(x<1. && x>-1.) x=0.0f;
    if(y<1. && y>-1.) y=0.0f;

    //final move
    this->sprite.move(x, y);
    std::cout << "x="<< x << " - y="<< y<<std::endl;
    //update position
    this->playerCenter.x = this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2;
    this->playerCenter.y = this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2;
}


void Player::Movement()
{
    if (Keyboard::isKeyPressed(this->controlsKey[controls::UP]))
    {
        this->direction.x = 0.f;
        this->direction.y = -1.f;

        if (this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0.f)
            this->currentVelocity.y += this->direction.y * this->acceleration;
    }
    if (Keyboard::isKeyPressed(this->controlsKey[controls::DOWN]))
    {
        this->direction.x = 0.f;
        this->direction.y = 1.f;

        if (this->currentVelocity.y < this->maxVelocity && this->direction.y > 0.f)
            this->currentVelocity.y += this->direction.y * this->acceleration;
    }

    if (Keyboard::isKeyPressed(this->controlsKey[controls::LEFT]))
    {
        this->direction.x = -1.f;
        this->direction.y = 0.f;

        if (this->currentVelocity.x > -this->maxVelocity && this->direction.x < 0.f)
            this->currentVelocity.x += this->direction.x * this->acceleration;

    }
    if (Keyboard::isKeyPressed(this->controlsKey[controls::RIGHT]))
    {
        this->direction.x = 1.f;
        this->direction.y = 0.f;

        if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0.f)
            this->currentVelocity.x += this->direction.x * this->acceleration;
    }

    //drag force
    if (this->currentVelocity.x > 0)
    {
        this->currentVelocity.x -= this->stabilizerForce;

        if (this->currentVelocity.x < 0)
            this->currentVelocity.x = 0;
    }
    else if (this->currentVelocity.x < 0)
    {
        this->currentVelocity.x += this->stabilizerForce;

        if (this->currentVelocity.x > 0)
            this->currentVelocity.x = 0;
    }

    if (this->currentVelocity.y > 0)
    {
        this->currentVelocity.y -= this->stabilizerForce;

        if (this->currentVelocity.y < 0)
            this->currentVelocity.y = 0;
    }
    else if (this->currentVelocity.y < 0)
    {
        this->currentVelocity.y += this->stabilizerForce;

        if (this->currentVelocity.y > 0)
            this->currentVelocity.y = 0;
    }

    //final move
    this->sprite.move(this->currentVelocity.x, this->currentVelocity.y);

    //update position
    this->playerCenter.x = this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2;
    this->playerCenter.y = this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2;

    //std::cout << "player position= " << this->sprite.getPosition().x << " " << this->sprite.getPosition().y << "\n";
}

void Player::Combat()
{
    if ((Keyboard::isKeyPressed(this->controlsKey[controls::SHOOT]) ||
        sf::Joystick::isButtonPressed(0, 1)
         /*|| sf::Mouse::isButtonPressed(sf::Mouse::Left)*/)
        && this->shootTimer >= this->shootTimerMax)
    {
        this->bullets.push_back(
            Bullet(bulletTexture, this->playerCenter,
                    Vector2f(1.f, 0.f), 5.f, 25.f, 0.5f));

        this->shootTimer = 0; // reset timer
    }
}

void Player::Update(Vector2u& windowBound)
{
    if (this->sprite.getPosition().x >= 0 && this->sprite.getPosition().x < windowBound.x
        && this->sprite.getPosition().y >= 0 && this->sprite.getPosition().y < windowBound.y)
    {
        //update timers
        if (this->shootTimer < this->shootTimerMax)
            this->shootTimer++;

        if (this->damageTimer < this->damageTimerMax)
            this->damageTimer++;

        if (sf::Joystick::isConnected(0))
            this->MovementJoystick();
        else
            this->Movement();
        this->UpdateAccessories();
        this->Combat();
    }
    else
    {
        if (this->sprite.getPosition().x < 0)
            this->sprite.setPosition(0, this->sprite.getPosition().y);
        if (this->sprite.getPosition().x > windowBound.x)
            this->sprite.setPosition(windowBound.x - 10, this->sprite.getPosition().y);
        if (this->sprite.getPosition().y < 0)
            this->sprite.setPosition(this->sprite.getPosition().x, 0);
        if (this->sprite.getPosition().y > windowBound.y)
            this->sprite.setPosition(this->sprite.getPosition().x, windowBound.y - 5);
    }
}


void Player::Draw(RenderTarget& target)
{
    for (size_t i = 0; i < this->bullets.size(); i++)
    {
        this->bullets[i].Draw(target);
    }
    target.draw(this->sprite);
    target.draw(this->mainGunSprite);
}
