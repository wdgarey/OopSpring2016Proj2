/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#include <cstdint>
#include <memory>
#include <queue>

#include "call-queue.h"
#include "call.h"

namespace Project2
{
    CallQueue::CallQueue(const uint32_t& capacity)
    {
        this->SetCapacity(capacity);
        this->SetCalls(make_shared<priority_queue<Call> >());
    }
    
    CallQueue::CallQueue(const CallQueue& src)
    {
        this->Copy(src);
    }
    
    uint32_t CallQueue::GetCapacity() const
    {
        return this->m_capacity;
    }
    
    bool CallQueue::IsAtCapacity() const
    {
        bool isAtCap = false;
        uint32_t capacity = this->GetCapacity();
        shared_ptr<priority_queue<Call> > calls = this->GetCalls();
        
        if ((capacity != 0) && (calls->size() >= capacity))
        {
            isAtCap = true;
        }
        
        return isAtCap;
    }
    
    bool CallQueue::IsEmpty() const
    {
        shared_ptr<priority_queue<Call> > calls = this->GetCalls();
        
        bool isEmpty = calls->empty();
        
        return isEmpty;
    }
    
    CallQueue& CallQueue::operator =(const CallQueue& src)
    {
        if (this != &src)
        {
            this->Copy(src);
        }
        
        return *this;
    }
    
    void CallQueue::SetCapacity(const uint32_t& capacity)
    {
        this->m_capacity = capacity;
    }
    
    bool CallQueue::TryAdd(const Call& call)
    {
        bool added = false;
        
        if (!this->IsAtCapacity())
        {
            shared_ptr<priority_queue<Call> > calls  = this->GetCalls();
            
            calls->push(call);
            
            added = true;
        }
        
        return added;
    }
    
    bool CallQueue::TryTake(Call& call)
    {
        bool taken = false;
        
        if (!this->IsEmpty())
        {
            shared_ptr<priority_queue<Call> > calls = this->GetCalls();
            
            call = Call(calls->top());
            
            taken = true;
        }
        
        return taken;
    }
    
    void CallQueue::Copy(const CallQueue& src)
    {
        uint32_t capacity = src.GetCapacity();
        shared_ptr<priority_queue<Call> > theirCalls = src.GetCalls();
        
        shared_ptr<priority_queue<Call> > myCalls = make_shared<priority_queue<Call> >(*theirCalls);
        
        this->SetCapacity(capacity);
        this->SetCalls(myCalls);
    }
    
    shared_ptr<priority_queue<Call> > CallQueue::GetCalls() const
    {
        return this->m_calls;
    }
    
    void CallQueue::SetCalls(const shared_ptr<priority_queue<Call> > calls)
    {
        this->m_calls = calls;
    }
}