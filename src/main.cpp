#include "Song.h"
#include "Songs.h"
#include "myexception.hpp"

#include <map>
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <iomanip>

using namespace std;


/**	@brief Mostra el titol i l'autor de la canço amb id "clau"
    @pre Cert
	@post Titol i autor amb (_tid == clau) o (_mXm_tid == clau) */
void getId(Songs &music, const string clau){
    shared_ptr<Song> s = music.getSong(clau);
    if(s != NULL){
        pair<string,string> res = s->getInfo(clau);
        cout << "Informacio de la SONG[" << clau << "]:" << endl
             << "Titol: " << res.first << endl
             << "Autor: " << res.second << endl;
    }
    else cout << "Song[" << clau << "] NO TROBADA"<< endl;
}

/**	@brief Elimina canço "clau"
    @pre Cert
	@post Canço amb (_tid == clau) o (_mXm_tid == clau) eliminada */
void deleteId(Songs &music, const string clau){
    if(music.deleteSong(clau))
        cout << "Song[" << clau << "] ELIMINADA" << endl;
    else
        cout << "Song[" << clau << "] NO TROBADA" << endl;
}

/**	@brief Mostra les cançons que tenen la paraula "clau"
    @pre Cert
	@post Mostra l'artista i el títol de les cançons amb la paraula "clau" */
void whereWord(Songs &music, const string clau){
    set<pair<string,string>> res = music.songsWithWord(clau);
    if(res.size() == 0) cout << "Paraula[" << clau << "] no trobada a cap Song" << endl;
    else{
        cout << "Paraula [" << clau << "] apareix en " << res.size() << " cancons:" << endl;
        set<pair<string,string>>::iterator it;
        for(it = res.begin(); it != res.end(); it++){
            cout << it->first << " - " << it->second << endl;
        }
    }
}

/**	@brief Mostra la paraula més frequent a la canço "clau"
    @pre Cert
	@post Mostra la paraula o paraules més frequents en la canço amb (_tid == clau) o (_mXm_tid == clau) */
void mostFreqIn(Songs &music, const string clau){
    if(!music.existeix(clau)){
        cout << "Canco [" << clau << "] NO EXISTEIX" << endl;
    }
    else{
        cout << "Paraules mes frequents en la canco [" << clau << "]:" << endl;
        list<string> lst = music.mostFrequentWordsIn(clau);
        list<string>::iterator it;
        for(it = lst.begin(); it != lst.end(); it++){
            if(it != lst.begin()) cout << ", ";
            cout << *it;
        }
        cout << endl;
    }
}

/**	@brief Mostra les n paraules més frequents en totes les cançons
    @pre Cert
	@post Mostra les n paraules més frequents en el conjunt */
void mostFreqN(Songs &music, const int n){
    set<string> res = music.mostFrequentN(ushort(n));
    set<string>::iterator it;
    cout << "Les " << n << " paraules son:" << endl;
    for(it = res.begin(); it != res.end(); it++){
        if(it != res.begin()) cout << ", ";
        cout << *it;
    }
    cout << endl;
}

/**	@brief Tracta la operacio entrada per teclat
    @pre Cert
	@post Operacio entrada per teclat realitzada */
void tractarOp(string op, Songs &music){
    string clau;
    switch(op[0]){
        case 'G':   cin >> clau;
                    getId(music, clau);         break;
        case 'D':   cin >> clau;
                    deleteId(music, clau);      break;
        case 'W':   cin >> clau >> clau; //Varies assignacions per ignorar les paraules abans de la clau
                    whereWord(music, clau);     break;
        case 'M':   cin >> clau >> clau >> clau >> clau;
                    mostFreqIn(music, clau);    break;
        case 'L':   cin >> clau >> clau; int n; cin >> n;
                    mostFreqN(music, n);        break;
    }
    cout << flush;
}

/**	@brief Seguit d'operacions realitzades
    @pre Cert
	@post Seguit d'operacions realitzades */
void Operacions(Songs &music){
    string operacio;
    cin >> operacio;
    while(operacio != "*"){
        tractarOp(operacio, music);
        cout << endl;
        cin >> operacio;
    }
}

/**	@brief Ignora els comentaris del fitxer
    @pre Cert
	@post Llegeix els comentaris de "fitxer" per poder començar a llegir dades */
void ignorarComentaris(ifstream& fitxer){
    char c;
    fitxer >> c;
    while(c == '#' && not fitxer.eof()){
        fitxer.ignore(200, '\n');
        fitxer >> c;
    }
	if (fitxer.eof()) throw myexception("No hi han cançons");
    else fitxer.unget();
}

/**	@brief  Llegeix les 5000 paraules més frequents en tot el mXm dataset
    @pre Cert
	@post Paraules de fitxer llegides */
void llegirMFW(ifstream& fitxer, Songs& music){
    char c;
    fitxer.get(c);
    if(c != '%') throw myexception("No és linea de llegir paraules");

    string p;
    for(int i = 1; i<5000; i++){
        getline(fitxer, p, ',');
        music.addWord(p);
    }
    getline(fitxer, p, '\n');
    music.addWord(p);
}

/**	@brief Llegeix les cançons dins el fitxer del mXm dataset
    @pre Cert
	@post Canço llegida desde el fitxer i guardada a lst */
void llegWordSong(ifstream& fitxer, map<string,map<ushort,ushort>> &lst){
    string clau; getline(fitxer, clau, ',');
    string aux; getline(fitxer, aux, ','); //ignorem el mXm_tid
    char c;
    ushort idx, cont;
    do{
        fitxer >> idx;
        fitxer.ignore(1);
        fitxer >> cont;
        lst[clau][idx] = cont;
        fitxer.get(c);
    }while(c != '\n');
}

/**	@brief Llegeix el fitxer de cançons MXM Dataset
    @pre Fitxer obert correctament
	@post Fitxer mXm_Dataset llegit */
void llegirMXM(ifstream& fitxer, map<string,map<ushort,ushort>>& cancons, Songs& music){
    ignorarComentaris(fitxer);
    cout << "\b\b\b\b" << " 15%" << flush;
    llegirMFW(fitxer, music);
    cout << "\b\b\b\b" << " 30%" << flush;
    char c; fitxer.get(c);
    while(not fitxer.eof()){
        fitxer.unget();
        llegWordSong(fitxer,cancons);
        fitxer.get(c);
    }
    cout << "\b\b\b\b" << " 100% " << flush;
}

/**	@brief Llegeix el fitxer de correspondencies del mXm amb el MSD
    @pre Fitxer obert correctament
	@post Fitxer MilionSongDataset llegit */
void llegirMSD(ifstream& fitxer, Songs &music, map<string, map<ushort,ushort>> &cancons){
    ignorarComentaris(fitxer);
    cout << "\b\b\b\b" << " 10%" << flush;
    string tid, msdNom, msdTitol, mxmTid, mxmNom, mxmTitol;
    do{
        getline(fitxer, tid, '<'); fitxer.ignore(5,'>');
        if(cancons.count(tid) == 1){
            getline(fitxer, msdNom, '<'); fitxer.ignore(50,'>');
            getline(fitxer, msdTitol, '<'); fitxer.ignore(50,'>');
            getline(fitxer, mxmTid, '<'); fitxer.ignore(50,'>');
            getline(fitxer, mxmNom, '<'); fitxer.ignore(50,'>');
            getline(fitxer, mxmTitol, '\n');
            music.addSong(tid, msdNom, msdTitol, mxmTid, mxmNom, mxmTitol, cancons[tid]);
        }
        else fitxer.ignore(500, '\n');

    }while(not fitxer.eof());
    cout << "\b\b\b\b" << " 100% ";
}

int main(){
    string nomFitxMXM, nomFitxMSD;
    cin >> nomFitxMXM >> nomFitxMSD;
    ifstream fitxMXM(nomFitxMXM.c_str()), correspMSD(nomFitxMSD.c_str());
    map<string,map<ushort,ushort>> wordSong; //Guarda un map de les cancons més frequents segons el tid de la cançó
    try{
        if(fitxMXM.is_open() && correspMSD.is_open()){
            Songs music;
            cout << "Llegint fitxer -> " << nomFitxMXM << "  0%" << flush;
            llegirMXM(fitxMXM, wordSong, music);
            cout << "COMPLETED" << endl << flush;
            cout << "Llegint fitxer -> " << nomFitxMSD << "  0%" << flush;
            llegirMSD(correspMSD, music, wordSong);
            cout << "COMPLETED" << endl << endl << flush;
            Operacions(music);
        }
        else throw myexception("Fitxers incorrectes");
    }
    catch (myexception e) { // El catch captura les excepcions
      cerr << e.what() << endl;
    }
    return 0;
}
