#include "../inc/Split.h"
#include "iostream"

/// @file
/// @brief Main function. Find dublicate files.
/// @author btv<example@example.com>
int main(int argc, char** argv) {
    
    if (argc < 4) {
      std::cout << "Need params <file_name> <num_map_threads> <num_reduce_threads>"<<std::endl;
      return -1;
    }
      
    std::string file_name = argv[1];
    std::size_t map_threads = std::stoi(argv[2]);
    std::size_t reduce_threads = std::stoi(argv[3]); 

    if (map_threads <=0 || reduce_threads<=0) {
      std::cout << "Num_threads must more, than 0"<<std::endl;
      return -1;
    }
    (void) reduce_threads;

    Split split(file_name,map_threads);
    auto sections = split.Work();
  //  Options_Parser options_parser;
  //  auto options = options_parser.Parse(argc, argv);
  //  if (!options)
  //     return 0;
 
  // PathFinder pathFinder(options.get().excPaths, options.get().depth, options.get().masks, options.get().minSize);
  // auto groupPath = pathFinder.FindPaths(options.get().incPaths);
  // FileScanner fileScanner(options.get().block, options.get().algo);  
  // auto duplicates = fileScanner.Scan(groupPath);

  // for (auto& dup : duplicates) {
  //   for (auto& path : dup) {
  //     std::cout << path << std::endl;
  //   }
  //   std::cout << std::endl;
  // }
   return 0;
}  
