#include <igl/readOBJ.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/colormap.h>
#define STB_IMAGE_IMPLEMENTATION 
#include <stb_image.h>



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
    {"sphere", "/sphere.obj"},
    {"face", "/face.obj"},
    {"cube", "/cube.obj"}
};



std::map<std::string, std::string> texture_pass = {
    { "started", "/d1bd21ec56d7af6c4f54cd3fc421f356.png"},
    {"skin1", "/1K - human_skin_4_diffuseOriginal.png"},
    {"color", "/pngwing.com.png"}
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
        //if (stb::read_image(started_tex, texture_R, texture_G, texture_B, texture_A)) {
        //    std::cerr << "Error opening texture file" << std::endl;
        //    return false;
        //}
     

        //unsigned char* data = stbi_load("testTexture.png", &texture_R, &texture_G, &texture_B, &texture_A);

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
            std::cout << "texture was found" << std::endl;
            Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> R, G, B, A;
            read_image(texture_name, R, G, B, A);
            data().set_texture(R, G, B, A);
            data().use_matcap = true;   
        }
    }

    void read_image(std::string key_image_name,
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
        }
};


int main() {
    Object object;
    object.load_program_object("face");
    object.create_viewerOBJ_data("face", "color");
    object.launch();


    
}
