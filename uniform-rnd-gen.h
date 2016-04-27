/* 
 * Author: Wesley Garey
 * Date: April 27, 2016
 */

#include <memory>

#include "rnd-gen.h"

#ifndef UNIFORM_RND_GEN_H
#define UNIFORM_RND_GEN_H

using namespace std;

namespace Project2
{
     /**
     * A class used to generate numbers with a uniform distribution.
     */
    class UniformRndGen : public RndGen
    {
    public:
        /**
         * Creates an instance of the NormRndGen class.
         * @param a The minimum value (inclusive).
         * @param b The max value (exclusive).
         * @param seed The seed to use.
         */
        UniformRndGen(const double& a, const double& b, const uint32_t& seed = 1);
        /**
         * The copy constructor of the UniformRndGen class.
         * @param src The instance to copy.
         */
        UniformRndGen(const UniformRndGen& src);
        /**
         * Gets the uniform distribution.
         * @return The distribution.
         */
        virtual shared_ptr<uniform_real_distribution<> > GetDist() const;
        /**
         * Gets the next number in the uniform distribution sequence.
         * @return The next number.
         */
        virtual double Next() override;
        /**
         * The assignment operator of the UniformRndGen class.
         * @param src The instance being assigned to.
         * @return The instance that was assigned.
         */
        virtual UniformRndGen& operator =(const UniformRndGen& src);
        /**
         * Sets the uniform distribution.
         * @param dist The uniform distribution.
         */
        virtual void SetDist(const shared_ptr<uniform_real_distribution<> >& dist);
    protected:
        /**
         * Deep copies the given UniformRndGen.
         * @param src The instance to copy.
         */
        virtual void Copy(const UniformRndGen& src);
    private:
        shared_ptr<uniform_real_distribution<> > m_dist; /// The uniform distribution.
    };
}

#endif