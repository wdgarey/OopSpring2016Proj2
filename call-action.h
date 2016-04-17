/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#define TRACE

#include <memory>
#include <sstream>

#include "action.h"
#include "rnd-gen.h"
#include "trace.h"
#include "call.h"

namespace Project2
{
    class CallQueued : public Action
    {
    public:
        shared_ptr<Call> call;
        
        virtual void Invoke() override
        {
            call->Queued();
        }
    };
    
    class CallServiced : public Action
    {
    public:
        shared_ptr<Call> call;
        
        virtual void Invoke() override
        {
            call->Serviced();
        }
    };
    
    class CallReleased : public Action
    {
    public:
        shared_ptr<Call> call;
        
        virtual void Invoke() override
        {
            call->Released();
        }
    };
}