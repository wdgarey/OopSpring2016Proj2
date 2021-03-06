/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#include "definitions.h"

#include <memory>
#include <vector>

#include "call.h"
#include "call-queue.h"
#include "call-taker.h"
#include "system-stats.h"
#include "system.h"
#include "server.h"

#ifdef SYSTEM_TRACE
#include <sstream>

#include "trace.h"
#endif

using namespace std;

namespace Project2
{
    System::System()
        :  m_stats(SystemStats())
    {
        this->SetCalls(make_shared<CallQueue>());
        this->SetServers(make_shared<vector<shared_ptr<Server>>>());
    }
    
    System::System(const System& src)
    {
        this->Copy(src);
    }
    
    void System::AddServer(const shared_ptr<Server>& server)
    {
        shared_ptr<vector<shared_ptr<Server>>> servers = this->GetServers();
        
        servers->push_back(server);
    }
    
    SystemStats System::GetStats() const
    {
        return this->m_stats;
    }
    
    System& System::operator =(const System& src)
    {
        if (this != &src)
        {
            this->Copy(src);
        }
        
        return *this;
    }
    
    void System::TakeCall(Call& call)
    {
        shared_ptr<CallQueue> calls = this->GetCalls();
#ifdef SYSTEM_TRACE
        uint32_t id = call.GetId();
        
        stringstream ss;
        
        ss << "System taking call" << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
        call.Queued();
            
        if (calls->TryAdd(call))
        {
            this->SendCallReadyNotification();
        }
    }
    
    void System::ReceiveCallProcessedNotification(Call& call)
    {
        SystemStats stats = this->GetStats();
#ifdef SYSTEM_TRACE
        uint32_t id = call.GetId();
        
        stringstream ss;
        
        ss << "System releasing call " << id << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
        call.Released();
        
        stats.Observe(call);
        
        this->SetStats(stats);
    }
    
    bool System::TryGiveCallForProcessing(Call& call)
    {
        shared_ptr<CallQueue> calls = this->GetCalls();
#ifdef SYSTEM_TRACE
        stringstream ss;
        
        ss << "System trying to retrieve call for processing" << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
        bool success = calls->TryTake(call);
        
        if (success)
        {
#ifdef SYSTEM_TRACE
        uint32_t id = call.GetId();
        
        stringstream ss;
        
        ss << "Call " << id << " retrieved" << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
            call.Serviced();
        }
        else
        {
#ifdef SYSTEM_TRACE
        uint32_t id = call.GetId();
        
        stringstream ss;
        
        ss << "Could not retrieve call" << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
        }
        
        return success;
    }
    
    void System::Copy(const System& src)
    {
        SystemStats stats = src.GetStats();
        shared_ptr<CallQueue> theirCalls = src.GetCalls();
        shared_ptr<vector<shared_ptr<Server>>> theirServers = src.GetServers();
        
        shared_ptr<CallQueue> myCalls = make_shared<CallQueue>(*theirCalls);
        shared_ptr<vector<shared_ptr<Server>>> myServers = make_shared<vector<shared_ptr<Server>>>(*theirServers);
        
        this->SetStats(stats);
        this->SetCalls(myCalls);
        this->SetServers(myServers);
    }
    
    shared_ptr<CallQueue> System::GetCalls() const
    {
        return this->m_calls;
    }
    
    shared_ptr<vector<shared_ptr<Server>>> System::GetServers() const
    {
        return this->m_servers;
    }
    
    void System::SendCallReadyNotification()
    {
        shared_ptr<vector<shared_ptr<Server>>> servers = this->GetServers();
#ifdef SYSTEM_TRACE
        stringstream ss;
        
        ss << "System sending call ready notifications" << ".";
        
        Trace::WriteLineToInst(ss.str());
#endif
        for (int idx = 0; idx < servers->size(); idx++)
        {
            shared_ptr<Server> server = (*servers)[idx];
            
            server->ReceiveCallReadyNotification();
        }
    }
    
    void System::SetCalls(const shared_ptr<CallQueue>& calls)
    {
        this->m_calls = calls;
    }
    
    void System::SetServers(const shared_ptr<vector<shared_ptr<Server>>>& servers)
    {
        this->m_servers = servers;
    }
    
    void System::SetStats(const SystemStats& stats)
    {
        this->m_stats = stats;
    }
}