/*
  Copyright (c) 2015-2016 Lester Hedges <lester.hedges+vmmc@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <cmath>

#include "Box.h"
#include "Particle.h"
#include "CellList.h"
#include "CosSquared.h"

CosSquared::CosSquared(
    Box& box_,
    std::vector<Particle>& particles_,
    CellList& cells_,
    unsigned int maxInteractions_,
    double interactionEnergy_,
    double interactionRange_) :
    Model(box_, particles_, cells_, maxInteractions_, interactionEnergy_, interactionRange_)
{
}

#ifndef ISOTROPIC
double CosSquared::computePairEnergy(const unsigned int particle1, const double* position1, const unsigned int type1,
    const double* orientation1, const unsigned int particle2, const double* position2,const unsigned int type2, const double* orientation2)
#else
double CosSquared::computePairEnergy(const unsigned int particle1,
    const double* position1, const unsigned int type1, const unsigned int particle2, const double* position2, const unsigned int type2)
#endif
        
{
    // Separation vector.
    std::vector<double> sep(box.dimension);

    // Calculate separation.
    for (unsigned int i=0;i<box.dimension;i++)
        sep[i] = position1[i] - position2[i];

    // Enforce minimum image.
    box.minimumImage(sep);

    double normSqd = 0;

    // Calculate squared norm of vector.
    for (unsigned int i=0;i<box.dimension;i++)
        normSqd += sep[i]*sep[i];

    // Particles interact.
    
    if (normSqd < 1)
    
    {
        double r2Inv = 1.0 / normSqd;
        double r6Inv = r2Inv*r2Inv*r2Inv;
        return interactionEnergy*((r6Inv*r6Inv) - 2*r6Inv + 1);
    }
    
    if (normSqd < squaredCutOffDistance && (type1 == type2) && type1 == 0){
        double r = sqrt(normSqd);
        //eps_fp*cos(M_PI*(r-sigma_fp)/(2*(interactionRange_-sigma_fp)))*cos(M_PI*(r-sigma_fp)/(2*(rcut_fp-sigma_fp)));
        double cosineterm = cos(M_PI*(r-1)/(2*(interactionRange-1))); //for now just assigned sigma = 1 rather than calling sigma
        return -interactionEnergy*cosineterm*cosineterm;
    }
    
    if (normSqd < squaredCutOffDistance && (type1 == type2) && type1 == 1){
        double r = sqrt(normSqd);
        //eps_fp*cos(M_PI*(r-sigma_fp)/(2*(interactionRange_-sigma_fp)))*cos(M_PI*(r-sigma_fp)/(2*(rcut_fp-sigma_fp)));
        double cosineterm = cos(M_PI*(r-1)/(2*(interactionRange-1))); //for now just assigned sigma = 1 rather than calling sigma
        return -5*interactionEnergy*cosineterm*cosineterm;
    }
    
    if (normSqd < squaredCutOffDistance*2 && (type1 != type2)){
        double r = sqrt(normSqd);
        //eps_fp*cos(M_PI*(r-sigma_fp)/(2*(interactionRange_-sigma_fp)))*cos(M_PI*(r-sigma_fp)/(2*(rcut_fp-sigma_fp)));
        double cosineterm = cos(M_PI*(r-1)/(2*(interactionRange-1))); //for now just assigned sigma = 1 rather than calling sigma
        return -interactionEnergy*cosineterm*cosineterm;
    }
    
    
    
    else return 0;
}
