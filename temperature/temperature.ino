#include <math.h>

//unsigned long UpdateDelay = 1000UL * 60 * 5;	//Update frequency
unsigned long UpdateDelay = 10;
const byte Temperature1Pin = A3;	//Thermistor 1 (Outdoor)
const int Resistance1 = 9900;	//Ohms (measured from R10K of voltage divider 1)
const byte NbSamples = 8;	//Averaging

void setup()
{
	delay(1000);
	Serial.begin(9600);	//Start serial port
	pinMode(Temperature1Pin, INPUT);
	digitalWrite(Temperature1Pin, LOW);
	analogRead(Temperature1Pin);
}

void loop()
{
	float rawADC1 = 0.0;
	for (byte i = NbSamples; i > 0; i--)
	{//Averaging over several readings
		rawADC1 += analogRead(Temperature1Pin);
		delay(100);
	}
	rawADC1 /= NbSamples;

	//Sending a JSON string over Serial/USB like: {"ab":"123","bc":"234","cde":"3546"}
	Serial.println("{\"adc\":\"" + String((long)round(100.0 * rawADC1)) +
			"\", \"temperature\":\"" + String((long)round(thermistor(rawADC1, Resistance1))) +
			"\"}");

	delay(UpdateDelay);
}

float thermistor(float rawADC, float rSeries)
{//http://arduino.cc/playground/ComponentLib/Thermistor2
        double voltagemv = rawADC * 4.9;
        double kVoltageAtZeroCmv = 400;
	double kTemperatureCoefficientmvperC = 19.5;
        double ambientTemperatureC = ((double) voltagemv - kVoltageAtZeroCmv)
        
			/ kTemperatureCoefficientmvperC;
        double temperatureF = (9.0 / 5.0) * ambientTemperatureC + 32.0;
        return temperatureF;
        //This method is not very advanced
	//long resistance = (1024 * rSeries / rawADC) - rSeries;
	//float temp = log(resistance);
	//temp = 1 / (0.001129148 + (0.000234125 * temp) + (0.0000000876741 * temp * temp * temp));
	//return temp - 273.15;	//Kelvin to Celsius
}
