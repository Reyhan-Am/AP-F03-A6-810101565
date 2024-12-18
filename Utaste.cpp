#include "Utaste.hpp"

UTaste::UTaste(string districts_path, string restaurants_path)
    : putter(districts_path, restaurants_path),
      poster(districts_path, restaurants_path),
      deleter(districts_path, restaurants_path),
      getter(districts_path, restaurants_path) {}

void UTaste::printing()
{
    
}