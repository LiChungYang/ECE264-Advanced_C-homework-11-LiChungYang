#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"
#include "mazehelper.h"
#include "path.h"
#include "list.h"

PathLL * solveMaze(Maze * m) {
	
	PathLL * successPaths = buildPaths();
	char * retval = malloc(((m->height * m->width) + 1) * sizeof(char));

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	depthFirstSolve(m, mp, retval, 0, successPaths);
	
	free(retval);
	
	return successPaths;
}

void depthFirstSolve(Maze * m, MazePos curpos, char * path, int step, PathLL * successPaths) {
	
  //Fill in. (Your best bet is to modify a working implementation from PA08)

	if (atEnd(curpos, m))
	{
	  path[step] = '\0';
	  addNode(successPaths, path);
	  return;
	}

	if (!squareOK(curpos, m))
        {
          return;
        }

	m -> maze[curpos.ypos][curpos.xpos].visited = true;

	MazePos North = curpos;
	North.xpos = curpos.xpos;
	North.ypos = curpos.ypos - 1;

	MazePos South = curpos;
        South.xpos = curpos.xpos;
        South.ypos = curpos.ypos + 1;

	MazePos West = curpos;
        West.xpos = curpos.xpos - 1;
        West.ypos = curpos.ypos;

	MazePos East = curpos;
        East.xpos = curpos.xpos + 1;
        East.ypos = curpos.ypos;
	path[step] = NORTH;
	depthFirstSolve(m, North, path, (step + 1), successPaths);
	path[step] = SOUTH;
	depthFirstSolve(m, South, path, (step + 1), successPaths);
	path[step] = WEST;
	depthFirstSolve(m, West, path, (step + 1), successPaths);
	path[step] = EAST;
	depthFirstSolve(m, East, path, (step + 1), successPaths);
	
	
	m -> maze[curpos.ypos][curpos.xpos].visited = false;
	return;
}	

