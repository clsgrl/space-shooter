#include "Player.h"
#include <iostream>

unsigned Player::playerNr = 0;

enum controls { UP = 0, DOWN, LEFT, RIGHT, SHOOT };

Player::Player(Texture* texture, Texture* bulletTexture, Texture* mainGunTexture, Keyboard::Key UP, Keyboard::Key DOWN, Keyboard::Key LEFT, Keyboard::Key RIGHT, Keyboard::Key SHOOT)
    : level(1), exp(0), expNext(100), hp(10), hpMax(10), damage(1), damageMax(2), score(0)
{
    this->texture = texture;
    this->bulletTexture = bulletTexture;
    this->sprite.setTexture(*this->texture);
    this->sprite.setScale(0.12f, 0.12f);

    this->mainGunTexture = mainGunTexture;
    this->mainGunSprite.setTexture(*this->mainGunTexture);
    this->mainGunSprite.setOrigin(this->mainGunSprite.getGlobalBounds().width / 2,
                                  this->mainGunSprite.getGlobalBounds().height / 2);
    this->mainGunSprite.rotate(90);

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

void Player::Movement()
{

    if (Keyboard::isKeyPressed(this->controlsKey[controls::UP]))
    {
        direction.x = 0.f;
        direction.y = -1.f;

        if (this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0.f)
            this->currentVelocity.y += direction.y * this->acceleration;
    }
    if (Keyboard::isKeyPressed(this->controlsKey[controls::DOWN]))
    {
        direction.x = 0.f;
        direction.y = 1.f;

        if (this->currentVelocity.y < this->maxVelocity && this->direction.y > 0.f)
            this->currentVelocity.y += direction.y * this->acceleration;
    }

    if (Keyboard::isKeyPressed(this->controlsKey[controls::LEFT]))
    {
        direction.x = -1.f;
        direction.y = 0.f;

        if (this->currentVelocity.x > -this->maxVelocity && this->direction.x < 0.f)
            this->currentVelocity.x += direction.x * this->acceleration;

    }
    if (Keyboard::isKeyPressed(this->controlsKey[controls::RIGHT]))
    {
        direction.x = 1.f;
        direction.y = 0.f;

        if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0.f)
            this->currentVelocity.x += direction.x * this->acceleration;
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
    this->playerCenter.x = this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/2;
    this->playerCenter.y = this->sprite.getPosition().y + this->sprite.getGlobalBounds().height/2;
}

void Player::Combat()
{
    if (Keyboard::isKeyPressed(this->controlsKey[controls::SHOOT]) && this->shootTimer >= this->shootTimerMax)
    {
        this->bullets.push_back(
            Bullet(bulletTexture, this->playerCenter,
                    Vector2f(1.f, 0.f), 5.f, 25.f, 0.5f));

        this->shootTimer = 0; // reset timer
    }
}


void Player::Update(Vector2u windowBound)
{
    //update timers
    if (this->shootTimer < this->shootTimerMax)
        this->shootTimer++;

    if (this->damageTimer < this->damageTimerMax)
        this->damageTimer++;

    this->Movement();
    this->UpdateAccessories();
    this->Combat();
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
