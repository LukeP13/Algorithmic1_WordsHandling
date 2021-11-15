## INPUT:
```
# -> comentari, ignorar
%word1,word2,... -> paraules mes frequents, de mes a menys
tid,mxm_tid,idx:cnt,idx:cnt,... -> ID del "track" en el MSD, ID en el MXM, 
								index paraula : comptador paraula, ...
```

## DATA INPUT:
```
	# -> comentari, ignorar
	tid | nom_artista | titol | mxm_tid | nom_artista | titol
		tid -> ID del "track" en el Million Song Dataset
		nom_artista -> nom de l’artista en el MSD
		titol -> titol en el MSD
		mxm_tid -> ID del "track" en el musiXmatch
		nom_artista -> nom de l’artista en el MXM
		titol -> titol en el MXM
		| -> separador real: <SEP>
```

## OPERACIONS

1. Donar t´ıtol i autor d’una can¸c´o (que aparegui al 1r fitxer) a partir de qualsevol dels seus
dos codis identificadors.
2. Esborrar una can¸c´o a partir de qualsevol dels seus dos codis.
3. Dir en quines can¸cons apareix una paraula determinada (de la llista de paraules del 1r
fitxer). Donar llista amb artista i can¸c´o, ordenada per ordre alfab`etic.
4. Dir quina ´es la paraula que apareix m´es vegades en una can¸c´o determinada (a partir de
qualsevol dels seus dos codis). En cas d’empat donar-les totes, en qualsevol ordre.
5. Llistar les n paraules m´es freq¨uents en el conjunt de can¸cons, en ordre alfab`etic. Nota:
en cas d’empat llistar-les totes


##Input Example
mxm_dataset_test.txt
mxm_779k_matches.txt
GET TRAAJPW128F42311BD
GET 6452870
GET TRZZZYX128F92D32C6
GET 681124
GET LOLA
DELETE 6452870
DELETE TRAATMF128F147921E
GET TRAAJPW128F42311BD
WHERE IS cake
WHERE IS bugs
MOST FREQUENT WORD IN 3390957
LIST MOST FREQUENT 10
LIST MOST FREQUENT 1
*

