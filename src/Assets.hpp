#pragma once

#include <SFML/Graphics.hpp>
//#include "res/textures/icons/icon.h"
//#include <SFML/Audio.hpp>
#include <memory>

class Assets{

        Assets(){}

    public :

        sf :: Image icon;
        sf :: Texture background[4];
        sf :: Texture cutscene1, cutscene2;
        sf :: Texture elementSheets[13];
        sf :: Texture elementTextures[13];

        sf :: Font font;
        sf :: Music music, Lostmusic;
        sf :: SoundBuffer click, level_failed, craft;

        static std :: shared_ptr<Assets> instance(){
            static std :: shared_ptr<Assets> inst{new Assets};
            return inst;
        }

        void loadAssets(){
            //ICON
            icon.loadFromFile("res/textures/icons/icon.png");
            //FONTS
            font.loadFromFile("res/fonts/font.ttf");
            // BCKGROUNDS
            background[0].loadFromFile("res/textures/backgrounds/game_background.png");
            background[1].loadFromFile("res/textures/backgrounds/start_background_sheet.png");
            background[2].loadFromFile("res/textures/backgrounds/lost_background_sheet.png");
            background[3].loadFromFile("res/textures/backgrounds/win_background_sheet.png");
            //SOUNDS
            click.loadFromFile("res/sounds/click.wav");
            level_failed.loadFromFile("res/sounds/levelfailed.wav");
            craft.loadFromFile("res/sounds/crafting.wav");
            //MUSIC
            music.openFromFile("res/sounds/cutscenetheme.wav");
            Lostmusic.openFromFile("res/sounds/levelfailed.wav");
            /// ANIMATED ELEMENTS
            elementSheets[0].loadFromFile("res/textures/element_sheets/water_sheet.png");
            elementSheets[1].loadFromFile("res/textures/element_sheets/fire_sheet.png");
            elementSheets[2].loadFromFile("res/textures/element_sheets/earth_sheet.png");
            elementSheets[3].loadFromFile("res/textures/element_sheets/air_sheet.png");
            elementSheets[4].loadFromFile("res/textures/element_sheets/stone_sheet.png");
            elementSheets[5].loadFromFile("res/textures/element_sheets/sand_sheet.png");
            elementSheets[6].loadFromFile("res/textures/element_sheets/glass_sheet.png");
            elementSheets[7].loadFromFile("res/textures/element_sheets/ironore_sheet.png");
            elementSheets[8].loadFromFile("res/textures/element_sheets/iron_sheet.png");
            elementSheets[9].loadFromFile("res/textures/element_sheets/keycast_sheet.png");
            elementSheets[10].loadFromFile("res/textures/element_sheets/firepit_sheet.png");
            elementSheets[11].loadFromFile("res/textures/element_sheets/wood_sheet.png");
            elementSheets[12].loadFromFile("res/textures/element_sheets/key_sheet.png");
            /// ELEMENTS
            // 0Water, 1Fire, 2Earth, 3Air, 4Stone, 5Sand, 6Glass, 7IronOre, 8Iron, 9KeyCast, 10FirePit, 11Wood
            /// CUTSCENE
            cutscene1.loadFromFile("res/textures/cutscenes/level1.png");
            cutscene2.loadFromFile("res/textures/cutscenes/level2.png");

        }

        Assets(Assets const&) = delete;
        void operator = (Assets const&) = delete;
};