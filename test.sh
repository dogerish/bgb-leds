#! /bin/bash
# test to make sure reading and writing to leds is working

# get config settings from config.txt
mapfile -t lines < config.txt
# dir to find leds in
leddir="${lines[0]}"
# text before the led's index
ledpre="${lines[1]}"
# text after the led's index
ledsuf="${lines[2]}"
# default values for the leds
defaults=(${lines[3]})
# file for changing trigger in $leddir
t="${lines[4]}"
# file for changing brightness in $leddir
b="${lines[5]}"
# duration to pause for between stages
d="${lines[6]}"

# pauses for $d time, echos out $1, and then
# executes felf for every file matching "$leddir/$ledpre"*"$ledsuf/$2",
# providing the file name and index as the arguments
felf () { :; }
foreachled ()
{
	sleep "$d"
	echo "$1"
	i=0
	for led in "$leddir/$ledpre"*"$ledsuf/$2"
	do
		felf "$led" $i
		(( i++ ))
	done
}
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

felf ()
{
	echoprev "$1" 1
	try none "$1"
}
foreachled "Turning all led triggers to 'none'" "$t"

felf ()
{
	echoprev "$1"
	try 1 "$1"
}
foreachled "Turning all leds ON" "$b"

felf () { try 0 "$1"; }
foreachled "Turning all leds OFF" "$b"

felf ()
{
	def="${defaults[$2]}"
	echo -e "\tResetting trigger for '$1' to '$def'"
	try "$def" "$1"
}
foreachled "Resetting triggers to DEFAULT state" "$t"
