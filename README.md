compilation et lancement depuis un terminal :

gcc -Wall -Wfatal-errors vigenere_codage.c -o vigenere_codage && ./vigenere_codage text.txt mdp text_crypte.txt

(remplacer mdp par le mot de passe avec lequel vous voulez crypter le message, essayez avec java pour retrouver le même message).

------------------------------------------------------------------------------------------------------------------
Bonjour, 
Ce programme permet de chiffrer un texte à l'aide du codage de Vigenère.

Le chiffre de Vigenère consiste, comme pour le chiffre de César, à décaler chaque lettre du texte avec un décalage bien précis. Le décalage à effectuer n’est cependant pas le même selon la position de la lettre dans le texte.

Imaginons que l’on souhaite chiffrer la phrase "la programmation, c’est vraiment bien !" (juste les
lettres, on ne touche pas aux signes de ponctuation). On choisit tout d’abord un mot de passe que le
destinataire du message doit aussi connaître : par exemple, choisissons "java" comme mot de passe. Le
mot de passe doit alors être transformé en une série de nombres, chacun correspondant à la position de
la lettre dans l’alphabet : ici, "java" devient 10-1-22-1. 
Pour chiffrer le message, on décalera la première lettre de 10 places, la seconde d’une place, la troisième
de 22 places, la quatrième de 1 place, puis on boucle : la cinquième lettre sera décalée de 10 places, la
sixième lettre sera décalée d’une place, etc...
Notre message devient alors :
(regarder avec le mode "code" pour une meilleure compréhension)

l  a  p  r  o  g  r  a  m  m  a  t  i  o  n, c ’ e  s  t  v  r  a  i  m  e  n  t  b  i  e  n  !                                                      
10 01 22 01 10 01 22 01 10 01 22 01 10 01 22 01  10 01 22 01 10 01 22 01 10 01 22 01 10 01 22

----------------------------------------------------------------------------------------------------------------
v  b  l  s  y  h  n  b  w  n  w  u  s  p  j,  d ’ o  t  p  w  b  b  e  n  o  o  p  c  s  f  j  !


On voit dans le résultat que deux lettres différentes à l’origine peuvent devenir la même lettre dans
le message crypté, et deux lettres similaires dans le message original peuvent devenir différentes dans le
message crypté.


Ce chiffrage a été utilisé pour la première fois pendant le 16ème siècle, et resta invaincu pendant près de trois siècles.
