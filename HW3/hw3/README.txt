Elliott Dobbs
HW3 Artificial Intelligence
823004322

Problem 1:

	Compile with 	"gplc hw3pr1.pl"
	Run with 	"./hw3pr1"

	Enter the query 

		"my_sort([***list of numbers separated by comma***], L)." 

	To get a sorted list of the given numbers


Problem 2: **NOT WORKING COMPLETELY**

	Compile with 	"gplc hw3pr2.pl"
	Run with 	"./hw3pr2"

	Enter the query 

		"my_topo_sort([***list of pairs separated by comma***], X)." 

	-To get a single list of input values without duplicates.  This might actually be 		a topological sort for most inputs, however no sorting occurs.
	-you query "my_max([***list of pairs separated by comma***], X)." to see that my 		max function is working as intended by the problem, returning an element 		of the list which can be appended to the back of the topological sorted list.


Problem 3:
	
	Compile with 	"gplc hw3pr3.pl"
	Run with 	"./hw3pr3"

	Enter the query:
		"mother(X, charles)." 
	To get the mother of charles (elizabeth)

	Enter the query:
		"grandchild(X, elizabeth)." 
	To get all the grandchildren of elizabeth (peter, zara, william, harry, beatrice, 	eugenie, louise, and james)

	Enter the query:
		"brother_in_law(X, diana)." 
	To get the brothers in law of diana (charles, andrew, and edward).

	Enter the query:
		"ancestor(X, eugenie)." 
	To get the ancestors of eugenie (sarah, andrew, elizabeth, philip, mum, and 		george)

	Lastly, enter the query:
		"cousin(X, charlotte)." 
	To see that charlotte has no cousins.
	If you want to see the cousin predicate working for someone who does have a 		cousin, query 
		"cousin(X, isla)."
	To get mia.


Extra Credit Problem 4:

	Compile with 	"gplc hw3pr4.pl"
	Run with 	"./hw3pr4"

	Enter the query:
		"grandpa(me, me)."
	To see that based on the information in the problem, you are your own grandpa.







