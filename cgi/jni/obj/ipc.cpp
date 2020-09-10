#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cgivars.h"
#include "eHttp.h"
#include "dmsg.h"

static const char *getIpcText(dxml &p, int idx, const char *part)
{
	char s[128];
	const char *val;
	sprintf (s, "/params/r%d/%s", idx, part);
	val = p.getText(s);
	return val ? val : "";
}

void process(char **getvars, char **postvars, int form_method)
{
 print_html_header(); 
	dmsg req;
	dxml p;
	req.request("/ui/web/ipc/read", NULL);
	p.load(req.body());

	if(form_method == POST) {
		dxml p2;
		int idx = eGetInt("dev_max");
		char s[512], s2[512];

		p2.setInt("/params/max", idx);
		for(int i=0; i<idx; i++) {
			sprintf(s, "/params/r%d/name", i);
			sprintf(s2, "name_%d", i);
			p2.setText(s, eGetText(s2));
			sprintf(s, "/params/r%d/url", i);
			sprintf(s2, "url_%d", i);
			p2.setText(s, eGetText(s2));
		}
		req.request("/ui/web/ipc/write", p2.data());

		p.load(p2.data());
	}
printf("<html>\n");
printf("\n");
printf("<head>\n");
printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
printf("<link href=\"/css/style.css\" rel=\"stylesheet\" type=\"text/css\">\n");
printf("\n");
printf("<script>\n");
printf("function select_dev_max(){\n");
printf("	var dev_max = document.getElementById(\"dev_max\").value;\n");
printf("	for (var i=0; i<8; i++) {\n");
printf("		var dev = document.getElementById(\"tr_id_\"+i);\n");
printf("		if (i<dev_max)\n");
printf("			dev.style.display = \"\";\n");
printf("		else\n");
printf("			dev.style.display = \"none\";\n");
printf("	}\n");
printf("}\n");
printf("</script>\n");
printf("\n");
printf("</head>\n");
printf("\n");
printf("<body>\n");
printf("\n");
printf("<form method=\"post\" action=\"ipc.cgi\">\n");
printf("	<table width=\"90%%\" border=\"0\" id=\"table1\">\n");
printf("		<tr>\n");
printf("			<td class=\"header\"><strong>");
 ePrint(ehttp_xml.get("/dnake/ipc/title")); printf("</strong></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td><hr></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td>\n");
printf("			<table border=\"0\">\n");
printf("				<tr>\n");
printf("					<td ><table border=\"0\">\n");
printf("						<tr>\n");
printf("							<td width=\"100\">");
 ePrint(ehttp_xml.get("/dnake/ipc/max")); printf(":</td>\n");
printf("							<td >\n");
printf("								<select style=\"width:60px;\" size=\"1\" id=\"dev_max\" name=\"dev_max\" onChange=\"select_dev_max()\">\n");
printf("									<option value=\"0\" ");
 if(p.getInt("/params/max", 0) == 0) ePrint("selected"); printf(">0</option>\n");
printf("									<option value=\"1\" ");
 if(p.getInt("/params/max", 0) == 1) ePrint("selected"); printf(">1</option>\n");
printf("									<option value=\"2\" ");
 if(p.getInt("/params/max", 0) == 2) ePrint("selected"); printf(">2</option>\n");
printf("									<option value=\"3\" ");
 if(p.getInt("/params/max", 0) == 3) ePrint("selected"); printf(">3</option>\n");
printf("									<option value=\"4\" ");
 if(p.getInt("/params/max", 0) == 4) ePrint("selected"); printf(">4</option>\n");
printf("									<option value=\"5\" ");
 if(p.getInt("/params/max", 0) == 5) ePrint("selected"); printf(">5</option>\n");
printf("									<option value=\"6\" ");
 if(p.getInt("/params/max", 0) == 6) ePrint("selected"); printf(">6</option>\n");
printf("									<option value=\"7\" ");
 if(p.getInt("/params/max", 0) == 7) ePrint("selected"); printf(">7</option>\n");
printf("									<option value=\"8\" ");
 if(p.getInt("/params/max", 0) == 8) ePrint("selected"); printf(">8</option>\n");
printf("								</select>\n");
printf("							</td>\n");
printf("						</tr>\n");
printf("					</table></td>\n");
printf("				</tr>\n");
printf("				");
 for(int i=0; i<8; i++) { printf("\n");
printf("				<tr id=\"tr_id_");
 ePrint(i); printf("\" style=\"");
 if (i<p.getInt("/params/max", 0)) ePrint("display:\"\";"); else ePrint("display:none;"); printf("\">\n");
printf("					<td ><table border=\"0\">\n");
printf("						<tr>\n");
printf("							<td width=\"100\">");
 ePrint(ehttp_xml.get("/dnake/ipc/device")); printf("&nbsp;");
ePrint(i+1);printf(":</td>\n");
printf("							<td ><input style=\"width:180px;\" name=\"name_");
 ePrint(i); printf("\" value=\"");
 ePrint(getIpcText(p, i, "name")); printf("\" /></td>\n");
printf("						</tr>\n");
printf("						<tr>\n");
printf("							<td>");
 ePrint(ehttp_xml.get("/dnake/ipc/url")); printf(":</td>\n");
printf("							<td><input style=\"width:400px;\" name=\"url_");
 ePrint(i); printf("\" value=\"");
 ePrint(getIpcText(p, i, "url")); printf("\" /></td>\n");
printf("						</tr>\n");
printf("					</table></td>\n");
printf("				</tr>\n");
printf("				");
 } printf("\n");
printf("			</table>\n");
printf("			</td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td><hr></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td>\n");
printf("			<input type=\"submit\" value=\"");
ePrint(ehttp_xml.get("/dnake/submit"));printf("\"></td>\n");
printf("		</tr>\n");
printf("	</table>\n");
printf("</form>\n");
printf("\n");
printf("</body>\n");
printf("</html>\n");
}

