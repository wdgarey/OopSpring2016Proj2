/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#ifndef CALL_QUEUE_H
#define CALL_QUEUE_H

#include <cstdint>
#include <memory>
#include <queue>

#include "call.h"

namespace Project2
{
    /**
     * A class used to store calls.
     */
    class CallQueue
    {
    public:
        /**
         * Creates an instance of the CallQueue class.
         * @param capacity The maximum number of calls that can be queued. A value of 0 means no limit.
         */
        CallQueue(const uint32_t& capacity = 0);
        /**
         * The copy constructor of the CallQueue.
         * @param src The instance to copy.
         */
        CallQueue(const CallQueue& src);
        /**
         * Gets the maximum number of calls that can be queued. A value of 0 means no limit.
         * @return The maximum number of calls.
         */
        virtual uint32_t GetCapacity() const;
        /**
         * Indicates whether or not the queue is at capacity.
         * @return True, if the queue is at capacity.
         */
        virtual bool IsAtCapacity() const;
        /**
         * Indicates whether or not the queue is empty.
         * @return True, if the queue is empty.
         */
        virtual bool IsEmpty() const;
        /**
         * The assignment operator of the CallQueue.
         * @param src The instance being assigned to.
         * @return The instance that was assigned.
         */
        virtual CallQueue& operator =(const CallQueue& src);
        /**
         * Sets the maximum number of calls that can be queued. A value of 0 means no limit.
         * @param capacity The maximum number of calls.
         */
        virtual void SetCapacity(const uint32_t& capacity);
        /**
         * Tries to add the given call to the queue.
         * @param call The call to add.
         * @return True, if the call was added successfully.
         */
        virtual bool TryAdd(const Call& call);
        /**
         * Tries to take a call from the queue.
         * @param call The call taken from the queue.
         * @return True, if a call was taken from the queue.
         */
        virtual bool TryTake(Call& call);
    protected:
        /**
         * Deep copies the given CallQueue.
         * @param src The instance to copy.
         */
        virtual void Copy(const CallQueue& src);
        /**
         * Gets the collection of queued calls.
         * @return The collection.
         */
        virtual shared_ptr<priority_queue<Call> > GetCalls() const;
        /**
         * Sets the collection of queued calls.
         * @param calls THe collection.
         */
        virtual void SetCalls(const shared_ptr<priority_queue<Call> > calls);
    private:
        uint32_t m_capacity; /// The maximum number of calls that can be queued.
        shared_ptr<priority_queue<Call> > m_calls; /// The queued calls.
    };
}

#endif