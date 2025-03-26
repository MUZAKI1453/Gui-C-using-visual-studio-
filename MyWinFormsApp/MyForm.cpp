#include "MyForm.h"

using namespace MyWinFormsApp;

[STAThreadAttribute]
int main(array<System::String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    MyForm form;
    Application::Run(% form);
    return 0;
}