#pragma once

#include "Player.h"
#include "Enemy.h"

class Game
{
    public:
        Game(RenderWindow* window);
        virtual ~Game();

        void InitUI();
        void UpdateUI();
        void Clear();
        void Update(const float& dt);
        void Draw();
        void DrawUI();

    //Accessors
    inline RenderWindow& getWindow() { return *this->window; }

    protected:

    private:
        RenderWindow* window;

        Font font;
        std::vector<Text> followPlayerTexts;
        std::vector<Text> staticPlayerTexts;

        std::vector<Player> players;
        std::vector<Texture> textures;
        std::vector<Enemy> enemies;

        float enemySpawnTimer;
        float enemySpawnTimerMax;

        float dtMultiplier = 60.f;

};
