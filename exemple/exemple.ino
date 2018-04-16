
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
int dir_dret = 1;								// Variable per a la direcció del motor dret
int dir_esquerra = 1;							// Variable per a la direcció del motor esquerra
int ultimGir = 0;								// Variable per enmagatzemar la direcció de l'ultim gir fet
int ValorGirEsquerra = 0;						// Variable per a la velocitat de gir esquerra
int ValorGirDreta = 0;							// Variable per a la velocitat de gir dreta

/////////////////////////////
// Definicions globals ******					// Ens serveixen per fer mes llegible el codi. 
/////////////////////////////					// Utilitzarem paraules en comptes de numeros
#define dreta 1
#define esquerra 2
#define endavant 3
#define endarrera 4
#define negre 5
#define blanc 6
/////////////////////////////

/////////////////////////////
// Variables Sensors ********
/////////////////////////////
int colorLinia = negre;

/////////////////////////////
// CONFIGURACIÓ   ***********
/////////////////////////////
// Aquest codi s'executara un sol cop al principi
void setup()
{
	// Inicialització motors i sensors
	Inicialitzem_Motors();						// Configurem els pins dels motors
	Inicialitzem_SensorsOptics();				// Configurem els pins dels sensors optics
	// Comunicació amb el PC
	Serial.begin (9600);						// Configurem comunicacio amb el PC a velocitat 9600 bauds per segon
	Serial.println ("\n*Robot seguidor*");		// Enviem missatge al ordinador
	Serial.println ("Començem a seguir la linea en 5 segons");
	// pausa 5 segons
	delay (5000);								
}


/////////////////////////////
// LOOP  ********************
/////////////////////////////
// Aquest codi s'executara indefinidament
void loop()
{
	// Linia negre sobre sensor central
	if (linia_SensCentre () && !linia_SensDret() && !linia_SensEsq()) {
		mouMotorsLiniaRecta (255);
	}
	
	// Linia negre sobre sensor central i sensor dret
	if (linia_SensCentre () && linia_SensDret() && !linia_SensEsq()) {
		giraDreta (150);
	}

	// Linia negre sobre sensor central i sensor esquerra
	if (linia_SensCentre () && !linia_SensDret() && linia_SensEsq()) {
		giraEsquerra(150);
	}

	// Linia negre sobre sensor dret
	if (!linia_SensCentre () && linia_SensDret() && !linia_SensEsq()) {
		giraDreta (200);
	}

	// Linia negre sobre sensor esquerra
	if (!linia_SensCentre () && !linia_SensDret() && linia_SensEsq()) {
		giraEsquerra(200);
	}

	// Linia negre sobre sensor central, dret i esquerra (possiblement estem perduts)
	if (linia_SensCentre () && linia_SensDret() && linia_SensEsq()) {
		if (ultimGir == esquerra) {		// Girem en la mateixa direccio que l'ultim cop que hem girat
			giraEsquerra(150);			
		}else if (ultimGir == dreta) {
			giraDreta (150);
		}else{
			mouMotorsLiniaRecta (150);
		}
	}

	// Linia negre enlloc (possiblement estem perduts)
	if (!linia_SensCentre () && !linia_SensDret() && !linia_SensEsq()) {
		if (ultimGir == esquerra) {		// Girem en la mateixa direccio que l'ultim cop que hem girat
			giraEsquerra(150);
		}else if (ultimGir == dreta) {
			giraDreta (150);
		}else{
			mouMotorsLiniaRecta (150);
		}
	}
	
}