#include "company.h"


Company *Company::getCompany(){
    if (company==nullptr)
        company = new Company();
    return company;
}

Company::Company(){}

Company::~Company(){
    cout<<getCompany()->services_on_queue_changed<<endl;
    if(getCompany()->services_on_queue_changed){
        Service::saveToFile(&services_finished,&services_on_transit,&services_on_queue);
    }
}

vector<Service*> *Company::getVectorServicesFinished(){
    return &services_finished;
}
vector<Service*> *Company::getVectorServicesOnTransit(){
    return &services_on_transit;
}
vector<Service*> *Company::getVectorServicesOnQueue(){
    return &services_on_queue;
}

vector<Client*> *Company::getVectorClients(){
    return &clients;
}
vector<Truck*> *Company::getVectorTrucks(){
    return &trucks;
}

Client *Company::getClient(unsigned nif){
    size_t l=0;
    unsigned t;
    vector<Client*> *temp(Company::getCompany()->getVectorClients());
    if(!temp->size())
        throw NotAClient(nif,"Couldn't find the client");
    size_t r=(*temp).size()-1;
    while (l <= r) {
        size_t m = l + (r - l) / 2;
        t=temp->at(m)->getNif();
        if (temp->at(m)->getNif() == nif)
            return Company::getCompany()->getVectorClients()->at(m);
        if (temp->at(m)->getNif() < nif)
            l = m + 1;
        else if(m>0)
            r = m - 1;
        else
            break;
    }
    throw NotAClient(nif,"Couldn't find the client");
}
Truck *Company::getTruck(string license){
    size_t l=0;
    string t;
    vector<Truck*> *vect(Company::getCompany()->getVectorTrucks());
    if(!vect->size())
        throw TruckDoNotExist("Couldn't find the Truck",license);
    size_t r=vect->size()-1;
    while (l <= r) {
        size_t m = l + (r - l) / 2;
        t=vect->at(m)->getlicense();
        if (vect->at(m)->getlicense() == license)
            return vect->at(m);
        if (vect->at(m)->getlicense() < license)
            l = m + 1;
        else if(m>0)
            r = m - 1;
        else
            break;
    }
    throw TruckDoNotExist("Couldn't find the Truck",license);
}


Service *getService(unsigned id){


}

void Company::updateTruckSituation(){
    time_t rawtime;struct tm *now;std::time( &rawtime );now = localtime( &rawtime );
    Date f(unsigned(now->tm_year-100),1+date_u_short(now->tm_mon),date_u_short(now->tm_mday),date_u_short(now->tm_hour),date_u_short(now->tm_min));

    for(auto it=services_on_transit.begin(); it!= services_on_transit.end();it++){
        if(*(*it)->getADate()<=f){
            break;
        }
        else{
            for(auto x:*(*it)->getTrucks())
            {
                x->setavailable(true);
                services_finished.push_back(*it);
                it=services_on_transit.erase(it);
            }
        }
    }

    for(auto it=services_on_queue.begin(); it!= services_on_queue.end();it++){
        if(*(*it)->getIDate()<=f){
            break;
        }
        else{
            for(auto x:*(*it)->getTrucks())
            {
                x->setavailable(false);
                services_on_transit.push_back(*it);
                it=services_on_queue.erase(it);
            }
        }
    }
    sort(services_on_queue.begin(),services_on_queue.end(),cmpOnQueue);
    sort(services_on_transit.begin(),services_on_transit.end(),cmpOnTransit);


}
