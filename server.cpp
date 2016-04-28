/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#include "definitions.h"

#include <cstdint>
#include <memory>

#include "call.h"
#include "class-action.h"
#include "rnd-gen.h"
#include "sim-time.h"
#include "simulator.h"
#include "system.h"
#include "server.h"

#ifdef SERVER_TRACE
#include <sstream>

#include "trace.h"
#endif

using namespace std;

namespace Project2
{
    Server::Server()
        : m_currCall(0),
          m_id(0),
          m_rnd(0)
    { }
    
    Server::Server(const uint32_t& id, const weak_ptr<System>& owner, const shared_ptr<NormRndGen>& rnd)
        : m_currCall(0)
    {
        this->SetId(id);
        this->SetOwner(owner);
        this->SetRnd(rnd);
    }
    
    Server::Server(const Server& src)
    {
        this->Copy(src);
    }
    
    uint32_t Server::GetId() const
    {
        return this->m_id;
    }
    
    weak_ptr<System> Server::GetOwner() const
    {
        return this->m_owner;
    }
    
    shared_ptr<NormRndGen> Server::GetRnd() const
    {
        return this->m_rnd;
    }
    
    bool Server::HasRnd() const
    {
        shared_ptr<NormRndGen> rnd = this->GetRnd();
        
        bool hasRnd = (rnd != 0);
        
        return hasRnd;
    }
    
    bool Server::IsBusy() const
    {
        shared_ptr<Call> currCall = this->GetCurrCall();
        
        bool isBusy = (currCall != 0);
        
        return isBusy;
    }
    
    Server& Server::operator =(const Server& src)
    {
        if (this != &src)
        {
            this->Copy(src);
        }
        
        return *this;
    }
    
    void Server::SetId(const uint32_t& id)
    {
        this->m_id = id;
    }
    
    void Server::SetOwner(const weak_ptr<System>& owner)
    {
        this->m_owner = owner;
    }
    
    void Server::SetRnd(const shared_ptr<NormRndGen>& rnd)
    {
        this->m_rnd = rnd;
    }
    
    void Server::ReceiveCallReadyNotification()
    {
#ifdef SERVER_TRACE
        uint32_t id = this->GetId();
        
        stringstream ss;
        
        ss << "Server " << id << " received call ready notification" << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
        if (!this->IsBusy())
        {
#ifdef SERVER_TRACE
        uint32_t id = this->GetId();
        
        stringstream ss;
        
        ss << "Server " << id << " is not busy" << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
            this->ServiceNextCall();
        }
        else
        {
#ifdef SERVER_TRACE
        uint32_t id = this->GetId();
        
        stringstream ss;
        
        ss << "Server " << id << " is busy" << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
        }
    }
    
    void Server::Copy(const Server& src)
    {
        uint32_t id = src.GetId();
        weak_ptr<System> owner = src.GetOwner();
        shared_ptr<Call> theirCall = src.GetCurrCall();
        shared_ptr<NormRndGen> theirRnd = src.GetRnd();
        
        shared_ptr<Call> myCall = make_shared<Call>(*theirCall);
        shared_ptr<NormRndGen> myRnd = make_shared<NormRndGen>(*theirRnd);
        
        this->SetId(id);
        this->SetOwner(owner);
        this->SetCurrCall(myCall);
        this->SetRnd(myRnd);
    }
    
    shared_ptr<Call> Server::GetCurrCall() const
    {
        return this->m_currCall;
    }
    
    void Server::SendCallProcessedNotification()
    {
        if (this->IsBusy())
        {
#ifdef SERVER_TRACE
        uint32_t id = this->GetId();
        
        stringstream ss;
        
        ss << "Server " << id << " sending call processed notification" << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
            shared_ptr<System> owner = this->GetOwner().lock();
            shared_ptr<Call> currCall = this->GetCurrCall();
            
            owner->ReceiveCallProcessedNotification(*currCall);
        }
        else
        {
#ifdef SERVER_TRACE
        uint32_t id = this->GetId();
        
        stringstream ss;
        
        ss << "***Server " << id << " could not send notification because it is not busy***" << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
        }
    }
    
    void Server::ReleaseCall()
    {
    #ifdef SERVER_TRACE
        uint32_t id = this->GetId();
        
        stringstream ss;
        
        ss << "Server " << id << " releasing call" << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
        this->SetCurrCall(0);
    }
    
    bool Server::TryRequestNextCall()
    {
        Call call;
        bool newCall = false;
        shared_ptr<System> owner = this->GetOwner().lock();
#ifdef SERVER_TRACE
        uint32_t id = this->GetId();
        
        stringstream ss;
        
        ss << "Server " << id << " requesting another call" << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif        
        if (owner->TryGiveCallForProcessing(call))
        {
#ifdef SERVER_TRACE
        uint32_t id = this->GetId();
        
        stringstream ss;
        
        ss << "Server " << id << " has received another call" << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
            this->SetCurrCall(make_shared<Call>(call));
            
            newCall = true;
        }
        else
        {
#ifdef SERVER_TRACE
        uint32_t id = this->GetId();
        
        stringstream ss;
        
        ss << "No calls available" << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
        }
        
        return newCall;
    }
    
    void Server::ScheduleNextService()
    {
        SimTime increase(1);
        SimTime curr = Simulator::Now();
        shared_ptr<Server> me = this->shared_from_this();
        shared_ptr<Action> action = make_shared<ClassAction<Server> >(me, &Server::ServiceNextCall);
        
        if (this->HasRnd())
        {
            shared_ptr<NormRndGen> rnd = this->GetRnd();
            
            double interval = rnd->Next();
            
            increase.SetSeconds(interval);
        }
        
        SimTime nextTime = curr + increase;
#ifdef SERVER_TRACE
        uint32_t id = this->GetId();
        
        stringstream ss;
        
        ss << "Server " << id << " scheduling next service time for " << nextTime << ".";
        ss << " " << increase << " from current time" << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
        
        Simulator::Schedule(nextTime, action);
    }
    
    void Server::ServiceNextCall()
    {
        if (this->IsBusy())
        {
            this->SendCallProcessedNotification();
            
            this->ReleaseCall();
        }
        
        if (this->TryRequestNextCall())
        {
            this->ScheduleNextService();
        }
    }
    
    void Server::SetCurrCall(const shared_ptr<Call>& currCall)
    {
        this->m_currCall = currCall;
    }
}
    