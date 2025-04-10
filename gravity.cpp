#include "gravity.h"

int main(int argc, char* argv[]){
  InitWindow(width, height, "Gravity Simulator");
  std::vector<object> objects;
  std::vector<std::string> args;
  std::string view_sort = argv[1];
  int count = 0;
  for(int i = 0; i < argc; i++){
    std::string entry = argv[i];
    args.push_back(entry);
  }
  print_cheatsheet();
  prepare(objects, args);
  init_sort(objects, "mass");
  while(!WindowShouldClose()){
    count++;
    update(objects, 1, 1);
    draw(objects, view_sort, 1, 1, argv[argc + 1] == "track_mass_epicenter");
  }
}
