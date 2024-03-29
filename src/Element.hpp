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
            click = sf :: Sound(Assets :: instance() -> click);
            click.setVolume(50);
        }

        void update(sf :: Event e, sf :: Vector2f m_pos, sf :: FloatRect* rects, std :: vector<Element>& items){
            /// update the text box
            showTextBox = sprite.getGlobalBounds().contains(m_pos) ? true :false;
            tb.setPosition(sprite.getPosition());
            // update animation
                animation.play(0, 0.1f, sprite);
            /// update the element

            bool clicked = false;

            if(this -> clicked(e, m_pos)){
                click.play();
                clicked = true;
                pressed = released = false;
            }

            if(index == INVENTORY_SIZE + 2){
                if(clicked){
                    this -> moveToClosestSocket(items);
                    return;
                }
            }

            if(selected && clicked){
                if(this -> isTouchingSocket(m_pos, rects)){
                    //index -1;
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

        bool clicked(sf :: Event e, sf :: Vector2f m_pos){
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
            index = index;
            float xi = index % INVENTORY_SIZE_X;
            float yi = (index - xi ) / INVENTORY_SIZE_X;
            float x = SOCKET_SIZE / 2 + OFFSETX + (SPACING + SOCKET_SIZE) * xi;
            float y = SOCKET_SIZE / 2 + OFFSETY + (SPACING + SOCKET_SIZE) * yi;
            sprite.setPosition(x, y);
        }

        void moveToSocket(sf :: FloatRect *rects, sf :: Vector2f m_pos){
            for(uint16_t i = 0 ; i < INVENTORY_SIZE + 2 ; i ++){
                sf :: FloatRect& rect = *(rects + i);
                if(rect.contains(m_pos)){
                    index = i;
                    sprite.setPosition(rect.left + rect.width/ 2, rect.top + rect.height/ 2);
                    return;
                }
            }
        }

         void moveToClosestSocket(const std :: vector<Element>& items){
            // Alternative method : check for the smallest, free index, where 0 < index < INVENTORY_SIZE and move the sprite there
            uint32_t indx; // I cant name it index because class Element already has a var called index
            for(uint32_t i = 0 ; i < INVENTORY_SIZE ; i ++){
                bool nextIndex = false;
                for(auto& j : items){
                    if(j.getIndex() == i){
                        nextIndex = true;
                        break;
                    }
                }
                if(nextIndex) continue;
                else{
                    index = i;
                    this -> moveToIndex(i);
                }
            }
        }

        bool isTouchingSocket(sf :: Vector2f m_pos, sf :: FloatRect* rects){
            bool done = false;
            for(uint32_t i = 0 ; i < INVENTORY_SIZE + 2 ; i++){
                sf :: FloatRect& rect = *(rects + i);
                if(rect.contains(m_pos)){
                    index = i;
                    done = true;
                    break;
                }
            }
            return done;
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

        sf :: Vector2f getPosition() const{
            return sprite.getPosition();
        }

        void setPosition(sf :: Vector2f pos){
            sprite.setPosition(pos);
        }

        sf :: Vector2f getScale() const{
            return sprite.getScale();
        }

        void setScale(sf :: Vector2f scale){
            sprite.setScale(scale);
        }

        int getIndex() const {
            return index;
        }

        void setIndex(uint32_t ix){
            index = ix;
        }

        Type getType() const{
            return t;
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