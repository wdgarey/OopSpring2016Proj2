/* 
 * Author: Wesley Garey
 * Date: April 14, 2016
 */

#define TRACE

#include <cstdlib>
#include <memory>
#include <sstream>

#include "call.h"
#include "call-action.h"
#include "event.h"
#include "exp-rnd-gen.h"
#include "norm-rnd-gen.h"
#include "sim-stats.h"
#include "sim-time.h"
#include "simulator.h"

#ifdef TRACE
#include "trace.h"
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
    
    SimTime stopTime;
    SimStats stats;
    shared_ptr<Call> call(new Call(1, true));
    shared_ptr<CallQueued> queuedAct(new CallQueued());
    shared_ptr<CallServiced> servicedAct(new CallServiced());
    shared_ptr<CallReleased> releasedAct(new CallReleased());
    
    queuedAct->call = call;
    servicedAct->call = call;
    releasedAct->call = call;
    
    Simulator::Schedule(Event(1, SimTime(5), queuedAct));
    Simulator::Schedule(Event(2, SimTime(15), servicedAct));
    Simulator::Schedule(Event(3, SimTime(16), releasedAct));
    
    Simulator::Run(stopTime);
    
    stats.Observe(*call);
    stats.Observe(*call);
    
    stringstream ss;
    
    ss << stats;
    
    Trace::WriteLineToInst(ss.str());
    
#ifdef TRACE
    Trace::CloseInst();
#endif
    
    return EXIT_SUCCESS;
}

