/* 
 * Author: Wesley Garey
 * Date: April 16, 2016
 */

#ifndef ACTION_H
#define ACTION_H

namespace Project2
{
    /**
     * A class that represents an action that can be carried out.
     */
    class Action
    {
    public:
        /**
         * Invokes the action so that it is carried out.
         */
        virtual void Invoke() = 0;
    };
}

#endif