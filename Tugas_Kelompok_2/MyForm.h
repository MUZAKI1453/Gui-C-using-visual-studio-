#pragma once

namespace StackWindowsFormsApp
{
    using namespace System;
    using namespace System::Windows::Forms;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
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
        System::Windows::Forms::ComboBox^ cboMenu;
        System::Windows::Forms::Button^ btnExecute;
        System::Windows::Forms::Button^ btnExit;
        System::Windows::Forms::TextBox^ txtInput;
        System::Windows::Forms::TextBox^ txtOutput;
        System::Windows::Forms::Label^ lblMessage;
        System::Windows::Forms::Label^ lblInput;
        System::Windows::Forms::Label^ lblMessageOutput;
        System::Windows::Forms::Button^ btnConfirm; // Tombol konfirmasi
        System::Windows::Forms::Timer^ messageTimer; // Timer untuk menghilangkan pesan

        const int MAX = 5;
        array<int>^ stack = gcnew array<int>(MAX);
        int top = -1;

        void InitializeComponent(void)
        {
            this->cboMenu = (gcnew System::Windows::Forms::ComboBox());
            this->btnExecute = (gcnew System::Windows::Forms::Button());
            this->btnExit = (gcnew System::Windows::Forms::Button());
            this->txtInput = (gcnew System::Windows::Forms::TextBox());
            this->txtOutput = (gcnew System::Windows::Forms::TextBox());
            this->lblMessage = (gcnew System::Windows::Forms::Label());
            this->lblInput = (gcnew System::Windows::Forms::Label());
            this->lblMessageOutput = (gcnew System::Windows::Forms::Label());
            this->btnConfirm = (gcnew System::Windows::Forms::Button()); // Inisialisasi tombol konfirmasi
            this->messageTimer = (gcnew System::Windows::Forms::Timer()); // Inisialisasi Timer

            // Timer Settings
            this->messageTimer->Interval = 3000; // Durasi 3 detik
            this->messageTimer->Tick += gcnew System::EventHandler(this, &MyForm::messageTimer_Tick);

            // cboMenu
            this->cboMenu->FormattingEnabled = true;
            this->cboMenu->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
                L"Push", L"Pop", L"Peek", L"IsEmpty", L"Size", L"Display"
            });
            this->cboMenu->Location = System::Drawing::Point(12, 12);
            this->cboMenu->Name = L"cboMenu";
            this->cboMenu->Size = System::Drawing::Size(121, 21);
            this->cboMenu->TabIndex = 0;

            // btnExecute
            this->btnExecute->Location = System::Drawing::Point(139, 12);
            this->btnExecute->Name = L"btnExecute";
            this->btnExecute->Size = System::Drawing::Size(75, 23);
            this->btnExecute->TabIndex = 1;
            this->btnExecute->Text = L"Execute";
            this->btnExecute->UseVisualStyleBackColor = true;
            this->btnExecute->Click += gcnew System::EventHandler(this, &MyForm::btnExecute_Click);

            // btnExit
            this->btnExit->Location = System::Drawing::Point(12, 200);
            this->btnExit->Name = L"btnExit";
            this->btnExit->Size = System::Drawing::Size(75, 23);
            this->btnExit->TabIndex = 2;
            this->btnExit->Text = L"Exit";
            this->btnExit->UseVisualStyleBackColor = true;
            this->btnExit->Click += gcnew System::EventHandler(this, &MyForm::btnExit_Click);

            // txtInput
            this->txtInput->Location = System::Drawing::Point(12, 69);
            this->txtInput->Name = L"txtInput";
            this->txtInput->Size = System::Drawing::Size(100, 20);
            this->txtInput->TabIndex = 3;
            this->txtInput->Visible = false;

            // txtOutput
            this->txtOutput->Location = System::Drawing::Point(12, 123);
            this->txtOutput->Multiline = true;
            this->txtOutput->Name = L"txtOutput";
            this->txtOutput->Size = System::Drawing::Size(250, 60);  // Perbesar ukuran TextBox output
            this->txtOutput->TabIndex = 4;
            this->txtOutput->Visible = false;

            // lblMessage
            this->lblMessage->Location = System::Drawing::Point(12, 103);
            this->lblMessage->Name = L"lblMessage";
            this->lblMessage->Size = System::Drawing::Size(200, 23);
            this->lblMessage->TabIndex = 5;
            this->lblMessage->Visible = false;

            // lblInput
            this->lblInput->Location = System::Drawing::Point(12, 53);
            this->lblInput->Name = L"lblInput";
            this->lblInput->Size = System::Drawing::Size(100, 13);
            this->lblInput->Text = L"Masukkan Elemen:";
            this->lblInput->Visible = false;

            // lblMessageOutput
            this->lblMessageOutput->Location = System::Drawing::Point(12, 186);
            this->lblMessageOutput->Name = L"lblMessageOutput";
            this->lblMessageOutput->Size = System::Drawing::Size(250, 23);  // Perbesar ukuran Label output
            this->lblMessageOutput->TabIndex = 6;
            this->lblMessageOutput->Visible = false;

            // btnConfirm (Tombol Konfirmasi)
            this->btnConfirm->Location = System::Drawing::Point(139, 69);
            this->btnConfirm->Name = L"btnConfirm";
            this->btnConfirm->Size = System::Drawing::Size(75, 23);
            this->btnConfirm->Text = L"Confirm";
            this->btnConfirm->Visible = false;
            this->btnConfirm->Click += gcnew System::EventHandler(this, &MyForm::btnConfirm_Click);

            // MyForm
            this->ClientSize = System::Drawing::Size(284, 261);
            this->Controls->Add(this->btnConfirm); // Menambahkan tombol konfirmasi
            this->Controls->Add(this->lblMessageOutput);
            this->Controls->Add(this->lblInput);
            this->Controls->Add(this->lblMessage);
            this->Controls->Add(this->txtOutput);
            this->Controls->Add(this->txtInput);
            this->Controls->Add(this->btnExit);
            this->Controls->Add(this->btnExecute);
            this->Controls->Add(this->cboMenu);
            this->Name = L"MyForm";
            this->Text = L"Stack Operations";
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        // Fungsi untuk menghandle tombol Execute
        void btnExecute_Click(System::Object^ sender, System::EventArgs^ e)
        {
            String^ selectedMenu = cboMenu->SelectedItem->ToString();
            if (selectedMenu == L"Push")
            {
                lblMessage->Visible = false;  // Menyembunyikan pesan
                lblInput->Visible = true;    // Menampilkan input untuk elemen
                txtInput->Visible = true;    // Menampilkan TextBox input
                btnConfirm->Visible = true;  // Menampilkan tombol konfirmasi
                txtOutput->Visible = false;  // Menyembunyikan output text
            }
            else if (selectedMenu == L"Pop")
            {
                lblMessage->Visible = false;  // Sembunyikan pesan
                lblInput->Visible = false;    // Sembunyikan input label
                txtInput->Visible = false;    // Sembunyikan input text
                txtOutput->Visible = false;   // Sembunyikan output text
                btnConfirm->Visible = false;  // Sembunyikan tombol konfirmasi

                // Lakukan operasi pop
                pop();
            }
            else if (selectedMenu == L"Peek")
            {
                lblMessage->Visible = false;
                lblInput->Visible = false;
                txtInput->Visible = false;
                txtOutput->Visible = true;
                btnConfirm->Visible = false; // Sembunyikan tombol konfirmasi
                txtOutput->Text = peek();
            }
            else if (selectedMenu == L"IsEmpty")
            {
                lblMessage->Visible = false;
                lblInput->Visible = false;
                txtInput->Visible = false;
                txtOutput->Visible = true;
                btnConfirm->Visible = false; // Sembunyikan tombol konfirmasi
                isEmpty();
            }
            else if (selectedMenu == L"Size")
            {
                lblMessage->Visible = false;
                lblInput->Visible = false;
                txtInput->Visible = false;
                txtOutput->Visible = true;
                btnConfirm->Visible = false; // Sembunyikan tombol konfirmasi
                size();
            }
            else if (selectedMenu == L"Display")
            {
                lblMessage->Visible = false;
                lblInput->Visible = false;
                txtInput->Visible = false;
                btnConfirm->Visible = false; // Sembunyikan tombol konfirmasi
                // Menampilkan elemen stack dalam txtOutput
                display();
            }
        }

        void btnConfirm_Click(System::Object^ sender, System::EventArgs^ e)
        {
            try
            {
                int elemen = Int32::Parse(txtInput->Text);
                push(elemen);
                lblMessageOutput->Text = "Elemen " + elemen + " berhasil ditambahkan ke dalam stack.";
                lblMessageOutput->Visible = true;

                // Mulai timer untuk menghapus pesan setelah beberapa detik
                messageTimer->Start();

                // Sembunyikan input, label, dan tombol konfirmasi setelah pesan berhasil ditampilkan
                lblMessage->Visible = false;
                lblInput->Visible = false;
                txtInput->Visible = false;
                btnConfirm->Visible = false;
            }
            catch (FormatException^)
            {
                lblMessageOutput->Text = "Input tidak valid!";
                lblMessageOutput->Visible = true;
                messageTimer->Start();
            }
        }

        void messageTimer_Tick(System::Object^ sender, System::EventArgs^ e)
        {
            // Hentikan timer dan sembunyikan pesan setelah 3 detik
            messageTimer->Stop();
            lblMessageOutput->Visible = false;
        }

        void push(int elemen)
        {
            if (top == MAX - 1)
            {
                lblMessageOutput->Text = "Stack penuh!";
            }
            else
            {
                stack[++top] = elemen;
            }
        }

        void pop()
        {
            if (top == -1)
            {
                txtOutput->Text = "Stack kosong! Tidak ada elemen yang bisa dihapus.";
            }
            else
            {
                txtOutput->Text = "Elemen " + stack[top--] + " telah dihapus.";
            }
            txtOutput->Visible = true;
            messageTimer->Start();
        }

        String^ peek()
        {
            if (top == -1)
            {
                return "Stack kosong!";
            }
            else
            {
                return "Elemen teratas: " + stack[top];
            }
        }

        void isEmpty()
        {
            if (top == -1)
            {
                txtOutput->Text = "Stack kosong!";
            }
            else
            {
                txtOutput->Text = "Stack tidak kosong!";
            }
            txtOutput->Visible = true;
            messageTimer->Start();
        }

        void size()
        {
            txtOutput->Text = "Ukuran stack saat ini: " + (top + 1);
            txtOutput->Visible = true;
            messageTimer->Start();
        }

        void display()
        {
            if (top == -1)
            {
                txtOutput->Text = "Stack kosong!";
            }
            else
            {
                String^ output = "Elemen-elemen dalam stack: ";
                for (int i = top; i >= 0; i--)
                {
                    output += stack[i] + " ";
                }
                txtOutput->Text = output;
            }
            txtOutput->Visible = true;
            messageTimer->Start();
        }

        void btnExit_Click(System::Object^ sender, System::EventArgs^ e)
        {
            this->Close();
        }
    };
}
