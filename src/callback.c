#define R_NO_REMAP
#include <Rinternals.h>

struct cb_data {
    SEXP env;
    SEXP sym;
    SEXP value;
};

static void cb(void* data_) {
    struct cb_data* data = (struct cb_data*) data_;
    Rf_defineVar(data->sym, data->value, data->env);
}

SEXP testCallbackReturn(SEXP env) {
    struct cb_data data1 = { env, Rf_install("foo"), R_NilValue};
    R_onExit(cb, (void*) &data1);

    struct cb_data data2 = { env, Rf_install("bar"), R_NilValue};
    R_onExit(cb, (void*) &data2);

    return R_NilValue;
}

SEXP testCallbackJump(SEXP env) {
    struct cb_data data1 = { env, Rf_install("foo"), R_NilValue};
    R_onExit(cb, (void*) &data1);

    struct cb_data data2 = { env, Rf_install("bar"), R_NilValue};
    R_onExit(cb, (void*) &data2);

    Rf_error("tilt");
}

static void jumpy_cb(void* data_) {
    Rf_error("jump");
}

SEXP testJumpyCallback(SEXP env) {
    R_onExit(jumpy_cb, NULL);

    struct cb_data data2 = { env, Rf_install("bar"), R_NilValue};
    R_onExit(cb, (void*) &data2);

    Rf_error("tilt");
}

SEXP testNoCallbacks() {
    return R_NilValue;
}
