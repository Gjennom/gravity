#include <ctime>
#include <iostream>
#include <utility>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include "raylib.h"

const double G = 6.67430e-11; // global gravitational constant
const float pi = 3.14159265358979323846;
const float minimum_distance = 10; // distance (in meters) below which gravitational acceleration is ignored, and objects collide
const float spatial_density = 1; // number of meters to a pixel
const int height = 1000; // height of window
const int width = 1500; // width of window

struct object{
  double x_pos;
  double y_pos;
  double z_pos;
  double x_vel;
  double y_vel;
  double z_vel;
  double mass;
};

std::vector<object> create_objects(const int count);

std::vector<object> create_objects(int count, 
object example, const std::string state);

float distance(const float x1, const float y1, const float x2, const float y2);

std::pair<float,float> acceleration(const float m2, const float distance);

int wrap(const int value, const int min, const int max);

void update(std::vector<object>& objects, const float y_scale, const float x_scale);

void draw(const std::vector<object>& objects, const std::string method,
const float x_scale, const float y_scale);

Color custom(int i, int total);

std::pair<float,float> orbit_velocity(float central_mass, float radius, float x_diff, float y_diff);

std::vector<std::string> parse(std::string input, char delimiter);

void prepare(std::vector<object>& objects, std::vector<std::string> input);

void init_sort(std::vector<object>& objects, std::string sort_by);

bool comp(object A, object B);

