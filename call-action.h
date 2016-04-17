/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#include "action.h"
#include "call.h"

namespace Project2
{
    class CallAction : public Action
    {
    public:
        Call call;
        
        virtual void Invoke() override
        {
            call.Queued();
        }
    };
}