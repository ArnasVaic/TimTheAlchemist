#include <SFML/Graphics.hpp>

#include "src/Inventory.hpp"
#include "src/Cutscene.hpp"
#include "src/Assets.hpp"
#include "src/Menu.hpp"
#include "src/State.hpp"
#include <time.h>

using namespace sf;
using namespace std;

void playMusic();
void stopMusic();

int main(){
    RenderWindow window(VideoMode(wSize.x , wSize.y), "Tim The Alchemist", Style :: Titlebar | Style :: Close);
	window.setFramerateLimit(120);

    Assets :: instance() -> loadAssets();
    std :: srand(time(NULL));

    Clock timer;
    long lastTime = timer.restart().asMicroseconds();
    double dt = 0;

    Sprite start_bg, lost_bg, game_bg(Assets :: instance() -> background[0]);
    game_bg.setScale(SCALE, SCALE);
    Animation start_animation(Assets :: instance() -> background[1], start_bg, sf :: Vector2u(8, 1), sf :: Vector2f(SCALE, SCALE));
    Animation lost_animation(Assets :: instance() -> background[2], lost_bg, sf :: Vector2u(8, 1), sf :: Vector2f(SCALE, SCALE));
    
    Cutscene scene1(Assets :: instance() -> cutscene1, 4, 8);
    scene1.textBoxes.push_back(Textbox("zzzzzz...", 24));
    scene1.textBoxes.push_back(Textbox("What ? Where ? Where am I ?", 24));
    scene1.textBoxes.push_back(Textbox("Is this a dungeon ? How did I get here ?", 24));
    scene1.textBoxes.push_back(Textbox("Hmmm. What is this ? A lock ? Maybe if I find a way to craft a key I can escape...", 24));

    Cutscene scene2(Assets :: instance() -> cutscene2, 4, 8);
    scene2.textBoxes.push_back(Textbox("Finally !", 24));
    scene2.textBoxes.push_back(Textbox("I was able to craft this key", 24));
    scene2.textBoxes.push_back(Textbox("Now I can unclock the hatchet !", 24));
    scene2.textBoxes.push_back(Textbox("Hmmm. I wonder what's next ?", 24));

    for(auto& i : scene1.textBoxes){
        i.setPosition(sf :: Vector2f(wSize.x / 2, wSize.y - 8 * SCALE));
    }

    for(auto& i : scene2.textBoxes){
        i.setPosition(sf :: Vector2f(wSize.x / 2, wSize.y - 8 * SCALE));
    }


    

    Menu startMenu(State :: Type :: Start);
    startMenu.addButton(State :: Type :: Cutscene1, "START", playMusic);
    startMenu.addButton(State :: Type :: Exit, "EXIT", empty);

    std :: vector<Element> level1_items;
    level1_items.push_back(Element(Element :: Type :: Earth, 0));
    level1_items.push_back(Element(Element :: Type :: Earth, 1));
    level1_items.push_back(Element(Element :: Type :: Earth, 2));
    level1_items.push_back(Element(Element :: Type :: Earth, 3));
    level1_items.push_back(Element(Element :: Type :: Fire, 4));
    level1_items.push_back(Element(Element :: Type :: Fire, 5));
    level1_items.push_back(Element(Element :: Type :: Fire, 6));
    level1_items.push_back(Element(Element :: Type :: Fire, 7));
    level1_items.push_back(Element(Element :: Type :: Air, 8));
    level1_items.push_back(Element(Element :: Type :: Water, 9));

    Inventory level1_inventory(level1_items, Element :: Type :: Key);

    Textbox tutorial;

    float musicVol = 0;
    Assets :: instance() -> music.setLoop(true);
    Assets :: instance() -> music.setVolume(musicVol);
   // Assets :: instance() -> music.play();

    while (window.isOpen()){
        Event e;
        while (window.pollEvent(e)){
            if(e.type == Event :: Closed){
				window.close();
			}
        }
        long time = timer.getElapsedTime().asMicroseconds();
        dt  += (double)(time - lastTime);
        lastTime = time;
        

        if(dt >= 1){ // Game logic goes here
            
            window.clear(Color :: White);
            sf :: Vector2f m_pos = (sf :: Vector2f) sf :: Mouse :: getPosition(window);
            startMenu.update(window, e);
            if(State :: instance() -> back() == State :: Type :: Start){
                start_animation.play(0, 0.1f, start_bg);
                window.draw(start_bg);
            }
            if(State :: instance() -> back() == State :: Type :: Cutscene1){
                if(musicVol < 25){
                    musicVol += 0.1;
                    Assets :: instance() -> music.setVolume(musicVol);
                }
                scene1.play();
                scene1.show(window);
                if(scene1.getProgress()){
                    State :: instance() -> pop();
                    State :: instance() -> push(State :: Type :: Level1);
                }
                if(e.type == Event :: MouseButtonPressed){
                    State :: instance() -> pop();
                    State :: instance() -> push(State :: Type :: Level1);
                }
            }
            if(State :: instance() -> back() == State :: Type :: Cutscene2){
                scene2.play();
                scene2.show(window);
                if(scene2.getProgress()){
                    State :: instance() -> pop();
                    State :: instance() -> push(State :: Type :: Level2);
                }
            
            }
            if(State :: instance() -> back() == State :: Type :: Level1){
                
                level1_inventory.update(window, e);
                if(level1_inventory.isLevelCompleted()){
                    State :: instance() -> pop();
                    State :: instance() -> push(State :: Type :: Cutscene2);
                }
                window.draw(game_bg);
                level1_inventory.show(window);
            }  
            if(State :: instance() -> back() == State :: Type :: Level2){
                window.clear(Color :: Black);
                if(musicVol > 0) musicVol -= .1;
            } 
            if(State :: instance() -> back() == State :: Type :: Lost){
                lost_animation.play(0, 0.1f, lost_bg);
                window.draw(lost_bg);
            }
            startMenu.show(window);

            window.display();
            if(State :: instance() -> back() == State :: Type :: Exit){ window.close(); }
            --dt;
        }
    }
    return 0;
}

void playMusic(){
    Assets :: instance() -> music.play();
}

void stopMusic(){
    Assets :: instance() -> music.stop();
}