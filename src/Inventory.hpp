#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <string>
#include <vector>
#include <memory>

#include "Utilities.hpp"
#include "Element.hpp"
#include "State.hpp"

class Inventory{

    public :
        Inventory(std :: vector<Element>& items, Element :: Type target) : target(target), completed(false), decraftIndex(INVENTORY_SIZE + 3) {
            // starting items :
            this -> items = items;  
            for(uint32_t y = 0 ; y < INVENTORY_SIZE_Y ; y ++){
                for(uint32_t x = 0 ; x < INVENTORY_SIZE_X ; x ++){
                    rects[x + y * INVENTORY_SIZE_X] = sf :: FloatRect(OFFSETX + x * (SOCKET_SIZE + SPACING),
                             OFFSETY + y * (SOCKET_SIZE + SPACING), SOCKET_SIZE, SOCKET_SIZE);
                
                    print(" LEFT = " << rects[x + y * INVENTORY_SIZE_X].left << 
                          " TOP = " << rects[x + y * INVENTORY_SIZE_X].top);
                          /*"  WIDTH = " << rects[x + y * INVENTORY_SIZE_X].width <<
                          " HEIGHT = " << rects[x + y * INVENTORY_SIZE_X].height); */
                
                }
            }
            
            rects[INVENTORY_SIZE] =     sf :: FloatRect(136 * SCALE, 32 * SCALE, SOCKET_SIZE, SOCKET_SIZE);
            rects[INVENTORY_SIZE + 2] = sf :: FloatRect(160 * SCALE, 52 * SCALE, SOCKET_SIZE, SOCKET_SIZE);
            rects[INVENTORY_SIZE + 1] = sf :: FloatRect(136 * SCALE, 72 * SCALE, SOCKET_SIZE, SOCKET_SIZE);

            fade1 = sf :: RectangleShape(sf :: Vector2f(wSize)); 
            fade2 = sf :: RectangleShape(sf :: Vector2f(wSize)); 
            fade1.setFillColor(sf :: Color(0, 0, 0, 0));
            fade2.setFillColor(sf :: Color(0, 0, 0, 0));

            score = 0;
            auto s = "Score : " + std :: to_string(score);
            scoreboard = Textbox(s, 24);
            scoreboard.setPosition(sf :: Vector2f(64 * SCALE, 8 * SCALE));

        }

        void update(sf :: RenderWindow& window, sf :: Event e){
            sf :: Vector2f m_pos = (sf :: Vector2f) sf :: Mouse :: getPosition(window);
            uint32_t index = 0;

            if(!isTargetCrafted()){
                for(auto& i : items){
                    i.update(e, m_pos, &rects[0]);
                }
            }
            else {
                sf :: Vector2f target(wSize.x/2, wSize.y/2);
                sf :: Vector2f pos(target.x - items.back().getPosition().x / 1000, target.y - items.back().getPosition().y / 1000);
                if(alpha_value1 < 255) alpha_value1 += 1;
                fade1.setFillColor(sf :: Color(0, 0, 0, alpha_value1));
                items.back().setPosition(pos);
                if(items.back().getScale().x < 2 && items.back().getScale().y < 2)items.back().setScale(sf :: Vector2f(items.back().getScale().x * 1.05 , items.back().getScale().y * 1.05));
                if(alpha_value1 == 255){
                    if(alpha_value2 < 255) alpha_value2 += 1;
                    fade2.setFillColor(sf :: Color(0, 0, 0, alpha_value2));
                }
                if(alpha_value2 == 255) completed = true;
                //print(" A1 = " << alpha_value1 << " A2 = " << alpha_value2);
            }
            this -> handleCrafting();
            this -> handleDecrating(e, m_pos);
            auto s = "Score : " + std :: to_string(score);
            scoreboard.setText(s);
            if(score < 0){
                State :: instance() -> push(State :: Type :: Lost);
            }
        }

        void show(sf :: RenderWindow& window){
            window.draw(fade1);

            for(auto& i : items){
                i.show(window);
            }

            scoreboard.show(window);
            
            window.draw(fade2);
        }

        bool isLevelCompleted(){
            return completed;
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
            // when index is INVENTORY_SIZE + 3 its just return because no items are in queue to craft
            if(selected[0] == INVENTORY_SIZE + 3 || selected[1] == INVENTORY_SIZE + 3) return;
            if(this -> craft(&selected[0], Element :: Type :: Earth, Element :: Type :: Fire, Element :: Type :: Stone)){ score += 10; return; }
            if(this -> craft(&selected[0], Element :: Type :: Stone, Element :: Type :: Stone, Element :: Type :: IronOre)){ score += 10; return; }
            if(this -> craft(&selected[0], Element :: Type :: Earth, Element :: Type :: Water, Element :: Type :: Wood)){ score += 10; return; }
            if(this -> craft(&selected[0], Element :: Type :: Wood, Element :: Type :: Fire, Element :: Type :: FirePit)){ score += 10; return; }
            if(this -> craft(&selected[0], Element :: Type :: IronOre, Element :: Type :: FirePit, Element :: Type :: Iron)){ score += 10; return; }
            if(this -> craft(&selected[0], Element :: Type :: Stone, Element :: Type :: Air, Element :: Type :: KeyCast)){  score += 10;return; }
            if(this -> craft(&selected[0], Element :: Type :: Iron, Element :: Type :: KeyCast, Element :: Type :: Key)){  score += 10;return; }
            else {
                items[selected[0]].moveToClosestSocket(items);
                items[selected[1]].moveToClosestSocket(items);
                selected[0] = selected[1] = INVENTORY_SIZE + 3;
                score -= 10;
                print(score);
                std :: string t = "" + score;
                scoreboard.setText(t);
            }
        }

        void handleDecrating(sf :: Event e, sf :: Vector2f m_pos){
            bool bruh = false;
            int vecIndex = -1;
            if(clickedRight(e, m_pos)){
                pressed = released = false;
                for(uint32_t i = 0 ; i < INVENTORY_SIZE ; i ++){
                    if(rects[i].contains(m_pos)){
                        vecIndex = i;
                        bruh = true;
                        break;
                    }
                }
                if(vecIndex == -1) return;
                sf :: FloatRect& sRect = rects[vecIndex];
                sf :: Vector2f rect_center(sRect.left + sRect.width/2, sRect.top + sRect.height/2);
                print("Selected Rect x = " << rect_center.x << " y = " << rect_center.y);

                for(uint32_t i = 0 ; i < INVENTORY_SIZE ; i ++){
                    print(" Items : " << items[i].getTypeAsString());
                    if(items[i].getPosition() == rect_center){
                        decraftIndex = i;
                        print("Item pos : x = " << items[i].getPosition().x << " y = " << items[i].getPosition().y << " Item type : " << items[i].getTypeAsString());
                        bruh = true;
                        break;
                    }
                }
            }
            if(decraftIndex == INVENTORY_SIZE + 3) return;

            if(bruh){
                if(this -> isTouchingAnySocket(m_pos)){
                    uint32_t indx = decraftIndex;
                    if(this -> decraft(indx,Element :: Type :: Stone, Element :: Type :: Earth, Element :: Type :: Fire)){
                        score-=10; return;
                    }
                    if(this -> decraft(indx,Element :: Type :: IronOre, Element :: Type :: Stone, Element :: Type :: Stone)){ 
                        score-=10; return;
                    }
                    if(this -> decraft(indx,Element :: Type :: Wood, Element :: Type :: Earth, Element :: Type :: Water)){ 
                        score-=10; return;
                    }
                    if(this -> decraft(indx,Element :: Type :: FirePit, Element :: Type :: Wood, Element :: Type :: Fire)){ 
                        score-=10; return;
                    }
                    if(this -> decraft(indx, Element :: Type :: Iron, Element :: Type :: IronOre, Element :: Type :: FirePit)){ 
                        score-=10; return;
                    }
                    if(this -> decraft(indx, Element :: Type :: KeyCast, Element :: Type :: Stone, Element :: Type :: Air)){ 
                        score-=10; return;
                    }
                }
            }
        }

        bool decraft(uint32_t index, Element :: Type t1, Element :: Type t2, Element :: Type t3){ 
            bool result = false;
            print("Deleted item index : " << index << " Type : " << items[index].getTypeAsString());
            if(items[index].getType() == t1){
                result = true;
                //print("bruh2");
            }
            if(result){
                items.erase(items.begin() + index);
                items.push_back(Element(t2, 0));
                items.back().moveToClosestSocket(items);
                items.push_back(Element(t3, 0));
                items.back().moveToClosestSocket(items);
            }
            return result;
        }

        bool isTouchingAnySocket(sf :: Vector2f m_pos){
            bool done = false;
            for(uint32_t i = 0 ; i < INVENTORY_SIZE; i++){
                if(rects[i].contains(m_pos)){
                    //decraftIndex = i;
                    done = true;
                    break;
                }
            }
            return done;
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
                uint32_t temp;
                if(*(selected + 1) == items.size() - 1){
                    /* temp = items[*selected].getIndex();
                    items[*selected].setIndex(  items[items.size() - 2].getIndex()  );
                    items[items.size() - 2].setIndex(temp); */

                    std :: swap(items[*selected], items[items.size() - 2]);            
                }
                else if(*selected == items.size() - 1){
                    /* temp = items[*(selected + 1)].getIndex();
                    items[*(selected + 1)].setIndex(items[items.size() - 2].getIndex());
                    items[items.size() - 2].setIndex(temp); */

                    std :: swap(items[*(selected + 1)], items[items.size() - 2]);            
                }
                else{
                    uint32_t temp2;

                    /* temp = (items[*selected].getIndex());;
                    items[*selected].setIndex(items.back().getIndex());
                    items.back().setIndex(temp); */

                    /* temp2 = items[*(selected + 1)].getIndex();
                    items[*(selected + 1)].setIndex(items[items.size() - 2].getIndex());
                    items[items.size() - 2].setIndex(temp); */

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

        bool isTargetCrafted(){
            return ( items.size() == 1 && items.back().getType() == target)? true : false;
        }

    private :
        uint32_t decraftIndex;
        int score;
        bool completed, lost;
        Element :: Type target;
        std :: vector<Element> items;
        sf :: FloatRect rects[INVENTORY_SIZE + 3];
        float alpha_value1 = 0, alpha_value2 = 0;
        sf :: RectangleShape fade1, fade2;
        Textbox scoreboard;
};

#endif