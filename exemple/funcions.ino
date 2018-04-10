
/////////////////////////////
// Arxiu funcions ***********
/////////////////////////////

// exemples funcions
// motorDretPWM (valor);		// Valor = número de 0 a 255. (0 = parat i 255 = màxima velocitat)
								// Modifica la velocitat a la que gira el motor
// motorEsquerraPWM (valor);	// Valor = número de 0 a 255. (0 = parat i 255 = màxima velocitat)
								// Modifica la velocitat a la que gira el motor
// motorDretDIR (valor);		// Valor = endavant o endarrera. Modifica la direcció a la que gira el motor dret
// motorEsquerraDIR (valor);	// Valor = endavant o endarrera. Modifica la direcció a la que gira el motor esquerra
// linea_SensCentre ();			// Ens retorna un valor (0 o 1 - FALSE o TRUE)
								// Ens indica si el sensor esta detectant una linea negre
// linea_SensDret ();			// Ens retorna un valor (0 o 1 - FALSE o TRUE)
								// Ens indica si el sensor esta detectant una linea negre
// linea_SensEsq ();			// Ens retorna un valor (0 o 1 - FALSE o TRUE)
								// Ens indica si el sensor esta detectant una linea negre

/////////////////////////////
// Inicialització ***********
/////////////////////////////

void Inicialitzem_Motors  () {
	// Configurem els pins dels motors
	pinMode(enA, OUTPUT);						// Configurem els pins com a OUTPUT (sortida)
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	// Inicialitzem motors
	motorDretDIR (endavant);					// Motor dret direcció endavant
	motorEsquerraDIR (endavant);				// Motor esquerra direcció endavant
}

void Inicialitzem_SensorsOptics () {
	// Configurem els pins del sensors optics
	pinMode(sens_esquerra, INPUT);				// Configurem els pins com a INPUT (entrada)
	pinMode(sens_centre, INPUT);
	pinMode(sens_dreta, INPUT);
}

/////////////////////////////
// Funcions motors***********
/////////////////////////////

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

/////////////////////////////
// Funcions Sensors *********
/////////////////////////////

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