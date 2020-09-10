/* cgivars.c
 * (C) Copyright 2000, Moreton Bay (http://www.moretonbay.com).
 * see HTTP (www.w3.org) and RFC
 */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cgivars.h"

/* local function prototypes */
char hex2char(char *hex);
void unescape_url(char *url);
char x2c(char *what);

/* hex2char */
/* RFC */
char hex2char(char *hex) {
	char char_value;
	char_value = (hex[0] >= 'A' ? ((hex[0] & 0xdf) - 'A') + 10 : (hex[0] - '0'));
	char_value *= 16;
	char_value += (hex[1] >= 'A' ? ((hex[1] & 0xdf) - 'A') + 10 : (hex[1] - '0'));
	return char_value;
}

/* unescape_url */
/* RFC */
void unescape_url(char *url) {
	int n, k;
	for(n=0, k=0;url[k];++n, ++k) {
		if((url[n] = url[k]) == '%') {
			url[n] = hex2char(&url[k+1]);
			k += 2;
		}
	}
	url[n] = '\0';
}


/* getRequestMethod
 * retn:	from_method (GET or POST) on success,
 *			-1 on failure.  */
int getRequestMethod() {
	char *request_method;
	int form_method;

	request_method = getenv("REQUEST_METHOD");
	if(request_method == NULL)
		return -1;

	if (!strcmp(request_method, "GET") || !strcmp(request_method, "HEAD") ) {
		form_method = GET;
	} else if (!strcmp(request_method, "POST")) {
		form_method = POST;
	} else {
		/* wtf was it then?!! */
		return -1;
	}
	return form_method;
}


/* getGETvars
 * retn:	getvars */
char **getGETvars() {
	int i;
	char **getvars;
	char *getinput;
	char **pairlist;
	int paircount = 0;
	char *nvpair;
	char *eqpos;

	getinput = getenv("QUERY_STRING");
	if (getinput)
		getinput = strdup(getinput);

	/* Change all plusses back to spaces */
   	for(i=0; getinput && getinput[i]; i++)
		if(getinput[i] == '+')
			getinput[i] = ' ';

   	pairlist = (char **) malloc(256*sizeof(char **));
	paircount = 0;
   	nvpair = getinput ? strtok(getinput, "&") : NULL;
	while (nvpair) {
		pairlist[paircount++]= strdup(nvpair);
        	if(!(paircount%256))
			pairlist = (char **) realloc(pairlist,(paircount+256)*sizeof(char **));
       		nvpair = strtok(NULL, "&");
	}

   	pairlist[paircount] = 0;
   	getvars = (char **) malloc((paircount*2+1)*sizeof(char **));
	for (i= 0; i<paircount; i++) {
		if((eqpos=strchr(pairlist[i], '='))) {
       	    		*eqpos = '\0';
            		unescape_url(getvars[i*2+1] = strdup(eqpos+1));
   	    	} else {
			unescape_url(getvars[i*2+1] = strdup(""));
        	}
		unescape_url(getvars[i*2] = strdup(pairlist[i]));
    	}
   	getvars[paircount*2] = 0;
    	for(i=0;pairlist[i];i++)
		free(pairlist[i]);
	free(pairlist);
	if (getinput)
		free(getinput);
	return getvars;
}

typedef struct {
	char name[128];
	char file[128];
	char *data;
	int length;
} form_data_t;

#define MAX_FORM_DATA_SIZE	32
static form_data_t form_data[MAX_FORM_DATA_SIZE];
static int form_data_idx = 0;
int is_form_data = 0;

int eGetFormData(const char *name, char **p)
{
	int i;

	for (i=0; i<form_data_idx; i++) {
		if (!strcmp (form_data[i].name, name)) {
			*p = form_data[i].data;
			return form_data[i].length;
		}
	}
	return -1;
}

char *eGetFormFile(const char *name)
{
	int i;

	for (i=0; i<form_data_idx; i++) {
		if (!strcmp (form_data[i].name, name))
			return form_data[i].file;
	}
	return NULL;
}

char *eGetFormText(const char *name)
{
	int i;

	for (i=0; i<form_data_idx; i++) {
		if (!strcmp (form_data[i].name, name))
			return form_data[i].data;
	}
	return NULL;
}

int eGetFormInt(const char *name, int val)
{
	int i;

	for (i=0; i<form_data_idx; i++) {
		if (!strcmp (form_data[i].name, name))
			return atoi(form_data[i].data);
	}
	return val;
}

static char *getMulBoundary(char *data, int length, char *bd)
{
	int i, len = strlen(bd);
	for (i=0; i<length; i++) {
		if (!memcmp (data+i, bd, len))
			return data+i;
	}
	return NULL;
}

static void getFormData(char *s, char *e)
{
	if (s+4>= e || form_data_idx >= MAX_FORM_DATA_SIZE)
		return;
	e -= 4;

	char *p, *p2, *p3, *p4, *p5;
	if ((p = strstr(s, " name=\"")) == NULL || p >= e)
		return;
	p += strlen(" name=\"");
	if ((p2 = strchr(p, '\"')) == NULL || p2 >= e)
		return;
	if ((p3 = strstr(s, "\r\n\r\n")) == NULL || p3 >= e)
		return;
	p3 += strlen("\r\n\r\n");
	if ((p4 = strstr(s, " filename=\"")) && p4 < e) {
		p4 += strlen(" filename=\"");
		p5 = strchr(p4, '\"');
	} else
		p4 = NULL;

	int idx = form_data_idx;
	int len = e-p3;

	memset (&form_data[idx], 0, sizeof(form_data_t));
	memcpy (form_data[idx].name, p, p2-p);
	if (p4)
		memcpy (form_data[idx].file, p4, p5-p4);
	form_data[idx].length = len;
	form_data[idx].data = (char *)malloc(len+1);
	memcpy (form_data[idx].data, p3, len);
	form_data[idx].data[len] = 0;

	form_data_idx++;
}

static void getMultipartVars(char *data, int length, char *bd)
{
	char *ps, *pe, *p, *p2;

	ps = data;
	pe = data+length;
	while (ps<pe) {
		p = getMulBoundary(ps, pe-ps, bd);
		if (p) {
			p += strlen(bd);
			p2 = getMulBoundary(p, pe-p, bd);
			if (p2 == NULL)
				p2 = pe;
			getFormData (p, p2);
			ps = p2;
		} else
			break;
	}
}


/* getPOSTvars
 * retn:	postvars */
char **getPOSTvars() {
	int i;
	int content_length;
	char **postvars;
	char *postinput;
	char **pairlist;
	int paircount = 0;
	char *nvpair;
	char *eqpos;
	char *content_type;

	form_data_idx = 0;
	is_form_data = 0;

	postinput = getenv("CONTENT_LENGTH");
	if (!postinput)
		exit(1);
	if(!(content_length = atoi(postinput)))
		exit(1);
	if(!(postinput = (char *) malloc(content_length+1)))
		exit(1);
	if (!fread(postinput, content_length, 1, stdin))
		exit(1);
	postinput[content_length] = '\0';

	content_type = getenv("CONTENT_TYPE");
	if (content_type && strstr(content_type, "multipart/form-data")) {
		char *p;

		is_form_data = 1;

		p = strstr(content_type, "boundary=");
		if (p) {
			char bd[256];
			strcpy (bd, p+strlen("boundary="));
			getMultipartVars(postinput, content_length, bd);
		}
		free(postinput);
		return NULL;
	}

   	for(i=0;postinput[i];i++)
		if(postinput[i] == '+')
			postinput[i] = ' ';

	pairlist = (char **) malloc(256*sizeof(char **));
	paircount = 0;
	nvpair = strtok(postinput, "&");
	while (nvpair) {
		pairlist[paircount++] = strdup(nvpair);
		if(!(paircount%256))
    			pairlist = (char **) realloc(pairlist, (paircount+256)*sizeof(char **));
		nvpair = strtok(NULL, "&");
	}
    
	pairlist[paircount] = 0;
	postvars = (char **) malloc((paircount*2+1)*sizeof(char **));
	for(i = 0;i<paircount;i++) {
        	if((eqpos = strchr(pairlist[i], '='))) {
       	    		*eqpos= '\0';
	        	unescape_url(postvars[i*2+1] = strdup(eqpos+1));
        	} else {
       	    		unescape_url(postvars[i*2+1] = strdup(""));
	   	}
        	unescape_url(postvars[i*2]= strdup(pairlist[i]));
	}
	postvars[paircount*2] = 0;

	for(i=0;pairlist[i];i++)
		free(pairlist[i]);
	free(pairlist);
	free(postinput);

	return postvars;
}

/* cleanUp
 * free the mallocs */
int cleanUp(int form_method, char **getvars, char **postvars) {
	int i;

	if (postvars) {
		for(i=0;postvars[i];i++)
			free(postvars[i]);
		free(postvars);
	}
	if (getvars) {
		for(i=0;getvars[i];i++)
			free(getvars[i]);
		free(getvars);
	}

	for (i=0; i<form_data_idx; i++) {
		if (form_data[i].data)
			free (form_data[i].data);
	}

	return 0;
}

static char eUser[128];

const char *eGetUser(void)
{
	char *user = getenv("REMOTE_USER");
	if (user)
		strcpy (eUser, user);
	else
		eUser[0] = 0;
	return eUser;
}

void print_html_header(void)
{
	printf("Cache-Control: no-cache,no-store\r\n");
	printf("Connection: Keep-Alive\r\n");
	printf("Content-Type: text/html; charset=utf-8\r\n");
	printf("\r\n");
}
