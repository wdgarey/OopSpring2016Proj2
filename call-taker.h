/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#ifndef CALL_TAKER_H
#define CALL_TAKER_H

#include "call.h"

namespace Project2
{
    /**
     * An interface for an object that can take calls.
     */
    class CallTaker
    {
    public:
        /**
         * Takes a call.
         * @param call The call to take.
         */
        virtual void TakeCall(Call& call) = 0;
    };
}

#endif
