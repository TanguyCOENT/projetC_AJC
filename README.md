Ecrire les programmes suivants:

file_merge
html_checker
base_converter
lipsum (facultatif)
file_merge
Programme fusionnant (concaténant) et "défusionnant" des fichiers. Le programme prendra par la ligne de commande le noms de fichiers à fusionner. Sortie: fichier unique créé par la fusion des fichiers pris en entrée
Le programme, par une option -u, devra "unmerge" le fichier

Trouver un moyen de stocker dans le fichier de sortie, les informations vous permettant de "défusionner" les fichiers par la suite.
Des fichiers de différents types pourront être fusionnés.

Exemples d'utilisation de la commande:
file_merge file1.png file2.png file3.pdf => output: fichier files.merge
file_merge -u files.merge => output: fichiers file1.png file2.png file3.pdf


html_checker
Le programme vérifiant le bon format (partiel) d'un fichier html. Le programme vérifiera que chaque balise ouvrante parmis celles recherchées est accompagnée de la balise fermante correspondante.
Balises recherchées:

<strong>, <p>, <h1>, <h2>, <a>
Exemples d'utilisation de la commande:
html_checker file.html => output: ok
html_checker file_bad.html => output: not ok


base_converter
Programme donnant deux autres bases à partir d'une fournie en entrée. Bases prises en compte: binaire (2), décimale (10), hexadécimale (16)
Option indiquant la base de départ: -b (2, 10, 16)

Exemples d'utilisation de la commande:
base_converter 42 -b 10 => output: 101010 (2) 2A (16)
base_converter 2A -b 16 => output: 101010 (2) 42 (10)


lipsum (facultatif)
Programme générant du texte aléatoire. En vous inspirant du site suivant: https://www.lipsum.com/ écrire un programme permettant de générer un nombre de mots ou de paragraphes via des options de ligne de commande. Ces mots ou paragraphes seront du texte "lipsum", c'est à dire des termes inspirés du latin choisis au hasard parmi un dictionnaire de mots.
Les paragraphes seront de longueur variable.

Exemples d'utilisation de la commande:
lipsum -w 5 => output (5 mots): Suspendisse at risus nisi. Nullam.
lipsum -p 3 => output (3 paragraphes):

Aenean molestie ut turpis at semper. Sed tincidunt consectetur finibus. Nullam nec nunc pretium, ullamcorper sem sed, sodales mi. In iaculis pretium urna, ac laoreet magna auctor ac.

Morbi dapibus sapien quis euismod rutrum. Pellentesque placerat risus eu ultricies malesuada. Praesent eu ex maximus, porttitor magna sit amet, rutrum neque. Maecenas eleifend tincidunt congue. Nulla efficitur lectus mauris, et commodo velit placerat eu. Quisque blandit lectus tristique, porta velit ac, faucibus massa. Fusce eu rutrum metus. Ut mollis velit velit, sed porttitor justo imperdiet nec. Quisque vehicula augue consectetur elit egestas sodales. Phasellus elementum, sapien ut gravida vestibulum, felis est dictum est, finibus vehicula felis eros eget risus. Mauris gravida leo at felis ornare, eu pellentesque metus semper. Proin id convallis massa. Etiam elementum, nibh ut dignissim finibus, leo tellus vulputate felis, at pellentesque lacus est ut sem. Quisque et lacinia quam.

Integer efficitur sollicitudin sodales. Vivamus feugiat nibh nec est vestibulum, blandit dictum felis semper. Ut tristique orci vitae ullamcorper euismod. Pellentesque in malesuada ante. Cras convallis feugiat nisi viverra vulputate. Aliquam accumsan vulputate justo porta euismod. Phasellus ligula orci, ullamcorper et ultricies vel, rutrum vitae leo. Vestibulum eleifend turpis a justo eleifend ultricies. Duis nec dapibus urna, faucibus pharetra velit.


