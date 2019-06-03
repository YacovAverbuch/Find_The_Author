# Find-The-Author

This program is part of the CPP lab at the Hebrew university

When run the command "make" on the command line and then, executable file named
'find the auothor' will apear. 

For every known autor file, we rank it according to the cosine between 
the vector of number of keywords appearance in this file,
and the vector of number of the keywords appearance in unknown file.
The output is the known file with the highest score - the closest to 1
(when the angle between the files are the smallest)

to run this program, you should give it the folloing arguments: 
1. text file with the frequent words we want to find in the files.
2. the text file we try to find its author.
3. a texts file contain text (which we know its author) one or more



