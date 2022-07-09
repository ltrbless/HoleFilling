#include "HoleFiller.h"
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/IO/reader/OFFReader.hh>
#include <OpenMesh/Core/IO/writer/OFFWriter.hh>
#include <iostream>

int main(int argc,char* argv[])
{
	OpenMesh::IO::_OFFReader_();
	OpenMesh::IO::_OFFWriter_();
    using Triangle_mesh = OpenMesh::TriMesh_ArrayKernelT<>;
  	Triangle_mesh mesh;
		// OpenMesh::IO::read_mesh(mesh, "D:/data/holeMesh/coutRepair.stl");
		OpenMesh::IO::read_mesh(mesh, "/home/taoran/HoleFill/MeshHoleFiller/test/bunnyhole.off");
		HoleFiller::SmoothMeshBoundary(mesh);
		for (auto hh : mesh.halfedges()) {
			if (mesh.is_boundary(hh)) {
				HoleFiller::hole_fillC0(mesh, hh, FixType::idMinAreaMaxDiheral);
			}
		}
		OpenMesh::IO::write_mesh(mesh, "/home/taoran/HoleFill/MeshHoleFiller/test/bunnyhole_c0_idminareamaxdiheral_out.off");
  return 0;
}

// #include <iostream>
// #include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
// #include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
// #include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
// #include <OpenMesh/Core/Mesh/PolyConnectivity.hh>
// #include <OpenMesh/Core/IO/MeshIO.hh>
// #include <OpenMesh/Core/Mesh/Traits.hh>
// #include <OpenMesh/Tools/Smoother/JacobiLaplaceSmootherT.hh>
// #include <OpenMesh/Core/IO/reader/OFFReader.hh>


// int main()
// {
// 	OpenMesh::IO::_OFFReader_();
// 	using Triangle_mesh = OpenMesh::TriMesh_ArrayKernelT<>;
// 	Triangle_mesh mesh;
// 	std::cout << "Hello\n";
// 	OpenMesh::IO::read_mesh(mesh, "/home/taoran/HoleFill/MeshHoleFiller/test/bunnyhole.off");
	
// 	return 0;
// }