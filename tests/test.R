
library("testCallback")
return_ptr <- testCallback:::testCallbackReturn
jump_ptr <- testCallback:::testCallbackJump
jumpy_cb_ptr <- testCallback:::testJumpyCallback
no_cb_ptr <- testCallback:::testNoCallbacks


test_no_exit_target <- function(env) .Call(jump_ptr, env)
env <- new.env()
tryCatch(test_no_exit_target(env), error = function(cnd) err <<- cnd)
stopifnot(err$message == "can't find exit target, jumping to top level")

test_return <- function(env) .safeCall(return_ptr, env)
env <- new.env()
test_return(env)
stopifnot(identical(names(env), c("foo", "bar")))

test_jump <- function(env) .safeCall(jump_ptr, env)
env <- new.env()
tryCatch(test_jump(env), error = function(cnd) err <<- cnd)
stopifnot(err$message == "tilt")
stopifnot(identical(names(env), c("foo", "bar")))

test_jumpy_cb <- function(env) .safeCall(jumpy_cb_ptr, env)
env <- new.env()
tryCatch(test_jumpy_cb(env), error = function(cnd) err <<- cnd)
stopifnot(err$message == "Error: jump\n")
stopifnot(identical(names(env), "bar"))

test_no_cb <- function() .safeCall(no_cb_ptr)
test_no_cb()
