#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"
using namespace cs225;

int main() {
  // List<int> help;
  
  // help.insertBack(2);
  // help.insertBack(-1);
  // help.insertBack(431);
  // help.insertBack(100);
  // help.insertBack(1);

  // mergesort(help.begin(), 5);

  PNG im1;       im1.readFromFile("../tests/merge1.png");
  PNG im2;       im2.readFromFile("../tests/merge2.png");
  PNG expected;  expected.readFromFile("../tests/expected-merge.png");

  PNG out(600, 400);

  vector<HSLAPixel> v1;
  for (unsigned i = 0; i < im1.width(); i++)
      for (unsigned j = 0; j < im1.height(); j++)
          v1.push_back(im1.getPixel(i, j));
  vector<HSLAPixel> v2;
  for (unsigned i = 0; i < im2.width(); i++)
      for (unsigned j = 0; j < im2.height(); j++)
          v2.push_back(im2.getPixel(i, j));
  List<HSLAPixel> l1(v1.begin(), v1.end());
  List<HSLAPixel> l2(v2.begin(), v2.end());
  l1.mergeWith(l2);
  //REQUIRE(l1.size() == 600*400);
  vector<HSLAPixel> merged(l1.begin(), l1.end());
  unsigned x = 0;
  for (unsigned i = 0; i < merged.size(); i++) {
      int y = i % 400;
      out.getPixel(x, y) = merged[i];
      if (y == 399)
          x++;
  }

  out.writeToFile("actual-merge.png");
  //INFO("Output image `out` saved as actual-merge.png");

  return 0;




  // List<int> list2;

  // list2.insertBack(1);
  // list2.insertBack(10);
  // list2.insertBack(12);
  // std::cout << list2 << std::endl;

  // help.mergeWith(list2);
  //std::cout << help << std::endl;
}