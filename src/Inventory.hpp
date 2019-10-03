#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <string>
#include <vector>
#include <memory>
#include "Element.hpp"

class Inventory{

    public :
        Inventory(){
            for(uint32_t i = 0 ; i < 5 ; i ++){
                auto t = static_cast<Element :: Type>(i);
                items.push_back(Element(t, i));
            }
        }

        void update(sf :: RenderWindow& window, sf :: Event e){
            sf :: Vector2f m_pos = (sf :: Vector2f) sf :: Mouse :: getPosition(window);
            uint32_t index = 0;
            for(auto& i : items){
                i.update(window, e, m_pos, index++);
            }
        }

        void show(sf :: RenderWindow& window){
            for(auto& i : items){
                i.show(window);
            }
        }

    private :
        std :: vector<Element> items;
        //std :: shared_ptr<Element> l;
};

#endif