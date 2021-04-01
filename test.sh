#! /bin/bash
# test to make sure reading and writing to leds is working

# get config settings from conf.txt
mapfile -t lines < conf.txt
# dir to find leds in
leddir="${lines[0]}"
# default values for the leds
defaults=(${lines[1]})
# file for changing trigger in $leddir
t="${lines[2]}"
# file for changing brightness in $leddir
b="${lines[3]}"
# duration to pause for between stages
d="${lines[4]}"

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
# fails the test and exits the script
fail ()
{
	echo Test failed.
	exit 1
}
# attempt to echo $1 to file $2 and fail the whole script if it fails
try () { echo "$1" > "$2" || fail; }

echo "Entering led directory '$leddir'"
cd "$leddir" || fail

# check that the trigger and brightness files are available in $leddir/*


sleep "$d"
echo "Turning all led triggers to 'none'"
for led in *"/$t"
do
	echoprev "$led" 1
	try none "$led"
done

sleep "$d"
echo "Turning all leds ON"
for led in *"/$b"
do
	echoprev "$led"
	try 1 "$led"
done

sleep "$d"
echo "Turning all leds OFF"
for led in *"/$b"
do
	try 0 "$led"
done

sleep "$d"
echo "Resetting triggers to DEFAULT state"
i=0
for led in *"/$t"
do
	def="${defaults[i]}"
	echo -e "\tResetting trigger for '$led' to '$def'"
	try "$def" "$led"
	(( i++ ))
done
