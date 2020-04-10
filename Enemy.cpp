#include "Enemy.h"

enum eTypes { MOVELEFT = 0, FOLLOW, FOLLOWFAST, FOLLOWSHOOT, FOLLOWFASTSHOOT};

Enemy::Enemy(Texture* texture, sf::Vector2u windowBounds, sf::Vector2f position, sf::Vector2f direction, sf::Vector2f scale, int type,
              int hpMax, int damageMax, int damageMin)
{
    this->texture = texture;
    this->sprite.setTexture(*this->texture);
    this->sprite.setScale(scale);
    this->sprite.setPosition(windowBounds.x - 100, rand() % windowBounds.y + this->sprite.getGlobalBounds().height);


    this->type = type;

    this->hpMax = hpMax;

    this->damageMax = damageMax;
    this->damageMin = damageMin;

}

Enemy::~Enemy()
{
    //dtor
}


void Enemy::TakeDamage(int damage)
{
    this->hp -= damage;

    if (this->hp <= 0)
        this->hp = 0;
}

void Enemy::Update()
{
    switch (this->type)
    {
    case 0:
        this->sprite.move(-1.f, 0.f);
        break;
    default:
        break;
    }
}

void Enemy::Draw(RenderTarget& target)
{
    target.draw(this->sprite);
}
