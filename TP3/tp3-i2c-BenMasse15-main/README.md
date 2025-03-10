# TP3 I2C

## Objectif du laboratoire
Réaliser le montage et compléter le code afin d'obtenir un produit complet qui peut compter pendant combien de temps un bouton a été appuyé. 
La dernière durée enregistrée doit être affichée sur l'écran LCD, même dans l'éventualité où il y ait une coupure d'alimentation. 

## Matériel
- 1 Carte PIC
-	1 Afficheur LCD I2C
-	1 mémoire EEPROM 24LC256
-	3 Résistances 10kΩ 
-	1 Résistance 100Ω
-	1 Condensateur environ 100nF (EEPROM)
-	1 Condensateur environ 1uF (circuit anti-rebond bouton)
-	1 bouton poussoir

## Manipulations

1. Ouvrir le projet fourni et s'assurer qu'il compile.
1. Activer le périphérique MSSP en mode I2C et faire les corrections afin qu'il puisse fonctionner. Voir Annexe I pour les détails.
1. Réaliser le montage afin que le LCD I2C puisse fonctionner.
1. Écrire le code pour faire afficher des caractères sur l'écran LCD I2C, ajuster jusqu'à pouvoir afficher correctement.\
   Note: La fiche technique de l’écran LCD indique que l’adresse I2C par défaut est 0x50. Les adresses des écrans I2C du magasin ont été modifiée à la valeur 0x28. 

1. Une fois que le LCD EEPROM fonctionne, réaliser le montage afin que le EEPROM I2C puisse fonctionner.
1. Modifier le code afin de lire et écrire dans la mémoire EEPROM.
1. Assurez-vous d’être en mesure de faire des « write » en EEPROM et de faire des « read » en EEPROM.\
Attention, ne pas faire de « write » à répétition puisque les EEPROM on un nombre maximal d’écriture.
1. Branchez l’analyseur logique, espionnez une trame de communication « read » et une trame de communication « write ».  Prendre une capture d’écran pour chacune des trames.  Ces captures d’écran vont dans le rapport, vous devez analyser la trame READ.
1. Trouvez la condition de départ (point vert), la condition d’arrêt (point rouge) et vérifiez si ACK ou NACK pour chaque transfert. Vérifiez si le premier transfert après la condition de départ est suivi du Setup Write. Vérifier le positionnement des bits de l’adresse et l’état du bit (read/write).
1. Vérifiez si plusieurs transferts de données peuvent se faire suivant le Setup Write. Comment est-ce possible ?  
1. Brancher le circuit suivant sur la broche C2.

![image](https://github.com/max848484/243-421-H24_TP3/assets/156249332/c24cf76f-da03-4523-b653-2f2db94649f9)

12. Utiliser le input capture pour compter combien de temps le bouton reste appuyé.
1. À chaque fois que le bouton est relâché, sauvegarder en EEPROM combien de temps le bouton est resté enfoncé puis affiché la donnée sur le LCD i2c.
1. Après un reset, le mcu doit aller lire en EEPROM quel-est le dernier temps enregistré et l’afficher sur le LCD i2c.


## Évaluation
### Faire vérifier
- Le fonctionnement sera vérifié au laboratoire.

### Remettre dans le répertoire GitHub
- Le programme bien commenté.
- Un fichier Word contenant une page de présentation, les captures d'écran demandées ainsi que l'analyse de la trame read dans le format suivant:

![image](https://github.com/max848484/243-421-H24_TP3/assets/156249332/965d0aab-9590-45d5-997d-b792b64ac57a)

### Pondération
- 20% - LCD I2C
- 60% - EEPROM read et write
- 20% - Bouton

## Annexe I - Comment créer un projet avec une interface MSSP
1. Sous MCC, ajouter l’interface MSSP, choisir le mode I2C et laisser les configurations par défaut.

![image](https://github.com/max848484/243-421-H24_TP3/assets/156249332/a45840f9-edce-4491-bde0-d953e9f025ca)
![image](https://github.com/max848484/243-421-H24_TP3/assets/156249332/221dba77-6375-443f-be7e-1c984b39f129)

2. Générer et ensuite compiler
1. Vous devriez obtenir plusieurs erreurs !!! Il y a un conflit de nom et même avec les versions plus récentes de la librairie le problème n’est toujours pas corrigé. C’est une situation à laquelle vous devrez probablement faire face dans votre carrière professionnelle et maintenant c’est l’occasion de voir qu’on doit parfois faire des « patchs ».
1. On doit faire quelques ajustements à la librairie du I2C.
1. Ouvrir les fichiers i2c_master.c et i2c_master.h
1. Rechercher « I2C_STOP » et modifier ainsi « I2C_STOP_M » partout dans ces fichiers.
1. En principe, si vous devez regénérer dans ce projet parce que vous devez ajouter d’autres interfaces, la librairie I2C ne devrait pas être touchée puisque vous n’y ferez plus de modifications. Toutefois, chaque fois que vous allez créer un nouveau projet il faudra refaire la même procédure.