#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cgivars.h"
#include "eHttp.h"
#include "dmsg.h"

#include "dmsg.h"

static inline void IpStrip(char *ip)
{
	char *p = ip;
	int dot = 1;

	while (*p) {
		if (*p == '0') {
			if (dot == 1 && *(p+1) != '.' && *(p+1) != 0)
				strcpy(p, p+1);
		} else if (*p == '.')
			dot = 1;
		else
			dot = 0;
		p++;
	}
}

static inline int IpValueOK(const char *p, const char *p2)
{
	char s[32];

	memset(s, 0, sizeof(s));
	memcpy(s, p, p2-p);
	if (atoi(s) > 255)
		return 1;
	return 0;
}

static inline int IpValided(const char *ip)
{
	int c = 0;
	const char *p = ip;

	while (*ip) {
		if (*ip == '.') {
			if (IpValueOK(p, ip))
				return 0;
			p = ip+1;
			if (*(ip+1) != '\0')
				c++;
		}
		ip++;
	}
	if (IpValueOK(p, ip))
		return 0;

	return (c == 3) ? 1 : 0;
}


void process(char **getvars, char **postvars, int form_method)
{
 print_html_header(); 
	dmsg req;
	dxml p;

	req.request("/ui/web/room/read", NULL);
	p.load(req.body());

	if(form_method == POST) {
		int val;
		val = eGetInt("build");
		if (val > 0 && val < 1000)
			p.setInt("/params/build", val);

		val = eGetInt("unit");
		if (val >= 0 && val < 100)
			p.setInt("/params/unit", val);
			
		val = eGetInt("family");
		if(val > 0 && val < 9900){
			int floor = val/100;
			int family = val%100;
			p.setInt("/params/floor", floor);
			p.setInt("/params/family", family);			
		}
	
		val = eGetInt("dcode");
		if (val >= 0 && val < 10)
			p.setInt("/params/dcode", val);

		const char *s;
		s = eGetText("sync");
		if (s != NULL && strlen(s) > 0 && strlen(s) < 16)
			p.setText("/params/sync", s);

		char s2[128];
		strcpy(s2, eGetText("server"));
		IpStrip(s2);
		if (IpValided(s2))
			p.setText("/params/server", s2);

		s = eGetText("passwd");
		if (s != NULL && strlen(s) > 0 && strlen(s) < 16)
			p.setText("/params/passwd", s);

		req.request("/ui/web/room/write", p.data());
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
printf("<form method=\"post\" action=\"room.cgi\">\n");
printf("	<table width=\"90%%\" border=\"0\" id=\"table1\">\n");
printf("		<tr>\n");
printf("			<td class=\"header\"><strong>");
 ePrint(ehttp_xml.get("/dnake/room/title")); printf("</strong></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td><hr></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td>\n");
printf("			<table border=\"0\" id=\"table2\">\n");
printf("				<tr>\n");
printf("					<td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/room/build")); printf("</td>\n");
printf("					<td><input style=\"width:80px;\" name=\"build\" value=\"");
 ePrint(p.getText("/params/build")); printf("\"></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/room/unit")); printf("</td>\n");
printf("					<td>\n");
printf("					<input style=\"width:80px;\" name=\"unit\" value=\"");
 ePrint(p.getText("/params/unit")); printf("\"></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/room/family")); printf("</td>\n");
printf("					<td>\n");
printf("					<input style=\"width:80px;\" name=\"family\" value=\"");
 ePrint(p.getInt("/params/floor",11)*100+p.getInt("/params/family",12)); printf("\"></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/room/dcode")); printf("</td>\n");
printf("					<td>\n");
printf("					<input style=\"width:80px;\" name=\"dcode\" value=\"");
 ePrint(p.getText("/params/dcode")); printf("\"></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/room/sync")); printf("</td>\n");
printf("					<td>\n");
printf("					<input style=\"width:160px;\" name=\"sync\" value=\"");
 ePrint(p.getText("/params/sync")); printf("\"></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>&nbsp;</td>\n");
printf("					<td>&nbsp;</td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/room/server")); printf("</td>\n");
printf("					<td>\n");
printf("					<input style=\"width:160px;\" name=\"server\" value=\"");
 ePrint(p.getText("/params/server")); printf("\"></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/room/passwd")); printf("</td>\n");
printf("					<td>\n");
printf("					<input style=\"width:160px;\" name=\"passwd\" value=\"");
 ePrint(p.getText("/params/passwd")); printf("\"></td>\n");
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

