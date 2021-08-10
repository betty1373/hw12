#include "../inc/Split.h"
#include "../inc/Shuffle.h"
#include "../inc/Map.h"


#include "iostream"
#include <sstream>

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

    Split splitter(file_name,map_threads);
    auto sections = splitter.Work();

	Map mapper(file_name);
	auto mapped = mapper.Work(sections,
			[&map = mapper]( std::ifstream &file, 
                                std::ifstream::pos_type beg_pos,
                                std::ifstream::pos_type end_pos,
                                std::shared_ptr<std::vector<std::string>> container) {
			std::size_t sizeBuffer =  end_pos - beg_pos;
			std::string buffer;
			buffer.resize(sizeBuffer);

			try
			{
				std::lock_guard<std::mutex> lk(map.mMutex);
				file.seekg(beg_pos,std::ios::beg);
				file.read(buffer.data(),sizeBuffer);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
			
			std::stringstream stream(buffer);
			std::string str;
			std::cout<<" part "<<beg_pos<<"-"<<end_pos<<"-"<<stream.str()<<std::endl;

			while (std::getline(stream,str,'\n')) {
				for (std::size_t i = 1; i < str.length(); i++) {
					std::cout<< str.substr(0, i)<<std::endl;
            		container->push_back(str.substr(0, i));
          		}
			}
		});
	Shuffle shuffler;
    auto merged = shuffler.Work(mapped);
    for (auto &merge :  merged) {
        std::cout<< merge<<std::endl;
    }
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
