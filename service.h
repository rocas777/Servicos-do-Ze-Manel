#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <fstream>

#include "truck.h"
#include "date.h"
#include "misc.h"
#include "client.h"

using namespace std;

class Service;
class Client;
class Truck;
class TemperatureService;
class HazardousService;

enum Hazard_enum {explosives, gases, flammableliq, flammablesolid, oxidizer, poisons, radioactive, corrosives, other}; //categories for the diferent dangers
enum Temperature_enum{_100,_200,_300,_400};

enum type {
    ordinary=0,hazardous=1,animal=2,lowTemperature=3
};

enum state {
    on_queue,on_transit,finished
};

class Service
{
public:
    Service(string origin, string destination, double time, unsigned distance, type type, state state, Date date,Client *client,float quantity);
    ~Service();

    //get methods
    string getOrigin() const;
    string getDestination() const;
    double getTime() const;
    unsigned getDistance() const;
    type getType() const;
    unsigned int getId() const;
    state getState() const;
    Date getDate() const;
    Client *getClient() const;
    vector<Truck*> *getTrucks();
    float getTotalPrice() const;
    float getQuantity() const;
    float getMultiplier(){return  1;}

    //set methods
    void setOrigin(string origin);
    void setDestination(string destination);
    void setTime(double time);
    void setDistance(unsigned distance);
    void setType(type type);
    void setState(state state);
    void setDate(Date date);
    void setClient(Client *client);
    void setQuantity(float quantity);

    void addTruck(Truck *truck);
    void calcPrice();

    //file methods
    static void saveToFile(vector<Service*>*services_finished, vector<Service *> *services_on_transit, vector<Service *> *services_on_queue);
    static void loadFromFile(vector<Service *> *services_finished, vector<Service *> *services_on_transit, vector<Service *> *services_on_queue);
    static Service *addService(vector<Service *> *services, Client *client=nullptr);
    static void editService(vector<Service *> *services);
    static void removeService(vector<Service *> *services);
    friend ostream& operator<<(ostream& os, Service &dt);

protected:
    string origin;
    string destination;
    double time;
    unsigned distance;
    float quantity;
    type ser_type;
    unsigned int id;
    vector<Truck*> trucks;
    state ser_state;
    Date initialDate;
    Client *client;
    float total_price;
    static unsigned int lastId;



};

class HazardousService: public Service
{
public:
    HazardousService(string origin, string destination, double time, unsigned distance, type type, state state, Date date,Client *client,float quantity,Hazard_enum hazard);
    Hazard_enum type;
};

class TemperatureService: public Service
{
public:
    TemperatureService(string origin, string destination, double time, unsigned distance, type type, state state, Date date,Client *client,float quantity,Temperature_enum hazard);
    Temperature_enum type;
};
