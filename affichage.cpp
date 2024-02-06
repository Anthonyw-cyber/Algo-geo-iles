#include "affichage.h"
#include "point.h"
#include "carte.h"
#include "graphics.h"

// Fonction pour tracer un segment entre deux points a et b
void segment(const Point &a, const Point &b)
{
    // Définit la couleur du segment (ici, en rouge)
    setcolor(RED);
    // Trace le segment entre les points a et b, en prenant en compte les coordonnées inversées
    line(a.x(), 500 - a.y(), b.x(), 500 - b.y());
}

// Fonction pour tracer un segment entre deux points a et b pour le débogage
void Debugge(const Point &a, const Point &b)
{
    // Définit la couleur du segment (ici, en bleu)
    setcolor(BLUE);
    // Trace le segment entre les points a et b, en prenant en compte les coordonnées inversées
    line(a.x(), 500 - a.y(), b.x(), 500 - b.y());
}

// Fonction pour tracer la carte C dans une fenêtre graphique
void trace(const Carte &C)
{
    // Parcours tous les demi-côtés de la carte
    for (int i = 0; i < C.nbDemiCotes(); ++i) {
        // Vérifie que l'index du demi-côté est inférieur à celui de son opposé
        if (C.demiCote(i)->index() < C.demiCote(i)->oppose()->index()) {
            // Trace le segment entre les coordonnées du demi-côté et celles de son opposé
            segment(C.demiCote(i)->coordonnees(), C.demiCote(i)->oppose()->coordonnees());
        }
    }
}
