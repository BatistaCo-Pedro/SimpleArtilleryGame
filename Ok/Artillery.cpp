#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>

using namespace std;

char done;
const int NUMOFSCHELLS = 10;
const double VELOCITY = 200.0;
const double GRAVITY = 32.2;
const double PI = 3.1415;

void StartUp() {
    cout << "Welcome to Artillery." << endl
        << "You are in the middle of a war and being charged by thousands of enemies." << endl
        << "You have one cannon, which you can shoot at any angle." << endl
        << "You only have 10 cannonballs for this target.." << endl
        << "Let's begin..." << endl;
}

void getCorrectInput() {
    bool correct = false;
    while (!correct) {
        cin >> done;
        if ((done == 'n') || (done == 'y')) correct = true;
    }
}

int claculateDistanceTraveled(double inputedAngle) {
    double timeInAir = (2.0 * VELOCITY * sin(inputedAngle)) / GRAVITY;
    return (int)round((VELOCITY * cos(inputedAngle)) * timeInAir);
}

int checkShot() {
    double angle = 0;
    int distance = 0;
    cout << "What angle?" << endl;
    if (!(cin >> angle)) return -1;
    angle = (angle * PI) / 180.0;
    return (distance = claculateDistanceTraveled(angle));
}

int Initialize(int minDistance, int maxDistance) {
    srand(time(0));
    int enemyDistance = minDistance + rand() % (maxDistance - minDistance);
    return enemyDistance;
}

int fire() {
    bool hit = false;
    int distanceTraveled = 0;
    int killed = 0;
    int shots = NUMOFSCHELLS;
    int enemyDistance = Initialize(300, 1000);
    cout << "The enemy is " << enemyDistance << " feet away!" << endl;
    do {
        distanceTraveled = checkShot();
        if (distanceTraveled == -1) {
            cout << "Enter numbers only..." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (abs(enemyDistance - distanceTraveled) <= 1) {
            cout << "You hit one" << endl;
            killed++;
            hit = true;
            cout << "It took you " << NUMOFSCHELLS - shots << " shots!" << endl;
        }
        else {
            distanceTraveled > enemyDistance ?  cout << "You overshot by " << distanceTraveled - enemyDistance << " feet." << endl :
                                                cout << "You undershot by " << enemyDistance - distanceTraveled << " feet." << endl;
        }
        shots--;
    } while ((!hit) && (shots > 0));
    if (shots == 0) {
        cout << "You have run out of ammo..." << endl;
    }
    return killed;
}

int main() {
    StartUp();
    int killed = 0;
    do {
        killed += fire();
        cout << "You have killed " << killed << endl;
        cout << "I see another one, are you ready? (Y/N) ";
        getCorrectInput();
    } while (done != 'n');
}