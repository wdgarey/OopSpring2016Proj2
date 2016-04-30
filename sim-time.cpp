/* 
 * Author: Wesley Garey
 * Date: April 16, 2016
 */

#include <cstdint>
#include <iostream>

#include "sim-time.h"

namespace Project2
{
    SimTime::SimTime()
        : m_seconds (0)
    { }
    
    SimTime::SimTime(const double& seconds)
        : m_seconds (0)
    {
        this->SetSeconds(seconds);
    }
    
    SimTime::SimTime(const uint32_t& hours, const uint32_t& minutes, const uint32_t& seconds)
        : m_seconds (0)
    {
        this->From(hours, minutes, seconds);
    }
    
    void SimTime::From(const uint32_t& hours, const uint32_t& minutes, const uint32_t& seconds)
    {
        double totalSeconds = 0.0;
        
        totalSeconds += hours * 3600;
        totalSeconds += minutes * 60;
        totalSeconds += seconds;
        
        this->SetSeconds(totalSeconds);
    }
    
    double SimTime::GetSeconds() const
    {
        return this->m_seconds;
    }
    
    bool SimTime::IsBefore(const SimTime& other) const
    {
        double mySeconds = this->GetSeconds();
        double theirSeconds = other.GetSeconds();
        
        bool laterThan = mySeconds < theirSeconds;
        
        return laterThan;
    }
    
    bool SimTime::operator <(const SimTime& other) const
    {
		bool less = this->IsBefore(other); 
        
        return less;
    }
    
    SimTime SimTime::operator -(const SimTime& other) const
    {
        double diff = 0;
        double mySeconds = this->GetSeconds();
        double theirSeconds = other.GetSeconds();
        
        if (mySeconds > theirSeconds)
        {
            diff = mySeconds - theirSeconds;
        }
        else
        {
            diff = theirSeconds - mySeconds;
        }
        
        return SimTime(diff);
    }
    
    SimTime SimTime::operator +(const SimTime& other) const
    {
        double mySeconds = this->GetSeconds();
        double theirSeconds = other.GetSeconds();
        
        double sum = mySeconds + theirSeconds;
        
        return SimTime(sum);
    }
    
    void SimTime::SetSeconds(const double& seconds)
    {
        this->m_seconds = seconds;
    }
    
    void SimTime::To(uint32_t& hours, uint32_t& minutes, uint32_t& seconds) const
    {
        uint32_t secondsLeft = (uint32_t)(this->GetSeconds());
        
        hours = secondsLeft / 3600;
        
        secondsLeft %= 3600;
        
        minutes = secondsLeft / 60;
        
        secondsLeft %= 60;
        
        seconds = secondsLeft;
    }
    
    ostream& operator <<(ostream& out, const SimTime& time)
    {
        uint32_t hours;
        uint32_t minutes;
        uint32_t seconds;
        
        time.To(hours, minutes, seconds);
        
        out << hours << ":" << minutes << ":" << seconds;
        
        return out;
    }
}