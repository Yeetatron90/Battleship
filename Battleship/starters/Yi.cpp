#include "Yi.h"
#include <algorithm>
#include <ctime>
#include <vector>

Yi::Yi(string n) : Player(n) {}

bool Yi::brace(Coords c) {
  myOcean[c.i][c.j].torpedo = true;
  return myOcean[c.i][c.j].ship; // leave this line in
}

// shoot() is a request to this Player to fire a
// torpedo at the opponent's ocean.  The return value
// is the place you want to shoot at your opponent.
// It is up to this you to record where you made this shot
// if you want to remember it.

Coords Yi::shoot() {
  // Make b equal to the result of another value function
  // The reason I need another function is because I need to control the vectors
  // within Yi.h. Which neccessitates passing the vector by reference to the
  // function as parameters.
  Coords b = decide(Candidatecoords);
  return b;
}

// The coordinate of next shot is always the first element of the candidate
// vector
Coords Yi::decide(vector<Coords> &Candidatecoords) {
  Coords c = Candidatecoords[0];
  return c;
}

void Yi::sound(Coords c, bool hit) {

  if (yourOcean[c.i][c.j].ship == true) {
    hit = true; // mark the hit as a success
    yourOcean[c.i][c.j].torpedo = true;
  }
  // mark the cell as hit
  // check if the ship was sunk
  else if (yourOcean[c.i][c.j].ship == false) {
    hit = false; // mark the hit as a miss
    yourOcean[c.i][c.j].torpedo = true;
  }

  // Again, in need of another function since I need to pass the vectors in Yi.h
  // by reference in order to manipulate them
  Vectorcontrol(c, hit, Candidatecoords, Tempocandidates, Already);
}

// The first coordinate gets deleted if the hit misses, pushing the second
// coordinate to become the first, until a hit becomes successful.
// Candidatecoords contains all essential coordinates. A ship must occur in one
// of those coordinates

// If a hit becomes successful, Candidatecoords is cleared to leave room for
// filling algorithm

void Yi::Vectorcontrol(Coords c, bool hit, vector<Coords> &Candidatecoords,
                       vector<Coords> &Tempocandidates, vector<Cell> &Already) {
  if (hit == true) {
    // Clear all other candidates to make sorting easier
    Candidatecoords.clear();

    // The filling algorithm
    // Takes all four adjacent blocks of the last cell that are within boundary
    // and reported a success Why those four? Since the next ship must be in one
    // of those four blocks
    if (((c.i) + 1 < 7) && yourOcean[(c.i) + 1][c.j].torpedo == false) {
      Tempocandidates.push_back({(c.i) + 1, c.j});
    }
    if (((c.j) + 1 < 7) && yourOcean[c.i][(c.j) + 1].torpedo == false) {
      Tempocandidates.push_back({c.i, (c.j) + 1});
    }
    if (((c.i) - 1 > -1) && yourOcean[(c.i) - 1][c.j].torpedo == false) {
      Tempocandidates.push_back({(c.i) - 1, c.j});
    }
    if (((c.j) - 1 > -1) && yourOcean[c.i][(c.j) - 1].torpedo == false) {
      Tempocandidates.push_back({c.i, (c.j) - 1});
    }
    // Those four blocks gets pushed first into a temporary vector. Then gets
    // pushed to the front of the Candidatecoords vector, waiting to be selected
    // by the decide function. Then the loop will ultimatly delete all invalid
    // blocks and land a correct hit
    Already.push_back(yourOcean[c.i][c.j]);
    Candidatecoords.insert(Candidatecoords.begin(), Tempocandidates.begin(),
                           Tempocandidates.end());
    // Clears the tempocandidates to make room for the next successful hit
    Tempocandidates.clear();

  } else if (hit == false) {
    Already.push_back(yourOcean[c.i][c.j]);
    // Erase the first element to make the second element candidate the first
    // element
    Candidatecoords.erase(Candidatecoords[0]);
  }
}

// This function is called before a match starts,
// before the two players start firing torpedos.
// At the very least, you need to put a ship in
// your ocean, 4 consecutive cells verticle or
// horizontal (with ship=true).  You may also
// set up anything else you like for your strategy.
void Yi::matchInit() {
  // Ship placed at [2][3],[3][3],[4][3],[5][3]
  for (int i = 2; i < 6; i++) {
    myOcean[i][3].ship = true;
  }
}
