#define sens1 2
#define sens2 3
#define sens3 4


void setup()
{
	pinMode(sens1, INPUT);
	pinMode(sens1, INPUT);
	pinMode(sens1, INPUT);
	Serial.begin (115200);
	Serial.println ("Proba sensors");
}


void loop()
{

	if (digitalRead(sens1)) {
		Serial.println ("Sensor 1 activat");
	}

	if (digitalRead(sens2)) {
		Serial.println ("Sensor 2 activat");
	}

	if (digitalRead(sens3)) {
		Serial.println ("Sensor 3 activat");
	}

	delay (500);

}

