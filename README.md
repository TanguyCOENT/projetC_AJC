# Projet en C

## Partie 1

Dans un cadre de renforcement sécuritaire de son infrastructure, la société SecU vous charge de développer une bibliothèque de fonctions en langage C.  

- generate_password
- is_password_strong
- cypher_rotate
- get_file_header
- is_file_png
- html_minifier

<br>

__generate_password__  
Entrée: longueur du mot de passe, présence de caractères spéciaux (0/1)  
Sortie: chaîne de caractères aléatoire contenant des lettres de l’alphabet (minuscule et majuscule), des chiffres et, selon paramétrage, des caractères spéciaux.  
Exemple d’utilisation: generate_password(10, 1) => pM2ga_bn1#  
<br>

__is_password_strong__  
Entrée: chaîne de caractères  
Sortie: 1 si la chaîne réunit toutes ces conditions:  
- de longueur 10 au moins
- contient au moins une majuscule
- contient au moins un chiffre
- contient au moins un caractère spécial  

0 sinon.  
Exemple d’utilisation: is_password_strong(“abc”) => 0   
<br>

__cypher_rotate__  
Implémentation du chiffrement par décalage/rotation (cf chiffre de César)  
Entrée: chaîne de caractères, sens de la rotation, longueur du décalage  
Sortie: chaîne de caractères avec décalage des caractères  
La rotation ne se fera que pour les lettres de l’alphabet minuscules.  
Exemple d’utilisation: cypher_rotate(“ab2aZ”, 0, 1) => “bc2bZ”    
Lien (Chiffre de César en python): https://www.tutorialspoint.com/cryptography_with_python/cryptography_with_python_caesar_cipher.htm  
<br>

__get_file_header__  
Entrée: fichier binaire  
Sortie: format de fichier trouvé (parmi ceux recherchés)  
On se limitera à rechercher les formats de fichier suivants: jpg, png, exe, pdf, doc  
Lien: https://en.wikipedia.org/wiki/List_of_file_signatures  
<br>

__is_file_png__  
Entrée: fichier binaire  
Sortie: 1 si le fichier est au format PNG, 0 sinon  
<br>

__html_minifier__  
Entrée: fichier html avec indentations et sauts de ligne  
Sortie: fichier html sans indentations et sans sauts de ligne    
Vous pouvez tester la fonction sur le fichier projet.html présent dans le dépôt  
