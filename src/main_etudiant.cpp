#include "main_etudiant.h"

using namespace std;

int gaucheDroite = 2;
/* si 0: affichage de l'image gauche,
si 1: affichage de l'image droite
si 2: affichage en stereo anaglyphe*/

// Décalages parallaxes Horizontales et Verticales
float parallaxeH = 0;
float parallaxeV = 0;
// "pas" de modification de la parallaxe
float pas = 0.01;

// JMN
int rot = 0;
boolean lightOn = false;
float lightPos[3] = { 0,0,0 };

// Choix de la forme a dessiner
// 0 pour sphere,
// 1 pour ligne verticale,
// 2 pour ligne horizontale,
// 3 pour un cube, (taille 0.5) cf. glutXXXCube a chercher sur Internet
// 4 pour teapot (taille 0.5) cf. glutXXXTeapot a chercher sur Internet
int choix = 0;

// Gestion de l'affichage de la forme 2D ou 3D
GLvoid affichageForme_etudiant(float parallaxeH, float parallaxeV)
{
    // On reste la matrice MODELVIEW
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Translation de la moitie de la parallaxe H et V sur X et Y
    // (on divise par 2 car on veut "la moitié" de la parallaxe ici)
    glTranslatef(parallaxeH * 0.5f, parallaxeV * 0.5f, 0.0f);

    // Nous allons dessiner en blanc et gerer le rouge/cyan avec les glColorMask
    glColor3f(1.0f, 1.0f, 1.0f);

    // Affichage des formes en fonction du choix de l'utilisateur
    switch (choix)
    {
        // Sphere "pleine" de taille 0.5 avec 30 slices et 30 stacks
    case 0:
        glutSolidSphere(0.5, 30, 30);
        break;

        // Ligne verticale entre [0, -0.5, 0] et [0, 0.5, 0]
    case 1:
        glBegin(GL_LINES);
        glVertex3f(0.0f, -0.5f, 0.0f);
        glVertex3f(0.0f, 0.5f, 0.0f);
        glEnd();
        break;

        // Ligne horizontale entre [-0.5, 0, 0] et [0.5, 0, 0]
    case 2:
        glBegin(GL_LINES);
        glVertex3f(-0.5f, 0.0f, 0.0f);
        glVertex3f(0.5f, 0.0f, 0.0f);
        glEnd();
        break;

        // Cube de taille 0.5
    case 3:
        // Bonus : rotation autour de Y controlee par les touches 'b' et 'n'
        glRotatef((float)rot, 0.0f, 1.0f, 0.0f);
        glutSolidCube(0.5f);
        break;

        // Théière "pleine" de taille 0.5
    case 4:
        // Bonus : rotation autour de Y controlee par les touches 'b' et 'n'
        glRotatef((float)rot, 0.0f, 1.0f, 0.0f);
        glutSolidTeapot(0.5f);
        break;
    }

    // On force le re-affichage
    glutPostRedisplay();
}

// Fonction qui gere l'affichage rouge/cyan pour les images gauche/droite
GLvoid affichage_etudiant()
{
    // On s'assure d'avoir le droit d'ecrire
    // dans les 4 canaux colorimetriques : R G B A
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

    // On efface le color buffer et le depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // On affiche l'image gauche : soit quand c'est "que" la gauche
    // soit quand on affiche gauche et droite
    if (gaucheDroite == 0 || gaucheDroite == 2)
    {
        // Nos lunettes ont le filtre rouge a sur l'oeil gauche
        // On ne doit pouvoir ecrire que dans le canal rouge
        // On filtre donc les canaux vert et bleu
        glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);

        // On affiche la forme choisie avec la parallaxe
        affichageForme_etudiant(parallaxeH, parallaxeV);
    }

    // Oeil droit ou les 2 yeux
    if (gaucheDroite == 1 || gaucheDroite == 2)
    {
        // We need to blend the images
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);

        // Oeil droit avec filtre cyan
        // On ecrit que dans les canaux vert et bleu
        glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);

        //  On affiche la forme choisie avec la parallaxe
        affichageForme_etudiant(-parallaxeH, -parallaxeV);
    }

    // On force le re-affichage
    glFlush();
}

// Gestion des interactions clavier
GLvoid clavier_etudiant(unsigned char touche, int x, int y)
{
    switch (touche)
    {
    case 'g':
        gaucheDroite = 1;  // ÉTAIT 0 → maintenant affiche image GAUCHE au bon endroit
        parallaxeH = 1;
        parallaxeV = 0;
        break;

    case 'd':
        gaucheDroite = 0;  // ÉTAIT 1 → affiche image DROITE au bon endroit
        parallaxeH = 1;
        parallaxeV = 0;
        break;

    case 's':
        gaucheDroite = 2;
        break;
    case '0':
        choix = 0;
        break;
    case '1':
        choix = 1;
        break;
    case '2':
        choix = 2;
        break;
    case '3':
        choix = 3;
        break;
    case '4':
        choix = 4;
        break;

    case 'p': //plein
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    case 'm': //fil de fer
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;

        // Rotation du modele 3D
    case 'b':
        rot++;
        break;
    case 'n':
        rot--;
        break;

        // Reset all
    case 'r':
        parallaxeH = 0;
        parallaxeV = 0;
        lightPos[0] = 0.;
        lightPos[1] = 0.;
        lightPos[2] = 0.;
        rot = 0;
        std::cout << "Light Position: " << lightPos[0] << " " << lightPos[1] << " " << lightPos[2] << endl;
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        break;

        // Turn on/off lighting:
    case 'a':
        if (lightOn) {
            glDisable(GL_LIGHTING);
        }
        else {
            glEnable(GL_LIGHTING);
        }
        lightOn = !lightOn;
        break;

    case 27:
    case 'q':
        exit(0);
        break;
    }
    glutPostRedisplay();
}

GLvoid clavierToucheSpeciale(int touche, int x, int y)
{
    // Gestion de la parallaxe avec les fleches du clavier
    switch (touche)
    {
        // On veut augmenter la parallaxe verticale du "pas"
    case GLUT_KEY_UP:
        parallaxeV += pas;
        break;

        // On veut diminuer la parallaxe verticale du "pas"
    case GLUT_KEY_DOWN:
        parallaxeV -= pas;
        break;

        // On veut diminuer la parallaxe horizontale du "pas"
    case GLUT_KEY_LEFT:
        parallaxeH -= pas;
        break;

        // On veut augmenter la parallaxe horizontale du "pas"
    case GLUT_KEY_RIGHT:
        parallaxeH += pas;
        break;
    }

    // On force le re-affichage
    glutPostRedisplay();
}


// La fonction principale de GLUT
int main(int argc, char** argv)
{
    // Initialisation de GLUT
    glutInit(&argc, argv);

    // Fenetre RGBA + Tampon de profondeur
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowPosition(200, 200);
    glutInitWindowSize(700, 700);
    glutCreateWindow("TP lunettes");

    // Couleur d'effacement : noir
    glClearColor(0, 0, 0, 0);

    //fonctions de callbacks
    //fonctions de callbacks
    glutDisplayFunc(affichage_etudiant);
    glutKeyboardFunc(clavier_etudiant);
    glutSpecialFunc(clavierToucheSpeciale);

    // Eclairage (pas strictement necessaire mais on voit mieux les formes 3D)
    if (lightOn) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }
    else {
        glDisable(GL_LIGHTING);
    }

    // Position de la source lumineuse (si "on")
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // Lissage de Gouraud
    glShadeModel(GL_SMOOTH);

    // TODO : si vous voulez demander le pas a l'utilisateur
    // faites le ici

    // Let's roll
    glutMainLoop();

    return 0;
}
