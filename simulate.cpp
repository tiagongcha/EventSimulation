//
//  WholeFood.cpp
//  EventSimulation
//
//  Created by Gong Tia on 4/2/19.
//  Copyright © 2019 Gong Tia. All rights reserved.
//

#include "simulate.hpp"
#include <iostream>
#include <stdlib.h>
//#include "EventQueue.hpp"
#include <algorithm>

void WholeFood::populateEvent(int seed, int simulationTime, double duration ,int totalCustomer){
    srand(seed);
    for(int i = 0; i < totalCustomer; i++){
        int arrivalTime = rand() % simulationTime;
        int serviceDuration = rand() % (int)duration + 1;
        Event event(arrival, arrivalTime, arrivalTime, serviceDuration);
        allCustomer.push(event);
    }
}

void WholeFood::findShortestChecker(Event e){
    int numChecker = (int) checkers.size();
    Checker* minChecker = &checkers[0];
    int min = 100000000;
    int checkerNum = 0;
    for (int i = 1; i < numChecker; i++) {
        if (checkers[i].getWaitingTime() < min) {
            min = checkers[i].getWaitingTime();
            minChecker = &checkers[i];
            checkerNum = i;
        }
    }
    //    make a departure event:
    Event finish(departure, e.arrivalTime + e.serviceDuration + minChecker->getWaitingTime(), e.arrivalTime, e.serviceDuration);
    minChecker->checkerLine.push(finish);
    minChecker->checkerLineWait += e.serviceDuration;
    finish.checkerNumber = checkerNum;
    allCustomer.push(finish);
}

void WholeFood::placeCustomer(Event e){
    int numChecker = (int)checkers.size();
    
    for(int i = 0; i < numChecker; i++){
        if(checkers[i].free){
            checkers[i].free = false;
            checkers[i].currentEvent = &e;
            Event finish(departure, e.arrivalTime + e.serviceDuration, e.arrivalTime, e.serviceDuration);
            checkers[i].currEventRemainTime = finish.serviceDuration;
            finish.checkerNumber = i;
            allCustomer.push(finish);
            return;
        }
    }
    
    findShortestChecker(e);
}

void WholeFood::simulate(){
    while(!allCustomer.isEmpty()){
        Event nextThing = allCustomer.popEvent();
        time = nextThing.executionTime;
//         std::cout << time << std::endl;
        if(time > 43200){
            return;
        }
//        std::cout << time << std::endl;
        //         TODO: add assertion about time
        if(nextThing.type == arrival){
            //placed customer meanwhile also push a departure event:
            placeCustomer(nextThing);
        }else if (nextThing.type == departure){
            //            add this departure event to the doneCustomer vector:
            doneCustomers.push_back(nextThing);
            int checkerNum = nextThing.checkerNumber;
            
            if(checkers[checkerNum].checkerLine.empty()){
                checkers[checkerNum].currentEvent = nullptr;
                checkers[checkerNum].free = true;
                checkers[checkerNum].currEventRemainTime = 0;
                checkers[checkerNum].checkerLineWait = 0;
            }else{
                checkers[checkerNum].currentEvent = &checkers[checkerNum].checkerLine.front();
                
                checkers[checkerNum].checkerLine.pop();
                
                checkers[checkerNum].currEventRemainTime = checkers[checkerNum].currentEvent->serviceDuration;
                
                checkers[checkerNum].checkerLineWait -= checkers[checkerNum].currentEvent->serviceDuration;
            }
        }
    }
}

void WholeFood::getStat(){
    int numDoneCustomer = (int)doneCustomers.size();
//     std::cout << "done customer number " << numDoneCustomer << std::endl;
    int serviceTime[numDoneCustomer];
    for (int i = 0; i < numDoneCustomer; i++) {
        serviceTime[i] = doneCustomers[i].executionTime - doneCustomers[i].arrivalTime;
    }
    int n = sizeof(serviceTime)/sizeof(serviceTime[0]);
    
    std::sort(serviceTime, serviceTime + n);
    int tenIdx = numDoneCustomer * 0.1 - 1;//substract 1 since array starts at 0
    std::cout << "10th percentile is "<<serviceTime[tenIdx]/60.0 << std::endl;
    int fiftyIdx = numDoneCustomer * 0.5 - 1;
    std::cout << "50th percentile is "<<serviceTime[fiftyIdx]/60.0 << std::endl;
    int ninetyIdx = numDoneCustomer * 0.9 - 1;
    std::cout << "90th percentile is "<<serviceTime[ninetyIdx]/60.0 << std::endl;
    int total = 0;
    for (int i = 0; i < numDoneCustomer; ++i)
        total +=serviceTime[i];
//    std::cout<< "avg service time " << total/numDoneCustomer/60.0 << std::endl;
}



///////////////////////////////////////////////////////////////////////////////////

void Bank::populateEvent(int seed, int simulationTime, double duration ,int totalCustomer){
    srand(seed);
   
    for(int i = 0; i < totalCustomer; i++){
        int arrivalTime = rand() % simulationTime;
        int serviceDuration = rand() % (int)duration + 1;
        Event event(arrival, arrivalTime, arrivalTime, serviceDuration);
        allCustomer.push(event);
    }
//    std::cout << "all customer size " << totalCustomer << std::endl;
}

void Bank::placeCustomer(Event e){
    int numCashier = (int) cashiers.size();
    for(int i = 0; i < numCashier; i++){
        if(cashiers[i].free){
            cashiers[i].currEventRemainTime = e.serviceDuration;
            cashiers[i].free = false;
            //            make a departure Event:
            Event finish(departure, time + e.serviceDuration, e.arrivalTime, e.serviceDuration);
            finish.checkerNumber = i;
            allCustomer.push(finish);
            return;
        }
    }
//    if there is no cashier free, we set this customer as the next in line
    waitLine.push(e);
}

void Bank::simulate(){
    while (!allCustomer.isEmpty()) {
        Event nextThing = allCustomer.popEvent();
        time = nextThing.executionTime;
        if(time > 43200){
            return;
        }
        if(nextThing.type == arrival){
            placeCustomer(nextThing);
        }else if(nextThing.type == departure){
//            push to the doneCustomer.
            doneCustomers.push_back(nextThing);
            
            int cashierNum = nextThing.checkerNumber;
            cashiers[cashierNum].free = true;
            cashiers[cashierNum].currEventRemainTime = 0;
            
            if(!waitLine.empty()){
                Event curr = waitLine.front();
                waitLine.pop();
                Event finish(departure, time + curr.serviceDuration, curr.arrivalTime, curr.serviceDuration);
                finish.checkerNumber = cashierNum;
                allCustomer.push(finish);
                cashiers[cashierNum].free = false;
                cashiers[cashierNum].currEventRemainTime = curr.serviceDuration;
            }
        }
    }
}

void Bank::getStat(){
    int numDoneCustomer = (int) doneCustomers.size();
//    std::cout << "done customer number " << numDoneCustomer << std::endl;
    int serviceTime[numDoneCustomer];
    for (int i = 0; i < numDoneCustomer; i++) {
        serviceTime[i] = doneCustomers[i].executionTime - doneCustomers[i].arrivalTime;
    }
    int n = sizeof(serviceTime)/sizeof(serviceTime[0]);
    
    std::sort(serviceTime, serviceTime + n);
    int tenIdx = numDoneCustomer * 0.1 - 1;//substract 1 since array starts at 0
    std::cout << "10th percentile is "<<serviceTime[tenIdx]/60.0 << std::endl;
    int fiftyIdx = numDoneCustomer * 0.5 - 1;
    std::cout << "50th percentile is "<<serviceTime[fiftyIdx]/60.0 << std::endl;
    int ninetyIdx = numDoneCustomer * 0.9 - 1;
    std::cout << "90th percentile is "<<serviceTime[ninetyIdx]/60.0 << std::endl;
    int total = 0;
    for (int i = 0; i < numDoneCustomer; ++i)
        total +=serviceTime[i];
//    std::cout<< "avg service time " << total/numDoneCustomer/60.0 << std::endl;
}
