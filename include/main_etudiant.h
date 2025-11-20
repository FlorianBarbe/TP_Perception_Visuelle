#pragma once

#ifdef __APPLE__
   #include <OPENGL/gl.h>
   #include <GLUT/glut.h>
#else
   #include <windows.h>
   #include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <iostream>

// Gestion des affichages en "rouge" (gauche) et "cyan" (droite) et du blending des 2 images
GLvoid affichage_etudiant();

// Affichage des formes avec gestion de la parallaxe
GLvoid affichageForme_etudiant(float parallaxeH, float parallaxeV);

// Gestion des touches du clavier
GLvoid clavier_etudiant(unsigned char touche, int x, int y);

// Gestion des fleches du clavier pour la parallaxe
GLvoid clavierToucheSpeciale(int touche, int x, int y);


int main(int argc, char** argv);
