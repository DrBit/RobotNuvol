
/////////////////////////////
// PROGRAMA *****************
/////////////////////////////

// Enganxa aquí els paràmetres de calibració aconseguits en el programa de configuració
/////////////////////////////
#define factor_motor_dret 		100	// factor de 0 a 100% de la velocitat
#define factor_motor_esquerra	100	// factor de 0 a 100% de la velocitat
/////////////////////////////
 

/////////////////////////////
// Definicio PINS ***********
/////////////////////////////
int enA = 10;			// motor dret
int in1 = 9;			// motor dret
int in2 = 8;			// motor dret
int in3 = 7;			// motor esquerra
int in4 = 6;			// motor esquerra
int enB = 5;			// motor esquerra
int sens_esquerra = 2;	// sensors optics
int sens_centre = 3;	// sensors optics
int sens_dreta = 4;		// sensors optics
/////////////////////////////


/////////////////////////////
// Variables Motors *********
/////////////////////////////
int vel_dreta = 0;								// Variable per a la velocitat del motor dret
int vel_esquerra = 0;							// Variable per a la velocitat del motor esquerra
int ultimGir = 0;								// Variable per enmagatzemar la direcció de l'ultim gir fet

/////////////////////////////
// Definicions globals ******					// Ens serveixen per fer mes llegible el codi. 
/////////////////////////////					// Utilitzarem paraules en comptes de numeros
#define dreta 1
#define esquerra 2
#define endavant 3
#define endarrera 4
/////////////////////////////

void setup()
{
	Inicialitzem_Motors();						// Configurem els pins dels motors
	Inicialitzem_SensorsOptics();				// Configurem els pins dels sensors optics
	// Comunicació amb el PC
	Serial.begin (9600);						// Configurem comunicacio amb el PC a velocitat 9600 bauds per segon
	Serial.println ("\n*Robot seguidor*");		// Enviem missatge al ordinador
	Serial.println ("Començem a seguir la linea en 3 segons");
	delay (3000);								// pausa 3 segons
}

void loop()
{
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