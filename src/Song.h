/** @file Song.h
	@brief Classe Song
*/

#ifndef SONG_H
#define SONG_H

#include <list>
#include <string>
#include <map>

using namespace std;

typedef unsigned short ushort;

/** @class Song
	@brief Canco de la base de dades de musiXmatch
	@author Lluc Pages Perez
*/

class Song{
    public:
        /**	@brief Crea una canco buida, constructor per defecte
			@pre Cert
			@post Canco creada -> strings igual a NULL i map '_paraules' buit */
        Song();

		/** @brief Crea una canco a partir de les dades donades a la funcio
			@pre Cert
			@post Canco creada i valors assignats */
        Song(const string tid, const string MSD_artist_name, const string MSD_title,
             const string mXm_tid, const string mXm_artist_name, const string mXm_title, map<ushort,ushort> words);

		/**	@brief Destructor de Song
			@pre Cert
			@post objecte eliminat
		*/
        ~Song();

        //Mètodes consultors

		/** @brief Retorna el numero de vegades que apareix la paraula amb index idx a la canco
			@pre Cert
			@post Diu quin es contador per l'index idx */
        ushort count(ushort idx) const;

		/** @brief Diu quines son la/les paraules mes frequents en la canco
			@pre Cert
			@post Retorna l'index de les paraules mes frequents en la canco */
        list<ushort> mostFrequentWordIdxs() const;

        /** @brief Diu si la paraula w hi es a la canco
			@pre Cert
			@post Retorna si canco w trobada */
        bool haveWord(const ushort w) const;

        /**	@brief Diu quin és el nom de l'artista segons mXm
			@pre Cert
			@post Retorna el nom de l'artista segons la base de dades mXm */
        string mXm_artist_name() const;

        /**	@brief Diu quin és el titol de la canco segons mXm
			@pre Cert
			@post Retorna el titol de la canco segons la base de dades mXm */
        string mXm_title() const;

        /**	@brief Diu quin és el tid de la canco segons MSD
			@pre Cert
			@post Retorna el tid de la canco segons la base de dades MSD */
        string tid() const;

        /**	@brief Diu quin és el tid de la canco segons mXm
			@pre Cert
			@post Retorna el tid de la canco segons la base de dades mXm */
        string mXm_tid() const;

        /**	@brief Retorna les paraules dins la canço
			@pre Cert
			@post Retorna el map de paraules de la canco */
        map<ushort,ushort> paraules() const;

        //Mètodes modificadors
		/**	@brief Afegeix l'index i el numero de vegades que apareix una paraula en la canco
			@pre No hi ha una paraula amb l'index idx en la canco
			@post La parella <idx,cnt> s'ha afegit a la llista de paraules de la canco */
        void addWord(ushort idx, ushort cnt);

        /**	@brief Retorna el títol i l'autor de la canço
			@pre (id == _tid) o (id == _mXm_tid)
			@post Retorna una parella de strings amb el títol i l'autor segons MSD o mXm */
        pair<string,string> getInfo(const string id) const;
    private:
        string _tid;
        string _MSD_artist_name;
        string _MSD_title;
        string _mXm_tid;
        string _mXm_artist_name;
        string _mXm_title;
        map<ushort,ushort> _paraules;

};

#endif // SONG_H
