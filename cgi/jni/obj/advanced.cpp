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

	req.request("/ui/web/advanced/read", NULL);
	p.load(req.body());

	if(form_method == POST) {
		p.setInt("/params/unlock/dtmf/enable", eGetInt("dtmf_enable"));
		p.setText("/params/unlock/dtmf/data", eGetText("dtmf_data"));
		p.setInt("/params/quick/enable", eGetInt("quick_enable"));
		p.setText("/params/quick/url", eGetText("quick_url"));
		req.request("/ui/web/advanced/write", p.data());
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
printf("<form method=\"post\" action=\"advanced.cgi\">\n");
printf("	<center>\n");
printf("	<table width=\"90%%\" border=\"0\" id=\"table1\">\n");
printf("		<tr>\n");
printf("			<td class=\"header\"><strong><FONT=ARIAL size=\"10\">");
 ePrint(ehttp_xml.get("/dnake/advanced/title")); printf("</strong></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td><hr></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td>\n");
printf("			<table border=\"0\" id=\"table2\">\n");
printf("				<tr>\n");
printf("					<td>");
 ePrint(ehttp_xml.get("/dnake/advanced/dtmf/enable")); printf("</td>\n");
printf("					<td>\n");
printf("					<input type=\"checkbox\" name=\"dtmf_enable\" value=\"1\" ");
 if (p.getInt("/params/unlock/dtmf/enable", 0)) ePrint("checked"); printf("/></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>");
 ePrint(ehttp_xml.get("/dnake/advanced/dtmf/data")); printf("</td>\n");
printf("					<td>\n");
printf("					<input style=\"width:100px;\" name=\"dtmf_data\" value=\"");
 ePrint(p.getText("/params/unlock/dtmf/data")); printf("\"></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>&nbsp;</td>\n");
printf("					<td>&nbsp;</td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>");
 ePrint(ehttp_xml.get("/dnake/advanced/quick/enable")); printf("</td>\n");
printf("					<td>\n");
printf("					<input type=\"checkbox\" name=\"quick_enable\" value=\"1\" ");
 if (p.getInt("/params/quick/enable", 0)) ePrint("checked"); printf("/></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>");
 ePrint(ehttp_xml.get("/dnake/advanced/quick/url")); printf("</td>\n");
printf("					<td>\n");
printf("					<input style=\"width:240px;\" name=\"quick_url\" value=\"");
 ePrint(p.getText("/params/quick/url")); printf("\"></td>\n");
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
printf("	</center>\n");
printf("</form>\n");
printf("\n");
printf("</body>\n");
printf("</html>\n");
}

