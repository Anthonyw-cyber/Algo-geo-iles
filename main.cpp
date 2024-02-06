#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "carte.h"
#include "affichage.h"
#include "point.h"
#include "graphics.h"

#define SCREEN_W 1280
#define SCREEN_H 500

int main() {

    //Permettre de  récupérer les points de l'ile Saint Christof
    const char* pointOfIsland = "C:\\Users\\awilhelm\\Documents\\Projet-master\\ileProject\\ileSaintChristof.txt";

    // Ouvrir le fichier en mode lecture
    std::ifstream fichier(pointOfIsland);
    std::cout << "ouverture du fichier ileSaintChristof.txt" << std::endl;

    // regarder si l'ouverture a réussi
    if (!fichier) {
        std::cerr << "Erreur lors de l'ouverture du fichier ileSaintChristof.txt." << std::endl;
        return 1;
    }

    // Lire le nombre de points
    int nombreDePoints;
    fichier >> nombreDePoints;
    std::cout << "nombre de points : " << nombreDePoints << std::endl;

    // Vector pour stocker les points
    std::vector<Point> pointsIslands;

    // Lire les coordonnées depuis le fichier
    std:: cout << "lecture des coordonnees" << std::endl;
    int x, y, z;
    for (int i = 0; i < nombreDePoints; ++i) {
        fichier >> x >> y >> z;

        // Créer un point avec les coordonnées lus
        Point point{x, y, z};

        // Ajouter le point au vector
        pointsIslands.push_back(point);
    }

    // Fermer le fichier
    std::cout << "fermeture du fichier ileSaintChristof.txt" << std::endl;
    fichier.close();

    // ouvrir le graphe
    std::cout << "ouverture du graphe" << std::endl;
    opengraphsize(1280, 500);


    // Triangulation et triangulation de delaunay
    std::vector<Point> points = {};

    // création des point
    std::cout << "creation des points" << std::endl;
    for (int i = 0; i < 1000; i++) {
        points.emplace_back(rand() % SCREEN_W, rand() % SCREEN_H, 0);
        std::cout << "point " << i << " : " << points[i].x() << " " << points[i].y() << std::endl;
    }
    //std::sort(points.begin(), points.end());
    //points.erase(std::unique(points.begin(), points.end()), points.end());

    Carte newCards {};

    //newCards.triangulation(points);  // Points de test
    newCards.triangulation(pointsIslands);  // Points de l ile
    trace(newCards);

    getch();

    cleardevice();

    newCards.delaunay(points);
    //newCards.AllTriangles();

    // Nom du fichier .obj
    std::cout<<"recherche du fichier maCarte.obj"<< std::endl;
    const char* nomFichierObj = "C:\\Users\\awilhelm\\Documents\\Projet-master\\IleProject\\maCarte.obj";

    // Ouvrir le fichier en mode écriture
    std::ofstream fichierObj(nomFichierObj);
    std::cout << "ouverture du fichier maCarte.obj"<< std::endl;

    // Vérifier si l'ouverture a réussi
    if (!fichierObj) {
        std::cerr << "Erreur lors de l'ouverture du fichier " << nomFichierObj << " en écriture." << std::endl;
        return 1;
    }
    fichierObj << "mtllib maTexture.mtl"<< std::endl;
    std:: cout << "ecriture du fichier"<< std::endl;
    // Écrire les points dans le fichier .obj

    for (int i = 0; i < newCards.nbSommets(); ++i) {
        fichierObj << "v " << newCards.sommet(i)->coordonnees().x() << " " << newCards.sommet(i)->coordonnees().y() << " " << newCards.sommet(i)->coordonnees().z() << std::endl;
    }
//ajout de la texture
    for (const auto& point : newCards.AllTriangles()) {
        if (newCards.sommet(point.point1)->coordonnees().z() == 0 && newCards.sommet(point.point2)->coordonnees().z() == 0 && newCards.sommet(point.point3)->coordonnees().z() == 0){
            fichierObj << "usemtl Eau"<< std::endl;
        }
        if (newCards.sommet(point.point3)->coordonnees().z() < 70 && (newCards.sommet(point.point3)->coordonnees().z() >= 1 || newCards.sommet(point.point1)->coordonnees().z() >= 1 || newCards.sommet(point.point2)->coordonnees().z() >= 1)){
            fichierObj << "usemtl Sable"<< std::endl;
        }
        if (newCards.sommet(point.point3)->coordonnees().z() < 500 && newCards.sommet(point.point3)->coordonnees().z() >= 70){
            fichierObj << "usemtl Gazon"<< std::endl;
        }
        if (newCards.sommet(point.point3)->coordonnees().z() >= 500){
            fichierObj << "usemtl Neige"<< std::endl;
        }

        fichierObj << "f " << point.point1+1 << " " << point.point2+1 << " " << point.point3+1 << std::endl;
    }

    for (const auto& point : newCards.AllTriangles()) {
        fichierObj << "usemtl myTexture"<< std::endl;
        fichierObj << "f " << point.point1+1 << " " << point.point2+1 << " " << point.point3+1 << std::endl;
    }

    // Fermer le fichier
    fichierObj.close();
    std::cout << "fin de l'ecriture du fichier"<< std::endl;

    trace(newCards);

    getch();

    closegraph();
    return 0;
}
