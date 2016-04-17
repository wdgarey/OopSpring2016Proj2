/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#define TRACE

#include <memory>
#include <sstream>

#include "action.h"
#include "call-taker.h"
#include "rnd-gen.h"
#include "sim-stats.h"
#include "trace.h"
#include "call.h"

namespace Project2
{
    class Taker : public CallTaker
    {
    public:
        shared_ptr<SimStats> stats;
        
        virtual void TakeCall(const Call& call) override
        {
            stats->Observe(call);
        }
        
    };
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