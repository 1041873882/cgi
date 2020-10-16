
#ifndef __E_HTTP_H__
#define __E_HTTP_H__

#include <time.h>

#include "tinyxml.h"
#include "dxml.h"
#include "dmsg.h"
#include "sMisc.h"

class eHttpXml {
public:
	eHttpXml();
	~eHttpXml();

	const char *get(const char *url);

public:
	TiXmlDocument m_doc;
	char m_zone[64];
};

class talkXml {
public:
	talkXml();
	~talkXml();

	const char *get(const char *url);

public:
	TiXmlDocument m_doc;
	char m_zone[64];
};

extern eHttpXml ehttp_xml;
extern talkXml talk_xml;

void eHttpResponse(int val);

void eHttpResponse(const char *val);

void eHttpResponse(float val);

int eHttpRequestInt(char **postvars, char **getvars, const char *name);

char *eHttpRequestText(char **postvars, char **getvars, const char *name);

#define ePrint(x)	eHttpResponse(x)

#define eGetInt(name)	eHttpRequestInt(postvars, getvars, name)

#define eGetText(name)	eHttpRequestText(postvars, getvars, name)

int eGetFormData(const char *name, char **p);

char *eGetFormFile(const char *name);

const char *eGetUser(void);

int limit(void);

void print_html_header(void);

#endif
