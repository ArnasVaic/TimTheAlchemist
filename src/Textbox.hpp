#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include "Utilities.hpp"
#include "Assets.hpp"

#define TBFS 18 // text box font size

class Textbox{

    public :

        Textbox(){}

        Textbox(const std :: string& message, uint32_t charSize = TBFS) : padding(20, 20){
            this -> text = sf :: Text(message, Assets :: instance() -> font, charSize);
            this -> text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
            this -> text.setFillColor(sf :: Color(255, 255, 255));

            rect = sf :: RectangleShape(sf :: Vector2f(text.getGlobalBounds().width + 2 * padding.x, text.getGlobalBounds().height + 2 * padding.y));            
            this -> rect.setOrigin(rect.getGlobalBounds().width / 2, rect.getGlobalBounds().height / 2);
            rect.setFillColor(sf :: Color(0, 0, 0, 100));
        }

        void show(sf :: RenderWindow& window){
            window.draw(rect);
            window.draw(text);
        }

        ~Textbox(){}

    private :
        sf :: Text text;
        sf :: RectangleShape rect;
        sf :: Vector2f padding;

    public :
        void setText(const std :: string& message){
            text.setString(message);
            rect.setSize(sf :: Vector2f(sf :: Vector2f(text.getGlobalBounds().width + 2 * padding.x, text.getGlobalBounds().height + 2 * padding.y)));
            this -> rect.setOrigin(rect.getGlobalBounds().width / 2, rect.getGlobalBounds().height / 2);
        }

        void setPosition(sf :: Vector2f pos){
            rect.setPosition(pos);
            text.setPosition(pos);
        }

        void setFillColor(sf :: Color col){
            text.setFillColor(col);
        }

        const std :: string getText() const{
            return text.getString();
        }

        sf :: Vector2f getPosition(){
            return text.getPosition();
        }

        sf :: Color getFillColor(){
            return text.getFillColor();
        }
};

#endif