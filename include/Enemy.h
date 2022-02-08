#pragma once

#include "Bullet.h"

class Enemy
{
    public:
        Enemy(Texture* texture, sf::Vector2u windowBounds, sf::Vector2f position, sf::Vector2f direction, sf::Vector2f scale, int type,
              int hpMax, int damageMax, int damageMin);
        virtual ~Enemy();

        inline const int getDamage() const { return rand() % this->damageMax + this->damageMin;}
        inline const int getHP() const { return this->hp; }
        inline const int getHPMax() const { return this->hpMax; }
        inline const bool isDead() const { return this->hp <= 0; }
        inline sf::FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
        inline sf::Vector2f getPosition() const { return this->sprite.getPosition(); }

        void TakeDamage(int damage);
        void BackOff();
        void Update(const float& dt);
        void Draw(RenderTarget& target);

    protected:

    private:
        Texture* texture;
        Sprite sprite;

        int type;
        int hp;
        int hpMax;
        int damageMin;
        int damageMax;

        float dtMultiplier;
};
