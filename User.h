#include <systemc.h>

#ifndef User_H_
#define User_H_

SC_MODULE(User){
	
	//zur Kontolleinheit
	sc_out<int> B_start, B_stop, p_gas, p_bremse, B_set, B_vm, B_vp;
	
	//von der Kontrolleinheit
	sc_in<int> tempomatstatus;	

	//vom FrontCar
	sc_in<double> dist;

	//zum Frontcar
	sc_out<double> v_car;
	sc_out<bool>  car_sighted;
	//Variablen
	int i,random, randomzeit;

	//Prozesse
	SC_CTOR(User){
		B_start.initialize(0);
		p_gas.initialize(0);
		p_bremse.initialize(0);
		B_set.initialize(0);
		car_sighted.initialize(false); 
		SC_THREAD(starten);
	}

	void starten()
	{
		//Aufgabe b) zweites Szenario
		B_start=1;	
		cout << "Nutzer startet den Motor" << endl;
		wait(SC_ZERO_TIME); 
	

		//Abfolge des Nutzers Szenrio 1 von b)
		cout << "Der Nutzer beschleunigt" << endl;
		p_gas=35;
		wait(13,SC_SEC);
		p_gas=0;

		cout << "Tempomat wird angeschalten" << endl;
		B_set=1;wait(1,SC_SEC);B_set=0; //Knopf wird wieder logelassen

		//3 min warten
		wait(60,SC_SEC);
		
		//Ein Auto wird gesichtet
		cout << "Auto wird gesichtet" << endl;
		car_sighted=true; 			
		v_car=20;

		//5 min folgen
		wait(60,SC_SEC);

		//Auto vorne bremst auf 15 m/s
		cout << "Auto bremst auf 15 m/s" << endl;
		v_car=15;
		
		//wieder 5 min folgen
		wait(60,SC_SEC);

		//Auto beschleunigt wieder auf 30 m/s
		cout << "Auto bschleunigt auf 35 m/s" << endl;
		v_car=35;
		wait(5,SC_SEC);
		
	}

};

#endif

 

