/* Your code here! */

#pragma once
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include <map>
#include <utility>
#include <tuple>


class SquareMaze {
    public:
        void makeMaze(int width, int height);	
        void setWall(int x, int y, int dir, bool exists);	
        std::vector<int> solveMaze();	
        bool canTravel(int x, int y, int dir) const;
	    cs225::PNG * drawMaze() const;
        cs225::PNG * drawMazeWithSolution();
        int findLongest(std::map<std::pair<int, int>, std::pair<std::pair<int, int>, int>> map);

        //std::vector<int> bfs(int startX, int startY);
        
        //std::map<std::pair<int, int>, std::pair<std::pair<int, int>, int>> bfs(int startX, int startY);
         
        //std::vector<int> createPath(std::map<std::pair<int, int>, std::pair<std::pair<int, int>, int>> path, int x, int y);
        //std::vector<int> bfs(int startX, int startY, std::vector<int> path, std::vector<std::pair<int, int>> visited);
        std::vector<int> bfs();


        int random(int low, int hight);


    private:
        int _width; // width
        int _height; // height
        //std::map<std::tuple<int, int, int>, bool> walls;
        //first = bottom, second = right
        //first = right
        //second = bottom
        std::vector<std::vector<std::pair<bool,bool>>> walls;  //2-d array that stores the right and bottom wall value

    

};