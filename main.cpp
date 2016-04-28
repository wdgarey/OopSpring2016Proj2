/* 
 * Author: Wesley Garey
 * Date: April 14, 2016
 */

#include "definitions.h"

#include <cstdlib>
#include <memory>
#include <sstream>

#include "call-producer.h"
#include "chance-gen.h"
#include "exp-rnd-gen.h"
#include "server.h"
#include "sim-time.h"
#include "simulator.h"
#include "system-stats.h"
#include "system.h"

#ifdef TRACE
#include "trace.h"
#include "call-producer.h"
#endif

using namespace std;
using namespace Project2;

/*
 * The entry point of the program.
 * @return The exit code.
 */
int main()
{
#ifdef TRACE
    Trace::OpenInst("trace2.txt");
#endif

    double callsPerHour = 25; // 25 calls arrive per hour
    int servers = 3; // 3 servers.
    double avgServTime = SimTime(0, 6, 0).GetSeconds(); // Average service time of six minutes.
    double stdDevServTime = SimTime(0, 2, 0).GetSeconds(); // Standard deviation of two minutes for service time.
	double subscriberProb = 1.0 / 4.0; // 25% chance that caller is a subscriber.
	double secondsPerHour = SimTime(1, 0, 0).GetSeconds(); // Compute the number of seconds in one hour.
	SimTime startTime = SimTime(0); // Start producing calls when simulation starts.
	SimTime stopTime = SimTime(24, 0, 0); // Stop producing calls after 24 hours.

    shared_ptr<System> sys = make_shared<System>();
    
    for (uint32_t index = 0; index < servers; index++)
    {
        uint32_t seed = (index + 1);
        uint32_t id = (index + 1);
        weak_ptr<System> sysWeak = sys;
        shared_ptr<NormRndGen> rnd = make_shared<NormRndGen>(avgServTime, stdDevServTime, seed);
        shared_ptr<Server> server = make_shared<Server>(id, sysWeak, rnd);
        
        sys->AddServer(server);
    }
    
    shared_ptr<ChanceGen> chanceGen = make_shared<ChanceGen>(subscriberProb, 10);
    shared_ptr<ExpRndGen> callCreationRnd = make_shared<ExpRndGen>(secondsPerHour, callsPerHour, 4);
    
    shared_ptr<CallProducer> producer = make_shared<CallProducer>(chanceGen, callCreationRnd, sys);
    
    producer->Start(startTime, stopTime);
    
    Simulator::Run(SimTime(0)); // Don't stop simulation until all events have been processed.
    
    SystemStats stats = sys->GetStats();
    
    cout << stats << endl << endl;

	getchar();
    
#ifdef TRACE
    
    stringstream ss;
    
    ss << stats;
    
    Trace::WriteLineToInst("");
    Trace::WriteLineToInst("Statistics: " + ss.str());
    
    Trace::CloseInst();
#endif
    
    return EXIT_SUCCESS;
}

