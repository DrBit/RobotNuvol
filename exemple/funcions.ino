
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
		dir_esquerra = endavant;
		digitalWrite(in1, HIGH);
		digitalWrite(in2, LOW);
	}else if (direccio == endarrera) {
		dir_esquerra = endarrera;
		digitalWrite(in1, LOW);
		digitalWrite(in2, HIGH);
	}
}

void motorEsquerraDIR (int direccio) {
	if (direccio == endavant) {
		dir_dret = endavant;
		digitalWrite(in3, HIGH);
		digitalWrite(in4, LOW);
	}else if (direccio == endarrera) {
		dir_dret = endarrera;
		digitalWrite(in3, LOW);
		digitalWrite(in4, HIGH);
	}
}

void motorDretPWM (int valorPWM) {
	if (valorPWM > 255 || valorPWM < -255) {
		Serial.println ("motorDretPWM: El valor no pot ser mes gran de 255 ni mes petit de -255");
		return;
	}

	vel_dreta = valorPWM;

	if (valorPWM < 0) {
		valorPWM = valorPWM * -1;		// Si la velocitat es negativa canviarem a positiu
		motorDretDIR (endarrera);
	}else{ 
		motorDretDIR (endavant);
	}

	#ifdef factor_motor_dret
	float temp_value = 0;
	temp_value = (float) valorPWM/100;
	temp_value = temp_value * (float) factor_motor_dret;
	valorPWM = (int) temp_value;
	#endif

	driver_Dret (valorPWM);
}

void motorEsquerraPWM (int valorPWM) {
	if (valorPWM > 255 || valorPWM < -255) {
		Serial.println ("motorEsquerraPWM: El valor no pot ser mes gran de 255 ni mes petit de -255");
		return;
	}

	vel_esquerra = valorPWM;

	if (valorPWM < 0) {
		valorPWM = valorPWM * -1;		// Si la velocitat es negativa canviarem a positiu
		motorEsquerraDIR (endarrera);
	}else{ 
		motorEsquerraDIR (endavant);
	}

	#ifdef factor_motor_esquerra
	float temp_value = 0;
	temp_value = (float) valorPWM/100;
	temp_value = temp_value * (float) factor_motor_esquerra;
	valorPWM = (int) temp_value;
	#endif

	driver_Esquerra (valorPWM);
}

void giraDreta (int valor_gir) {
	if (valor_gir > 255 || valor_gir < -255) {
		Serial.println ("griaDreta: El valor no pot ser mes gran de 255 ni mes petit de 0");
		return;
	}

	if (vel_esquerra != vel_dreta) {		// motors estan girant, primer els posem a velocitat igual
		int diferencia = 0;
		int vel_final = 0;
		if (vel_esquerra > vel_dreta) {
			diferencia = vel_esquerra - vel_dreta;
			diferencia = diferencia / 2;
			vel_final = vel_dreta + diferencia;
			motorEsquerraPWM (vel_final);
			motorDretPWM (vel_final);
		}else{
			diferencia = vel_dreta - vel_esquerra;
			diferencia = diferencia / 2;
			vel_final = vel_esquerra + diferencia;
			motorEsquerraPWM (vel_final);
			motorDretPWM (vel_final);
		}
	}
	// un cop tenim la velocitat final a les dues rodes podem processar el gir

	int valor_gir_meitat = valor_gir / 2;
	int velocitat_final_dreta = vel_dreta - valor_gir_meitat;
	int velocitat_final_esquerra = vel_esquerra + valor_gir_meitat;
	motorEsquerraPWM (velocitat_final_esquerra);
	motorDretPWM (velocitat_final_dreta);
}

void giraEsquerra (int valor_gir) {
	if (valor_gir > 255 || valor_gir < -255) {
		Serial.println ("giraEsquerra: El valor no pot ser mes gran de 255 ni mes petit de 0");
		return;
	}

	if (vel_esquerra != vel_dreta) {		// motors estan girant, primer els posem a velocitat igual
		int diferencia = 0;
		int vel_final = 0;
		if (vel_esquerra > vel_dreta) {
			diferencia = vel_esquerra - vel_dreta;
			diferencia = diferencia / 2;
			vel_final = vel_dreta + diferencia;
			motorEsquerraPWM (vel_final);
			motorDretPWM (vel_final);
		}else{
			diferencia = vel_dreta - vel_esquerra;
			diferencia = diferencia / 2;
			vel_final = vel_esquerra + diferencia;
			motorEsquerraPWM (vel_final);
			motorDretPWM (vel_final);
		}
	}
	// un cop tenim la velocitat final a les dues rodes podem processar el gir

	int valor_gir_meitat = valor_gir / 2;
	int velocitat_final_dreta = vel_dreta + valor_gir_meitat;
	int velocitat_final_esquerra = vel_esquerra - valor_gir_meitat;
	motorEsquerraPWM (velocitat_final_esquerra);
	motorDretPWM (velocitat_final_dreta);
}

void mouMotorsLineaRecta (int valor_PWM) {
	if (valor_PWM > 255 || valor_PWM < -255) {
		Serial.println ("mouMotorsLineaRecta: El valor no pot ser mes gran de 255 ni mes petit de -255");
		return;
	}

	motorEsquerraPWM(valor_PWM);
	motorDretPWM(valor_PWM);
}

void driver_Dret (int valorPWM) {
	// Velocitat 0~255
	analogWrite(enA, valorPWM);
}

void driver_Esquerra (int valorPWM) {
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