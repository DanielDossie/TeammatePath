Miami Heap

Daniel Dossie
Anna Giunta
Dillon Aldrich


CASE 0
Analysis
    O(1)
Description

    Regardless of input size, this case will take a constant number of operations to execute. If no input file is given or if there is an incorrectly formatted input, the program will terminate without processing any data. An error message will be produced.

CASE 1
Analysis
    O(PS) 
    PS = Number of Player-seasons
Description

    Opens and prints contents of file. Only operation is reading each line once and printing the contents out. Each line is equivalent to one player-season so the total number of player-seasons is the number of lines in the file.

CASE 2a
Analysis
    O(P + T + ElogE)
    P = number of players
    T = number of teams
    E = number of edges
Description
    Each individual player and team get their own vertex object. Then each vertex object is inserted into the hashtable. This is done in constant time. This happens P + T times. Linked list insertion is constant time as well. This happens P + T times. Assuming our hash-function evenly distributes the vertices, searching for the player at the index of their hash value is constant time. Once the player is found, traversing its linked list of teams and adding each team to a vector takes O(E) which makes runtime O(P + T + E). This also applies for the for loop with our sorting vector. The sorting function that is used takes O(ElogE) time. The runtime then becomes O(P + T + ElogE).


CASE 2b
Analysis
    O(P + T + ElogE)
    P = number of players
    T = number of teams
    E = number of  edges
Description
    Same runtime as Case 2a. The only difference is that we added a single constant time operation inside of one of the for loops. This has no effect on runtime. Each individual player and team get their own vertex object. Then each vertex object is inserted into the hashtable. This is done in constant time. This happens P + T times. Linked list insertion is constant time as well. This happens P + T times. Assuming our hash-function evenly distributes the vertices, searching for the player at the index of their hash value is constant time. Once the player is found, traversing its linked list of teams and adding each team to a vector takes O(E) which makes runtime O(P + T + E). This also applies for the for loop with our sorting vector. The sorting function that is used takes O(ElogE) time. The runtime then becomes O(P + T + ElogE).
CASE 3
Analysis
    O(P+ (TE) + ElogE)
    P = number of players
    T = number of teams
    E = number of edges
Description

    Each individual player and team get their own vertex object. Then each vertex object is inserted into the hashtable. This is done in constant time. This happens P + T times. Linked list insertion is constant time as well. This happens P + T times. Considering our hash function is designed to place the same team names in the same vector within the hashtable, worst-case, we must go through every team. For each desired team, we traverse its linked list of players and increase the count of each player which takes O(TE) as well as push it to the back of the vector which is a constant operation. The sorting function sorts the vector of players based on how many years they spent with the team and then alphabetically. This takes O(ElogE) time. Adding them together, the runtime of this is O(P + (TE) + (ElogE))  
CASE 4
Analysis
    O(P + T + E)
    P = number of players
    T = number of teams
    E = number of edges 
Description

    Each individual player and team get their own vertex object. Then each vertex object is inserted into the hashtable. This is done in constant time. This happens P + T times. Linked list insertion is constant time as well. This happens P + T times. Assuming our hash-function evenly distributes the vertices, searching for the player at the index of their hash value is constant time. This makes runtime O(P + T). In our BFS algorithm, for the total number of vertices, which is equivalent to P + T, we go through a for loop that executes a maximum of E times. This will result in a runtime of O(P + T + E). So, O((P + T) + (P + T + E)) results in O(P + T + E).