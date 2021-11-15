/** @file Songs.h
	@brief Classe Songs
*/

#ifndef SONGS_H
#define SONGS_H

#include "Song.h"
#include <list>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <memory>


/** @class Songs
	@brief Llista de cancons indexades per tid i mXm_tid, i una llista de paraules
	@author Lluc Pages Perez
*/
class Songs{
	public:
		/**	@brief Crea una llista de cancons, constructor per defecte
			@pre Cert
			@post Llista creada i buida */
		Songs();

		//Metodes Consultors

		/**	@brief Retorna un punter a la canco amb tid o mXm_tid igual a 'id'
			@pre Cert
			@post Si existeix una canco (tid == id) o (mXm_tid == id) retorna un punter a la canco, sino retorna un punter null */
		std::shared_ptr<Song> getSong(const std::string id) const;

		/**	@brief Retorna les cancons on hi apareix la paraula 'w'
			@pre Cert
			@post Retorna una llista de parelles <mXm_artist_name, mXm_title> de les cancons amb la paraula 'w' */
		std::set<std::pair<std::string, std::string>> songsWithWord(std::string w) const;

		/**	@brief Retorna les paraules mes frequents de la canco 'id'
			@pre Cert
			@post Si existeix una canco (tid == id) o (mXm_tid == id) retorna una llista de les paraules mes frequents, sino retorna una llista buida */
		std::list<std::string> mostFrequentWordsIn(const std::string id) const;

		/**	@brief Diu quines son les n paraules mes frequents de la llista de cancons
			@pre Cert
			@post Retorna les n paraules mes frequents en la llista de cancons */
		std::set<std::string> mostFrequentN(ushort n) const;

		bool existeix(const std::string &id) const;

		//Metodes Modificadors

		/**	@brief Afegeix una canco a la llista de cancons
			@pre No hi ha cap canco amb el mateix tid i mXm_tid a la llista de cancons
			@post La canco s'ha afegit i retorna un shared pointer a ella */
		std::shared_ptr<Song> addSong(const std::string tid, const std::string MSD_artist_name,
									  const std::string MSD_title, const std::string mXm_tid,
									  const std::string mXm_artist_name, const std::string mXm_title,const std::map<ushort,ushort>& words);

		/**	@brief Elimina la canco amb tid o mXm_tid igual a id
			@pre Cert
			@post La canco amb (tid == id) o (mXm_tid == id) eliminada, retorna si ha tingut exit */
		bool deleteSong(const std::string id);

		/**	@brief Afegeix una paraula 's' al final de la llista
			@pre cert
			@post S'ha afegit com l'ultima paraula de la llista */
		void addWord(const std::string s);

    private:
        /**	@brief Retorna l'index de la paraula s
			@pre cert
			@post retorna la posicio de l'string s a words, en cas de no existir llança una excepcio */
        ushort idxWord(const std::string s) const;

        /**	@brief Afegeix a 's' les paraules que apareixen valor vegades a _contParaules
			@pre
			@post S'ha afegit a 's' les paraules que apareixer 'valor' vegades a _contParaules */
        void afegirParaules(std::set<std::string> &s, int &valor) const;

        /**	@brief Diu quin es el valor mes alt en el vector c
			@pre cert
			@post Retorna el valor maxim dins el vector c */
        int maxValueWord() const;

        void addWords(const std::map<ushort,ushort> &w);

        void deleteWords(const std::map<ushort,ushort> &w);

        ///Atributs
        std::vector<std::string> _words;
        std::map<std::string,std::shared_ptr<Song>> _songs;
        std::vector<int> _contParaules;

};

#endif //SONGS_H
