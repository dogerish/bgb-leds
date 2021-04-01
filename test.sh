#! /bin/bash
# test to make sure reading and writing to leds is working

# dir to find leds in
leddir="/sys/class/leds"
# default values for the leds
defaults=(heartbeat mmc0 cpu0 mmc1)
# file for changing trigger in $leddir
t="trigger"
# file for changing brightness in $leddir
b="brightness"

# pause
pause () { sleep 2; }
# echo out previous state for $1
# if $2 is 1, it will filter the output from cat to only show what is in []
echoprev ()
{
	out="`cat "$1"`"
	if (( "$2" ))
	then
		out="`echo "$out" | sed 's/^.*\[\(.*\)\].*$/\1/'`"
	fi
	echo -e "\tPrevious state for '$1': '$out'"
}

echo "Entering led directory '$leddir'"
cd "$leddir"

pause
echo "Turning all led triggers to 'none'"
for led in *"/$t"
do
	echoprev "$led" 1
	echo none > "$led"
done

pause
echo "Turning all leds ON"
for led in *"/$b"
do
	echoprev "$led"
	echo 1 > "$led"
done

pause
echo "Turning all leds OFF"
for led in *"/$b"
do
	echo 0 > "$led"
done

pause
echo "Resetting triggers to DEFAULT state"
i=0
for led in *"/$t"
do
	def="${defaults[i]}"
	echo -e "\tResetting trigger for '$led' to '$def'"
	echo "$def" > "$led"
	(( i++ ))
done
