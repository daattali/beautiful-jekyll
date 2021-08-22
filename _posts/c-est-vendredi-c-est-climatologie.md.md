---
title: C'est vendredi c'est climatologie
subtitle: Filez moi une planète il faut que j'essaye des trucs...
cover-img: 
  - /assets/img/chalk-board-physics.jpg : "Photo by athree23 de Pixabay"
  - /assets/img/splash-glass.jpg : "Photo by Dawid Zawiła on Unsplash"
thumbnail-img: /assets/img/chalk-board-physics-thumb.jpg
layout: post
tags: [someone was wrong, sciences, physique, geographie, climat]
---

« *Comment ça fonctionne le climat des région du monde ?* »\\
**-- Z.**

Voilà ce qu'on m'a posé la question et bon bah comme d'hab' je vais essayer d'y répon… quoi ?! On me l'a pas vraiment demandé ?

Bon ok, techniquement ce qu'on m'a dit c'est « *Le programme de géo au collège c'est chiant* », il est possible qu'après j'ai sur-interprété la requête de mon interlocutrice…

Bon une grande partie de la géo au collège c'est apprendre où sont les trucs (continents, océan, pays…), mais aussi voir le climat des différentes régions du monde.

![](https://c.tenor.com/_aIAA5G35OcAAAAC/drunk-alcohol.gif){: width="100%" }

Alors autant la position et le nom des pays, des mers et le découpage en continent c'est vraiment arbitraire (avoir un Pakistan et un Afghanistan qui ont une frontière qui coupe littéralement le peuple Pachtoune  ça n'a aucune logique autre que "ça arrangeait bien les anglais, les perses et les russes au XIXème siècle"). Autant les climat ça c'est logique… il y a plein de machin à prendre en compte mais il y a une logique derrière !

Et si il y a de la logique derrière, PYM peut pondre un pavé dessus ! [^theorem]

[^theorem]: Ça pourrait être un théorème !

## Chapitre 1 : Pôle et équateur

Ousékifécho ?

Bon là c'est facile, vous allez me dire qu'il fait chaud à l'équateur et froid aux pôles… alors déjà je pense que peu d'entre-vous ont été le constater par eux-même (quoique… mon audience va peut-être jusqu'au bases polaires et aux bar équatoriens !). En plus on a dit qu'on essayait d'aborder ça de manière lo-gi-queu ! Donc on va pas juste affirmer qu'il fait chaud ou froid !

Alors pour ça comme pour la suite on va partir d'un modèle un poil simplifié et on complexifiera plus tard.

Modèle "un poil" simplifié de la Terre…?

![](https://c.tenor.com/BdcwU6gstRoAAAAC/pooh-think.gif){: width="100%" }

Ok on va dire que la Terre est sphérique (*c'est pas tout à fait vrai elle est aplatie aux pôles*), on va dire aussi que son axe de rotation est pas incliné (*alors qu'il l'est de 23,45°, c'est pas rien !*), bon et on va même carrément négliger totalement la rotation de la terre pour commencer (*pour être exact on va la moyenner et voir ce qui se passe sur le long terme uniquement*).

« *Quoi encore ?* \\
— *Ça serait encore plus simple si la Terre était plate…?!* \\
— *Dehors le platiste ! Tu sors !* \\
— *…* \\
— *Nan ça serait pas plus simple. En physique on aime bien les trucs rond… ça a tout plein de symétries qui facilitent tous les calcul… et ça permet de se la péter avec de sinus et des cosinus partout !* #trigoÉlitisme »

Donc notre planète ronde qui tourne pas elle se chauffe comment ?

Chaleur interne ? 🤔 le noyau interne chauffe (à cause de réaction nucléaire et de frottement du magma qui bouge) effectivement la surface… par contre il chauffe uniformément toute la surface… et vraiment pas des masses…

Alors quoi ? Bah le soleil bébé ! #seaSexAndSun

…ah bah nan… notre modèle est un peu trop simple pour "sea, sex and sun" 👉 on va oublier la ~~sea~~ et le ~~sex~~ (sorry) et on va garder juste le **sun**.

![](https://c.tenor.com/G1CpZxGWnmQAAAAC/perrie-edwards-sighs.gif){: width="100%" }

Le soleil chauffe la Terre par rayonnement, comme un lampe qui vous chauffe ta main quand tu la met devant. Donc en gros la face de la Terre qui est face au soleil devrait être uniformément chaude nan ?

Ben nan pas du tout : aviez-vous déjà remarqué que le matin et le soir il fait vachement moins chaud qu'à midi ?[^ete] Mais pourquoi donc ? Ah ah ! C'est l'heure du premier schema !

![Inclinaison des rayons solaires](/assets/img/inclinaison-des-rayons-solaires.png){: width="100%" }

Quand on prend la lumière du soleil, il est tellement loin et gros que tous ses rayon sont parallèles. Si on prend un "tube"  de rayon solaire (disons d'1m² de diamètre) il apporte une certain quantité d'énergie (donc de chaleur). Si on prend un tube qui tape à l'équateur bah voilà il tape bien à la verticale, youpi 🥵 ! Mais si il tape plus près d'un pôle... il arrive sur un sol tout incliné ! Résultat l'énergie est "étalée" sur une surface bien plus grande et comme c'est la même quantité d'énergie sur une surface plus grande ça fait moins d'énergie au mètre carré 🥶 donc il fait tout plein plus froid vu que le chauffage solaire est moins fort.
#cqfd

À l'équateur il faut donc plus chaud et au pôle plus froid.

![](https://c.tenor.com/G1HwNUeNNrcAAAAC/no-stop.gif){: width="100%" }

…ah un peu de contradiction, c'est bien ça la contradiction ! Oui mon bon Donald que veux-tu ?

« *STOP ! Moi je pense qu'on se prend la tête : si il fait plus froid au pôle c'est juste parce qu'il est plus loin du soleil que l'équateur du soleil !* \\
— *Ah oui...* \\ 
— *Et quand je test avec la lampe je vois bien que plus je suis loin moins ma main est chaude !* \\
— *Certes mon cher palmipède... certes...* \\
— *Ah ah ! Je le savais !* \\
— *Sauf que nan... déjà ta lampe elle est toute petite et proche donc ses rayons s'écartent les un des autres (ils ne sont pas parallèles) donc à la place d'un tube tu as un cône et ça fait que l'énergie "s'étale avec la distance" (en `R²` si tu veux tout savoir).* \\
— *Et c'est pas le cas avec le Soleil peut-être ?!* \\
— *Si mais sur des distance démentiellement grande... genre de l'ordre de la distance entre l'orbite de la Terre et l'orbite de Mars : 78 millions de km... et la différence entre l'équateur et le pôle en terme de distance parcouru par la lumière du soleil c'est le rayon de la Terre : 6371 km c'est-à-dire en gros 10 000 fois moins. Si la différence équateur/pôle c'était du à ça elle serait elle aussi ridicule en terme de température.* \\
— *Ah merde... ça semblait facile avec la lampe…* \\
— *Sorry Donald.* »

C'est bien l'inclinaison qui fait la différence de température épicétou !

Alors si la Terre ne tournait pas sur son axe ça serait vraiment la merde car on aurait une face cramée et une face congelée (comme c'est le cas sur Mercure) heureusement nous on a une planète qui tourne bien comme il faut comme un bon kebab : le rayonnement soleil se répartit tout bien sur tout le tour. Donc tout l'équateur est chaud et tout le tour des pôles est bien froid (entre les deux c'est ni glacé ni brûlant). \\
… \\
… \\
Bon bah voilà le climat c'est facile : il fait chaud autour et froid aux pôles !

Alors si on avait pas d'atmosphère ça serait vrai...

[^ete]: Ça se remarque bien l'été… enfin quand on a pas [un été tout pourri… ☔️](https://france3-regions.francetvinfo.fr/bourgogne-franche-comte/pourquoi-l-ete-2021-est-il-si-pourri-3-minutes-pour-comprendre-2203537.html)

## Chapitre 2 : Atmosphère, atmosphère... est-ce que j'ai une gueule d'atmosphère ?

<iframe width="560" height="315" src="https://www.youtube.com/embed/KYic1U1a6yw?start=58" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Oui je ne l'avais pas dit tout à l'heure, mais mon premier modèle c'était avec une Terre sans atmosphère aussi... mais qu'est ce que ça change ?

L'air, comme à peu près tout quand on le chauffe il prend plus de place (il se dilate, c'est lié à l'agitation des molécules... je rentre pas dans les détails) comme il prend plus de place mais qu'on va pas non plus faire "gonfler l'atmosphère" (son épaisseur est fixée par le champ de gravitation terrestre... autant dire un truc pas hyper flexible...).

Donc si notre air chauffe il ne peut pas prendre plus de place, damned ! Alors c'est la pression qui va augmenter !

Forcément là où il fait froid c'est l'inverse : l'air devrait se contracter mais il va se contenter de baisser sa pression.

Et ?

Eh ben pfffffft !

![](https://c.tenor.com/ZkBrMi_7MlsAAAAC/ariel-little-mermaid.gif){: width="100%" }

Bah oui : pfffffffffffffffffffffffff… Du vent quoi !

Quand tu a un gaz sous pression d'un côté et un gaz à basse pression de l'autre côté, qu'est-ce qui se passe ? Et ben un courant se crée de la haute à la basse pression. Jusqu'à ce que les pression s'égalise.

En gros tu as un ballon de baudruche (haute pression vu que tu as fait rentré de force de l'air dedans en soufflant comme un ouf) et une pièce à pression normale (basse par rapport au ballon). Et là tu ouvre l'embouchure du ballon[^pfff] :

![](https://c.tenor.com/p_tny-9Xgq0AAAAC/blow-blowing.gif){: width="100%" }

Oui voilà... du vent dans ta gueule ! Simple !

Sur Terre c'est pareil : 
- equateur 👉 chaud 👉 surpression
- pôle 👉 froid 👉 sous-pression

Conclusion : il y a du vent de l'équateur vers les pôles ! Tout le temps. \\
…\\
…\\
Ah on m'informe dans l'oreillette que nan c'est pas le cas : il n'y a pas un vent permanent sud-nord dans l'hémisphère nord et pas de vent permanent nord-sud dans l'hémisphère sud... Damned !

Bah faut dire que mon raisonnement avait un gros défaut : si on suis mon raisonnement très rapidement il n'y a plus d'air à l'équateur ! Tout serait aspiré vers les pôles ! Alors quoi ? Et ben on a réfléchit en 2D alors que la vraie vie c'est en 3D : l'atmosphère ça a de la hauteur ma bonne dame !

Ça change quoi ? Bah déjà l'air chaud comme ça se dilate... c'est plus léger que l'air froid (car moins dense) donc il a tendance à monter et l'air froid à descendre.
#frèreMontgolfier

![Si tu enferme ton air chaud dans un gros drap tu obtiens un ballon à air chaud cad une montgolfière](https://c.tenor.com/IEP7uGsgkwIAAAAC/gemab-mab.gif){: width="100%" }

Donc ça fait juste que notre air chaud de l'équateur monte et se décale vers le pôle. Et parallèlement l'air froid au pôle lui descend...

Mais mais mais... si à l'équateur l'air se barre en altitude... en fait au niveau du sol on a plus une surpression... on a une sous-pression (vu que tout l'air se barre). Et au pôle si l'air retombe vers le sol on a en fait une surpression !

Et bah oui : Il y a en permanence un vent que se rapproche de l'équateur : les Alizés ! Et en permanence un vent (super puissant sa mère la flûte) que s'écarte des pôle : le vent polaire !

Vous vous êtes jamais demandé pourquoi tout les explorateurs polaires on systématiquement le vent dans la gueule ? Et ben parce qu'il veut aller **VERS LE PÔLE** et que le vent polaire lui il veut pas !

![](https://c.tenor.com/rg2xhwUVLpYAAAAC/frozen-disney.gif){: width="100%" }

👆Ah nan pas elle... je vais encore avoir une chanson dans la tête[^toolate]

![Con de vent...](https://c.tenor.com/H28Qg_6XK5IAAAAC/bob-seger-seger.gif){: width="100%" }

Au final on a un vent d'altitude de l'équateur vers le pôle et un vent au sol du pôle vers l'équateur ? Nan… évidemment ça serait trop simple : il y a beaucoup trop de chemin de l'un à l'autre... résultat l'air chaud de l'équateur une fois en altitude il finit par se refroidir (vu qu'il n'est plus à l'équateur) et retomber comme une merde 💩

Où ça ? Bah ça dépend pas mal de la taille de la planète : si la Terre était plus petite ça retomberait à mi-chemin et si elle était plus grosse (comme Jupiter) ça retomberait à beaucoup plus tôt.

Sur Terre, vu le rayonnement solaire, l'épaisseur de l'atmosphère et la taille de la planète ça retombe à un tiers du chemin 👉 les tropiques !!!! (oui c'est pour ça que cette latitude chelou qui semble posé comme un cochon sur un gâteau de mariage est si importante : c'est là que l'air de l'équateur retombe).

Bon en vrai ça tombe pas pile-poil sur les tropiques... ça tombe sur la 🐎[latitude des chevaux](https://fr.wikipedia.org/wiki/Latitudes_des_chevaux)🐎.

Exactement de manière similaire le vent au sol issu des pôle continue pas indéfiniment : rapidement l'air se réchauffe et finit par monter : idem à un tiers du voyage. C'est ce qu'on appelle le front polaire a.k.a. la limite avant de se prendre un vent de merde dans la gueule.

L'air (chaud en surpression) remonte et repart vers le pôle (froid en sous-pression).

Ça forme donc ce qu'on appelle une "cellule" 🔁 : un vent qui tourne en continu : \\
⬇️ descend au pôle \\
➡️ va vers l'équateur au raz du sol \\
⬆️ monte au niveau du front polaire \\
⬅️ retourne vers le pôle en altitude

On a aussi une cellule 🔁 de chaque côté de l'équateur : \\
⬆️ monte au niveau de l'équateur \\
⬅️ va vers le pôle en altitude \\
⬇️ descend à la latitude des chevaux 🐎 \\
➡️ retourne vers l'équateur au raz du sol \\

Mais entre les deux cellules, il se passe quoi ? Ça correspond à la région tempérée du globe... c'est un peu important !

D'un côté on a le front polaire avec son air "chaud" (c'est relatif il est "moins froid que l'air polaire) qui monte... et de l'autre la latitude des chevaux avec son air "froid" qui descend. Comme l'air s'accumule au sol au niveau de des chevaux (surpression) et qu'il se barre tout vers le haut au niveau du front polaire (sous-pression) 👉 paf on forme encore du vent... et de nouveau une cellule. 

Sauf qu'elle tourne à l'inverse de ses voisine : le vent au sol va de l'équateur vers le pôle et le vent en altitude du pôle vers l'équateur.

Aller hop petit schéma de tout ça :

![Voilà nos 3 cellules qui s'emboîtent bien comme des engrenages](https://upload.wikimedia.org/wikipedia/commons/thumb/b/ba/Atmospheric_circulation-fr.svg/1024px-Atmospheric_circulation-fr.svg.png){: width="100%" }

Ces 3 cellules dans chaque hémisphère explique qu'on ait 4 climats bien marqué et nettement séparés : 
- climat polaire 🥶
- climat tempéré 😎
- climat subtropical 🥵
- climat équatorial 🥵🥵

Voilà on a résolu notre problème : on a bien de l'air sur toute la surface de la terre ! Et en plus on a retrouvé des vents qui existent en vrai !

...enfin...

...là on a que des vent nord-sud ou sud-nord (ce qui est rare en vrai). Et même nos alizés et nos vents polaires, eh ben ils sont au bon endroit... mais pas complètement dans le bon sens : les alizé pousse vers l'ouest (pratique pour faire Europe-Amérique ! N'est-ce pas monsieur Colomb ?) et idem pour les vent polaires !

En plus sur mon schéma là au dessus il y a des A et des D, c'est quoi ces machins ?

## Chapitre 3 : va faire ton cours de physique dans un manège

<iframe width="560" height="315" src="https://www.youtube.com/embed/ScXxy0MI2WQ?start=20" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Alors pour nos vent ne sont pas nord-sud bien droit et tout ?! Eh ben parce que notre modèle atteint un peu ses limites : en vraie la Terre elle tourne !

Bon bah ok elle tourne… euh ça a pas l'air de changer grand chose à notre raisonnement de la faire tourner (d'ailleurs on l'avait déjà fait tourner tout à l'heure histoire de ne pas avoir une face [Dracaufeu](https://www.pokepedia.fr/Dracaufeu) 🔥 et une face [Sorbouboul](https://www.pokepedia.fr/Sorbouboul) 🧊.

Mais en fait si ça change un truc… seulement comme on a pas l'habitude de se déplacer sur un truc qui tourne (bon à part la Terre…) on est pas habitué à la physique "dans un référentiel en rotation uniforme". Utilisons donc la vraie arme de tous les physiciens, climatologues et autres géographes : les souvenir d'enfance !

![vous voyez bien, quand on était gamin on kiffait les les référentiels en rotation uniforme ! Et vous avez vu comment je portais bien la robe de princesse ?](https://c.tenor.com/LnVVa9CicNIAAAAC/flower-girl-girls.gif){: width="100%" }

[^pfff]: Je te conseille de faire l'expérience en mettant ta petite gueule devant l'embouchure du ballon... si si...
[^toolate]: Trop tard ! Libérééééééééeeeee, Délivréééééééeeeee... et vous aussi maintenant. Ça vous apprendra à lire mes notes de bas de page débiles.

### Premier souvenir d'enfance : le tourniquet

C'est cet espèce de machin qui tourne et où on peut monter sur les bords (souvent en s'accrochant à des barre pour pas ce casser la gueule) …un genre de tourne disque géant quoi…

Et ben là très très vite, même à 4 ans tu remarques qu'il y a un truc bizarre : dès que ça tourne… tu es tiré vers l'arrière. Et plus ça tourne vite, plus ça te tire fort. D'où l'intérêt des fameuses barre pour s'accrocher !

Et pourtant aucun objet ne nous attire vers l'extérieur (un aimant à nain ?!) et aucun objet ne nous repousse depuis l'intérieur (un aimant à nain mais avec le même pôle que le nain ??!?).

Nan rien de tout ça…

C'est ce qu'on appelle une pseudo-force : ça ressemble à une force sauf que ça n'a pas d'objet physique pour la créer.

Chelou vous disais-je.

En fait c'est juste que quand le tourniquet commence à tourner… ben vous bouger avec, ça vous donne une vitesse. Seulement les objet (tous les objets !!) aiment garder des trajectoire rectiligne (c'est l'inertie) donc en fait le tourniquet si vous ne vous teniez pas vous éjecterait tout de suite car vous continueriez tout droit dans le sens de la marche (on dit tangentiellement au putain de tourniquet quand on veut briller en société mais garder sa street cred')

C'est le principe de la fronde : on fait tourner un truc au bout d'une ficelle et quand on lâche il part tout droit (perpendiculairement à la ficelle… ça surprend tous les novice cui se retrouve à éborgner leurs potes à côté plutôt que les cons en face)

![David il était balèze à la fronde ! Goliath lui était plutôt balèze en pierre dans la gueule…](https://c.tenor.com/InanccWZ7rcAAAAd/david-goliath.gif){: width="100%" }

Donc la force centrifuge c'est juste ton corps qui a envie de continuer tout droit… mais comme tu vois le tourniquet fixe (bordel arrête d'agiter la tête dans tous les sens ça foire mon explication !) tu a l'impression qu'on te tire vers l'arrière.

Voilà 4 ans et on a déjà expérimenté une pseudo-force !

Bon par contre pas de bol celle-là n'a quasi aucun effet sur le climat 😅 à part aux pôles où elle contribue à rendre les vents polaires au sol encore pire : elle éloigne l'air du pôle donc pile poil le sens des vents pôlaires !

![…je le remet pour le plaisir, j'adore le voir galérer \<rire dément de méchant de James Bond\>](https://c.tenor.com/H28Qg_6XK5IAAAAC/bob-seger-seger.gif){: width="100%" }

Allons donc voir ailleurs si la pseudo-force qui nous manque y est !

### Deuxième souvenir d'enfance : le manège !

Un manège c'est le niveau au dessus du tourniquet. Déjà il tourne tout seul pas besoin de le lancer soi-même. Ensuite il y a des chevaux (rien à voir avec la latitude du même nom), des voitures, des carrosses et plein d'autre montures fantastique.

\<PYM aime les manèges\>

Mais bon quand on est gamins, on a beau nous dire de rester sur notre cheval/voiture/canard en bois… quand, comme moi vous êtes un gros punk, dès que les adultes avait la tête tournée 👉 zoooouuuuuuu tu change de monture !

Sauf que…

…là tu remarques que te déplacer du cheval A au hérisson clignotant B s'avère bordel plus compliqué. Même pire : c'est bordel plus compliqué sa mère. Pire : c'est nomdidiou plus compliqué sa grand-mère la fille de joie !

Mais pourquoi donc, mon cruel ?!

J'avais pourtant passé des semaines si ce n'est des mois entiers à maîtriser le tourniquet et sa force centrifuge : je sais que je vais subir une force chelou qui cherche à m'expulser du manège ! Mais là c'est pas pareil, certes il y a la force centrifuge, mais ça je maîtrise, mais en plus j'ai l'impression de marcher comme un vieil alcoolo après un soir de match !

![Ça va aller madame…](https://c.tenor.com/MW4184ju7VcAAAAC/stumbling-drunk.gif){: width="100%" }

Je pars du **cheval A** je vise le **hérisson clignotant B**, je compense la force centrifuge en forçant un peu vers l'extérieur proportionnellement à la vitesse angulaire et au rayon (oui petit déjà j'avais une approche assez analytique du monde). Mais nan ! Peau de zigounette ! Je me retrouve à faire une espèce de courbe merdasse et je finis sur la **luciole rose C** !

![Pourquoi !? ](https://c.tenor.com/PSGySzyYf_YAAAAC/but-why-why.gif){: width="100%" }

En fait c'est encore une pseudo-force très très chelou puissance 10 : la **force de Coriolis** !

Et elle t'empêche de marcher droit en te poussant toujours vers la droite (ou la gauche ça dépend du sens de rotation de ton manège…).

« *Je n'y crois pas ! Je suis platiste vous mentez !* » Ah notre ami platiste est de retour[^platiste]… pas de bol pour lui : même si la Terre était plate (ce qu'elle n'est pas !) pourvu qu'elle tourne, il y aurait une force de Coriolis… aller « *Couché panier le platiste !* »

![Quelle plaie…](https://c.tenor.com/jIBAZnwaM4EAAAAC/ill-be-back-sunglasses.gif){: width="100%" }

Maintenant qu'on sait qu'il y a une force en plus… essayons de la comrendre un peu. Et pour ça utilisons encore un souvenir de ~~votre~~ **mon** ~~enfance~~ **adulescence** !

[^platiste]: Mais qui l'a laissé entrer ? Moi… si on leur coupe l'accès à la science comment veux-tu qu'ils apprennent ?

### Troisième souvenir d'enfance : le manège du Palais de la Découverte

Bon ok si vous avez pas passé votre enfance à Paris c'est plus dur… mais venez faire un tour dans [ce musée tout plein d'expériences cools et de gens passionnés](https://www.palais-decouverte.fr/fr/accueil/) !

Alors c'est quoi un manège du Palais de la découverte ? C'est une plaque ronde de plusieurs mètres de diamètre, bien plate sans rien dessus à part des siège sur le tour, fort judicieusement tournés vers l'intérieur (et avec des dossier pour pas basculer comme des merdes avec la force centrifuge). En gros c'est un bar lounge qui tourne… et sans mojito… quelle honte !

Mais voyez plutôt :

<iframe width="560" height="315" src="https://www.youtube.com/embed/8H3GF8Q73a8" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

👆 Le jeu est très simple : une fois le manège en rotation il faut juste réussir à lancer la balle à une personne en face (ils disent de la faire rouler pour éviter qu'elle parte dans le décors… bon moi j'ai essayé ça fait pareil au sol ou en l'air c'est juste moins visible car on lance plus fort généralement).

Et là bordel : la balle tourne toute seule !!!!

Remarquez que la caméra est dans le manège, elle bouge avec tout le monde… mais si on avait une caméra à l'extérieur du manège et ben là on verrait… une belle ligne droite 😱 Ce qui nous donne l'impression que la balle "tourne" c'est qu'elle va tout droit et que NOUS on tourne !

![This file is licensed under the Creative CommonsAttribution-Share Alike 3.0 Unported license.](https://upload.wikimedia.org/wikipedia/commons/b/b6/Corioliskraftanimation.gif){: width="100%" }

👆 En haut la balle vu de l'extérieur immobile \\
En bas la même balle vue depuis le disque qui tourne

« *Bordel c'est magique !* \\
— *Non c'est scientifique !* \\
— *Pardon* \\
— *Ya pas de mal* »

Donc dès qu'on est sur un truc qui tourne (et où qu'on soit dessus) il faut ajouter une force de Coriolis !

La Terre tourne d'Ouest en Est donc vu depuis le Pôle nord comme le disque de ma figure d'avant : dans l'hémisphère nord la force de Coriolis est donc vers la droite (comme dans la figure). Dans l'hémisphère sud (on voit le disque par en dessous) la force est vers la gauche.

Dans tous les cas elle est toujours perpendiculaire au mouvement : elle te fait toujours tourner… d'où l'impression d'être tout bourré dans un manège : on arrive VRAIMENT pas à marcher droit !

**À retenir :**

- Coriolis hémisphère **nord** : à **DROITE**
- Coriolis hémisphère **sud** : à **GAUCHE**

Mais… on est tous sur Terre ! On devrait le sentir tout le temps !!! On devrait le voir partout ! Sauf que non ! Pourquoi ?

Bah Coriolis c'est une force ridiculement petite… elle arrive à avoir un effet notable si tu bouge pas trop vite, sur de longue distance et que tu résiste pas trop… les vents et les courants marins ça marche. À la rigueur si tu es tireur d'élite et que tu tires à plus d'1km de distance tu commence à devoir bien te faire chier car ta balle se décale avec la force de Coriolis[^kyudo][^punk]…

« *Ah mais en fait je connais ! C'est ça qui fait que le tourbillon qui se forme quand je vide ma baignoire tourne dans le sens des aiguilles d'une montre ! Et même quand tu passe l'équateur ça change de sens ! [Je l'ai vu sur Facebook](https://www.lesnumeriques.com/vie-du-net/facebook-terrain-fertile-a-la-propagation-des-fake-news-selon-une-etude-n153589.html) !!!* »

![Tiens ça faisait longtemps…](https://c.tenor.com/WQkVAtajaR4AAAAC/vampire-diaries-eye-roll.gif){: width="100%" }

Bon déjà on prend pas ses infos scientifiques sur Facebook… ensuite tu peux essayer : tourne avec ton doigt dans le sens inverse avant de vider ta baignoire et pouf le tourbillon sera dans le sens inverse ! Pour que ça marche il faudrait un bassin circulaire de plusieurs kilomètres ! Et même là l'effet serait minime. Nan ce qui joue le plus c'est la forme de ta baignoire et l'agitation de l'au avant de la vider.

Et j'avais vérifié ça à 9 ans ! Le matos pour vérifier ça c'est : une baignoire (ou un lavabo), de l'eau et un doigt bordel !!!

Bref… back to the climat.

Qu'est ce que ça change à notre modèle ?

Bas tous nos vent, genre tous, vont tourner ! Par exemple nos alizés de l'hémisphère nord qui jusqu'ici allaient de la latitude des chevaux jusqu'à l'équateur (du nord au sud) maintenant tourne à droite… donc vers l'ouest ! Ça tombe bien… Christophe Colomb sinon il aurait eu du mal à traverser l'Atlantique !

Non seulement tous nos gros vent vont virer à droite ou à gauche… mais il y a mieux : dès que quelque-part il y a un basse pression (pour quelque raison que ce soit) il devrait y avoir du vent vers le milieu de cette basse pression pour "boucher le trou". Un genre de "convergence de vent".

Oui mais là aussi Coriolis : le vent va aller vers le centre de la basse pression… mais en tournant à droite (dans l'hémisphère nord). On obtient alors un tourbillon qui s'enroule dans le sens des aiguilles d'une montre. En météo on appelle ça une "dépression" et vous en voyez tous les jour sur les photos satellite de la météo !

À l'opposé si il y a une surpression le vent devrait rayonner depuis cette surpression sauf que Coriolis ta mère : ça tourne à droite 👉 tourbillon mais dans le sens inverse des aiguilles d'une montre ! En météo (pour des raisons historiques) on appelle ça un anticyclone. Idem vous en voyez tous les jours à la météo.

« *Mais pourquoi anticyclone ?* » Rhaaaaa j'aurais du m'y attendre… bah c'est simple, une dépression qui tourne mal (beaucoup de vent, très humide et chaude) ça donne un cyclone, pas cool… et assez vite on à remarqué qu'avant un cyclone il y avait une baisse de pression (vu que c'est une dépression) mais que si la pression restait haute bah jamais cyclone 👉 haute pression = anti-cyclone

Et pourquoi seul les tourbillons des dépression font de la merde ? Bah la basse pression donc ça crée un effet d'aspiration au niveau de sol… ou de la mer et donc ça "pompe" de l'humidité en permanence. Les anticylone eux avec leurs haute pression plaque l'humidité au sol. #cqfd

Re-voyons notre schema de tout à l'heure il va maintenant prendre tout son sens :

![Voilà nos 3 cellules qui s'emboîtent bien comme des engrenages](https://upload.wikimedia.org/wikipedia/commons/thumb/b/ba/Atmospheric_circulation-fr.svg/1024px-Atmospheric_circulation-fr.svg.png){: width="100%" }

[^kyudo]: Les archers japonais qui pratiquaient le Kyudo (art martial du tir à l'arc) pouvaient toucher une cible à plus de 800m voir plus… là aussi il devait compenser la force de Coriolis… généralement sans avoir la moindre idée de son existence !!! Costauds les loulous !
[^punk]: Au palais de la découverte le manège tourne assez vite pour que tout soit affecté… donc si vous vous déplacez pour aller vous asseoir au siège d'en face (ce qui est interdit) vous aller tituber comme jamais. Je le sais je l'ai fait #punkNotDead
<!--stackedit_data:
eyJoaXN0b3J5IjpbMTY2NTE3MjA0LDE5MTM5MjMyMjQsNTk0MT
YwMTQzLC04MjIwNzUzMDIsODI1MDg5NzU2LDE5MjA5NDc1MDUs
LTIwMjQ5MjU4NjRdfQ==
-->