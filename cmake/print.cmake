function(print)
	foreach(var ${ARGN})
		message(("${var} = ${${var}}"))
	endforeach()
endfunction(print)

function(print_env)
	foreach(var ${ARGN})
		message("${var} = $ENV{${var}}")
	endforeach()
endfunction(print_env)