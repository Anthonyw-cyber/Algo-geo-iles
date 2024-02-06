#include "point.h"
#include <cmath>

// Fonction pour déterminer si un point est à gauche, à droite ou sur une droite orientée
int Point::aGauche(const Point &a, const Point &b) const
{
    // Calcule le déterminant de la matrice formée par les points a, b et le point actuel (this)
    double d = (b.x() - a.x()) * (this->d_y - a.d_y) - (this->x() - a.x()) * (b.y() - a.y());

    // Si le déterminant est égal à zéro, le point est sur la droite
    if (d == 0) {
        return 0;
    }
        // Si le déterminant est négatif, le point est à droite de la droite orientée
    else if (d < 0) {
        return -1;
    }
        // Si le déterminant est positif, le point est à gauche de la droite orientée
    else if (d > 0) {
        return 1;
    }
}

// Fonction pour déterminer si un point est à l'intérieur, à l'extérieur ou sur le cercle circonscrit à trois points
int Point::inTheCircle(const Point &a, const Point &b, const Point &c) const
{
    // Calcul des composantes de la matrice
    double A = (a.x() - this->x());
    double B = (a.y() - this->y());
    double C = (pow(a.x() - this->x(), 2) + pow(a.y() - this->y(), 2));
    double D = (b.x() - this->x());
    double E = (b.y() - this->y());
    double F = (pow(b.x() - this->x(), 2) + pow(b.y() - this->y(), 2));
    double G = (c.x() - this->x());
    double H = (c.y() - this->y());
    double I = (pow(c.x() - this->x(), 2) + pow(c.y() - this->y(), 2));

    // Calcul du déterminant de la matrice
    double resultat = (A * E * I) - (A * F * H) + (B * F * G) - (B * D * I) + (C * D * H) - (C * E * G);

    // Si le déterminant est positif, le point est à l'intérieur du cercle
    if (resultat > 0) {
        return 1;
    }
        // Si le déterminant est négatif, le point est à l'extérieur du cercle
    else if (resultat < 0) {
        return -1;
    }
        // Si le déterminant est nul, le point est sur le cercle
    else {
        return 0;
    }
}
