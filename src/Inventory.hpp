#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <string>
#include <vector>
#include <memory>
#include "Utilities.hpp"
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
                if(isNull(i)) continue;
                i.update(window, e, m_pos, &rects[0]);
            }

            this -> craft();
            //print("Items : " << this -> occupied());
        }

        uint32_t occupied(){ 
            // returns the number of non Null  elements,
            // in other words - the number of occupied inventory spaces
            uint32_t count = 0;
            for(auto& i : items){
                if(isNull(i)) continue;
                count ++;
            } return count;
        }

        void show(sf :: RenderWindow& window){

            for(auto& i : items){
                if(isNull(i)) continue;
                i.show(window);
            }
        }

        bool isNull(Element e){
            return (e.getType() == Element :: Type :: Null);
        }

    private :

        void craft(){
            // find the index of elements that have been selected to craft
            // by default the indexes of selected items are INVENTORY_SIZE + 3
            //if no indexes have been found this functions returns without finishing 
            uint32_t selected[2];
            selected[0] = selected[1] = INVENTORY_SIZE + 3;
            for(uint32_t i = 0 ; i < INVENTORY_SIZE + 2 ; i ++){
                if(items[i].getIndex() == INVENTORY_SIZE) selected[0] = i;
                if(items[i].getIndex() == INVENTORY_SIZE + 1) selected[1] = i;
            } if( selected[0] == selected[1] == INVENTORY_SIZE + 3) return;
            
            // look up what are the types of selected elements and craft a new one
            if(this -> checkTypes(&selected[0], Element :: Type ::Fire, Element :: Type :: Water)){
                items[selected[0]].setType(Element :: Type :: Null);
                items[selected[1]].setType(Element :: Type :: Null);
                items.push_back(Element(Element :: Type :: Stone, INVENTORY_SIZE + 2));
            }
        }

        bool checkTypes(uint32_t* selected, Element :: Type t1, Element :: Type t2){ 
            // selected is the pointer to the array which holds the indexes of Elements who have been selected to craft
            // this function returns true if your provided element types are the types of selected elements
            print("Selected : index 1 :" << *(selected + 1) << " Index 2 : " << *(selected));
            return  (items[*(selected)].getType() == t1 && items[*(selected + 1)].getType() == t2)
             || (items[*(selected + 1)].getType() == t1 && items[*(selected)].getType() == t2);
        }

    private :
        std :: vector<Element> items;
        sf :: FloatRect rects[INVENTORY_SIZE + 3];
};

#endif