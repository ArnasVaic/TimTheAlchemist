#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

class Assets{

        Assets(){}

    public :

        sf :: Texture background[2];
        sf :: Texture cutscene;
        sf :: Texture elementSheets[1];
        sf :: Texture elementTextures[13];

        sf :: Font font;
        sf :: Music music;
        sf :: SoundBuffer click, level_failed, craft;

        static std :: shared_ptr<Assets> instance(){
            static std :: shared_ptr<Assets> inst{new Assets};
            return inst;
        }

        void loadAssets(){
            //FONTS
            font.loadFromFile("res/fonts/pixelmix.TTF");
            // BCKGROUNDS
            background[0].loadFromFile("res/textures/backgrounds/game_background.png");
            background[1].loadFromFile("res/textures/backgrounds/start_background_sheet.png");
            //SOUNDS
            click.loadFromFile("res/sounds/click.wav");
            level_failed.loadFromFile("res/sounds/levelfailed.wav");
            craft.loadFromFile("res/sounds/craft.wav");
            //MUSIC
            music.openFromFile("res/sounds/cutscenetheme.wav");
            /// ANIMATED ELEMENTS
            elementSheets[0].loadFromFile("res/textures/element_icons/water.png");
            elementSheets[1].loadFromFile("res/textures/element_icons/fire.png");
            elementSheets[2].loadFromFile("res/textures/element_icons/earth.png");
            elementSheets[0].loadFromFile("res/textures/element_icons/air_sheet.png");
            /// ELEMENTS
            // 0Water, 1Fire, 2Earth, 3Air, 4Stone, 5Sand, 6Glass, 7IronOre, 8Iron, 9KeyCast, 10FirePit, 11Wood
            elementTextures[0].loadFromFile("res/textures/element_icons/water.png");
            elementTextures[1].loadFromFile("res/textures/element_icons/fire.png");
            elementTextures[2].loadFromFile("res/textures/element_icons/earth.png");
            elementTextures[3].loadFromFile("res/textures/element_icons/air.png");
            elementTextures[4].loadFromFile("res/textures/element_icons/stone.png");
            elementTextures[5].loadFromFile("res/textures/element_icons/sand.png");
            elementTextures[6].loadFromFile("res/textures/element_icons/glass.png");
            elementTextures[7].loadFromFile("res/textures/element_icons/ironore.png");
            elementTextures[8].loadFromFile("res/textures/element_icons/iron.png");
            elementTextures[9].loadFromFile("res/textures/element_icons/keycast.png");
            elementTextures[10].loadFromFile("res/textures/element_icons/firepit.png");
            elementTextures[11].loadFromFile("res/textures/element_icons/wood.png");
            elementTextures[12].loadFromFile("res/textures/element_icons/key.png");
            /// CUTSCENE
            cutscene.loadFromFile("res/textures/cutscenes/level1.png");

        }

        Assets(Assets const&) = delete;
        void operator = (Assets const&) = delete;

};

#endif