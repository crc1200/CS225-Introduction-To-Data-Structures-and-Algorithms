/* Your code here! */
#include <vector>
#include "maze.h"
#include <random>
#include "dsets.h"
#include<bits/stdc++.h>
#include <iostream>
#include <map>

#include <queue>

std::random_device rd;
std::mt19937 gen(rd());
 
int SquareMaze::random(int low, int high) {
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

void SquareMaze::makeMaze(int width, int height) { // m x n: m = _height, n = _width

    _width = width;
    _height = height;
    
    DisjointSets set;
    set.addelements(_height * _width);

    std::pair insertPair = std::make_pair(true, true);
    std::vector<std::vector<std::pair<bool,bool>>> vec(_height , std::vector<std::pair<bool,bool>> (_width, insertPair));

    while (set.size(0) < (_width) * (_height)) {

        int i = random(0, _height - 1);
        int j = random(0, _width - 1);
        int direction = random(0,1);

        int k = j + (i * _width);

        //d = 0 - down
        // d = 1 - right

        if (direction == 0 && vec[i][j].first && i < _height - 1) {
            int b = j + ((i + 1) * _width);
            if (set.find(k) != set.find(b)) {
                std::pair insertPair = std::make_pair(false, vec[i][j].second);
                vec[i][j] = insertPair;
                //setWall(i, j, 1, false);
                set.setunion(k, b);
            }
        } else if (direction == 1 && vec[i][j].second && j < _width - 1) {
            int b = k + 1;
            if (set.find(k) != set.find(b)) {
                std::pair insertPair = std::make_pair(vec[i][j].first, false);
                vec[i][j] = insertPair;
                //setWall(i, j, 0, false);
                set.setunion(k, b);
            }
        }
    }
    walls = vec;
    
}
void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (dir == 0) { // right
        walls[y][x] = std::make_pair(walls[y][x].first, exists);
    } else { // down
       walls[y][x] = std::make_pair(exists, walls[y][x].second);
    }
}	

//should use BFS to solve
std::vector<int> SquareMaze::solveMaze() {
    std::vector<int> res = bfs();
    std::reverse(res.begin(), res.end());
    return res;
}






//keeps track of node it traveled to, node it traveled from, direction
//return - contains the keys as the node traveled to, values is the direction and the node that it came from





bool SquareMaze::canTravel(int x, int y, int dir) const {
    //we store right and down information
    if (x < 0 || y < 0 || x > _width || y > _height) {
        return false;
    }
    if ((x == 0 && dir == 2) || (x == _width - 1 && dir == 0) || (y == 0 && dir == 3) || (y == _height - 1 && dir == 1)) {
        return false;
    }
    if (dir == 2) {
        return !(walls[y][x - 1].second);
    } else if (dir == 3) {
        return !(walls[y -1][x].first);
    } else {
        if (dir == 0) {
            return !(walls[y][x].second);
        }
        return !(walls[y][x].first);
    }
}
cs225::PNG * SquareMaze::drawMaze() const {
    cs225::PNG * res = new cs225::PNG((_width * 10) + 1, (_height * 10) + 1);
    for (unsigned j = 10; j < res -> width(); j++) {
        res -> getPixel(j, 0) = cs225::HSLAPixel(0,0,0);
    }
    for (unsigned i = 0; i < res -> height(); i++) {
        res -> getPixel(0, i) = cs225::HSLAPixel(0,0,0);
    }

    for (int i = 0; i < _width; i++) {
        for (int j = 0; j < _height; j++) {
            
            bool downWallStatus = walls[j][i].first;
            bool rightWallStatus = walls[j][i].second;
            
            if (rightWallStatus) {
                for (unsigned k = 0; k <= 10; k++) {
                    res -> getPixel((i + 1) * 10, (j * 10) + k) = cs225::HSLAPixel(0,0,0);
                }
            }
            if (downWallStatus) {
                for (unsigned k = 0; k <= 10; k++) {
                    res -> getPixel((i * 10) + k, (j + 1) * 10) = cs225::HSLAPixel(0,0,0);
                }
            }
        }
    }

    return res;
}

// dir = 0 represents a rightward step (+1 to the x coordinate)
// dir = 1 represents a downward step (+1 to the y coordinate)
// dir = 2 represents a leftward step (-1 to the x coordinate)
// dir = 3 represents an upward step (-1 to the y coordinate)

cs225::PNG * SquareMaze::drawMazeWithSolution() {
    cs225::PNG * res = drawMaze();
    std::vector<int> path = solveMaze();
    int currentX = 5;
    int currentY = 5;
    for (int dir : path) {
        if (dir == 0) {
            for (int i = 0; i < 11; i++) {
                res -> getPixel(currentX + i, currentY) = cs225::HSLAPixel(0,1,.5);
            }
            currentX += 10;
        } else if (dir == 1) {
            for (int i = 0; i < 11; i++) {
                res -> getPixel(currentX, currentY + i) = cs225::HSLAPixel(0,1,.5);
            }
            currentY += 10;

        } else if (dir == 2) {
            for (int i = 0; i < 11; i++) {
                res -> getPixel(currentX - i, currentY) = cs225::HSLAPixel(0,1,.5);
            }
            currentX -= 10;

        } else if (dir == 3) {
            for (int i = 0; i < 11; i++) {
                res -> getPixel(currentX, currentY - i) = cs225::HSLAPixel(0,1,.5);
            }
            currentY -= 10;
        }
    }
    currentX -= 5;
    currentY += 5;
    for (int k = 1; k < 10; k++) {
        res -> getPixel(currentX + k, currentY) = cs225::HSLAPixel(1,1,1);
    }
    return res;
}	

std::vector<int> SquareMaze::bfs() {
    
    std::pair<int, int> endNode = std::make_pair(0, 0);

    std::queue<std::pair<int, int>> points;
    std::vector<std::vector<bool>> visited(_height , std::vector<bool> (_width, false));

    std::map<std::pair<int, int>, std::pair<std::pair<int, int>, int>> map;


    points.push(endNode);
    visited[0][0] = true;

    while (!points.empty()) {

        auto current = points.front();
        int currentX = current.first;
        int currentY = current.second;
        points.pop();

        //create neighbors
        std::pair<int, int> rightNeighbor = std::make_pair(currentX + 1, currentY);
        std::pair<int, int> leftNeighbor = std::make_pair(currentX - 1, currentY);
        std::pair<int, int> upNeighbor = std::make_pair(currentX, currentY - 1);
        std::pair<int, int> downNeighbor = std::make_pair(currentX, currentY + 1);


        //check right
        if (canTravel(currentX, currentY, 0) && !visited[rightNeighbor.second][rightNeighbor.first]) {
            points.push(rightNeighbor);
            visited[rightNeighbor.second][rightNeighbor.first] = true;
            auto i = std::make_pair(current, 0);
            map.insert({rightNeighbor, i});
        }
        //check left
        if (canTravel(currentX, currentY, 2) && !visited[leftNeighbor.second][leftNeighbor.first]) {
            points.push(leftNeighbor);
            visited[leftNeighbor.second][leftNeighbor.first] = true;
            auto i = std::make_pair(current, 2);
            map.insert({leftNeighbor, i});
        }
        //check up
        if (canTravel(currentX, currentY, 3) && !visited[upNeighbor.second][upNeighbor.first]) {
            points.push(upNeighbor);
            visited[upNeighbor.second][upNeighbor.first] = true;
            auto i = std::make_pair(current, 3);
            map.insert({upNeighbor, i});
        }
        //check down
        if (canTravel(currentX, currentY, 1) && !visited[downNeighbor.second][downNeighbor.first]) {
            points.push(downNeighbor);
            visited[downNeighbor.second][downNeighbor.first] = true;
            auto i = std::make_pair(current, 1);
            map.insert({downNeighbor, i});
        }
    }
    int loc = findLongest(map);

    auto s = std::make_pair(loc, _height - 1);

    std::vector<int> path;
    while (s != endNode) {
        auto x = map[s];
        path.push_back(x.second);
        s = x.first;
    }
    return path;
}

int SquareMaze::findLongest(std::map<std::pair<int, int>, std::pair<std::pair<int, int>, int>> map) {
    int max = 0;
    int loc = 0;
    for (int i = 0; i < _width; i++)
    {
        int c = 0;
        std::pair<int, int> endNode = std::make_pair(i, _height - 1);
        std::pair<int, int> startNode = std::make_pair(0, 0);
        while (endNode != startNode)
        {
            auto x = map[endNode];
            endNode = x.first;
            c++;
        }
        if (c > max)
        {
            max = c;
            loc = i;
        }
    }
    return loc;
}


