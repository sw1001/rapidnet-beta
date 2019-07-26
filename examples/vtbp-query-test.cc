#include "ns3/core-module.h"
#include "ns3/simulator-module.h"
#include "ns3/node-module.h"
#include "ns3/rapidnet-module.h"
#include "ns3/values-module.h"
#include "ns3/helper-module.h"
#include "ns3/vtbp-module.h"
#include "ns3/vtbp-query-module.h"
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>

#define emissionData \
"./data/viterbi/emission.csv"

#define transitionData \
"./data/viterbi/transition.csv"

#define observationData \
"./data/viterbi/observation.csv"

#define emission(loc, observed, state, prob_em) \
tuple (Vtbp::EMISSION, \
attr ("emission_attr1", Ipv4Value, loc), \
attr ("emission_attr2", StrValue, observed), \
attr ("emission_attr3", StrValue, state), \
attr ("emission_attr4", RealValue, prob_em))

#define transition(loc, state, state_pre, prob_tr) \
tuple (Vtbp::TRANSITION, \
attr ("transition_attr1", Ipv4Value, loc), \
attr ("transition_attr2", StrValue, state), \
attr ("transition_attr3", StrValue, state_pre), \
attr ("transition_attr4", RealValue, prob_tr))

#define observation(loc, observed, order, prob_ob) \
tuple (Vtbp::OBSERVATION, \
attr ("observation_attr1", Ipv4Value, loc), \
attr ("observation_attr2", StrValue, observed), \
attr ("observation_attr3", Int32Value, order), \
attr ("observation_attr4", RealValue, prob_ob))

#define insertemission(loc, observed, state, prob_em) \
app(loc)->Insert (emission(addr(loc), observed, state, prob_em));

#define inserttransition(loc, state, state_pre, prob_tr) \
app(loc)->Insert (transition(addr(loc), state, state_pre, prob_tr));

#define insertobservation(loc, observed, order, prob_ob) \
app(loc)->Insert (observation(addr(loc), observed, order, prob_ob));

//define the tuple you would like to query and how to insert it
#define tupleQuery(loc, name, attr1, attr2, attr3, attr4) \
tuple (VtbpQuery::TUPLE, \
attr ("tuple_attr1", Ipv4Value, loc), \
attr ("tuple_attr2", StrValue, name), \
attr ("tuple_attr3", Ipv4Value, attr1), \
attr ("tuple_attr4", StrValue, attr2), \
attr ("tuple_attr5", StrValue, attr3), \
attr ("tuple_attr6", Int32Value, attr4))

#define inserttuple(loc, name, attr1, attr2, attr3, attr4) \
queryNode->Insert (tupleQuery(queryNode->GetAddress(), name, addr(attr1), attr2, attr3, attr4));

using namespace std;
using namespace ns3;
using namespace ns3::rapidnet;
using namespace ns3::rapidnet::vtbp;
using namespace ns3::rapidnet::vtbpquery;

ApplicationContainer apps;
ApplicationContainer queryapps;

void 
initApps()
{
    NodeContainer mainAppNodes;
    mainAppNodes.Create (3);

    NodeContainer queryAppNodes;
    queryAppNodes.Create (1);

    NodeContainer csmaNodes;
    csmaNodes.Add(mainAppNodes);
    csmaNodes.Add(queryAppNodes);

    CsmaHelper csma;

    NetDeviceContainer csmaDevices;
    csmaDevices = csma.Install (csmaNodes);

    InternetStackHelper stack;
    stack.Install (csmaNodes);

    Ipv4AddressHelper address;
    Ipv4Address base = "10.1.1.0";

    address.SetBase (base, "255.255.255.0");
    address.Assign (csmaDevices);

    apps.Add(Create<VtbpHelper>()->Install(mainAppNodes));
    queryapps.Add(Create<VtbpQueryHelper>()->Install(queryAppNodes));

    SetMaxJitter (apps, 0.001);
    SetMaxJitter (queryapps, 0.001);
}

void
Load (string filename, char flag)
{
	ifstream fin(filename.c_str());
	string line;
	while (getline(fin, line))
	{
		istringstream sin(line);
		vector <string> fields;
		string field;
		while (getline(sin, field, ','))
		{
			fields.push_back(field);	
		}
		if (flag == 'e')
		{
			double pe = atof(fields[2].c_str());
			insertemission(1, fields[0], fields[1], pe);
		} 
		else if (flag == 't')
		{
			double pt = atof(fields[2].c_str());
			inserttransition(1, fields[0], fields[1], pt);
		}
		else if (flag == 'o')
		{
			int order = atoi(fields[1].c_str());
			double po = 1.0;
			insertobservation(1, fields[0], order, po);
		}
		else
		{
			cout << "error when loading data" << endl;
		} 
	}
	fin.close();
}

void
LoadData ()
{
	Load (emissionData, 'e');
	Load (transitionData, 't');
	Load (observationData, 'o');
}

void
TupleToQuery ()
{
    Ptr<RapidNetApplicationBase> queryNode = queryapps.Get(0)->GetObject<RapidNetApplicationBase>();
    inserttuple(1, "maxProb", 1, "END", "END", 5);  
}

void
Print()
{
    // PrintRelation(apps, Vtbp::EMISSION);
    // PrintRelation(apps, Vtbp::TRANSITION);
    // PrintRelation(apps, Vtbp::OBSERVATION);
    PrintRelation(apps, Vtbp::MATRIXTEMP);
    PrintRelation(apps, Vtbp::MAXPROB);
    // PrintRelation(apps, Vtbp::PROV);
	// PrintRelation(apps, Vtbp::RULEEXEC);
    // PrintRelation(apps, Vtbp::SHARESULT);

    PrintRelation (queryapps, VtbpQuery::TUPLE);
	// cout << "Size of Prov: " << apps.Get(0)->GetRelation(Vtbp::PROV)->GetAllTuples()->size() << endl;
    // cout << "Size of RuleExec: " << apps.Get(0)->GetRelation(Vtbp::RULEEXEC)->GetAllTuples()->size() << endl;
    PrintRelation (queryapps, VtbpQuery::RECORDS); //modify: add col tuple's vid (hash)
    cout<<"---------------------------"<<endl;
}


int main(int argc, char *argv[]){

    // LogComponentEnable("Vtbp", LOG_LEVEL_INFO);
    // LogComponentEnable("VtbpQuery", LOG_LEVEL_INFO);
    // LogComponentEnable("RapidNetApplicationBase", LOG_LEVEL_INFO);
    
    initApps();
    
    apps.Start (Seconds (0.0));
    apps.Stop (Seconds (10.0));
    queryapps.Start (Seconds (0.0));
    queryapps.Stop (Seconds (10.0));

    schedule (1.0, TupleToQuery);	
    schedule (2.0, LoadData);
    schedule (5.0, Print);

    Simulator::Run ();
    Simulator::Destroy ();
    
    return 0;
}

