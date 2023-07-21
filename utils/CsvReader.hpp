#pragma once
#include <string>
#include <vector>

class CsvReader
{
public:
    CsvReader(std::string filename, int rowsOffset, int colsOffset);

    bool ReadFile();
    void Clear(){m_csvContent.clear();}
    std::vector<std::vector<int>> &GetContent(){return m_csvContent;}
private:

    std::vector<std::vector<int>> m_csvContent;
    std::string m_filename;
    int m_rowsOffset, m_colsOffset;
};