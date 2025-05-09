/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>
#include <string_view>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    if (first[curDim] < second[curDim]) {
      return true;
    } else if (second[curDim] < first[curDim]) {
      return false;
    } else {
      return first < second;
    }
}
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    int currentDistance = 0;
    int potentialDistance = 0;
    for (int i = 0; i < Dim; i++) {
      currentDistance += std::pow(target[i] - currentBest[i], 2);
      potentialDistance += std::pow(target[i] - potential[i], 2);
    }
    if (potentialDistance < currentDistance) {
      return true;
    } else if (currentDistance < potentialDistance) {
      return false;
    } else {
      return potential < currentBest;
    }
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& points, int left, int right, int pivotIndex, int dim) {
  auto pivotVal = points[pivotIndex];
  std::swap(points[pivotIndex], points[right]);
  int storeIdx = left;
  for (int i = left; i < right; i++) {
    if (smallerDimVal(points[i], pivotVal, dim)) {
      std::swap(points[storeIdx], points[i]);
      storeIdx ++;
    }
  }
  std::swap(points[right], points[storeIdx]);
  return storeIdx;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(vector<Point<Dim>>& list, int l, int r, int k, int dim) {
  while (true) {
    if (l == r) {
      return list[l];
    }     
    int pIdx = (l + r) / 2;
    pIdx = partition(list, l, r, pIdx, dim);
    if (k == pIdx) {
      return list[k];
    } else if (k < pIdx) {
      r = pIdx - 1;
    } else {
      l = pIdx + 1;
    }    
  }
}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    auto v = newPoints;
    buildTree(v, 0, 0, v.size() - 1, root);
}

template <int Dim>
void KDTree<Dim>::buildTree(vector<Point<Dim>>& points, int dim, int left, int right, KDTreeNode *& curr) {
  if (left <= right) {
    int mid = (left + right) / 2;
    auto point = quickSelect(points, left, right, mid, dim);
    curr = new KDTreeNode(point);
    buildTree(points, (dim + 1) % Dim, left, mid - 1, curr -> left);
    buildTree(points, (dim + 1) % Dim, mid + 1, right, curr -> right);
  }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> querryCopy = query;
    auto rootCopy = root;
    Point<Dim> x = neighborHelper(querryCopy, 0, rootCopy);
    return x;
}

template <int Dim>
Point<Dim> KDTree<Dim>::neighborHelper(Point<Dim>& query, int dim, KDTreeNode *& curr) const {
  Point<Dim> nearest = curr -> point;
  Point<Dim> tmp = curr -> point;
  if (curr -> left == NULL && curr -> right == NULL) {
    return curr -> point; 
  }
  if (smallerDimVal(query, curr -> point, dim) && curr -> left != NULL) {
    tmp = neighborHelper(query, (dim + 1) % Dim, curr -> left);
  } else if (curr -> right != NULL) {
    tmp = neighborHelper(query, (dim + 1) % Dim, curr -> right);
  }
  if (shouldReplace(query, nearest, tmp)) {
    nearest = tmp;
  }
  double radius = 0;
    for (int i = 0; i < Dim; i++) {
      int d1 = query[i] - nearest[i];
      int d1Squared = std::pow(d1, 2);
      radius += d1Squared;
    }
  double splitDist = std::pow((curr -> point[dim] - query[dim]), 2);

  if (radius >= splitDist) {
    //Point<Dim> tmp = curr -> point;
    if (smallerDimVal(query, curr -> point, dim) && curr -> right != NULL) {
      tmp = neighborHelper(query, (dim + 1) % Dim, curr -> right);
    } else if (curr -> left != NULL){
      tmp = neighborHelper(query, (dim + 1) % Dim, curr -> left);
    }
    if (shouldReplace(query, nearest, tmp)) {
      nearest = tmp;
    }
  }
  return nearest;
}


