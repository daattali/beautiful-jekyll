---
layout: post
title: Tutoriel Shiny app
subtitle: Premières étapes avec Shiny
bigimg: /img/path.jpg
---

Pour améliorer la compréhension de l'information dans les rapports et les résumés des résultats nous allons mettre en œuvre un outil pour la visualisation directe. La bibliothèque Shiny du logiciel R open source permet le développement des applications Web interactives par le biais du programme de R, sans avoir besoin de connaissances avancées dans HTML ou JavaScript. 
Le terme «interactive» implique que l'utilisateur peut interagir avec l’interface grâce à l'introduction de widgets, qui sont des éléments graphiques (boîtes qui permettent le choix des variables, la saisie de texte, des listes d'objets, des boutons ou des icônes représentant des actions, etc.) qui permettent à l'utilisateur de communiquer avec le système d'information qui est "derrière" l’application Web.

###Structure d'une application Shiny

Les applications Shiny ont deux composantes:
• un script d'interface utilisateur (ui.R)
• un script de serveur (server.R)

Le script d'interface utilisateur est un fichier de texte qui doit être nommé ui.R, qui contiendra le code qui permettra la visualisation des composants du site Web et qui contrôle l'apparence de l'application: l'agencement du texte, des tableaux, des graphiques et des objets, les couleurs, le type police, etc.
Le script de serveur c’est un fichier de texte qui doit être nommé server.R, qui contiendra des instructions requises par le serveur pour générer l'application.
Afin de faciliter la lecture des codes, nous pouvons utiliser un dossier www, qui contiendra les fichiers nécessaires pour faire fonctionner le site: images, logos, etc. Et un dossier R pour stocker les fonctions purement de R.
Ces trois éléments doivent être stockés ensemble dans le même répertoire.

Afin que l'application fonctionne correctement, le code inclus dans les fichiers ui.R et server.R doivent répondre à certaines exigences :
•	Le fichier ui.R doit commencer par shinyUI(fluidPage ()) et le fichier
server.R par shinyServer (function (input, output){}); le code restant doit être écrit
à l'intérieur des parenthèses qui accompagnent la fonction fluidPage et
dans les accolades qui accompagnent la fonction de function (input, output) respectivement (voir exemple __).
•	Chaque élément interactif introduit en ui.R (ce qui signifie qui provient d'une demande de l'utilisateur au serveur) doit avoir sa contrepartie dans le fichier server.R. En revanche, des éléments statiques, telle que le titre de la page web, des images qui servent à l’agencement visuel de la page doivent seulement apparaitre dans le fichier ui.R.

Il y a trois groupes principaux de commandes Shiny.

•	Les commandes qui définissent l'interface graphique de l’utilisateur, soit le moyen par lequel l'utilisateur communique avec l'application web. Shiny offre une grande variété d'interfaces différentes (voir Table __ et/ou Figure __)
•	Les commandes pour la création d’objets web qui déterminent le type d'objet qui sera
retourné par le serveur. Shiny permet de créer des images, des tableaux, des graphiques, etc., à la fois statiques et interactives.
•	Les commandes d’insertion d'objets Web: une fois l'objet créé, ces commandes permettent l'affichage sur le Web. Chaque type de commande de création est associé à une commande particulière d’insertion (voir Tableau __)
Pour un fonctionnent correct, chacune des applications ou des widgets créés avec Shiny doit contenir la commande qui définissent l'interface de l’utilisateur, la commande de création de l'objet web et la commande d’insertion.
Si vous n'avez toujours pas installé le package Shiny, ouvrez une session R, connectez-vous à Internet et lancez :
install.packages("shiny") 
library(Shiny).
Si vous souhaitez approfondir sur ‘utilisation de Shiny ; vous pouvez aller sur le site http://shiny.rstudio.com/tutorial/
