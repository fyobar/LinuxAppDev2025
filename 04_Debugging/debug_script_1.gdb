set pagination off
set inferior-tty /dev/null
set args 1 12

break main
run
break range
continue

set $_start = start
set $_stop = stop
set $_step = start

break display
continue

commands
    silent
    if (value % 5 == 0)
	printf "start = %d, stop = %d, step = %d, value = %d\n", $_start, $_stop, $_step, value
    end
    continue
end

continue
quit
