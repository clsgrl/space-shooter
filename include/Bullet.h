#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

using namespace sf;

class Bullet
{
    public:
        Bullet(Texture* texture, Vector2f position,
               Vector2f direction, float initialVelocity,
               float maxVelocity, float acceleration);
        virtual ~Bullet();

        //Accessprs
        inline const FloatRect getGlobalBounds() const
        {
            return this->sprite.getGlobalBounds();
        }

        inline const Vector2f getPosition() const
        {
            return this->sprite.getPosition();
        }

        //Functions
        void Movement(const float& dt);
        void Update(const float& dt);
        void Draw(RenderTarget& target);

    protected:

    private:
        Texture* texture;
        Sprite sprite;
        Vector2f currentVelocity;
        float maxVelocity;
        float acceleration;
        Vector2f direction;

        float dtMultiplier;
};
