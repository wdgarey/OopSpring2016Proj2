/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#include <cstdint>
#include <memory>

#include "call.h"
#include "rnd-gen.h"
#include "sim-time.h"
#include "simulator.h"
#include "system.h"
#include "server.h"
#include "server-action.h"

namespace Project2
{
    Server::Server()
        : m_currCall(0),
          m_id(0),
          m_owner(0),
          m_rnd(0)
    { }
    
    Server::Server(const uint32_t& id, System* owner, shared_ptr<NormRndGen> rnd)
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
    
    System* Server::GetOwner() const
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
    
    void Server::SetOwner(System* owner)
    {
        this->m_owner = owner;
    }
    
    void Server::SetRnd(const shared_ptr<NormRndGen> rnd)
    {
        this->m_rnd = rnd;
    }
    
    void Server::ReceiveCallReadyNotification()
    {
        if (!this->IsBusy())
        {
            this->ServiceNextCall();
        }
    }
    
    void Server::Copy(const Server& src)
    {
        uint32_t id = src.GetId();
        System* owner = src.GetOwner();
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
            System* owner = this->GetOwner();
            shared_ptr<Call> currCall = this->GetCurrCall();
            
            owner->ReceiveCallProcessedNotification(*currCall);
        }
    }
    
    void Server::ReleaseCall()
    {
        this->SetCurrCall(0);
    }
    
    bool Server::TryRequestNextCall()
    {
        Call call;
        bool newCall = false;
        System* owner = this->GetOwner();
        
        
        if (owner->TryGiveCallForProcessing(call))
        {
            this->SetCurrCall(make_shared<Call>(call));
        }
        
        return newCall;
    }
    
    void Server::ScheduleNextService()
    {
        SimTime increase(1);
        SimTime curr = Simulator::Now();
        shared_ptr<ServerAction> action = make_shared<ServerAction>(this, ServerAction::Name::ServiceNextCall);
        
        if (this->HasRnd())
        {
            shared_ptr<NormRndGen> rnd = this->GetRnd();
            
            double interval = rnd->Next();
            
            increase.SetSeconds(interval);
        }
        
        SimTime nextTime = curr + increase;
        
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
    
    void Server::SetCurrCall(const shared_ptr<Call> currCall)
    {
        this->m_currCall = currCall;
    }
}
    