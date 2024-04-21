#pragma once

#include "SceneType.h"
#include <sstream>
#include <iomanip>

namespace OpenGLTechniques {

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

		static bool TranslateChecked;
		static bool RotateChecked;
		static bool ScaleChecked;

		static float Frequency;
		static float Amplitude;
		static bool WireframeRenderChecked;
		static bool TintBlueChecked;

		static bool ResetLightPosition;
		static bool ResetTransform;

		ToolWindow(void)
		{
			InitializeComponent();

			ResetLightPosition = false;
			ResetTransform = false;
			SelectedSceneType = MOVE_LIGHT;
			SpecularStrength = 4;
			SpecularColorR = 1.0f;
			SpecularColorG = 1.0f;
			SpecularColorB = 1.0f;

			Frequency = 4.0f;
			Amplitude = 0.01f;
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
	protected:

	private: System::Windows::Forms::RadioButton^ radioTransform;
	private: System::Windows::Forms::RadioButton^ radioWaterScene;
	private: System::Windows::Forms::RadioButton^ radioSpaceScene;
	private: System::Windows::Forms::Button^ buttonResetLightPosition;
	private: System::Windows::Forms::TrackBar^ trackBarSpecularStrength;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TrackBar^ trackBarSpecularColorR;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ labelSpecularStrength;


	private: System::Windows::Forms::Label^ R;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ labelSpecularColorR;
	private: System::Windows::Forms::TrackBar^ trackBarSpecularColorB;
	private: System::Windows::Forms::TrackBar^ trackBarSpecularColorG;
	private: System::Windows::Forms::Label^ labelSpecularColorB;
	private: System::Windows::Forms::Label^ labelSpecularColorG;
	private: System::Windows::Forms::Button^ buttonResetTransform;
	private: System::Windows::Forms::CheckBox^ checkBoxTranslate;
	private: System::Windows::Forms::CheckBox^ checkBoxRotate;
	private: System::Windows::Forms::CheckBox^ checkBoxScale;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TrackBar^ trackBarFrequency;
	private: System::Windows::Forms::Label^ labelFrequency;
	private: System::Windows::Forms::Label^ labelAmplitude;
	private: System::Windows::Forms::TrackBar^ trackBarAmplitude;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::CheckBox^ checkBoxWireframeRender;
	private: System::Windows::Forms::CheckBox^ checkBoxTintBlue;
	protected:

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
			this->radioTransform = (gcnew System::Windows::Forms::RadioButton());
			this->radioWaterScene = (gcnew System::Windows::Forms::RadioButton());
			this->radioSpaceScene = (gcnew System::Windows::Forms::RadioButton());
			this->buttonResetLightPosition = (gcnew System::Windows::Forms::Button());
			this->trackBarSpecularStrength = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->trackBarSpecularColorR = (gcnew System::Windows::Forms::TrackBar());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->labelSpecularStrength = (gcnew System::Windows::Forms::Label());
			this->R = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->labelSpecularColorR = (gcnew System::Windows::Forms::Label());
			this->trackBarSpecularColorB = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarSpecularColorG = (gcnew System::Windows::Forms::TrackBar());
			this->labelSpecularColorB = (gcnew System::Windows::Forms::Label());
			this->labelSpecularColorG = (gcnew System::Windows::Forms::Label());
			this->buttonResetTransform = (gcnew System::Windows::Forms::Button());
			this->checkBoxTranslate = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxRotate = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxScale = (gcnew System::Windows::Forms::CheckBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->trackBarFrequency = (gcnew System::Windows::Forms::TrackBar());
			this->labelFrequency = (gcnew System::Windows::Forms::Label());
			this->labelAmplitude = (gcnew System::Windows::Forms::Label());
			this->trackBarAmplitude = (gcnew System::Windows::Forms::TrackBar());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->checkBoxWireframeRender = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxTintBlue = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularStrength))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorB))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorG))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarFrequency))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarAmplitude))->BeginInit();
			this->SuspendLayout();
			// 
			// radioMoveLight
			// 
			this->radioMoveLight->AutoSize = true;
			this->radioMoveLight->Checked = true;
			this->radioMoveLight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioMoveLight->Location = System::Drawing::Point(13, 13);
			this->radioMoveLight->Name = L"radioMoveLight";
			this->radioMoveLight->Size = System::Drawing::Size(88, 17);
			this->radioMoveLight->TabIndex = 0;
			this->radioMoveLight->TabStop = true;
			this->radioMoveLight->Text = L"Move Light";
			this->radioMoveLight->UseVisualStyleBackColor = true;
			this->radioMoveLight->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioMoveLight_CheckedChanged);
			// 
			// radioTransform
			// 
			this->radioTransform->AutoSize = true;
			this->radioTransform->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioTransform->Location = System::Drawing::Point(13, 266);
			this->radioTransform->Name = L"radioTransform";
			this->radioTransform->Size = System::Drawing::Size(81, 17);
			this->radioTransform->TabIndex = 1;
			this->radioTransform->Text = L"Transform";
			this->radioTransform->UseVisualStyleBackColor = true;
			this->radioTransform->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioTransform_CheckedChanged);
			// 
			// radioWaterScene
			// 
			this->radioWaterScene->AutoSize = true;
			this->radioWaterScene->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioWaterScene->Location = System::Drawing::Point(13, 408);
			this->radioWaterScene->Name = L"radioWaterScene";
			this->radioWaterScene->Size = System::Drawing::Size(99, 17);
			this->radioWaterScene->TabIndex = 2;
			this->radioWaterScene->Text = L"Water Scene";
			this->radioWaterScene->UseVisualStyleBackColor = true;
			this->radioWaterScene->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioWaterScene_CheckedChanged);
			// 
			// radioSpaceScene
			// 
			this->radioSpaceScene->AutoSize = true;
			this->radioSpaceScene->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioSpaceScene->Location = System::Drawing::Point(13, 604);
			this->radioSpaceScene->Name = L"radioSpaceScene";
			this->radioSpaceScene->Size = System::Drawing::Size(101, 17);
			this->radioSpaceScene->TabIndex = 3;
			this->radioSpaceScene->Text = L"Space Scene";
			this->radioSpaceScene->UseVisualStyleBackColor = true;
			this->radioSpaceScene->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioSpaceScene_CheckedChanged);
			// 
			// buttonResetLightPosition
			// 
			this->buttonResetLightPosition->Location = System::Drawing::Point(36, 37);
			this->buttonResetLightPosition->Name = L"buttonResetLightPosition";
			this->buttonResetLightPosition->Size = System::Drawing::Size(130, 23);
			this->buttonResetLightPosition->TabIndex = 4;
			this->buttonResetLightPosition->Text = L"Reset Light Position";
			this->buttonResetLightPosition->UseVisualStyleBackColor = true;
			this->buttonResetLightPosition->Click += gcnew System::EventHandler(this, &ToolWindow::buttonResetLightPosition_Click);
			// 
			// trackBarSpecularStrength
			// 
			this->trackBarSpecularStrength->LargeChange = 8;
			this->trackBarSpecularStrength->Location = System::Drawing::Point(134, 66);
			this->trackBarSpecularStrength->Maximum = 256;
			this->trackBarSpecularStrength->Minimum = 1;
			this->trackBarSpecularStrength->Name = L"trackBarSpecularStrength";
			this->trackBarSpecularStrength->Size = System::Drawing::Size(267, 45);
			this->trackBarSpecularStrength->TabIndex = 5;
			this->trackBarSpecularStrength->TickFrequency = 2;
			this->trackBarSpecularStrength->Value = 4;
			this->trackBarSpecularStrength->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarSpecularStrength_Scroll);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(33, 77);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(92, 13);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Specular Strength";
			// 
			// trackBarSpecularColorR
			// 
			this->trackBarSpecularColorR->LargeChange = 50;
			this->trackBarSpecularColorR->Location = System::Drawing::Point(134, 117);
			this->trackBarSpecularColorR->Maximum = 300;
			this->trackBarSpecularColorR->Name = L"trackBarSpecularColorR";
			this->trackBarSpecularColorR->Size = System::Drawing::Size(267, 45);
			this->trackBarSpecularColorR->TabIndex = 7;
			this->trackBarSpecularColorR->Value = 100;
			this->trackBarSpecularColorR->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarSpecularColorR_Scroll);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(33, 117);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(76, 13);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Specular Color";
			// 
			// labelSpecularStrength
			// 
			this->labelSpecularStrength->AutoSize = true;
			this->labelSpecularStrength->Location = System::Drawing::Point(422, 77);
			this->labelSpecularStrength->Name = L"labelSpecularStrength";
			this->labelSpecularStrength->Size = System::Drawing::Size(13, 13);
			this->labelSpecularStrength->TabIndex = 9;
			this->labelSpecularStrength->Text = L"4";
			// 
			// R
			// 
			this->R->AutoSize = true;
			this->R->Location = System::Drawing::Point(118, 122);
			this->R->Name = L"R";
			this->R->Size = System::Drawing::Size(15, 13);
			this->R->TabIndex = 12;
			this->R->Text = L"R";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(118, 172);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(15, 13);
			this->label3->TabIndex = 13;
			this->label3->Text = L"G";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(119, 223);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(14, 13);
			this->label4->TabIndex = 14;
			this->label4->Text = L"B";
			// 
			// labelSpecularColorR
			// 
			this->labelSpecularColorR->AutoSize = true;
			this->labelSpecularColorR->Location = System::Drawing::Point(422, 122);
			this->labelSpecularColorR->Name = L"labelSpecularColorR";
			this->labelSpecularColorR->Size = System::Drawing::Size(28, 13);
			this->labelSpecularColorR->TabIndex = 15;
			this->labelSpecularColorR->Text = L"1.00";
			// 
			// trackBarSpecularColorB
			// 
			this->trackBarSpecularColorB->LargeChange = 50;
			this->trackBarSpecularColorB->Location = System::Drawing::Point(134, 201);
			this->trackBarSpecularColorB->Maximum = 300;
			this->trackBarSpecularColorB->Name = L"trackBarSpecularColorB";
			this->trackBarSpecularColorB->Size = System::Drawing::Size(267, 45);
			this->trackBarSpecularColorB->TabIndex = 16;
			this->trackBarSpecularColorB->Value = 100;
			this->trackBarSpecularColorB->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarSpecularColorB_Scroll);
			// 
			// trackBarSpecularColorG
			// 
			this->trackBarSpecularColorG->LargeChange = 50;
			this->trackBarSpecularColorG->Location = System::Drawing::Point(134, 159);
			this->trackBarSpecularColorG->Maximum = 300;
			this->trackBarSpecularColorG->Name = L"trackBarSpecularColorG";
			this->trackBarSpecularColorG->Size = System::Drawing::Size(267, 45);
			this->trackBarSpecularColorG->TabIndex = 17;
			this->trackBarSpecularColorG->Value = 100;
			this->trackBarSpecularColorG->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarSpecularColorG_Scroll);
			// 
			// labelSpecularColorB
			// 
			this->labelSpecularColorB->AutoSize = true;
			this->labelSpecularColorB->Location = System::Drawing::Point(422, 211);
			this->labelSpecularColorB->Name = L"labelSpecularColorB";
			this->labelSpecularColorB->Size = System::Drawing::Size(28, 13);
			this->labelSpecularColorB->TabIndex = 18;
			this->labelSpecularColorB->Text = L"1.00";
			// 
			// labelSpecularColorG
			// 
			this->labelSpecularColorG->AutoSize = true;
			this->labelSpecularColorG->Location = System::Drawing::Point(422, 172);
			this->labelSpecularColorG->Name = L"labelSpecularColorG";
			this->labelSpecularColorG->Size = System::Drawing::Size(28, 13);
			this->labelSpecularColorG->TabIndex = 19;
			this->labelSpecularColorG->Text = L"1.00";
			// 
			// buttonResetTransform
			// 
			this->buttonResetTransform->Location = System::Drawing::Point(36, 289);
			this->buttonResetTransform->Name = L"buttonResetTransform";
			this->buttonResetTransform->Size = System::Drawing::Size(130, 23);
			this->buttonResetTransform->TabIndex = 20;
			this->buttonResetTransform->Text = L"Reset Transform";
			this->buttonResetTransform->UseVisualStyleBackColor = true;
			this->buttonResetTransform->Click += gcnew System::EventHandler(this, &ToolWindow::buttonResetTransform_Click);
			// 
			// checkBoxTranslate
			// 
			this->checkBoxTranslate->AutoSize = true;
			this->checkBoxTranslate->Location = System::Drawing::Point(36, 319);
			this->checkBoxTranslate->Name = L"checkBoxTranslate";
			this->checkBoxTranslate->Size = System::Drawing::Size(70, 17);
			this->checkBoxTranslate->TabIndex = 21;
			this->checkBoxTranslate->Text = L"Translate";
			this->checkBoxTranslate->UseVisualStyleBackColor = true;
			this->checkBoxTranslate->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxTranslate_CheckedChanged);
			// 
			// checkBoxRotate
			// 
			this->checkBoxRotate->AutoSize = true;
			this->checkBoxRotate->Location = System::Drawing::Point(36, 343);
			this->checkBoxRotate->Name = L"checkBoxRotate";
			this->checkBoxRotate->Size = System::Drawing::Size(58, 17);
			this->checkBoxRotate->TabIndex = 22;
			this->checkBoxRotate->Text = L"Rotate";
			this->checkBoxRotate->UseVisualStyleBackColor = true;
			this->checkBoxRotate->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxRotate_CheckedChanged);
			// 
			// checkBoxScale
			// 
			this->checkBoxScale->AutoSize = true;
			this->checkBoxScale->Location = System::Drawing::Point(36, 367);
			this->checkBoxScale->Name = L"checkBoxScale";
			this->checkBoxScale->Size = System::Drawing::Size(53, 17);
			this->checkBoxScale->TabIndex = 23;
			this->checkBoxScale->Text = L"Scale";
			this->checkBoxScale->UseVisualStyleBackColor = true;
			this->checkBoxScale->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxScale_CheckedChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(68, 442);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(57, 13);
			this->label5->TabIndex = 24;
			this->label5->Text = L"Frequency";
			// 
			// trackBarFrequency
			// 
			this->trackBarFrequency->LargeChange = 100;
			this->trackBarFrequency->Location = System::Drawing::Point(134, 433);
			this->trackBarFrequency->Maximum = 400;
			this->trackBarFrequency->Name = L"trackBarFrequency";
			this->trackBarFrequency->Size = System::Drawing::Size(267, 45);
			this->trackBarFrequency->TabIndex = 25;
			this->trackBarFrequency->Value = 400;
			this->trackBarFrequency->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarFrequency_Scroll);
			// 
			// labelFrequency
			// 
			this->labelFrequency->AutoSize = true;
			this->labelFrequency->Location = System::Drawing::Point(422, 442);
			this->labelFrequency->Name = L"labelFrequency";
			this->labelFrequency->Size = System::Drawing::Size(28, 13);
			this->labelFrequency->TabIndex = 26;
			this->labelFrequency->Text = L"4.00";
			// 
			// labelAmplitude
			// 
			this->labelAmplitude->AutoSize = true;
			this->labelAmplitude->Location = System::Drawing::Point(422, 493);
			this->labelAmplitude->Name = L"labelAmplitude";
			this->labelAmplitude->Size = System::Drawing::Size(28, 13);
			this->labelAmplitude->TabIndex = 29;
			this->labelAmplitude->Text = L"0.01";
			// 
			// trackBarAmplitude
			// 
			this->trackBarAmplitude->LargeChange = 10;
			this->trackBarAmplitude->Location = System::Drawing::Point(134, 484);
			this->trackBarAmplitude->Maximum = 100;
			this->trackBarAmplitude->Minimum = 1;
			this->trackBarAmplitude->Name = L"trackBarAmplitude";
			this->trackBarAmplitude->Size = System::Drawing::Size(267, 45);
			this->trackBarAmplitude->TabIndex = 28;
			this->trackBarAmplitude->Value = 1;
			this->trackBarAmplitude->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarAmplitude_Scroll);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(68, 493);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(53, 13);
			this->label7->TabIndex = 27;
			this->label7->Text = L"Amplitude";
			// 
			// checkBoxWireframeRender
			// 
			this->checkBoxWireframeRender->AutoSize = true;
			this->checkBoxWireframeRender->Location = System::Drawing::Point(71, 534);
			this->checkBoxWireframeRender->Name = L"checkBoxWireframeRender";
			this->checkBoxWireframeRender->Size = System::Drawing::Size(112, 17);
			this->checkBoxWireframeRender->TabIndex = 30;
			this->checkBoxWireframeRender->Text = L"Wireframe Render";
			this->checkBoxWireframeRender->UseVisualStyleBackColor = true;
			this->checkBoxWireframeRender->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxWireframeRender_CheckedChanged);
			// 
			// checkBoxTintBlue
			// 
			this->checkBoxTintBlue->AutoSize = true;
			this->checkBoxTintBlue->Location = System::Drawing::Point(71, 558);
			this->checkBoxTintBlue->Name = L"checkBoxTintBlue";
			this->checkBoxTintBlue->Size = System::Drawing::Size(68, 17);
			this->checkBoxTintBlue->TabIndex = 31;
			this->checkBoxTintBlue->Text = L"Tint Blue";
			this->checkBoxTintBlue->UseVisualStyleBackColor = true;
			this->checkBoxTintBlue->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxTintBlue_CheckedChanged);
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(492, 638);
			this->Controls->Add(this->checkBoxTintBlue);
			this->Controls->Add(this->checkBoxWireframeRender);
			this->Controls->Add(this->labelAmplitude);
			this->Controls->Add(this->trackBarAmplitude);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->labelFrequency);
			this->Controls->Add(this->trackBarFrequency);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->checkBoxScale);
			this->Controls->Add(this->checkBoxRotate);
			this->Controls->Add(this->checkBoxTranslate);
			this->Controls->Add(this->buttonResetTransform);
			this->Controls->Add(this->labelSpecularColorG);
			this->Controls->Add(this->labelSpecularColorB);
			this->Controls->Add(this->trackBarSpecularColorG);
			this->Controls->Add(this->trackBarSpecularColorB);
			this->Controls->Add(this->labelSpecularColorR);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->R);
			this->Controls->Add(this->labelSpecularStrength);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->trackBarSpecularColorR);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->trackBarSpecularStrength);
			this->Controls->Add(this->buttonResetLightPosition);
			this->Controls->Add(this->radioSpaceScene);
			this->Controls->Add(this->radioWaterScene);
			this->Controls->Add(this->radioTransform);
			this->Controls->Add(this->radioMoveLight);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &ToolWindow::ToolWindow_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularStrength))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorR))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorB))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorG))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarFrequency))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarAmplitude))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


		private: SceneType GetSelectedRadio()
		{
			if (this->radioMoveLight->Checked) {
				return MOVE_LIGHT;
			}
			else if (this->radioTransform->Checked) {
				return TRANSFORM;
			}
			else if (this->radioWaterScene->Checked) {
				return WATER_SCENE;
			}
			else {
				return SPACE_SCENE;
			}
		}

		private: System::Void SetSelectedRadio(SceneType _scene)
		{
			SelectedSceneType = _scene;
		}

		private: System::Void ToolWindow_Load(System::Object^ sender, System::EventArgs^ e) {
		}

		private: System::Void radioMoveLight_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			SetSelectedRadio(MOVE_LIGHT);
		}
		private: System::Void radioTransform_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			SetSelectedRadio(TRANSFORM);
		}
		private: System::Void radioWaterScene_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			SetSelectedRadio(WATER_SCENE);
		}
		private: System::Void radioSpaceScene_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			SetSelectedRadio(SPACE_SCENE);
		}

		private: System::Void trackBarSpecularStrength_Scroll(System::Object^ sender, System::EventArgs^ e) {
			SpecularStrength = trackBarSpecularStrength->Value;
			labelSpecularStrength->Text = System::Convert::ToString(SpecularStrength);
		}
		private: System::Void trackBarSpecularColorR_Scroll(System::Object^ sender, System::EventArgs^ e) {
			float val = trackBarSpecularColorR->Value / 100.0f;
			SpecularColorR = val;
			labelSpecularColorR->Text = getFormattedString(val);
		}
		private: System::Void trackBarSpecularColorG_Scroll(System::Object^ sender, System::EventArgs^ e) {
			float val = trackBarSpecularColorG->Value / 100.0f;
			SpecularColorG = val;
			labelSpecularColorG->Text = getFormattedString(val);
		}
		private: System::Void trackBarSpecularColorB_Scroll(System::Object^ sender, System::EventArgs^ e) {
			float val = trackBarSpecularColorB->Value / 100.0f;
			SpecularColorB = val;
			labelSpecularColorB->Text = getFormattedString(val);
		}

		private: System::Void trackBarFrequency_Scroll(System::Object^ sender, System::EventArgs^ e) {
			float val = trackBarFrequency->Value / 100.0f;
			Frequency = val;
			labelFrequency->Text = getFormattedString(val);
		}
		private: System::Void trackBarAmplitude_Scroll(System::Object^ sender, System::EventArgs^ e) {
			float val = trackBarAmplitude->Value / 100.0f;
			Amplitude = val;
			labelAmplitude->Text = getFormattedString(val);
		}
		private: System::Void checkBoxTranslate_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			TranslateChecked = checkBoxTranslate->Checked;
		}
		private: System::Void checkBoxRotate_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			RotateChecked = checkBoxRotate->Checked;

		}
		private: System::Void checkBoxScale_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			ScaleChecked = checkBoxScale->Checked;
		}
		private: System::Void checkBoxWireframeRender_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			WireframeRenderChecked = checkBoxWireframeRender->Checked;
		}
		private: System::Void checkBoxTintBlue_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			TintBlueChecked = checkBoxTintBlue->Checked;
		}
		private: System::Void buttonResetLightPosition_Click(System::Object^ sender, System::EventArgs^ e) {
			ResetLightPosition = true;
		}
		private: System::Void buttonResetTransform_Click(System::Object^ sender, System::EventArgs^ e) {
			ResetTransform = true;
		}
	   private: System::String^ getFormattedString(float val) {
		   std::stringstream stream;
		   stream << std::fixed << std::setprecision(2) << val;

		   return gcnew String(stream.str().c_str());
	   }
	};
}
