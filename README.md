# miniRT

miniRT est un projet de RayTracer réalisé en C avec la MiniLibX. Il calcule des intersections vectorielles pour afficher des objets simples (sphère, plan, cylindre) et charge la scène depuis un fichier de configuration `.rt`.

## Compilation

```bash
make
```

Le binaire produit est `miniRT`.

## Exécution

```bash
./miniRT
```

Le programme lit par défaut le fichier `scenes/sphere.rt`.

## Format du fichier de scène

Chaque ligne du fichier `.rt` décrit un élément de la scène :

- `C x,y,z  x,y,z  fov`
  - Caméra : position, direction, champ de vision en degrés.
- `A ratio  r,g,b`
  - Lumière ambiante : intensité `[0.0, 1.0]`, couleur RGB.
- `L x,y,z  ratio  r,g,b`
  - Source lumineuse : position, intensité `[0.0, 1.0]`, couleur RGB.
- `sp x,y,z  diameter  r,g,b`
  - Sphère : centre, diamètre, couleur RGB.
- `pl x,y,z  x,y,z  r,g,b`
  - Plan : point, vecteur normalisé, couleur RGB.
- `cy x,y,z  x,y,z  diameter  height`
  - Cylindre : centre, axe, diamètre, hauteur.

### Exemple

```text
C 0,0,0  0,0,-1  90
A 0.2  255,255,255
sp 0,0,-5  2.0  255,0,0
```

## Structure du projet

- `srcs/` : sources C.
- `includes/` : fichiers d'en-tête.
- `mlx/` : MiniLibX.
- `scenes/` : fichiers de scène.


