#include "Bullet.h"

Bullet::Bullet(Texture* texture, Vector2f position,
               Vector2f direction, float initialVelocity,
               float maxVelocity, float acceleration)
{
    this->texture = texture;
    this->sprite.setTexture(*this->texture);
    this->maxVelocity = maxVelocity;
    this->sprite.setScale(0.1f, 0.1f);
    this->sprite.setPosition(position);
    this->maxVelocity = maxVelocity;
    this->acceleration = acceleration;
    this->direction = direction;
    this->currentVelocity = Vector2f(initialVelocity * this->direction.x, initialVelocity * this->direction.y);
    this->sprite.setPosition(Vector2f(position.x - this->sprite.getGlobalBounds().width / 2,
                                      position.y - this->sprite.getGlobalBounds().height / 2));
    this->dtMultiplier = 60.f;
}

Bullet::~Bullet()
{

}

void Bullet::Movement(const float& dt)
{
    if (this->acceleration > 0.f)
    {
        if (this->currentVelocity.x < this->maxVelocity)
            this->currentVelocity.x += this->acceleration * this->direction.x * dt * dtMultiplier;
        if (this->currentVelocity.y < this->maxVelocity)
            this->currentVelocity.y += this->acceleration * this->direction.y * dt * dtMultiplier;
    }
    else
    {
        this->currentVelocity = Vector2f(
             this->maxVelocity * this->direction.x,
             this->maxVelocity * this->direction.y);
    }

    this->sprite.move(this->currentVelocity * dt * dtMultiplier);
}

void Bullet::Update(const float& dt)
{
    this->Movement(dt);
}

void Bullet::Draw(RenderTarget& target)
{
    target.draw(this->sprite);
}
