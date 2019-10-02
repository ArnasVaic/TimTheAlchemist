#include <SFML/Graphics.hpp>
#include "src/Element.hpp"
#include "src/Assets.hpp"
#include "src/Menu.hpp"
#include "src/State.hpp"
#include <time.h>

using namespace sf;
using namespace std;

int main(){
    RenderWindow window(VideoMode(wSize.x , wSize.y), "Tim The Alchemist", Style :: Titlebar | Style :: Close);
	window.setFramerateLimit(120);

    Assets :: instance() -> loadAssets();
    std :: srand(time(NULL));

    Clock timer;
    long lastTime = timer.restart().asMicroseconds();
    double dt = 0;

    Sprite background(Assets :: instance() -> background);

    Menu startMenu(State :: Type :: Start);
    startMenu.addButton(State :: Type :: Game, "START", empty);
    startMenu.addButton(State :: Type :: Exit, "EXIT", empty);

    Element el(Element :: Type :: Water);

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
            if(State :: instance() -> back() == State :: Type :: Game){

                el.update(window, e, m_pos, 0);

                window.draw(background);

                el.show(window);
            }   
            startMenu.show(window);

            window.display();
            if(State :: instance() -> back() == State :: Type :: Exit){ window.close(); }
            --dt;
        }
    }
    return 0;
}