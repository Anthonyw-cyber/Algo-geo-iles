#ifndef CARTE_H
#define CARTE_H

#include <vector>
#include "point.h"

using namespace std;

class DemiCote;

class Sommet
{
	friend class Carte;
	friend class DemiCote;

public:
	// Renvoie les coordonn�es du sommet
    Point coordonnees() const {return d_coordonnees;}

    // Renvoie un demi-c�t� issu du sommet
    DemiCote* demiCote() const {return d_demiCote;}

    // Renvoie l'index du sommet
    int index() const {return d_index;}

    // Renvoie la marque du demi-c�t�
    int marque() const {return d_marque;}

    // Met la marque du demi-c�t� � m
    void changeMarque(int m) const {const_cast<int&>(d_marque) = m;}

private:

	// Construit un sommet dont les coordonn�es sont celles de p,
	// � l'extr�mit� du demi-c�t� demiCote et dont l'index est index
    Sommet(const Point &p, DemiCote* demiCote, int index)
           : d_coordonnees(p), d_demiCote{demiCote}, d_index{index}, d_marque{0} {};

	// Destructeur de sommet priv�
	~Sommet() = default;

	Point d_coordonnees;
	DemiCote* d_demiCote;   // l'un des demi-c�t�s issus du sommet
	int d_index;            // la position du sommet dans le tableau d_tabSommets
    int d_marque;	   // la marque du demi-c�t� (0 par d�faut)
};

class DemiCote
{
	friend class Carte;

public:

    // Renvoie l'adresse du demi-c�t� suivant dans le sens trigonom�trique
	DemiCote* suivant() const {return d_suivant;}

    // Renvoie l'adresse du demi-c�t� precedent dans le sens trigonom�trique
	DemiCote* precedent() const {return d_precedent;}

    // Renvoie l'adresse du demi-c�t� oppos�
	DemiCote* oppose() const {return d_oppose;}

	// Renvoie le sommet dont est issu le demi-c�t�
    Sommet* sommet() const {return d_sommet;}

	// Renvoie les coordonn�es du sommet dont est issu le demi-c�t�
    Point coordonnees() const {return d_sommet->d_coordonnees;}

	// Renvoie l'index du demi-c�t�
    int index() const {return d_index;}

    // Renvoie la marque du demi-c�t�
	int marque() const {return d_marque;}

    // Met la marque du demi-c�t� � m
	void changeMarque(int m) const {const_cast<int&>(d_marque) = m;}

private:

	// Construit un demi-c�t� dont suivant est le demi-c�t� suivant,
	// precedent est le demi-c�t� pr�c�dent, oppose est le demi-c�t� oppos�,
	// sommet est le sommet dont il est issu et index est l'index
	DemiCote(DemiCote* suivant, DemiCote* precedent, DemiCote* oppose, Sommet* sommet, int index)
			 : d_suivant{suivant}, d_precedent{precedent}, d_oppose{oppose},
			 d_sommet{sommet}, d_index{index}, d_marque{0} {};

	// Destructeur de demi-c�t� priv�
	~DemiCote() = default;


	DemiCote* d_suivant;
	DemiCote* d_precedent;
	DemiCote* d_oppose;
	Sommet* d_sommet;
	int d_index;       // la position du demi-c�t� dans le tableau d_tabDemiCote
	int d_marque;	   // la marque du demi-c�t� (0 par d�faut)
};

class Carte
{
public:

    // Constructeur par d�faut
    Carte() : d_demiCoteParticulier{nullptr} {}

	// Destructeur
	~Carte();

    // Renvoie le nombre de sommets de la carte
	int nbSommets() const {return d_tabSommets.size();}

    // Renvoie l'adresse du sommet d'index i (0 <= i < nbSommets())
	Sommet* sommet(int i) const	{return d_tabSommets[i];}

    // Renvoie le nombre de demi-c�t�s de la carte
	int nbDemiCotes() const {return d_tabDemiCotes.size();}

    // Renvoie l'adresse du demi-c�t� d'index i (0 <= i < nbDemiCotes())
	DemiCote* demiCote(int i) const	{return d_tabDemiCotes[i];}

	// Renvoie l'adresse du demi-c�t� particulier de la carte
	DemiCote* demiCoteParticulier() const {return d_demiCoteParticulier;}

	// Modifie le demi-c�t� particulier de la carte
	void changeDemiCoteParticulier(DemiCote* particulier)
	{d_demiCoteParticulier = particulier;}

    // Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2
    // dont precedent1 et precedent2 seront les demi-c�t�s pr�c�dents respectifs.
    // On suppose precedent1 et precedent2 d�j� pr�sents dans la carte.
    // Renvoie l'adresse de dc1.
	DemiCote* ajouteCote(DemiCote* precedent1, DemiCote* precedent2);

    // Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2.
    // precedent1 sera le demi-c�t� pr�c�dent de dc1. dc2 sera issu d�un
    // nouveau sommet (� cr�er) dont les coordonn�es sont celles du point p2.
    // On suppose precedent1 d�j� pr�sent dans la carte.
    // Renvoie l'adresse de dc1.
	DemiCote* ajouteCote(DemiCote* precedent1, const Point& p2);

    // Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2.
    // precedent2 sera le demi-c�t� pr�c�dent de dc2. dc1 sera issu d�un
    // nouveau sommet (� cr�er) dont les coordonn�es sont celles du point p1.
    // On suppose precedent2 d�j� pr�sent dans la carte.
    // Renvoie l'adresse de dc1.
	DemiCote* ajouteCote(const Point& p1, DemiCote* precedent2);

    // Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2.
    // dc1 et dc2 seront issus de deux nouveaux sommets (� cr�er) dont les
	// coordonn�es sont celles des points p1 et p2 respectivement.
    // Renvoie l'adresse de dc1.
	DemiCote* ajouteCote(const Point& p1, const Point& p2);

    void addDemiCoteParticulier(DemiCote* premierDC);

    void triangulation(std::vector<Point> &T);

    void delaunay(std::vector<Point> &T);

    void flip(DemiCote *d);

    void flipDemiCote(DemiCote *d);

    void dansCercle(const Point &a, const Point &b, const Point &c) const;

    struct Face{
        int point1, point2, point3;
    };

    vector<Face> AllTriangles();

private:

	// Ajoute un nouveau demi-c�t� dans la carte dont precedent sera le demi-c�t�
	// 	pr�c�dent et oppose sera le demi-c�t� oppos�.
	// On suppose que le demi-c�t� precedent est d�j� pr�sent dans la carte.
	// Le demi-c�t� oppose est soit d�j� pr�sent dans la carte soit nul (valeur
	// par d�faut).
	// Renvoie l�adresse du nouveau demi-c�t�.
	DemiCote* ajouteDemiCote(DemiCote* precedent, DemiCote* oppose=nullptr);

	// Ajoute un nouveau demi-c�t� dans la carte qui sera issu d�un nouveau
	// sommet (� cr�er) dont les coordonn�es sont celles du point p.
	// oppose sera le demi-c�t� oppos� du nouveau demi-c�t�.
	// oppose est soit d�j� pr�sent dans la carte soit nul (valeur par d�faut).
	// Renvoie l�adresse du nouveau demi-c�t�.
	DemiCote* ajouteDemiCote(const Point &p, DemiCote* oppose=nullptr);


    vector<Sommet*> d_tabSommets;       // tableau des sommets
	vector<DemiCote*> d_tabDemiCotes;   // tableau des demi-c�t�s
	DemiCote* d_demiCoteParticulier;    // demi-c�t� particulier (nul par d�faut)
};

#endif
