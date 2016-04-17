/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#include "sim-time.h"
#include "sim-time-statistics.h"
#include "statistics.h"

namespace Project2
{
    SimTimeStatistics::SimTimeStatistics()
        : Statistics()
    { }
    
    SimTime SimTimeStatistics::StdDev() const
    {
        double stdDev = Statistics::ComputeStdDev();
        
        return SimTime(stdDev);
    }
    
    SimTime SimTimeStatistics::Avg() const
    {
         double avg = Statistics::GetAvg();
         
         return SimTime(avg);
    }
    
    SimTime SimTimeStatistics::Max() const
    {
        double max = Statistics::GetMax();
        
        return SimTime(max);
    }
    
    SimTime SimTimeStatistics::Min() const
    {
         double min = Statistics::GetMin();
         
         return SimTime(min);
    }
    
    SimTime SimTimeStatistics::Sum() const
    {
        double sum = Statistics::GetSum();
        
        return SimTime(sum);
    }
    
    void SimTimeStatistics::Observe(const SimTime& val, const double& weight)
    {
        double seconds = val.GetSeconds();
        
         Statistics::Observe(seconds);
    }
}