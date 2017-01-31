#include "systemc.h"
#include "User.h"
#include "Control.h"
#include "Engine.h"
#include "FrontCar.h"

int sc_main(int argc, char* argv[])
{
	// generating the sc_signal
	sc_signal<int> B_start_sig,B_stop_sig,S_on_sig, S_off_sig, man_sig, p_gas_sig, p_bremse_sig, B_set_sig, B_vm_sig, B_vp_sig, tempomatstatus_sig;
	sc_signal<double> v_acc_signal, v_car_sig, dist_sig, m_throttle_sig, v_current_sig;
	sc_signal<bool> in_range_sig,car_sighted_sig;
	
	
	// generating the modules
	User U1("User1");
	Control C1("Control1");	
	Engine E1("Engine1");
	FrontCar F1("FrontCar1");
	
 
	// connecting modules via signals
 
		//User
		U1.B_start(B_start_sig);
		U1.B_stop(B_stop_sig);
		U1.p_gas(p_gas_sig);
		U1.p_bremse(p_bremse_sig);
		U1.B_set(B_set_sig);
		U1.B_vm(B_vm_sig);
		U1.B_vp(B_vp_sig);
		U1.dist(dist_sig);
		U1.car_sighted(car_sighted_sig);
		U1.v_car(v_car_sig);
		U1.tempomatstatus(tempomatstatus_sig);
	        
		//Control
		C1.B_start(B_start_sig);
		C1.B_stop(B_stop_sig);
		C1.S_on(S_on_sig);
		C1.S_off(S_off_sig);
		C1.m_throttle(m_throttle_sig);
		C1.v_current(v_current_sig);
		C1.p_gas(p_gas_sig);
		C1.p_bremse(p_bremse_sig);
		C1.B_set(B_set_sig);
		C1.B_vm(B_vm_sig);
		C1.B_vp(B_vp_sig);
		C1.v_acc(v_acc_signal);
		C1.in_range(in_range_sig);
		C1.tempomatstatus(tempomatstatus_sig);


		//Engine
		E1.S_on(S_on_sig);
		E1.S_off(S_off_sig);
		E1.m_throttle(m_throttle_sig);
		E1.v_current(v_current_sig);

		//FrontCar
		F1.in_range(in_range_sig);
		F1.dist(dist_sig);
		F1.car_sighted(car_sighted_sig);
		F1.v_acc(v_acc_signal);
		F1.v_current(v_current_sig);
		F1.v_car(v_car_sig);
		F1.tempomatstatus(tempomatstatus_sig);

	// Run the simulation till sc_stop is encountered
	sc_start(240,SC_SEC);

	return 0;
}

