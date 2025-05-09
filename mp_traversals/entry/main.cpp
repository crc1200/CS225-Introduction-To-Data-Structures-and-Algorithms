
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {
  PNG png;      png.readFromFile("../tests/evilLebron.png");
  
  FloodFilledImage image(png);
  BFS bfs(png, Point(40, 40), 0.05);
  DFS dfs(png, Point(0,0), .05);
  RainbowColorPicker rainbow(0.05);
  MyColorPicker lebronIfy(.01);
  image.addFloodFill( dfs, lebronIfy );
  image.addFloodFill( bfs, lebronIfy );

  Animation animation = image.animate(1000);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );

  lastFrame.writeToFile("../myFloodFill.png");
  animation.write("../myFloodFill.gif");
  return 0;
}
