
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eHttp.h"

eHttpXml ehttp_xml;

eHttpXml::eHttpXml()
{
	FILE *fp = fopen("/var/etc/language", "r");
	if (fp) {
		fscanf(fp, "%s", m_zone);
		fclose(fp);
	} else
		strcpy(m_zone, "CHS");

	// m_doc.LoadFile("/dnake/httpd/http.xml", TIXML_ENCODING_UTF8);	//origin 2020 9/8
	m_doc.LoadFile("/dnake/httpd/cgi-bin/http.xml", TIXML_ENCODING_UTF8);	//ybh 2020 9/8
}

eHttpXml::~eHttpXml()
{
}

const char *eHttpXml::get(const char *url)
{
	TiXmlNode *node;
	char s[128];

	sprintf(s, "%s/%s", url, m_zone);

	if ((node = m_doc.FindFirstNode (s)) && node->FirstChild())
		return node->FirstChild()->Value();

	return "err";
}

void eHttpResponse(int val)
{
	printf ("%d", val);
}

void eHttpResponse(const char *val)
{
	if (val)
		printf ("%s", val);
}

void eHttpResponse(float val)
{
	printf ("%f", val);
}

extern int is_form_data;
char *eGetFormText(const char *name);

char *eHttpRequestText(char **postvars, char **getvars, const char *name)
{
	if (is_form_data) {
		return eGetFormText(name);
	} else {
		int i;
		if (postvars) {
			for (i=0; postvars[i]; i+= 2) {
				if(!strcmp(postvars[i], name))
					return postvars[i+1];
			}
		}

		if (getvars) {
			for (i=0; getvars[i]; i+= 2) {
				if(!strcmp(getvars[i], name))
					return getvars[i+1];
			}
		}
	}
	return NULL;
}

int eHttpRequestInt(char **postvars, char **getvars, const char *name)
{
	char *p = eHttpRequestText(postvars, getvars, name);
	if (p == NULL)
		return 0;
	return atoi(p);
}

int limit(void)
{
	static int sys_limit = -1;
	if (sys_limit != -1)
		return sys_limit;

	sys_limit = 0;
	FILE *fp = fopen("/dnake/etc/limit", "r");
	if (fp) {
		fscanf(fp, "%d", &sys_limit);
		fclose(fp);
	}
	return sys_limit;
}
