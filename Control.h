#include "systemc.h"

#ifndef Control_H_
#define Control_H_

SC_MODULE(Control){
	//Signale
	//vom Nutzer/Umgebung
	sc_in<int> B_start,B_stop, p_gas, p_bremse, B_set, B_vm, B_vp;
	sc_out<int> tempomatstatus;

	//zum Motor
	sc_out<int> S_on,S_off;
	sc_out<double>m_throttle;

	//vom Motor
	sc_in<double> v_current;
	
	//vom Frontcar
	sc_in<double> v_acc;
	sc_in<bool> in_range;

	//Variablen
	double v_d;
	int t;

	//Konstanten
	static const int v_min = 0; // [m/s]
 	static const int v_max = 55; // [m/s]

	//Prozessdefinition
	SC_CTOR(Control){
		
		SC_METHOD(control_unit);
		t=0;
		sensitive << B_start << B_stop << p_gas << p_bremse << B_set << B_vm << B_vp;
	}

	//Prozess
	void control_unit()
	{ 
		if(B_start==1){
			//Motor wird gestartet
			S_on=1;

			//Gas wurde gedrückt						
			if(p_bremse==0)
			m_throttle = p_gas;

			//Bremse wurde gedrückt
			if(p_bremse > 0){
			m_throttle = -p_bremse; t=0; tempomatstatus=0;}

			//Tempomat wurde angeschalten
			if(B_set==1)tempomatstatus=1; 

			//Tempomatmodus
			if(tempomatstatus==1 && p_bremse==0){
					//v_d=v_current nur beim Anschalten
					if(t==0){	
						v_d=v_current;
						}
					t=1;	
				
					//v_d anpassen
					if (B_vm==1 && v_current > 0) v_d=v_d-1;
					if (B_vp==1 && v_current < 55) v_d=v_d+1;
					
					//Tempomat passt m_throttle an
					if(p_gas==0){
						
						//Tempomat normal 
						if(in_range==false)m_throttle= controller(v_d, v_current);
						
						//ACC, FrontCar gesichtet
						if(in_range==true){
							//ACC wenn v_d>v_acc (Vergleich double ist schlecht)
							if(v_d>v_acc)m_throttle=controller(v_acc, v_current);
							//Tempomat
							if(v_d<=v_acc)m_throttle= controller(v_d, v_current);
						}	
					}			
					next_trigger(1,SC_SEC);	
			}
		}
		else S_off=1,S_on=0, m_throttle=0, tempomatstatus=0;
	}


	double controller(double v_d, double v)
		{
		
		// Parameter und Hilfsvariablen für PD-Controller		
		int kp=8, kd=4;
		double e_old = 0.0, e_new, dE, throttle_new;
		
		e_new = v_d-v;
		dE = e_new - e_old;
		e_old = e_new;
		
		throttle_new = kp*e_new + kd*dE;

		if(throttle_new > 100)
			return 100;
		else if ( throttle_new < -100)
			return -100;
		else
			return throttle_new;

		}
};
#endif

 

