#include "internal_types.h"
#include "activation_functions.h"
#include "mkl.h" // Intel® Math Kernel Library 

typedef struct network_struct network_t;
typedef struct layer_struct layer_t;
typedef float weight_t;

//network_t* create_network(void* stuff);

network_t* alocate_network(tiny_int layer_count, layer_t* current_layer);

void dealocate_network(network_t* network);

weight_t* solve(weight_t* input, network_t *network);

void train(weight_t* input, weight_t* desired_output, weight_t coeficient, network_t* network);

export int test();
