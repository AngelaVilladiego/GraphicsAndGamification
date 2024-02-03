#pragma once

#include "Vec3.h"
#include <string>
#include <stdexcept>
#include <iostream>

namespace Exercise1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ToolWindow
	/// </summary>
	public ref class ToolWindow : public System::Windows::Forms::Form
	{
	public:

		ToolWindow(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ToolWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	
	private:
		float vec1x;
		float vec1y;
		float vec1z;
		float vec2x;
		float vec2y;
		float vec2z;
		float scalar;
	
	private: System::Windows::Forms::Label^ vectorALabel;
	protected:
	private: System::Windows::Forms::Label^ vectorAXLabel;
	private: System::Windows::Forms::TextBox^ vectorAXTextbox;
	private: System::Windows::Forms::TextBox^ vectorAYTextbox;

	private: System::Windows::Forms::Label^ vectorAYLabel;
	private: System::Windows::Forms::TextBox^ vectorAZTextbox;


	private: System::Windows::Forms::Label^ vectorAZLabel;
	private: System::Windows::Forms::TextBox^ vectorBZTextbox;
	private: System::Windows::Forms::Label^ vectorBZLabel;
	private: System::Windows::Forms::TextBox^ vectorBYTextbox;
	private: System::Windows::Forms::Label^ vectorBYLabel;
	private: System::Windows::Forms::TextBox^ vectorBXTextbox;
	private: System::Windows::Forms::Label^ vectorBXLabel;
	private: System::Windows::Forms::Label^ vectorBLabel;
	private: System::Windows::Forms::Label^ scalarLabel;
	private: System::Windows::Forms::TextBox^ scalarTextbox;
	private: System::Windows::Forms::Button^ calculateButton;
	private: System::Windows::Forms::Label^ addOutput;
	private: System::Windows::Forms::Label^ subOutput;
	private: System::Windows::Forms::Label^ mulOutput;
	private: System::Windows::Forms::Label^ divOutput;
	private: System::Windows::Forms::Label^ distOutput;
	private: System::Windows::Forms::Label^ crossOutput;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;








	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->vectorALabel = (gcnew System::Windows::Forms::Label());
			this->vectorAXLabel = (gcnew System::Windows::Forms::Label());
			this->vectorAXTextbox = (gcnew System::Windows::Forms::TextBox());
			this->vectorAYTextbox = (gcnew System::Windows::Forms::TextBox());
			this->vectorAYLabel = (gcnew System::Windows::Forms::Label());
			this->vectorAZTextbox = (gcnew System::Windows::Forms::TextBox());
			this->vectorAZLabel = (gcnew System::Windows::Forms::Label());
			this->vectorBZTextbox = (gcnew System::Windows::Forms::TextBox());
			this->vectorBZLabel = (gcnew System::Windows::Forms::Label());
			this->vectorBYTextbox = (gcnew System::Windows::Forms::TextBox());
			this->vectorBYLabel = (gcnew System::Windows::Forms::Label());
			this->vectorBXTextbox = (gcnew System::Windows::Forms::TextBox());
			this->vectorBXLabel = (gcnew System::Windows::Forms::Label());
			this->vectorBLabel = (gcnew System::Windows::Forms::Label());
			this->scalarLabel = (gcnew System::Windows::Forms::Label());
			this->scalarTextbox = (gcnew System::Windows::Forms::TextBox());
			this->calculateButton = (gcnew System::Windows::Forms::Button());
			this->addOutput = (gcnew System::Windows::Forms::Label());
			this->subOutput = (gcnew System::Windows::Forms::Label());
			this->mulOutput = (gcnew System::Windows::Forms::Label());
			this->divOutput = (gcnew System::Windows::Forms::Label());
			this->distOutput = (gcnew System::Windows::Forms::Label());
			this->crossOutput = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// vectorALabel
			// 
			this->vectorALabel->AutoSize = true;
			this->vectorALabel->Location = System::Drawing::Point(13, 13);
			this->vectorALabel->Name = L"vectorALabel";
			this->vectorALabel->Size = System::Drawing::Size(51, 13);
			this->vectorALabel->TabIndex = 0;
			this->vectorALabel->Text = L"Vector A:";
			// 
			// vectorAXLabel
			// 
			this->vectorAXLabel->AutoSize = true;
			this->vectorAXLabel->Location = System::Drawing::Point(13, 37);
			this->vectorAXLabel->Name = L"vectorAXLabel";
			this->vectorAXLabel->Size = System::Drawing::Size(14, 13);
			this->vectorAXLabel->TabIndex = 1;
			this->vectorAXLabel->Text = L"X";
			// 
			// vectorAXTextbox
			// 
			this->vectorAXTextbox->Location = System::Drawing::Point(33, 33);
			this->vectorAXTextbox->Name = L"vectorAXTextbox";
			this->vectorAXTextbox->Size = System::Drawing::Size(100, 20);
			this->vectorAXTextbox->TabIndex = 2;
			// 
			// vectorAYTextbox
			// 
			this->vectorAYTextbox->Location = System::Drawing::Point(171, 33);
			this->vectorAYTextbox->Name = L"vectorAYTextbox";
			this->vectorAYTextbox->Size = System::Drawing::Size(100, 20);
			this->vectorAYTextbox->TabIndex = 4;
			// 
			// vectorAYLabel
			// 
			this->vectorAYLabel->AutoSize = true;
			this->vectorAYLabel->Location = System::Drawing::Point(151, 37);
			this->vectorAYLabel->Name = L"vectorAYLabel";
			this->vectorAYLabel->Size = System::Drawing::Size(14, 13);
			this->vectorAYLabel->TabIndex = 3;
			this->vectorAYLabel->Text = L"Y";
			// 
			// vectorAZTextbox
			// 
			this->vectorAZTextbox->Location = System::Drawing::Point(315, 33);
			this->vectorAZTextbox->Name = L"vectorAZTextbox";
			this->vectorAZTextbox->Size = System::Drawing::Size(100, 20);
			this->vectorAZTextbox->TabIndex = 6;
			// 
			// vectorAZLabel
			// 
			this->vectorAZLabel->AutoSize = true;
			this->vectorAZLabel->Location = System::Drawing::Point(295, 37);
			this->vectorAZLabel->Name = L"vectorAZLabel";
			this->vectorAZLabel->Size = System::Drawing::Size(14, 13);
			this->vectorAZLabel->TabIndex = 5;
			this->vectorAZLabel->Text = L"Z";
			// 
			// vectorBZTextbox
			// 
			this->vectorBZTextbox->Location = System::Drawing::Point(315, 89);
			this->vectorBZTextbox->Name = L"vectorBZTextbox";
			this->vectorBZTextbox->Size = System::Drawing::Size(100, 20);
			this->vectorBZTextbox->TabIndex = 13;
			// 
			// vectorBZLabel
			// 
			this->vectorBZLabel->AutoSize = true;
			this->vectorBZLabel->Location = System::Drawing::Point(295, 93);
			this->vectorBZLabel->Name = L"vectorBZLabel";
			this->vectorBZLabel->Size = System::Drawing::Size(14, 13);
			this->vectorBZLabel->TabIndex = 12;
			this->vectorBZLabel->Text = L"Z";
			// 
			// vectorBYTextbox
			// 
			this->vectorBYTextbox->Location = System::Drawing::Point(171, 89);
			this->vectorBYTextbox->Name = L"vectorBYTextbox";
			this->vectorBYTextbox->Size = System::Drawing::Size(100, 20);
			this->vectorBYTextbox->TabIndex = 11;
			// 
			// vectorBYLabel
			// 
			this->vectorBYLabel->AutoSize = true;
			this->vectorBYLabel->Location = System::Drawing::Point(151, 93);
			this->vectorBYLabel->Name = L"vectorBYLabel";
			this->vectorBYLabel->Size = System::Drawing::Size(14, 13);
			this->vectorBYLabel->TabIndex = 10;
			this->vectorBYLabel->Text = L"Y";
			// 
			// vectorBXTextbox
			// 
			this->vectorBXTextbox->Location = System::Drawing::Point(33, 89);
			this->vectorBXTextbox->Name = L"vectorBXTextbox";
			this->vectorBXTextbox->Size = System::Drawing::Size(100, 20);
			this->vectorBXTextbox->TabIndex = 9;
			// 
			// vectorBXLabel
			// 
			this->vectorBXLabel->AutoSize = true;
			this->vectorBXLabel->Location = System::Drawing::Point(13, 93);
			this->vectorBXLabel->Name = L"vectorBXLabel";
			this->vectorBXLabel->Size = System::Drawing::Size(14, 13);
			this->vectorBXLabel->TabIndex = 8;
			this->vectorBXLabel->Text = L"X";
			// 
			// vectorBLabel
			// 
			this->vectorBLabel->AutoSize = true;
			this->vectorBLabel->Location = System::Drawing::Point(13, 69);
			this->vectorBLabel->Name = L"vectorBLabel";
			this->vectorBLabel->Size = System::Drawing::Size(51, 13);
			this->vectorBLabel->TabIndex = 7;
			this->vectorBLabel->Text = L"Vector B:";
			// 
			// scalarLabel
			// 
			this->scalarLabel->AutoSize = true;
			this->scalarLabel->Location = System::Drawing::Point(13, 132);
			this->scalarLabel->Name = L"scalarLabel";
			this->scalarLabel->Size = System::Drawing::Size(40, 13);
			this->scalarLabel->TabIndex = 7;
			this->scalarLabel->Text = L"Scalar:";
			// 
			// scalarTextbox
			// 
			this->scalarTextbox->Location = System::Drawing::Point(56, 129);
			this->scalarTextbox->Name = L"scalarTextbox";
			this->scalarTextbox->Size = System::Drawing::Size(100, 20);
			this->scalarTextbox->TabIndex = 9;
			// 
			// calculateButton
			// 
			this->calculateButton->Location = System::Drawing::Point(184, 181);
			this->calculateButton->Name = L"calculateButton";
			this->calculateButton->Size = System::Drawing::Size(75, 23);
			this->calculateButton->TabIndex = 14;
			this->calculateButton->Text = L"Calculate";
			this->calculateButton->UseVisualStyleBackColor = true;
			this->calculateButton->Click += gcnew System::EventHandler(this, &ToolWindow::calculateButton_Click);
			// 
			// addOutput
			// 
			this->addOutput->AutoSize = true;
			this->addOutput->Location = System::Drawing::Point(94, 218);
			this->addOutput->Name = L"addOutput";
			this->addOutput->Padding = System::Windows::Forms::Padding(0, 0, 0, 3);
			this->addOutput->Size = System::Drawing::Size(0, 16);
			this->addOutput->TabIndex = 15;
			// 
			// subOutput
			// 
			this->subOutput->AutoSize = true;
			this->subOutput->Location = System::Drawing::Point(94, 234);
			this->subOutput->Name = L"subOutput";
			this->subOutput->Padding = System::Windows::Forms::Padding(0, 0, 0, 3);
			this->subOutput->Size = System::Drawing::Size(0, 16);
			this->subOutput->TabIndex = 16;
			// 
			// mulOutput
			// 
			this->mulOutput->AutoSize = true;
			this->mulOutput->Location = System::Drawing::Point(94, 250);
			this->mulOutput->Name = L"mulOutput";
			this->mulOutput->Padding = System::Windows::Forms::Padding(0, 0, 0, 3);
			this->mulOutput->Size = System::Drawing::Size(0, 16);
			this->mulOutput->TabIndex = 16;
			// 
			// divOutput
			// 
			this->divOutput->AutoSize = true;
			this->divOutput->Location = System::Drawing::Point(94, 266);
			this->divOutput->Name = L"divOutput";
			this->divOutput->Padding = System::Windows::Forms::Padding(0, 0, 0, 3);
			this->divOutput->Size = System::Drawing::Size(0, 16);
			this->divOutput->TabIndex = 16;
			// 
			// distOutput
			// 
			this->distOutput->AutoSize = true;
			this->distOutput->Location = System::Drawing::Point(94, 282);
			this->distOutput->Name = L"distOutput";
			this->distOutput->Padding = System::Windows::Forms::Padding(0, 0, 0, 3);
			this->distOutput->Size = System::Drawing::Size(0, 16);
			this->distOutput->TabIndex = 16;
			// 
			// crossOutput
			// 
			this->crossOutput->AutoSize = true;
			this->crossOutput->Location = System::Drawing::Point(94, 298);
			this->crossOutput->Name = L"crossOutput";
			this->crossOutput->Padding = System::Windows::Forms::Padding(0, 0, 0, 3);
			this->crossOutput->Size = System::Drawing::Size(0, 16);
			this->crossOutput->TabIndex = 16;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(60, 218);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(29, 13);
			this->label1->TabIndex = 17;
			this->label1->Text = L"Add:";
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(60, 234);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(29, 13);
			this->label2->TabIndex = 18;
			this->label2->Text = L"Sub:";
			this->label2->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(62, 250);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(27, 13);
			this->label3->TabIndex = 19;
			this->label3->Text = L"Mul:";
			this->label3->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(63, 266);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(26, 13);
			this->label4->TabIndex = 20;
			this->label4->Text = L"Div:";
			this->label4->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(61, 282);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(28, 13);
			this->label5->TabIndex = 21;
			this->label5->Text = L"Dist:";
			this->label5->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(53, 298);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(36, 13);
			this->label6->TabIndex = 22;
			this->label6->Text = L"Cross:";
			this->label6->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(438, 347);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->crossOutput);
			this->Controls->Add(this->distOutput);
			this->Controls->Add(this->divOutput);
			this->Controls->Add(this->mulOutput);
			this->Controls->Add(this->subOutput);
			this->Controls->Add(this->addOutput);
			this->Controls->Add(this->calculateButton);
			this->Controls->Add(this->vectorBZTextbox);
			this->Controls->Add(this->vectorBZLabel);
			this->Controls->Add(this->vectorBYTextbox);
			this->Controls->Add(this->vectorBYLabel);
			this->Controls->Add(this->scalarTextbox);
			this->Controls->Add(this->vectorBXTextbox);
			this->Controls->Add(this->vectorBXLabel);
			this->Controls->Add(this->scalarLabel);
			this->Controls->Add(this->vectorBLabel);
			this->Controls->Add(this->vectorAZTextbox);
			this->Controls->Add(this->vectorAZLabel);
			this->Controls->Add(this->vectorAYTextbox);
			this->Controls->Add(this->vectorAYLabel);
			this->Controls->Add(this->vectorAXTextbox);
			this->Controls->Add(this->vectorAXLabel);
			this->Controls->Add(this->vectorALabel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &ToolWindow::ToolWindow_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ToolWindow_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	
private: System::Void calculateButton_Click(System::Object^ sender, System::EventArgs^ e) {
	System::Double tempVal;
	try 
	{
		
		if (System::Double::TryParse(vectorAXTextbox->Text, tempVal))
		{
			vec1x = (float)tempVal;
		}
		else
		{
			throw gcnew System::String("Vector A's x value");
		}
		

		
		if (System::Double::TryParse(vectorAYTextbox->Text, tempVal))
		{
			vec1y = (float)tempVal;
		}
		else
		{
			throw gcnew System::String("Vector A's y value");
		}
		

		if (System::Double::TryParse(vectorAZTextbox->Text, tempVal))
		{
			vec1z = (float)tempVal;
		}
		else
		{
			throw gcnew System::String("Vector A's z value");
		}

		if (System::Double::TryParse(vectorBXTextbox->Text, tempVal))
		{
			vec2x = (float)tempVal;
		}
		else
		{
			throw gcnew System::String("Vector B's x value");
		}

		if (System::Double::TryParse(vectorBYTextbox->Text, tempVal))
		{
			vec2y = (float)tempVal;
		}
		else
		{
			throw gcnew System::String("Vector B's y value");
		}

		if (System::Double::TryParse(vectorBZTextbox->Text, tempVal))
		{
			vec2z = (float)tempVal;
		}
		else
		{
			throw gcnew System::String("Vector B's z value");
		}

		if (System::Double::TryParse(scalarTextbox->Text, tempVal))
		{
			scalar = (float)tempVal;
		}
		else
		{
			throw gcnew System::String("Scalar's value");
		}	


		Vec3 vec1 = Vec3(vec1x, vec1y, vec1z);
		Vec3 vec2 = Vec3(vec2x, vec2y, vec2z);
		addOutput->Text = Vec3::Add(vec1, vec2).ToString();
		subOutput->Text = Vec3::Sub(vec1, vec2).ToString();
		mulOutput->Text = Vec3::Mul(vec1, scalar).ToString();
		divOutput->Text = Vec3::Div(vec1, scalar).ToString();
		distOutput->Text = Vec3::Dist(vec1, vec2).ToString();
		crossOutput->Text = Vec3::Cross(vec1, vec2).ToString();
	}
	catch (System::String^ errorString)
	{
		MessageBox::Show(errorString + " is not a valid number.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

}
};
}
