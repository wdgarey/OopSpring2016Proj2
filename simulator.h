/* 
 * Author: Wesley Garey
 * Date: April 16, 2016
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <functional>
#include <memory>
#include <queue>

#include "event.h"

using namespace std;

namespace Project2
{
    /**
     * The class used to drive the simulation.
     */
    class Simulator
    {
    public:
        /**
         * Stops the simulator from executing any more vents.
         */
        static void Halt();
        /**
         * Gets the simulation time.
         * @return The simulation time.
         */
        static SimTime Now();
        /**
         * Runs the simulation until the given stop time. If a time of 0 is
         * given the simulator will run until all events have been processed;
         * indefinitely 
         * @param stopTime The time at which to halt the simulation.
         */
        static void Run(const SimTime& stopTime);
        /**
         * Schedules an event.
         * @param event The event to schedule.
         */
        static void Schedule(const Event& event);
    private:
        static Simulator s_instance; /// The static instance of the simulator.
    public:
        /**
         * Creates an instance of the simulator class.
         */
        Simulator();
        /**
         * The copy constructor of the Simulator class.
         * @param src The instance to copy.
         */
        Simulator(const Simulator& src);
        /**
         * Adds an event to the simulation.
         * @param event The event to add.
         */
        virtual void Add(const Event& event);
        /**
         * Deep copies the given simulator.
         * @param src The instance to copy.
         */
        virtual void Copy(const Simulator& src);
        /**
         * Gets the time of the event that will be executed next.
         * @return The simulation time.
         */
        virtual SimTime GetCurrEventTime() const;
        /**
         * Indicates whether or not the simulator is running.
         * @return True, if the simulator is running.
         */
        virtual bool IsRunning() const;
        /**
         * The assignment operator of the simulator class.
         * @param src The instance being assigned to.
         * @return The instance that was assigned.
         */
        virtual Simulator& operator =(const Simulator& src);
        /**
         * Starts executing events.
         */
        virtual void Start();
        /**
         * Stops executing events.
         */
        virtual void Stop();
    protected:
        /**
         * Advances the simulation by one discrete-event.
         */
        virtual void Run();
        /**
         * Gets the flag that indicates if the simulator is running.
         * @return The flag.
         */
        virtual bool GetRunning() const;
        /**
         * Sets the flag that indicates if the simulator is funning.
         * @param running The flag.
         */
        virtual void SetRunning(const bool& running);
        /**
         * Gets the collection of events to execute.
         * @return The collection of events.
         */
        virtual shared_ptr<priority_queue<Event,vector<Event>,greater<Event>>> GetSched () const;
        /**
         * Sets the collection of events to execute.
         * @param sched The collection of events.
         */
        virtual void SetSched(const shared_ptr<priority_queue<Event,vector<Event>,greater<Event>>>& sched);
        /**
         * Gets the time at which the simulation is supposed to stop.
         * @return The simulation time (a value of 0 means indefinite).
         */
        virtual SimTime GetStopTime() const;
        /**
         * Sets the time at which the simulation should stop.
         * @param stopTime The simulation time (a value of 0 means indefinite).
         */
        virtual void SetStopTime(const SimTime& stopTime);
    private:
        bool m_running; /// A flag used to indicate if the simulator is running.
        shared_ptr<priority_queue<Event,vector<Event>,greater<Event>>> m_sched; /// The schedule of events to execute.
        SimTime m_stopTime; /// The time at which to stop the simulation.
    };
}

#endif