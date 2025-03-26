#pragma once

namespace MyWinFormsApp {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            // Tambahkan event handler
            buttonExit->Click += gcnew EventHandler(this, &MyForm::buttonExit_Click);
            buttonInfo->Click += gcnew EventHandler(this, &MyForm::buttonInfo_Click);
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        System::Windows::Forms::Button^ buttonExit; 
        System::Windows::Forms::Button^ buttonInfo; 

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->buttonExit = (gcnew System::Windows::Forms::Button());
            this->buttonInfo = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // buttonExit
            // 
            this->buttonExit->Location = System::Drawing::Point(10, 260);
            this->buttonExit->Name = L"buttonExit";
            this->buttonExit->Size = System::Drawing::Size(75, 23);
            this->buttonExit->TabIndex = 0;
            this->buttonExit->Text = L"exit";
            this->buttonExit->UseVisualStyleBackColor = true;
            // 
            // buttonInfo
            // 
            this->buttonInfo->Location = System::Drawing::Point(90, 260);
            this->buttonInfo->Name = L"buttonInfo";
            this->buttonInfo->Size = System::Drawing::Size(75, 23);
            this->buttonInfo->TabIndex = 1;
            this->buttonInfo->Text = L"masuk";
            this->buttonInfo->UseVisualStyleBackColor = true;
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(300, 300);
            this->Controls->Add(this->buttonInfo);
            this->Controls->Add(this->buttonExit);
            this->Name = L"MyForm";
            this->Text = L"MyForm";
            this->ResumeLayout(false);
        }
#pragma endregion

    private:
        void buttonExit_Click(System::Object^ sender, System::EventArgs^ e) {
            Application::Exit(); 
        }

        void buttonInfo_Click(System::Object^ sender, System::EventArgs^ e) {
            MessageBox::Show("Ini adalah aplikasi Windows Forms sederhana.", "Informasi");
        }
    };
}