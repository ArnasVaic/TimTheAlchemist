#pragma once

#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <memory>

class Assets{

        Assets(){}

    public :

        sf :: Texture background, elementTextures[4];
        sf :: Font font;
        //sf :: SoundBuffer buttonClick;

        static std :: shared_ptr<Assets> instance(){
            static std :: shared_ptr<Assets> inst{new Assets};
            return inst;
        }

        void loadAssets(){
            font.loadFromFile("res/fonts/Font.TTF");
            background.loadFromFile("res/background.png");
            //buttonClick.loadFromFile("res/sounds/buttonClick.wav");
            elementTextures[0].loadFromFile("res/water.png");
            elementTextures[1].loadFromFile("res/fire.png");
            elementTextures[2].loadFromFile("res/earth.png");
            elementTextures[3].loadFromFile("res/air.png");
        }

        Assets(Assets const&) = delete;
        void operator = (Assets const&) = delete;

};