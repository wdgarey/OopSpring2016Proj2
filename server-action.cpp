/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#include "action.h"
#include "server-action.h"
#include "server.h"

namespace Project2
{
    ServerAction::ServerAction()
    : m_actName(ServerAction::Name::ServiceNextCall),
      m_inst(0)
    { }
    
    ServerAction::ServerAction( Server* inst, const Name& actName)
    {
        this->SetActName(actName);
        this->SetInst(inst);
    }
    
    ServerAction::Name ServerAction::GetActName() const
    {
        return this->m_actName;
    }
    
    Server* ServerAction::GetInst() const
    {
        return this->m_inst;
    }
    
    void ServerAction::Invoke()
    {
        Server* inst = this->GetInst();
        ServerAction::Name name = this->GetActName();
        
        if (name == ServerAction::Name::ServiceNextCall)
        {
            inst->ServiceNextCall();
        }
    }
    
    void ServerAction::SetActName(const Name& actName)
    {
        this->m_actName = actName;
    }
    
    void ServerAction::SetInst(Server* inst)
    {
        this->m_inst = inst;
    }
}