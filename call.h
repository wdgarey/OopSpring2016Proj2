/* 
 * Author: Wesley Garey
 * Date: April 16, 2016
 */

#ifndef CALL_H
#define CALL_H

#include <cstdint>

#include "sim-time.h"

namespace Project2
{
    /**
     * A class used to represent a call to the tech support center.
     */
    class Call
    {
    public:
        /**
         * Creates an instance of the Call class.
         */
        Call();
        /**
         * Creates an instance of the Call class.
         * @param id The ID of the call.
         * @param subscriber The flag that indicates if the caller is a subscriber.
         */
        Call(const uint32_t& id, const bool& subscriber);
        /**
         * Computes the total amount of time spent in the queue.
         * @return The amount of time spent in the queue.
         */
        virtual SimTime ComputeTimeInQueue() const;
        /**
         * Computes the total amount of time spent being served.
         * @return The amount of time spent being served.
         */
        virtual SimTime ComputeTimeInService() const ;
        /**
         * Computes the total amount of time spent in the system.
         * @return The amount of time spent in system.
         */
        virtual SimTime ComputeTimeInSystem() const;
        /**
         * Gets the ID of the call.
         * @return The ID.
         */
        virtual uint32_t GetId() const;
        /**
         * Gets the time at which the call was placed in the system's queue.
         * @return The simulation time.
         */
        virtual SimTime GetQueued() const;
        /**
         * Gets the time that indicates when the call left the system.
         * @return The simulation time.
         */
        virtual SimTime GetReleased() const;
        /**
         * Gets the time at which the call began to get service.
         * @return The simulation time.
         */
        virtual SimTime GetServed() const;
        /**
         * Indicates whether or not this call has priority over the given call.
         * @param other The other caller.
         * @return True, if this call has priority over the given call.
         */
        virtual bool HasPriorityOver(const Call& other) const;
        /**
         * Indicates whether or not the caller has a subscription.
         * @return True, if the caller has a subscription.
         */
        virtual bool IsSubscriber() const;
        /**
         * Indicates whether or not this call has less priority than the given call.
         * @param The other call.
         * @return True, if this call has less priority.
         */
        virtual bool operator <(const Call& other) const;
        /**
         * Indicates the call has arrived a the queue.
         */
        virtual void Queued();
        /**
         * Indicates that the call has been released from the system.
         */
        virtual void Released();
        /**
         * Indicates that the called is being serviced.
         */
        virtual void Serviced();
    protected:

        /**
         * Sets the ID of the call.
         * @param id The ID.
         */
        virtual void SetId(const uint32_t& id);
        /**
         * Sets the time at which the call was placed in the system's queue.
         * @param time The simulation time.
         */
        virtual void SetQueued(const SimTime& time);
        /**
         * Sets the time that indicates when the call left the system.
         * @param time The simulation time.
         */
        virtual void SetReleased(const SimTime& time);
        /**
         * Sets the time at which the call began to get service.
         * @param time The simulation time.
         */
        virtual void SetServed(const SimTime& time);
        /**
         * Gets the flag that indicates if the caller is a subscriber.
         * @return The flag
         */
        virtual bool GetSubscriber() const;
        /**
         * Sets the flag that indicates if the caller is a subscriber.
         * @param subscriber The flag.
         */
        virtual void SetSubscriber(const bool& subscriber);
    private:
        uint32_t m_id; /// The ID of the call.        
        SimTime m_queued; /// The time at which the call entered the queue.
        SimTime m_released; /// The time at which the call left the system.
        bool m_subscriber; /// A flag that indicates if the caller is a subscriber.
        SimTime m_served; /// The time at which the call received service.
    };
}

#endif