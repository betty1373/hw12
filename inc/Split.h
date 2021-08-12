#ifndef Split_H
#define Split_H
#include <fstream>
#include <vector>

class Split {
public:
    Split(std::string fileName,std::size_t numThreads);
    std::vector<std::iostream::pos_type> Work();

private:
    Split()=delete;
    std::vector<std::iostream::pos_type> GetSections(long sectionSize,long end_pos);
    std::ifstream m_file;
    std::size_t m_Threads;
};
#endif