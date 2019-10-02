#pragma once

#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <memory>

class Assets{

        Assets(){}

    public :

        sf :: Font font;
        //sf :: SoundBuffer buttonClick;

        static std :: shared_ptr<Assets> instance(){
            static std :: shared_ptr<Assets> inst{new Assets};
            return inst;
        }

        void loadAssets(){
            font.loadFromFile("res/fonts/Font.TTF");
            //buttonClick.loadFromFile("res/sounds/buttonClick.wav");
        }

        Assets(Assets const&) = delete;
        void operator = (Assets const&) = delete;

};