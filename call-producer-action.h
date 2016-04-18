/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#ifndef CALL_PRODUCER_ACTION_H
#define CALL_PRODUCER_ACTION_H

#include <memory>

#include "action.h"
#include "call-producer.h"

namespace Project2
{
    /**
     * A class used to invoke actions for the CallProducer class.
     */
    class CallProducerAction : public Action
    {
    public:
        /**
         * Enumerator for selecting which action to invoke.
         */
        enum Name
        {
            Produce = 0 /// Represents the "produce" action.
        };
        /**
         * Creates an instance of the CallProducerAction class.
         */
        CallProducerAction();
        /**
         * Creates an instance of the CallProducerAction class.
         * @param inst The instance to invoke the action for.
         * @param actName The name of the action to invoke. 
         */
        CallProducerAction(CallProducer* inst, const Name& actName);
        /**
         * Gets the name of the action to invoke.
         * @return The name.
         */
        virtual Name GetActName() const;
        /**
         * Sets the instance to invoke the action for.
         * @return The instance.
         */
        virtual CallProducer* GetInst() const;
        /**
         * Invokes the selected action.
         */
        virtual void Invoke() override;
        /**
         * Sets the name of the action to invoke.
         * @param actName The name of the action.
         */
        virtual void SetActName(const Name& actName);
        /**
         * Sets the instance to invoke the action for.
         * @param inst The instance.
         */
        virtual void SetInst(CallProducer* inst);
    private:
        Name m_actName; /// The name of the action to invoke.
        CallProducer* m_inst; /// The instance to invoke the action for.
    };
}

#endif