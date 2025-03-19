Bonjour, 
Ce programme permet de chiffrer un texte à l'aide du codage de César.

Le chiffre de César consiste à décaler, dans un message, toutes les lettres d’un certain nombre de
places. Par exemple, si le décalage vaut trois, alors la lettre ’a’ devient ’d’, ’b’ devient ’e’, ..., ’z’ devient
’c’. Le destinataire du message doit connaître ce décalage afin de pouvoir l’appliquer (de façon inversée)
sur le message chiffré et obtenir le message.

Vous pouvez tester ce programme en le compilant depuis un terminal à l'aide de la commande :
gcc -Wall -Wfatal-errors cesar_codage.c -o cesar_codage

puis en l'exécutant avec la commande (en remplaçant decalage par le nombre de votre choix) :
./cesar_codage mon_fichier.txt decalage sortie.txt

par exemple vous pouvez l'exécuter avec : ./cesar_codage mon_fichier.txt 3 sortie.txt
alors le décalage de votre message chiffré sera de 3 par rapport au fichier d'origine.
