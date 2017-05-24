#include "assignment2.h"

double calcAverageWaitingTime(struct Simulation * S)
{
    double aveTime = 0;
    double totT = 0;
    double num = (S->eventQueue).currSize;
    struct Data d;
    
    // compute average waiting time
    while (S->eventQueue.currSize!=0) {
        d = dequeue(&S->eventQueue);
        //printf("%f\n",aveTime);
        totT += (d.departureTime - d.arrivalTime);
    }
    aveTime = totT/num;
    
    // free all the dynamic allocation
    freeQueue(&(S->buffer));
    freeQueue(&(S->eventQueue));
    return aveTime;
    
    /*******************
     alternative way:
     using dequeue then the data returned can be used to calc the waiting time
     *******************/
}

struct Simulation initSimulation(double arrivalRate, double serviceTime, double simTime)
{
    struct Simulation S;
    S.timeForNextArrival = getRandTime(arrivalRate);
    S.timeForNextDeparture = serviceTime + S.timeForNextArrival;
    S.arrivalRate = arrivalRate;
    S.serviceTime = serviceTime;
    S.currTime = 0;
    S.totalSimTime = simTime;
    S.buffer = initQueue();
    S.eventQueue = initQueue();
    return S;
}

double runSimulation(double arrivalRate, double serviceTime, double simTime)
{
    struct Simulation S = initSimulation(arrivalRate, serviceTime, simTime);
    struct Data d;
    // progress through simulation
    while ( S.currTime < simTime ) {
        // determine the event
        if (S.timeForNextArrival<S.timeForNextDeparture) {
            S.e = ARRIVAL;
            S.currTime = S.timeForNextArrival;
            d.arrivalTime = S.currTime;
            d.departureTime = 0;
            enqueue(&S.buffer, d);
            S.timeForNextArrival += getRandTime(arrivalRate);
            
            
        } else {
            S.e = DEPARTURE;
            S.currTime = S.timeForNextDeparture;
            d = dequeue(&S.buffer);
            d.departureTime = S.currTime;
            enqueue(&S.eventQueue, d);
            if (S.buffer.currSize == 0) {
                S.timeForNextDeparture = serviceTime + S.timeForNextArrival;
            } else {
                S.timeForNextDeparture = serviceTime + S.timeForNextDeparture;
            }
        }
        
    }
    
    return calcAverageWaitingTime(&S);
}


