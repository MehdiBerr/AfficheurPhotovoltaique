# AfficheurEolienne


## Membres de l'équipe

Emre KORKMAZ

Leon PEYRAT

Hugo Pietri

## Introduction

Ce projet a pour but la réalisation d'un dispositif de mesure de la production électrique et de la vitesse de rotation d'une éolienne de particulier, avec afficheur et interface web.

Il y a plusieurs modèles d’éoliennes qui ont des courants allant jusqu’à 20 A et des tensions jusqu’à 40 V *(pas exact à modifier)*

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
