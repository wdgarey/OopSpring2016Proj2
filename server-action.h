/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#ifndef SERVER_ACTION_H
#define SERVER_ACTION_H

#include "action.h"
#include "server.h"

namespace Project2
{
    /**
     * A class used to invoke server actions.
     */
    class ServerAction : public Action
    {
    public:
        /**
         * An enumeration that describes the possible server action.
         */
        enum Name
        {
            ServiceNextCall = 0 /// The name of the action to service the next call.
        };
        /**
         * Creates an instance of the ServerAction class.
         */
        ServerAction();
        /**
         * Creates an instance of the ServerAction class.
         * @param inst The instance to perform the action with.
         * @param actName The name of the action to perform.
         */
        ServerAction(Server* inst, const Name& actName);
        /**
         * Gets the name of the action to carry out.
         * @return The name of the action.
         */
        virtual Name GetActName() const;
        /**
         * Gets the instance to perform the action with.
         * @return The instance.
         */
        virtual Server* GetInst() const;
        /**
         * Invokes the server action.
         */
        virtual void Invoke() override;
        /**
         * Sets the name of the action to carry out.
         * @param actName The name.
         */
        virtual void SetActName(const Name& actName);
        /**
         * Sets the instance to perform the action with.
         * @param inst The instance.
         */
        virtual void SetInst(Server* inst);
    private:
        Name m_actName; /// The name of the action to invoke.
        Server* m_inst; /// The instance to invoke the action with.
    };
}

#endif