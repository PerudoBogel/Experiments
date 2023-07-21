#include "CsvReader.hpp"
#include <fstream>
#include <iostream>

constexpr char CSVDelimiter = ';';
constexpr int loopSafetyLimit = 10000;

namespace
{
    bool isHexInString(std::string &string)
    {
        bool rVal = false;
        for(auto it = string.begin(); it < string.end() ; it++)
        {
            if(*it == '"')
                *it = ' ';

            if(*it == 'x' && *(it -1) == '0')
            {
                rVal = true;
                *it = ' ';
                *(it - 1) = ' ';
            }
        }
        return rVal;
    }
}

CsvReader::CsvReader(std::string filename, int rowsOffset, int colsOffset)
{
   m_filename = filename;
   m_rowsOffset = rowsOffset;
   m_colsOffset = colsOffset;
};

bool CsvReader::ReadFile()
{
    std::fstream file;

    file.open(m_filename);
    if(!file.is_open())
        return false;
    
    m_csvContent.clear();
    
    bool eofFound = false;
    for(int rowNo = 0; rowNo < loopSafetyLimit && !eofFound; rowNo++)
    {
        std::string line;
        int readCh;

        for(int j = 0; j < loopSafetyLimit; j++)
        {
            readCh = file.get();
            line.push_back(static_cast<char>(readCh));
            
            if(readCh == -1)
            {
                eofFound = true;
                break;
            }
            if(readCh == '\n')
                break;
        }
        
        if(rowNo < m_rowsOffset)
            continue;
        if(line == "")
            break;
        
        m_csvContent.push_back(std::vector<int>());

        for(int columnNo = 0; columnNo < loopSafetyLimit; columnNo++)
        {
            int value = 0;
            int delimiterPosition = line.find(CSVDelimiter);
            std::string sValue = line.substr(0, delimiterPosition);
            line = line.substr(delimiterPosition + 1,line.size());

            if(columnNo >= m_colsOffset)
            {   
                if(sValue != "")
                {
                    try
                    {
                        if(isHexInString(sValue))
                            value = std::stoi(sValue,0,16);
                        else
                            value = std::stoi(sValue);
                    }
                    catch(const std::exception& e)
                    {
                        value = 0;
                    }
                }

                m_csvContent.back().push_back(value);
            }

            if(delimiterPosition == -1)
                break;
        }
    }
    file.close();
    return true;
};