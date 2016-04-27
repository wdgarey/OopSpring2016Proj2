/* 
 * Author: Wesley Garey
 * Date: April 27, 2016
 */

#ifndef CHANCE_GEN_H
#define CHANCE_GEN_H

#include <memory>

#include "uniform-rnd-gen.h"

using namespace std;

namespace Project2
{
    /**
     * A class used to determine whether or not an event has occurred based on
     * probability.
     */
    class ChanceGen
    {
    public:
        /**
         * Creates an instance of the ChanceGen class.
         * @param probability The probability that the event will occur.
         * @param seed The seed to use when determining whether or not the event occurred.
         */
        ChanceGen(const double& probability, const uint32_t& seed = 1);
        /**
         * The copy constructor of the ChanceGen class.
         * @param src The instance to copy.
         */
        ChanceGen(const ChanceGen& src);
        /**
         * Gets the probability that the event will occur.
         * @return The probability.
         */
        virtual double GetProbability() const;
        /**
         * Indicates whether or not the next event occurred.
         * @return True, if the next event occurred.
         */
        virtual bool Next();
        /**
         * The assignment operator of the ChanceGen class.
         * @param src The instance being assigned to.
         * @return The instance that was assigned.
         */
        ChanceGen& operator =(const ChanceGen& src);
        /**
         * Sets the probability that an event will occur.
         * @param probability The probability.
         */
        virtual void SetProbability(const double& probability);
    protected:
        /**
         * Deep copies the given instance.
         * @param src The instance to copy.
         */
        virtual void Copy(const ChanceGen& src);
        /**
         * Gets the random number generator being used.
         * @return The random number generator.
         */
        virtual shared_ptr<UniformRndGen> GetRnd() const;
        /**
         * Sets the random number generator being used.
         * @param rnd The random number generator.
         */
        virtual void SetRnd(const shared_ptr<UniformRndGen>& rnd);
    private:
        double m_probability; /// The probability of the event.
        shared_ptr<UniformRndGen> m_rnd; /// The generator to use.
    };
}

#endif