#include "typewise-alert.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const      coolingLowerLimit = 0;
vector<int>    coolingUpperLimits{30, 45, 40};
vector<string> breachTypeMessage{"Temperature is Normal", "Temperature is too low", "Temperature is too high"};

BreachType inferBreach(double value, double lowerLimit, double upperLimit)
{
    if (value < lowerLimit)
    {
        return TOO_LOW;
    }
    if (value > upperLimit)
    {
        return TOO_HIGH;
    }
    return NORMAL;
}

int getLowerLimitFromcoolingType() { return (coolingLowerLimit); }

int getupperLimitFromcoolingType(CoolingType coolingType) { return (coolingUpperLimits[coolingType]); }

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC)
{
    int lowerLimit = getLowerLimitFromcoolingType();
    int upperLimit = getupperLimitFromcoolingType(coolingType);
    return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

bool checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC)
{
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    bool       response   = false;
    switch (alertTarget)
    {
    case TO_CONTROLLER:
        response = sendToController(breachType);
        break;
    case TO_EMAIL:
        sendToEmail(breachType);
        break;
    }
    return response;
}

bool sendToController(BreachType breachType)
{
    const unsigned short header = 0xfeed;
    std::cout << header << breachType;
    return true;
}

string sendToEmail(BreachType breachType)
{
    const string recepient = "a.b@c.com";
    std::cout << "To: " << recepient << endl << breachTypeMessage[breachType] << endl;
    return breachTypeMessage[breachType];
}
