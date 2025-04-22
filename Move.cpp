/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * Aditya Kutty
 * akutty
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "Move.h"

using namespace std;
/**
 * Requires: commandString is a valid string
 * Modifies: elevatorId, targetFloor, isPass, isPickup, isSave, isQuit
 * Effects:  creates a Move object based on
 *           the characters in commandString
 *
 *           Examples:
 *           commandString = "e1f4"; - elevatorID of 1 has a targetFloor of 4
 *           commandString = "e1p"; - elevatorID of 1 will pickup people on
 *                                    its current floor
 *
 *           when commandString is "", or "S", or "Q", etc.:
 *                sets the corresponding private data member to true
 */
Move::Move(string commandString) : Move() {
    if (commandString == "S") {
        isSave = true;
    }
    else if (commandString == "Q") {
        isQuit = true;
    }
    else if (commandString == "") {
        isPass = true;
    }
    else {
        int i = 1;
        while (commandString[i]!= 'f' && commandString[i]!='p'){
            i ++;
        }
        
        elevatorId = stoi(commandString.substr(1,(i-1)));
        if (commandString[i] == 'f') {
            setTargetFloor(stoi(commandString.substr(i + 1)));
        }
        
        else if (commandString[i] == 'p') {
            isPickup = true;
        }
        
    }
}
/**
 * Requires: elevators represents the elevator servicing states
 * Modifies: nothing
 * Effects:  returns true if this Move instance is valid, false otherwise
 *
 *           The following are the criterion for validity:
 *
 *           If a move is a Pass Move, a Quit Move, or a Save Move it is valid
 *           For both Pickup Moves and Servicing Moves:
 *               0 <= elevatorId < NUM_ELEVATORS
 *               The corresponding Elevator is currently not
 *                  servicing a request.
 *           For Servicing Moves only:
 *               0 <= targetFloor < NUM_FLOORS
 *               targetFloor is different from the corresponding
 *                  Elevator's currentFloor
 * Elevator::isServicing(), Elevator::getCurrentFloor()
 */
bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    if (isPass || isSave || isQuit) {
        return true;
    }
    if (0 <= elevatorId && elevatorId < NUM_ELEVATORS && !elevators[elevatorId].isServicing()) {
        if (isPickup) {
            return true;
        }
        if (0 <= targetFloor && targetFloor < NUM_FLOORS &&
            targetFloor != elevators[elevatorId].getCurrentFloor()) {
            return true;
        }
    }
    return false;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor,
                             const Floor& pickupFloor) {
    numPeopleToPickup = 0;
    totalSatisfaction = 0;

    stringstream ss(pickupList);
    int index;

    while (ss >> index) {
        if (index >= 0 && index < pickupFloor.getNumPeople()) {
            Person person = pickupFloor.getPersonByIndex(index);
            peopleToPickup[numPeopleToPickup] = index;
            numPeopleToPickup++;
            totalSatisfaction += MAX_ANGER - person.getAngerLevel();

            int destination = person.getTargetFloor();
            if (numPeopleToPickup == 1 ||
                abs(destination - currentFloor) > abs(targetFloor - currentFloor)) {
                targetFloor = destination;
            }
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
    return isPass;
}

bool Move::isSaveMove() const {
    return isSave;
}

bool Move::isQuitMove() const {
    return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}

