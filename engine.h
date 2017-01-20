#include <systemc.h>

#ifndef ENGINE_H_
#define ENGINE_H_

SC_MODULE(Engine){

	sc_in<int> S_on;
	sc_in<int> S_off;

	double v_current, m_throttle;//v_current muss wahrscheinlich sc_out sein

	SC_CTOR(Engine){
		SC_METHOD(turn);
		sensitive << S_on << S_off;
	}

	void turn()
	{
		if(S_on){
			//timer Sache muss noch rein, dass alle sekunde v erhöht wird
			v_current = v_current + acceleration(m_throttle,v_current)
			cout << "[" << sc_time_stamp() << "](" << name() << "): read " << v_current << " from port data." << endl;
		}

		if(S_off){}			

	}

//B! Diese Funktion vielleicht auslagern?

	//! VORGABE: Hilfsfunktionen für die erste Hausaufgabe
	// Parameter für Beschleunigungsverhalten des Autos
	int a_max = 7; // [m/s^2]
	int v_min = 0; // [m/s]
	int v_max = 55; // [m/s]
	int v_descent = 21; // [m/s] 

	/* Funktion zur Berechnung der Beschleunigung abhängig von Geschwindigkeit und Motoreinstellung
	   \param throttle: Motoreinstellung, Wertebereich [-100, 100]
	   \param v: derzeitige Geschwindigkeit in [m/s]
	   \return Beschleunigung in [m/s^2]
	 */
	double acceleration(double throttle, double v)
	{
		if(throttle > 100)
			throttle = 100;
		if(throttle < -100)
			throttle = -100;

	    if(v >= v_min || throttle >= 0) {
	    	if(v <= v_descent || throttle < 0)
		    	return (a_max * throttle)/100;
	    	else
		    	return ( ((v-v_descent)*(-a_max)*throttle)/(v_max-v_descent) + a_max*throttle )/100;
	    } else
		return 0.0;
	}


};

#endif

	
