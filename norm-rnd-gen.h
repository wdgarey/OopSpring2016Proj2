/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#ifndef NORM_RND_GEN_H
#define NORM_RND_GEN_H

#include <memory>
#include <random>

#include "rnd-gen.h"

using namespace std;

namespace Project2
{
    /**
     * A class used to generate numbers with a normal distribution.
     */
    class NormRndGen : public RndGen
    {
    public:
        /**
         * Creates an instance of the NormRndGen class.
         * @param avg The average.
         * @param stdDev The standard deviation.
         * @param seed The seed to use.
         */
        NormRndGen(const double& avg, const double& stdDev,const uint32_t& seed = 1);
        /**
         * The copy constructor of the NormRndGen class.
         * @param src The instance to copy.
         */
        NormRndGen(const NormRndGen& src);
        /**
         * Gets the average.
         * @return The average.
         */
        virtual shared_ptr<normal_distribution<> > GetDist() const;
        /**
         * Gets the next number in the normal distribution sequence.
         * @return The next number.
         */
        virtual double Next() override;
        /**
         * The assignment operator of the NormRndGen class.
         * @param src The instance being assigned to.
         * @return The instance that was assigned.
         */
        virtual NormRndGen& operator =(const NormRndGen& src);
        /**
         * Sets the normal distribution.
         * @param dist The normal distribution.
         */
        virtual void SetDist(const shared_ptr<normal_distribution<> >& dist);
    protected:
        /**
         * Deep copies the given NormRndGen.
         * @param src The instance to copy.
         */
        virtual void Copy(const NormRndGen& src);
    private:
        shared_ptr<normal_distribution<> > m_dist; /// The normal distribution.
    };
}

#endif