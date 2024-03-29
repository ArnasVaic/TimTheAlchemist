#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <random>
#include <math.h>

#define PI 3.14159265359 

#define INVENTORY_SIZE_X 5
#define INVENTORY_SIZE_Y 4
#define INVENTORY_SIZE INVENTORY_SIZE_X * INVENTORY_SIZE_Y

#define SCALE 8

#define SPACING 8 * SCALE
#define SOCKET_SIZE 16 * SCALE
#define OFFSETX 8 * SCALE
#define OFFSETY 16 * SCALE

const sf :: Vector2u CRAFTSOCKET1(160 * SCALE, 52 * SCALE); // coord of the socket where you get your new items
const sf :: Vector2u CRAFTSOCKET2(136 * SCALE, 32 * SCALE); // coord of socket where you put items
const sf :: Vector2u CRAFTSOCKET3(136 * SCALE, 72 * SCALE); // coord of socket where you put items

bool pressed = false, released = false;

#define DEFAULT_TEXTURE_SIZE 16
#define print(x) std :: cout << x << std :: endl

const sf :: Vector2u wSize(192 * SCALE, 116 * SCALE);

float mag(sf :: Vector2u v){
    return sqrt(v.x * v.x + v.y * v.y);
}

float mag(sf :: Vector2f v){
    return sqrt(v.x * v.x + v.y * v.y);
}

bool clickedRight(sf :: Event e, sf :: Vector2f m_pos){
    if(e.mouseButton.button == sf :: Mouse :: Right){
        if(e.type == sf :: Event :: MouseButtonPressed) pressed = true;
        else  if(e.type == sf :: Event :: MouseButtonReleased && pressed) released = true;
    }
    return pressed && released;
}


void empty(){ }

#endif