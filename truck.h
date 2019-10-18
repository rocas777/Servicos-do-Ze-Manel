#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "service.h"
using namespace std;

class Service;
class Client;
class Truck;

class Truck
{
protected:
	string license; //format XX-YY-ZZ
	bool availabe;	//is the truck available right now?
	bool registered;	//is the truck registered to a service in the future?
	vector<Service*> assignedServices;	//pretty self-explanatory I'd say
	unsigned short capacity; //in KG
	unsigned short cargo; //if in transit this holds the weight it transports

public:
    Truck(string license);
    virtual ~Truck()=0;
	//get methods
	virtual float getprice(Service* service) const = 0;
	unsigned short getcapacity() const;
	bool getavailable() const;
	string getlicense() const;
	bool getregistered() const;
	unsigned short get_cargo() const;
	//set methods
	virtual void setprice(float newval) = 0;
	void setregistered(bool foo);
	void setavailable(bool foo);
	//load and save to file
	
	//other
	void add_service(Service* service); //adds to the vector the service which the truck is assigned to
	void remove_service(unsigned int id); //removes an assigned service when it is finished, searches by id
	void start_transport(unsigned short cargo); //sets the needed variables so the truck is in transport
};

class Congelation : public Truck
{
public:
    Congelation(string license_c);
	~Congelation() {}

	float getprice(Service* service) const;
	void setprice(float newval);


private:
	//static unordered_map<Hazard, int> table;
	static float pricePerKG;
};

class HazardousMat : public Truck
{
public:
    HazardousMat(string license_h);
	~HazardousMat(){}


    float getprice(Service* service)const;
    //using Truck::getprice;

	void setprice(float newval);

private:
    static float pricePerKG;
};

class Animal : public Truck
{
public:
    Animal(string license_a);
    ~Animal(){}

	float getprice(Service* service)const;
	void setprice(float newval);

private:
	static float pricePerKG;
};

class Normal : public Truck
{
public:
    Normal(string license_n);
    ~Normal(){}

	float getprice(Service* service)const;
	void setprice(float newval);

private:
	static float pricePerKG;
};
