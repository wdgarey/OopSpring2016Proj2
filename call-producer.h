/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#ifndef CALL_PRODUCER_H
#define CALL_PRODUCER_H

#include <cstdint>
#include <memory>

#include "call.h"
#include "call-taker.h"
#include "sim-time.h"
#include "exp-rnd-gen.h"

namespace Project2
{
    /**
     * A class used to produce calls and given them to the call taker.
     */
    class CallProducer
    {
        /**
         * A class used to execute scheduled CallProducer actions.
         */
        friend class CallProducerAction;
    public:
        /**
         * Creates an instance of the CallProducer class.
         */
        CallProducer();
        /**
         * Creates an instance of the CallProducer class.
         * @param rnd The random number generator to use.
         * @param taker The object responsible for taking the calls.
         */
        CallProducer(const shared_ptr<ExpRndGen> rnd, const shared_ptr<CallTaker> taker);
        /**
         * The copy constructor of the call producer class.
         * @param src The instance to copy.
         */
        CallProducer(const CallProducer& src);
        /**
         * Gets the random generator used to schedule when calls are produced.
         * @return The random generator.
         */
        virtual shared_ptr<ExpRndGen> GetRnd() const;
        /**
         * Gets the object responsible for taking the producer's calls.
         * @return The object responsible for taking the calls.
         */
        virtual shared_ptr<CallTaker> GetTaker() const;
        /**
         * Indicates whether or not a random number generator has been given.
         * @return True, if a random number generator has been given.
         */
        virtual bool HasRnd() const;
        /**
         * Indicates whether or not the producer has an object to take its calls.
         * @return True, if it has an object to take its calls.
         */
        virtual bool HasTaker() const;
        /**
         * Indicates whether or not the call producer is producing calls.
         * @return True, if the call producer is producing calls.
         */
        virtual bool IsProducing() const;
        /**
         * The assignment operator of the CallProducer class.
         * @param src The instance being assigned to.
         * @return The instance that was assigned.
         */
        virtual CallProducer& operator =(const CallProducer& src);
        /**
         * Sets the random generator used to schedule when calls are produced.
         * @param rnd The random generator.
         */
        virtual void SetRnd(const shared_ptr<ExpRndGen> rnd);
        /**
         * Sets the object responsible for taking the producer's calls.
         * @param taker The object responsible for taking calls.
         */
        virtual void SetTaker(const shared_ptr<CallTaker> taker);
        /**
         * Starts producing calls.
         * @param start The time at which to start producing calls.
         * @param stop The time at which to stop producing calls. A time of 0 indicates that calls should be produced indefinitely.
         */
        virtual void Start(const SimTime& start = SimTime(), const SimTime& stop = SimTime());
        /**
         * Stops producing calls.
         */
        virtual void Stop();
    protected:
        /**
         * Deep copies the given instance.
         * @param src The instance to copy.
         */
        virtual void Copy(const CallProducer& src);
        /**
         * Gets the ID that will be assigned to the next call that is produced.
         * @return The ID.
         */
        virtual uint32_t GetNextSeq() const;
        /**
         * Gets the flag that indicates if the call producer is producing calls.
         * @return The flag.
         */
        virtual bool GetProducing() const;
        /**
         * Gets the time at which the producer is to start producing calls.
         * @return The simulation time.
         */
        virtual SimTime GetStart() const;
        /**
         * Gets the time at which the producer should stop producing calls.
         * @return The simulation time.
         */
        virtual SimTime GetStop() const;
        /**
         * Gets the next sequence number and increases the current value by one.
         * @return The next sequence number.
         */
        virtual uint32_t NextSeq();
        /**
         * Produces a call.
         */
        virtual void Produce();
        /**
         * Schedules the next time at which a call will be produced.
         */
        virtual void ScheduleNextProd();
        /**
         * Sets the ID that will be assigned to the next call that is produced.
         * @param nextSeq The ID.
         */
        virtual void SetNextSeq(const uint32_t& nextSeq);
        /**
         * Sets the flag that indicates if the call producer is producing calls.
         * @param producing The flag.
         */
        virtual void SetProducing(const bool& producing);
        /**
         * Sets the time at which the producer is to start producing calls.
         * @param start The simulation time.
         */
        virtual void SetStart(const SimTime& start);
        /**
         * Sets the time at which the producer should stop producing calls.
         * @param stop The simulation time.
         */
        virtual void SetStop(const SimTime& stop);
    private:
        uint32_t m_nextSeq; /// The ID that will be assigned to the next call that is produced.
        bool m_producing; /// A flag that indicates if the producer is producing calls.
        shared_ptr<ExpRndGen> m_rnd; /// The random generator to use to schedule when to produce calls.
        SimTime m_start; /// The time at which to stop producing calls.
        SimTime m_stop; /// The time at which to start producing calls.
        shared_ptr<CallTaker> m_taker; /// The object responsible for taking calls.
    };
}

#endif