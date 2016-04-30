/* 
 * Author: Wesley Garey
 * Date: April 16, 2016
 */

#ifndef EVENT_H
#define EVENT_H

#include <cstdint>
#include <memory>

#include "action.h"
#include "sim-time.h"

namespace Project2
{
    /**
     * A class that represents a scheduled event.
     */
    class Event
    {
    public:
        /**
         * Creates an instance of the Event class.
         */
        Event();
        /**
         * Creates an instance of the Event class.
         * @param id The ID of the event.
         * @param time The time at which the action should be invoked.
         * @param action The action to invoke.
         */
        Event(const uint32_t& id, const SimTime& time, const shared_ptr<Action>& action);
        /**
         * Invokes the action.
         */
        virtual void InvokeAction();
        /**
         * Indicates whether or not this even occurs before the given event. 
         * @param other The given event.
         * @return True, if this event should occur before the given event.
         */
        virtual bool IsBefore(const Event& other) const;
        /**
         * Indicates if this event should occur before the given event.
         * @param other The given event.
         * @return True, if this event should occur before the given.
         */
        virtual bool operator <(const Event& other) const;
        /**
         * Gets the action that should be invoked.
         * @return The action.
         */
        virtual shared_ptr<Action> GetAction() const;
        /**
         * Gets the ID of the event.
         * @return The ID.
         */
        virtual uint32_t GetId() const;
        /**
         * Gets the time at which the action should be invoked.
         * @return The simulation time.
         */
        virtual SimTime GetTime() const;
    protected:
        /**
         * Sets the action that should be invoked.
         * @param action The action.
         */
        virtual void SetAction(const shared_ptr<Action>& action);
        /**
         * Sets the ID of the event.
         * @param id The ID.
         */
        virtual void SetId(const uint32_t& id);
        /**
         * Sets the time at which the action should be invoked.
         * @param time The simulation time.
         */
        virtual void SetTime(const SimTime& time);
    private:
        shared_ptr<Action> m_action; /// The action to carry out.
        uint32_t m_id; /// The ID of the event.
        SimTime m_time; /// The time at which the action should be carried out.
    };
}

#endif