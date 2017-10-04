Elliott Dobbs
823004322
HW1



Problem 1:

Build with "g++ -std=c++17 hw1pr1.cpp"
Execute with "./a.out"



Problem 2:

Build with "g++ -std=c++17 -Ofast hw1pr1.cpp"
Execute with "./a.out"

** I was only able to get input files with up to 18 points to run under 60 seconds **
However all should have correct output



Problem 3:

Build with "g++ -std=c++17 hw1pr3.cpp"
Execute with "./a.out"

I feel like my implementation will be pretty different than others.  In my process of creating the BFS, I noticed that I could represent move sequences as base 5 numbers as long as the base 5 number does not have 0s in it.  
With each digit representing a move of the blank tile...
	Up 	: 1
	Right	: 2
	Down 	: 3
	Left	: 4
0 does not represent a valid move so if the number has any 0s then I just skip over it in my BFS iterations. Counting up with base 5 numbers without 0s goes as follows:

	1
	2
	3
	4
	11
	12
	13
	14
	21
	22
	23
	24
	...
	43
	44
	111
	112

With this implementation, I just gave my BFS function a single integer.  This number would be transformed to base 5 to get the sequence of moves for the given game state then checked if it is the same as the end state.  If it is not, then it returns the given number with a flag to represent if it is the not the correct sequence.  Then the main function iterates to the next integer that represents a valid base 5 movement sequence and sends it to carry on the BFS.