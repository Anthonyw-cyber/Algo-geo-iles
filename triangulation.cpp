//
// Created by etipi on 17/11/2023.
//

#include <vector>
#include <algorithm>
#include "point.h"
#include "carte.h"

using namespace std;

void triangulation(std::vector<Point> &T, Carte &C)
{
    //std::sort(T.begin(), T.end());
    DemiCote* c1 = C.ajouteCote(static_cast<const Point>(T[0]) , static_cast<const Point>(T[0]));
    //C.changeDemiCoteParticulier() = c1;
}