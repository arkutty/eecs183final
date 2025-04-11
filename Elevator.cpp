/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Elevator.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * Aditya Kutty
 * akutty
 *
 * Final Project - Elevators
 */

#include "Elevator.h"
#include <iostream>

using namespace std;
/**
* Requires: currentTime is valid
* Modifies: currentFloor, servicing
* Effects:  If the currentTime is divisible by TICKS_PER_ELEVATOR_MOVE and
*           the elevator is servicing a request:
*               Moves the value of current floor by 1 in the direction
*               of the target floor
*               Also, If the new current floor is the target floor:
*                   servicing is set to false
*
*           Otherwise, does nothing
*
*/
void Elevator::tick(int currentTime) {
    Elevator elevator;
    if (currentTime % TICKS_PER_ELEVATOR_MOVE == 0 && isServicing() == true){
        if (getTargetFloor() > currentFloor){
            currentFloor += 1;
        } else{
            currentFloor -= 1;
        }
        if (currentFloor == targetFloor){
            servicing = false;
        }
    }
}
/**
 * Requires: 0 <= floorNum <= NUM_FLOORS
 * Modifies: targetFloor, servicing
 * Effects:  Sets the targetFloor and marks the Elevator as
 *           currently servicing
 */
void Elevator::serviceRequest(int floorNum) {
    Elevator elevator;
    targetFloor = floorNum;
    servicing = true;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

void Elevator::print(ostream &outs) {
    outs << currentFloor;
    if (!servicing){
        outs << "w";
    } else {
        outs << "s" << targetFloor;
    }
}

Elevator::Elevator() {
    currentFloor = 0;
    servicing = false;
	targetFloor = 0;
}

void Elevator::setCurrentFloor(int currentFloorIn) {
    currentFloor = currentFloorIn;
}

bool Elevator::isServicing() const {
	return servicing;
}

int Elevator::getCurrentFloor() const {
    return currentFloor;
}

int Elevator::getTargetFloor() const {
    return targetFloor;
}
