#ifndef CUTSCENE_HPP
#define CUTSCENE_HPP

#include <SFML/Graphics.hpp>
#include "Utilities.hpp"
#include "Animation.hpp"
#include "Assets.hpp"

class Cutscene{

    public :

        Cutscene(){}

        Cutscene(const sf :: Texture& sheet, uint32_t frames, float frame_length) : finished(false), frame_length(frame_length){
            scene = Animation(Assets :: instance() -> cutscene, sprite, sf :: Vector2u(frames, 1), sf :: Vector2f(SCALE, SCALE));
            shade = sf :: RectangleShape(scene.getSpriteSize());
            shade.setScale(SCALE, SCALE);
        }

        void play(){
            finished = scene.playOnce(0, frame_length, sprite);
            float fade = this -> fade(scene.getEllapsed());
            shade.setFillColor(sf :: Color(0, 0, 0, 255 * fade));
        }

        void show(sf :: RenderWindow& window){
            window.draw(sprite);
            textBoxes[scene.getCurrentFrame()].show(window);
            window.draw(shade);
        }

        float fade(float ellapsed){
            return pow(1 - abs(cos(PI * (2 * ellapsed - frame_length)/(2 * frame_length))) , 2);
        }

        bool getProgress(){ return finished; }

    private :

        bool finished;
        float frame_length;
        uint32_t current_frame;
        Animation scene;
        sf :: Sprite sprite;
        sf :: RectangleShape shade;
    public :
        std :: vector<Textbox> textBoxes;
};

#endif