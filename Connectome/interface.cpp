////#include <tbb\parallel_for.h>
////#include <tbb\blocked_range.h>
//
//void create_networks();
//
//
//extern "C" {
//	#include "connectome.h"
//#include "internal_types.h"
//#include "activation_functions.h"
//
//	int test() {
//		return 0;
//	}
//
//	void initialize(const char *str_config) {
//		layer_t layers[] = {{ 3, 4, rectified_linear },  // { Inputs, Neurons, Activation Function }
//							{ 4, 2, rectified_linear },
//							{ 2, 1, binary_step } };
//
//		tiny_int layer_count = 3;
//
//		network_t* nn = alocate_network(3, layers);
//
//		dealocate_network(nn);
//	}
//
//	network_t* create_network(void* stuff) {
//		layer_t L1[] = { { 3, 4 },
//						 { 4, 2 },
//						 { 2, 1 } };
//		//create_networks();
//
//		return alocate_network(3, L1);
//	}
//
//	void delete_networks(network_t *networks[]) {
//		// TODO: Multi Thread
//
//		delete_network(networks[0]);
//	}
//
//	void delete_network(network_t* network) {
//		free(network->layers);
//		free(network->weight_collection);
//		free(network);
//	}
//
//}
//
////using namespace tbb;
//
//extern network_t* alocate_network(tiny_int layer_count, layer_t* layer);
//
//void create_networks() {
//
//	layer_t L1[] = {{ 3, 4 },
//					{ 4, 2 },
//					{ 2, 1 }};
//
//	//parallel_for(blocked_range<size_t>(0, 5),
//	//	[=](const blocked_range<rsize_t>& r) {
//	//	alocate_network(3, NULL);
//	//});
//}
