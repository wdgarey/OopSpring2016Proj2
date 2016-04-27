/* 
 * Author: Wesley Garey
 * Date: April 14, 2016
 */

//#define TRACE

#include <cstdlib>
#include <memory>
#include <sstream>

#include "call-producer.h"
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
    Trace::OpenInst("trace.txt");
#endif
    
    double callsPerHour = 25;
    int servers = 3;
    double avgServTime = SimTime(0, 6, 0).GetSeconds();
    double stdDevServTime = SimTime(0, 2, 0).GetSeconds();
    
    shared_ptr<System> sys = make_shared<System>();
    
    for (uint32_t index = 0; index < servers; index++)
    {
        uint32_t seed = (index + 1);
        uint32_t id = (index + 1);
        weak_ptr<System> sysWeak = sys;
        shared_ptr<NormRndGen> rnd = make_shared<NormRndGen>(seed, avgServTime, stdDevServTime);
        shared_ptr<Server> server = make_shared<Server>(id, sysWeak, rnd);
        
        sys->AddServer(server);
    }
    
    shared_ptr<ExpRndGen> callCreationRnd = make_shared<ExpRndGen>(4, SimTime(1, 0, 0).GetSeconds(), callsPerHour);
    
    shared_ptr<CallProducer> producer = make_shared<CallProducer>(callCreationRnd, sys);
    
    producer->Start(SimTime(0), SimTime(24, 0, 0));
    
    Simulator::Run(SimTime(0));
    
    SystemStats stats = sys->GetStats();
    
    cout << stats << endl << endl;
    
#ifdef TRACE
    
    stringstream ss;
    
    ss << stats;
    
    Trace::WriteLineToInst("");
    Trace::WriteLineToInst("Statistics: " + ss.str());
    
    Trace::CloseInst();
#endif
    
    return EXIT_SUCCESS;
}

