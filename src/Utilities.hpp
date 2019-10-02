#pragma once
#include <SFML/Graphics.hpp>
#include <sys/stat.h>
#include <string>

#define TILESIZE 16

#define print(x) std :: cout << x << std :: endl
const sf :: Vector2f gScale(4, 4);
const sf :: Vector2u wSize(512, 768);

bool exists(const std :: string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

void empty(){ }