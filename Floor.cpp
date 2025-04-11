/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */


#include "Floor.h"
#include <algorithm>

using namespace std;

int Floor::tick(int currentTime) {
    //TODO: Implement tick
	int indicesToRemove[MAX_PEOPLE_PER_FLOOR] = {};
	int numPeopleToRemove = 0; 
	for (int i = 0; i < numPeople; i++) {
		// people[i].tick()
		if (people[i].tick(1) == true) {
			indicesToRemove[numPeopleToRemove] = i;
			numPeopleToRemove++;
		}
	}
	removePeople(indicesToRemove, numPeopleToRemove);

    return numPeopleToRemove;
}

void Floor::addPerson(Person newPerson, int request) {
    //TODO: Implement addPerson
	if (numPeople < MAX_PEOPLE_PER_FLOOR) {
		people[numPeople] = newPerson;
		if (request > 0) {
			setHasUpRequest(1);
		}
		else if (request < 0) {
			setHasDownRequest(1);
		}
		numPeople++;
	}
}

void Floor::removePeople(const int indicesToRemove[MAX_PEOPLE_PER_FLOOR],
                         int numPeopleToRemove) {
    //TODO: Implement removePeople
	int indicesToRemoveSorted[MAX_PEOPLE_PER_FLOOR] = {};

	for (int i = 0; i < numPeopleToRemove; i++) {
		indicesToRemoveSorted[i] = indicesToRemove[i];
	}

	sort(indicesToRemoveSorted, indicesToRemoveSorted + numPeopleToRemove);
	for (int j = 0; j < numPeopleToRemove; j++) {
		indicesToRemoveSorted[j] - j;
		for (int k = indicesToRemoveSorted[j]; k < numPeople - indicesToRemoveSorted[j]; k++) {
			people[k] = people[k + 1];
		}
		numPeople--;
	}
}

void Floor::resetRequests() {
    //TODO: Implement resetRequests
	int request;
	bool noUp = 0;
	bool noDown = 0;
	for (int i = 0; i < numPeople; i++) {
		request = people[i].getTargetFloor() - people[i].getCurrentFloor();
		if (request > 0) {
			setHasUpRequest(1);
			noUp = 1;
		}
		else if (request < 0) {
			setHasDownRequest(1);
			noDown = 1;
		}
	}

	if (noUp == 0) {
		setHasUpRequest(0);
	}
	if (noDown == 0) {
		setHasDownRequest(0);
	}
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i){
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
