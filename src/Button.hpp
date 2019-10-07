#pragma once
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <memory>

#include "State.hpp"
#include "Utilities.hpp"
#include "Assets.hpp"

#define DEFAULT_CHAR_SIZE 36
#define SELECTED_CHAR_SIZE 42

class Button{

    public :

        Button(){}

        Button(const State :: Type point, void (*command)(),
        sf :: Font& font, const std :: string text = "Button",
        const sf :: Vector2f pos = sf :: Vector2f(0, 0)) : point(point), position(pos){

            pressed = released = false;
            this -> command = command;
            message = sf :: Text(text, font, DEFAULT_CHAR_SIZE);
           //message.setFillColor(sf :: Color :: White);
            message.setOrigin(message.getGlobalBounds().width / 2, message.getGlobalBounds().height / 2);
            message.move(position);

            //click =sf :: Sound(Assets :: instance() -> click);
            //click.setVolume(50);

        }

        void update(sf :: Event e, sf :: RenderWindow& window){
            if(this -> clicked(e, window)){
            //click.play();
            command();
            pressed = released = false;
            State :: instance() -> push(point);
	        }
        }

        void show(sf :: RenderWindow& window){
            window.draw(message);
        }

        bool clicked(sf :: Event e, sf :: RenderWindow& window){
 
            if(message.getCharacterSize() != DEFAULT_CHAR_SIZE) message.setCharacterSize(DEFAULT_CHAR_SIZE);

            sf :: Vector2i mousePos = sf :: Mouse :: getPosition(window);


            if(message.getGlobalBounds().contains((sf :: Vector2f)mousePos)){

                message.setCharacterSize(SELECTED_CHAR_SIZE);

                if(e.mouseButton.button == sf :: Mouse :: Left){

                    if(e.type == sf :: Event :: MouseButtonReleased && pressed) released = true;

                    else if(e.type == sf :: Event :: MouseButtonPressed) pressed = true;

                }
            }

            message.setOrigin(message.getGlobalBounds().width / 2, message.getGlobalBounds().height / 2);
            message.setPosition(position);

            return pressed && released;

        }

        ~Button(){}

    private :

        State :: Type point; // pointState and existState
        sf :: Vector2f position;
        sf :: Text message;
        //sf :: Sound click;
        void (*command)();
        bool pressed, released;

};