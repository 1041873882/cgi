#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cgivars.h"
#include "eHttp.h"
#include "dmsg.h"

void process(char **getvars, char **postvars, int form_method)
{
 print_html_header(); 
	srand(clock());
printf("<html>\n");
printf("<head>\n");
printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
printf("<link href=\"/css/style.css\" rel=\"stylesheet\" type=\"text/css\">\n");
printf("<script type=\"text/javascript\" src=\"/js/jquery-1.8.0.min.js\"></script>\n");
printf("</head>\n");
printf("\n");
printf("<script>\n");
printf("function on_reboot_submit()\n");
printf("{\n");
printf("	if(confirm(\"");
 ePrint(ehttp_xml.get("/dnake/other/reboot/warning")); printf("\")) {\n");
printf("		var url = \'/cgi-bin/jsapi.cgi?api=reboot&__tag=");
 ePrint(rand()); printf("\';\n");
printf("		$.get(url, function(json) {\n");
printf("		}, \"json\");\n");
printf("	}\n");
printf("}\n");
printf("</script>\n");
printf("\n");
printf("<body>\n");
printf("	<table width=\"90%%\" border=\"0\" id=\"table1\">\n");
printf("		<tr>\n");
printf("			<td class=\"header\"><strong>");
 ePrint(ehttp_xml.get("/dnake/other/title")); printf("</strong></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td><hr></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td>&nbsp;</td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td>");
 ePrint(ehttp_xml.get("/dnake/other/reboot/prompt")); printf("</td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td><input type=\"button\" value=\"");
 ePrint(ehttp_xml.get("/dnake/other/reboot/title")); printf("\" onClick=\"on_reboot_submit()\"></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td>&nbsp;</td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td><hr></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td>&nbsp;</td>\n");
printf("		</tr>\n");
printf("	</table>\n");
printf("</body>\n");
printf("</html>\n");
}

