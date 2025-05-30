#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal = NULL;
}
unsigned ImageTraversal::Iterator::getX() {
  return current.x;
}
unsigned ImageTraversal::Iterator::getY() {
  return current.y;
}

ImageTraversal::Iterator::Iterator(ImageTraversal *traversal, Point start, const PNG * inImg, double inTol) : traversal(traversal), start(start), img(inImg), tolerance(inTol){
  current = traversal->peek();
  std::vector<std::vector<bool>> s(img->width(), std::vector<bool> (img->height(), false));
  seen = s;
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  std::vector<std::pair<int, int>> directions;

  directions.push_back(std::make_pair(1,0));
  directions.push_back(std::make_pair(0,1));
  directions.push_back(std::make_pair(-1,0));
  directions.push_back(std::make_pair(0,-1));

  seen[current.x][current.y] = true;

  for (auto d : directions) {
    traversal -> add(Point(current.x + d.first, current.y + d.second));
  }

  while (( !traversal->empty()) && (traversal->peek().x < 0 || 
            traversal->peek().x >= img->width() || 
            traversal->peek().y < 0 || 
            traversal->peek().y >= img->height() || 
            calculateDelta(img->getPixel(start.x, start.y), img->getPixel(traversal->peek().x, traversal->peek().y)) > tolerance || 
            seen[traversal->peek().x][traversal->peek().y] == true)) {
    traversal -> pop();
  }

  if (!traversal -> empty()) {
    current = traversal -> peek();
  }

  return *this;
}

/**
 * Iterator accessor opreator.
 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {  //from tree lab
  /** @todo [Part 1] */
  bool thisEmpty = false; 
  bool otherEmpty = false;

  if (traversal == NULL) { thisEmpty = true; }
  if (other.traversal == NULL) { otherEmpty = true; }

  if (!thisEmpty)  { thisEmpty = traversal->empty(); }
  if (!otherEmpty) { otherEmpty = other.traversal->empty(); }

  if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
  else if ((!thisEmpty)&&(!otherEmpty)) return (traversal != other.traversal); //both not empty then compare the traversals
  else return true; // one is empty while the other is not, return true
}

