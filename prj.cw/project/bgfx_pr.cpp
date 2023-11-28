#include <igl/readOBJ.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/colormap.h>
#include <stb_image.h>
#include <D:/proga_pr/libigl/include/igl/stb/read_image.h>


//буду хранить объект
struct project_object {
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    Eigen::MatrixXd V_uv;
    Eigen::MatrixXi F_uv;
    Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> texture_R,
        texture_G, texture_B, texture_A;
};

std::map<std::string, std::string> obj_pass = {
    {"sphere", "D:/proga_pr/projects/bgfx_pr/sphere.obj"},
    {"face", "D:/proga_pr/projects/bgfx_pr/face.obj"},
    {"cube", "D:/proga_pr/projects/bgfx_pr/cube.obj"}
};



std::map<std::string, std::string> texture_pass = {
    { "started", "C:/Users/katya/OneDrive/Рабочий стол/d1bd21ec56d7af6c4f54cd3fc421f356.png"},
    {"skin1", "C:/Users/katya/Downloads/1K - human_skin_4_diffuseOriginal.png"},
    {"color", "C:/Users/katya/Downloads/pngwing.com.png"}
};

class Object : public igl::opengl::glfw::Viewer
{
private:


public:
    Object() = default;
    ~Object() = default;
    

    std::map<std::string, project_object> project_objects_map; //словарь в котором лежат ключи ввиде названий моделей и объект структуры 
                                                                //в которой хранятся матрицы с вершинами, поверхностями и текстурными штуками

    bool load_program_object(std::string fileOBJ) {
        Eigen::MatrixXd normals;
        Eigen::MatrixXi fNorm;

        Eigen::MatrixXd UV_V;
        Eigen::MatrixXi UV_F;
        Eigen::MatrixXd V;
        Eigen::MatrixXi F;
        Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> texture_R,
            texture_G, texture_B, texture_A;

        auto itO = obj_pass.find(fileOBJ);
        if (itO == obj_pass.end()) {
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
        auto started_tex = texture_pass.find("started")->second;
        if (igl::stb::read_image(started_tex, texture_R, texture_G, texture_B, texture_A)) {
            std::cerr << "Error opening texture file" << std::endl;
            return false;
        }
        //занесу данные объекта в структуру     PROJECT_MODEL   (вершины, поверхности, данные о текстуре)
        project_objects_map.insert(std::pair<std::string, 
                                            struct project_object>(fileOBJ, project_object{ V, F, UV_V, UV_F,
                                                texture_R, texture_G, texture_B, texture_A }));
        return true;
    }



    void create_viewerOBJ_data(std::string obj_name, std::string texture_name) {
        std::cout << "+" << std::endl;
        auto it = project_objects_map.find(obj_name);
        std::cout << "+" << std::endl;
        if (it != project_objects_map.end()) {
            std::cout << "+" << std::endl;
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

            loading_texture(texture_name);

        }   
    }

    void create_viewerOBJ_data(std::string obj_name) {
        std::cout << "+" << std::endl;
        auto it = project_objects_map.find(obj_name);
        std::cout << "+" << std::endl;
        if (it != project_objects_map.end()) {
            std::cout << "+" << std::endl;
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
    }

    void loading_texture(std::string texture_name) {
        auto it = texture_pass.find(texture_name);
        if (it != texture_pass.end()) {
            Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> R, G, B, A;
            std::string pass_to_texture = it->second;
            igl::stb::read_image(pass_to_texture, R, G, B, A);
            data().set_texture(R, G, B, A);
            data().use_matcap = true;
            
        }
    }

    ////не мое
    //bool read_image(std::string image_file,
    //    Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>& R,
    //    Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>& G,
    //    Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>& B,
    //    Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>& A)
    //{
    //    int cols, rows, n;
    //    unsigned char* data = stbi_load(image_file.c_str(), &cols, &rows, &n, 4);
    //    if (data == NULL) {
    //        return false;
    //    }

    //    R.resize(cols, rows);
    //    G.resize(cols, rows);
    //    B.resize(cols, rows);
    //    A.resize(cols, rows);

    //    for (unsigned i = 0; i < rows; ++i) {
    //        for (unsigned j = 0; j < cols; ++j) {
    //            R(j, rows - 1 - i) = data[4 * (j + cols * i) + 0];
    //            G(j, rows - 1 - i) = data[4 * (j + cols * i) + 1];
    //            B(j, rows - 1 - i) = data[4 * (j + cols * i) + 2];
    //            A(j, rows - 1 - i) = data[4 * (j + cols * i) + 3];
    //        }
    //    }

    //    stbi_image_free(data);
    //    return true;
    //}
};



int main() {
    Object object;
    object.load_program_object("sphere");
    object.create_viewerOBJ_data("sphere", "color");
    object.launch();

}