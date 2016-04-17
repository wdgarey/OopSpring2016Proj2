/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#include "call.h"
#include "sim-time.h"
#include "sim-stats.h"
#include "statistics.h"

namespace Project2
{
    SimStats::SimStats()
        : m_queued(SimTimeStatistics()),
          m_served(SimTimeStatistics()),
          m_system(SimTimeStatistics())
    { }
    
    SimTimeStatistics SimStats::GetQueued() const
    {
        return this->m_queued;
    }
    
    SimTimeStatistics SimStats::GetServed() const
    {
        return this->m_served;
    }
    
    SimTimeStatistics SimStats::GetSystem() const
    {
        return this->m_system;
    }
    
    double SimStats::GetTotalCalls() const
    {
        SimTimeStatistics queued = this->GetQueued();
        
        return queued.GetCount();
    }
    
    void SimStats::Observe(const Call& call)
    {
        SimTimeStatistics queued = this->GetQueued();
        SimTimeStatistics served = this->GetServed();
        SimTimeStatistics system = this->GetSystem();
        
        SimTime queuedTime = call.ComputeTimeInQueue();
        SimTime servedTime = call.ComputeTimeInService();
        SimTime systemTime = call.ComputeTimeInSystem();
        
        queued.Observe(queuedTime);
        served.Observe(servedTime);
        system.Observe(systemTime);
        
        this->SetQueued(queued);
        this->SetServed(served);
        this->SetSystem(system);
    }
    
    void SimStats::SetQueued(const SimTimeStatistics& queued)
    {
        this->m_queued = queued;
    }
    
    void SimStats::SetServed(const SimTimeStatistics& served)
    {
        this->m_served = served;
    }
    
    void SimStats::SetSystem(const SimTimeStatistics& system)
    {
        this->m_system = system;
    }
    
    ostream& operator <<(ostream& out, const SimStats& stats)
    {
        double calls = stats.GetTotalCalls();
        SimTimeStatistics queued = stats.GetQueued();
        SimTimeStatistics system = stats.GetSystem();
        
        out << "Total Calls=" << calls << ";";
        out << "Avg. Sys. Time=" << system.Avg() << ";";
        out << "Avg. Wait Time=" << queued.Avg() << ";";
        
        return out;
    }
}