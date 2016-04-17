/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#ifndef SIM_STATS_H
#define SIM_STATS_H

#include <cstdint>
#include <iostream>

#include "call.h"
#include "sim-time-statistics.h"

using namespace std;

namespace Project2
{
    /**
     * A class used to store and compute simulation statistics.
     */
    class SimStats
    {
    public:
        /**
         * Creates an instance of the SimStats class.
         */
        SimStats();
        /**
         * Gets the queued statistics.
         * @return The queued statistics.
         */
        virtual SimTimeStatistics GetQueued() const;
        /**
         * Sets the served statistics.
         * @return The served statistics.
         */
        virtual SimTimeStatistics GetServed() const;
        /**
         * Sets the system statistics.
         * @return The system statistics.
         */
        virtual SimTimeStatistics GetSystem() const;
        /**
         * Gets the total number of calls that were observed.
         * @return The total number of calls.
         */
        virtual double GetTotalCalls() const;
        /**
         * Records a call's measurements to the statistics.
         * @param call The call to observe.
         */
        virtual void Observe(const Call& call);
    protected:
        /**
         * Sets the queued statistics.
         * @param queued The queued statistics.
         */
        virtual void SetQueued(const SimTimeStatistics& queued);
        /**
         * Sets the served statistics.
         * @param served The served statistics.
         */
        virtual void SetServed(const SimTimeStatistics& served);
        /**
         * Sets the system statistics.
         * @param system The system statistics.
         */
        virtual void SetSystem(const SimTimeStatistics& system);
    private:
        SimTimeStatistics m_queued; /// The queued time statistics.
        SimTimeStatistics m_served; /// The served time statistics.
        SimTimeStatistics m_system; /// The system time statistics.
    };
    /**
     * The overloaded output operator of the SimStats class.
     * @param out
     * @param stats
     * @return 
     */
    ostream& operator <<(ostream& out, const SimStats& stats);
}

#endif