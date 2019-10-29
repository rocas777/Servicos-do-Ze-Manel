#pragma once
#include <string>
#include <vector>

#include "service.h"
#include "misc.h"


using namespace std;

class Service;
class Truck;

class Client
{
public:
    Client(string name, unsigned int nif, vector<Service *> *services=nullptr);
    ~Client();

	void loadClients(const string &clientsNameFile, vector<Client> &clientsVector); // Reads the clients file and stores the result in a vector
	//void removeClient(vector<Client>& clientsVector);

    //get methods
    string getName() const;
    unsigned getNif() const;
    void getServicesVector(vector<Service*> *services) const;

    //set methods
    void setName(string name);
    void setNif(unsigned nif);

    //add methods
    void addService(Service *service);


    //ostream& operator<<(ostream& out, const Client& client) const;

    //bool operator == (const Client& client1, const Client& client2) const;

protected:
    Client(){};
    string name;
    unsigned int id;
    unsigned int nif;
    vector<Service*> services;
    static unsigned int lastId;

};

class NotAClient:public Client{
public:
    string erro;
    NotAClient(unsigned nif_n, string erro): Client(), erro(erro){
        this->nif=nif_n;
    }
	unsigned int getNif() const {
		return nif;
	}
};

class CantOpenClientFile: public Client {
public:
	string erro;
	CantOpenClientFile(string erro): Client(), erro(erro) {}
};