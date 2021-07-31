#include <fstream>
#include <iostream>
#include "TemplateReader.hpp"
#include "../../../lodepng/lodepng.h"

std::vector<unsigned char> TemplateReader::m_tmpBuffer;

TemplateReader::TemplateReader(std::string fileName) : 
m_mapTemplate()
{
	unsigned w,h;
	unsigned error = lodepng::decode(m_tmpBuffer, w, h, fileName);
    if(error)
    	std::cout<<"could not open: "<<fileName<<std::endl;
    for(unsigned int index=0;index < m_tmpBuffer.size();index+=4)
        m_mapTemplate.push_back(m_tmpBuffer[index]);
    m_size = Size(w,h);

}
