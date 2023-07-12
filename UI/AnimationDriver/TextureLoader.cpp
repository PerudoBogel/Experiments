#include "TextureLoader.hpp"
#include "Debug.hpp"

bool TextureLoader::ReadTexture(std::string filename, int id)
{
    bool rVal = false;
	sf::Image image;
    DEBUG_DUMP_CALL();
    DEBUG_DUMP_VAR(filename);

	if (image.loadFromFile(filename.c_str()))
	{
		image.createMaskFromColor(sf::Color(255,255,255));
		m_configMap[id].m_texture.loadFromImage(image);

        auto pixel = image.getPixel(0, 0);
        m_configMap[id].m_frameSize.w = pixel.r + pixel.g + pixel.b;
        pixel = image.getPixel(1, 0);
        m_configMap[id].m_frameSize.w += pixel.r + pixel.g + pixel.b;

        pixel = image.getPixel(2, 0);
        m_configMap[id].m_frameSize.h = pixel.r + pixel.g + pixel.b;
        pixel = image.getPixel(3, 0);
        m_configMap[id].m_frameSize.h += pixel.r + pixel.g + pixel.b;
        
        loadModeInfo(id, image);

        rVal = true;
	}

    return rVal;
}

TextureConfig *TextureLoader::GetTextureConfig(int id)
{
    TextureConfig *rVal = nullptr;
    auto config = m_configMap.find(id);

    if( config != m_configMap.end() )
    {
        rVal = &m_configMap[id];
    }

    return rVal;
}

void TextureLoader::loadModeInfo(int id, sf::Image &image)
{
    TextureMode prevModeId = TextureMode::NONE;
    int altTextureId;
    std::map<int, int> probabilityGrad;
    DEBUG_DUMP_CALL();
    
    for(int y = 1; y < image.getSize().y; y += m_configMap[id].m_frameSize.h)
    {
        auto pixel = image.getPixel(0, y);
        TextureMode modeId = static_cast<TextureMode>(pixel.r + pixel.g + pixel.b);
        pixel = image.getPixel(0, y + 1);
        int probGradient = pixel.r + pixel.g + pixel.b;
        pixel = image.getPixel(0, y + 2);
        int frameCount = pixel.r + pixel.g + pixel.b;

        if(frameCount == 765)
        {
            break;
        }

        auto &pModeInfo = m_configMap[id].m_modeInfo[modeId];
        if(prevModeId != modeId)
        {
            updateAltProbablitities(m_configMap[id].m_modeInfo[prevModeId], probabilityGrad);
            pModeInfo.m_xOffset = 1;
            pModeInfo.m_yOffset = y;
            altTextureId = 0;
            probabilityGrad.clear();
        }
        else
        {
            altTextureId++;
        }

        probabilityGrad[altTextureId] = probGradient;
        pModeInfo.m_altFrameCount[altTextureId] = frameCount;

        prevModeId = modeId;
    }
    
    updateAltProbablitities(m_configMap[id].m_modeInfo[prevModeId], probabilityGrad);
}

void TextureLoader::updateAltProbablitities(TextureConfig::ModeInfo &modeInfo, std::map<int, int> &probabilityGrad)
{
    std::map<int, int> histogram, histoProb;
    DEBUG_DUMP_CALL();

    if(probabilityGrad.size() == 0)
    {
        return;
    }

    for(auto altInfo: probabilityGrad)
    {
        auto pHistEntry = histogram.find(altInfo.second);
        if(pHistEntry == histogram.end())
        {
            histogram[altInfo.second] = 0;
        }
        histogram[altInfo.second]++; 
    }

    int higherOrEqCount = 0;
    int probSum = 0;
    for(auto histIt = histogram.rbegin(); histIt != histogram.rend(); histIt++)
    {
        higherOrEqCount += histIt->second;
        histoProb[histIt->first] = histIt->first/higherOrEqCount;

        probSum += histIt->second * histoProb[histIt->first];
    }

    float probScale = 100.0f / probSum;
    int probOffset = 0;

    for(auto altInfo: probabilityGrad)
    {
        probOffset += histoProb[altInfo.second] * probScale;
        modeInfo.m_altProb[altInfo.first] = probOffset;
        DEBUG_DUMP_VAR(altInfo.first);
        DEBUG_DUMP_VAR(modeInfo.m_altProb[altInfo.first]);
    }
}