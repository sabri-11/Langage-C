Recherche d'un plus court chemin
-----------------------------------------------------------------------------------------------------------------------------------------------------------------

Vous pouvez compiler et exécuter le programme en tapant make dans un terminal si vous téléchargez le fichier make.


Un chasseur de trésors se trouve dans un bâtiment rectangulaire d’un seul étage
constitué d’un ensemble de salles de même taille et formant donc une grille n × m.
Chaque salle est repérée par ses coordonnées (i, j) et contient des objets d’une valeur
entière valeur[i,j].
Voici ci-dessous une instance possible de bâtiment. Dans chaque salle est inscrite la
valeur des objets qui s’y trouvent.

![image](https://github.com/user-attachments/assets/9d4a4f9c-6663-46d0-9740-1f27b090f356)


Le chasseur est initialement dans la salle (1, 1) (sans pouvoir ressortir du bâtiment
par celle-ci) située dans le coin supérieur gauche du bâtiment et doit atteindre l’unique
sortie par la salle (n, m) située dans le coin en bas à droite en se déplaçant successivement
d’une salle (i, j) vers la salle (i, j + 1) ou vers la salle (i + 1, j) (i.e. vers la droite ou le
bas depuis la salle où il se trouve en considérant le bâtiment vu du dessus).
Le chasseur collecte les objets dans les salles qu’il traverse. Son objectif est bien sûr
de collecter un ensemble d’objets d’une valeur totale maximale.

La grille du bâtiment est modélisé par différentes matrices de différentes tailles, vous remarquerez que
le programme récursif mets trop de temps à s'exécuter pour la matrice la plus grande.
