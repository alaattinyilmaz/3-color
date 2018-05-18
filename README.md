
# 3-COLOR

**Problem Description**

A proper graph-colouring is the assignment of colors to the vertices of a graph under the condition that no adjacent vertices joined by an edge have the same color. More formally, 
An n-node undirected graph G(V,E) with node set V and edge set E, an assignment of a color ϕv, ϕv ≠ ϕw for every (v,w) ∈ E.
A graph colouring that properly uses k colors is called k-colouring. The k-colouring decision problem asks, for each graph, G, is G k-colourable. Call this problem k-COLOR.
	In this project, an NP-Complete Graph Colouring problem 3-COLOR will be examined, therefore our problem can be expressed as follows:
	
- On an n-node undirected graph G(V,E) with node set V and edge set E, can each node of G(V,E) be assigned exactly one of three colors
Red, Blue, Green - in such a way that no two nodes which are joined by an edge, are assigned the same color?

**Algorithm**

 There is not an exact algorithm that solves 3-COL problem in polynomial time but there are some heuristics such as 
 greedy coloring algorithm and a more efficient one 3-coloring in time O(1.3446n) algorithm by Richard Beigel and David Eppstein.

In this project, we covered and analyzed the performance of the greedy approach to 3-COL problem.


For our analysis, please see the Project Report.

