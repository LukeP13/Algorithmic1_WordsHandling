#include "Song.h"
#include "Songs.h"
#include "myexception.hpp"

#include <vector>
#include <map>
#include <list>
#include <set>
#include <string>
#include <iostream>
#include <memory>
#include <algorithm>

using namespace std;

/*** CONSTRUCTOR ***/
Songs::Songs(){
    _words.clear();
    _songs.clear();
    _words.push_back("NULL");
    _contParaules.clear();
    _contParaules.push_back(0);
}


/*** MÈTODES CONSULTORS ***/
shared_ptr<Song> Songs::getSong(const string id) const{
    map<string,shared_ptr<Song>>::const_iterator it = _songs.find(id);
    shared_ptr<Song> res;
    if(it == _songs.end()) res = nullptr;
    else res = it->second;
    return res;
}

set<pair<string,string>> Songs::songsWithWord(string w) const{
    set<pair<string,string>> res;
    res.clear();
    ushort idx = idxWord(w);
    if(idx != 0){
        pair<string,string> aux;
        map<string,shared_ptr<Song>>::const_iterator it;
        for(it = _songs.begin(); it != _songs.end(); it++){
            if(it->second->haveWord(idx)){
                aux.first = it->second->mXm_artist_name();
                aux.second = it->second->mXm_title();
                res.insert(aux);
            }
        }
    }
    return res;
}

list<string> Songs::mostFrequentWordsIn(const string id) const{
    list<string> res;
    shared_ptr<Song> s = getSong(id);
    list<ushort> lst = s->mostFrequentWordIdxs();
    list<ushort>::iterator it;
    for(it = lst.begin(); it != lst.end(); it++){
        res.push_back(_words[*it]);
    }
    return res;
}

set<string> Songs::mostFrequentN(ushort n) const{
    set<string> res;
    int mxValue = maxValueWord();
    for(int i = 0; i < n; i++){
        afegirParaules(res, mxValue);
        mxValue--;
    }

    return res;
}

shared_ptr<Song> Songs::addSong(const string tid, const string MSD_artist_name,
                                const string MSD_title, const string mXm_tid,
                                const string mXm_artist_name, const string mXm_title,const map<ushort,ushort>& words){
    shared_ptr<Song> sNew(new Song(tid, MSD_artist_name, MSD_title, mXm_tid, mXm_artist_name, mXm_title, words));
    addWords(words);
    _songs[mXm_tid] = sNew;
    _songs[tid] = sNew;
    return sNew;
}

bool Songs::deleteSong(const string id){
    map<string,shared_ptr<Song>>::iterator it = _songs.find(id);
    bool trobada = false;
    if(it != _songs.end()){
        deleteWords(it->second->paraules());
        trobada = true;
        if(id == it->second->tid())
            _songs.erase(it->second->mXm_tid());
        else
            _songs.erase(it->second->tid());

        _songs.erase(it);
    }
    return trobada;
}

void Songs::addWord(const string s){
    _words.push_back(s);
    _contParaules.push_back(0);
}

bool Songs::existeix(const string &id) const{
    map<string,shared_ptr<Song>>::const_iterator it = _songs.find(id);
    return (it != _songs.end());
}

/*** MÈTODES PRIVATS ***/

ushort Songs::idxWord(const string s) const{
    ushort cont = 0;
    bool trobat = false;
    while(not trobat and cont < _words.size()){
        if(_words[cont] == s) trobat = true;
        else cont++;
    }
    if(not trobat) cont = 0;

    return cont;
}

void Songs::afegirParaules(set<string> &s, int &valor) const{
    vector<int>::const_iterator it = find(_contParaules.begin(), _contParaules.end(), valor);
    while(it == _contParaules.end()){
        valor--;
        it = find(_contParaules.begin(), _contParaules.end(), valor);
    }
    for(unsigned i = 0; i < _contParaules.size(); i++){
        if(_contParaules[i] == valor) s.insert(_words[i]);
    }
}

int Songs::maxValueWord() const{
    vector<int>::const_iterator res = max_element(_contParaules.begin(), _contParaules.end());
    return *res;
}

void Songs::addWords(const map<ushort,ushort> &w){
    map<ushort,ushort>::const_iterator it;
    for(it = w.begin(); it != w.end(); it++){
        _contParaules[it->first] += it->second;
    }
}

void Songs::deleteWords(const map<ushort,ushort> &w){
    map<ushort,ushort>::const_iterator it;
    for(it = w.begin(); it != w.end(); it++){
        _contParaules[it->first] -= it->second;
    }
}
