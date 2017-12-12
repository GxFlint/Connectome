#include "internal_types.h"
#include "connectome.h"
#include "activation_functions.h"
#include "mkl.h" // Intel� Math Kernel Library 

struct layer_struct {
	int_u input_count;
	int_u neuron_count;

	void(*activation_function)(tiny_int, weight_t*);
	void(*derivative_function)(tiny_int, weight_t*);

	weight_t* weights;
};

struct network_struct {
	tiny_int layer_count;
	layer_t* layers;
	weight_t* weight_collection;
};

network_t* alocate_network(tiny_int layer_count, layer_t* layers) {

	network_t *network = malloc(sizeof(network_t));
	network->layer_count = layer_count;
	network->layers = layers;
	network->weight_collection = malloc(sizeof(weight_t));

	int_u weight_count = 0;

	layer_t* current_layer = layers;
	layer_t* last_layer = &layers[layer_count - 1];

	do { // for each layer
		current_layer->weights = &network->weight_collection[weight_count];

		// Network weight count == Sum of layer's -> (Weight Matrix) + Bias Vector
		weight_count += (current_layer->input_count * current_layer->neuron_count) + current_layer->neuron_count;
	} while (current_layer++ != last_layer);

	realloc(network->weight_collection, sizeof(weight_t) * weight_count);

	return network;
}

void dealocate_network(network_t* network) {
	free(network->weight_collection);
	free(network);
}

void matrix_multiply(int_u input_count, weight_t* input, int_u neuron_count, weight_t* weight_matrix, weight_t* weighted_input) {
	const float alpha = 1.0, beta = 0.0; // ?
	const int_u n = 1;

	realloc(input, sizeof(weight_t) * input_count + 1);
	input[input_count] = 1.0; // Bias input
	
	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
		neuron_count, n, input_count + 1, alpha, weight_matrix, input_count + 1, input, n, beta, weighted_input, n);
}


weight_t* solve(weight_t* input, network_t *network) {
	
	weight_t* weighted_input = malloc(sizeof(weight_t));

	layer_t* current_layer = network->layers;
	layer_t* last_layer = &network->layers[network->layer_count - 1];

	do {
		matrix_multiply(current_layer->input_count, input, current_layer->neuron_count, current_layer->weights, weighted_input);

		(current_layer->activation_function)(current_layer->neuron_count, weighted_input);

		input = weighted_input;
	} while (current_layer++ != last_layer);

	return weighted_input;
}

float calc_error_signal(int_u i, weight_t* error_signal, layer_t* layer) {
	weight_t weight;
	weight_t error;

	layer->neuron_count;
	layer->input_count;

	for (int_u n = 0; n < layer->neuron_count; n++) {
		weight = layer->weights[(layer->input_count * n) + i];
		error = error_signal[n];

	}	
}

float sum(layer_t* layer, weight_t* error_signal, int_u n) {
	layer->weights[layer->neuron_count]
	error_signal[n] 
}

void train(weight_t* input, weight_t* desired_output, weight_t coeficient, network_t* network) {
	int_u neuron_count;
	int_u input_count;

	weight_t** error_signal;
	weight_t* result;

	tiny_int layer_count = network->layer_count;

	layer_t* layer = network->layers;
	layer_t* current_layer;
	layer_t* last_layer = &network->layers[layer_count - 1];
	

	error_signal = malloc(sizeof(weight_t*) * layer_count + 1);

	{ // for the results of the last layer
		result = solve(input, network);

		error_signal[layer_count] = malloc(sizeof(weight_t) * neuron_count);
		for (int_u n = 0; n < neuron_count; n++) { // for each neuron in the last layer
			error_signal[layer_count][n] = desired_output[n] - result[n];
		}
	};

	neuron_count = last_layer->neuron_count;

	result = solve(input, network);

	// defining the error signal of each neuron
	for (tiny_int L = layer_count - 1; L >= 0; L--) { // for each layer
		error_signal[L] = malloc(sizeof(weight_t) * layer[L].neuron_count);
		for (int_u n = 0; n < neuron_count; n++) { // for each neuron
			error_signal[L][n] = sum(error_signal[L - 1], n, &layer[L]);
		}
	}

	current_layer = layer;
	do {

	} while (current_layer++ != last_layer);
	

	for (tiny_int L = layer_count - 2; L >= 0; L--) { // for each layer before the last
		error_signal[L] = malloc(sizeof(weight_t) * layer[L].neuron_count);
		neuron_count = layer[L].neuron_count;
		input_count = layer[L].input_count;

		for (unsigned int n = 0; n < neuron_count; n++) { // for each neuron
			for (tiny_int i = 0; i < input_count; i++) {
				error_signal[L][n] = error_signal[L - 1][n] * layer[L].weights[(n * input_count) + i];
			}
		}
	}

	for (tiny_int L = 0; L < layer_count; L++) {
		neuron_count = layer[L].neuron_count;
		for (tiny_int n = 0; n < neuron_count; n++) {
			input_count = layer[L].input_count;
			for (tiny_int i = 0; i < input_count; i++) {
				unsigned int weight_id = (n * input_count) + i;
				layer[L].weights[weight_id] = layer[L].weights[weight_id] + coeficient * error_signal[L][i];
			}
		}
	}

	free(result);
	for (tiny_int i = 0; i < layer_count + 1; i++) {
		free(error_signal[i]);
	}
	free(error_signal);
}

int test() {
	tiny_int layer_count = 3;
	layer_t layers[] = {{ 3, 4, rectified_linear, derivative_rectified_linear },
						{ 4, 2, rectified_linear, derivative_rectified_linear },
						{ 2, 1, binary_step,	  derivative_binary_step }};

	network_t* nn = alocate_network(layer_count, layers);

	free(nn);

	return 0;
}