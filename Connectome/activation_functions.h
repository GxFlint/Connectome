#include "internal_types.h"
#include "math.h"

// =========================================================================
// == Activation Functions =================================================
// =========================================================================

// f(x) = x -> (-∞, ∞)
void identity(tiny_int count, weight_t *x);

// f(x) = 1 if x > 0 else 0 -> {0, 1}
void binary_step(tiny_int count, weight_t *x);

// f(x) = 0 if x < 0 else x -> (0, ∞)
void rectified_linear(tiny_int count, weight_t *x);

// f(x) = 0.01x if x < 0 else 0 -> (-∞, ∞)
void leaky_rectified_linear(tiny_int count, weight_t *x);

// f(x) = tanh(x) -> (-1, 1)
void tangent(tiny_int count, weight_t *x);

// f(X)j = tanhf(e^X)j / Σ tanhf(e^X)k -> (0, 1)
void softmax_normalized(tiny_int count, weight_t *x);


// =========================================================================
// == Derivative ===========================================================
// =========================================================================

// f'(x) = 1 -> {1}
void derivative_identity(tiny_int count, weight_t *x);

// f'(x) = 0 if x != 0 else ? -> {0}
void derivative_binary_step(tiny_int count, weight_t *x);

// f'(x) = 0 if x < 0 else 1 -> {0, 1}
void derivative_rectified_linear(tiny_int count, weight_t *x);

// f'(x) = 0.01 if x < 0 else 1 -> {0.01, 1}
void derivative_leaky_rectified_linear(tiny_int count, weight_t *x);

// f'(x) = 1 - tanh(x)² -> (-1, 1)
void derivative_tangent(tiny_int count, weight_t *x);

// f'(X)j = f(X)(1 - f(X)) -> (0, 1)
void derivative_softmax_normalized(tiny_int count, weight_t *x);
