#include "carte.h"
#include "point.h"
#include "affichage.h"
#include "graphics.h"
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Destructeur de la classe Carte
Carte::~Carte()
{
}

// Ajoute dans la carte un nouveau côté composé de deux demi-côtés dc1 et dc2
// dont precedent1 et precedent2 seront les demi-côtés précédents respectifs.
// On suppose precedent1 et precedent2 déjà présents dans la carte.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(DemiCote* precedent1, DemiCote* precedent2)
{
    DemiCote* dc1 = ajouteDemiCote(precedent1, nullptr);
    ajouteDemiCote(precedent2, dc1);
    return dc1;
}

// Ajoute dans la carte un nouveau côté composé de deux demi-côtés dc1 et dc2.
// precedent1 sera le demi-côté précédent de dc1. dc2 sera issu d'un
// nouveau sommet (à créer) dont les coordonnées sont celles du point p2.
// On suppose precedent1 déjà présent dans la carte.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(DemiCote* precedent1, const Point& p2)
{
    DemiCote* dc1 = ajouteDemiCote(precedent1, nullptr);
    ajouteDemiCote(p2, dc1);
    return dc1;
}

// Ajoute dans la carte un nouveau côté composé de deux demi-côtés dc1 et dc2.
// precedent2 sera le demi-côté précédent de dc2. dc1 sera issu d'un
// nouveau sommet (à créer) dont les coordonnées sont celles du point p1.
// On suppose precedent2 déjà présent dans la carte.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(const Point& p1, DemiCote* precedent2)
{
    DemiCote* dc1 = ajouteDemiCote(p1, nullptr);
    ajouteDemiCote(precedent2, dc1);
    return dc1;
}

// Ajoute dans la carte un nouveau côté composé de deux demi-côtés dc1 et dc2.
// dc1 et dc2 seront issus de deux nouveaux sommets (à créer) dont les
// coordonnées sont celles des points p1 et p2 respectivement.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(const Point& p1, const Point& p2)
{
    DemiCote* dc1 = ajouteDemiCote(p1, nullptr);
    ajouteDemiCote(p2, dc1);
    return dc1;
}

// Ajoute un nouveau demi-côté dans la carte dont precedent sera le demi-côté
// précédent et oppose sera le demi-côté opposé.
// On suppose que le demi-côté precedent est déjà présent dans la carte.
// Le demi-côté oppose est soit déjà présent dans la carte soit nul (valeur
// par défaut).
// Renvoie l'adresse du nouveau demi-côté.
DemiCote* Carte::ajouteDemiCote(DemiCote* precedent, DemiCote* oppose)
{
    // Crée un nouveau demi-côté
    DemiCote* NouveauDemiCote = new DemiCote{precedent->suivant(), precedent, oppose, precedent->sommet(), static_cast<int>(d_tabDemiCotes.size())};
    // Ajoute le nouveau demi-côté à la liste des demi-côtés de la carte
    d_tabDemiCotes.push_back(NouveauDemiCote);
    // Met à jour les liens avec les demi-côtés adjacents
    precedent->d_suivant = NouveauDemiCote;
    NouveauDemiCote->d_suivant->d_precedent = NouveauDemiCote;
    if (oppose != nullptr){
        oppose->d_oppose = NouveauDemiCote;
    }
    return NouveauDemiCote;
}

// Ajoute un nouveau demi-côté dans la carte qui sera issu d'un nouveau
// sommet (à créer) dont les coordonnées sont celles du point p.
// oppose sera le demi-côté opposé du nouveau demi-côté.
// oppose est soit déjà présent dans la carte soit nul (valeur par défaut).
// Renvoie l'adresse du nouveau demi-côté.
DemiCote* Carte::ajouteDemiCote(const Point &p, DemiCote* oppose)
{
    // Crée un nouveau sommet avec les coordonnées du point p
    Sommet* NouveauSommet = new Sommet{p, nullptr, static_cast<int>(d_tabSommets.size())};
    // Crée un nouveau demi-côté
    DemiCote* NouveauDemiCote = new DemiCote{nullptr, nullptr, oppose, NouveauSommet, static_cast<int>(d_tabDemiCotes.size())};
    // Met à jour le lien entre le sommet et le demi-côté
    NouveauSommet->d_demiCote = NouveauDemiCote;
    // Initialise les liens du demi-côté avec lui-même (nouveau sommet)
    NouveauDemiCote->d_suivant = NouveauDemiCote;
    NouveauDemiCote->d_precedent = NouveauDemiCote;
    // Si un demi-côté opposé est spécifié, met à jour son lien
    if (oppose != nullptr){
        oppose->d_oppose = NouveauDemiCote;
    }
    // Ajoute le nouveau demi-côté à la liste des demi-côtés de la carte
    d_tabDemiCotes.push_back(NouveauDemiCote);
    // Ajoute le nouveau sommet à la liste des sommets de la carte
    d_tabSommets.push_back(NouveauSommet);
    return NouveauDemiCote;
}

// Fonction pour ajouter un demi-côté particulier à la carte
void Carte::addDemiCoteParticulier(DemiCote* premierDC)
{
    double bestAngle = 1000;
    DemiCote* bestDC;

    double hypo;
    double coteAdj;
    double coteOppo;
    DemiCote* dcCheck = premierDC->oppose();
    do {
        dcCheck = dcCheck->oppose()->suivant()->oppose();
        coteAdj = dcCheck->sommet()->coordonnees().y() - premierDC->sommet()->coordonnees().y();
        if (coteAdj < 0)
        {
            coteAdj = coteAdj * (-1);
        }
        coteOppo = dcCheck->sommet()->coordonnees().x() - premierDC->sommet()->coordonnees().x();
        hypo = sqrt(coteAdj*coteAdj + coteOppo*coteOppo);

        double angleEnDegre = acos(coteAdj / hypo) * (180.0 / M_PI);

        if (angleEnDegre < bestAngle)
        {
            bestAngle = angleEnDegre;
            bestDC = dcCheck;
        }
    } while (dcCheck != premierDC->oppose());

    // Vérifie le sens du meilleur demi-côté
    if (bestDC->sommet()->coordonnees().y() < bestDC->oppose()->sommet()->coordonnees().y())
    {
        this->d_demiCoteParticulier = bestDC->oppose();
    }
    else
    {
        this->d_demiCoteParticulier = bestDC;
    }
}

// Fonction pour réaliser la triangulation de Delaunay
void Carte::triangulation(std::vector<Point> &T)
{
    // Trie les points T en ordre croissant
    std::sort(T.begin(), T.end());

    // Ajoute le premier côté avec les deux premiers points
    DemiCote* dc = this->ajouteCote(T[0], T[1]);

    // Garde une référence au premier côté ajouté
    DemiCote* premierCote = dc;

    // Ajoute les côtés restants avec les points suivants
    for (int i = 2; i < T.size(); ++i) {
        dc = ajouteCote(T[i], dc);

        // Garde une référence au côté ajouté
        DemiCote* stock = dc;

        // Vérifie si le point i est à gauche du côté opposé
        while (T[i].aGauche(dc->oppose()->coordonnees(), dc->oppose()->suivant()->oppose()->coordonnees()) < 0)
        {
            dc = ajouteCote(dc->precedent(), dc->oppose()->suivant()->oppose());
        }

        // Rétablit la référence au côté ajouté
        dc = stock;

        // Vérifie si le point i est à gauche du côté précédent opposé
        while (T[i].aGauche(dc->oppose()->coordonnees(), dc->oppose()->precedent()->oppose()->coordonnees()) > 0)
        {
            dc = ajouteCote(dc, dc->oppose()->precedent()->oppose()->precedent());
        }
    }

    // Ajoute le demi-côté particulier
    this->addDemiCoteParticulier(premierCote);
}

// Fonction pour réaliser la triangulation de Delaunay
void Carte::delaunay(std::vector<Point> &T)
{
    // Variable pour marquer les côtés extérieurs
    DemiCote* dcLoop = this->demiCoteParticulier();

    // Initialisation de la pile
    vector<DemiCote*> pile;

    do {
        dcLoop->changeMarque(1);
        dcLoop->oppose()->changeMarque(1);
        //Debugge(dcLoop->coordonnees(), dcLoop->oppose()->coordonnees());
        //getch();
        dcLoop = dcLoop->oppose()->suivant();
    } while (dcLoop != this->demiCoteParticulier());

    // Marque les côtés et les ajoute à la pile
    for (int i = 0; i < this->nbDemiCotes(); ++i) {
        DemiCote* marque = this->demiCote(i);
        if (marque->marque() != 1)
        {
            marque->changeMarque(1);
            marque->oppose()->changeMarque(1);
            pile.push_back(this->demiCote(i));
        }
    }

    while (!pile.empty())
    {
        DemiCote* traitee = pile[pile.size() - 1];
        pile.pop_back();
        traitee->changeMarque(0);
        traitee->oppose()->changeMarque(0);
        Sommet* pointOpposeeTriangle = traitee->precedent()->oppose()->sommet();
        float firstPointisInsideTheCircle;
        firstPointisInsideTheCircle = pointOpposeeTriangle->coordonnees().inTheCircle(traitee->coordonnees(),
                                                                                      traitee->suivant()->oppose()->coordonnees(),
                                                                                      traitee->oppose()->coordonnees());

        if (firstPointisInsideTheCircle < 0)
        {
            if (traitee->suivant()->marque() == 0){
                traitee->suivant()->changeMarque(1);
                traitee->suivant()->oppose()->changeMarque(1);
                pile.push_back(traitee->suivant());
            }

            if (traitee->precedent()->marque() == 0){
                traitee->precedent()->changeMarque(1);
                traitee->precedent()->oppose()->changeMarque(1);
                pile.push_back(traitee->precedent());
            }

            if (traitee->oppose()->precedent()->marque() == 0){
                traitee->oppose()->precedent()->changeMarque(1);
                traitee->oppose()->precedent()->oppose()->changeMarque(1);
                pile.push_back(traitee->oppose()->precedent());
            }

            if (traitee->oppose()->suivant()->marque() == 0){
                traitee->oppose()->suivant()->changeMarque(1);
                traitee->oppose()->suivant()->oppose()->changeMarque(1);
                pile.push_back(traitee->oppose()->suivant());
            }

            flip(traitee);
        }
    }
}

// Fonction pour effectuer un flip de demi-côté
void Carte::flip(DemiCote* d) {
    flipDemiCote(d);
    flipDemiCote(d->oppose());
}

// Fonction pour effectuer un flip de demi-côté spécifique
void Carte::flipDemiCote(DemiCote* d) {
    // Définit un marqueur de la position du demi-côté de départ
    auto demiCoteDepart = d->suivant()->oppose();
    // Change le demi-côté représentant le sommet
    if (d->d_sommet->demiCote() == d) {
        d->d_sommet->d_demiCote = d->suivant();
    }
    // Met à jour les anciens voisins de d
    d->suivant()->d_precedent = d->precedent();
    d->precedent()->d_suivant = d->suivant();
    // Déplace d
    d->d_precedent = demiCoteDepart;
    d->d_suivant = demiCoteDepart->suivant();
    // Met à jour les nouveaux voisins de d
    d->precedent()->d_suivant = d;
    d->suivant()->d_precedent = d;
    // Met à jour le sommet de d
    d->d_sommet = demiCoteDepart->sommet();
}

// Fonction pour obtenir tous les triangles de la carte
vector<Carte::Face> Carte::AllTriangles()
{
    vector<Face> faces;
    for (int i = 0; i < this->nbSommets(); ++i) {
        DemiCote* dc = this->sommet(i)->demiCote();
        do {
            dc = dc->suivant();
            if (dc->suivant()->oppose()->sommet() == dc->oppose()->precedent()->oppose()->sommet() && dc->oppose()->sommet()->marque() == 0 && dc->suivant()->oppose()->sommet()->marque() == 0)
            {
                faces.push_back({dc->sommet()->index(), dc->oppose()->sommet()->index(), dc->suivant()->oppose()->sommet()->index()});
            }
        } while (dc != this->sommet(i)->demiCote());

        this->sommet(i)->changeMarque(1);
    }

    return faces;
}
