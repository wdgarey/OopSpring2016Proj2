/* 
 * Author: Wesley Garey
 * Date: April 16, 2016
 */

#define TRACE

#ifdef TRACE
#include <sstream>
#endif

#include "call.h"
#include "sim-time.h"
#include "simulator.h"
#include "trace.h"

namespace Project2
{
    Call::Call()
        : m_id (0),
          m_queued(SimTime()),
          m_released(SimTime()),
          m_subscriber(false),
          m_served(SimTime())
            
    { }
    
    Call::Call(const uint32_t& id, const bool& subscriber)
        : m_queued(SimTime()),
          m_released(SimTime()),
          m_served(SimTime())
    {
        this->SetId(id);
        this->SetSubscriber(subscriber);
    }
    
    SimTime Call::ComputeTimeInQueue() const
    {
        SimTime queued = this->GetQueued();
        SimTime served = this->GetServed();
        
        SimTime timeInQueue = served - queued;
        
        return timeInQueue;
    }
    
    SimTime Call::ComputeTimeInService() const
    {
        SimTime released = this->GetReleased();
        SimTime served = this->GetServed();
        
        SimTime timeInService = released - served;
        
        return timeInService;
    }
    
    SimTime Call::ComputeTimeInSystem() const
    {
        SimTime queued = this->GetQueued();
        SimTime released = this->GetReleased();
        
        SimTime timeInSystem = released - queued;
        
        return timeInSystem;
    }
    
    bool Call::HasPriorityOver(const Call& other) const
    {
        bool higherPriority = false;
        bool sameLvl = (this->IsSubscriber() && other.IsSubscriber())
                        || (!this->IsSubscriber() && !other.IsSubscriber());
        
        if (sameLvl)
        {
            SimTime myArrival = this->GetQueued();
            SimTime theirArrival = other.GetQueued();
                
            higherPriority = (theirArrival > myArrival);
        }
        else if (this->IsSubscriber())
        {
            higherPriority = true;
        }
        
        return higherPriority;
    }
    
    bool Call::IsSubscriber() const
    {
        bool isSub = this->GetSubscriber();
        
        return isSub;
    }
    
    bool Call::operator <(const Call& call) const
    {
        bool less = !this->HasPriorityOver(call);
        
        return less;
    }
    
    void Call::Queued()
    {
        SimTime queued = Simulator::Now();
#ifdef TRACE
        uint32_t id = this->GetId();
        stringstream ss;
        
        ss << "Call " << id << " arrived at " << queued << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
        this->SetQueued(queued);
    }
    
    void Call::Released()
    {
        SimTime released = Simulator::Now();
#ifdef TRACE
        uint32_t id = this->GetId();
        stringstream ss;
        
        ss << "Call " << id << " left system at " << released << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif        
        this->SetReleased(released);
    }
    
    void Call::Serviced()
    {
        SimTime served = Simulator::Now();
#ifdef TRACE
        uint32_t id = this->GetId();
        stringstream ss;
        
        ss << "Call " << id << " began service at " << served << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif        
        this->SetServed(served);
    }
    
    uint32_t Call::GetId() const
    {
        return this->m_id;
    }
    
    void Call::SetId(const uint32_t& id)
    {
        this->m_id = id;
    }
    
    SimTime Call::GetQueued() const
    {
        return this->m_queued;
    }
    
    void Call::SetQueued(const SimTime& time)
    {
        this->m_queued = time;
    }
    
    SimTime Call::GetReleased() const
    {
        return this->m_released;
    }
    
    void Call::SetReleased(const SimTime& time)
    {
        this->m_released = time;
    }
    
    SimTime Call::GetServed() const
    {
        return this->m_served;
    }
    
    void Call::SetServed(const SimTime& time)
    {
        this->m_served = time;
    }
    
    bool Call::GetSubscriber() const
    {
        return this->m_subscriber;
    }
    
    void Call::SetSubscriber(const bool& subscriber)
    {
        this->m_subscriber = subscriber;
    }
}