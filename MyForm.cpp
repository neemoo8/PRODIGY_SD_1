#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

static void StartApplication() {
	convtemp1::MyForm form;
	Application::Run(% form);
}

int main(array<String^>^ args) {
	StartApplication();
	return 0;
}

double ConvertToCelsius(double temperature, String^ unit) {
	if (unit == "Fahrenheit") {
		return (temperature - 32) * 5 / 9;
	}
	else if (unit == "Kelvin") {
		return temperature - 273.15;
	}
	return temperature; // Already Celsius
}

double ConvertToFahrenheit(double temperature, String^ unit) {
	if (unit == "Celsius") {
		return (temperature * 9 / 5) + 32;
	}
	else if (unit == "Kelvin") {
		return (temperature - 273.15) * 9 / 5 + 32;
	}
	return temperature; // Already Fahrenheit
}

double ConvertToKelvin(double temperature, String^ unit) {
	if (unit == "Celsius") {
		return temperature + 273.15;
	}
	else if (unit == "Fahrenheit") {
		return (temperature - 32) * 5 / 9 + 273.15;
	}
	return temperature; // Already Kelvin
}

System::Void convtemp1::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {
	// Get the text from textBox1
	System::String^ text = textBox1->Text;

	// Check if input is empty
	if (String::IsNullOrWhiteSpace(text)) {
		MessageBox::Show("Input cannot be empty.", "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	// Convert the text to a double
	double temperature;
	try {
		temperature = System::Convert::ToDouble(text);
	}
	catch (System::FormatException^ ex) {
		MessageBox::Show("Please enter a valid number.", "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;  // Exit the function if the conversion fails
	}

	// Check which RadioButton is selected
	String^ unit;
	if (radioButton1->Checked) {
		unit = "Kelvin";
	}
	else if (radioButton2->Checked) {
		unit = "Celsius";
	}
	else if (radioButton3->Checked) {
		unit = "Fahrenheit";
	}

	// Variables to store the converted values
	double Fahrenheit, Celsius, Kelvin;

	// Perform the temperature conversion based on the selected unit
	if (unit == "Celsius") {
		if (temperature < -273.15) {
			MessageBox::Show("Temperature cannot be lower than absolute zero (-273.15°C).", "Conversion Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else {
			Fahrenheit = ConvertToFahrenheit(temperature, "Celsius");
			Kelvin = ConvertToKelvin(temperature, "Celsius");

			// Create and show MyForm1 with results in textBox1
			MyForm1^ resultWindow = gcnew MyForm1();
			resultWindow->textBox1->Text = "Temperature in Fahrenheit: " + Fahrenheit.ToString("F2") + "\r\n" +
				"Temperature in Kelvin: " + Kelvin.ToString("F2");
			resultWindow->ShowDialog();
		}
	}
	else if (unit == "Fahrenheit") {
		if (temperature < -459.67) {
			MessageBox::Show("Temperature cannot be lower than absolute zero (-459.67°F).", "Conversion Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else {
			Celsius = ConvertToCelsius(temperature, "Fahrenheit");
			Kelvin = ConvertToKelvin(Celsius, "Celsius");

			// Create and show MyForm1 with results in textBox1
			MyForm1^ resultWindow = gcnew MyForm1();
			resultWindow->textBox1->Text = "Temperature in Celsius: " + Celsius.ToString("F2") + "\r\n" +
				"Temperature in Kelvin: " + Kelvin.ToString("F2");
			resultWindow->ShowDialog();
		}
	}
	else if (unit == "Kelvin") {
		if (temperature < 0) {
			MessageBox::Show("Temperature cannot be lower than absolute zero (0K).", "Conversion Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else {
			Celsius = ConvertToCelsius(temperature, "Kelvin");
			Fahrenheit = ConvertToFahrenheit(Celsius, "Celsius");

			// Create and show MyForm1 with results in textBox1
			MyForm1^ resultWindow = gcnew MyForm1();
			resultWindow->textBox1->Text = "Temperature in Celsius: " + Celsius.ToString("F2") + "\r\n" +
				"Temperature in Fahrenheit: " + Fahrenheit.ToString("F2");
			resultWindow->ShowDialog();
		}
	}
}
