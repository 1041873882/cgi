
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "cgivars.h"

void process(char **getvars, char **postvars, int form_method);

int main ()
{
	char **postvars = NULL; /* POST request data repository */
	char **getvars = NULL; /* GET request data repository */
	int form_method; /* POST = 1, GET = 0 */  
	
	form_method = getRequestMethod();

	if(form_method == POST) {
		getvars = getGETvars();
		postvars = getPOSTvars();
	} else if(form_method == GET) {
		getvars = getGETvars();
	}

	process (getvars, postvars, form_method);

	cleanUp(form_method, getvars, postvars);

	fflush(stdout);
	return 0;
}
