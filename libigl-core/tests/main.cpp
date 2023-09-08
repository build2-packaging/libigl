// This simple test is taken from
// the first tutorial of the documentation.
//
#include <iostream>
//
#include <igl/readOFF.h>
#include <igl/writeOBJ.h>

using namespace std;

int main(int argc, char *argv[]) {
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;

  // Load a mesh in OFF format
  igl::readOFF("cube.off", V, F);

  // Print the vertices and faces matrices
  cout << "Vertices:\n"
       << V << '\n'  //
       << "Faces:\n"
       << F << endl;

  // Save the mesh in OBJ format
  igl::writeOBJ("cube.obj", V, F);
}
