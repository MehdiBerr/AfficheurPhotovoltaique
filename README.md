# AfficheurEolienne


## Membres de l'équipe

Emre KORKMAZ

Leon PEYRAT

Hugo PIETRI

## Introduction

Ce projet a pour but la réalisation d'un dispositif de mesure de la production électrique et de la vitesse de rotation d'une éolienne de particulier, avec afficheur et interface web.

Le projet doit s'adapter aux éoliennes du réseau français Tripalium : https://www.tripalium.org/

Lui-même basé sur le réseau Windempowerment : https://windempowerment.com/

Il y a plusieurs modèles d’éoliennes qui ont des tensions allant de 12 V à 350 V et des puissances pouvant atteindre 2000 W pour la plus grande éolienne (4 m 20 de diamètre). Nous n'adapterons pas notre éolienne pour la version haute tension 350 V ni pour la version 12 V qui délivre directement une tension continue.
Les courants maximums mis en jeux vont de 4 A pour la plus petite éolienne en 48 V à plus de 80 A pour la plus grande en 24 V.

La mesure de vitesse de rotation doit se faire en exploitant le signal triphasé sortant directement de l’éolienne. La mesure de tension et de courant (permettant d’en déduire la fréquence) se fait après le module redresseur de tension, donc en signal continu. 

On doit indiquer les mesures sur des afficheurs dont l’un visuel et didactique (du type rangée de led qui s’allume plus si la puissance produite est plus importante). 

Le système doit être autonome et alimenté directement par l’éolienne (donc nécessité d’une batterie pour l’alimenter en l’absence de vent)


## Contexte du projet



## Cahier des charges

### Cahier des charges avec ses fonctions de contraintes 
 
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




## Circuit et PCB

Le circuit électrique du dispositif est disponible ici : https://easyeda.com/Hupigotri/compteur_eolienne


## Détails pour la réplication du projet

Le circuit et les documents associés sont disponibles en open source et peuvent-être répliqués ou réutilisés sans contraintes.


### Versions de la carte

#### Version 1.0

##### Réglage de la carte

##### Erreurs de conception

#### Version 1.1 ?



## Choix et dimensionnement des composants

### Composants pour les mesures

#### L’amplificateur d’isolement AMC1200 (mesure fréquence, composant 1)

L’amplificateur d’isolement AMC1200 supporte au maximum une tension d’entrée crête à crête de 250 mV. 
On effectue un pont diviseur pour obtenir cette tension lorsque la tension max de l’éolienne est présente en entrée (lorsque les batteries sont quasiment chargées), soit 4×14,5 V=58 V+2 V de marge, donc 60 V redressé. Ces 60 V redressés correspondent à 60 ×√2 crête-à-crête, et 60×√2×√3=147 V pour la tension composée (entre 2 phases) crête-à crête. 
On calcule le rapport des résistances du PDT : (tension éolienne composée càc)/(tension entrée AOP)=147/0,250=588
On choisit R9=180 kΩ  et R20=300 Ω  
En plus de leur rapport, on fait attention à 2 points :
	R20 ≪ résistance entrée AMC1200 =28 kΩ 
	R9+R20 pas trop faible pour limiter la dissipation thermique (P_max=0,1 W pour les CMS R0603)


AMC1200 alimenté en 3,3 V, sa sortie oscille autour de 1,27 V avec une amplitude proportionnelle à la tension en entrée. 



#### AOP TLV225 (mesure fréquence, composant 2)

L’AOP TLV225 est monté en Bascule de Schmitt non inverseuse. 
Les 2 résistances (R21 + R34) et R32 sont un pdt permettant de définir la tension de seuil moyenne. Les 2 autres résistances (R23 + R33) et R22 permettent de fixer les seuils inférieurs et supérieurs de basculement. 
Cette tension est un compromis entre des seuils très différents pour éviter des erreurs dus à des parasites ou au bruit, et des seuils proches permettant de mesurer la fréquence même lorsque l’éolienne tourne très lentement et sa tension de sortie est faible. 

##### Compromis parasites :
Si l’on choisit des résistances (R23 + R33) et R22 avec un rapport 40 (1kΩ  et 40kΩ), on a une différence de seuil haut et bas de 0,08 V en sortie de l’AOP alimenté en 3,3V. Soit un rapport de tensions de  60/3.3≈20 , donc 0,08×20=1,6 V de variations sur la tension d’entrée. Si les parasites sont inférieurs à cette valeur, la mesure de fréquence ne sera pas faussée. 


##### Compromis limite minimale de mesure de fréquence :
On reprend les mêmes résistances (R23 + R33) et R22 avec un rapport 40 (1kΩ et 40kΩ), on se rappelle de la différence entre seuil haut et bas de 0,08 V, on peut donc mesurer une sinusoïde qui a cette valeur crête à crête au minimum. Avec une simple règle de 3, on calcule la tension correspondante en entrée de l’AOP : (0,08×0,250)/3,3=6,06 mV 
On utilise le rapport des résistances du PDT calculé plus haut pour déterminer la tension min nécessaire à la mesure de fréquence : 6,06∙10^(-3)×588=3,56 V
Grâce aux valeurs des vitesses de démarrage de charge du livre page 86, on peut déterminer leur vitesse de rotation pour atteindre cette tension.
Éolienne 24 V et 1m20 : (300×3,56)/24=44,5 tr/min ou 0,74 Hz
Éolienne 48 V et 4m20 : (120×3,56)/48=8,9 tr/min ou 0,15 Hz


#### AOP TLV225 (mesure tension)


On effectue un simple pont diviseur sur la tension redressée pour avoir une image de la tension en entrée de l’AOP. 
Cet AOP est utilisé pour prévenir du risque de détruire l’ESP : si la sortie du pont était directement reliée sur le CAN de l’ESP, une surtension sur l’entrée ferait monter la tension en entrée du CAN au-dessus de 3,3 V. 
Avec l’AOP entre les 2, ce n’est plus un problème : l’AOP peut supporter des tensions d’entrées supérieures, et étant alimenté en 3,3 V, sa sortie peut saturer mais ne dépassera jamais cette valeur ce qui évite d’endommager l’ESP.


On dimensionne à nouveau le pdt pour une tension max de 60 V : 
On choisit un gain du montage non inverseur de 1+R17/R16=1+10/10=2
Dans ce cas si on veut 3,3 V en sortie au maximum, il nous faut 3,3/2=1,65 V maximum en entrée de l’AOP. 
Le PDT doit donc avoir un rapport min de 60/1,65=36,36 
On choisit 100 kΩ et 2,7 kΩ (rapport de 37,03)


#### Capteur à effet Hall CSM015SPT5 (mesure courant)





### Composants pour l'alimentation (Buck 5V)

On veut un buck acceptant une tension d'entrée allant jusqu'à 60 V. Pour cela il y a des contrôleurs pour buck particuliers. C'est le cas du LM296HV que nous avons choisi d'utiliser. 

Ce choix a été fait car c'est le composant présent sur la carte suivante et qu'il fonctionnait parfaitement lors des tests :
https://www.aliexpress.com/item/32842453339.html?

Les condensateurs situés en entrée et sortie doivent aussi supporter les tensions maximales à l'entrée et à la sortie respectivement. 
Le choix plus complexe a été celui de l'inductance du circuit


A DETAILLER




### Composants pour la gestion de charge de la batterie

Pour ce bloc fonctionnel on s'est grandement inspiré de deux exemples de circuits de gestion de batterie très similaires :

Celui de GreatScott : https://www.instructables.com/DIY-LiPo-ChargeProtect5V-Boost-Circuit/

Celui d'électronoob : https://electronoobs.com/eng_circuitos_tut49.php

Le seul composant à modifier en fonction de l'utilisation est la résistance placée entre le pin "PROG" du TP4056 et la masse. En effet cette résistance permet de régler le courant de charge de la batterie. On a choisi une résistance de 2 kΩ ce qui définit un courant de charge de 580 mA. Les batteries li-ion 18650 que l'on utilise peuvent-être endommagées avec un courant plus élevé. Si l'on souhaite doubler l'autonomie, on peut placer 2 batteries en parallèle, et dans ce cas on peut aussi doubler le courant de charge. Il faut cependant veiller à ce que l'alimentation (le buck 5V et l'alimentation USB) puisse délivrer le courant nécessaire.

La partie Boost 5V présente dans ces deux circuits n'a pas été concervée car les composants nécessitant une alimentation 5V que nous utilisons sont directement reliés à la sortie 5V du Buck sur la carte. Le 5V n'est donc présent que lorsque l'éolienne tourne, mais ce n'est pas un problème puisque seul le  capteur de courant fonctionne en 5V, et le courant est nul lorsque l'éolienne est à l'arrêt. 


### Microcontrôleur (ESP32)

Le choix du microcontrôleur s'est porté sur un ESP-WROOM-32U. 
Il est en effet largement utilisé dans l'industrie et facile à programmer. 
Nous l'avons préféré par rapport à un ESP8266 car il est plus rapide, dispose de plus de GPIO, supporte plus d'interruptions et dispose de plus d'entrées analogiques. Il est donc moins restrictif quant à une amélioration future de la carte nécessitant plus de ressources et périphériques.

Dans sa version 32U, il dispose d'un connecteur IPEX permettant de lui attacher une antenne externe. Cela permet d'améliorer la portée WIFI de l'ESP32, notamment en choisissant une antenne à fort gain et en la placant judicieusement.







