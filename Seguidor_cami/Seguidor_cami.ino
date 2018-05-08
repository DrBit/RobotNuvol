//Robonuvol


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

/////////////////////////////
// Definicions globals ******					// Ens serveixen per fer mes llegible el codi. 
/////////////////////////////					// Utilitzarem paraules en comptes de numeros
#define dreta 1
#define esquerra 2
#define endavant 3
#define endarrera 4
#define negre 5
#define blanc 6
#define dretaC 7
#define esquerraC 8

#define sortint_esquerra 9
#define sortint_dreta 10
#define sortint_dreta_rectificant 11
#define sortint_esquerra_rectificant 12
/////////////////////////////


/////////////////////////////
// CONFIGURACIÓ   ***********
/////////////////////////////
// Aquest codi s'executara un sol cop al principi
void setup()
{
	// Inicialització motors i sensors
	Inicialitzem_Motors();						// Configurem els pins dels motors
	Inicialitzem_SensorsOptics();				// Configurem els pins dels sensors optics
	Serial.begin (9600);						// Configurem comunicacio amb el PC a velocitat 9600 bauds per segon
	Serial.println ("\n*Robot seguidor*");		// Enviem missatge al ordinador
	Serial.println ("Començem a seguir la linea en 2 segons");
	delay (2000);	// pausa 2 segons					
}


/////////////////////////////
// LOOP  ********************
/////////////////////////////
// Aquest codi s'executara indefinidament
void loop()
{

	int vel_rapid = 180;
	int vel_lent = 100;

	// No detectem cap linia negre, en principi estem be
	if (!linia_SensDret() && !linia_SensCentre () && !linia_SensEsq()) {
		mouMotorsLiniaRecta(vel_rapid);		// Mou recte
	}

	// Continua el codi segons el diagrama de flux


	
}

// funcions que es poden utilitzar:
/*


mouMotorsLiniaRecta(velocitat 0 - 250);	
giraEsquerra(velocitat 0 - 250);
giraDreta(velocitat 0 - 250);	

linia_SensCentre();		// Si es detecta linia al sensor centre retorna TRUE, sino FALSE
linia_SensDret();		// Si es detecta linia al sensor dret retorna TRUE, sino FALSE
linia_SensEsq();		// Si es detecta linia al sensor esquerra retorna TRUE, sino FALSE
// Es poden negar amb el operador !


*/