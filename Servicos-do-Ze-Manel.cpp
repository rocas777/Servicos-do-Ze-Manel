// Serviços do Zé Manel.cpp : This file contains the 'main' function. Program execution begins and ends There.
//

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <ctime>
#include <map>

#include "client.h"
#include "truck.h"
#include "service.h"
#include "company.h"
#include "misc.h"

using namespace std;


void manage_client(Client *client){
    unsigned opt=1;
    while (opt!=0) {
        clearScreen();
        cout <<*client<<endl;
        cout<<"[1] Edit Client"<<endl;
        cout<<"[2] Remove Client"<<endl;
        cout<<"[3] Edit Services"<<endl;
        cout<<"[4] Cancel Service"<<endl;
        cout<<"[5] See Service"<<endl;
        cout<<"[0] Return"<<endl;
        if(cin>>opt && opt<=5)
        {
            clearScreen();
            switch (opt) {
            case 1: {
                clearBuffer();
                client->editClient();
                break;
            }
            case 2:{
                try {
                    clearBuffer();
                    client->removeClient(*Company::getCompany()->getVectorClients());
                }
                catch (...) {
                }
                return;
            }
            case 0:{
                return;
            }

            case 3:{

                long id=long(0);
                if(Company::getCompany()->getVectorServicesOnQueue()->size()){
                    Service *temp_client = nullptr;
                    do{
                        for(auto i: *Company::getCompany()->getVectorServicesOnQueue()){
                            cout<<"("<<i->getId()<<") "<<i->getMaterial()<<"   "<<i->getIDate()->getYear()<<"/"<<i->getIDate()->getMonth()<<"/"<<i->getIDate()->getDay()<<", "<<i->getIDate()->getHour()<<":"<<i->getIDate()->getMinute()<<endl;
                        }
                    }while((id=askForId("Service","Edit","Id"))==-2);
                    clearScreen();
                    for(auto i: *Company::getCompany()->getVectorServicesOnQueue()){
                        if(i->getId()==long(id)){
                            temp_client=i;
                            break;
                        }
                    }
                    if(temp_client==nullptr){
                        cout<<"couldn't find the specified service"<<endl;
                        clearBuffer();
                        enter_to_exit();
                    }
                    else{

                        temp_client->editService();
                        cout<<"Successfully Edited"<<endl;
                    }
                }
                else{
                    cout<<"No Service can be Edited"<<endl;
                    clearBuffer();
                    enter_to_exit();
                }
                break;

            }
            case 4:{

                long id=long(0);
                if(Company::getCompany()->getVectorServicesOnQueue()->size()){
                    Service *temp_client = nullptr;
                    do{
                        for(auto i: *Company::getCompany()->getVectorServicesOnQueue()){
                            cout<<"("<<i->getId()<<") "<<i->getMaterial()<<"   "<<i->getIDate()->getYear()<<"/"<<i->getIDate()->getMonth()<<"/"<<i->getIDate()->getDay()<<", "<<i->getIDate()->getHour()<<":"<<i->getIDate()->getMinute()<<endl;
                        }
                    }while((id=askForId("Service","Remove","Id"))==-2);
                    clearScreen();
                    for(auto i: *Company::getCompany()->getVectorServicesOnQueue()){
                        if(i->getId()==long(id)){
                            temp_client=i;
                            break;
                        }
                    }
                    if(temp_client==nullptr){
                        cout<<"couldn't find the specified service"<<endl;
                    }
                    else{
                        try{
                            Service::removeService(Company::getCompany()->getVectorServicesOnQueue(),unsigned(id));
                            cout<<"Successfully Removed"<<endl;
                        }
                        catch(ServiceDoNotExist e){
                            cout<<e.erro<<endl;
                        }
                    }
                }
                else{
                    cout<<"No Service can be Canceled"<<endl;
                }
                clearBuffer();
                enter_to_exit();
                break;

            }
            case 5:{
                clearBuffer();
                cout << "Services: " << endl;
                for (auto it = client->getServicesVector()->begin(); it != client->getServicesVector()->end(); it++)
                {
                    cout << (*it) << endl;
                }
                enter_to_exit();
                break;
            }

            default:
                opt=1;
            }
        }
        else{
            opt=1;
            clearBuffer();
            clearScreen();
            cout<<"Not a valid option, please try again"<<endl;
        }
    }
}

void menu_services();
void menu_editprices();
void mainMenu();
void menu_clients();
void menu_trucks();
void information();
void clientsInformation();
void trucksInformation();
void infoEveryServices(),infoOnQueueServices(),infoOnTransitServices(),infoFinishedServices();


/*
This function receives a name and returns true if it is valid
*/

template<class T> bool cmp_classes(T *a,T *b){
    return *a<*b;
}

Company *Company::company = nullptr;
int main()
{
    clearScreen();
    Company *Ze_Manel = nullptr;
    Ze_Manel=Company::getCompany();
    Truck::loadFromFile(Ze_Manel->getVectorTrucks());
    Client::loadClients(*Ze_Manel->getVectorClients());
    sort(((*Ze_Manel).getVectorTrucks())->begin(),((*Ze_Manel).getVectorTrucks())->end(),cmp_classes<Truck>);
    sort(((*Ze_Manel).getVectorClients())->begin(),((*Ze_Manel).getVectorClients())->end(),cmp_classes<Client>);
    sort(((*Ze_Manel).getVectorServicesOnQueue())->begin(),((*Ze_Manel).getVectorServicesOnQueue())->end(),cmpOnQueue);
    sort(((*Ze_Manel).getVectorServicesOnTransit())->begin(),((*Ze_Manel).getVectorServicesOnTransit())->end(),cmpOnTransit);
    Service::loadFromFile(Ze_Manel->getVectorServicesFinished(),Ze_Manel->getVectorServicesOnTransit(),Ze_Manel->getVectorServicesOnQueue());
    enter_to_exit();
    //vector<Truck*> a(*Ze_Manel->getVectorTrucks());
    string temp;
    mainMenu();
    Client::saveToFile(*Ze_Manel->getVectorClients());
    delete Ze_Manel;


    return 0;
}

void mainMenu(){
    unsigned opt=1;
    while (opt != 0) {
        cout<<"[0] Exit program"<<endl;
        cout<<"[1] Clients"<<endl;
        cout<<"[2] Trucks"<<endl;
        cout<<"[3] Services"<<endl;
        cout<<"[4] Information"<<endl;
        if(cin>>opt && opt<=4)
        {
            clearScreen();
            switch (opt) {
            case 0:
                break;
            case 1:{
                menu_clients();
                break;
            }
            case 2:{
                menu_trucks();
                break;
            }

            case 3:{
                menu_services();
                break;
            }
            case 4:{
                information();
                break;
            }

            default:
                opt=1;
            }
        }
        else{
            opt=1;
            clearBuffer();
            clearScreen();
            cout<<"Not a valid option, please try again"<<endl;
        }
    }
}

void menu_clients(){
    unsigned opt=1;
    while (opt!=0) {
        clearScreen();
        cout<<"[1] Add Client"<<endl;
        cout<<"[2] Manage Client"<<endl;
        cout<<"[0] Return to Main Menu"<<endl;
        if(cin>>opt && opt<=2)
        {
            clearScreen();
            switch (opt) {
            case 0:
                break;
            case 1:{
                try {
                    clearBuffer();
                    Client::addClient(Company::getCompany()->getVectorClients());
                }
                catch(...){

                }

                break;
            }
            case 2:{
                long nif=0;
                Client *temp_client;
                do{
                    for(auto i: *Company::getCompany()->getVectorClients()){
                        cout<<*i;
                    }
                }while((nif=askForId("Client","manage","Nif"))==-2);

                if(nif>0){
                    try {
                        temp_client=Company::getCompany()->getClient(unsigned(nif));
                        manage_client(temp_client);

                    } catch (NotAClient e) {
                        clearScreen();
                        clearBuffer();
                        cout << e.erro<<"erty" << endl;
                        enter_to_exit();
                    }
                }
                break;
            }

            default:
                opt=1;
            }
        }
        else{
            opt=1;
            clearBuffer();
            clearScreen();
            cout<<"Not a valid option, please try again"<<endl;
        }
    }
}

void menu_trucks() {
    unsigned opt = 1;
    while (opt != 0) {
        clearScreen();
        cout << "[1] Add Truck" << endl;
        cout << "[2] Edit Truck Prices" << endl;
        cout << "[3] Remove Truck" << endl;
        cout << "[0] Return to Main Menu" << endl;
        if (cin >> opt && opt <= 3)
        {
            clearScreen();
            switch (opt) {
            case 0:
                break;
            case 1: {
                clearBuffer();
                Truck::createTruck(Company::getCompany()->getVectorTrucks());
                break;
            }
            case 2: {
                clearBuffer();
                menu_editprices();
                break;
            }
            case 3: {
                clearBuffer();
                Truck::removeTruck(Company::getCompany()->getVectorTrucks());
                break;
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

void menu_services(){
    unsigned opt=1;
    while (opt!=0) {
        clearScreen();
        cout<<"[1] Add Service"<<endl;
        cout<<"[0] Return to Main Menu"<<endl;
        if(cin>>opt && opt<=2)
        {
            clearScreen();
            switch (opt) {
            case 0:
                break;
            case 1:{
                clearScreen();
                for(auto i:*Company::getCompany()->getVectorClients()){
                    cout<<*i;
                }
                try{
                    int temp=int(askForId("Client","add a Service","Nif"));
                    if(temp==-1)
                        break;
                    Client *tempClient= Company::getCompany()->getClient(unsigned(temp));
                    clearBuffer();
                    clearScreen();
                    Service::addService(Company::getCompany()->getVectorServicesOnQueue(),tempClient);
                    enter_to_exit();
                }
                catch(NotAClient e){
                    clearBuffer();
                    cout<<e.erro<<endl;
                    enter_to_exit();
                }
                break;
            }

            default:
                opt=1;
            }
        }
        else{
            opt=1;
            clearBuffer();
            clearScreen();
            cout<<"Not a valid option, please try again"<<endl;
        }
    }
}

void information(){
    unsigned opt=1;
    while (opt!=0) {
        clearScreen();
        cout<<"[1] Clients"<<endl;
        cout<<"[2] Services"<<endl;
        cout<<"[3] Trucks"<<endl;
        cout<<"[0] Return"<<endl;
        if(cin>>opt && opt<=3)
        {
            clearScreen();
            switch (opt) {
            case 0:{
                return;
            }
            case 1:
                clientsInformation();
                break;
            case 2:{
                // Adicionar info dos servicos
                break;
            }
            case 3:
                trucksInformation();
                break;

            default:
                opt=1;
            }
        }
        else{
            opt=1;
            clearBuffer();
            clearScreen();
            cout<<"Not a valid option, please try again"<<endl;
        }
    }
}

void clientsInformation(){
    unsigned opt=1;
    clearScreen();
    while (opt!=0) {
        cout<<"[1] Order by Nif"<<endl;
        cout<<"[2] Order by money Spent(low to high)"<<endl;
        cout<<"[3] Order by money Spent(high to low)"<<endl; // Não funciona
        cout<<"[4] Order by number of Services"<<endl;
        cout<<"[5] Show Clients with Services on queue"<<endl;
        cout<<"[6] Show Clients with Services on Transit"<<endl;
        cout<<"[7] Show Specific Client"<<endl;
        cout<<"[0] Return"<<endl;
        if(cin>>opt && opt<=7)
        {
            clearScreen();
            switch (opt) {
            case 0:{
                return;
            }
            case 1:
                if(Company::getCompany()->getVectorClients()->size())
                    for(auto i: *Company::getCompany()->getVectorClients()){
                        cout<<*i;
                    }
                else
                    cout<<"There is no Information to show"<<endl;
                clearBuffer();
                enter_to_exit();
                break;
            case 2:{
                vector<Client*> temp(*Company::getCompany()->getVectorClients());
                sort(temp.begin(),temp.end(),cmp_classes<Client>);
                if(temp.size())
                    for(auto i: temp){
                        cout<<*i;
                        cout<<i->getMoneySpent()<<endl;
                    }
                else
                    cout<<"There is no Information to show"<<endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 3:{
                vector<Client*> temp(*Company::getCompany()->getVectorClients());
                sort(temp.begin(),temp.end(),[](Client *a, Client *b)
                {
                    return !(a->getMoneySpent() < b->getMoneySpent());
                }
                );
                if(temp.size())
                    for(auto i: temp){
                        cout<<*i;
                        cout<<i->getMoneySpent()<<endl;
                    }
                else
                    cout<<"There is no Information to show"<<endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 4:{
                vector<Client*> temp(*Company::getCompany()->getVectorClients());
                sort(temp.begin(),temp.end(),[](Client *a, Client *b)
                {
                    return (a->getServicesVector()->size() < b->getServicesVector()->size());
                }
                );
                if(temp.size())
                    for(auto i: temp){
                        cout<<*i;
                        cout<<i->getServicesVector()->size()<<endl;
                    }
                else
                    cout<<"There is no Information to show"<<endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 5:{
                map<Client*, int>::iterator it;
                map<Client*, int> temp_ocurre;
                for(auto i: *Company::getCompany()->getVectorServicesOnQueue()){
                    it = temp_ocurre.find(i->getClient());
                    if(it != temp_ocurre.end()){
                        it->second++;
                    }
                    else {
                        temp_ocurre[i->getClient()]=0;
                    }
                }
                if(temp_ocurre.size())
                    for(auto i: temp_ocurre){
                        cout<<*i.first;
                    }
                else
                    cout<<"There is no Information to show"<<endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 6:{
                map<Client*, int>::iterator it;
                map<Client*, int> temp_ocurre;
                for(auto i: *Company::getCompany()->getVectorServicesOnTransit()){
                    it = temp_ocurre.find(i->getClient());
                    if(it != temp_ocurre.end()){
                        it->second++;
                    }
                    else {
                        temp_ocurre[i->getClient()]=0;
                    }
                }
                if(temp_ocurre.size())
                    for(auto i: temp_ocurre){
                        cout<<*i.first;
                    }
                else
                    cout<<"There is no Information to show"<<endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 7:{
                long nif = 0;
                Client* temp_client;
                do {
                    clearScreen();
                    for (auto i : *Company::getCompany()->getVectorClients()) {
                        cout << *i;
                    }
                    if(nif==-2){
                        cout<<"Nif not Acceptable"<<endl;
                    }
                } while ((nif = askForId("Client", "manage", "Nif")) == -2);
                clearScreen();

                if (nif > 0) {
                    try {
                        temp_client = Company::getCompany()->getClient(unsigned(nif));
                        cout << endl << *temp_client << endl;
                        cout << "Services: " << endl;
                        for(auto it = temp_client->getServicesVector()->begin(); it != temp_client->getServicesVector()->end(); it++)
                        {
                            cout << (*it) << endl;
                        }
                    }
                    catch (NotAClient e) {
                        cout << e.erro << endl;
                    }
                }
                //clearBuffer(); Tem de estar comentado senão não apresenta o menu no ecrã
                string temp;
                getline(cin, temp);
                break;
            }

            default:
                opt=1;
            }
        }
        else{
            opt=1;
            clearBuffer();
            clearScreen();
            cout<<"Not a valid option, please try again"<<endl;
        }
    }
}

void trucksInformation() {
    unsigned opt = 1;
    clearScreen();
    while (opt != 0) {
        cout << "[1] See all" << endl;
        cout << "[2] See Congelation trucks" << endl;
        cout << "[3] See Hazardous Material trucks" << endl; // Não funciona
        cout << "[4] See Animal Material trucks" << endl;
        cout << "[5] See Normal Material trucks" << endl;
        cout << "[6] Show Trucks with Services on queue" << endl;
        cout << "[7] Show Trucks on Transit" << endl;
        cout << "[8] Show Specific Truck" << endl;
        cout << "[9] Show Multipliers and Standart Prices" << endl;
        cout << "[0] Return" << endl;
        if (cin >> opt && opt <= 9)
        {
            clearScreen();
            switch (opt) {
            case 0: {
                return;
            }
            case 1:{
                bool nInfo=true;
                if (Company::getCompany()->getVectorTrucks()->size())
                    for (auto i : *Company::getCompany()->getVectorTrucks()) {
                        i->info();
                        nInfo=false;
                    }
                if(nInfo)
                    cout << "There is no Information to show" << endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 2: {
                bool nInfo=true;
                if (Company::getCompany()->getVectorTrucks()->size())
                    for (auto i : *Company::getCompany()->getVectorTrucks()) {
                        if (typeid(*i)==typeid(Congelation)) {
                            i->info();
                            nInfo=false;
                        }
                    }
                if(nInfo)
                    cout << "There is no Information to show" << endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 3: {
                bool nInfo=true;
                if (Company::getCompany()->getVectorTrucks()->size())
                    for (auto i : *Company::getCompany()->getVectorTrucks()) {
                        if (typeid(*i) == typeid(HazardousMat)) {
                            i->info();
                            nInfo=false;
                        }
                    }
                if(nInfo)
                    cout << "There is no Information to show" << endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 4: {
                bool nInfo=true;
                if (Company::getCompany()->getVectorTrucks()->size())
                    for (auto i : *Company::getCompany()->getVectorTrucks()) {
                        if (typeid(*i) == typeid(Animal)) {
                            i->info();
                            nInfo=false;
                        }
                    }
                if(nInfo)
                    cout << "There is no Information to show" << endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 5: {
                bool nInfo=true;
                if (Company::getCompany()->getVectorTrucks()->size())
                    for (auto i : *Company::getCompany()->getVectorTrucks()) {
                        if (typeid(*i) == typeid(Normal)) {
                            i->info();
                            nInfo=false;
                        }
                    }
                if(nInfo)
                    cout << "There is no Information to show" << endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 6: {
                bool nInfo=true;
                if (Company::getCompany()->getVectorTrucks()->size())
                    for (auto i : *Company::getCompany()->getVectorTrucks()) {
                        if ((!(i->getavailable()) && i->getServices()->size()>1) || (i->getavailable() && i->getregistered())) {
                            i->info();
                            nInfo=false;
                        }
                    }
                if(nInfo)
                    cout << "There is no Information to show" << endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 7: {
                bool nInfo=true;
                if (Company::getCompany()->getVectorTrucks()->size())
                    for (auto i : *Company::getCompany()->getVectorTrucks()) {
                        if (!(i->getavailable())) {
                            i->info();
                            nInfo=true;
                        }
                    }
                if(nInfo)
                    cout << "There is no Information to show" << endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 8: {
                string license;
                bool invalidInput;
                vector<string> auxVec;
                if (Company::getCompany()->getVectorTrucks()->size()) {
                    clearBuffer();

                    do {
                        clearScreen();
                        invalidInput = false;
                        cout << "What's the license of the truck you wish to see (XX-YY-ZZ)? "; getline(cin, license);
                        if (license == "!q") break;

                        //verifies if the license is valid or if it already exists.
                        if (!checkLicenseV2(license)) {
                            invalidInput = true;
                        }
                        else {
                            invalidInput = true;
                            for (vector<Truck*>::iterator it = Company::getCompany()->getVectorTrucks()->begin(); it != Company::getCompany()->getVectorTrucks()->end(); it++) {
                                if ((*it)->getlicense() == license) {
                                    clearScreen();
                                    cout << "Truck found!!!" << endl;
                                    (*it)->info();
                                    invalidInput=false;
                                    break;
                                }
                            }
                            if(invalidInput){
                                cout << "Truck with license " << license << " is not a part of the company's database" << endl;
                                enter_to_exit();
                            }
                        }
                    } while (invalidInput);
                }
                else
                    cout << "There is no Information to show" << endl;
                enter_to_exit();
                break;
            }

            case 9:
                clearScreen();
                clearBuffer();
                cout << "---Hazards---" << endl;
                cout << "Explosives multiplier: " << HazardousMat::hazardMul[Hazard_enum::explosives] << endl;
                cout << "Flammable liquid multiplier: " << HazardousMat::hazardMul[Hazard_enum::flammableliq] << endl;
                cout << "Flammable solid multiplier: " << HazardousMat::hazardMul[Hazard_enum::flammablesolid] << endl;
                cout << "Gases multiplier: " << HazardousMat::hazardMul[Hazard_enum::gases] << endl;
                cout << "Oxidizer multiplier: " << HazardousMat::hazardMul[Hazard_enum::oxidizer] << endl;
                cout << "Poisons multiplier: " << HazardousMat::hazardMul[Hazard_enum::poisons] << endl;
                cout << "Corrosives multiplier: " << HazardousMat::hazardMul[Hazard_enum::corrosives] << endl;
                cout << "Radioactive multiplier: " << HazardousMat::hazardMul[Hazard_enum::radioactive] << endl;
                cout << "'Other' multiplier: " << HazardousMat::hazardMul[Hazard_enum::other] << endl;
                cout <<endl<< "---Congelation---" << endl;
                cout << "_100 multiplier: " << Congelation::tempMul[Temperature_enum::_100] << endl;
                cout << "_200 multiplier: " << Congelation::tempMul[Temperature_enum::_200] << endl;
                cout << "_300 multiplier: " << Congelation::tempMul[Temperature_enum::_300] << endl;
                cout << "_400 multiplier: " << Congelation::tempMul[Temperature_enum::_400] << endl;
                cout <<endl<< "---STD Prices---" << endl;
                cout << "Congelation price per KG: " << Congelation::pricePerKG << endl;
                cout << "Hazard price per KG: " << HazardousMat::pricePerKG << endl;
                cout << "Animal price per KG: " << Animal::pricePerKG << endl;
                cout << "Normal price per KG: " << Normal::pricePerKG << endl;
                enter_to_exit();
                break;

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

void menu_editprices() {
    unsigned opt = 1;
    while (opt != 0) {
        clearScreen();
        cout << "[1] Temperature Price Multipliers" << endl;
        cout << "[2] Hazard Multipliers" << endl;
        cout << "[3] Standart price per KG" << endl;
        cout << "[0] Return to Main Menu" << endl;
        if (cin >> opt && opt <= 3)
        {
            clearScreen();
            switch (opt) {
            case 0:
                break;
            case 2: {
                clearBuffer();
                unsigned opt1 = 1;
                string aux;
                while (opt1 != 0) {
                    clearScreen();
                    cout << "[1] Edit Explosives" << endl;
                    cout << "[2] Edit Gases" << endl;
                    cout << "[3] Edit Flammable Liquid" << endl;
                    cout << "[4] Edit Flammable Solid" << endl;
                    cout << "[5] Edit Oxidizer" << endl;
                    cout << "[6] Edit Poison" << endl;
                    cout << "[7] Edit Radioactive" << endl;
                    cout << "[8] Edit Corrosives" << endl;
                    cout << "[9] Edit 'Other'" << endl;
                    cout << "[0] Return to Main Menu" << endl;
                    if (cin >> opt1 && opt1 <= 9)
                    {
                        clearScreen();
                        switch (opt) {
                        case 0:
                            break;
                        case 1: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for explosives is: " << HazardousMat::hazardMul[Hazard_enum::explosives] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::hazardMul[Hazard_enum::explosives] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 2: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for gases is: " << HazardousMat::hazardMul[Hazard_enum::gases] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::hazardMul[Hazard_enum::gases] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 3: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for flammable liquid is: " << HazardousMat::hazardMul[Hazard_enum::flammableliq] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::hazardMul[Hazard_enum::flammableliq] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 4: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for flammable solid is: " << HazardousMat::hazardMul[Hazard_enum::flammablesolid] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::hazardMul[Hazard_enum::flammablesolid] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 5: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for oxidizer is: " << HazardousMat::hazardMul[Hazard_enum::oxidizer] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::hazardMul[Hazard_enum::oxidizer] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 6: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for poisons is: " << HazardousMat::hazardMul[Hazard_enum::poisons] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::hazardMul[Hazard_enum::poisons] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 7: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for radioactive is: " << HazardousMat::hazardMul[Hazard_enum::radioactive] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::hazardMul[Hazard_enum::radioactive] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 8: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for corrosive is: " << HazardousMat::hazardMul[Hazard_enum::corrosives] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::hazardMul[Hazard_enum::corrosives] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 9: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for 'other' is: " << HazardousMat::hazardMul[Hazard_enum::other] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::hazardMul[Hazard_enum::other] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }

                        default:
                            opt1 = 1;
                        }
                    }
                    else {
                        opt = 1;
                        clearBuffer();
                        clearScreen();
                        cout << "Not a valid option, please try again" << endl;
                    }
                }
                break;
            }
            case 1: {
                clearBuffer();
                unsigned opt1 = 1;
                string aux;
                while (opt1 != 0) {
                    clearScreen();
                    cout << "[1] Edit _100" << endl;
                    cout << "[2] Edit _200" << endl;
                    cout << "[3] Edit _300" << endl;
                    cout << "[4] Edit _400" << endl;
                    cout << "[0] Return to Main Menu" << endl;
                    if (cin >> opt1 && opt1 <= 4)
                    {
                        clearScreen();
                        switch (opt) {
                        case 0:
                            break;
                        case 1: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for _100 is: " << Congelation::tempMul[Temperature_enum::_100] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    Congelation::tempMul[Temperature_enum::_100] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 2: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for _200 is: " << Congelation::tempMul[Temperature_enum::_200] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    Congelation::tempMul[Temperature_enum::_200] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 3: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for _300 is: " << Congelation::tempMul[Temperature_enum::_300] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    Congelation::tempMul[Temperature_enum::_300] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 4: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for _400 is: " << Congelation::tempMul[Temperature_enum::_400] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    Congelation::tempMul[Temperature_enum::_400] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }

                        default:
                            opt1 = 1;
                        }
                    }
                    else {
                        opt = 1;
                        clearBuffer();
                        clearScreen();
                        cout << "Not a valid option, please try again" << endl;
                    }
                }
                break;
            }
            case 3: {
                clearBuffer();
                unsigned opt1 = 1;
                string aux;
                while (opt1 != 0) {
                    clearScreen();
                    cout << "[1] Edit congelation trucks' price per KG" << endl;
                    cout << "[2] Edit hazardous material trucks' price per KG" << endl;
                    cout << "[3] Edit animal trucks' price per KG" << endl;
                    cout << "[4] Edit normal trucks' price per KG" << endl;
                    cout << "[0] Return to Main Menu" << endl;
                    if (cin >> opt1 && opt1 <= 4)
                    {
                        clearScreen();
                        switch (opt) {
                        case 0:
                            break;
                        case 1: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current congelation trucks' price per KG: " << Congelation::pricePerKG << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    Congelation::pricePerKG = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 2: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current hazardous material trucks' price per KG is: " << HazardousMat::pricePerKG << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::pricePerKG = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 3: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current animal trucks' price per KG is: " << Animal::pricePerKG << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    Animal::pricePerKG = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 4: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current normal trucks' price per KG is: " << Normal::pricePerKG << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    Normal::pricePerKG = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }

                        default:
                            opt1 = 1;
                        }
                    }
                    else {
                        opt = 1;
                        clearBuffer();
                        clearScreen();
                        cout << "Not a valid option, please try again" << endl;
                    }
                }
                break;
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
void servicesInformation(){
    unsigned opt=1;
    clearScreen();
    while (opt!=0) {
        cout<<"[1] Every Service"<<endl;
        cout<<"[2] Services On Queue"<<endl;
        cout<<"[3] Services On Transit"<<endl; // Não funciona
        cout<<"[4] Services Finished"<<endl;
        cout<<"[0] Return"<<endl;
        if(cin>>opt && opt<=4)
        {
            clearScreen();
            switch (opt) {
            case 0:{
                return;
            }
            case 1:
                infoEveryServices();
                break;
            case 2:{
                infoOnQueueServices();
                break;
            }
            case 3:{
                infoOnTransitServices();
                break;
            }
            case 4:{
                infoFinishedServices();
                break;
            }


            default:
                opt=1;
            }
        }
        else{
            opt=1;
            clearBuffer();
            clearScreen();
            cout<<"Not a valid option, please try again"<<endl;
        }
    }
}

void infoEveryServices(){
    unsigned opt=1;
    clearScreen();
    while (opt!=0) {
        cout<<"[1] Every Service"<<endl;
        cout<<"[2] Services On Queue"<<endl;
        cout<<"[3] Services On Transit"<<endl;
        cout<<"[4] Services Finished"<<endl;
        cout<<"[0] Return"<<endl;
        if(cin>>opt && opt<=4)
        {
            clearScreen();
            switch (opt) {
            case 0:{
                return;
            }
            case 1:
                infoEveryServices();
                break;
            case 2:{
                infoOnQueueServices();
                break;
            }
            case 3:{
                infoOnTransitServices();
                break;
            }
            case 4:{
                infoFinishedServices();
                break;
            }


            default:
                opt=1;
            }
        }
        else{
            opt=1;
            clearBuffer();
            clearScreen();
            cout<<"Not a valid option, please try again"<<endl;
        }
    }
}
void infoOnQueueServices(){

}
void infoOnTransitServices(){

}
void infoFinishedServices(){

}

