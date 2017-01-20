#include "systemc.h"
#include "controllunit.h"
#include "engine.h"
//#include "frontCar.h"
//#include "user.h"

int sc_main(int argc, char* argv[])
{
	// generating the sc_signal
	//sc_signal<int> data_sig;
	//sc_signal<int> data2_sig;

	// generating the modules
	controllunit ctrlunit1("controllunit");
	engine engine1("engine");
	//user user1("user");

	// connecting modules via signals
	/*prod1.data(data_sig);
	cons1.data(data_sig);
	prod2.data(data2_sig);
	cons1.data2(data2_sig);
*/
	// Run the simulation till sc_stop is encountered
	sc_start();

	return 0;
}

