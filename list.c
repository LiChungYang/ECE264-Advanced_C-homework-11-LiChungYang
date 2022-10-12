#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

/** INTERFACE FUNCTIONS **/

PathLL * buildPaths() {
	PathLL * retval = malloc(sizeof(PathLL));
	retval->head = NULL;
	return retval;
}

void freePaths(PathLL * p) {
	//fill in
	if(p -> head == NULL){
	  free(p);
	  return;
	}

	PathNode * phead = p -> head;
	p -> head = p -> head -> next;
	freeNode(phead);
	freePaths(p);

	return;
}
PathNode * buildNode(char * path) {
	//fill in
	
	//WARNING: don't forget to use strcpy to copy path into the
	//new node. Don't just set them equal, otherwise if the input path changes
	//the node will have the wrong path.
	PathNode * retval = malloc(sizeof(PathNode));
	retval -> path = malloc(sizeof(char) * (strlen(path) + 1));

	strcpy(retval -> path, path);
	retval -> next = NULL;
	return retval;
}

void freeNode(PathNode * p) {
	//fill in
	free(p -> path);
	free(p);
	return;
}

int turn(char * p1, char * p2){
	int c1 = 0;
	int c2 = 0;

	for(int i = 0; i < strlen(p1) - 1; i++){
		if(p1[i] != p1[i+1]){
			c1++;
		}
		if(p2[i] != p2[i+1]){
			c2++;
		}
	}

	return(c1 - c2);
}

bool sortPath(char * p1, char * p2){
	if(strlen(p1) < strlen(p2)){
		return true;
	}

	if(strlen(p1) == strlen(p2)){
		if(turn(p1, p2) < 0){
			return true;
		}
		else if(turn(p1, p2) == 0){
			if(strcmp(p1, p2) < 0){
				return true;
			}
		}
	}

	return false;
}

bool addNode(PathLL * paths, char * path) {
	if(paths -> head == NULL){
		PathNode * answer = buildNode(path);
		paths -> head = answer;
		return true;
	}

	if(paths -> head -> next == NULL){
		if(!sortPath(path, paths -> head -> path)){
			PathNode * answer = buildNode(path);
			paths -> head -> next = answer;
			return true;
		}
		PathNode * answer = buildNode(paths -> head -> path);
		paths -> head -> next = answer;
		strcpy(paths->head->path, path);
		return true;
	}

	PathNode * cr = paths -> head;
	PathNode * nx = paths -> head -> next;
	while(nx != NULL){
		if(sortPath(path, cr -> path)){
			PathNode * answer = buildNode(cr -> path);
			cr -> next = answer;
			answer -> next = nx;
			strcpy(cr -> path, path);
			return true;
		}
		cr = cr -> next;
		nx = nx -> next;
	}

	if(sortPath(path, cr -> path)){
		PathNode * answer = buildNode(cr -> path);
		cr -> next = answer;
		answer -> next = nx;
		strcpy(cr -> path, path);
		return true;
	}
	PathNode * answer = buildNode(path);
	cr -> next = answer;
	return true;
}

bool removeNode(PathLL * paths, char * path) {
	PathNode * cur = paths -> head;
	while(cur != NULL){
		if(strcmp(path, cur -> path) == 0){
			PathNode * temp = cur;
			temp -> next = temp -> next -> next;
			freeNode(cur);
			return true;
		}
		else{
			cur = cur -> next;
		}
	}

	return false;
}
	
bool containsNode(PathLL * paths, char * path) {
	//fill in
	PathNode * curr = paths -> head;
	while(curr != NULL)
	{
		if(!(strcmp(path, curr -> path)) == 0)
		{
		  return true;
		}
			
		
		curr = curr -> next;
		
	}
	return false;
}

void printPaths(PathLL * paths, FILE * fptr) {
	PathNode * curr = paths->head;
	int i = 0;
	while (curr != NULL) {
		fprintf(fptr, "Path %2d: %s\n", i, curr->path);
		i++;
		curr = curr->next;
	}
}
