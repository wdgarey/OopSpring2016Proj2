/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#include <cstdint>
#include <memory>

#include "call-producer-action.h"
#include "call-producer.h"
#include "call-taker.h"
#include "call.h"
#include "exp-rnd-gen.h"
#include "sim-time.h"
#include "simulator.h"

namespace Project2
{
    CallProducer::CallProducer()
        : m_nextSeq(1),
          m_producing(false),
          m_rnd(0),
          m_start(SimTime()),
          m_stop(SimTime()),
          m_taker(0)
    { }
    
    CallProducer::CallProducer(const shared_ptr<ExpRndGen> rnd, const shared_ptr<CallTaker> taker)
        : m_nextSeq(1),
          m_producing(false),
          m_start(SimTime()),
          m_stop(SimTime())
    {
        this->SetRnd(rnd);
        this->SetTaker(taker);
    }
    
    CallProducer::CallProducer(const CallProducer& src)
    {
        this->Copy(src);
    }
    
    shared_ptr<ExpRndGen> CallProducer::GetRnd() const
    {
        return this->m_rnd;
    }
    
    shared_ptr<CallTaker> CallProducer::GetTaker() const
    {
        return this->m_taker;
    }
    
    bool CallProducer::HasRnd() const
    {
        shared_ptr<ExpRndGen> rnd = this->GetRnd();
        
        bool hasRnd = (rnd != 0);
        
        return hasRnd;
    }
    
    bool CallProducer::HasTaker() const
    {
        shared_ptr<CallTaker> taker = this->GetTaker();
        
        bool hasTaker = (taker != 0);
        
        return hasTaker;
    }
    
    bool CallProducer::IsProducing() const
    {
        bool isProducing = this->GetProducing();
        
        return isProducing;
    }
    
    CallProducer& CallProducer::operator =(const CallProducer& src)
    {
        if (this != &src)
        {
            this->Copy(src);
        }
        
        return *this;
    }

    void CallProducer::SetRnd(const shared_ptr<ExpRndGen> rnd)
    {
        this->m_rnd = rnd;
    }
    
    void CallProducer::SetTaker(const shared_ptr<CallTaker> taker)
    {
        this->m_taker = taker;
    }
    
    void CallProducer::Start(const SimTime& start, const SimTime& stop)
    {
        if (!this->IsProducing())
        {
            this->SetProducing(true);
        
            this->SetStart(start);
            this->SetStop(stop);
        
            this->ScheduleNextProd();
        }
    }
    
    void CallProducer::Stop()
    {
        if (this->IsProducing())
        {
            this->SetProducing(false);
        }
    }
    
    void CallProducer::Copy(const CallProducer& src)
    {
        uint32_t nextSeq = src.GetNextSeq();
        bool producing = src.GetProducing();
        shared_ptr<ExpRndGen> theirRnd = src.GetRnd();
        SimTime start = src.GetStart();
        SimTime stop = src.GetStop();
        shared_ptr<CallTaker> taker = src.GetTaker();
        
        shared_ptr<ExpRndGen> myRnd = make_shared<ExpRndGen>(*theirRnd);
        
        this->SetNextSeq(nextSeq);
        this->SetProducing(producing);
        this->SetRnd(myRnd);
        this->SetStart(start);
        this->SetStop(stop);
        this->SetTaker(taker);
    }
    
    uint32_t CallProducer::GetNextSeq() const
    {
        return this->m_nextSeq;
    }
    
    bool CallProducer::GetProducing() const
    {
        return this->m_producing;
    }
    
    SimTime CallProducer::GetStart() const
    {
        return this->m_start;
    }
    
    SimTime CallProducer::GetStop() const
    {
        return this->m_stop;
    }
        
    uint32_t CallProducer::NextSeq()
    {
        uint32_t nextSeq = this->GetNextSeq();
        
        this->SetNextSeq(nextSeq + 1);
        
        return nextSeq;
    }
    
    void CallProducer::Produce()
    {
        if (this->HasTaker())
        {
            uint32_t id = this->GetNextSeq();
            shared_ptr<CallTaker> taker = this->GetTaker();
            
            Call call(id, true);
            
            call.Queued();
            call.Serviced();
            call.Released();
            
            taker->TakeCall(call);
        }
        
        this->ScheduleNextProd();
    }
    
    void CallProducer::ScheduleNextProd()
    {
        SimTime curr = Simulator::Now();
        SimTime stop = this->GetStop();
        
        if (stop.GetSeconds() > 0.0 && curr > stop)
        {
            this->Stop();
        }
        else
        {
            SimTime nextTime;
            shared_ptr<Action> action = make_shared<CallProducerAction>(this, CallProducerAction::Name::Produce);
            SimTime start = this->GetStart();
            
            if (start > curr)
            {
                nextTime = start;
            }
            else if (this->HasRnd())
            {
                shared_ptr<ExpRndGen> rnd = this->GetRnd();
                
                double step = rnd->Next();
                
                nextTime = curr + SimTime (step);
            }
            else
            {
                nextTime = curr + SimTime(1);
            }
            
            Simulator::Schedule(nextTime, action);
        }
    }
    
    void CallProducer::SetNextSeq(const uint32_t& nextSeq)
    {
        this->m_nextSeq = nextSeq;
    }
    
    void CallProducer::SetProducing(const bool& producing)
    {
        this->m_producing = producing;
    }
    
    void CallProducer::SetStart(const SimTime& start)
    {
        this->m_start = start;
    }
    
    void CallProducer::SetStop(const SimTime& stop)
    {
        this->m_stop = stop;
    }
}