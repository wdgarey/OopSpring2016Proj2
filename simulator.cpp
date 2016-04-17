/* 
 * Author: Wesley Garey
 * Date: April 16, 2016
 */

#define TRACE

#include <cstdint>
#include <functional>
#include <memory>
#include <stdexcept>
#include <vector>

#ifdef TRACE
#include <sstream>
#endif

#include "action.h"
#include "event.h"
#include "sim-time.h"
#include "simulator.h"
#include "trace.h"

namespace Project2
{
    void Simulator::Halt()
    {
        if (s_instance.IsRunning())
        {
            s_instance.Stop();
        }
    }
    
    SimTime Simulator::Now()
    {
        SimTime now = s_instance.GetCurrTime();
        
        return now;
    }
    
    void Simulator::Run(const SimTime& stopTime)
    {
        if (s_instance.IsRunning())
        {
            Simulator::Halt();
        }
        
        s_instance.SetStopTime(stopTime);
        
        s_instance.Start();
    }
    
    uint32_t Simulator::Schedule(const SimTime& time, const shared_ptr<Action> action)
    {
        uint32_t eventId = s_instance.AddEvent(time, action);
        
        return eventId;
    }
    
    Simulator Simulator::s_instance = Simulator();
    
    Simulator::Simulator()
        : m_nextEventId(1),
          m_running (false),
          m_sched (0),
          m_stopTime (SimTime())
    {
        shared_ptr<priority_queue<Event,vector<Event>,greater<Event>>> sched(new priority_queue<Event,vector<Event>,greater<Event> >());
        
        this->SetSched(sched);
    }
    
    Simulator::Simulator(const Simulator& src)
    {
        this->Copy(src);
    }
    
    uint32_t Simulator::AddEvent(const SimTime& time, const shared_ptr<Action> action)
    {
        uint32_t eventId = this->NextEventId();
        Event event(eventId, time, action);
        
        shared_ptr<priority_queue<Event,vector<Event>,greater<Event>>> sched = this->GetSched();
        
        sched->push(event);
        
#ifdef TRACE
        stringstream ss;
        
        ss << "Event " << eventId << " scheduled for time : " << time;
        
        Trace::WriteLineToInst(ss.str());
#endif
        
        return eventId;
    }
    
    void Simulator::Copy(const Simulator& src)
    {
        uint32_t nextEventId = src.GetNextEventId();
        bool running = src.GetRunning();
        SimTime stopTime = src.GetStopTime();
        shared_ptr<priority_queue<Event,vector<Event>,greater<Event>>> theirSched = src.GetSched();
        
        shared_ptr<priority_queue<Event,vector<Event>,greater<Event>>> mySched = make_shared<priority_queue<Event,vector<Event>,greater<Event>>>(*theirSched);
        
        this->SetNextEventId(nextEventId);
        this->SetRunning(running);
        this->SetStopTime(stopTime);
        this->SetSched(mySched);
    }
    
    SimTime Simulator::GetCurrTime() const
    {
        SimTime currTime = this->GetCurr();
        
        return currTime;
    }
    
    bool Simulator::IsRunning() const
    {
        bool isRunning = this->GetRunning();
        
        return isRunning;
    }
    
    Simulator& Simulator::operator =(const Simulator& src)
    {
        if (this != &src)
        {
            this->Copy(src);
        }
        
        return *this;
    }
    
    void Simulator::Start()
    {
        this->SetRunning(true);
        
        this->Run();
    }
    
    void Simulator::Stop()
    {
        this->SetRunning(false);
    }
    
    SimTime Simulator::GetCurr() const
    {
        return this->m_curr;
    }
    
    uint32_t Simulator::GetNextEventId() const
    {
        return this->m_nextEventId;
    }
    
    bool Simulator::GetRunning() const
    {
        return this->m_running;
    }
    
    shared_ptr<priority_queue<Event,vector<Event>,greater<Event>>> Simulator::GetSched() const
    {
        return this->m_sched;
    }
    
    SimTime Simulator::GetStopTime() const
    {
        return this->m_stopTime;
    }
    
    uint32_t Simulator::NextEventId()
    {
        uint32_t nextId = this->GetNextEventId();
        
        this->SetNextEventId(nextId + 1);
        
        return nextId;
    }
    
    void Simulator::Run()
    {
        shared_ptr<priority_queue<Event,vector<Event>,greater<Event>>> sched = this->GetSched();
        
        while (this->IsRunning())
        {
            if (!sched->empty())
            {
                SimTime stopTime = this->GetStopTime();
                SimTime currTime = this->GetCurrTime();

                if (stopTime.GetSeconds() == 0 || stopTime > currTime)
                {
                    Event event = sched->top();
                    SimTime eventTime = event.GetTime();
                    
                    if (currTime > eventTime)
                    {
                        throw runtime_error("Missed event!");
                    }
                    
                    this->SetCurr(eventTime);
#ifdef TRACE
        stringstream ss;
        
        ss << "Executing event " << event.GetId() << " at " << eventTime;
        
        Trace::WriteLineToInst(ss.str());
#endif                    
                    event.InvokeAction();

                    sched->pop();
                }
                else
                {
                    this->Stop();
#ifdef TRACE
                    Trace::WriteLineToInst("Stopping simulation because stop time was exceeded.");
#endif
                }
            }
            else
            {
                this->Stop();
#ifdef TRACE
                Trace::WriteLineToInst("Stopping simulation b/c event queue is empty.");
#endif
            }
        }
    }
    
    void Simulator::SetCurr(const SimTime& time)
    {
        this->m_curr = time;
    }
    
    void Simulator::SetNextEventId(const uint32_t& nextId)
    {
        this->m_nextEventId = nextId;
    }
    
    void Simulator::SetRunning(const bool& running)
    {
        this->m_running = running;
    }
    
    void Simulator::SetSched(const shared_ptr<priority_queue<Event,vector<Event>,greater<Event> > >& sched)
    {
        this->m_sched = sched;
    }
    
    void Simulator::SetStopTime(const SimTime& stopTime)
    {
        this->m_stopTime = stopTime;
    }
}