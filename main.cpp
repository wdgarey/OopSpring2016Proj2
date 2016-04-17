/* 
 * Author: Wesley Garey
 * Date: April 14, 2016
 */

#define TRACE

#include <cstdlib>
#include <memory>
#include <sstream>

#include "call-action.h"
#include "event.h"
#include "exp-rnd-gen.h"
#include "norm-rnd-gen.h"
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
    
    shared_ptr<CallAction> act(new CallAction());
    
    act->generator = make_shared<NormRndGen>(6, 2);
    
    for (int count = 0; count < 20; count++)
    {
        Event event1(count, SimTime(count), act);
    
        Simulator::Schedule(event1);
    }

    Simulator::Run(stopTime);
    
#ifdef TRACE
    Trace::CloseInst();
#endif
    
    return EXIT_SUCCESS;
}

