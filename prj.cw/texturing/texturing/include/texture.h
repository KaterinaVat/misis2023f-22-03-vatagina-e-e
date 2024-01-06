#include <igl/readOBJ.h>
#include <igl/opengl/glfw/Viewer.h>


/*!
    \file texture.h
    \brief заголовочный файл с описанием классов Simur, OneObj и NotOneObj

    

    Класс Simur - родительский класс
    Классы OneObj и NotOneObj - дочерние 


*/

/**
 * @class Simur
 * @brief Класс содержащий вспомогательный  методы, связанные с чтением изображения, 
 *   добавлением пользовательской тестуры и наложения текстуры на объекты 
 * @details Класс управляет доступом к используемым входным данным таким как текстуры, сетки ввиде файлов obj
 * @details наследует igl::opengl::glfw::Viewer
 */
class Simur :public igl::opengl::glfw::Viewer {
public:


 /**
 * @brief Словарь содержит в себе ввиде ключа название части лица и ввиде значения путь к соответствующему obj файлу
 * @details Данный словарь предназначен для загрузки лица как совокупности различных сеток
 */
    std::map <std::string, std::string> parts_head =
    { {"skin", "../human_head/skin.obj"},
        {"eye", "../human_head/eye.obj"},
        {"lips", "../human_head/lips.obj"},
        {"brows", "../human_head/brows.obj"},
        {"blushes","../human_head/blushes.obj"}
    };

    /**
 * @brief Словарь содержит в себе ввиде ключа название части лица и ввиде значения путь к соответствующему obj файлу
 * @details Данный словарь предназначен для загрузки лица как единой сетки
 */

    std::map <std::string, std::string> face_pass =
    {
        {"face", "../face.obj"}
    };


    /**
 * @struct project_object
 * @brief структура, содержащая данные сетки
 *
 * V - количество вершин 
 * F - количество поверхностей
 * V_uv, F_uv - текстурные координаты
 * texture_* (R,G,B,A) - значения матрицы оттенков в rgb
 * 
 */

    struct project_object {
        Eigen::MatrixXd V;
        Eigen::MatrixXi F;
        Eigen::MatrixXd V_uv;
        Eigen::MatrixXi F_uv;
        Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> texture_R,
            texture_G, texture_B, texture_A;
    };



    /**
* @brief Словарь содержит в себе ввиде ключа название части лица и индекс обращения и ввиде значения путь к соответствующему png файлу текстуры
* @details Возможно добавление элементов в данный словарь
*/
    std::map<std::string, std::string> texture_pass = {
    {"face1", "../textures/серый.png"},
    {"face2", "../textures/pngwing.com.png"},
    {"face3", "..\\textures\\light.png"},


    { "eye1", "../textures\\green.png"},
    { "eye3", "../textures\\blue.png"},
    { "eye2", "../textures\\brown.png"},

    { "skin1", "../textures\\light.png"},
    { "skin2", "../textures\\ivory.png"},
    { "skin3", "../textures\\sandy.png"},

    { "brows3", "../textures\\brown.png"},
    { "brows2", "../textures\\pictureb.png"},
    { "brows1", "../textures\\picturebl.png"},


    { "lips1", "../textures/розовый.png"},
    { "lips2", "../textures/red.png"},
    { "lips3", "../textures/another_red.png"},

    };


    /**
    * @brief метод для чтения изображения
    * @param key_image_name ключ к изображению
    * @param R матрица с коэффициентами оттенка красного
    * @param G матрица с коэффициентами оттенка зеленого
    * @param B матрица с коэффициентами оттенка синего
    */
    void ReadImage(std::string key_image_name,
        Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>& R,
        Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>& G,
        Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>& B,
        Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>& A);
    /**
  * @brief метод для установки текстуры на сетку
  * @param texture_name ключ к изображению
  */
    void LoadTexture(std::string texture_name); 
    /**
* @brief метод для установки текстуры на сетку
* @param InputId индекс соответствующей текстуры
* @param texture_name ключ к изображению
*/
    void LoadTexture(int InputId, std::string name); 
    /**
* @brief метод для загрузки пользовательской текстуры
* @param name_part_of_face название части лица
* @param pass абсолютный путь к изображению
*/
    void InputCustomTexture(const std::string& name_part_of_face, std::string& pass); 

};




/**
 * @class OneObj
 * @brief Класс содержащий методы, связанные рендерингом сеток и фиксировании отратных вызовов 
 */
class OneObj : public Simur {
public:
    std::map<std::string, project_object> project_objects_map;
 
    /**
* @brief метод для загрузки  единого объекта
* @param fileOBJ ключ к файлу сетки
*/
    bool LoadProgramObject(std::string fileOBJ);  
 
    /**
* @brief метод для рендеринга единого объекта
* @param obj_name ключ к файлу сетки
* @param texture_name ключ к файлу сетки
*/
    void CreateViewerOBJData(std::string obj_name, std::string texture_name);

    /**
* @brief метод для рендеринга единого объекта
* @param obj_name ключ к файлу сетки
*/
    void CreateViewerOBJData(std::string obj_name);
    /**
* @brief метод для фиксирвоания обратного вызова с клавиатуры - назначение текстур объекту
*/
    bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned int key, int modifier);

};

/**
 * @class NotOneObj
 * @brief Класс содержащий методы, связанные рендерингом сеток и фиксировании отратных вызовов
 */
class NotOneObj : public Simur {
public:
    /**
* @brief метод для рендеринга составного объекта
* @param idOfMeshes вектор содержащий индексы сеток
*/
    void LoadObjects(std::vector<int>& idOfMeshes);


    /**
* @brief метод для изменения оттенка щек
* @param InputId индекс сетки
* @param r оттенок красного
* @param g оттенок зеленого
* @param b оттенок голубого
*
*/
    void ChangeColorOBJ(int InputId, int r, int g, int b); 
    /**
* @brief метод для считывания текста из консоли - предназначен для определения предназначения пользовательской текстуры
*/
    void getPart();

    /**
* @brief метод для фиксирвоания обратного вызова с клавиатуры - назначение текстур объекту
*/
    bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned int key, int modifier);
   
};
