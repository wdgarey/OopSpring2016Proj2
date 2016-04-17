/* 
 * Author: Wesley Garey
 * Date: April 16, 2016
 */

#include <cstdlib>

#include "action.h"
#include "event.h"
#include "sim-time.h"

namespace Project2
{
    Event::Event()
        : m_action(0),
          m_id(0),
          m_time(SimTime())
    { }
    
    Event::Event(const uint32_t& id, const SimTime& time, const shared_ptr<Action> action)
    {
        this->SetId(id);
        this->SetTime(time);
        this->SetAction(action);
    }
    
    void Event::InvokeAction()
    {
        shared_ptr<Action> act = this->GetAction();
        
        act->Invoke();
    }
    
    bool Event::IsLaterThan(const Event& other) const
    {
        SimTime myTime = this->GetTime();
        SimTime theirTime = other.GetTime();
        
        bool laterThan = myTime > theirTime;
        
        return laterThan;
    }
    
    bool Event::operator >(const Event& other) const
    {
        bool greater = this->IsLaterThan(other);
        
        return greater;
    }
    
    shared_ptr<Action> Event::GetAction() const
    {
        return this->m_action;
    }
    
    void Event::SetAction(const shared_ptr<Action> action)
    {
        this->m_action = action;
    }
    
    uint32_t Event::GetId() const
    {
        return this->m_id;
    }
    
    void Event::SetId(const uint32_t& id)
    {
        this->m_id = id;
    }
    
    SimTime Event::GetTime() const
    {
        return this->m_time;
    }
    
    void Event::SetTime(const SimTime& time)
    {
        this->m_time = time;
    }
}