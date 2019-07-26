/* _*_ Mode:C++; c_file_style:"gnu"; indent_tabs_mode:nil; _*_ */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111_1307  USA
 */

#include "ns3/core-module.h"
#include "ns3/simulator-module.h"
#include "ns3/node-module.h"
#include "ns3/rapidnet-module.h"
#include "ns3/values-module.h"
#include "ns3/helper-module.h"
#include "ns3/acquaintance-module.h"
#include "ns3/list-value.h"
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list> 


#define KnowObs \
"./data/acquaintance/knows_obs.txt"

#define KnowObsBack \
"./data/acquaintance/knows_obs.bak"

#define LikeObs \
"./data/acquaintance/likes_obs_back.txt"

#define LikeObsBack \
"./data/acquaintance/likes_obs_back.bak"

#define LiveObs \
"./data/acquaintance/lived_obs.txt"

#define LiveObsBack \
"./data/acquaintance/lived_obs.bak"

#define KnowTar \
"./data/acquaintance/knows_target.txt"

#define KnowTru \
"./data/acquaintance/knows_truth.txt"


#define live(local, person, city) \
tuple (Acquaintance::LIVEEVENT, \
attr ("liveEvent_attr1", Ipv4Value, local), \
attr ("liveEvent_attr2", Int32Value, person), \
attr ("liveEvent_attr3", Int32Value, city))

#define like(local, person, hobby) \
tuple (Acquaintance::LIKEEVENT, \
attr ("likeEvent_attr1", Ipv4Value, local), \
attr ("likeEvent_attr2", Int32Value, person), \
attr ("likeEvent_attr3", Int32Value, hobby))

#define know(local, person1, person2, state, path) \
tuple (Acquaintance::KNOWEVENT, \
attr ("knowEvent_attr1", Ipv4Value, local), \
attr ("knowEvent_attr2", Int32Value, person1), \
attr ("knowEvent_attr3", Int32Value, person2), \
attr ("knowEvent_attr4", Int32Value, state), \
attr ("knowEvent_attr5", ListValue, path))

#define relation(local, person1, person2) \
tuple (Acquaintance::RELATION, \
attr ("relation_attr1", Ipv4Value, local), \
attr ("relation_attr2", Int32Value, person1), \
attr ("relation_attr3", Int32Value, person2))


#define insertknow(local, person1, person2, state, path) \
app(local)->Insert(know(addr(local), person1, person2, state, path)); \

#define insertlike(local, person, hobby) \
app(local)->Insert(like(addr(local), person, hobby));

#define insertlive(local, person, city) \
app(local)->Insert(live(addr(local), person, city));

#define insertrelation(local, person1, person2) \
app(local)->Insert(relation(addr(local), person1, person2));



using namespace std;
using namespace ns3;
using namespace ns3::rapidnet;
using namespace ns3::rapidnet::acquaintance;


map<string, int> people;
map<string, int> cities;
map<string, int> hobbies;

ApplicationContainer apps;

vector<string> readFile(string filename){
	vector<string> re;
	string s;
	ifstream f(filename.c_str(), ios_base::in);

	while(!f.eof()){
		getline(f, s);
		re.push_back(s);
	}
	f.close();
	return re;
}


void parse(vector<string> know_obs,
		   vector<string> live_obs,
		   vector<string> like_obs
){

	// first parse know_obs
	int num_people = 0;
	for(int i=0; i<know_obs.size()-1; i++){
		string know = know_obs[i];
		if(know.size()==0) continue;
		int l = 0;
		while(know.at(l)!=' ') l++;
		string person1 = know.substr(0, l);
		l++;
		string person2 = know.substr(l, know.length()-l);
		if(people.count(person1)==0){
			people.insert(pair<string, int>(person1, people.size()));
			cout << person1 << ' ' << num_people << endl;
			num_people++;
		}
		if(people.count(person2)==0){
			people.insert(pair<string, int>(person2, people.size()));
			cout << person2 << ' ' << num_people << endl;
			num_people++;
		}
		cout << people[person1] << ' ' << people[person2] << endl;
		list< Ptr<Value> > p;
		Ptr<Value> p1 = (Ptr<Value>) Create<Int32Value>(people[person1]);
		Ptr<Value> p2 = (Ptr<Value>) Create<Int32Value>(people[person2]);
		p.push_back(p1);
		p.push_back(p2);
		
		// p.push_back(people[person1]);
		// p.push_back(people[person2]);
		insertknow(1, people[person1], people[person2], 1, p);
	}	
	cout << endl;

	cout << "live size: " << live_obs.size() << endl;
	for(int i=0; i<live_obs.size(); i++){
		cout << live_obs[i] << endl; 
	}

	// parse live_obs
	for(int i=0; i<live_obs.size()-1; i++){
		string live = live_obs[i];
		if(live.size()==0) continue;
		int l = 0;
		while(live.at(l)!=' ') l++;
		string person = live.substr(0, l);
		l++;
		string city = live.substr(l, live.length()-l);
		if(people.count(person)==0)
			people.insert(pair<string, int>(person, people.size()));
		if(cities.count(city)==0)
			cities.insert(pair<string, int>(city, cities.size()));
		// cout << people[person] << ' ' << cities[city] << endl;
		insertlive(1, people[person], cities[city]);
	}
	cout << endl;

	cout << "likes size: " << like_obs.size() << endl;
	for(int i=0; i<like_obs.size(); i++){
		cout << like_obs[i] << endl;
	}

	//parse like_obs
	for(int i=0; i<like_obs.size()-1; i++){
		cout << i << endl;
		string like = like_obs[i];
		if(like.size()==0) continue;
		int l = 0;
		while(like.at(l)!=' ') l++;
		string person = like.substr(0, l);
		l++;
		string hobby = like.substr(l, like.length()-l);
		if(people.count(person)==0)
			people.insert(pair<string, int>(person, people.size()));
		if(hobbies.count(hobby)==0)
			hobbies.insert(pair<string, int>(hobby, hobbies.size()));
		// cout << people[person] << ' ' << hobbies[hobby] << endl;
		insertlike(1, people[person], hobbies[hobby]);
	}
}

void Print(){
	PrintRelation(apps, Acquaintance::KNOW);
	PrintRelation(apps, Acquaintance::LIVE);
    PrintRelation(apps, Acquaintance::RELATION);
	// PrintRelation(apps, Acquaintance::LIKE);

	// PrintRelation(apps, Acquaintance::PROV);
}


void train(){
	vector<string> know_obs = readFile(KnowObsBack);
	vector<string> live_obs = readFile(LiveObs);
	vector<string> like_obs = readFile(LikeObs);
	parse(know_obs, live_obs, like_obs);
}



int main(int argc, char *argv[]){

	apps = InitRapidNetApps (3, Create<AcquaintanceHelper> ());
	SetMaxJitter (apps, 0.001);

	apps.Start (Seconds (0.0));
	apps.Stop (Seconds (10.0));

	schedule (2.0, train);
	schedule (5.0, Print);

	Simulator::Run ();
	Simulator::Destroy ();

	return 0;

}
	






