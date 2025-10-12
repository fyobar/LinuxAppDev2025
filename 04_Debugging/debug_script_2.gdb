set pagination off
set inferior-tty /dev/null
set args -100 100 3

break main
run
break range
continue

set $_start = start
set $_stop = stop
set $_step = start

break display
continue

set $counter = 1

commands
    silent
    set $counter++
    if ($counter >=28 && $counter <= 35)
	printf "start = %d, stop = %d, step = %d, value = %d\n", $_start, $_stop, $_step, value
    end
    continue
end

continue
quit
