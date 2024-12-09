#include <stdlib.h>
#include <string.h>

// Key stores the path of the Route
// Value stores the function to be called
struct Route {
	char* key;
	char* value;

	struct Route *left, *right;
};

struct Route * initRoute(char * key, char* value);

struct Route * addRoute(struct Route * root, char * key, char* value);

struct Route * search(struct Route * root, char * key);

void inorder(struct Route * root);
