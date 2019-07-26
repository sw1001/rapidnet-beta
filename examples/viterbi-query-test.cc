#include "ns3/core-module.h"
#include "ns3/simulator-module.h"
#include "ns3/node-module.h"
#include "ns3/rapidnet-module.h"
#include "ns3/values-module.h"
#include "ns3/helper-module.h"
#include "ns3/viterbi-module.h"
#include "ns3/viterbi-query-module.h"
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
tuple (Viterbi::EMISSION, \
attr ("emission_attr1", Ipv4Value, loc), \
attr ("emission_attr2", StrValue, observed), \
attr ("emission_attr3", StrValue, state), \
attr ("emission_attr4", RealValue, prob_em))

#define transition(loc, state, state_pre, prob_tr) \
tuple (Viterbi::TRANSITION, \
attr ("transition_attr1", Ipv4Value, loc), \
attr ("transition_attr2", StrValue, state), \
attr ("transition_attr3", StrValue, state_pre), \
attr ("transition_attr4", RealValue, prob_tr))

#define observation(loc, observed, order) \
tuple (Viterbi::OBSERVATION, \
attr ("observation_attr1", Ipv4Value, loc), \
attr ("observation_attr2", StrValue, observed), \
attr ("observation_attr3", Int32Value, order))

#define insertemission(loc, observed, state, prob_em) \
app(loc)->Insert (emission(addr(loc), observed, state, prob_em));

#define inserttransition(loc, state, state_pre, prob_tr) \
app(loc)->Insert (transition(addr(loc), state, state_pre, prob_tr));

#define insertobservation(loc, observed, order) \
app(loc)->Insert (observation(addr(loc), observed, order));

//define the tuple you would like to query and how to insert it
#define tupleQuery(loc, name, attr1, attr2, attr3, attr4, attr5) \
tuple (ViterbiQuery::TUPLE, \
attr ("tuple_attr1", Ipv4Value, loc), \
attr ("tuple_attr2", StrValue, name), \
attr ("tuple_attr3", Ipv4Value, attr1), \
attr ("tuple_attr4", StrValue, attr2), \
attr ("tuple_attr5", StrValue, attr3), \
attr ("tuple_attr6", Int32Value, attr4), \
attr ("tuple_attr7", RealValue, attr5))

#define inserttuple(loc, name, attr1, attr2, attr3, attr4, attr5) \
queryNode->Insert (tupleQuery(queryNode->GetAddress(), name, addr(attr1), attr2, attr3, attr4, attr5));

using namespace std;
using namespace ns3;
using namespace ns3::rapidnet;
using namespace ns3::rapidnet::viterbi;
using namespace ns3::rapidnet::viterbiquery;

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

    apps.Add(Create<ViterbiHelper>()->Install(mainAppNodes));
    queryapps.Add(Create<ViterbiQueryHelper>()->Install(queryAppNodes));

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
			insertobservation(1, fields[0], order);
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
    inserttuple(1, "maxProb", 1, "END", "END", 5, 2.7216e-05);  
}

void
Print()
{
    // PrintRelation(apps, Viterbi::EMISSION);
    // PrintRelation(apps, Viterbi::TRANSITION);
    // PrintRelation(apps, Viterbi::OBSERVATION);
    // PrintRelation(apps, Viterbi::MATRIXTEMP);
    PrintRelation(apps, Viterbi::MAXPROB);
    // PrintRelation(apps, Viterbi::PROV);
    // PrintRelation(apps, Viterbi::RULEEXEC);
    // PrintRelation(apps, Viterbi::SHARESULT);

    PrintRelation (queryapps, ViterbiQuery::TUPLE);
    // cout << "Size of Prov: " << apps.Get(0)->GetRelation(Viterbi::PROV)->GetAllTuples()->size() << endl;
    // cout << "Size of RuleExec: " << apps.Get(0)->GetRelation(Viterbi::RULEEXEC)->GetAllTuples()->size() << endl;
    PrintRelation (queryapps, ViterbiQuery::RECORDS); //modify: add col tuple's vid (hash)
    cout<<"---------------------------"<<endl;
}


int main(int argc, char *argv[]){

    // LogComponentEnable("Viterbi", LOG_LEVEL_INFO);
    LogComponentEnable("ViterbiQuery", LOG_LEVEL_INFO);
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

