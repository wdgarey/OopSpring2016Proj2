/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#ifndef RND_GEN_H
#define RND_GEN_H

#include <memory>
#include <random>

using namespace std;

namespace Project2
{
    /**
     * A class used to generate random numbers.
     */
    class RndGen
    {
    public:
        /**
         * Creates an instance of the RndGen class.
         */
        RndGen();
        /**
         * The copy constructor of the RndGen class.
         * @param src The instance to copy.
         */
        RndGen(const RndGen& src);
        /**
         * Gets the engine be used to generate numbers.
         * @return The engine.
         */
        virtual shared_ptr<default_random_engine> GetEngine() const;
        /**
         * Generates a random number and returns it.
         * @return The randomly generated number.
         */
        virtual double Next() = 0;
        /**
         * The assignment operator of the RndGen class.
         * @param src The instance being assigned to.
         * @return The instance that was assigned.
         */
        virtual RndGen& operator =(const RndGen& src);
        /**
         * Sets the engine to use when generating numbers.
         * @param engine The engine.
         */
        virtual void SetEngine(const shared_ptr<default_random_engine> engine);
    protected:
        /**
         * Deep copies the given instance.
         * @param src The instance to copy.
         */
        virtual void Copy(const RndGen& src);
    private:
        shared_ptr<default_random_engine> m_engine; /// The default random engine.
    };
}

#endif