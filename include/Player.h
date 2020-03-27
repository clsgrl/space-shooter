#pragma once

#include "Bullet.h"

using namespace sf;

class Player
{
    public:
        Player(Texture* texture, Texture* bulletTexture, int UP = 28, int DOWN = 18, int LEFT = 0, int RIGHT = 3, int SHOOT = 57);
        Player(Texture* texture, Texture* bulletTexture, Keyboard::Key UP, Keyboard::Key DOWN, Keyboard::Key LEFT, Keyboard::Key RIGHT, Keyboard::Key SHOOT);
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

        //Functions
        void Combat();
        void Movement();
        void Update(Vector2u windowBound);
        void Draw(RenderTarget& target);

        //statics
        static unsigned playerNr;

    protected:

    private:

        unsigned playerNumber;
        Vector2f playerCenter;

        int shootTimer;
        int shootTimerMax;
        int damageTimer;
        int damageTimerMax;

        Texture* texture;
        Texture* bulletTexture;
        Sprite sprite;
        RectangleShape hitBox;

        std::vector<Bullet> bullets;

        int controls[5];
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
};