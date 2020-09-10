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

	req.request ("/ui/web/voip/read", NULL);
	p.load(req.body());

	if(form_method == POST) {
		p.setInt("/params/enable", eGetInt("enable"));
		p.setText("/params/proxy", eGetText("proxy"));
		p.setText("/params/realm", eGetText("realm"));
		p.setText("/params/user", eGetText("user"));
		p.setText("/params/passwd", eGetText("passwd"));
		p.setText("/params/stun/ip", eGetText("stun_ip"));
		p.setInt("/params/stun/port", eGetInt("stun_port"));

		p.setInt("/params/timeout", eGetInt("timeout"));
		p.setInt("/params/host2id", eGetInt("host2id"));

		int h264 = eGetInt("h264");
		if (h264 < 90)
			h264 = 102;
		p.setInt("/params/payload/h264", h264);

		req.request("/ui/web/voip/write", p.data());
	}
printf("<html>\n");
printf("\n");
printf("<head>\n");
printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
printf("<link href=\"/css/style.css\" rel=\"stylesheet\" type=\"text/css\">\n");
printf("</head>\n");
printf("\n");
printf("<body>\n");
printf("\n");
printf("<form method=\"post\" action=\"voip.cgi\">\n");
printf("	<table width=\"90%%\" border=\"0\" id=\"table1\">\n");
printf("		<tr>\n");
printf("			<td class=\"header\"><strong>");
 ePrint(ehttp_xml.get("/dnake/voip/title")); printf("</strong></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td><hr></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td>\n");
printf("			<table border=\"0\" id=\"table2\">\n");
printf("				<tr>\n");
printf("					<td>");
 ePrint(ehttp_xml.get("/dnake/voip/enable")); printf("</td>\n");
printf("					<td>\n");
printf("					<input type=\"checkbox\" name=\"enable\" value=\"1\" ");
 if (p.getInt("/params/enable", 0)) ePrint("checked"); printf("/></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>&nbsp;</td>\n");
printf("					<td>&nbsp;</td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/voip/proxy")); printf("</td>\n");
printf("					<td><input style=\"width:180px;\" name=\"proxy\" value=\"");
 ePrint(p.getText("/params/proxy")); printf("\"></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>");
 ePrint(ehttp_xml.get("/dnake/voip/realm")); printf("</td>\n");
printf("					<td>\n");
printf("					<input style=\"width:180px;\" name=\"realm\" value=\"");
 ePrint(p.getText("/params/realm")); printf("\"></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>");
 ePrint(ehttp_xml.get("/dnake/voip/user")); printf("</td>\n");
printf("					<td>\n");
printf("					<input style=\"width:180px;\" name=\"user\" value=\"");
 ePrint(p.getText("/params/user")); printf("\"></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>");
 ePrint(ehttp_xml.get("/dnake/voip/passwd")); printf("</td>\n");
printf("					<td>\n");
printf("					<input style=\"width:180px;\" name=\"passwd\" type=\"password\" value=\"");
 ePrint(p.getText("/params/passwd")); printf("\"></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>&nbsp;</td>\n");
printf("					<td>&nbsp;</td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>");
 ePrint("H.264:"); printf("</td>\n");
printf("					<td>\n");
printf("					<input style=\"width:64px;\" name=\"h264\" value=\"");
 ePrint(p.getInt("/params/payload/h264", 102)); printf("\"></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>");
 ePrint(ehttp_xml.get("/dnake/voip/stun_ip")); printf("</td>\n");
printf("					<td>\n");
printf("					<input style=\"width:180px;\" name=\"stun_ip\" value=\"");
 ePrint(p.getText("/params/stun/ip")); printf("\"></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>");
 ePrint(ehttp_xml.get("/dnake/voip/stun_port")); printf("</td>\n");
printf("					<td>\n");
printf("					<input style=\"width:64px;\" name=\"stun_port\" value=\"");
 ePrint(p.getInt("/params/stun/port", 5060)); printf("\"></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>&nbsp;</td>\n");
printf("					<td>&nbsp;</td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>");
 ePrint(ehttp_xml.get("/dnake/voip/timeout")); printf("</td>\n");
printf("					<td>\n");
printf("						<select name=\"timeout\" style=\"width:100px;\">\n");
printf("						<option value=\"120\" ");
if(p.getInt("/params/timeout", 0) == 120) ePrint("selected");printf(">120s</option>\n");
printf("						<option value=\"300\" ");
if(p.getInt("/params/timeout", 0) == 300) ePrint("selected");printf(">300s</option>\n");
printf("						<option value=\"600\" ");
if(p.getInt("/params/timeout", 0) == 600) ePrint("selected");printf(">600s</option>\n");
printf("						<option value=\"1200\" ");
if(p.getInt("/params/timeout", 0) == 1200) ePrint("selected");printf(">1200s</option>\n");
printf("						<option value=\"1800\" ");
if(p.getInt("/params/timeout", 0) == 1800) ePrint("selected");printf(">1800s</option>\n");
printf("						</select>\n");
printf("					</td>\n");
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

