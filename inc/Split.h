#ifndef Split_H
#define Split_H
#include <fstream>
#include <vector>

class Split {
public:
    Split(std::string fileName,std::size_t maspThreads);
    std::vector<std::iostream::pos_type> Work();

private:
    std::vector<std::iostream::pos_type> GetSections(long sectionSize,long fileEndPos);
    std::ifstream m_file;
    std::size_t m_mapThreads;
};
#endif