/*
 * Copyright 2023 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 *
 *
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core#include "AI.h"

string getAIPickupList(const Move& move, const BuildingState& building, const Floor& floor) {
    string pickupList = "";
    std::vector<int> indexAndDistance;

    int currentFloor = building.elevators[move.getElevatorId()].currentFloor;
    int direction = 0;

    // Iterate over people on the floor to build the pickup list
    for (int i = 0; i < NUM_PEOPLE; ++i) {
        const Person& person = floor.getPersonByIndex(i);
        if (person.getTargetFloor() == -1) continue;

        int target = person.getTargetFloor();
        int distance = abs(target - currentFloor);

        if (target > currentFloor) {
            direction = 1;
        } else {
            direction = -1;
        }

        indexAndDistance.push_back(i);
    }

    // Sort manually by distance from farthest to nearest
    for (int i = 0; i < indexAndDistance.size(); ++i) {
        for (int j = i + 1; j < indexAndDistance.size(); ++j) {
            int a = indexAndDistance[i];
            int b = indexAndDistance[j];

            int distA = abs(floor.getPersonByIndex(a).getTargetFloor() - currentFloor);
            int distB = abs(floor.getPersonByIndex(b).getTargetFloor() - currentFloor);

            if (distB > distA) {
                int temp = indexAndDistance[i];
                indexAndDistance[i] = indexAndDistance[j];
                indexAndDistance[j] = temp;
            }
        }
    }

    for (int i = 0; i < indexAndDistance.size(); ++i) {
        if (pickupList.length() >= ELEVATOR_CAPACITY) break;

        int idx = indexAndDistance[i];
        const Person& person = floor.getPersonByIndex(idx);
        int target = person.getTargetFloor();

        int personDir;
        if (target > currentFloor) {
            personDir = 1;
        } else {
            personDir = -1;
        }

        if (personDir == direction) {
            pickupList += static_cast<char>('0' + idx);
        }
    }

    return pickupList;
}

string getAIMoveString(const BuildingState& building) {
    int bestElevator = -1;
    int maxPeople = 0;
    int floorWithMostPeople = -1;

    for (int e = 0; e < NUM_ELEVATORS; ++e) {
        int floor = building.elevators[e].currentFloor;
        if (building.floors[floor].getNumPeople() > 0) {
            return "e" + std::to_string(e) + "p";
        }
    }

    for (int f = 0; f < NUM_FLOORS; ++f) {
        int waiting = building.floors[f].getNumPeople();
        if (waiting > maxPeople) {
            maxPeople = waiting;
            floorWithMostPeople = f;
        }
    }

    if (floorWithMostPeople != -1) {
        for (int e = 0; e < NUM_ELEVATORS; ++e) {
            if (building.elevators[e].targetFloor == -1) {
                return "e" + std::to_string(e) + "f" + std::to_string(floorWithMostPeople);
            }
        }
    }

    return "e0f0";
}
