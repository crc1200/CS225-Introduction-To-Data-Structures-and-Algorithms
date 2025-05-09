/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
        * @todo Implement this function!
    */

    //build kd tree of points with LUV values
    std::vector<Point<3>> tilesColorValues;
    MosaicCanvas* result = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    std::map<Point<3>, TileImage*> map;

    for (unsigned i = 0; i < theTiles.size(); i++) {
        Point<3> insert = convertToXYZ(theTiles[i].getAverageColor());
        map.insert({insert, &theTiles[i]});
        tilesColorValues.push_back(insert);
    }

    KDTree tree = KDTree(tilesColorValues);
    unsigned row = theSource.getRows();
    unsigned col = theSource.getColumns();

    for (unsigned r = 0; r < row; r++) {
        for (unsigned c = 0; c < col; c++) {
            //find nearest neighbor of the region of the source given our kd tree of tiles

            cs225::LUVAPixel color = theSource.getRegionColor(r, c);
            Point<3> imagePoint = convertToXYZ(color);
            Point<3> p = tree.findNearestNeighbor(imagePoint);

            // unsigned loc = map.at(p);
            auto img = map.at(p);
            result -> setTile(r, c, img);
           
        }
    }
    return result;
}


  // if (it == map.end()) {
            //     //std::cout << "not found in map" << std::endl;
            //     std::cout << "This is the point we cant find" << std::endl;
            //     std::cout << p[0] << std::endl;
            //     std::cout << p[1] << std::endl;
            //     std::cout << p[2] << std::endl;
            // }

                //std::cout << "not found in map" << std::endl;