#include "../inc/Split.h"

Split::Split(std::string fileName,std::size_t mapThreads) :
    m_file(fileName),
    m_mapThreads(mapThreads) {}

std::vector<std::iostream::pos_type> Split::Work() {
    if (!m_file.good()) {
        throw std::ifstream::failure("ReadFile error");
    }
    m_file.seekg(0,std::ios::end);
    long file_EndPos = m_file.tellg();
    long section_Size = file_EndPos / m_mapThreads;

    m_file.seekg(section_Size,std::ios::beg);
    return GetSections(section_Size,file_EndPos); 
}

std::vector<std::iostream::pos_type> Split::GetSections(long sectionSize, long fileEndPos) {
    std::vector<std::iostream::pos_type> sections;
    sections.reserve(m_mapThreads);

    long currPos = sectionSize;

    while ((currPos < fileEndPos) && (currPos >=0))
    {
        auto buffer = '\0';
        m_file.seekg(currPos,std::ios::beg);
        
        while (buffer!='\n' && !m_file.fail()) {
            m_file.read(&buffer,1);
        } 

        currPos = m_file.tellg();
        if (currPos >= 0) {
            sections.push_back(currPos);
            currPos += sectionSize;
        }  
    }    
    sections.push_back(fileEndPos);
    return sections;
}
