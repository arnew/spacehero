/* 
 * This file is part of Spacehero.
 * 
 * Spacehero is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Spacehero is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Spacehero.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "Editor.h"

Editor::Editor(Universe &universe) : uni(universe),maxreserve(MAXSTARTRESERVE),all(false),massreserve(maxreserve),size(medium),type(hole)
{
}

#define MPYTH(a,b,c) ((mousex-a)*(mousex-a) + (mousey-b)*(mousey-b) <= (c)*(c))
void Editor::check(double mousex, double mousey)
{
  unsigned int i, remove = 0;

  for(i = 0; i < uni.holes.size(); i++)
  {
    if( MPYTH(uni.holes[i].x, uni.holes[i].y, uni.holes[i].radius) )
    {
      remove = 1;
      
      /* pruefen ob der ueberhaupt geloescht werden darf */
      if(!uni.holes[i].level || all)
      {
        if(!all) massreserve += uni.holes[i].mass;
        uni.holes.erase(uni.holes.begin()+i);
      }
    }
  }

  if(all && !remove)
  {
    for(i = 0; i < uni.galaxies.size(); i++)
    {
      if( MPYTH(uni.galaxies[i].x, uni.galaxies[i].y, uni.galaxies[i].radius) )
      {
        remove = 1;
        uni.galaxies.erase(uni.galaxies.begin()+i);
        uni.calcStars();
      }
    }
  }
  
  if(!remove)
  {
    if(!all)
    {
      if(massreserve >= getHoleWeight())
      {
        massreserve -= getHoleWeight();
        uni.holes.push_back(Blackhole(mousex,mousey,getHoleWeight()));        
      }
    }
    else
    {
      switch(type)
      {
        case hole:
          uni.holes.push_back(Blackhole(mousex,mousey,getHoleWeight()));
          break;
        case bulge:
          srand(time(NULL));
          uni.galaxies.push_back(Galaxy(mousex,mousey,getBulgeWeight(),(rand()%2),(rand()%2)));
          uni.calcStars();
          break;
        case goal:
          uni.goal.setX(mousex);
          uni.goal.setY(mousey);
          uni.goal.setRadius(getGoalRadius());
          break;
        default:
          // nix setzen
          break;
      }
    }
  }
}

double Editor::getQuotient()
{
  return massreserve/maxreserve;
}

double Editor::getHoleWeight()
{
  switch(size)
  {
    case small:
      return HOLESMALLMASS;
      break;
    case medium:
      return HOLEMEDIUMMASS;
      break;
    case large:
      return HOLELARGEMASS;
      break;
    default:
      return 0;
      break;
  }
}

double Editor::getBulgeWeight()
{
  switch(size)
  {
    case small:
      return BULGESMALLMASS;
      break;
    case medium:
      return BULGEMEDIUMMASS;
      break;
    case large:
      return BULGELARGEMASS;
      break;
    default:
      return 0;
      break;
  }
}



double Editor::getGoalRadius()
{
  switch(size)
  {
    case small:
      return SMALLGOAL;
      break;
    case medium:
      return MEDIUMGOAL;
      break;
    case large:
      return LARGEGOAL;
      break;
    default:
      return 0;
      break;
  }
}

void Editor::parseButtons(ButtonFlags &flags)
{
  if(flags.checkFlag(ButtonFlags::small))
  {
    size = small;
  }

  if(flags.checkFlag(ButtonFlags::medium))
  {
    size = medium;
  }

  if(flags.checkFlag(ButtonFlags::large))
  {
    size = large;
  }

  if(flags.checkFlag(ButtonFlags::putHole))
  {
    type = hole;
  }

  if(flags.checkFlag(ButtonFlags::putBulge))
  {
    type = bulge;
  }

  if(flags.checkFlag(ButtonFlags::putGoal))
  {
    type = goal;
  }
}

SpaceDisplay::BridgeView Editor::getView()
{
  return (all)?SpaceDisplay::EditorView:SpaceDisplay::PutView;
}
