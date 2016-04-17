/* 
 * Author: Wesley Garey
 * Date: April 16, 2016
 */

#define TRACE

#include <functional>
#include <memory>
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
        SimTime now = s_instance.GetCurrEventTime();
        
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
    
    void Simulator::Schedule(const Event& event)
    {
        s_instance.Add(event);
    }
    
    Simulator Simulator::s_instance = Simulator();
    
    Simulator::Simulator()
        : m_running (false),
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
    
    void Simulator::Add(const Event& event)
    {
        shared_ptr<priority_queue<Event,vector<Event>,greater<Event>>> sched = this->GetSched();
        
        sched->push(event);
        
#ifdef TRACE
        stringstream ss;
        
        ss << "Event " << event.GetId() << " scheduled for time : " << event.GetTime();
        
        Trace::WriteLineToInst(ss.str());
#endif
    }
    
    void Simulator::Copy(const Simulator& src)
    {
        bool running = src.GetRunning();
        SimTime stopTime = src.GetStopTime();
        shared_ptr<priority_queue<Event,vector<Event>,greater<Event>>> theirSched = src.GetSched();
        
        shared_ptr<priority_queue<Event,vector<Event>,greater<Event>>> mySched(new priority_queue<Event,vector<Event>,greater<Event> >(*theirSched));
        
        this->SetRunning(running);
        this->SetStopTime(stopTime);
        this->SetSched(mySched);
    }
    
    SimTime Simulator::GetCurrEventTime() const
    {
        SimTime currTime;
        shared_ptr<priority_queue<Event,vector<Event>,greater<Event>>> sched = this->GetSched();
        
        if (!sched->empty())
        {
            const Event& nextEvent = sched->top();
        
            currTime = nextEvent.GetTime();
        }
        
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
            shared_ptr<priority_queue<Event,vector<Event>,greater<Event>>> sched = this->GetSched();
            
            sched.reset();
            
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
    
    void Simulator::Run()
    {
        shared_ptr<priority_queue<Event,vector<Event>,greater<Event>>> sched = this->GetSched();
        
        while (this->IsRunning())
        {
            if (!sched->empty())
            {
                SimTime stopTime = this->GetStopTime();
                SimTime currTime = this->GetCurrEventTime();

                if (stopTime.GetSeconds() == 0 || stopTime > currTime)
                {
                    Event event = sched->top();
#ifdef TRACE
        stringstream ss;
        
        ss << "Executing event " << event.GetId() << " at " << currTime;
        
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
    
    bool Simulator::GetRunning() const
    {
        return this->m_running;
    }
    
    void Simulator::SetRunning(const bool& running)
    {
        this->m_running = running;
    }
    
    shared_ptr<priority_queue<Event,vector<Event>,greater<Event>>> Simulator::GetSched() const
    {
        return this->m_sched;
    }
    
    void Simulator::SetSched(const shared_ptr<priority_queue<Event,vector<Event>,greater<Event> > >& sched)
    {
        this->m_sched = sched;
    }
    
    SimTime Simulator::GetStopTime() const
    {
        return this->m_stopTime;
    }
    
    void Simulator::SetStopTime(const SimTime& stopTime)
    {
        this->m_stopTime = stopTime;
    }
}