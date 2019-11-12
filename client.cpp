#include "client.h"

// TODO: excecoes, verificacoes, hipotese de cancelar com !q, usar enter_to_exit() nos menus
Client::Client() {}

Client::Client(Client const &x){
    this->nif=x.getNif();
    this->name=x.getName();
}

Client::Client(string name, unsigned int nif, vector<Service*> *services): name(name), nif(nif){
	if(services==nullptr)
        services=new vector<Service*>;

    //if (!checkNif(nif))
    //throw BadNif(nif, "NIF not allowed!");
}


Client::~Client(){
    for (size_t i = 0; i < services.size(); i++)
    {
        services.at(i)->~Service();
    }
}

//get methods
string Client::getName() const { return name; }

unsigned Client::getNif() const { return nif; }

vector<Service *> *Client::getServicesVector() { return &services; }

//set methods
void Client::setName(string name){
    this->name=name;
}
void Client::setNif(unsigned nif){
    this->nif=nif;
}

//other methods	
void Client::addService(Service *service){
    services.push_back(service);
}

void Client::addClient(vector<Client *> *clientsVector) {
    clearScreen();
    string tempName;
    string tempNif;
    bool variable_error=true;
    while (variable_error) {
        cout<<"Enter the Name"<<endl;

        getline(cin,tempName);
        checkIfOut(tempName);
        clearScreen();
        if(strIsChar(tempName))
            variable_error=false;
        else{
            variable_error=true;
            cout<<"Name Input not acceptable, please try again"<<endl;
        }

    }
    variable_error=true;
    while (variable_error) {
        cout<<"Enter the Nif"<<endl;

        getline(cin,tempNif);
        checkIfOut(tempNif);
        clearScreen();
        if(strIsNumber(tempNif) && tempNif.size()==9)
            variable_error=false;
        else{
            variable_error=true;
            cout<<"Nif Input not acceptable, please try again"<<endl;
        }
    }
    Client *tempClient = new Client(tempName,unsigned(stoi(tempNif)));
	for (auto it = *clientsVector->begin(); it != *clientsVector->end(); it++)
	{
		if (tempClient->getNif() == (*it).getNif())
			throw ClientInVector(tempClient->getNif(), "Client you're trying to add already exists in the database!");
			
	}
	clientsVector->push_back(tempClient);

}

void Client::editClient()
{
	unsigned opt = 1;
	while (opt != 0) {
		clearScreen();
		cout << "[1] Edit Name" << endl;
		cout << "[2] Edit Nif" << endl;
		cout << "[0] Return" << endl;
		if (cin >> opt && opt <= 2) {
			clearScreen();
			clearBuffer();
			switch (opt) {
			case 1: {
				string tempName;
				bool variable_error = true;
				while (variable_error) {
					cout << "Enter the Name" << endl;

					getline(cin, tempName);
					checkIfOut(tempName);
					clearScreen();
					if (strIsChar(tempName))
						variable_error = false;
					else {
						variable_error = true;
						cout << "Name Input not acceptable, please try again" << endl;
					}
				}

				setName(tempName);
				break;
			}
			case 2: {
				bool variable_error = true;
				string tempNif;
				while (variable_error) {
					cout << "Enter the Nif" << endl;

					getline(cin, tempNif);
					checkIfOut(tempNif);
					clearScreen();
					if (strIsNumber(tempNif) && tempNif.size() == 9)
						variable_error = false;
					else {
						variable_error = true;
						cout << "Nif Input not acceptable, please try again" << endl;
					}
				}

				setNif(unsigned(stoi(tempNif)));
				break;
			}
			case 0: {
				return;
			}
			default:
				opt = 1;
			}
		}
		else {
			opt = 1;
			clearBuffer();
			clearScreen();
			cout << "Not a valid option, please try again" << endl;
		}
	}
}

// Removes client from the vector
void Client::removeClient(vector<Client*>& clientsVector) {
	Client *client;

	for (auto it = clientsVector.begin(); it != clientsVector.end(); it++)
	{
		if ((*it)->getNif() == nif) {
			if ((*it)->getServicesVector()->size() == 0) {
				(*it)->~Client();
				clientsVector.erase(it);
				cout << "Client removed sucessfully" << endl;
				enter_to_exit();
				return;
			}
			else {
				cout << "That client cannot be removed as it has at least one service reserved" << endl;
				return;
			}
		}
	}
	throw ClientNotInVector(nif, "Client doesn't exist in the database");
}


void Client::loadClients(vector<Client*>& clientsVector) {

    string clientsNameFile = "./files/clients.txt"; // File containing clients
    string clientsText; // String containing contents of clients.txt
    ifstream clientsFile;
    Client client;

    int i = 0;

    clientsFile.open(clientsNameFile);
    if (clientsFile.fail())
    {
        throw CantOpenClientFile("Could not open associated clients.txt file");
    }

    else
    {
        while (getline(clientsFile, clientsText))
        {
            switch (i)
            {
            case 0:
                client.setName(clientsText);
                break;
            case 1:
                client.setNif(unsigned(stoi(clientsText)));
                break;
            default:
                break;
            }
            i++;
            if (i == 3) {
                Client *temp=new Client(client);
                clientsVector.push_back(temp);
                i = 0;
            }
        }
    }
    clientsFile.close();
}

void Client::saveToFile(vector<Client*>& clientsVector){
	string clientsNameFile = "./files/clients.txt"; // File containing clients
	ofstream clientsFile;
	clientsFile.open(clientsNameFile);
	if (clientsFile.fail()){
		throw CantOpenClientFile("Could not open associated clients.txt file");
	}
	else{
		for (auto it = clientsVector.begin(); it != clientsVector.end(); it++)
		{
			clientsFile << (*it)->getName() << endl;
			clientsFile << (*it)->getNif() << endl;
			clientsFile << "::::::::::::::::::::::::::::" << endl;
		}
	}
	clientsFile.close();
}


// OPERATOR OVERLOADING

bool Client::operator==(const Client& client1) const {
    return nif == client1.nif;
}

bool Client::operator<(const Client &a) const{
    return nif < a.getNif();
}

ostream& operator<<(ostream& out, const Client& client) {
    out << "Name:" << client.name << endl;
    out << "NIF: " << client.nif << endl; 
	out << "*********************************" << endl;

    return out;
}


ClientInVector::~ClientInVector(){
}

ClientNotInVector::~ClientNotInVector(){
}


CantOpenClientFile::~CantOpenClientFile(){

}

NotAClient::~NotAClient(){

}

float Client::getMoneySpent() const{
    return money_spent;
}

void Client::calcMoneySpent(){
    money_spent=0;
    for(auto i:services){
        money_spent+=i->getTotalPrice();
    }
}