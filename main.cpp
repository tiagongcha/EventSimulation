//
//  main.cpp
//  EventSimulation
//
//  Created by Gong Tia on 4/2/19.
//  Copyright © 2019 Gong Tia. All rights reserved.
//

#include <iostream>
#include <string>
//#include "simulate.hpp"
#include "bank.h"
#include "market.h"
//#include "checker.h"
//#include "event.h"



int main(int argc, const char * argv[]) {
//    if (argc < 4) {
//        exit(1);
//    }
//
    int simulationDuration = 43200;
//    double arrivalRate = std::stod(argv[1]);
//    int totalCustomer = (int)(arrivalRate * 60 * 12);
//    double serviceRange = std::stod(argv[2]);
//    double serviceTime = serviceRange * 60;
//    int seed = std::stoi(argv[3]);

    int arrivalRate = 10;
    int totalCustomer = 10;
    double serviceRange = 10;
    double serviceTime = 10;
    int seed = 34567;

//    std::cout << arrivalRate << std::endl;
//    std::cout <<  totalCustomer << std::endl;
//    std::cout << serviceRange << std::endl;
//    std::cout << "service time " <<serviceTime << std::endl;
//    std::cout << seed << std::endl;


    std::cout << "the arrival rate is " << arrivalRate << std::endl;
    std::cout << "super market stat is " << std::endl;
    market wholefood;
    wholefood.populateEvent(seed, simulationDuration, serviceTime, totalCustomer);
    wholefood.simulate();
    wholefood.getStat();

    std::cout << "bank stat is " << std::endl;
    Bank bank;
    bank.populateEvent(seed, simulationDuration, serviceTime, totalCustomer);
    bank.simulate();
    bank.getStat();
//     std::cout << "-----------**********************------------------------- " << std::endl;
    return 0;
}