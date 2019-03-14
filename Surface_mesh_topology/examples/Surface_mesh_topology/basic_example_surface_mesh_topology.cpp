#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Surface_mesh_curve_topology.h>

#include <CGAL/Path_generators.h>
#include <CGAL/Path_on_surface.h>
#include <CGAL/draw_lcc_with_paths.h>

typedef CGAL::Linear_cell_complex_for_combinatorial_map<2,3> LCC_3_cmap;

///////////////////////////////////////////////////////////////////////////////
int main()
{
  LCC_3_cmap lcc;
  if (!CGAL::load_off(lcc, "data/double-torus-example.off"))
  {
    std::cout<<"ERROR reading file data/double-torus-example.off"<<std::endl;
    exit(EXIT_FAILURE);
  }

  CGAL::Surface_mesh_curve_topology<LCC_3_cmap> smct(lcc);

  CGAL::Path_on_surface<LCC_3_cmap> p1(lcc); // A first path
  p1.push_back_by_index(14); // Its starting dart
  for (int i=0; i<7; ++i)
  { p1.extend_positive_turn(2); } // Extend the path
  
  CGAL::Path_on_surface<LCC_3_cmap> p2(lcc); // A second path
  std::vector<std::size_t> indices={202, 206, 335, 317, 322, 69, 62, 414}; // All the indices of the darts
  for (int i=0; i<indices.size(); ++i)
  { p2.push_back_by_index(indices[i]); }

  CGAL::Path_on_surface<LCC_3_cmap> p3(lcc); // A third path
  p3.push_back_by_index(470); // Its starting dart
  for (int i=0; i<13; ++i)
  { p3.extend_positive_turn(2); } // Extend the path
  
  bool res1=smct.is_contractible(p1);
  std::cout<<"Path p1 (pink) "<<(res1?"IS":"IS NOT")<<" contractible."<<std::endl;
  
  bool res2=smct.are_freely_homotopic(p1, p2);
  std::cout<<"Path p1 (pink) "<<(res2?"IS":"IS NOT")<<" homotopic with path p2 (green)."<<std::endl;

  bool res3=smct.are_freely_homotopic(p1, p3);
  std::cout<<"Path p1 (pink) "<<(res3?"IS":"IS NOT")<<" homotopic with path p3 (orange)."<<std::endl;

#ifdef CGAL_USE_BASIC_VIEWER
  std::vector<CGAL::Path_on_surface<LCC_3_cmap> > paths;
  paths.push_back(p1);
  paths.push_back(p2);  
  paths.push_back(p3);  
  CGAL::draw(lcc, paths); // Enable only if CGAL was compiled with Qt5
#endif // CGAL_USE_BASIC_VIEWER
  
  return EXIT_SUCCESS;
}
