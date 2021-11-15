#include "Song.h"
#include <string>
#include <list>
#include <map>
#include <iostream>
#include <memory>

using namespace std;

///Constructor
Song::Song(){
    _tid = _MSD_artist_name = _MSD_title = _mXm_tid = _mXm_artist_name = _mXm_title = "NULL";
}

Song::Song(const string tid, const string MSD_artist_name, const string MSD_title,
           const string mXm_tid, const string mXm_artist_name, const string mXm_title, map<ushort,ushort> words){
    _tid = tid;
    _MSD_artist_name = MSD_artist_name;
    _MSD_title = MSD_title;
    _mXm_tid = mXm_tid;
    _mXm_artist_name = mXm_artist_name;
    _mXm_title = mXm_title;
    _paraules = words;
}

///Destructor
Song::~Song(){
    //dtor
}

///Mètodes Consultors
ushort Song::count(ushort idx) const {
//Pre: --
//Post:  says which is the count for index idx
    ushort res = 0;
    map<ushort,ushort>::const_iterator it = _paraules.find(idx);
    if(it != _paraules.end()) res = it->second;
    return res;
}

list<ushort> Song::mostFrequentWordIdxs() const{
// Pre: --
// Post: returns the indices of the most frequent words in this song
    map<ushort,ushort>::const_iterator it =_paraules.begin();
    list<ushort> res;
    if(it != _paraules.end()){
        res.push_back(it->first);
        it++;
    }
    map<ushort,ushort>::const_iterator it2;
    while(it != _paraules.end()){
        it2 = _paraules.find(res.front());
        if(it->second > it2->second){
            res.clear();
            res.push_back(it->first);
        }
        else if(it->second == it2->second){
            res.push_back(it->first);
        }
        it++;
    }
    return res;
}

bool Song::haveWord(const ushort w) const{
    map<ushort,ushort>::const_iterator it = _paraules.find(w);
    return (it != _paraules.end());
}

string Song::mXm_artist_name() const{ return _mXm_artist_name; }

string Song::mXm_title() const{ return _mXm_title; }

string Song::tid() const{ return _tid; }

string Song::mXm_tid() const{ return _mXm_tid; }

pair<string,string> Song::getInfo(const string id) const{
    pair<string,string> res;
    if(id == _tid){
        res.first = _MSD_title;
        res.second = _MSD_artist_name;
    }
    else{
        res.first = _mXm_title;
        res.second = _mXm_artist_name;
    }
    return res;
}

map<ushort,ushort> Song::paraules() const{
    return _paraules;
}

///Mètodes Modificadors

void Song::addWord(ushort idx, ushort cnt){
//Pre: There is no word with index idx in this song
//Post: The pair <idx,cnt> has been added to the set of words of this song
    _paraules[idx] = cnt;
}

