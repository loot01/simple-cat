# simple-cat
A simple recreating of the cat command, written entirely in C

## Compilation
`make`

## Usage
`./simple-cat <FLAGS> <FILES>`

Flags:\
	 -E display $ at end of each line\
	 -n number all output lines\
	 -T display TAB characters as ^I\
	 -V show non printable characters as .

To use stdin add `-` instead of a filename.
