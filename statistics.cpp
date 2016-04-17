/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#include <cmath>
#include <iostream>

#include "statistics.h"

using namespace std;

namespace Project2
{
    Statistics::Statistics()
        : m_avg(0),
          m_count(0),
          m_max(0),
          m_min(0),
          m_sum(0),
          m_varSum(0)
    { }
    
    double Statistics::ComputeStdDev() const
    {
        double count = this->GetCount();
        double varSum = this->GetVarSum();
        
        double stdDev = sqrt(varSum / count);
        
        return stdDev;
    }
    
    double Statistics::GetAvg() const
    {
        return this->m_avg;
    }
    
    double Statistics::GetCount() const
    {
        return this->m_count;
    }
    
    double Statistics::GetMax() const
    {
        return this->m_max;
    }
    
    double Statistics::GetMin() const
    {
        return this->m_min;
    }
    
    double Statistics::GetSum() const
    {
        return this->m_sum;
    }
    
    void Statistics::Observe(const double& val, const double& weight)
    {
        double max = this->GetMax();
        double min = this->GetMin();
        double sum = this->GetSum();
        double avg = this->GetAvg();
        double count = this->GetCount();
        double varSum = this->GetVarSum();
        
        if (count == 0)
        {
            max = val;
            min = val;
        }
        else
        {
            max = (val > max ? val : max);
            min = (val < min ? val : min);
        }
        
        double newValue = val * weight;
        double newSum = sum + newValue;
        double newCount = count + weight;
        double newAvg = (newSum / newCount);
        double newVarSum = varSum + ((newValue - avg) * (newValue - newAvg));

        this->SetMax(max);
        this->SetMin(min);
        this->SetSum(newSum);
        this->SetAvg(newAvg);
        this->SetCount(newCount);
        this->SetVarSum(newVarSum);
    }
    
    double Statistics::GetVarSum() const
    {
        return this->m_varSum;
    }
    
    void Statistics::SetAvg(const double& avg)
    {
        this->m_avg = avg;
    }
    
    void Statistics::SetCount(const double& count)
    {
        this->m_count = count;
    }
    
    void Statistics::SetMax(const double& max)
    {
        this->m_max = max;
    }
    
    void Statistics::SetMin(const double& min)
    {
        this->m_min;
    }
    
    void Statistics::SetSum(const double& sum)
    {
        this->m_sum = sum;
    }
    
    void Statistics::SetVarSum(const double& varSum)
    {
        this->m_varSum = varSum;
    }
    
    ostream& operator <<(ostream& out, const Statistics& stats)
    {
        double stdDev = stats.ComputeStdDev();
        double max = stats.GetMax();
        double min = stats.GetMin();
        double sum = stats.GetSum();
        double avg = stats.GetAvg();
        double count = stats.GetCount();
        
        out << "Count=" << count << ";";
        out << "Avg=" << avg << ";";
        out << "StdDev=" << stdDev << ";";
        out << "Min=" << min << ";";
        out << "Max=" << max << ";";
        out << "Sum=" << sum << ";";
        
        return out;
    }
}