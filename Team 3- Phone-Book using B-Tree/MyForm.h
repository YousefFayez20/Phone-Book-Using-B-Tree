#pragma once
#include "Tree.hpp"
#include "MyForm1.h"
#include "MyForm2.h"
#include "MyForm3.h"
#include <msclr/marshal_cppstd.h>
#include <msclr/marshal.h>
#include<iostream>
#include <string>
#include <fstream>
using namespace std;
BTree b(3);

namespace really {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			ifstream infile("C:\\Users\\hamsa\\Desktop\\Liam.txt");
			string word1, word2;
			while (infile >> word1 >> word2) {
				b.insertion(word2, word1);
			}

			infile.close();
			TraverseArray();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Label^ label1;




	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::Label^ label2;




	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(47, 401);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(215, 48);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Insert";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(652, 401);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(215, 48);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Delete";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(348, 401);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(215, 48);
			this->button3->TabIndex = 4;
			this->button3->Text = L"Search";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Demi Cond", 48, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(891, 98);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Welcome to the Phone-Book";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// listBox1
			// 
			this->listBox1->BackColor = System::Drawing::Color::White;
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(370, 173);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(175, 173);
			this->listBox1->TabIndex = 11;
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Demi Cond", 27.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(370, 122);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(175, 39);
			this->label2->TabIndex = 12;
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(915, 461);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::SystemColors::ControlText;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->TransparencyKey = System::Drawing::Color::Maroon;
			this->ResumeLayout(false);

		}
#pragma endregion
	private:void TraverseArray()
	{
		listBox1->Items->Clear();
		arr.clear();
		b.traverse();
		for (int i = 0; i < arr.size(); i += 2)
		{
			std::string stdStr = arr[i];
			System::String^ str = msclr::interop::marshal_as<System::String^>(stdStr);
			listBox1->Items->Add(str);
			std::string stdStr1 = arr[i + 1];
			System::String^ str1 = msclr::interop::marshal_as<System::String^>(stdStr1);
			listBox1->Items->Add(str1);
			listBox1->Items->Add("");
		}
	}
	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		MyForm3^ form3 = gcnew MyForm3();
		form3->ShowDialog();
		string node1 = b.search(form3->GetText1());
		if (node1 != "") {
			String^ managedStr = gcnew String(node1.c_str());
			label1->Text = "Found Succesfully with Name: ";
		    label2->Text = managedStr;
		}
		else {
			label1->Text = "Not Found";
		}
	};

		   //delete from tree
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		MyForm2^ form2 = gcnew MyForm2();
		form2->ShowDialog();
		if (b.search(form2->GetPhone1()) != "") {
			b.deletion(form2->GetPhone1());
			label1->Text = "Deleted";
			TraverseArray();
		}
		else { label1->Text = "There is no such number"; }
		label2->Text = "";
	}
		   //insert in the b-tree
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		MyForm1^ form1 = gcnew MyForm1();
		form1->ShowDialog();
		//int d = 0100000000;
		//if (atoi(form1->GetPhone().c_str()) < d) {
		//	label1->Text = "Invalid Phone Number";
		//}
		if (b.search(form1->GetPhone()) == "") {
			b.insertion(form1->GetPhone(), form1->GetName());
			//label1->Text = "Inserted Succesfully";
			TraverseArray();
		}
		else { label1->Text = "This number already exists"; }
		label2->Text = "";
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
