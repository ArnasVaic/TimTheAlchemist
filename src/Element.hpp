#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <SFML/Graphics.hpp>

#include "Utilities.hpp"
#include "Assets.hpp"

class Element{

    public :

        enum Type{
            Water, Fire, Earth, Air
        };

        Element(){ }

        Element(Type t) : t(t) { 
            sprite = sf :: Sprite(Assets :: instance() -> elementTextures[static_cast<unsigned int>(t)]);
            sprite.setOrigin(DEFAULT_TEXTURE_SIZE / 2 , DEFAULT_TEXTURE_SIZE / 2);
            pressed = released = selected = false;
        }

        void update(sf :: RenderWindow& window, sf :: Event e, sf :: Vector2f m_pos, uint32_t index){
            bool clicked = false;
            if(this -> clicked(window, e, m_pos)){
                clicked = true;
                pressed = released = false;
            }

            if(selected && clicked){
                selected = false;
                sprite.setPosition(48 + 16 + 128 * ((index + 1 ) % 4), 48 +  240 + 128 * ((index + 1 ) % 4));
                return;
            } 

            if(clicked) selected = true;
            if(clicked) print("Click");

            if(selected){
                sprite.setPosition(m_pos);
            }
        }

        void show(sf :: RenderWindow& window){
            window.draw(sprite);
        }

        bool clicked(sf :: RenderWindow& window, sf :: Event e, sf :: Vector2f m_pos){
            if(sprite.getGlobalBounds().contains(m_pos)){
                if(e.mouseButton.button == sf :: Mouse :: Left){
                    if(e.type == sf :: Event :: MouseButtonReleased && pressed) released = true;
                    else if(e.type == sf :: Event :: MouseButtonPressed) pressed = true;
                }
            }
            return pressed && released;
        }

    private :
        sf :: Sprite sprite;
        bool selected, pressed, released;
        Type t;
};

#endif