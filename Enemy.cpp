#include "Enemy.h"

enum eTypes { MOVELEFT = 0, FOLLOW, FOLLOWFAST, FOLLOWSHOOT, FOLLOWFASTSHOOT};

Enemy::Enemy(Texture* texture, sf::Vector2f position, sf::Vector2f direction, sf::Vector2f scale, int type,
              int hpMax, int damageMax, int damageMin)
{
    this->texture = texture;
    this->sprite.setTexture(*this->texture);
    this->sprite.setScale(scale);

    this->type = type;

    this->hpMax = hpMax;

    this->damageMax = damageMax;
    this->damageMin = damageMin;

}

Enemy::~Enemy()
{
    //dtor
}


void Enemy::TakeDamage()
{

}

void Enemy::Update()
{
    switch (this->type)
    {
    case 0:
        this->sprite.move(-10.f, 0.f);
        break;
    default:
        break;
    }
}

void Enemy::Draw(RenderTarget& target)
{
    target.draw(this->sprite);
}
