#include "texture.h"
#include <iostream>
#include <igl/readOBJ.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/colormap.h>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION 
#include <stb_image.h>


void Simur::ReadImage(std::string key_image_name,
    Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>& R,
    Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>& G,
    Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>& B,
    Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>& A)
{
    auto it = texture_pass.find(key_image_name);
    std::string pass_to_img = "";
    pass_to_img = it->second;

    int width, height, channels;
    unsigned char* img = stbi_load(pass_to_img.c_str(), &width, &height, &channels, 0);
    if (img == NULL) {
        std::cerr << "Error in loading the image" << std::endl;
    }


    R.resize(width, height);
    G.resize(width, height);
    B.resize(width, height);
    A.resize(width, height);

    for (unsigned i = 0; i < height; ++i) {
        for (unsigned j = 0; j < width; ++j) {
            R(j, height - 1 - i) = img[4 * (j + width * i) + 0];
            G(j, height - 1 - i) = img[4 * (j + width * i) + 1];
            B(j, height - 1 - i) = img[4 * (j + width * i) + 2];
            A(j, height - 1 - i) = img[4 * (j + width * i) + 3];
        }
    }
    stbi_image_free(img);
};

void Simur::LoadTexture(std::string texture_name) {
    auto it = texture_pass.find(texture_name);
    if (it != texture_pass.end()) {
        std::cout << "texture was found" << std::endl;
        Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> R, G, B, A;
        ReadImage(texture_name, R, G, B, A);
        data().set_texture(R, G, B, A);
        data().use_matcap = true;
    }
    else {
        std::cerr << "Texture was not found" << std::endl;
    }
};


void Simur::LoadTexture(int InputId, std::string name) {
    auto it = texture_pass.find(name);
    if (it != texture_pass.end()) {
        std::cout << "texture was found" << std::endl;
        Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> R, G, B, A;
        ReadImage(name, R, G, B, A);
        data(InputId).set_texture(R, G, B, A);
        data(InputId).use_matcap = true;
    }
    else {
        std::cerr << "Texture was not found" << std::endl;
    }
};


void Simur::InputCustomTexture(const std::string& name_part_of_face, std::string& pass) {
    std::ifstream file(pass);
    if (!file.is_open()) {
        std::cerr << "Input correct file pass ";
        std::cin >> pass;
    }
    else {
        std::string full_name = name_part_of_face + std::to_string(pass.length() % 11);
        texture_pass.insert(std::make_pair(full_name, pass));
        std::cout << "Use this texture with number " << pass.length() % 11 << std::endl;
    }

};


bool OneObj::LoadProgramObject(std::string fileOBJ) {
    Eigen::MatrixXd normals;
    Eigen::MatrixXi fNorm;

    Eigen::MatrixXd UV_V;
    Eigen::MatrixXi UV_F;
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> texture_R,
        texture_G, texture_B, texture_A;

    auto itO = face_pass.find(fileOBJ);
    if (itO == face_pass.end()) {
        std::cerr << "Unknown model. Put correct name" << std::endl;
        return false;
    }

    //считаю модельку obj
    if (!(igl::readOBJ(itO->second, V, UV_V, normals, F, UV_F, fNorm))) {
        std::cerr << "Error reading OBJ file" << "file name" << std::endl;
        return false;
    }
    else {
        std::cout << "Model was loaded" << std::endl;
    }

    //установлю текстуру по умолчанию (серый цвет)
    auto started_tex = texture_pass.find("face1")->second;
    //занесу данные объекта в структуру     PROJECT_MODEL   (вершины, поверхности, данные о текстуре)
    project_objects_map.insert(std::pair<std::string,
        struct project_object>(fileOBJ, project_object{ V, F, UV_V, UV_F,
            texture_R, texture_G, texture_B, texture_A }));
    return true;
}




void OneObj::CreateViewerOBJData(std::string obj_name, std::string texture_name) {
    auto it = project_objects_map.find(obj_name);
    if (it != project_objects_map.end()) {
        //проверяем не пустой ли текущий набор данных 
        if (!(data().V.rows() == 0 && data().F.rows() == 0)) {
            append_mesh();  /* на самом деле это выглядит так igl::opengl::glfw::Viewer.append_mesh()*/
        }
        data().set_mesh(it->second.V, it->second.F); /* по файкту взяли и обратились к значению ключа
        (а это есть наша структура) и достали оттуда матрицы V F*/
        if (it->second.V_uv.rows() == 0) {
            data().grid_texture();
        }
        else {
            data().set_uv(it->second.V_uv, it->second.F_uv);
        }
        data().set_colors(Eigen::RowVector3d(1, 1, 1));

        LoadTexture(texture_name);
    }
};



void OneObj::CreateViewerOBJData(std::string obj_name) {
    auto it = project_objects_map.find(obj_name);
    if (it != project_objects_map.end()) {
        //проверяем не пустой ли текущий набор данных 
        if (!(data().V.rows() == 0 && data().F.rows() == 0)) {
            append_mesh();  /* на самом деле это выглядит так igl::opengl::glfw::Viewer.append_mesh()*/
        }
        data().set_mesh(it->second.V, it->second.F); /* по файкту взяли и обратились к значению ключа
        (а это есть наша структура) и достали оттуда матрицы V F*/
        if (it->second.V_uv.rows() == 0) {
            data().grid_texture();
        }
        else {
            data().set_uv(it->second.V_uv, it->second.F_uv);
        }
        data().set_colors(Eigen::RowVector3d(1, 1, 1));

    }
};

bool OneObj::key_down(igl::opengl::glfw::Viewer& viewer, unsigned int key, int modifier) {
    std::string name = "face";
    if (key == '1') {
        LoadTexture("face1");
    }
    if (key == '2') {
        LoadTexture("face2");
    }
    if (key == '3') {
        LoadTexture("face" + std::to_string(3));
    }
    return false;
}



void NotOneObj::LoadObjects(std::vector<int>& idOfMeshes) {

    for (auto el = parts_head.begin(); el != parts_head.end(); el++) {
        load_mesh_from_file(el->second);
        LoadTexture("face1");
        int id = data().id;

        idOfMeshes.push_back(id);
    }
    
     std::ifstream file("..\\descriptions.txt");
        if (!file.is_open()) {
      std::cerr << "Не удалось открыть файл " << "descriptions.txt" << "\n";
      return;
  }

  std::string line;
  while (std::getline(file, line)) {
      std::cout << line << '\n';
  }

  file.close();
}

void NotOneObj::ChangeColorOBJ(int InputId, int r, int g, int b) {
    Eigen::MatrixXd C;
    C.resize(1183, 3);
    for (int i = 0; i < 1183; ++i) {
        C(i, 0) = r / 255.0;
        C(i, 1) = g / 255.0;
        C(i, 2) = b / 255.0;
    }
    std::cout << "+";
    data(InputId).set_colors(C);
    std::cout << "+";
}

void NotOneObj::getPart() {
    std::cout << "Input part of head that you with to texture" << std::endl;
    std::string state;
    std::cin >> state;
    std::cout << std::endl;
}



bool NotOneObj::key_down(igl::opengl::glfw::Viewer& viewer, unsigned int key, int modifier) {
    int number;
    if (key == 'S') {
        std::cout << "Choose texture:" << std::endl << "press key 1 for white" << std::endl
            << "press key 2 for ivory" << std::endl << "press key 3 for sandy" << std::endl;
        std::cin >> number;
        LoadTexture(4, "skin" + std::to_string(number));

    };

    //eyes
    if (key == 'E') {
        std::cout << "Choose texture:" << std::endl << "press key 1 for green" << std::endl
            << "press key 2 for brown" << std::endl << "press key 3 for blue" << std::endl;

        std::cin >> number;
        LoadTexture(2, "eye" + std::to_string(number));

    }

    //lips
    if (key == 'G') {
        std::cout << "Choose texture:" << std::endl << "press key 1 for pink" << std::endl
            << "press key 2 for red" << std::endl << "press key 3 for another red" << std::endl;
        std::cin >> number;
        LoadTexture(3, "lips" + std::to_string(number));

    }
    //brows
    if (key == 'B') {
        std::cout << "Choose texture:" << std::endl << "press key 1 for light brown" << std::endl
            << "press key 2 for brown" << std::endl << "press key 3 for dark brown" << std::endl;
        std::cin >> number;
        LoadTexture(1, "brows" + std::to_string(number));

    }
    //blushes by color
    if (key == 'R') {
        std::cout << "Input color of blushes in rgb" << std::endl;
        std::cout << "You can choose one of 255/182/193" << std::endl;
        std::cout << "255/105/180" << std::endl;
        std::cout << "255/20/147 or your" << std::endl;
        int r, g, b;
        std::cin >> r;
        std::cin >> g;
        std::cin >> b;
        ChangeColorOBJ(0, r, g, b);
    }

    if (key == 'X') {
        std::cout << "Now you can add your texture" << std::endl;
        std::cout << "Add name of part such as skin eye lips brows and then full pass to the file" << std::endl;
        std::string name;
        std::string pass;
        std::cin >> name >> pass;
        InputCustomTexture(name, pass);
    }
    return false;
}
