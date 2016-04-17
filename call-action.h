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

namespace Project2
{
    class CallAction : public Action
    {
    public:
        shared_ptr<RndGen> generator;
        
        virtual void Invoke() override
        {
            double rndNum = generator->Next();
#ifdef TRACE
            stringstream ss;
            
            ss << "Generated: " << rndNum;
            
            Trace::WriteLineToInst(ss.str());
#endif
            
        }
    };
}