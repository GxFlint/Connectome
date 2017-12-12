#include "internal_types.h"
#include "activation_functions.h"
#include "math.h"

// f(x) = x
void identity(tiny_int count, weight_t *x) {
	return;
}

// f(x) = 1 if x > 0 else 0 -> {0, 1}
void binary_step(tiny_int count, weight_t *x) {
	for (tiny_int i = 0; i < count; i++) {
		if (x[i] < 0) {
			x[i] = 0;
		}
		else {
			x[i] = 1;
		}
	}
}

// f(x) = 0 if x < 0 else x -> (0, ∞)
void rectified_linear(tiny_int count, weight_t *x) {
	for (tiny_int i = 0; i < count; i++) {
		if (x[i] < 0) {
			x[i] = 0;
		}
	}
}

// f(x) = 0.01x if x < 0 else 0 -> (-∞, ∞)
void leaky_rectified_linear(tiny_int count, weight_t *x) {
	for (tiny_int i = 0; i < count; i++) {
		if (x[i] < 0) {
			x[i] = 0.01 * x[i];
		}
	}
}

// f(x) = tanh(x) -> (-1, 1)
void tangent(tiny_int count, weight_t *x) {
	for (tiny_int i = 0; i < count; i++) {
		x[i] = tanhf(x[i]);
	}
}

// f(X)j = tanhf(e^X)j / Σ tanhf(e^X)k -> (0, 1)
void softmax_normalized(tiny_int count, weight_t *x) {
	weight_t sum = 0.0;
	for (tiny_int i = 0; i < count; i++) {
		sum += x[i] = expf(tanhf(x[i]));
	}
	for (tiny_int i = 0; i < count; i++) {
		x[i] = x[i] / sum;
	}
}

// Derivative ==============================================================

// f'(x) = 1 -> {1}
void derivative_identity(tiny_int count, weight_t *x) {
	for (tiny_int i = 0; i < count; i++) {
		x[i] = 1.0;
	}
}

// f'(x) = 0 if x != 0 else ? -> {0}
void derivative_binary_step(tiny_int count, weight_t *x) {
	for (tiny_int i = 0; i < count; i++) {
		x[i] = 0.0;
	}
}

// f'(x) = 0 if x < 0 else 1 -> {0, 1}
void derivative_rectified_linear(tiny_int count, weight_t *x) {
	for (tiny_int i = 0; i < count; i++) {
		if (x[i] < 0) {
			x[i] = 0.0;
		}
		else {
			x[i] = 1.0;
		}
	}
}

// f'(x) = 0.01 if x < 0 else 1 -> {0.01, 1}
void derivative_leaky_rectified_linear(tiny_int count, weight_t *x) {
	for (tiny_int i = 0; i < count; i++) {
		if (x[i] < 0) {
			x[i] = 0.01;
		}
		else {
			x[i] = 1.0;
		}
	}
}

// f'(x) = 1 - tanh(x)² -> (-1, 1)
void derivative_tangent(tiny_int count, weight_t *x) {
	for (tiny_int i = 0; i < count; i++) {
		x[i] = powf(tanhf(x[i]), 2);
	}
}

// f'(X)j = f(X)(1 - f(X)) -> (0, 1)
void derivative_softmax_normalized(tiny_int count, weight_t *x) {
	softmax_normalized(count, x);
	for (tiny_int i = 0; i < count; i++) {
		x[i] = x[i] * (1 - x[i]);
	}
}

