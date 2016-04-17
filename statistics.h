/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */


#ifndef STATISTICS_H
#define STATISTICS_H

#include <iostream>

using namespace std;

namespace Project2
{
    /**
     * A class used to store and compute basic statistics.
     */
    class Statistics
    {
    public:
        /**
         * Creates an instance of the Statistics class.
         */
        Statistics();
        /**
         * Computes the standard deviation.
         * @return The standard deviation.
         */
        virtual double ComputeStdDev() const;
        /**
         * Gets the average of value of all observed values.
         * @return The average.
         */
        virtual double GetAvg() const;
        /**
         * Gets the total number of values that were observed.
         * @return The total number of values.
         */
        virtual double GetCount() const;
        /**
         * Gets the largest value that was observed.
         * @return The largest value.
         */
        virtual double GetMax() const;
        /**
         * Gets the smallest value that was observed.
         * @return The smallest value.
         */
        virtual double GetMin() const;
        /**
         * Gets the sum of all the values that were observed.
         * @return The sum.
         */
        virtual double GetSum() const;
        /**
         * Includes the value in the statistics.
         * @param val The value to include.
         * @parm weight The weight of the value.
         */
        virtual void Observe(const double& val, const double& weight = 1.0);
    protected:
        /**
         * Gets the variance total of all observed values.
         * @return 
         */
        virtual double GetVarSum() const;
        /**
         * Sets the average value of all observed points.
         * @param avg The average.
         */
        virtual void SetAvg(const double& avg);
        /**
         * Sets the total number of values that were observed.
         * @param count The total number of values.
         */
        virtual void SetCount(const double& count);
        /**
         * Sets the largest value that was observed.
         * @param max The largest value.
         */
        virtual void SetMax(const double& max);
        /**
         * Sets the smallest value that was observed.
         * @param min The smallest value.
         */
        virtual void SetMin(const double& min);
        /**
         * Sets the sum of all the values that were observed.
         * @param sum The sum.
         */
        virtual void SetSum(const double& sum);
        /**
         * Sets the variance total of all observed values.
         * @param varSum The variance total.
         */
        virtual void SetVarSum(const double& varSum);
    private:
        double m_avg; /// The average value of all observed values.
        double m_count; /// The total number of values that were observed.
        double m_max; /// The largest value of that was observed.
        double m_min; /// The smallest value that was observed.
        double m_sum; /// The sum of all the values that were observed.
        double m_varSum; /// The variance total of all observed values.
    };
    /**
     * The output operator of the Statistics class.
     * @param out The output stream to write to.
     * @param stats The statistics to write to the stream.
     * @return The stream that was written to.
     */
    ostream& operator <<(ostream& out, const Statistics& stats);
}

#endif