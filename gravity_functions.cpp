#include "gravity.h"

// creates count gravity objects, with all parameters set to 0
std::vector<object> create_objects(const int count){
  object temp = {0};
  std::vector<object> result(count, temp);
  return result;
}

/*
  places each object in a random coordinate if RANDOMIZE
  all other parameters besides position set to those in example

  places objects in a neat grid if GRID

  makes copies of example, if DEFAULT
*/
std::vector<object> create_objects(const int count, 
object example, const std::string state){
  std::vector<object> result;
  result.reserve(count);
  if(state == "RANDOMIZE"){
    srand(time(0));
    object temp = example;
    for(int i = 0; i < count; i++){
      temp.x_pos = spatial_density * ((rand()%width) - width / 2);
      temp.y_pos = spatial_density * ((rand()%height) - height / 2);
      result.push_back(temp);
    }
  }
  else if(state == "GRID"){
    int cols = (count % static_cast<int>(sqrt(count)));
    int rows = 0;
    object temp = example;
    int h = height / cols;
    int w = width / cols;
    for(int i = 0; i < count; i++){
      if((i + 1) % cols == 0)rows++;
      temp.x_pos = spatial_density * ((i + 1) % (cols * w - width / 2));
      temp.y_pos = spatial_density * (rows * h - height / 2);
      result.push_back(temp);
    }
  }
  else if(state == "CIRCULAR"){
    srand(time(0));
    object temp = example;
    for(int i = 0; i < count; i++){
      temp.x_pos = 300 * cos((2*pi*i) / count);
      temp.y_pos = 300 * sin((2*pi*i) / count);
      result.push_back(temp);
    }
  }
  else{
    object temp = example;
    for(int i = 0; i < count; i++){
      result.push_back(temp);
    }
  }
  return result;
}

float distance(const float x1, const float y1, const float x2, const float y2){
  return(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

std::pair<float,float> acceleration(const float m2, const float distance, float x_delta,
float y_delta){
  float dif = (G * m2 / -pow(distance,0.5));
  std::pair<float,float> result;
  result.first = dif * x_delta;
  result.second = dif * y_delta;
  return result;
}

int wrap(const int value, const int min, const int max){
  return ((value - min) % (max - min) + (max - min)) % (max - min) + min;
}

void update(std::vector<object>& objects, const float y_scale, const float x_scale){
  bool zero_mass_flag = false;
  for(int i = 0; i < objects.size(); i++){
    float ax_d = 0;
    float ay_d = 0;
    for(int j = 0; j < objects.size(); j++){
      if(objects[j].mass == 0)break;
      float dist = distance(objects[i].x_pos, objects[i].y_pos, objects[j].x_pos, objects[j].y_pos);
      float x_d = objects[i].x_pos - objects[j].x_pos; 
      float y_d = objects[i].y_pos - objects[j].y_pos;
      if(dist > minimum_distance){
        std::pair<float,float> accel = acceleration(objects[j].mass,
        dist, x_d, y_d);
        ax_d += accel.first;
        ay_d += accel.second;
      }
    }
    objects[i].x_vel += ax_d;
    objects[i].y_vel += ay_d;
    objects[i].x_pos += objects[i].x_vel;
    objects[i].y_pos += objects[i].y_vel;
  }
}

void draw(const std::vector<object>& objects, const std::string method,
const float x_scale, const float y_scale){
  BeginDrawing();
  Color orig;
  if(method == "TITLE"){
    ClearBackground(BLACK);
    for(int i = 0; i < objects.size(); i++){
      int pos_x = (width / 2) + (1 / x_scale * (float)objects[i].x_pos);
      int pos_y = (height / 2) + (1 / y_scale * (float)objects[i].y_pos);
      orig = custom(i, objects.size());
      DrawCircle(pos_x, pos_y, 10, orig);
      DrawText(std::to_string(i).c_str(), pos_x - 5, pos_y + 10, 20, orig);
    }
  }
  else if(method == "TRACE"){
    for(int i = 0; i < objects.size(); i++){
      int pos_x = (width / 2) + (1 / x_scale * objects[i].x_pos);
      int pos_y = (height / 2) + (1 / y_scale * objects[i].y_pos);
      orig = custom(i, objects.size());
      DrawPixel(pos_x, pos_y, orig);
    }
  }
  else if(method == "POINTS"){
    ClearBackground(BLACK);
    for(int i = 0; i < objects.size(); i++){
      int pos_x = (width / 2) + (1 / x_scale * objects[i].x_pos);
      int pos_y = (height / 2) + (1 / y_scale * objects[i].y_pos);
      orig = custom(i, objects.size());
      DrawPixel(pos_x, pos_y, orig);
    }
  }
  else if(method == "WRAP"){
    for(int i = 0; i < objects.size(); i++){
      int pos_x = (width / 2) + (1 / x_scale * objects[i].x_pos);
      int pos_y = (height / 2) + (1 / y_scale * objects[i].y_pos);
      orig = custom(i, objects.size());
      DrawPixel(wrap(pos_x, width, 0), wrap(pos_y, height, 0), orig);
    }
  }
  else if(method == "CIRCLES"){
    ClearBackground(BLACK);
    for(int i = 0; i < objects.size(); i++){
      int pos_x = (width / 2) + (1 / x_scale * (float)objects[i].x_pos);
      int pos_y = (height / 2) + (1 / y_scale * (float)objects[i].y_pos);
      orig = custom(i, objects.size());
      DrawCircle(pos_x, pos_y, 10, orig);
    }
  }
  else{
    std::cout << "Unrecognised method, please enter TRACE, CIRCLES, or TITLE" << std::endl;
  }
  EndDrawing();
}

Color custom(int i, int total){
      Color c = (Color) {
        (unsigned char)((sin(2 * pi * (float)i / total) + 1) * 127),
        (unsigned char)((-sin(2 * pi * (float)i / total) + 1) * 127),
        (unsigned char)((cos(2 * pi * (float)i / total) + 1) * 127),
        (unsigned char)(100 + (-cos(2 * pi * (float)i / total) + 1) * 32)  
      };
  return c;
}

std::pair<float,float> orbit_velocity(float central_mass, float radius, float x_diff, float y_diff){
  float mag = std::sqrt(G * central_mass / radius);
  float r = std::sqrt(x_diff * x_diff + y_diff * y_diff);
  std::pair<float,float> result;
  result.first = -mag * y_diff / r;
  result.second = mag * x_diff / r;
  return(result);
}

std::vector<std::string> parse(std::string input, char delimiter){
  std::vector<std::string> result;
  std::string word;
  for(char letter : input){
    if(letter == delimiter){
      result.push_back(word);
      word = "";
    }else{
      word += letter;
    }
  }
  if(word.size() != 0) result.push_back(word);
  return result;
}

/*
syntax: ./gravity new add:10 mass:1000000 position:random & add:1 mass:10000000000 position:1000:1000 is_center_of_system

translates to: make a new sim, add 10 objects of mass 1000000 and random position
               then, add an additional object of mass 1000000000 and positioned at 1000, 1000, then have all rotate around it
*/

void prepare(std::vector<object>& objects, std::vector<std::string> input){
  int new_objects = 0;
  float new_mass = 0;
  float new_x = 0;
  float new_y = 0;
  float new_vel_x = 0;
  float new_vel_y = 0;
  std::string new_keyword = "";
  std::string position;
  std::vector<std::string> instruct;

  for(auto thing : input){
    std::cout << "@ " << thing << std::endl;
  }

  for(int i = 2; i < input.size(); i++){
    std::string entry = input[i];
    instruct = parse(entry,':');
    if(instruct[0] == "new") objects.clear();
    else if(instruct[0] == "add"){
      new_objects = std::stol(instruct[1]);
    }else if(instruct[0] == "mass"){
      new_mass = std::stof(instruct[1]);
    }else if(instruct[0] == "position"){
      if(instruct[1] == "random"){
        position = "RANDOMIZE";
      }else if(instruct[1] == "circular"){
        position = "CIRCULAR";
      }else if(instruct[1] == "grid"){
        position = "GRID";
      }else{
        new_x = std::stof(instruct[1]);
        new_y = std::stof(instruct[2]);
      }
    }else if(instruct[0] == "velocity"){
      new_vel_x = std::stof(instruct[1]);
      new_vel_y = std::stof(instruct[2]);
    }else if(instruct[0] == "is_center_of_system"){
      new_keyword = "is_center_of_system";
    }else if(instruct[0] == "and"){
      std::vector<object> objects_2 = create_objects(new_objects, {new_x, new_y, 0, new_vel_x, new_vel_y, 0, new_mass}, position);
      objects.insert(objects.end(), objects_2.begin(), objects_2.end());
      new_objects = 0;
      new_mass = 0;
      new_x = 0;
      new_y = 0;
      new_vel_x = 0;
      new_vel_y = 0;
      new_keyword = "";
      position;
      instruct.clear();
    }
  }
  std::vector<object> objects_2 = create_objects(new_objects, {new_x, new_y, 0, new_vel_x, new_vel_y, 0, new_mass}, position);
  objects.insert(objects.end(), objects_2.begin(), objects_2.end());

  if(new_keyword == "is_center_of_system"){
    int max_index = 0;
    float mass_max = 0;
    for(int i = 0; i < objects.size(); i++){
      if(objects[i].mass > mass_max) max_index = i;
    }
    
    for(int i = 0; i < objects.size(); i++){
      if(i != max_index){
        float x_diff = objects[i].x_pos - objects[max_index].x_pos; 
        float y_diff = objects[i].y_pos - objects[max_index].y_pos;
        float rad = distance(objects[max_index].x_pos ,objects[max_index].y_pos ,objects[i].x_pos ,objects[i].y_pos);
        std::pair v = orbit_velocity(objects[max_index].mass,rad,x_diff,y_diff);
        objects[i].x_vel = v.first;
        objects[i].y_vel = v.second;
      }
    }
  }
}

bool comp(object A, object B){
  return A.mass > B.mass;
}

void init_sort(std::vector<object>& objects, std::string sort_by){
  if(sort_by == "mass"){
    std::cout << "before sort" << ' ';
    std::sort(objects.begin(), objects.end(), comp);
  }
}
