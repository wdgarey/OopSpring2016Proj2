/* 
 * Author: Wesley Garey
 * Date: April 16, 2016
 */

#ifndef SIM_TIME_H
#define SIM_TIME_H

#include <cstdint>
#include <iostream>

using namespace std;

namespace Project2
{
    /**
     * A class that represents simulation time.
     */
    class SimTime
    {
    public:
        /**
         * Creates an instance of the SimTime class.
         */
        SimTime();
        /**
         * Creates an instance of the SimTime class.
         * @param seconds The number of simulation seconds.
         */
        SimTime(const uint32_t seconds);
        /**
         * Creates an instance of the SimTime class.
         * @param hours The number of simulation hours.
         * @param minutes The number of simulation minutes.
         * @param seconds The number of simulation seconds.
         */
        SimTime(const uint32_t& hours, const uint32_t& minutes, const uint32_t& seconds);
        /**
         * Sets the simulation time from the given number of hours, minutes, and seconds.
         * @param hours The number of simulation hours.
         * @param minutes The number of simulation minutes.
         * @param seconds The number of simulation seconds.
         */
        virtual void From(const uint32_t& hours, const uint32_t& minutes, const uint32_t& seconds);
        /**
         * Gets the number of simulation seconds.
         * @return The number of simulation seconds.
         */
        virtual uint32_t GetSeconds() const;
        /**
         * Indicates whether or not this time is later than the given time.
         * @param other The given time.
         * @return True, if this time is later.
         */
        virtual bool IsLaterThan(const SimTime& other) const;
        /**
         * Indicates whether or not this time is later/younger than the given time.
         * @param other The given time.
         * @return True, if this time is earlier/younger than the given time.
         */
        virtual bool operator >(const SimTime& other) const;
        /**
         * The overloaded subtraction operator for the SimTime class.
         * @param other The time to subtract.
         * @return The difference of the two times.
         */
        virtual SimTime operator -(const SimTime& other) const;
        /**
         * The overloaded addition operator for the SimTime class.
         * @param other The time to add.
         * @return The sum of the two times.
         */
        virtual SimTime operator +(const SimTime& other) const;
        /**
         * Sets the number of simulation seconds.
         * @param seconds The number of simulation seconds.
         */
        virtual void SetSeconds(const uint32_t& seconds);
        /**
         * Gets the simulation time put in hours, minutes, and seconds.
         * @param hours The number of simulation hours.
         * @param minutes The number of simulation minutes.
         * @param seconds The number of simulation seconds.
         */
        virtual void To(uint32_t& hours, uint32_t& minutes, uint32_t& seconds) const;
    private:
        uint32_t m_seconds; /// The number of simulation seconds.
    };
    
    /**
     * The overloaded output stream operator for the SimTime class.
     * @param out The output stream to write to.
     * @param time The instance to write to the stream.
     * @return The stream that was written to.
     */
    ostream& operator <<(ostream& out, const SimTime& time);
}

#endif