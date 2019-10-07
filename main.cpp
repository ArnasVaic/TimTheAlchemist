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

    Sprite start_bg;
    Animation startBackground(Assets :: instance() -> background[1], start_bg, sf :: Vector2u(8, 1), sf :: Vector2f(SCALE, SCALE));

    Cutscene scene(Assets :: instance() -> cutscene, 4, 8);
    scene.textBoxes.push_back(Textbox("zzzzzz...", 24));
    scene.textBoxes.push_back(Textbox("What ? Where ? Where am I ?", 24));
    scene.textBoxes.push_back(Textbox("Is this a dungeon ? How did I get here ?", 24));
    scene.textBoxes.push_back(Textbox("Hmmm. What is this ? A lock ? Maybe if I find a way to craft a key I can escape...", 24));

    for(auto& i : scene.textBoxes){
        i.setPosition(sf :: Vector2f(wSize.x / 2, wSize.y - 8 * SCALE));
    }


    Sprite gameBackground(Assets :: instance() -> background[0]);
    gameBackground.setScale(SCALE, SCALE);

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

    Inventory level1_inventory(level1_items);

    float musicVol = 0;
    Assets :: instance() -> music.setLoop(true);
    Assets :: instance() -> music.setVolume(musicVol);

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
                startBackground.play(0, 0.1f, start_bg);
                window.draw(start_bg);
            }
            if(State :: instance() -> back() == State :: Type :: Cutscene1){
                if(musicVol < 10){
                    musicVol += 0.01;
                    print(musicVol);
                    Assets :: instance() -> music.setVolume(musicVol);
                }
                scene.play();
                scene.show(window);
                if(scene.getProgress()){
                    State :: instance() -> pop();
                    State :: instance() -> push(State :: Type :: Level1);
                }
            }
            if(State :: instance() -> back() == State :: Type :: Level1){
                
                level1_inventory.update(window, e);

                window.draw(gameBackground);

                level1_inventory.show(window);
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