#include "Image.h"
#include "StickerSheet.h"
#include <iostream>

//#include <catch2/catch_test_macros.hpp>

using namespace cs225;


int main() {
  Image alma;     alma.readFromFile("../tests/alma.png");
  Image i;        i.readFromFile("../tests/i.png");
  Image expected; expected.readFromFile("../tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200);
  sheet.addSticker(i, 20, 200);
  for (unsigned int i = 0; i < sheet.getLayers().size(); i++) {
    if (std::get<0>(sheet.getLayers()[i]) == NULL) {
      std::cout << "Hello" << std::endl;
    }
  }
  sheet.removeSticker(0);
  std::cout << "This is the size after " << sheet.getLayers().size() << std::endl;
  sheet.render().writeToFile("../otherTest.png");
  expected.writeToFile("../expectedTEst.png");

  //REQUIRE( sheet.render() == expected );

  return 0;
}
