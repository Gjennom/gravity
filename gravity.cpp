#include "gravity.h"

//  args correspond to:
//    name, number of objects, mass average, mass of first object, zoom	 

int main(int argc, char* argv[]){
  InitWindow(width, height, "Gravity Simulator");
  std::vector<object> objects;
  std::vector<std::string> args;
  std::string view_sort = argv[1];
  for(int i = 0; i < argc; i++){
    std::string entry = argv[i];
    args.push_back(entry);
  }
  prepare(objects, args);
  init_sort(objects, "mass");
  while(!WindowShouldClose()){
    update(objects, 1, 1);
    draw(objects, view_sort, 1, 1);
  }
}