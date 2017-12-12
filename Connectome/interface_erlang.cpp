#include <string>
#include <erl_nif.h>

extern "C" {
#include "internal_types.h"
#include "connectome.h"
}

//static ERL_NIF_TERM foo_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
//	int x, ret;
//	if (!enif_get_int(env, argv[0], &x)) {
//		return enif_make_badarg(env);
//	}
//	ret = foo(x);
//	return enif_make_int(env, ret);
//}

static ERL_NIF_TERM test_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
	return enif_make_atom(env, "ok");
}

static ErlNifFunc nif_funcs[] = {
	{ "test_nif", 0, test_nif }
};

ERL_NIF_INIT(connectome, nif_funcs, NULL, NULL, NULL, NULL)
