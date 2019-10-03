#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <SFML/Graphics.hpp>

#include "Utilities.hpp"
#include "Assets.hpp"

class Element{

    public :

        enum Type{
            Water, Fire, Earth, Air, Stone
        };

        Element(){ }

        Element(Type t, uint32_t index) : t(t) { 
            sprite = sf :: Sprite(Assets :: instance() -> elementTextures[static_cast<unsigned int>(t)]);
            sprite.setOrigin(DEFAULT_TEXTURE_SIZE / 2 , DEFAULT_TEXTURE_SIZE / 2);
            this -> moveToIndex(index);
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
                this -> moveToIndex(index);
                return;
            } 

            if(clicked) selected = true;

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

        void moveToIndex(uint32_t index){
            sprite.setPosition(48 + 16 + 112 * (index % 4), 48 + 16 + 112 * (int(index / 5)));
        }

    private :
        sf :: Sprite sprite;
        bool selected, pressed, released;
        Type t;
};

#endif