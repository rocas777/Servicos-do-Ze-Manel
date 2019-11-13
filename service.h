#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <map>
#include <fstream>

#include "truck.h"
#include "date.h"
#include "misc.h"
#include "client.h"
#include "company.h"
#include "Address.h"

using namespace std;

class Service;
class Client;
class Truck;
class TemperatureService;
class HazardousService;
class Date;
class Company;
class Address;

enum class Hazard_enum {explosives=0, gases=1, flammableliq=2, flammablesolid=3, oxidizer=4, poisons=5, radioactive=6, corrosives=7, other=8}; //categories for the diferent dangers
enum class Temperature_enum{_100=0,_200=1,_300=2,_400=3};

enum class type {ordinary=0,hazardous=1,animal=2,lowTemperature=3};

enum state {
    on_queue=0,on_transit=1,finished=2
};

class Service
{
public:
    ~Service();
    Service();
    //get methods
    Address getOrigin() const; /*!< @return string #origin  */
    Address getDestination() const;
    unsigned getDistance() const;
    type getType() const;
    unsigned int getId() const;
    state getState() const;
    Date *getIDate() const;
    Date *getADate() const;
    Client *getClient() const;
    map<Truck *, float> *getTrucks();
    float getTotalPrice() const;
    float getQuantity() const;
    float getMultiplier(){return  1;}
    string getMaterial() const;

    //set methods
    void setOrigin(Address origin);
    void setDestination(Address destination);
    void setTime(double time);
    void setDistance(unsigned distance);
    void setType(type type);
    void setState(state state);
    void setIDate(Date *date);
    void setADate(Date *date);
    void setClient(Client *client);
    void setQuantity(float quantity);
    void setMaterial(string material);

    void addTruck(Truck *truck,float cargo);

    //file methods
    static void saveToFile(list<Service*>*services_finished, vector<Service *> *services_on_transit, vector<Service *> *services_on_queue);
    static void loadFromFile(list<Service *> *services_finished, vector<Service *> *services_on_transit, vector<Service *> *services_on_queue);
    static Service *addService(vector<Service *> *services, Client *client=nullptr);
    void editService();
    static bool removeService(vector<Service *> *services,unsigned id);
    friend ostream& operator<<(ostream& os, Service *a);

    static void test();

protected:
    Service(string material,Address origin, Address destination, Date *arrivalDate, unsigned distance, type type, state state, Date *date,Client *client,float quantity);
    Service(string material, string origin, string destination, Date *arrivalDate, unsigned distance, type type, state state, Date *date, Client *client, float quantity, float total_price,unsigned id);
    Address *origin; /**< stores the origin of the Service */
    Address *destination;
    string material;
    Date *arrivalDate;
    unsigned distance;
    float quantity;
    type ser_type;
    unsigned int id;
    map<Truck*,float> trucks;
    state ser_state;
    Date *initialDate;
    Client *client;
    float total_price;
    static unsigned int lastId;
    int autoAddTrucks();



};

class HazardousService: public Service
{
public:
    HazardousService(string material,Address origin, Address destination, Date *arrivalDate, unsigned distance, type type, state state, Date *date,Client *client,float quantity,Hazard_enum hazard);
    HazardousService(string material,string origin, string destination, Date *arrivalDate, unsigned distance, type type, state state, Date *date,Client *client,float quantity,Hazard_enum hazard,float total_price,unsigned id);
    Hazard_enum type;
};

class TemperatureService: public Service
{
public:
    TemperatureService(string material,Address origin, Address destination, Date *arrivalDate, unsigned distance, type type, state state, Date *date,Client *client,float quantity,Temperature_enum hazard);
    TemperatureService(string material, string origin, string destination, Date *arrivalDate, unsigned distance, type type, state state, Date *date, Client *client, float quantity, Temperature_enum hazard, float total_price, unsigned id_s);
    Temperature_enum type;
};

class ServiceDoNotExist{
public:
    string erro;
    ServiceDoNotExist(string erro):erro(erro){}
};
