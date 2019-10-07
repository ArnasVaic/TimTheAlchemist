#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "Utilities.hpp"
#include "Textbox.hpp"
#include "Assets.hpp"

class Element{

    public :

        enum Type{
            Water, Fire, Earth, Air, Stone, Sand, Glass, IronOre, Iron, KeyCast, FirePit, Wood, Key
        };

        Element(){ }

        Element(Type t, uint32_t index) : t(t), index(index), showTextBox(false) { 
            animation = Animation(Assets :: instance() -> elementSheets[static_cast<unsigned int>(t)], sprite, sf :: Vector2u(8, 1), sf :: Vector2f(SCALE, SCALE));
            sprite.setOrigin(DEFAULT_TEXTURE_SIZE / 2 , DEFAULT_TEXTURE_SIZE / 2);
            this -> moveToIndex(index);

            pressed = released = selected = false;
            tb = Textbox(this -> getTypeAsString());
            click =sf :: Sound(Assets :: instance() -> click);
            click.setVolume(50);
        }

        void update(sf :: RenderWindow& window, sf :: Event e, sf :: Vector2f m_pos, sf :: FloatRect* rects){
            /// update the text box
            showTextBox = sprite.getGlobalBounds().contains(m_pos) ? true :false;
            tb.setPosition(sprite.getPosition());
            // update animation
                animation.play(0, 0.1f, sprite);
            /// update the element

            bool clicked = false;
            if(this -> clicked(window, e, m_pos)){
                click.play();
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
            if(showTextBox) tb.show(window);
        }

        bool clicked(sf :: RenderWindow& window, sf :: Event e, sf :: Vector2f m_pos){
            if(e.mouseButton.button == sf :: Mouse :: Left){
                if(sprite.getGlobalBounds().contains(m_pos)){
                    if(!selected) showTextBox = true;
                    if(e.type == sf :: Event :: MouseButtonPressed) pressed = true;
                    else  if(e.type == sf :: Event :: MouseButtonReleased && pressed) released = true;
                }
            }
            return pressed && released;
        }

        void moveToIndex(uint32_t index){
            if(index == INVENTORY_SIZE + 2){
                sprite.setPosition(160 * SCALE + SOCKET_SIZE / 2, 52 * SCALE + SOCKET_SIZE / 2);
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

        std :: string getTypeAsString(){
            // Water, Fire, Earth, Air, Stone, Sand,
            // Glass, IronOre, Iron, KeyCast, FirePit, Wood,
            // Key
            switch(t){
                case Fire :
                    return "Fire";
                    break;
                case Water :
                    return "Water";
                    break;
                case Earth :
                    return "Earth";
                    break;
                case Air :
                    return "Air";
                    break;
                case Stone :
                    return "Stone";
                    break;
                case  Sand :
                    return " Sand";
                    break;
                case Glass :
                    return "Glass";
                    break;
                case IronOre :
                    return "Iron Ore";
                    break;
                case Iron :
                    return "Iron";
                    break;
                case KeyCast :
                    return "Key Cast";
                    break;
                case FirePit :
                    return "Fire Pit";
                    break;
                case Wood :
                    return "Wood";
                    break;
                case Key :
                    return "Key";
                    break;
                default :
                    return "NULL";
                    break;
            }
        }

        void setType(Type t){
            this -> t = t;
        }

    private :

        sf :: Sound click;
        sf :: Sprite sprite;
        Animation animation;
        int index; // index of the rect it is in
        Textbox tb;
        bool selected, pressed, released, showTextBox;
        Type t;
};

#endif