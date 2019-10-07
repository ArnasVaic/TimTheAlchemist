#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>

class Animation
{
public :
    Animation(){}

    Animation(sf :: Texture& sprite_sheet, sf :: Sprite& sprite, sf :: Vector2u imageCount, sf ::Vector2f scale ) : imageCount(imageCount), scale(scale), finished(false){
        sprite_size =sf :: Vector2f(sprite_sheet.getSize().x / imageCount.x, sprite_sheet.getSize().y / imageCount.y);
        body = sf :: IntRect(0, 0, sprite_size.x, sprite_size.y);
        sprite = sf :: Sprite(sprite_sheet, body);
        sprite.setScale(scale);
    }

    void play(size_t row, float deltaTime, sf :: Sprite& sprite)
    {
        body.top = row * sprite_size.y;
        const float& elapsedTime = clock.getElapsedTime().asSeconds();
        if(elapsedTime > deltaTime)
        {
            body.left += sprite_size.x;
            if(body.left == imageCount.x * sprite_size.x) body.left=0;
            clock.restart();
        } sprite.setTextureRect(body);
    }

    bool playOnce(size_t row, float deltaTime, sf :: Sprite& sprite)
    {
        if(!finished){
            body.top = row * sprite_size.y;
            const float& elapsedTime = clock.getElapsedTime().asSeconds();
            if(elapsedTime > deltaTime)
            {
                body.left += sprite_size.x;
                if(body.left == imageCount.x * sprite_size.x){
                    body.left=0;
                    finished = true;
                }
                clock.restart();
            } sprite.setTextureRect(body);
        }
        return finished;
    }

    uint32_t getCurrentFrame(){
        return (uint32_t)(body.left / sprite_size.x );
    }
    void flipSprite(sf :: Sprite& sprite){
        sprite.setScale(-scale.x, scale.y);
    }
    void resetSprite(sf :: Sprite& sprite){
        sprite.setScale(scale);
    }
    sf :: Vector2f getSpriteSize(){
        return sprite_size;
    }
    sf :: Vector2f getHalfSpriteSize(){
        return sf :: Vector2f(sprite_size.x/2, sprite_size.y/2);
    }
    sf :: Vector2f getSpriteScale(){
        return scale;
    }

    float getEllapsed(){
        return clock.getElapsedTime().asSeconds();
    }
    ~Animation(){}
    
private:

    bool finished;
    sf :: IntRect body;
    sf :: Clock clock;
    sf :: Vector2f sprite_size;
    sf :: Vector2u imageCount;
    sf :: Vector2f scale;
};

#endif