
#include <stdio.h>
#include <string.h>

#include "dmsg.h"
#include "cgivars.h"
#include "eHttp.h"

static void sys_reboot(void)
{
	FILE *fp = fopen("/var/etc/watchdog", "w+");
	if (fp) {
		fprintf(fp, "1");
		fclose(fp);
	}
}

static void print_json_header(void)
{
	printf("Cache-Control: no-cache,no-store\r\n");
	printf("Connection: Keep-Alive\r\n");
	printf("Content-Type: text/plain; charset=utf-8\r\n");
	printf("\r\n");
}

static void api_name_dial(const char *id, const char *name)
{
	if (id == NULL || name == NULL) {
		printf("{\"result\":101, \"text\":\"Data empty!\"}");
		return;
	}

	dxml p;
	dmsg req;
	p.setText("/params/id", id);
	p.setText("/params/name", name);
	req.request("/ui/web/name/write", p.data());

	printf("{\"result\":0, \"text\":\"OK\"}");
}

static void api_forward(const char *id, const char *tel)
{
	if (id == NULL || tel == NULL) {
		printf("{\"result\":101, \"text\":\"Data empty!\"}");
		return;
	}

	dxml p;
	dmsg req;
	p.setText("/params/id", id);
	p.setText("/params/tel", tel);
	req.request("/ui/web/forward/write", p.data());

	printf("{\"result\":0, \"text\":\"OK\"}");
}

static void api_reboot(void)
{
	printf("{\"result\":0, \"text\":\"OK\"}");
	sys_reboot();
}

static void api_default(void)
{
	dmsg req;
	req.request("/ui/web/default/write", NULL);

	printf("{\"result\":0, \"text\":\"OK\"}");
}

void process(char **getvars, char **postvars, int form_method)
{
	print_json_header();

	const char *api = eGetText("api");
	if (api) {
		if (!strcmp(api, "name_dial"))
			api_name_dial(eGetText("id"), eGetText("name"));
		else if (!strcmp(api, "forward"))
			api_forward(eGetText("id"), eGetText("tel"));
		else if (!strcmp(api, "reboot"))
			api_reboot();
		else if (!strcmp(api, "default"))
			api_default();
	} else {
		printf("{\"result\":100, \"text\":\"Not api define!\"}");
	}
}
