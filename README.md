# Problème du voyageur de commerce

## Résolution par l'algorithme de Little

## Auteur: LAPLANCHE Alexis 21800347

## Format du fichier de config:
Pour renseigner le problème a notre programme il faut saisir la matrice des coûts en informant les dimensions de notre matrice comme dans l'exemple suivant:
```
Dimension: 6x6
Matrice:
-1 780 320 580 480 660
780 -1 700 460 300 200
320 700 -1 380 820 630
580 460 380 -1 750 310
480 300 820 750 -1 500
660 200 630 310 500 -1
```

## Compilation:
Un Makefile est fourni avec cette archive, il suffit juste de taper la commande suivante pour compiler:
```bash
	make
```

## Exécution
Le code peut être éxécuter grâce au Makefile avec la commande suivante, le fichier config "config.txt" sera chargé de base:
```bash
	make run
```
Une fois le code compiler, il peut être éxécuter avec la commande suivante:
```bash
	./main <fichier_config.txt>
```