#include <texture.h>

/*
������ ���������� ������, ��������� �� ���������� �����, � ����� ��������� �� ��� ������� 
*/
int main() {
    Simur object;
    NotOneObj notOneObj;
    std::vector<int> ids;
    notOneObj.LoadObjects(ids);
    notOneObj.callback_key_down = [&notOneObj](igl::opengl::glfw::Viewer& viewer, unsigned int key, int modifier) {
        return notOneObj.key_down(viewer, key, modifier);
        };
    notOneObj.launch();

}