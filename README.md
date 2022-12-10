# Titre : 
Estimation du prix
***

# Date & groupe : 
10/12/2022 - Projet de Ing1 GM1 
***

# Auteurs : 
Melisande Clisson & Lucie Charrier
***

# Compilation : 
make all
***

# Description : 

* On va estimer le prix de logements grace a l'utilisation d'un tableau representant le fichier.

* On commence par creer un tableau reprenant les elements du fichier.
* Chacun des elements du tableau contient lui-meme un tableau avec les distances qu'il a avec chaque autre logement.
* On randomise le tableau pour comparer les elements avec un nouveau logement.
* Puis on calcule la distance du premier logement du tableau avec chaque autre bien, en fonction de une ou plusieurs caracteristiques.
* Ensuite on trie le tableau de distance du logement en question en mettant les plus proches logements a cote.
* On Estime le prix du logement en fonction des k premiers logements les plus proches du tableau.
