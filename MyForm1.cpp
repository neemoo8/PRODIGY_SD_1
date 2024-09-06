#include "MyForm1.h"
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

System::Void convtemp1::MyForm1::button1_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Close();

	MyForm^ newForm = gcnew MyForm();
	newForm->Show();
}