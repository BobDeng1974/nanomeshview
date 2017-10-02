/*
* nanomeshviewer : minimalist mesh viewer based on libigl, nanogui and other open source projects
*
* Copyright (C) 2016 by VLAM3D Software inc. https://www.vlam3d.com
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/  

#include <args.hxx>
#include <iostream>
#include <experimental/filesystem>
#include <igl/draco/readDRC.h>
#include <igl/readOFF.h>
#include <igl/readOBJ.h>
#include <igl/readPLY.h>
#include <igl/viewer/Viewer.h>
// workaround an issue with autoexplicit for readSTL and readWRL
#undef IGL_STATIC_LIBRARY
#include <igl/list_to_matrix.h>
#include <igl/readSTL.h>
#include <igl/readWRL.h>

Eigen::MatrixXd V;
Eigen::MatrixXi F;
Eigen::MatrixXi N;

namespace fs = std::experimental::filesystem;

int main(int argc, char *argv[])
{
    args::ArgumentParser parser("nanomeshview: minimalist mesh viewer", "");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    args::Positional<std::string> input_mesh(parser, "input_mesh", "Full path to input mesh [DRC, OFF, OBJ, PLY, STL, WRL] ");

    try
    {
        parser.ParseCLI(argc, argv);

        if (!input_mesh)
        {
            throw args::UsageError("Missing input_mesh argument");
        }
    }
    catch (args::Help)
    {
        std::cout << parser;
        return 0;
    }
    catch (args::UsageError e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    catch (args::ParseError e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    assert(input_mesh);
    fs::path input_mesh_path(args::get(input_mesh));
    if (!fs::exists(input_mesh_path))
    {
        std::cerr << input_mesh_path << " not found" << std::endl;
        return 1;
    }

    // DRC, OFF, OBJ, PLY, STL, WRL
    if (input_mesh_path.extension() == ".drc")
    {
        igl::readDRC(args::get(input_mesh), V, F);
    }
    else if (input_mesh_path.extension() == ".off")
    {
        igl::readOFF(args::get(input_mesh), V, F);
    }
    else if (input_mesh_path.extension() == ".obj")
    {
        igl::readOBJ(args::get(input_mesh), V, F);
    }
    else if (input_mesh_path.extension() == ".ply")
    {
        igl::readPLY(args::get(input_mesh), V, F);
    }
    else if (input_mesh_path.extension() == ".stl")
    {
        igl::readSTL(args::get(input_mesh), V, F, N);
    }
    else if (input_mesh_path.extension() == ".wrl")
    {
        std::vector<std::vector<double>> vV;
        std::vector<std::vector<double>> vF;
        igl::readWRL(args::get(input_mesh), vV, vF);
        igl::list_to_matrix(vV, V);
        igl::list_to_matrix(vF, F);
    }

    // Plot the mesh
    igl::viewer::Viewer viewer;
    viewer.data.set_mesh(V, F);
    viewer.launch();

    return 0;
}
