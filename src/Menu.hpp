#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
// my headers
#include "State.hpp"
#include "Button.hpp"
#include "Assets.hpp"

class Menu{
	public :
		Menu(){ }

		Menu(State :: Type exist) : exist(exist){ }

		void addButton(State :: Type point, std :: string text, void(*command)()){
			buttons.push_back(Button(point, command, Assets :: instance() -> font,
					text,sf :: Vector2f(wSize.x / 2 , 4 * wSize.y / 5 + buttons.size() * 64)));
		}

		void update(sf :: RenderWindow& window, sf :: Event e){
			if(exist == State :: instance() -> back()){
				for(auto& bt : buttons){
					bt.update(e, window);
				}
			}
		}

		void show(sf :: RenderWindow& window){
			if(exist == State :: instance() -> back()){
				for(auto& bt : buttons){
					bt.show(window);
				}
			}
		}

		~Menu(){ }
	private :
		State :: Type exist; // In what state does this menu exist
		std :: vector<Button> buttons;
};