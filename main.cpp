#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "src/Inventory.hpp"
#include "src/Cutscene.hpp"
#include "src/Assets.hpp"
#include "src/Menu.hpp"
#include "src/State.hpp"

#include <windows.h>
#include <time.h>

using namespace sf;
using namespace std;

void playMusic();
void stopMusic();
void playLoseMusic();
void stopLoseMusic();
void restart();

static Inventory level1_inventory;
static std :: vector<Element> level1_items;
static bool lostmp = false;

int main(){

    HWND myConsole = GetConsoleWindow();
    ShowWindow(myConsole,0);

    Assets :: instance() -> loadAssets();

    RenderWindow window(VideoMode(wSize.x , wSize.y), "Tim The Alchemist", Style :: Titlebar | Style :: Close);
	window.setFramerateLimit(120);
    window.setIcon(16, 16, Assets :: instance() -> icon.getPixelsPtr());
    
    std :: srand(time(NULL));

    Clock timer;
    long lastTime = timer.restart().asMicroseconds();
    double dt = 0;

    Sprite start_bg, lost_bg, won_bg, game_bg(Assets :: instance() -> background[0]);
    game_bg.setScale(SCALE, SCALE);
    Animation start_animation(Assets :: instance() -> background[1], start_bg, sf :: Vector2u(8, 1), sf :: Vector2f(SCALE, SCALE));
    Animation lost_animation(Assets :: instance() -> background[2], lost_bg, sf :: Vector2u(8, 1), sf :: Vector2f(SCALE, SCALE));
    Animation won_animation(Assets :: instance() -> background[3], won_bg, sf :: Vector2u(8, 1), sf :: Vector2f(SCALE, SCALE));
    
    Cutscene scene1(Assets :: instance() -> cutscene1, 4, 8);
    scene1.textBoxes.push_back(Textbox("zzzzzz...", 24));
    scene1.textBoxes.push_back(Textbox("What ? Where ? Where am I ?", 24));
    scene1.textBoxes.push_back(Textbox("Is this a dungeon ? How did I get here ?", 24));
    scene1.textBoxes.push_back(Textbox("Hmmm. What is this ? A lock ? Maybe if I find a way to craft a key I can escape...", 24));

    Cutscene scene2(Assets :: instance() -> cutscene2, 4, 8);
    scene2.textBoxes.push_back(Textbox("Finally !", 24));
    scene2.textBoxes.push_back(Textbox("I was able to craft this key", 24));
    scene2.textBoxes.push_back(Textbox("Now I can unlock the hatch !", 24));
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
    
    Menu gameMenu(State :: Type :: Level1);
    gameMenu.addButton(State :: Type :: Start, "EXIT", stopMusic);
    gameMenu.setButtonPosition(0, sf :: Vector2f( wSize.x - 8 * SCALE, 8 * SCALE));

    Menu lostMenu(State :: Type :: Lost);
    lostMenu.addButton(State :: Type :: Start, "MAIN MENU", empty);
    lostMenu.addButton(State :: Type :: Level1, "TRY AGAIN", restart);

    Menu wonMenu(State :: Type :: Won);
    wonMenu.addButton(State :: Type :: Start, "MAIN MENU", empty);

    
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

    level1_inventory = Inventory(level1_items, Element :: Type :: Key);


    bool restartTutorialClock = true;
    sf :: Clock tutorialTimer;
    float tutorialTime = 6; // the ammount of time (sec) each tutorial textbox has to appear
    uint32_t tutorialIndex = 0; // which tutorial to display
    Textbox tutorial[5];

    tutorial[0] = Textbox("To drag the element aroud press the left mouse button.", 24);
    tutorial[1] = Textbox("To get a new element, place two other elements in sockets marked with squares", 24);
    tutorial[2] = Textbox("To de-combine an element press the right mouse button on it ", 24);
    tutorial[3] = Textbox("Combining the wrong elements or de-combining one reduces your score ! ", 24);
    tutorial[4] = Textbox("If you have a negative score you lose the game so be careful ! ", 24);

    for(uint32_t i = 0 ; i < 5 ; i ++){
        tutorial[i].setPosition(sf :: Vector2f(wSize.x / 2, wSize.y - 8 * SCALE));
    }

    float musicVol = 0;
    Assets :: instance() -> music.setLoop(true);
    Assets :: instance() -> music.setVolume(musicVol);
    Assets :: instance() -> Lostmusic.setLoop(true);
    Assets :: instance() -> Lostmusic.setVolume(15);

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
            gameMenu.update(window, e);
            lostMenu.update(window, e);
            wonMenu.update(window, e);

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
                /* if(e.type == Event :: MouseButtonPressed){
                    State :: instance() -> pop();
                    State :: instance() -> push(State :: Type :: Level1);
                } */
            }
            if(State :: instance() -> back() == State :: Type :: Cutscene2){
                scene2.play();
                scene2.show(window);
                if(scene2.getProgress()){
                    State :: instance() -> pop();
                    State :: instance() -> push(State :: Type :: Won);
                }
            
            }
            if(State :: instance() -> back() == State :: Type :: Level1){
                if(restartTutorialClock){
                    tutorialTimer.restart();
                    restartTutorialClock = false;
                }

                if(tutorialTimer.getElapsedTime().asSeconds() >= tutorialTime){
                    if(tutorialIndex < 5) ++tutorialIndex;
                    tutorialTimer.restart();
                }
                
                level1_inventory.update(window, e);
                if(level1_inventory.isLevelCompleted()){
                    State :: instance() -> pop();
                    State :: instance() -> push(State :: Type :: Cutscene2);
                }
                window.draw(game_bg);
                level1_inventory.show(window);
                
                if(tutorialIndex <= 4)tutorial[tutorialIndex].show(window);
            }  
            if(State :: instance() -> back() == State :: Type :: Level2){
                window.clear(Color :: Black);
                if(musicVol > 0) musicVol -= .1;
            }
            if(State :: instance() -> back() == State :: Type :: Won){
                won_animation.play(0, 0.1f, won_bg);
                window.draw(won_bg);
            }
            if(State :: instance() -> back() == State :: Type :: Lost){
                stopMusic();
                if(!lostmp){
                    playLoseMusic();
                    lostmp = true;
                }
                if(lostmp) stopLoseMusic();
               
                lost_animation.play(0, 0.1f, lost_bg);
                window.draw(lost_bg);
            }
            startMenu.show(window);
            gameMenu.show(window);
            lostMenu.show(window);
            wonMenu.show(window);
            window.display();
            print(lostmp);
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

void playLoseMusic(){
    Assets :: instance() -> Lostmusic.play();
}

void stopLoseMusic(){
    Assets :: instance() -> Lostmusic.stop();
}

void restart(){
    level1_inventory.restart(level1_items);
    lostmp = false;
    stopLoseMusic();
    playMusic();
}