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
	dmsg req;
	dxml p;
	req.request("/ui/web/advanced2/read", NULL);
	p.load(req.body());

	if(form_method == POST) {
		const char *mac = eGetText("mac");
		if (mac) {
			dmsg req;
			dxml p2;
			p2.setText("/params/mac", mac);
			req.request("/ui/web/advanced2/write", p2.data());
		}
		p.setText("/params/mac", mac);
	}
printf("<html>\n");
printf("\n");
printf("<head>\n");
printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
printf("<link href=\"/css/style.css\" rel=\"stylesheet\" type=\"text/css\">\n");
printf("\n");
printf("</head>\n");
printf("\n");
printf("<body>\n");
printf("\n");
printf("<form method=\"post\" action=\"advanced2.cgi\">\n");
printf("	<table width=\"90%%\" border=\"0\" id=\"table1\">\n");
printf("		<tr>\n");
printf("			<td class=\"header\"><strong>");
 ePrint(ehttp_xml.get("/dnake/advanced2/title")); printf("</strong></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td><hr></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td>\n");
printf("			<table border=\"0\" id=\"table2\">\n");
printf("				<tr>\n");
printf("					<td width=60>");
 ePrint(ehttp_xml.get("/dnake/advanced2/mac")); printf("</td>\n");
printf("					<td>\n");
printf("					<input style=\"width:200px;\" name=\"mac\" value=\"");
 ePrint(p.getText("/params/mac")); printf("\"></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>&nbsp;</td>\n");
printf("					<td>&nbsp;</td>\n");
printf("				</tr>\n");
printf("				</table>\n");
printf("			</td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td><hr></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td>\n");
printf("			<input type=\"submit\" value=\"");
 ePrint(ehttp_xml.get("/dnake/submit")); printf("\"></td>\n");
printf("		</tr>\n");
printf("	</table>\n");
printf("</form>\n");
printf("\n");
printf("</body>\n");
printf("</html>\n");
}

