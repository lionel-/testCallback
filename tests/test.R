
library("testCallback")
return_ptr <- testCallback:::testCallbackReturn
jump_ptr <- testCallback:::testCallbackJump
jumpy_cb_ptr <- testCallback:::testJumpyCallback
no_cb_ptr <- testCallback:::testNoCallbacks


test_no_exit_target <- function(node) .Call(jump_ptr, node)
node <- pairlist(NULL)
tryCatch(test_no_exit_target(node), error = function(cnd) err <<- cnd)
stopifnot(err$message == "can't find exit target, jumping to top level")
stopifnot(identical(node, pairlist(NULL, quote(first))))

test_return <- function(node) .safeCall(return_ptr, node)
node <- pairlist(NULL)
test_return(node)
stopifnot(identical(node, pairlist(NULL, quote(first), quote(second))))

test_jump <- function(node) .safeCall(jump_ptr, node)
node <- pairlist(NULL)
tryCatch(test_jump(node), error = function(cnd) err <<- cnd)
stopifnot(err$message == "tilt")
stopifnot(identical(node, pairlist(NULL, quote(first), quote(second))))

test_jumpy_cb <- function(node) .safeCall(jumpy_cb_ptr, node)
node <- pairlist(NULL)
tryCatch(test_jumpy_cb(node), error = function(cnd) err <<- cnd)
stopifnot(err$message == "Error: jump\n")
stopifnot(identical(node, pairlist(NULL, quote(first), quote(second))))

test_no_cb <- function() .safeCall(no_cb_ptr)
test_no_cb()
