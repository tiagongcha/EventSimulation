//
//  main.cpp
//  EventSimulation
//
//  Created by Gong Tia on 4/2/19.
//  Copyright © 2019 Gong Tia. All rights reserved.
//

#include <iostream>
#include <string>
#include "simulate.hpp"



int main(int argc, const char * argv[]) {
    if (argc < 4) {
        exit(1);
    }
//
    int simulationDuration = 43200;
    double arrivalRate = std::stod(argv[1]);
////    std::cout << arrivalRate << std::endl;
    int totalCustomer = (int)(arrivalRate * 60 * 12);
////    std::cout <<  totalCustomer << std::endl;
    double serviceRange = std::stod(argv[2]);
////     std::cout << serviceRange << std::endl;
    double serviceTime = serviceRange * 60;
//    std::cout << "service time " <<serviceTime << std::endl;
    int seed = std::stoi(argv[3]);
////     std::cout << seed << std::endl;
    std::cout << "the arrival rate is " << arrivalRate << std::endl;
    std::cout << "super market stat is " << std::endl;
    WholeFood wholefood;
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
