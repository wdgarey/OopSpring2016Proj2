/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#include <memory>

#include "call-producer-action.h"
#include "call-producer.h"

namespace Project2
{
    CallProducerAction::CallProducerAction()
        : m_actName(CallProducerAction::Name::Produce),
          m_inst(0)
    { }
        
    CallProducerAction::CallProducerAction(CallProducer* inst, const Name& actName)
    {
        this->SetInst(inst);
        this->SetActName(actName);
    }
    
    CallProducerAction::Name CallProducerAction::GetActName() const
    {
        return this->m_actName;
    }
    
    CallProducer* CallProducerAction::GetInst() const
    {
        return this->m_inst;
    }
    
    void CallProducerAction::Invoke()
    {
        CallProducer* inst = this->GetInst();
        
        inst->Produce();
    }
    
    void CallProducerAction::SetActName(const Name& actName)
    {
        this->m_actName = actName;
    }
    
    void CallProducerAction::SetInst(CallProducer* inst)
    {
        this->m_inst = inst;
    }
}