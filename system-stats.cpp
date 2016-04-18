/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#include "call.h"
#include "sim-time.h"
#include "system-stats.h"
#include "statistics.h"

namespace Project2
{
    SystemStats::SystemStats()
        : m_queued(SimTimeStatistics()),
          m_served(SimTimeStatistics()),
          m_system(SimTimeStatistics())
    { }
    
    SimTimeStatistics SystemStats::GetQueued() const
    {
        return this->m_queued;
    }
    
    SimTimeStatistics SystemStats::GetServed() const
    {
        return this->m_served;
    }
    
    SimTimeStatistics SystemStats::GetSystem() const
    {
        return this->m_system;
    }
    
    double SystemStats::GetTotalCalls() const
    {
        SimTimeStatistics queued = this->GetQueued();
        
        return queued.GetCount();
    }
    
    void SystemStats::Observe(const Call& call)
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
    
    void SystemStats::SetQueued(const SimTimeStatistics& queued)
    {
        this->m_queued = queued;
    }
    
    void SystemStats::SetServed(const SimTimeStatistics& served)
    {
        this->m_served = served;
    }
    
    void SystemStats::SetSystem(const SimTimeStatistics& system)
    {
        this->m_system = system;
    }
    
    ostream& operator <<(ostream& out, const SystemStats& stats)
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