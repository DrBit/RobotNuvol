// #include <Servo.h>

/////////////////////////////
// PROGRAMA ****************
/////////////////////////////

/////////////////////////////
#define INSTALL
// #define CALIBRATION
// #define RUN
/////////////////////////////
#define factor_motor_dret 		100	// factor de 0 a 100% de la velocitat
#define factor_motor_esquerra	100	// factor de 0 a 100% de la velocitat
/////////////////////////////
 

/////////////////////////////
// Config PINS **************
/////////////////////////////
// motor dret
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor esquerra
int in3 = 7;
int in4 = 6;
int enB = 5;
// sensors optics
int sens_esquerra = 2;
int sens_centre = 3;
int sens_dreta = 4;
//servo
// int servoPIN = 11;
// Servo myservo;  // create servo object to control a servo
/////////////////////////////


//////////////////////////////
// Variables Motors *********
/////////////////////////////
int vel_dreta = 0;
int vel_esquerra = 0;
int ultimGir = 0;
#define dreta 1
#define esquerra 2
#define endavant 1
#define endarrera 2
/////////////////////////////

void setup()
{
	// Sensors
	pinMode(sens_esquerra, INPUT);
	pinMode(sens_centre, INPUT);
	pinMode(sens_dreta, INPUT);
	// Motors
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	// servo
	// myservo.attach(servoPIN);  // attaches the servo on pin 9 to the servo object
	// Serial
	Serial.begin (9600);
	Serial.println ("\n*Robot seguidor*");
	// Inicialitzem motors
	motorDretDIR (endavant);
	motorEsquerraDIR (endavant);
}

void loop()
{
	//////////////////////////////////
	#ifdef INSTALL
	// test motors
	Serial.println ("\nConecta motor dret i comproba que vagi en direccio endavant");
	Serial.println ("Si no va endavant, canvia els cables de lloc");
	Serial.println ("Envia un caracter per continuar");
	motorDretDIR (endavant);
	motorDretPWM (255);
	pausa ();
	motorDretPWM (0);

	Serial.println ("\nConecta motor esquerra i comproba que vagi en direccio endavant");
	Serial.println ("Si no va endavant, canvia els cables de lloc");
	Serial.println ("Envia un caracter per continuar");
	motorEsquerraDIR (endavant);
	motorEsquerraPWM (255);
	pausa ();
	motorEsquerraPWM (0);

	/*
	Serial.println ("Comprova que el servo es mou d'un canto a l'altre");
	for (int a = 0; a < 3; a++) {
		myservo.write(0);	// definex l'angle del servo
		delay (1000);
		myservo.write(255);	// definex l'angle del servo
		delay (1000);
	}
	Serial.println ("Envia un caracter per continuar");
	pausa ();
	*/

	// test sensors
	Serial.println ("\nComprova que els 3 sensors estan conectats i en l'ordre determinat");
	Serial.println ("Tapa amb el dit cada un d'ells i veuras quan s'activen per aquí");
	Serial.println ("Envia un caracter per continuar");
	neteja_serial ();
	boolean sens1 = 0;
	boolean sens2 = 0;
	boolean sens3 = 0;
	while (Serial.available() == 0){
		boolean temp1 = linea_SensEsq ();
		if (temp1 != sens1) {
			sens1 = temp1;
			if (temp1) {
				Serial.println ("Esquerra activat");
			}else{
				Serial.println ("Esquerra desactivat");
			}
		}


		boolean temp2 = linea_SensCentre ();
		if (temp2 != sens2) {
			sens2 = temp2;
			if (temp2) {
				Serial.println ("Centre activat ");
			}else{
				Serial.println ("Centre desactivat ");
			}
		}

		boolean temp3 = linea_SensDret ();
		if (temp3 != sens3) {
			sens3 = temp3;
			if (temp3) {
				Serial.println ("Dreta activat");
			}else{
				Serial.println ("Dreta desactivat");
			}
		}
		delay (500);
	}

	Serial.println ("\nEl cotxe ja esta configurat!");
    while(1);
	#endif

    //////////////////////////////////////
	#ifdef CALIBRATION
	// test motors
	Serial.println ("\nComprovem que els 2 motors giren a la mateixa velocitat");
	Serial.println ("Canvia si cal els parametres del codi \'factor_motor_dret\' i \'factor_motor_esquerra\' ");
	Serial.print ("factor_motor_dret= ");
	Serial.print (factor_motor_dret);
	Serial.print ("\% \nfactor_motor_esquerra= ");
	Serial.print (factor_motor_esquerra);
	Serial.println ("\% \nEnvia un caracter per continuar");
	motorDretDIR (endavant);
	motorDretPWM (255);
	motorEsquerraDIR (endavant);
	motorEsquerraPWM (255);
	pausa ();
	// para els motors
	motorDretPWM (0);
	motorEsquerraPWM (0);

	/*
	// servo centrat
	Serial.println ("Modifica la posicio del sensor ultrason per a que estigui centrat");
	Serial.println ("Envia un caracter per continuar");
	myservo.write(90);	// 90 es per centrar el servo
	pausa ();
	delay (1000);
	Serial.println ("Sensor a la dreta");
	myservo.write(0);	// 0 dreta
	delay (2000);
	Serial.println ("Sensor a l'esquerra");
	myservo.write(180);	// 180 esquerra
	delay (2000);
	Serial.println ("Sensor centrat");
	myservo.write(90);	// 90 esquerra
	delay (2000);
	pausa ();
	*/

	while(1);

	#endif

	///////////////////////////////////////
	#ifdef RUN

	Serial.println ("Començem a seguir la linea en 3 segons");
	delay (3000);

	while (true) {
		vel_dreta = 0;
		vel_esquerra = 0;

		if (linea_SensCentre () && !linea_SensDret() && !linea_SensEsq()) {
			vel_dreta = 255;
			vel_esquerra = 255;
		}

		if (linea_SensCentre () && linea_SensDret() && !linea_SensEsq()) {
			vel_dreta = 150;
			vel_esquerra = 255;
			ultimGir = esquerra;
		}

		if (linea_SensCentre () && linea_SensEsq() && !linea_SensDret()) {
			vel_dreta = 255;
			vel_esquerra = 150;
			ultimGir = dreta;

		}

		if (!linea_SensCentre () && linea_SensDret() && !linea_SensEsq()) {
			vel_dreta = 0;
			vel_esquerra = 255;
			ultimGir = esquerra;
		}

		if (!linea_SensCentre () && linea_SensEsq() && !linea_SensDret()) {
			vel_dreta = 255;
			vel_esquerra = 0;
			ultimGir = dreta;
		}

		if (linea_SensCentre () && linea_SensEsq() && linea_SensDret()) {
			
			if (ultimGir == esquerra) {
				vel_dreta = 0;
				vel_esquerra = 155;
			}else if (ultimGir == dreta) {
				vel_dreta = 155;
				vel_esquerra = 0;
			}	
		}

		if (!linea_SensCentre () && !linea_SensEsq() && !linea_SensDret()) {
			if (ultimGir == esquerra) {
				vel_dreta = 0;
				vel_esquerra = 155;
			}else if (ultimGir == dreta) {
				vel_dreta = 155;
				vel_esquerra = 0;
			}
		}

		motorDretPWM (vel_dreta);
		motorEsquerraPWM (vel_esquerra);
	}

	#endif
}

void motorDretDIR (int direccio) {
	if (direccio == endavant) {
		digitalWrite(in1, HIGH);
		digitalWrite(in2, LOW);
	}else if (direccio == endarrera) {
		digitalWrite(in1, LOW);
		digitalWrite(in2, HIGH);
	}
}

void motorEsquerraDIR (int direccio) {
	if (direccio == endavant) {
		digitalWrite(in3, HIGH);
		digitalWrite(in4, LOW);
	}else if (direccio == endarrera) {
		digitalWrite(in3, LOW);
		digitalWrite(in4, HIGH);
	}
}

void motorDretPWM (int valorPWM) {
	#ifdef factor_motor_dret
	float temp_value = 0;
	temp_value = (float) valorPWM/100;
	temp_value = temp_value * (float) factor_motor_dret;
	valorPWM = (int) temp_value;
	#endif

	// Velocitat 0~255
	analogWrite(enA, valorPWM);
}

void motorEsquerraPWM (int valorPWM) {
	#ifdef factor_motor_esquerra
	float temp_value = 0;
	temp_value = (float) valorPWM/100;
	temp_value = temp_value * (float) factor_motor_esquerra;
	valorPWM = (int) temp_value;
	#endif

	// Velocitat 0~255
	analogWrite(enB, valorPWM);
}


void pausa () {
	neteja_serial ();
	while (Serial.available() == 0) {
		delay (100);
	}
}

void neteja_serial () {
	while (Serial.available() > 0) {
		char inChar = (char) Serial.read();
	}
}

boolean linea_SensCentre () {
	if (!digitalRead(sens_centre)) {
		return true;
	}else{
		return false;
	}
}

boolean linea_SensDret () {
	if (!digitalRead(sens_dreta)) {
		return true;
	}else{
		return false;
	}
}

boolean linea_SensEsq () {
	if (!digitalRead(sens_esquerra)) {
		return true;
	}else{
		return false;
	}
}