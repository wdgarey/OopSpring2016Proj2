/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#ifndef EXP_RND_GEN_H
#define EXP_RND_GEN_H

#include <cstdlib>
#include <memory>
#include <random>

#include "rnd-gen.h"

using namespace std;

namespace Project2
{
    /**
     * A class used to generate numbers with an exponential distribution.
     */
    class ExpRndGen : public RndGen
    {
    public:
        /**
         * Creates an instance of the ExpRndGen class.
         * @param bound The bound to apply the lambda to.
         * @param lambda The lambda to use.
         */
        ExpRndGen(const uint32_t& bound, const double& lambda);
        /**
         * The copy constructor of the ExpRndGen class.
         * @param src The instance to copy.
         */
        ExpRndGen(const ExpRndGen& src);
        /**
         * Gets the bound that the lambda is applied to.
         * @return The bound.
         */
        virtual uint32_t GetBound() const;
        /**
         * Gets the exponential distribution.
         * @return The exponential distribution.
         */
        virtual shared_ptr<exponential_distribution<> > GetDist() const;
        /**
         * Gets the next number in the exponential distribution sequence.
         * @return The next number.
         */
        virtual uint32_t Next() override;
        /**
         * The assignment operator of the ExpRndGen class.
         * @param src The instance being assigned to.
         * @return The instance that was assigned.
         */
        virtual ExpRndGen& operator =(const ExpRndGen& src);
        /**
         * Sets the bound that the lambda is applied to.
         * @param bound The bound.
         */
        virtual void SetBound(const uint32_t& bound);
        /**
         * Sets the exponential distribution.
         * @param dist The exponential distribution.
         */
        virtual void SetDist(const shared_ptr<exponential_distribution<> > dist);
    protected:
        /**
         * Deep copies the given ExpRndGen.
         * @param src The instance to copy.
         */
        virtual void Copy(const ExpRndGen& src);
    private:
        uint32_t m_bound; /// The bound to use when applying lambda.
        shared_ptr<exponential_distribution<> > m_dist; /// The exponential distribution.
    };
}

#endif