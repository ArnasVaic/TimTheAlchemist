#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sys/stat.h>
#include <string>
#include <math.h>

#define INVENTORY_SIZE_X 4
#define INVENTORY_SIZE_Y 5
#define INVENTORY_SIZE INVENTORY_SIZE_X * INVENTORY_SIZE_Y

#define SPACING 16
#define SOCKET_SIZE 64
#define OFFSETX 64
#define OFFSETY 32

#define DEFAULT_TEXTURE_SIZE 64
#define print(x) std :: cout << x << std :: endl

const sf :: Vector2u wSize(768, 464);


bool exists(const std :: string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

float mag(sf :: Vector2u v){
    return sqrt(v.x * v.x + v.y * v.y);
}

float mag(sf :: Vector2f v){
    return sqrt(v.x * v.x + v.y * v.y);
}


void empty(){ }