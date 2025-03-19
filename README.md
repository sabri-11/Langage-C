Compression et Décompression de fichiers texte à l'aide du codage de Huffman.
------------------------------------------------------------------------------------------------------------------------------------------------------------------
Vous pouvez comprimer le fichier texte fourni depuis un terminal à l'aide des commandes : 
gcc -Wall -Wfatal-errors compression.c -o compression
./compression fichiers/vingtmille.txt comp

Un fichier comp sera créé, ce sera le fichier comprimé, vous pouvez vérifier la taille de ce fichier dans propriétés.

Vous pouvez ensuite décompresser ce fichier à l'aide des commandes : 
gcc -Wall -Wfatal-errors decompression.c fonctions.c -o decompression
./decompression comp decomp

Un fichier decomp sera créé, il décompresse le fichier comp et corresponds donc au fichier d'origine.

Le sujet du devoir est également disponible.

