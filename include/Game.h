#pragma once

#include "Player.h"

class Game
{
    public:
        Game(RenderWindow* window);
        virtual ~Game();

        void InitUI();
        void UpdateUI();
        void Clear();
        void Update();
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
        Texture playerTexture;
        Texture bulletTexture;
        Texture gunTexture01;

};
