#pragma once

class FrameTick
{
public:
    
    FrameTick(FrameTick &pObj) = delete;
    FrameTick(FrameTick &&pObj) = delete;

    static FrameTick *GetIntance()
    {
        if(m_pInstance == nullptr)
        {
            m_pInstance = new FrameTick();
        }
        return m_pInstance;
    }

    static void Terminate()
    {
        if(m_pInstance != nullptr)
        {
            delete m_pInstance;
        }
    }

    void Update(int timeBusy_ms, int limitFps = 60)
    {
        m_fps = limitFps;
        m_tick++;

		while((m_timeLeft = (1000.0 / m_fps) - timeBusy_ms) < 0)
        {
            m_fps--;
        }
    }

    double GetTimeToSleep_ms()
    {
        return m_timeLeft;
    }

    int GetFps()
    {
        return m_fps;
    }

    int GetTick()
    {
        return m_tick;
    }

private:
    int m_fps, m_tick;
    double m_timeLeft;
    static FrameTick *m_pInstance;
    
    FrameTick(){};
};