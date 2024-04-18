#pragma once

#include "SceneType.h"

namespace MultiRenders {

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

		static SceneType SelectedSceneType;

		static int SpecularStrength;
		static float SpecularColorR;
		static float SpecularColorG;
		static float SpecularColorB;

		static bool ResetLightPosition;
		static bool ResetTeapotPosition;

		ToolWindow(void)
		{
			InitializeComponent();
			
			ResetLightPosition = false;
			ResetTeapotPosition = false;
			SelectedSceneType = MOVE_LIGHT;
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
	private: System::Windows::Forms::RadioButton^ radioMoveLight;
	private: System::Windows::Forms::RadioButton^ radioColorByPosition;
	private: System::Windows::Forms::RadioButton^ radioMoveCubesToSphere;
	protected:


	private: System::Windows::Forms::Button^ buttonResetLightPosition;
	private: System::Windows::Forms::Button^ buttonResetTeapotPosition;


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ labelSpecularStrength;
	private: System::Windows::Forms::Label^ labelSpecularColorR;
	private: System::Windows::Forms::Label^ labelSpecularColorG;
	private: System::Windows::Forms::Label^ labelSpecularColorB;
	private: System::Windows::Forms::TrackBar^ trackBarSpecularStrength;
	private: System::Windows::Forms::TrackBar^ trackBarSpecularColorR;
	private: System::Windows::Forms::TrackBar^ trackBarSpecularColorG;
	private: System::Windows::Forms::TrackBar^ trackBarSpecularColorB;











	protected:

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
			this->radioMoveLight = (gcnew System::Windows::Forms::RadioButton());
			this->radioColorByPosition = (gcnew System::Windows::Forms::RadioButton());
			this->radioMoveCubesToSphere = (gcnew System::Windows::Forms::RadioButton());
			this->buttonResetLightPosition = (gcnew System::Windows::Forms::Button());
			this->buttonResetTeapotPosition = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->labelSpecularStrength = (gcnew System::Windows::Forms::Label());
			this->labelSpecularColorR = (gcnew System::Windows::Forms::Label());
			this->labelSpecularColorG = (gcnew System::Windows::Forms::Label());
			this->labelSpecularColorB = (gcnew System::Windows::Forms::Label());
			this->trackBarSpecularStrength = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarSpecularColorR = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarSpecularColorG = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarSpecularColorB = (gcnew System::Windows::Forms::TrackBar());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularStrength))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorG))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorB))->BeginInit();
			this->SuspendLayout();
			// 
			// radioMoveLight
			// 
			this->radioMoveLight->AutoSize = true;
			this->radioMoveLight->Checked = true;
			this->radioMoveLight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioMoveLight->Location = System::Drawing::Point(12, 12);
			this->radioMoveLight->Name = L"radioMoveLight";
			this->radioMoveLight->Size = System::Drawing::Size(88, 17);
			this->radioMoveLight->TabIndex = 0;
			this->radioMoveLight->TabStop = true;
			this->radioMoveLight->Text = L"Move Light";
			this->radioMoveLight->UseVisualStyleBackColor = true;
			this->radioMoveLight->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioMoveLight_CheckedChanged);
			// 
			// radioColorByPosition
			// 
			this->radioColorByPosition->AutoSize = true;
			this->radioColorByPosition->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->radioColorByPosition->Location = System::Drawing::Point(12, 274);
			this->radioColorByPosition->Name = L"radioColorByPosition";
			this->radioColorByPosition->Size = System::Drawing::Size(121, 17);
			this->radioColorByPosition->TabIndex = 0;
			this->radioColorByPosition->Text = L"Color By Position";
			this->radioColorByPosition->UseVisualStyleBackColor = true;
			this->radioColorByPosition->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioColorByPosition_CheckedChanged);
			// 
			// radioMoveCubesToSphere
			// 
			this->radioMoveCubesToSphere->AutoSize = true;
			this->radioMoveCubesToSphere->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->radioMoveCubesToSphere->Location = System::Drawing::Point(12, 345);
			this->radioMoveCubesToSphere->Name = L"radioMoveCubesToSphere";
			this->radioMoveCubesToSphere->Size = System::Drawing::Size(158, 17);
			this->radioMoveCubesToSphere->TabIndex = 0;
			this->radioMoveCubesToSphere->Text = L"Move Cubes To Sphere";
			this->radioMoveCubesToSphere->UseVisualStyleBackColor = true;
			this->radioMoveCubesToSphere->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioMoveCubesToSphere_CheckedChanged);
			// 
			// buttonResetLightPosition
			// 
			this->buttonResetLightPosition->Location = System::Drawing::Point(30, 35);
			this->buttonResetLightPosition->Name = L"buttonResetLightPosition";
			this->buttonResetLightPosition->Size = System::Drawing::Size(118, 23);
			this->buttonResetLightPosition->TabIndex = 1;
			this->buttonResetLightPosition->Text = L"Reset Light Position";
			this->buttonResetLightPosition->UseVisualStyleBackColor = true;
			this->buttonResetLightPosition->Click += gcnew System::EventHandler(this, &ToolWindow::buttonResetLightPosition_Click);
			// 
			// buttonResetTeapotPosition
			// 
			this->buttonResetTeapotPosition->Location = System::Drawing::Point(30, 297);
			this->buttonResetTeapotPosition->Name = L"buttonResetTeapotPosition";
			this->buttonResetTeapotPosition->Size = System::Drawing::Size(128, 23);
			this->buttonResetTeapotPosition->TabIndex = 1;
			this->buttonResetTeapotPosition->Text = L"Reset Teapot Position";
			this->buttonResetTeapotPosition->UseVisualStyleBackColor = true;
			this->buttonResetTeapotPosition->Click += gcnew System::EventHandler(this, &ToolWindow::buttonResetTeapotPosition_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(49, 75);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(92, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Specular Strength";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(65, 120);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(76, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Specular Color";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(161, 120);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(15, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"R";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(161, 171);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(15, 13);
			this->label4->TabIndex = 2;
			this->label4->Text = L"G";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(162, 222);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(14, 13);
			this->label5->TabIndex = 2;
			this->label5->Text = L"B";
			// 
			// labelSpecularStrength
			// 
			this->labelSpecularStrength->AutoSize = true;
			this->labelSpecularStrength->Location = System::Drawing::Point(418, 75);
			this->labelSpecularStrength->Name = L"labelSpecularStrength";
			this->labelSpecularStrength->Size = System::Drawing::Size(13, 13);
			this->labelSpecularStrength->TabIndex = 2;
			this->labelSpecularStrength->Text = L"4";
			// 
			// labelSpecularColorR
			// 
			this->labelSpecularColorR->AutoSize = true;
			this->labelSpecularColorR->Location = System::Drawing::Point(418, 120);
			this->labelSpecularColorR->Name = L"labelSpecularColorR";
			this->labelSpecularColorR->Size = System::Drawing::Size(28, 13);
			this->labelSpecularColorR->TabIndex = 2;
			this->labelSpecularColorR->Text = L"1.00";
			// 
			// labelSpecularColorG
			// 
			this->labelSpecularColorG->AutoSize = true;
			this->labelSpecularColorG->Location = System::Drawing::Point(418, 171);
			this->labelSpecularColorG->Name = L"labelSpecularColorG";
			this->labelSpecularColorG->Size = System::Drawing::Size(28, 13);
			this->labelSpecularColorG->TabIndex = 2;
			this->labelSpecularColorG->Text = L"1.00";
			// 
			// labelSpecularColorB
			// 
			this->labelSpecularColorB->AutoSize = true;
			this->labelSpecularColorB->Location = System::Drawing::Point(418, 222);
			this->labelSpecularColorB->Name = L"labelSpecularColorB";
			this->labelSpecularColorB->Size = System::Drawing::Size(28, 13);
			this->labelSpecularColorB->TabIndex = 2;
			this->labelSpecularColorB->Text = L"1.00";
			// 
			// trackBarSpecularStrength
			// 
			this->trackBarSpecularStrength->Location = System::Drawing::Point(179, 69);
			this->trackBarSpecularStrength->Maximum = 128;
			this->trackBarSpecularStrength->Minimum = 1;
			this->trackBarSpecularStrength->Name = L"trackBarSpecularStrength";
			this->trackBarSpecularStrength->Size = System::Drawing::Size(230, 45);
			this->trackBarSpecularStrength->TabIndex = 3;
			this->trackBarSpecularStrength->Value = 4;
			this->trackBarSpecularStrength->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarSpecularStrength_Scroll);
			// 
			// trackBarSpecularColorR
			// 
			this->trackBarSpecularColorR->Location = System::Drawing::Point(182, 120);
			this->trackBarSpecularColorR->Maximum = 300;
			this->trackBarSpecularColorR->Name = L"trackBarSpecularColorR";
			this->trackBarSpecularColorR->Size = System::Drawing::Size(230, 45);
			this->trackBarSpecularColorR->TabIndex = 3;
			this->trackBarSpecularColorR->Value = 100;
			this->trackBarSpecularColorR->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarSpecularColorR_Scroll);
			// 
			// trackBarSpecularColorG
			// 
			this->trackBarSpecularColorG->Location = System::Drawing::Point(182, 171);
			this->trackBarSpecularColorG->Maximum = 300;
			this->trackBarSpecularColorG->Name = L"trackBarSpecularColorG";
			this->trackBarSpecularColorG->Size = System::Drawing::Size(230, 45);
			this->trackBarSpecularColorG->TabIndex = 3;
			this->trackBarSpecularColorG->Value = 100;
			this->trackBarSpecularColorG->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarSpecularColorG_Scroll);
			// 
			// trackBarSpecularColorB
			// 
			this->trackBarSpecularColorB->Location = System::Drawing::Point(182, 222);
			this->trackBarSpecularColorB->Maximum = 300;
			this->trackBarSpecularColorB->Name = L"trackBarSpecularColorB";
			this->trackBarSpecularColorB->Size = System::Drawing::Size(230, 45);
			this->trackBarSpecularColorB->TabIndex = 3;
			this->trackBarSpecularColorB->Value = 100;
			this->trackBarSpecularColorB->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarSpecularColorB_Scroll);
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(506, 384);
			this->Controls->Add(this->trackBarSpecularColorB);
			this->Controls->Add(this->trackBarSpecularColorG);
			this->Controls->Add(this->trackBarSpecularColorR);
			this->Controls->Add(this->trackBarSpecularStrength);
			this->Controls->Add(this->labelSpecularColorB);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->labelSpecularColorG);
			this->Controls->Add(this->labelSpecularColorR);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->labelSpecularStrength);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->buttonResetTeapotPosition);
			this->Controls->Add(this->buttonResetLightPosition);
			this->Controls->Add(this->radioMoveCubesToSphere);
			this->Controls->Add(this->radioColorByPosition);
			this->Controls->Add(this->radioMoveLight);
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularStrength))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorR))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorG))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorB))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: System::Void radioMoveLight_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			SelectedSceneType = MOVE_LIGHT;
		}
		private: System::Void radioColorByPosition_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			SelectedSceneType = COLOR;
		}
		private: System::Void radioMoveCubesToSphere_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			SelectedSceneType = CUBES;
		}
		private: System::Void trackBarSpecularStrength_Scroll(System::Object^ sender, System::EventArgs^ e) {
			SpecularStrength = trackBarSpecularStrength->Value;
			labelSpecularStrength->Text = System::Convert::ToString(SpecularStrength);
		}
		private: System::Void trackBarSpecularColorR_Scroll(System::Object^ sender, System::EventArgs^ e) {
			float val = trackBarSpecularColorR->Value / 100.0f;
			SpecularColorR = val;
			labelSpecularColorR->Text = System::Convert::ToString(val);
		}
		private: System::Void trackBarSpecularColorG_Scroll(System::Object^ sender, System::EventArgs^ e) {
			float val = trackBarSpecularColorG->Value / 100.0f;
			SpecularColorG = val;
			labelSpecularColorG->Text = System::Convert::ToString(val);
		}
		private: System::Void trackBarSpecularColorB_Scroll(System::Object^ sender, System::EventArgs^ e) {
			float val = trackBarSpecularColorB->Value / 100.0f;
			SpecularColorB = val;
			labelSpecularColorB->Text = System::Convert::ToString(val);
		}
		private: System::Void buttonResetLightPosition_Click(System::Object^ sender, System::EventArgs^ e) {
			ResetLightPosition = true;
		}
		private: System::Void buttonResetTeapotPosition_Click(System::Object^ sender, System::EventArgs^ e) {
			ResetTeapotPosition = true;
		}
	};
}
