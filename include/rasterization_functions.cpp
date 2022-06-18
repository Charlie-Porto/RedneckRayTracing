#ifndef rasterization_functions_cpp
#define rasterization_functions_cpp

#include <ezprint.cpp>

namespace pce {
namespace raster {

/* for Circle Drawing */
std::vector<std::vector<int>> getCircleOctet(int xc, int yc, int x, int y) {
  std::vector<std::vector<int>> points;
  points.push_back({xc+x, yc+y});
  points.push_back({xc-x, yc+y});
  points.push_back({xc+x, yc-y});
  points.push_back({xc-x, yc-y});
  points.push_back({xc+y, yc+x});
  points.push_back({xc-y, yc+x});
  points.push_back({xc+y, yc-x});
  points.push_back({xc-y, yc-x});
  return points;
}


std::vector<std::vector<int>> getCircleRasterizationPoints(int xc, int yc, int r) {
  int x = 0;
  int y = r;
  int d = 3 - 2 * r;
  std::vector<std::vector<int>> points_list = getCircleOctet(xc, yc, x, y);
  while (y >= x) {
    x++;
    if (d > 0) {
      y--;
      d = d + 4 * (x - y) + 10;
    } else {
      d = d + 4 * x + 6;
    }
    std::vector<std::vector<int>> new_points = {
      {xc+x, yc+y},
      {xc-x, yc+y},
      {xc+x, yc-y},
      {xc-x, yc-y},
      {xc+y, yc+x},
      {xc-y, yc+x},
      {xc+y, yc-x},
      {xc-y, yc-x},
    };
    points_list.insert(points_list.end(), new_points.begin(), new_points.end());
  }
  return points_list;
}


}
}

#endif /* rasterization_functions_cpp */
