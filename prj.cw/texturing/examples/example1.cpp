#include <texture.h>

/*
������ �������� ������ ������ �� ����� � ��������� ������ �������� 
*/
int main() {
    Simur object;
    OneObj oneObj;
    oneObj.LoadProgramObject("face");
    oneObj.CreateViewerOBJData("face");
    oneObj.callback_key_down = [&](igl::opengl::glfw::Viewer& viewer, unsigned int key, int modifier) {
        return oneObj.key_down(viewer, key, modifier); 
        };
    oneObj.launch();
  
}