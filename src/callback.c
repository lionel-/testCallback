#define R_NO_REMAP
#include <Rinternals.h>

struct cb_data {
    SEXP node;
    SEXP value;
};

static void cb(void* data_) {
    struct cb_data* data = (struct cb_data*) data_;
    SETCDR(data->node, Rf_cons(data->value, CDR(data->node)));
}

SEXP testCallbackReturn(SEXP node) {
    struct cb_data data1 = { node, Rf_install("first") };
    R_onExit(cb, (void*) &data1);

    struct cb_data data2 = { node, Rf_install("second") };
    R_onExit(cb, (void*) &data2);

    return R_NilValue;
}

SEXP testCallbackJump(SEXP node) {
    struct cb_data data1 = { node, Rf_install("first") };
    R_onExit(cb, (void*) &data1);

    struct cb_data data2 = { node, Rf_install("second") };
    R_onExit(cb, (void*) &data2);

    Rf_error("tilt");
}

static void jumpy_cb(void* data_) {
    Rf_error("jump");
}

SEXP testJumpyCallback(SEXP node) {
    R_onExit(jumpy_cb, NULL);

    struct cb_data data1 = { node, Rf_install("first") };
    R_onExit(cb, (void*) &data1);

    struct cb_data data2 = { node, Rf_install("second") };
    R_onExit(cb, (void*) &data2);

    Rf_error("tilt");
}

SEXP testNoCallbacks() {
    return R_NilValue;
}
