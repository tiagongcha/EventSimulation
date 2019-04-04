//
//  WholeFood.hpp
//  EventSimulation
//
//  Created by Gong Tia on 4/2/19.
//  Copyright © 2019 Gong Tia. All rights reserved.
//

#ifndef WholeFood_hpp
#define WholeFood_hpp

#include <stdio.h>
//#include <stdio.h>
#include <stdio.h>
#include <queue>

enum EventType {arrival, departure};
class Event{
public:
    int executionTime;
    int arrivalTime;
    int serviceDuration;
    int checkerNumber;
    EventType type;
    
    Event(){
        this->arrivalTime = 0;
        this->executionTime = 0;
        this->serviceDuration = 0;
        this->checkerNumber = -1;
    }
    
    Event(EventType type, int executionTime, int arrivalTime, int serviceDuration){
        this->arrivalTime = arrivalTime;
        this->executionTime = executionTime;
        this->serviceDuration = serviceDuration;
        this->checkerNumber = -1;
        this->type = type;
    }
};

class Checker{
public:
    std::queue<Event> checkerLine;
    
    int currEventRemainTime;
    
    Event* currentEvent;
    
    bool free;
    
    int checkerLineWait;
    
    //    Constructor:
    Checker(){
        currentEvent = nullptr;
        currEventRemainTime = 0;
        checkerLineWait = 0;
        free = true;
    }
    
    int getWaitingTime(){
        return currEventRemainTime + checkerLineWait;
    }
};

//overload operator for priority-queue sorting:
struct EventCompare{
    bool operator()(const Event &e1, const Event &e2) const{
        return e1.executionTime > e2.executionTime;
    }
};


class EventQueue{
private:
    std::priority_queue<Event, std::vector<Event>, EventCompare> queue;
    
public:

    bool isEmpty(){
        return queue.empty();
    }
    
    void push(Event e){
        queue.push(e);
    }
    
    Event popEvent(){
        if(queue.empty()){
            perror("pop an empty queuez? execuse you!");
            exit(1);
        }
        Event ret = queue.top();
        queue.pop();
        return ret;
    }
};


class WholeFood{
public:
    int time;
    std::vector<Checker> checkers;
    EventQueue allCustomer;
    std::vector<Event> doneCustomers;
    void populateEvent(int seed, int simulationTime, double duration ,int totalCustomer);
    void simulate();
    void placeCustomer(Event e);
    void findShortestChecker(Event e);
    void getStat();
    
    WholeFood(){
        for (int i = 0; i < 6; i++) {
            Checker checker;
            checkers.push_back(checker);
        }
    }
};

class Cashier{
public:
    int currEventRemainTime;
    bool free;
//    Event* currentEvent;
    Cashier(){
        currEventRemainTime = 0;
        free = true;
//        currentEvent = nullptr;
    }
};

class Bank{
public:
    int time;
    std::vector<Cashier> cashiers;
    EventQueue allCustomer;
    std::vector<Event> doneCustomers;
    void populateEvent(int seed, int simulationTime, double duration ,int totalCustomer);
    void simulate();
    void placeCustomer(Event e);
    void getStat();
    std::queue<Event> waitLine;
    
    Bank(){
        time = 0;
        for(int i = 0; i < 6; i++){
            Cashier cashier;
            cashiers.push_back(cashier);
        }
    }
};

#endif /* WholeFood_hpp */
