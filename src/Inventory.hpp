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
            // starting items :
            items.push_back(Element(Element :: Type :: Earth, 0));
            items.push_back(Element(Element :: Type :: Earth, 1));
            items.push_back(Element(Element :: Type :: Earth, 2));
            items.push_back(Element(Element :: Type :: Earth, 3));

            items.push_back(Element(Element :: Type :: Fire, 4));
            items.push_back(Element(Element :: Type :: Fire, 5));
            items.push_back(Element(Element :: Type :: Fire, 6));
            items.push_back(Element(Element :: Type :: Fire, 7));

            items.push_back(Element(Element :: Type :: Air, 8));
            items.push_back(Element(Element :: Type :: Water, 9)); 
            items.push_back(Element(Element :: Type :: Glass, 10)); 

            for(uint32_t y = 0 ; y < INVENTORY_SIZE_Y ; y ++){
                for(uint32_t x = 0 ; x < INVENTORY_SIZE_X ; x ++){
                    rects[x + y * INVENTORY_SIZE_X] = sf :: FloatRect(OFFSETX + x * (SOCKET_SIZE + SPACING),
                             OFFSETY + y * (SOCKET_SIZE + SPACING), SOCKET_SIZE, SOCKET_SIZE);
                    /* print("LEFT = " << rects[x + y * INVENTORY_SIZE_X].left << 
                          "TOP = " << rects[x + y * INVENTORY_SIZE_X].top <<
                          "WIDTH = " << rects[x + y * INVENTORY_SIZE_X].width <<
                          "HEIGHT = " << rects[x + y * INVENTORY_SIZE_X].height); */
                }
            }
            
            rects[INVENTORY_SIZE] =     sf :: FloatRect(136 * SCALE, 32 * SCALE, SOCKET_SIZE, SOCKET_SIZE);
            rects[INVENTORY_SIZE + 2] = sf :: FloatRect(160 * SCALE, 52 * SCALE, SOCKET_SIZE, SOCKET_SIZE);
            rects[INVENTORY_SIZE + 1] = sf :: FloatRect(136 * SCALE, 72 * SCALE, SOCKET_SIZE, SOCKET_SIZE);
        }

        void update(sf :: RenderWindow& window, sf :: Event e){
            sf :: Vector2f m_pos = (sf :: Vector2f) sf :: Mouse :: getPosition(window);
            uint32_t index = 0;

            for(auto& i : items){
                i.update(window, e, m_pos, &rects[0]);
            }

            this -> handleCrafting();
        }

        void show(sf :: RenderWindow& window){

            for(auto& i : items){
                i.show(window);
            }
        }

    private :

        void handleCrafting(){
            // find the index of elements that have been selected to craft
            // by default the indexes of selected items are INVENTORY_SIZE + 3
            //if no indexes have been found this functions returns without finishing 
            uint32_t selected[2];

            selected[0] = selected[1] = INVENTORY_SIZE + 3;

            for(uint32_t i = 0 ; i < items.size() ; i ++){

                if(items[i].getIndex() == INVENTORY_SIZE) selected[0] = i;
                if(items[i].getIndex() == INVENTORY_SIZE + 1) selected[1] = i;
            } 
            
            if(selected[0] == INVENTORY_SIZE + 3 || selected[1] == INVENTORY_SIZE + 3) return;
            if(this -> craft(&selected[0], Element :: Type :: Earth, Element :: Type :: Fire, Element :: Type :: Stone)){ return; }
            if(this -> craft(&selected[0], Element :: Type :: Stone, Element :: Type :: Stone, Element :: Type :: IronOre)){ return; }
            if(this -> craft(&selected[0], Element :: Type :: Earth, Element :: Type :: Water, Element :: Type :: Wood)){ return; }
            if(this -> craft(&selected[0], Element :: Type :: Wood, Element :: Type :: Fire, Element :: Type :: FirePit)){ return; }

            if(this -> craft(&selected[0], Element :: Type :: IronOre, Element :: Type :: FirePit, Element :: Type :: Iron)){ return; }
            if(this -> craft(&selected[0], Element :: Type :: Stone, Element :: Type :: Air, Element :: Type :: KeyCast)){ return; }
            if(this -> craft(&selected[0], Element :: Type :: Iron, Element :: Type :: KeyCast, Element :: Type :: Key)){ return; }
        }

        bool craft(uint32_t* selected, Element :: Type t1, Element :: Type t2, Element :: Type t3){ 
            // selected is the pointer to the array which holds the indexes of Elements who have been selected to craft
            // this function returns true if your provided element types are the types of selected elements
            //print("Selected : index 1 :" << *(selected + 1) << " Index 2 : " << *(selected));
            bool result = false;
            if(items[*selected].getType() == t1){
                if(items[*(selected + 1)].getType() == t2){
                    result = true;
                }
            }
            if(!result){
                if(items[*(selected + 1)].getType() == t1){
                    if(items[*selected].getType() == t2){
                        result = true;
                    }
                }
            }
            
            if(result){
                // finds the two elements that need to crafted, places them at the back and deletes them.
                // then pushes back the new element

                if(*(selected + 1) == items.size() - 1){
                    std :: swap(items[*selected], items[items.size() - 2]);            
                }
                else if(*selected == items.size() - 1){
                    std :: swap(items[*(selected + 1)], items[items.size() - 2]);            
                }
                else{
                    std :: swap(items[*selected], items.back());            
                    std :: swap(items[*(selected + 1)], items[items.size() - 2]);
                }

                items.pop_back();
                items.pop_back();

                items.push_back(Element(t3, INVENTORY_SIZE + 2));
            }

            return result;
        }

        bool check(uint32_t* selected){
            return !(*selected == INVENTORY_SIZE + 3 || *(selected + 1) == INVENTORY_SIZE + 3);
        }

    private :
        std :: vector<Element> items;
        sf :: FloatRect rects[INVENTORY_SIZE + 3];
};

#endif