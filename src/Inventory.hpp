#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <string>
#include <vector>
#include <memory>
#include "Element.hpp"

class Inventory{

    public :
        Inventory(){
            items.reserve(INVENTORY_SIZE);
            for(uint32_t i = 0 ; i < 2 ; i ++){
                auto t = static_cast<Element :: Type>(i);
                items.push_back(Element(t, i));
            }

            for(uint32_t y = 0 ; y < INVENTORY_SIZE_Y ; y ++){
                for(uint32_t x = 0 ; x < INVENTORY_SIZE_X ; x ++){
                    rects[x + y * INVENTORY_SIZE_X] = sf :: FloatRect(OFFSETX + x * (SOCKET_SIZE + SPACING),
                             OFFSETY + y * (SOCKET_SIZE + SPACING), SOCKET_SIZE, SOCKET_SIZE);
                }
            }
            
            rects[INVENTORY_SIZE] =     sf :: FloatRect(576, 88, SOCKET_SIZE, SOCKET_SIZE);
            rects[INVENTORY_SIZE + 2] = sf :: FloatRect(576, 192, SOCKET_SIZE, SOCKET_SIZE);
            rects[INVENTORY_SIZE + 1] = sf :: FloatRect(576, 291, SOCKET_SIZE, SOCKET_SIZE);
        }

        void update(sf :: RenderWindow& window, sf :: Event e){
            sf :: Vector2f m_pos = (sf :: Vector2f) sf :: Mouse :: getPosition(window);
            uint32_t index = 0;
            for(auto& i : items){
                i.update(window, e, m_pos, &rects[0]);
            }

        }

        void show(sf :: RenderWindow& window){
            for(auto& i : items){
                i.show(window);
            }
        }

        void erase(uint32_t index){
            items.erase(items.begin() + index - 1);
        }
    private :

        void craft(){
            
        }

    private :
        std :: vector<Element> items;
        sf :: FloatRect rects[INVENTORY_SIZE + 3];
};

#endif