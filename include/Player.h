#pragma once

#include "Bullet.h"

using namespace sf;

class Player
{
    public:
        Player(std::vector<Texture>& textures, Keyboard::Key UP, Keyboard::Key DOWN, Keyboard::Key LEFT, Keyboard::Key RIGHT, Keyboard::Key SHOOT);
        virtual ~Player();

        //Accessprs
        inline std::vector<Bullet>& getBullets()
        {
            return this->bullets;
        }
        inline const Vector2f& getPosition() const
        {
            return this->sprite.getPosition();
        }

        inline const String getHpAsString() const { return std::to_string(this->hp) + "/" + std::to_string(this->hpMax); }
        inline const int getDamage() const { return rand() % this->damageMax + this->damage; }
        inline const int getHp() const { return this->hp; }
        inline sf::FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }

        //Functions
        void UpdateAccessories(const float& dt);
        void Combat(const float& dt);
        void MovementMouse();
        void MovementJoystick();
        void Movement(const float& dt);
        void Update(Vector2u& windowBound, const float& dt);
        void Draw(RenderTarget& target);

        void TakeDamage(int damage);

        //statics
        static unsigned playerNr;

    protected:

    private:

        unsigned playerNumber;
        Vector2f playerCenter;

        float shootTimer;
        float shootTimerMax;
        float damageTimer;
        float damageTimerMax;

        Texture* texture;
        Texture* bulletTexture;
        Texture* mainGunTexture;
        Sprite sprite;
        RectangleShape hitBox;

        Sprite mainGunSprite;

        std::vector<Bullet> bullets;

        Keyboard::Key controlsKey[5];

        Vector2f currentVelocity;
        float maxVelocity;
        float acceleration;
        Vector2f direction;
        float stabilizerForce;
        int level;
        int exp;
        int expNext;

        int hp;
        int hpMax;

        int damage;
        int damageMax;

        int score;

        float dtMultiplier;
};
