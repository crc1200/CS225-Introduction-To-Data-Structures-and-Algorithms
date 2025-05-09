#include "Image.h"
#include "StickerSheet.h"
#include <catch2/catch_test_macros.hpp>


int main() {
  Image water; water.readFromFile("../water.png");
  Image shark;    shark.readFromFile("../shark.png");
  Image whale;    whale.readFromFile("../whale.png");
  Image sub;    sub.readFromFile("../sub.png");
  Image house;    house.readFromFile("../house3.png");

  StickerSheet sheet(water, 5);
  
  //std::cout << water.width() << std::endl;
  //std::cout << water.height() << std::endl;
  water.scale(360, 100);

  // Image rain; 
  
  // rain = rain.createRainbowImage();
  

  // std::cout << rain.width() << std::endl;
  // std::cout << rain.height() << std::endl;

  // rain.scale(180, 80);

  // std::cout << rain.width() << std::endl;
  // std::cout << rain.height() << std::endl;
  //std::cout << water.width() << std::endl;
  //std::cout << water.height() << std::endl;

  shark.scale(.095);
  sub.scale(.05);
  whale.scale(.5);
  house.scale(.5);


  sheet.addSticker(shark, 10, 40);
  sheet.addSticker(whale, 400, 120);
  sheet.addSticker(sub, 300, 100);
  sheet.addSticker(house, 200, 300);


  //const Image &renderXBound = sheet.render();
  sheet.render().writeToFile("../myImage.png");


  return 0;
}
