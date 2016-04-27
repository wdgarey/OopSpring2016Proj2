/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

//#define TRACE

#include <cstdint>
#include <memory>

#include "call-producer.h"
#include "call-taker.h"
#include "call.h"
#include "class-action.h"
#include "exp-rnd-gen.h"
#include "sim-time.h"
#include "simulator.h"

#ifdef TRACE
#include <sstream>
#include "trace.h"
#endif 

namespace Project2
{
    CallProducer::CallProducer()
        : m_chanceGen(0),
          m_nextSeq(1),
          m_producing(false),
          m_productionRnd(0),
          m_start(SimTime()),
          m_stop(SimTime()),
          m_taker(0)
    { }
    
    CallProducer::CallProducer(const shared_ptr<ChanceGen>& chanceGen, const shared_ptr<ExpRndGen>& rnd, const shared_ptr<CallTaker>& taker)
        : m_nextSeq(1),
          m_producing(false),
          m_start(SimTime()),
          m_stop(SimTime())
    {
        this->SetChanceGen(chanceGen);
        this->SetRnd(rnd);
        this->SetTaker(taker);
    }
    
    CallProducer::CallProducer(const CallProducer& src)
    {
        this->Copy(src);
    }
    
    shared_ptr<ChanceGen> CallProducer::GetChanceGen() const
    {
        return this->m_chanceGen;
    }
    
    shared_ptr<ExpRndGen> CallProducer::GetProductionRnd() const
    {
        return this->m_productionRnd;
    }
    
    shared_ptr<CallTaker> CallProducer::GetTaker() const
    {
        return this->m_taker;
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
    
    void CallProducer::SetChanceGen(const shared_ptr<ChanceGen>& chanceGen)
    {
        this->m_chanceGen = chanceGen;
    }

    void CallProducer::SetRnd(const shared_ptr<ExpRndGen>& rnd)
    {
        this->m_productionRnd = rnd;
    }
    
    void CallProducer::SetTaker(const shared_ptr<CallTaker>& taker)
    {
        this->m_taker = taker;
    }
    
    void CallProducer::Start(const SimTime& start, const SimTime& stop)
    {
        if (!this->IsProducing())
        {
#ifdef TRACE
        stringstream ss;
        
        ss << "Call producer " << "starting to produce calls" << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
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
#ifdef TRACE
        stringstream ss;
        
        ss << "Call producer " << "stopping" << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
            this->SetProducing(false);
        }
    }
    
    void CallProducer::Copy(const CallProducer& src)
    {
        shared_ptr<ChanceGen> theirChanceGen = src.GetChanceGen();
        uint32_t nextSeq = src.GetNextSeq();
        bool producing = src.GetProducing();
        shared_ptr<ExpRndGen> theirRnd = src.GetProductionRnd();
        SimTime start = src.GetStart();
        SimTime stop = src.GetStop();
        shared_ptr<CallTaker> taker = src.GetTaker();
        
        shared_ptr<ChanceGen> myChanceGen = make_shared<ChanceGen>(*theirChanceGen);
        shared_ptr<ExpRndGen> myRnd = make_shared<ExpRndGen>(*theirRnd);
        
        this->SetChanceGen(myChanceGen);
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
        uint32_t id = this->NextSeq();
        shared_ptr<ChanceGen> chanceGen = this->GetChanceGen();
        shared_ptr<CallTaker> taker = this->GetTaker();
#ifdef TRACE
        stringstream ss;
        
        ss << "Call producer " << "producing call " << id << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
        bool subscriber = chanceGen->Next();
        
        Call call(id, subscriber);

        taker->TakeCall(call);
        
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
            shared_ptr<CallProducer> me = this->shared_from_this();
            shared_ptr<Action> action = make_shared<ClassAction<CallProducer> >(me, &CallProducer::Produce);
            SimTime start = this->GetStart();
            
            if (start > curr)
            {
                nextTime = start;
            }
            else
            {
                shared_ptr<ExpRndGen> rnd = this->GetProductionRnd();
                
                double step = rnd->Next();
                
                nextTime = curr + SimTime (step);
            }
            
            Simulator::Schedule(nextTime, action);
#ifdef TRACE
        stringstream ss;
        
        ss << "Call producer " << "next production at " << nextTime << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
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