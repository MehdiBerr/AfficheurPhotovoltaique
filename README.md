<html>
<head>
</head>
<body>
<div style="text-align: justify">

* [Afficheur éolienne et Banc de test Photovoltaïque](#Afficheur-éolienne-et-Banc-de-test-Photovoltaïque)
* [Afficheur Photovoltaïque](#Afficheur-Photovoltaïque)

# Afficheur éolienne et Banc de test Photovoltaïque


## Membres de l'équipe

Emre KORKMAZ

Leon PEYRAT

Hugo PIETRI

![](Images/Circuit_assemble_1.JPG)



## I-Introduction

Ce projet a pour but la réalisation d'un dispositif de mesure de la production électrique et de la vitesse de rotation d'une éolienne de particulier, avec afficheur et interface web.

Le projet doit s'adapter aux éoliennes du réseau français Tripalium : https://www.tripalium.org/

Lui-même basé sur le réseau Windempowerment : https://windempowerment.com/

Il y a plusieurs modèles d’éoliennes qui ont des tensions allant de 12 V à 350 V et des puissances pouvant atteindre 2000 W pour la plus grande éolienne (4 m 20 de diamètre). Nous n'adapterons pas notre dispositif pour la version haute tension 350 V ni pour la version 12 V qui délivre directement une tension continue.
Les courants maximums mis en jeux vont de 4 A pour la plus petite éolienne en 48 V à plus de 80 A pour la plus grande en 24 V.

La mesure de vitesse de rotation doit se faire en exploitant le signal triphasé sortant directement de l’éolienne. La mesure de tension et de courant (permettant d’en déduire la fréquence) se fait après le module redresseur de tension, donc en signal continu. 

On doit indiquer les mesures sur des afficheurs dont l’un visuel et didactique (du type rangée de led qui s’allume plus si la puissance produite est plus importante). 

Le système doit être autonome et alimenté directement par l’éolienne (donc nécessité d’une batterie pour l’alimenter en l’absence de vent)


## II-Fonctionnement global de la carte :

### II.1-Partie puissance (alimentation des composants et batterie) :

La carte peut être alimentée de 2 manières : soit par un connecteur micro-USB, soit directement par la tension redressée générée par l’éolienne. Le choix d’alimentation est à effectuer au moyen d’un interrupteur. 
Dans le cas de l’alimentation par l’éolienne, la tension d’entrée est abaissée et régulée à 5 V par un circuit BUCK. Celui-ci accepte en entrée des tensions allant de 6 à 60 V, ce qui lui permet de fonctionner correctement avec les éoliennes 24 et 48 V, et de fournir 5 V même pour des vitesses de rotation de l’éolienne faibles.

Les 5 V en sortie de ce BUCK permettent d’alimenter le circuit de charge de la batterie, le capteur de courant, et l’éventuel vu-mêtre externe.

Comme son nom l’indique, le circuit de charge et protection batterie permet de gérer la charge de la batterie et lui assurer une protection contre les décharges profondes. 

Le régulateur 3,3V a pour objectif de fournir une tension stable pour les composants nécessitant cette tension d’alimentation. C’est le cas de l’ESP32 ou de certains circuits intégrés. 

### II.2-Partie mesures :

La carte est capable de mesurer 3 grandeurs physiques : la tension et le courant en continu, ainsi que la vitesse de rotation de l’éolienne.

La mesure de tension est effectuée par un AOP monté en non inverseur associé à un pont diviseur de tension. La tension est directement prélevée sur le bornier d’alimentation de la carte.

La mesure de courant utilise un capteur à effet Hall dans lequel on fait passer un fil traversé par le courant à mesurer. Il existe plusieurs modèles de ce capteur destinés à mesurer des courants maximums allant de 5 à 50 A. Ce capteur fonctionnant en 5 V et pas en 3,3 V comme l’ESP, on passe par l’intermédiaire d’un circuit d’adaptation de tension.

La mesure de vitesse de rotation est une mesure de fréquence : elle est effectuée sur le signal alternatif en sortie de l’éolienne et entre 2 phases. 
Un bornier présent sur la carte permet de les connecter. Le signal sinusoïdal est d’abord réduit en tension par un pont diviseur, il passe ensuite par un amplificateur d’isolement pour éviter que des surtensions endommagent la carte, puis un AOP monté en bascule de Schmitt non inverseuse permet de le transformer en signal carré plus facilement traitable par l’ESP.


### II.3-Partie affichage :

Les mesures sont affichées sur un site web en local. Pour y accéder, il faut d’abord indiquer dans la zone code prévue à cet effet le nom du réseau WIFI ainsi que le mot de passe pour s’y connecter. 
Une fois le programme téléversé, ouvrez le moniteur série, l’adresse IP de la page web à rentrer dans le navigateur devrait être affichée.

## III-Cahier des charges avec ses fonctions de contraintes 

 
|   | FONCTIONS DE SERVICE     | CRITERES      | NIVEAUX    |  
|---------|---------|--------|-------|
| FP                                                   | Réalisation d'un dispositif de mesure de la production et de la vitesse de rotation d'une éolienne de particulier, avec afficheur et interface web | Précision du système             | 2° de liberté         |  
| FC1                                                  | Conception                        |                                                  |       |  
| FC1-1                                                | Alimentation de la maquette       | Batterie rechargée par la production éolienne    | autonomie d'une semaine sans vent  |  
| FC1-2                                                | Simplicité de fabrication         |              |             |  
| FC1-3                                                | Liaison sans fil                  | Bonne portée                                     | 100m                               |  
| FC1-4                                                | Afficheur de données n°1                                                                                                                           | lisible et précis                                | affichage LCD numérique            |  
| FC1-5                                                | Afficheur de données n°2                                                                                                                           | Ludique, visuel                                  |                                    |  
| FC1-6                                                | Données consultables depuis un smartphone                                                                                                          | facile d'accès et fonctionnelle                  |                                    |  
| FC2                                                  | Mesures                                                                                                                                            |                                                  |                                    |  
| FC2-1                                                | Capteur de courant                                                                                                                                 | Angle de résolution minimal                      | à 0,1A près                        |  
| FC2-2                                                | Mesure de tension                                                                                                                                  | Précis                                           | à 0,1V près                        |  
| FC2-3                                                | Mesure de fréquence                                                                                                                                | Précis                                           | au demi Hertz près                 |  
| FC2-4                                                | Placement des capteurs n'influençant pas le résultat de la mesure                                                                                  |                                                  |                                    |  
| FC2-5                                                | Adaptable sur toute la game d'éoliennes de différentes puissances                                                                                  | Maximiser la précision de mesure dans chaque cas |                                    |  
| FC3                                                  | Coût du dispositif                                                                                                                                 | accessible                                       | moins de 50 €                      |  
| FC5                                                  | Respect du temps imparti pour la réalisation                                                                                                       | contrainte imposée par les enseignants           | Avant mi-janvier                   |  




## IV-Circuit et PCB

Le circuit électrique du dispositif est disponible ici : https://easyeda.com/Hupigotri/compteur_eolienne


## V-Détails pour la réplication du projet

Le circuit et les documents associés sont disponibles en open source et peuvent-être répliqués ou réutilisés sans contraintes.



### V.1-Versions de la carte

#### V.1.a-Version 1.0

Lien du circuit de cette ancienne version : https://easyeda.com/Hupigotri/compteur_eolienne_copy


##### V.1.a.1-Réglage de la carte

Pour téléverser le code, vous aurez besoin d'une carte usb vers uart comme celle à cette adresse : https://fr.aliexpress.com/item/33000531104.html

Lors du téléversement, NE PAS CONNECTER LE VCC sauf si c'est la seule alimentation de l'ESP (ni usb, ni éolienne, ni batterie), il ne faut jamais connecter 2 alimentations ensemble, sinon des composants peuvent griller.

Une fois tous les composants placés sur la carte, il faut régler les 2 potentiomètres. Il est nécessaire de disposer d’un oscilloscope pour cette opération connecté entre la masse et le GPIO 32 de l’ESP. Pour cela, dévissez complètement le potentiomètre n°R33 ce qui a pour effet de mettre sa valeur à son maximum (100 kΩ) et d’annuler la fonction d’hystérésis (seuil basculement haut = seuil basculement bas). 
Ensuite balayez toute la plage de résistance avec le potentiomètre R34 jusqu’à obtenir un signal carré, puis ajustez le pour se rapprocher le plus possible d’un signal de rapport cyclique 0,5. La tension de seuil moyenne a bien été définie.

Ensuite revenez sur le potentiomètre R33 qui permet de fixer les seuils inférieurs et supérieurs de basculement. Cette valeur est un compromis entre des seuils très différents pour éviter des erreurs dus à des parasites ou au bruit, et des seuils proches permettant de mesurer la fréquence même lorsque l’éolienne tourne très lentement et sa tension de sortie est faible. Donc les résultats de mesure de fréquence sont erronés, vissez ce potentiomètre jusqu’à obtenir des valeurs cohérentes, et vissez quelques tours de plus afin de garantir une marge de sécurité.


##### V.1.a.2-Erreurs de conception

-	Le 5 V de sortie du buck n’est pas relié à l’entrée 5 V du capteur de courant, il est nécessaire de souder un fil en externe entre la pin « chargein5v » du contrôleur de charge U1 et le pad 5V de la résistance R25. 
-	Un problème de conversion de tension est présent entre le capteur de courant et l’ESP ce qui limite le courant mesurable à seulement 56 % du courant nominal maximum du capteur de courant (8,5 A dans le cas du capteur 15 A)
-	L’interrupteur de sélection de l’alimentation est inversé : sur la position « éolienne » la carte est alimentée par USB, et inversement.
-	Les potentiomètres sont câblés en inverse, donc lorsque l’on visse la résistance augmente pour l’un et diminue pour l’autre ce qui peut porter à confusion.
-	Pour la sortie vers un éventuel vu-mêtre basé sur des LEDS WS2812, en plus des pin de masse et GPIO19, il y a un VCC (3,3V) alors que ldes leds fonctionnent en 5V.
-	Le dessin PCB du support pour batterie est le mauvais, il est trop petit comparé au support reçu.

#### V.1.b-Version 1.1 

Une nouvelle version de la carte qui corrige les erreurs de conception citées ci-dessus est disponible au lien suivant (même lien que celui indiqué au début du GitHub) : 
https://easyeda.com/Hupigotri/compteur_eolienne

Détail des corrections :

-	Le 5 V de sortie du buck est maintenant bien relié à l’entrée 5 V du capteur de courant, l'étiquette « chargein5v » a été transformée en étiquette d'alimentation et renommée « 5V » pour simplifier la nomenclature.
-	Le problème de conversion est résolu : le transistor a été remplacé par un simple pont diviseur de tension.
-	L’interrupteur de sélection de l’alimentation n'est plus inversé.
-	Les potentiomètres sont bien câblés
-	Pour la sortie vers un éventuel vu-mêtre basé sur des LEDS WS2812, le troisième pin est maintenant une sortie 5V (non actif lors du fonctionnement uniquement sur batterie !).
-       ATTENTION, le support de batterie n'a pas été remplacé, il est toujours trop petit, la modification est à faire ! (non remplacé car il est probablement préférable de remplacer le support par un simple connecteur comme suggéré plus bas dans les pistes d'amélioration)


## VI-Choix et dimensionnement des composants

### VI.1-Composants pour les mesures

#### VI.1.a-L’amplificateur d’isolement AMC1200 (mesure fréquence, composant 1)

L’amplificateur d’isolement AMC1200 supporte au maximum une tension d’entrée crête à crête de 250 mV. 
On effectue un pont diviseur pour obtenir cette tension lorsque la tension max de l’éolienne est présente en entrée (lorsque les batteries sont quasiment chargées), soit 4×14,5V=58 V + 2 V de marge, donc 60 V redressés. Ces 60 V redressés correspondent à 60 ×√2 crête-à-crête, et 60×√2×√3=147 V pour la tension composée (entre 2 phases) crête-à crête. 

On calcule le rapport des résistances du pont diviseur de tension : (tension éolienne composée càc)/(tension entrée AOP)=147/0,250=588
On choisit R9=180 kΩ  et R20=300 Ω  
En plus de leur rapport, on fait attention à 2 points :
- R20 ≪ résistance entrée AMC1200 =28 kΩ 
- R9+R20 pas trop faible pour limiter la dissipation thermique (P_max=0,1 W pour les CMS R0603)


L'AMC1200 est alimenté en 3,3 V, sa sortie oscille autour de 1,27 V avec une amplitude proportionnelle à la tension en entrée. 



#### VI.1.b-AOP TLV225 (mesure fréquence, composant 2)

L’AOP TLV225 est monté en Bascule de Schmitt non inverseuse. 
Les 2 résistances (R21 + R34) et R32 sont un pont diviseur de tension permettant de définir la tension de seuil moyenne. Les 2 autres résistances (R23 + R33) et R22 permettent de fixer les seuils inférieurs et supérieurs de basculement. 
Cette tension est un compromis entre des seuils très différents pour éviter des erreurs dues à des parasites ou au bruit, et des seuils proches permettant de mesurer la fréquence même lorsque l’éolienne tourne très lentement et sa tension de sortie est faible. 

##### V.1.b.1-Compromis parasites :
Si l’on choisit des résistances (R23 + R33) et R22 avec un rapport 40 (1kΩ  et 40kΩ), on a une différence de seuil haut et bas de 0,08 V en sortie de l’AOP alimenté en 3,3V. Soit un rapport de tensions de  60/3.3≈20 , donc 0,08×20=1,6 V de variations sur la tension d’entrée. Si les parasites sont inférieurs à cette valeur, la mesure de fréquence ne sera pas faussée. 


##### VI.1.b.2-Compromis limite minimale de mesure de fréquence :
On reprend les mêmes résistances (R23 + R33) et R22 avec un rapport 40 (1kΩ et 40kΩ), on se rappelle de la différence entre seuil haut et bas de 0,08 V, on peut donc mesurer une sinusoïde qui a cette valeur crête à crête au minimum. Avec une simple règle de 3, on calcule la tension correspondante en entrée de l’AOP : (0,08×0,250)/3,3=6,06 mV 
On utilise le rapport des résistances du pont diviseur de tension calculé plus haut pour déterminer la tension minimale nécessaire à la mesure de fréquence : 6,06∙10^(-3)×588=3,56 V
Grâce aux valeurs des vitesses de démarrage de charge du livre page 86, on peut déterminer la vitesse de rotation des éoliennes pour atteindre cette tension.
Éolienne 24 V et 1m20 : (300×3,56)/24=44,5 tr/min ou 0,74 Hz
Éolienne 48 V et 4m20 : (120×3,56)/48=8,9 tr/min ou 0,15 Hz


#### VI.1.c-AOP TLV225 (mesure tension)


On effectue un simple pont diviseur sur la tension redressée pour avoir une image de la tension en entrée de l’AOP. 
Cet AOP est utilisé pour prévenir du risque de détruire l’ESP : si la sortie du pont était directement reliée sur le CAN de l’ESP, une surtension sur l’entrée ferait monter la tension en entrée du CAN au-dessus de 3,3 V. 
Avec l’AOP entre les 2, ce n’est plus un problème : l’AOP peut supporter des tensions d’entrées supérieures, et étant alimenté en 3,3 V, sa sortie peut saturer mais ne dépassera jamais cette valeur ce qui évite d’endommager l’ESP.


On dimensionne à nouveau le pdt pour une tension max de 60 V : 
On choisit un gain du montage non inverseur de 1+R17/R16=1+10/10=2
Dans ce cas si on veut 3,3 V en sortie au maximum, il nous faut 3,3/2=1,65 V maximum en entrée de l’AOP. 
Le pont diviseur de tension doit donc avoir un rapport min de 60/1,65=36,36 
On choisit 100 kΩ et 2,7 kΩ (rapport de 37,03)


#### VI.1.d-Capteur à effet Hall CSM015SPT5 (mesure courant)

Il existe plusieurs modèles de ce capteur destinés à mesurer des courants maximums allant de 5 à 50 A. 
Ce capteur fonctionnant en 5 V et délivre une tension de 2,5 V pour un courant nul. Ensuite cette tension varie linéairement jusqu'à 4,5 V pour le courant maximum du modèle de capteur choisi, et jusqu'à 0,5 V pour le courant équivalent mais négatif. 
Comme il fonctionne en 5 V et pas en 3,3 V comme l’ESP, on passe par l’intermédiaire d’un circuit d’adaptation de tension. 
On a choisi un circuit classique bidirectionnel composé d'un transistor LBSS138LT1G. 



### VI.2-Composants pour l'alimentation (Buck 5V)

On veut un buck acceptant une tension d'entrée allant jusqu'à 60 V. Pour cela il y a des contrôleurs pour buck particuliers. C'est le cas du LM296HV que nous avons choisi d'utiliser. 

Ce choix a été fait car c'est le composant présent sur la carte suivante et qu'il fonctionnait parfaitement lors des tests :
https://www.aliexpress.com/item/32842453339.html?

Les condensateurs situés en entrée et sortie doivent aussi supporter les tensions maximales à l'entrée et à la sortie respectivement. 
Le choix plus complexe a été celui de l'inductance du circuit


On cherche à la dimensionner afin d'être capable de fournir un courant de 2,5A en sortie.
Pour cela on utilise d’abord la relation d’entrée-sortie : BuckOut = α×Eol_continue  

On connait par ailleurs, grâce à la datasheet, la période de hachage : T =6,67µs et on a fixé l’inductance L2=33µH

On veut Iméd=2,5A on cherche donc à dimensionner IL2MAX sachant qu’on peut calculer l’ondulation de courant dans L2 donné par la relation suivante :
 ∆IL= I_L2MAX  - I_L2MIN  =  ((Eol_continue×T))/L2×α(1-α)  
 
On a l’ondulation maximale pour α=0,5 donc lorsque Eol_continue =10V et BuckOut =5V

On a ∆ILmax=((Eol_continue×T))/(4×L2)=0,5A

On a donc I_L2MAX  = I_méd  +(∆I_Lmax)/2 
AN : I_L2MAX  =2,75A 

On choisit finalement un Inductance I_L2MAX=2,7A



### VI.3-Composants pour la gestion de charge de la batterie

Pour ce bloc fonctionnel on s'est grandement inspiré de deux exemples de circuits de gestion de batterie très similaires :

Celui de GreatScott : https://www.instructables.com/DIY-LiPo-ChargeProtect5V-Boost-Circuit/

Celui d'électronoob : https://electronoobs.com/eng_circuitos_tut49.php

Le seul composant à modifier en fonction de l'utilisation est la résistance placée entre le pin "PROG" du TP4056 et la masse. En effet cette résistance permet de régler le courant de charge de la batterie. On a choisi une résistance de 2 kΩ ce qui définit un courant de charge de 580 mA. Les batteries lithium-ion 18650 que l'on utilise peuvent-être endommagées avec un courant plus élevé. Si l'on souhaite doubler l'autonomie, on peut placer 2 batteries en parallèle, et dans ce cas on peut aussi doubler le courant de charge. Il faut cependant veiller à ce que l'alimentation (le buck 5V et l'alimentation USB) puisse délivrer le courant nécessaire.

La partie Boost 5V présente dans ces deux circuits n'a pas été concervée car les composants nécessitant une alimentation 5V que nous utilisons sont directement reliés à la sortie 5V du Buck sur la carte. Le 5V n'est donc présent que lorsque l'éolienne tourne, mais ce n'est pas un problème puisque seul le  capteur de courant fonctionne en 5V, et le courant est nul lorsque l'éolienne est à l'arrêt. 


### VI.4-Microcontrôleur (ESP32)

Le choix du microcontrôleur s'est porté sur un ESP-WROOM-32U. 
Il est en effet largement utilisé dans l'industrie et facile à programmer. 
Nous l'avons préféré par rapport à un ESP8266 car il est plus rapide, dispose de plus de GPIO, supporte plus d'interruptions et dispose de plus d'entrées analogiques. Il est donc moins restrictif quant à une amélioration future de la carte nécessitant plus de ressources et périphériques.

Dans sa version 32U, il dispose d'un connecteur IPEX permettant de lui attacher une antenne externe. Cela permet d'améliorer la portée WIFI de l'ESP32, notamment en choisissant une antenne à fort gain et en la placant judicieusement.



##   VII-Explications du code

Ce code a été développé sous un environnement arduino. Pour s’assurer son bon fonctionnement, vous devez télécharger les librairies arduino compatibles avec l’Esp32. Le lien suivant vous guidera pour votre installation : https://projetsdiy.fr/installer-esp-idf-esp32-ide-arduino-macos-windows-raspberry/


###   VII.1-Code pour le capteur de tension

Nous avons relié le capteur de tension au pin numéro 34 de notre microcontrôleur. Ainsi, la tension mesurée, qui varie entre 0 et 3,3 V arrive par ce pin. Nous le configurons comme une entrée pour l’esp. L’esp va convertir, via un convertisseur analogique-numérique, cette tension en une valeur allant de 0 à 4096. Les valeurs ici sont binaires et chaque état de tension correspond à un bit. Le 4096 correspond à la valeur maximale de tension fournie par l’éolienne et le 0 à la valeur minimale. Ensuite, nous reconvertissons les valeurs binaires pour arriver à la valeur réelle de la tension fournie par l’éolienne. Afin d’obtenir les valeurs les plus proches de la réalité, nous avons utilisé une fonction affine (y=ax+b). Les coefficients a et b ont été déterminés grâce à un étallonage. Cette fonction permet d’enlever les petites imprécisions du capteur et du CAN.


###   VII.2-Code pour le capteur de courant

Le code du capteur de courant est presque similaire à celui réalisé pour la mesure de tension. Le pin utilisé ici est le pin 35. Il est lui aussi configuré en entrée. On réalise les mêmes conversions que pour la tension. L’esp reçoit une tension entre 0 et 3.3V qu’il convertit en une valeur binaire comprise entre 0 et 4096. Nous retrouvons cette fois-ci le courant fourni par l’éolienne grâce à un polynôme du second degré de la forme a*x²+b*x+c. Un second degré a été choisi car la mesure n'était pas parfaitement linéaire.


###    VII.3-Code pour le capteur de fréquence
Le code pour cette mesure est différent et plus difficile que celui réalisé pour les deux premières mesures. L’initialisation reste, cependant, identique : le pin 32 correspond à l’entrée sur laquelle arrive l’information. Ensuite, nous avons utilisé une interruption pour mesurer la durée d’un créneau de tension car le signal de tension est reçu par l’esp sous la forme d’un signal carré. Pour obtenir la fréquence de l’éolienne, il faut prendre l’inverse de la durée d'une période, soit réaliser l’opération : 1/durée. L’interruption intervient pour mesurer cette durée. En effet, dans notre programme, à chaque fois que la tension va passer de l’état haut (3.3V) à l’état bas (0V), le programme principal va se stopper. L’interruption est prioritaire sur ce dernier. Il reprendra lorsque la tension passera de l’état bas à l’état haut. L’arrêt du programme principal est très court (quelques microsecondes) et nous permet, via une fonction comptant le temps appelée timer, d’obtenir la valeur de la durée. Grâce à l’opération F=1/durée, on obtient la fréquence de l’éolienne. 


## VIII-Atteinte des objectifs

•  Les fonctionnalités
--> Le circuit répond aux exigences primaires exposées dans le cahier des charges : il mesure la tension, le courant et la fréquence, il fonctionne sur batterie, et les grandeurs calculées sont affichées sur une page WEB et sur un écran LCD.

•  Les performances techniques :

L’autonomie : 
--> le circuit consomme 120 mA en fonctionnement normal sous une tension batterie de 3,7 V. La batterie fait 2500 mAh, donc l’autonomie est de 2500/120 = 20,8 heures. C’est moins que la semaine espérée dans le cahier des charges, mais néanmoins largement suffisant pour éviter des redémarrages intempestifs à chaque rafale de vent.

La mesure de tension : 
--> le CAN est de 12 bits donc on a une précision de 60V/2^12 = 0,0146 V. En réalité, sa qualité moyenne amène à des fluctuations qui diminue cette précision à 0,1 V environ. Cette précision est correcte.
	
	
La mesure de courant : 
--> la tension de sortie du capteur varie de 2,5 à 4,5 V, ramené dans la plage 1,65 à 2,97 V, soit un ΔV = 1,32 V. La précision est donc de (1,32×2^12)/3,3=1638 bits. Pour le capteur 15 A, cela correspond à 15/1638 = 9,15 mA. Mais comme pour la mesure de tension, la qualité du CAN amène à des fluctuations qui limitent la précision à environ 100 mA. Ce n’est pas une très bonne précision.


La mesure de fréquence : 
--> D’après nos mesures, la mesure de fréquence et donc de vitesse de rotation est précise à ± 2 %. C’est une valeur correcte.

•  Le coût
--> Une carte revient à 45€ avec ses composants, on est donc bien en dessous des 50 € indiqués dans le cahier des charges.
En revanche, les composants SMD ne sont pas soudés. Si on les fais souder par le fabricant de la carte, il facture un surcoût de 32€, soit 77€ au total.


## IX-Pistes d’amélioration

- Code pour un réglage des potentiomètres sans oscilloscope
- Code pour commander un vu-mêtre connecté à la sortie prévue pour
- Amélioration de l’interface de l’écran avec d’autres menus et d’autres informations
- Ajout d’un circuit permettant de changer la plage de tension de sortie du capteur de courant de 2,5 → 4,5 V à 0 → 5 V
- Remplacer le support de la batterie par un simple connecteur pour réduire la taille de la carte et augmenter les possibilités de choix et agencement de batterie

# Afficheur Photovoltaïque

## Sommaire

* [Membres de l'équipe de l'afficheur photovoltaïque](#Membres-de-l'équipe-de-l'afficheur-photovoltaïque)
* [Introduction](#Introduction)
* [Choix de la lampe](#Choix-de-la-lampe)
* [Choix du panneau photovoltaïque](#Choix-du-panneau-photovoltaïque)
* [Choix des gradateurs](#Choix-des-gradateurs)
* [Calcul de la section des conducteurs et dimensionnement des protections](#Calcul-de-la-section-des-conducteurs-et-dimensionnement-des-protections)
* [Caractérisation du panneau photovoltaïque](#Caractérisation-du-panneau-photovoltaïque)
* [Utilisation de la carte MPPT LibreSolar](#Utilisation-de-la-carte-MPPT-LibreSolar)
* [Mise en réseau et gestion des données du banc de test](#Mise-en-réseau-et-gestion-des-données-du-banc-de-test)
* [Création d'un site en débarqué](#Création-d'un-site-en-débarqué)
* [Création d'un site en embarqué](#Création-d'un-site-en-embarqué)
* [Conclusion](#Conclusion)
* [ Perspective d'amélioration](#Perspective-d'amélioration)

## Membres de l'équipe de l'afficheur photovoltaïque

Mehdi Berrada

Adrien Merel

Youcef Amine Aissaoui

Eliza Filip

Adam Mezaber

## Introduction 

Ce projet a pour but la création d’un banc de test photovoltaïque pour la caractérisation de cartes MPPT (Maximum Power Point Tracking). La première carte est la carte LibreSolar open source. La seconde est une carte industrielle. Pour ce faire, nous allons commander et récupérer un certains nombres de composants tels que des lampes, un panneau photovoltaique ou encore un capteur de luminosité que nous allons assembler pour obtenir au final une puissance de sortie maximale sur les MPPT. L'objectif sera, en plus de la réalisation du banc de test, la visibilité des mesuresdes courants-tensions-puissances en temps réelvia une interface web. Des pages web seront donc embarquées dans le microcontroleur ESP32 et devrons être accessible via un PC ou un smartphone. 

La figure suivante explique schématiquement la structuration du banc d’essai :

![](Images/Schema_projet.PNG)

## Choix de la lampe

Notre PRT consiste à tester et comparer deux MPPT : un Libre Solar en open source ainsi qu’un MPPT industriel.

Ces derniers permettent de prendre la valeur maximale de puissance en sortie d’un panneau photovoltaïque, et ce, à tout instants. Pour procéder aux tests, nous utiliserons un panneau solaire 100W que nous éclairerons avec des lampes fournissant près de 1000W au total. 

Le but étant de se rapprocher des conditions standards de test, il est très important de bien choisir les lampes d’éclairage pour reproduire au mieux la puissance fixer par les STC (standard test conditions), ainsi que le spectre lumineux du soleil.
Nous allons dons vous présenter ici notre choix de lampe et les raisons de ce choix.

Pour les tests à réaliser, nous avons choisit de prendre deux lampes halogènes de 400W chacune. En effet, nous voulons en sortie du panneau photovoltaïque 100W. Or, nous savons que ce dernier dispositif possède un rendement de près de 10%. Ainsi, deux lampes de 400W (800W au total) va nous permettre de nous rapprocher au maximum des 100W voulus.
Nous avons fait le choix de prendre ce kit de lampe là (et non deux lampes de 500W chacune) car il est livré avec un trépied qui nous permettra d’ajuster facilement la distance source lumineuse – panneau photovoltaïque et d’ajuster l’angle d’impact de la lumière sur le panneau pour tester plusieurs plages de spectre.
Aussi, le prix de ce dispositif (environ 50€) nous parait très correct.
En ce qui concerne le type des lampes, ce sont des lampes halogènes. Nous avons fait le choix de prendre des lampes halogènes pour avoir des lampes fournissant près de 400W et qui rentrent dans notre budget. De plus, le spectre d’une lampe halogène présente quasiment la même allure que le spectre du soleil en après-midi et en fin de journée. Il convient donc pour ces tests.

![](Images/spectre_2.PNG)

Ci-dessous, le lien vers le trépied halogène de chez RS :

https://fr.rs-online.com/web/p/projecteurs-de-chantier/7918267/

## Choix du panneau photovoltaïque

Les contraintes que nous avons pour le choix du panneau sont les suivantes :

-	Puissance délivrée d’environ 100W
-	Prix le plus faible possible
-	Fournisseurs : RS
 
Afin de respecter ces trois contraintes nous avons choisi le panneau suivant à près de 146€ :

https://fr.rs-online.com/web/p/panneaux-solaires/1881234/?fbclid=IwAR1PjmZR-h3LvUEhJExDubokRcnUdeqzKAehREmtDqtzwf_Se5cUT-zvQHs

Il s’agit d’un panneau photovoltaïque monocristallin comportant 36 cellules et délivrant une puissance crète d’environ 100W. Ses caractéristiques principales sont résumées dans l’extrait de la datasheet suivant :

![](Images/datasheetPV.PNG)

Avec ce panneau et nos lampes, nous nous attendons à avoir une puissance délivrée en sortie de 80 à 100W. Cette dernière nous permettrait de caractériser correctement nos convertisseurs MPPT.

## Choix des gradateurs

Il n’est pas nécessaire de rappeler que le but de notre PRT est de tester deux cartes MPPT.
Ainsi, une des conditions de test à prendre en compte est l’éclairage du panneau photovoltaïque. Dans un premier temps, à l’aide du trépied-support des deux lampes, nous pouvons régler l’angle d’incidence de la lumière sur le panneau photovoltaïque et simuler l’angle optimal pour obtenir un maximum de puissance en sortie. Ensuite, nous voulons aussi pouvoir régler la puissance de la luminosité arrivant sur le panneau. Le but étant d’expérimenter les MPPT sous différentes puissances de luminosité et de voir comment ces derniers se comportent. Ainsi, la meilleure façon d’y arriver est d’installer un gradateur en amont de chaque lampe. Cela va nous permettre de régler à notre guise la puissance de luminosité.
Comme expliquer plus tôt, nous avons deux lampes de 400W qui vont éclairer le panneau photovoltaïque. Nous avons choisi d’installer deux gradateurs, un pour chaque lampe, pour des raisons financières. En effet, un gradateur de 800W coûte bien plus cher que deux gradateurs de 400W.

Les deux gradateurs ont été commandé sur RS Component : 

https://fr.rs-online.com/web/p/variateurs-de-lumiere/7903050/

![](Images/gradateur4.PNG)

## Calcul de la section des conducteurs et dimensionnement des protections

Calcul de la section des conducteurs par la méthode du courant Iz fictif :

Formule générale : Iz = In/(K1*K2*K3)

Avec un courant nominal de 10A (le MPPT ne pouvant supporter plus de 10A, on considère cette valeur comme nominale pour être sûr que notre câble pourra supporter le courant circulant)

Détermination de la lettre de sélection et des coefficients à partir des tables

Lettre de sélection : F

K1 = 1 (D’après le tableau correspondant à K1, la lettre de sélection F correspond à un coefficient 1)

K2 = 1 (Un seul câble)

K3 = 1,06 (D’après la lettre et la température ambiante d’environ 25°C)

Iz = 9,4A 

D’après le tableau de détermination de la section minimale, nous trouvons une section de 1,5mm²

Nous avons chercher à vérifier notre dimensionnement en utilisant un outil de calcul de section de câble.

Calcul Section Câble : https://commentcalculer.fr/calcul/section-cable/

![](Images/section.PNG)

Pour ce qui est de la protection, nous allons utiliser un fusible 10A en amont de l'alimentation de la batterie au MPPT comme indiqué sur le schéma suivant : 

![](Images/fuse.PNG)

## Caractérisation du panneau photovoltaïque

Après réception du panneau photovoltaïque, nous avons caractérisé ce dernier. Ainsi, nous avons connecté notre panneau à une charge électronique programmable et nous avons placé notre source lumineuse à 70 cm du panneau et nous l'avons orienté de façon à avoir le meilleur éclairage possible. 

Ci-dessous, vous pouvez voir une photo de l'expérience de caractérisation du panneau :

![](Images/banc_panneau.PNG)

A l'aide de la charge programmable, nous avons pu imposer un courant de sortie au panneau et donc tracer ses caractéristiques V(I) et P(I), qui ont une forme très similaire à la litérature. Les courbes sont référencées ci dessous :


![](Images/carac_panneau.PNG)

Nous remarquons que la puissance maximale du panneau avec ce niveau d'éclairage est bien en dessous de celle attendue dans notre premier dimensionnement. Nous avons donc décidé de réaliser un bilan de puissance de notre installation (Lampes / panneau / charge) pour mieux comprendre ces faibles valeurs : 

![](Images/bilan_puissance.PNG)

Nous remarquons deux points à prendre en compte :

1- Le rendement entre  la puissance électrique en entrée des lampes et la puissance lumineuse qui arrive sur le panneau est particulièrement faible en utilisant des lampes halogènes. En effet, ce type de lampe disperse beaucoup d'énergie sous forme de chaleur, ce qui réduit son efficacité.

2- Le rendement du panneau indiqué sur le bilan de puissance est celui donné par le constructeur (pour le spectre de la lumière solaire). Il se voit donc fortement réduit due aux différences de spectre entre la lampe halogène et le soleil. Ce qui va encore déteriorer le rendement de nos lampes.

Lors de notre premier dimensionnement, nous n'avions pas pris en compte de telles pertes dans les lampes halogènes, ce qui fausse la puissance de sortie. Pour corriger ce problème et avoir environ 100W en sortie, il nous faudrait environ 15 lampes 400W ! Ceci n'étant pas une solution valable au vue de notre budget initial d'environ 200€ que nous avions déjà dépensé pour nos différentes commandes. Il nous faudra donc nous contenter d'une faible puissance pour le moment. Un changement de technologie de lampe serait une piste d'amélioration pour ce projet mais le budget ne sera pas le même.

## Utilisation de la carte MPPT LibreSolar

LA carte MPPT est un système intelligent d'asservissement à base de hacheurs buck.

Afin de pouvoir utiliser le MPPT, il faut que la carte soit flasher suivant le type de batterie que l'on connecte au MPPT. En effet, d'après la documentation de LibreSolar concernant le MPPT, la partie du code gérant la batterie est différent selon le type de batterie (par exemple batterie Lithium, batterie Plomb...). Au départ, le carte est flashée pour une batterie Pb (plomb), ce qui fait que l'on a pas eu à flasher la carte puisque nous utilisons une batterie Pb (plomb).

Néanmoins,s'il nous fallait flasher la carte, voici comment se présente le processus de flashage : 

Suivant la datasheet LibreSolar, le code à flasher a été fait/écrit en C/C++ et est téléchargeble depuis la page GitHub associée au MPPT 1210 HUS.
De ce fait, il est nécéssaire de télécharger Visual Studio, un environnement de developpement, et de rajouter l'extension PlatformIO IDE pour pouvoir compiler le code sur le micrcontroleur STM32 du MPPT. Aussi, une bibliothèque spécial zephyr est à télécharger pour assurer le bon fonctionnement du code dans la carte. 
Au final, l'utilisation d'un J-link va nous permettre de transmettre le code depuis l'ordinateur jusqu'au STM32.

## Mise en réseau et gestion des données du banc de test

L'objectif de la deuxième partie de notre projet est de pouvoir utiliser les données du banc photovoltaïque. A l'aide du banc de test décrit précédemment, nous souhaitons présenter des mesures de courant, de tension et de puissance en temps réel via une interface web. Pour cela, nous utilisons le microcontrôleur ESP32, sur lequel nous allons embarquer notre serveur web, également disponible via un smartphone ou d'autres appareils électroniques avec accès au wifi.
<br/>

### DISPOSITIFS UTILISÉS
* ESP32
<br/>
L'ESP32 est un système bon marché, efficace et extrêmement populaire qui vous permet de construire des appareils communiquant via WiFi et Bluetooth. Ce module est le successeur du système ESP8266. La nouvelle version est équipée d'un microcontrôleur plus efficace, grâce auquel elle s'inscrit encore mieux dans la tendance IoT. ESP32 est une puce SoC (System-on-a-chip). Ce système intègre les éléments nécessaires à la communication via WiFi et Bluetooth, ce qui le rend idéal pour la construction d'appareils Internet des objets relativement bon marché et économes en énergie. Le système est principalement équipé d'un capteur tactile, que nous utilisons pour simuler une mesure de la température de l'environnement.

![](Images/ESP32.jpg)
<br/>

* MPPT
<br/>
Ce contrôleur de charge est un tracker de point de puissance maximale (MPPT), qui s'adapte automatiquement sa tension d'entrée au panneau solaire connecté pour extraire autant de puissance que possible. La fonction MPPT ne peut être réalisée qu'à l'aide d'un convertisseur DC/DC, qui constitue la partie centrale de la charge PCB du contrôleur. Il peut être reconnu par le grand inducteur et la grande entrée et sortie électrolytiques condensateurs de filtrage.

![](Images/MPPT.jpg)
<br/>

### MPPT
En raison de la non-linéarité des caractéristiques I-U du panneau photovoltaïque, sa puissance maximale est obtenue lorsqu'il fonctionne au point d'inflexion. Pour que le panneau fonctionne à son point optimal, l'algorithme de suivi du point de puissance maximale (MPPT) doit être utilisé dans la structure de contrôle. L'objectif principal du suivi MPP est de maintenir le générateur photovoltaïque en fonctionnement au point d'inflexion I(U), quels que soient les changements de température et d'ensoleillement. En raison de l'ombrage partiel des panneaux solaires connectés en série, par exemple en raison de la couverture nuageuse, plusieurs points d'inflexion apparaissent sur la caractéristique I(U). Les méthodes MPPT conventionnelles ne convergent pas au point de puissance maximale globale dans des conditions PSC. La présence de plusieurs pics sur la caractéristique P(U) rend très difficile le suivi du point de fonctionnement optimal et nécessite l'utilisation d'un algorithme de contrôle qui distingue les points de puissance maximale globale et locale.

* IMPLEMENTATION
<br/>
Lorsque la charge est directement connectée au panneau solaire, le point de fonctionnement du panneau sera rarement à la puissance maximale. L'impédance vue par le panneau détermine le point de fonctionnement du panneau solaire. De cette façon, en changeant l'impédance vue à travers le panneau, le point de fonctionnement peut être décalé vers le point de puissance crête. Étant donné que les panneaux sont des dispositifs CC, utilisez des convertisseurs CC à CC pour convertir l'impédance d'un circuit (source) en un autre circuit (charge). La modification du rapport cyclique du convertisseur DC-DC entraîne une modification de l'impédance vue par le panneau. À une certaine impédance (c'est-à-dire un cycle de service), le point de service sera le transfert de puissance de crête. La courbe du panneau IV peut varier considérablement en fonction des conditions météorologiques telles que l'irradiation et la température. Par conséquent, il n'est pas possible de déterminer le facteur de remplissage dans de telles conditions de travail changeant de manière dynamique.
Les implémentations MPPT utilisent des algorithmes qui échantillonnent fréquemment les tensions et les courants du panneau, puis ajustent le cycle de service selon les besoins. Des microcontrôleurs sont utilisés pour implémenter les algorithmes.

![](Images/PIV.png)
<br/>

### SERVEUR WEB
En plus de mesurer les paramètres, ils devaient être visualisés d'une manière ou d'une autre, c'est pourquoi nous avons créé à cet effet un serveur Web connecté au MPPT, à partir duquel il récupère les données et les présente en temps réel.
* PREMIÈRE APPROCHE DE LA TÂCHE
<br/>
Au début de la création du site web, nous avons décider de travailler sur un site web débarqué que nous pourrions ensuite implanter sur microcontrôleur. Nous utilisions en même temps les langages HTML, CSS, PHP et JavaScript, en passant constamment des variables d'un langage à l'autre, afin de pouvoir à la fois récupérer des données (dans la première phase nous avons en fait généré des données à la main) et le présenter. Cependant, il s'est rapidement avéré que ce n'était pas la meilleure façon d'effectuer notre tâche et que le PHP n'était pas directement implantable sur microcontrôleur. Nous avons donc changé la méthode de fonctionnement. Malgré tout, nous avons aussi réussi à créer un site internet sur lequel nous avons saisi des données et avons pu les présenter.
<br/>

* DEUXIÈME APPROCHE DE LA TÂCHE
<br/>
Une fois que le premier site fonctionnais en débarqué et que nous avons réaliser que celui-ci ne pourrait pas être implanter sur microcontrôleur, nous avons décider de repartir de zéros avec une nouvelle façon de gérer les données et une nouvelle interface. La transition à pu être rapide grâce à la première expérience que nous avons eu avec le site en débarqué. Cette fois-ci la gestion de données s'est faite grâce au javascript et au langage d'arduino. Cette solution est celle que nous avons décider d'implanter sur microcontrôleur car celle-ci permettait de visualiser les données en temps réel avec un rafraichissement automatique. Cette méthode nous à aussi permis de sauver des données pour ensuite les afficher sous différents formats.
<br/>

## Création d'un site en débarqué
Notre première approche à été de créer un site en débarqué pour ensuite l'implanter dans le microcontrôleur. Afin c'effectuer cette tâche, nous nous sommes d'abord renseignés sur les différentes façon de créer des sites web. Nous avons donc découvert les différents langages de programmation des sites web : html, javascript, css et php. Dans un premier temps nous avons essayer de comprendre l'intérêt de tous ces langages. Le langages html est le langages qui permet de gérer la structure de la page web. Le css est un langage permettant de gerer des objets graphiques statique. Le javascript est utiliser pour les animations et plus généralement pour la dynamique du site web. Enfin, le PHP est le langage permettant de gerer les données en dialoguant avec le serveur.
<br/>
<br/>
Pour répondre au cahier des charges, le site web doit pouvoir afficher les valeurs envoyées par le microcontrôleur. Afin de gérer cet échange de données entre le serveur (microcontrôleur) et le site web, la solution qui nous est venue a été d'utiliser du PHP. C'est alors que grâce au logiciel MAMP nous avons créer un serveur avec un interpréteur PHP. Sur ce serveur nous avons donc coder des pages web en .php. Notre solution consistait à afficher des valeurs enregistrer au préalable dans un fichier .txt. Ce fichier .txt était remplis par un formulaire html dans lequel l'utilisateur peut entrer une donnée en x et en y.
<br/>
<br/>
Notre site web devait donc comporter 3 pages pour être fonctionnel, une page d'accueil où les données du mircocontrôleurs sont affichées en temps réel, une page pour la saisie des donnée et enfin, une page pour l'affichage des données dans un tableau et dans un graph. Nous avons ajouter une quatrième page pour présenter l'équipe du projet.
<br/>
<br/>
![](Images/Site_debar.png)
![](Images/Graph_debar.PNG)
<br/>
<br/>
Le site étant maintenant créer il ne nous manquait plus qu'a l'implanter sur microcontrôleur.


## Création d'un site en embarqué
L'implantation sur microcontroôleur s'est avéré plus compliqué que prévu car nous n'avons pas trouvé de moyen de créer un serveur embarqué comportant un interpréteur PHP. Nous nous sommes donc renseigné sur les différentes façon d'implanter des sites web sur microcontrôleur. De plus il fallait trouver une méthode pour gérer un serveur en embarqué. La méthode utilisée dans notre cas a été de gerer le serveur directement sur l'ESP32 en utilisant le langage arduino. Le code consiste donc à faire une recherche de reseau grâce aux informations écrites sur la carte puis effctuer des tentatives de connexions jusqu'au succès. Une fois connecté au reseau, le microcontrôleur envoie le site web sur le serveur. Le site est désormait accessible lorsque qu'un appareil est connecté sur le même reseau que le microcontrôleur à l'adresse 172.20.10.4.
<br/>
<br/>
Afin de répondre au cahier des charges, nous avons créé une page web permettant de visualiser les données du microcontrôleur en temps réel avec un rafraichissement des valeurs toutes les secondes. L'acquisition des valeurs se fait par les PIN analogiques de l'ESP32 connectés sur le convertisseur analogique numérique. Cette valeur est récuperer par le serveur et placer dans diffrérents logs (tension, courant, température, luminosité, puissance). Ces logs sont enregistrés dans un objet json puis enregistrer dans un fichier json. L'objet json est un vecteur ou à chaque ajout d'une nouvelle valeur, la premiere valeur de l'objet json est supprimé, et cette nouvelle valeur est ajoutée en fin de chaîne. Le tableau de donnée est donc dit "circulaire". Le fichier json ainsi créer pour donc servir à afficher les données sous forme de tableau ou de graphique.
<br/>
<br/>
Nous avons donc testé le site en nous connectant sur l'ESP32 à partir d'un ordinateur puis d'un téléphone.
![](Images/ord_emb.png)
![](Images/tel_emb.jpg)

## Conclusion
A travers ce projet nous avons pu dimensionner tous les éléments relatifs au bon fonctionnement du panneau solaire ainsi que sa connexion avec ke MPPT. Nous avons aussi créer un site internet sur un serveur web que nous avons embarqué sur le microcontrôleur. Celui-ci permet de visualiser en temps réel les données reçu sur les PIN de l'ESP32. Cependant, le temps et les ressources nous ont manqués pour réaliser la connexion entre l'ESP32 et le mircôcontroleur avec la carte du groupe précédent. C'est pourquoi nous metterons dans les perspectives d'amélioration toutes les pistes que nous avions envisagé de suivre avec plus de temps. Dans le git vous pourrez trouver les différents codes que nous avons écrit pour les différents sites web, embarqué et débarqué. Le projet du site web débarqué se trouve dans le dossier "Site_Debraque" et le projet du site web embarqué se trouve dans le dossier "ESP32_WebServ_Ard".
<br/>
<br/>

## Perspective d'amélioration

- La carte developpée pour le projet éolienne n'inclut qu'une mesure de tension et de courant, il serait donc interéssant de refaire une nouvelle carte en intégrant un interfaçage capteur pour la mesure de la luminosité. 

- La puissance délivrée par les lampes étaient très faible dû aux pertes et au très mauvais rendement des lampes halogènes, il serait donc interéssant de remplacer les lampes halogènes par d'autres lampes sur le banc de test.

- Ajout de la librairie ARDUINOJSON.h et Google Charts pour permettre le transfert de données à l'interface WEB et la représentation de ces derniers sous forme graphique.

-  Ajout de la librairie WiFiManager.h Pour permettre à l'utilisateur de choisir le réseau auquel il veut se connecter.

-  Ajout de la fonctionnalité de controle des performance du MPPT en ajoutant plus de mémoire sur l'ESP32 pour contenir et afficher plus de valeurs sur un temps très court.
</div>
</body>
</html>