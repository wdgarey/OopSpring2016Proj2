/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#ifndef SIM_TIME_STATISTICS_H
#define SIM_TIME_STATISTICS_H

#include "sim-time.h"
#include "statistics.h"

namespace Project2
{
    /**
     * A class used to represent simulation time statistics.
     */
    class SimTimeStatistics : public Statistics
    {
    public:
        /**
         * Creates an instance of the SimTimeStatistics class.
         */
        SimTimeStatistics();
        /**
         * Computes the standard deviation.
         * @return The standard deviation.
         */
        virtual SimTime StdDev() const;
        /**
         * Gets the average of value of all observed values.
         * @return The average.
         */
        virtual SimTime Avg() const;
        /**
         * Gets the largest value that was observed.
         * @return The largest value.
         */
        virtual SimTime Max() const;
        /**
         * Gets the smallest value that was observed.
         * @return The smallest value.
         */
        virtual SimTime Min() const;
        /**
         * Gets the sum of all the values that were observed.
         * @return The sum.
         */
        virtual SimTime Sum() const;
        /**
         * Includes the value in the statistics.
         * @param val The value to include.
         * @parm weight The weight of the value.
         */
        virtual void Observe(const SimTime& val, const double& weight = 1.0);
    };
}

#endif