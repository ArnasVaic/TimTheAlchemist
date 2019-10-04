#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <SFML/Graphics.hpp>

#include "Utilities.hpp"
#include "Assets.hpp"

class Element{

    public :

        enum Type{
            Water, Fire, Earth, Air, Stone, Null
        };

        Element(){ }

        Element(Type t, uint32_t index) : t(t), index(index) { 
            sprite = sf :: Sprite(Assets :: instance() -> elementTextures[static_cast<unsigned int>(t)]);
            sprite.setOrigin(DEFAULT_TEXTURE_SIZE / 2 , DEFAULT_TEXTURE_SIZE / 2);
            this -> moveToIndex(index);
            
            //ori = index;
            pressed = released = selected = false;
        }

        void update(sf :: RenderWindow& window, sf :: Event e, sf :: Vector2f m_pos, sf :: FloatRect* rects){
            bool clicked = false;
            if(this -> clicked(window, e, m_pos)){
                clicked = true;
                pressed = released = false;
            }

            if(selected && clicked){
                if(this -> isTouchingSocket(m_pos, rects)){
                    index -1;
                    selected = false;
                    this -> moveToSocket(rects, m_pos);  
                } 
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
            if(e.mouseButton.button == sf :: Mouse :: Left){
                if(sprite.getGlobalBounds().contains(m_pos)){
                    if(e.type == sf :: Event :: MouseButtonPressed) pressed = true;
                    else  if(e.type == sf :: Event :: MouseButtonReleased && pressed) released = true;
                }
            }
            return pressed && released;
        }

        void moveToIndex(uint32_t index){
            if(index == INVENTORY_SIZE + 2){
                sprite.setPosition(576 + SOCKET_SIZE / 2, 192 + SOCKET_SIZE / 2);
                index %= INVENTORY_SIZE;
                return;
            }
            float xi = index % INVENTORY_SIZE_X;
            float yi = (index - xi ) / INVENTORY_SIZE_X;
            float x = SOCKET_SIZE / 2 + OFFSETX + (SPACING + SOCKET_SIZE) * xi;
            float y = SOCKET_SIZE / 2 + OFFSETY + (SPACING + SOCKET_SIZE) * yi;
            sprite.setPosition(x, y);
        }

        void moveToSocket(sf :: FloatRect *rects, sf :: Vector2f m_pos){
            bool done = false;
            for(uint16_t i = 0 ; i < INVENTORY_SIZE + 2 ; i ++){
                sf :: FloatRect& rect = *(rects + i);
                if(rect.contains(m_pos)){
                    index = i;
                    sprite.setPosition(rect.left + rect.width/ 2, rect.top + rect.height/ 2);
                    done = true;
                    return;
                }
            }
        }

        sf :: Vector2f getPosition(){
            return sprite.getPosition();
        }

        bool isTouchingSocket(sf :: Vector2f m_pos, sf :: FloatRect* rects){
            bool done = false;
            for(uint32_t i = 0 ; i < INVENTORY_SIZE + 2 ; i++){
                sf :: FloatRect& rect = *(rects + i);
                if(rect.contains(m_pos)){
                    done = true;
                    break;
                }
            }
            return done;
        }

        int getIndex(){
            return index;
        }

        Type getType(){
            return t;
        }

        void setType(Type t){
            this -> t = t;
        }

        /* sf :: Vector2f setPosition(sf :: Vector2f pos){
            sprite.setPosition(pos);
        }    */

    private :
        sf :: Sprite sprite;
        int index; // index of the rect it is in
        bool selected, pressed, released;
        Type t;
};

#endif