#pragma once
#include "Player.h"
#include <vector>

class Yi : public Player {
protected:
//This vector contains all points on the two diagonals of the map. On which a ship must pass.
vector<Coords>Candidatecoords {{3,3},{6,0},{1,5},{0,6},{0,0},{1,1},{2,2},{4,4},{5,5},{6,6},{4,2},{5,1},{2,4}};
//This vector stores the four adjacent coordinates of the cell that reported a successful hit
vector<Coords> Tempocandidates{};
//This vector records all previous shots as cells
vector<Cell> Already{};

public:
  Yi(string n);
  bool brace(Coords);
  Coords shoot();
  void sound(Coords, bool);
  void matchInit();
  void Vectorcontrol(Coords c, bool hit, vector<Coords>&Candidatecoords, vector<Coords>&Tempocandidates, vector<Cell> &Already);
  Coords decide(vector<Coords>&Candidatecoords);
};
