#pragma once
#include <string>
#include <vector>
#include "Size.hpp"

class TemplateReader
{
public:
    TemplateReader() = delete;
    TemplateReader(std::string fileName);

    inline const std::vector<unsigned char>& getTemplate() { return m_mapTemplate; }
    inline const Size& getSize() { return m_size; }

private:
    std::vector<unsigned char> m_mapTemplate;
    Size m_size;

    static std::vector<unsigned char> m_tmpBuffer;
};
