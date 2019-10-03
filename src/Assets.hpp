#pragma once

#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <memory>

class Assets{

        Assets(){}

    public :

        sf :: Texture background, elementTextures[5];
        sf :: Font font;
        //sf :: SoundBuffer buttonClick;

        static std :: shared_ptr<Assets> instance(){
            static std :: shared_ptr<Assets> inst{new Assets};
            return inst;
        }

        void loadAssets(){
            font.loadFromFile("res/fonts/Font.TTF");
            background.loadFromFile("res/textures/background.png");
            //buttonClick.loadFromFile("res/sounds/buttonClick.wav");
            elementTextures[0].loadFromFile("res/textures/element_icons/water.png");
            elementTextures[1].loadFromFile("res/textures/element_icons/fire.png");
            elementTextures[2].loadFromFile("res/textures/element_icons/earth.png");
            elementTextures[3].loadFromFile("res/textures/element_icons/air.png");
            elementTextures[4].loadFromFile("res/textures/element_icons/stone.png");
        }

        Assets(Assets const&) = delete;
        void operator = (Assets const&) = delete;

};