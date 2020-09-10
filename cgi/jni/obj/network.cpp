#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cgivars.h"
#include "eHttp.h"
#include "dmsg.h"

static inline void IpStrip(char *ip)
{
	const char *p[4];
	char s[128];
	int err = 0;

	strcpy(s, ip);
	p[0] = strtok(s, ".");
	p[1] = strtok(NULL, ".");
	p[2] = strtok(NULL, ".");
	p[3] = strtok(NULL, ".");
	for(int i=0; i<4; i++) {
		if (p[i] == NULL) {
			err = 1;
			break;
		}
	}
	if (!err)
		sprintf(ip, "%d.%d.%d.%d", atoi(p[0]), atoi(p[1]), atoi(p[2]), atoi(p[3]));
	else
		sprintf(ip, "err");
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

static inline int IpValided2(const char *ip, const char *mask, const char *gateway)
{
	in_addr_t _ip, _mask, _gateway;

	_ip = inet_addr(ip);
	_mask = inet_addr(mask);
	_gateway = inet_addr(gateway);

	if ((_gateway & 0xFF000000) == 0x00 || (_gateway & 0xFF000000) == 0xFF000000)
		return 0;
	if ((_ip & 0xFF000000) == 0xFF000000) //½�Ϊ255
		return 0;
	if ((_ip & _mask) == (_gateway & _mask))
		return 1;
	return 0;
}

void process(char **getvars, char **postvars, int form_method)
{
 print_html_header(); 
	dmsg req;
	dxml p;

	req.request("/ui/web/network/read", NULL);
	p.load(req.body());

	if(form_method == POST) {
		char ip[128], mask[128], gateway[128], dns[128];
		int dhcp = eGetInt("dhcp");

		p.setInt("/params/dhcp", dhcp);
		if (!dhcp) {
			strcpy(ip, eGetText("ip"));
			strcpy(mask, eGetText("mask"));
			strcpy(gateway, eGetText("gateway"));
			strcpy(dns, eGetText("dns"));

			IpStrip(ip);
			IpStrip(mask);
			IpStrip(gateway);
			IpStrip(dns);

			if (IpValided(ip) && IpValided(mask) && IpValided(gateway) && IpValided(dns) && IpValided2(ip, mask, gateway)) {
				p.setText("/params/ip", ip);
				p.setText("/params/mask", mask);
				p.setText("/params/gateway", gateway);
				p.setText("/params/dns", dns);
				req.request("/ui/web/network/write", p.data());
			}
		} else
			req.request("/ui/web/network/write", p.data());
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
printf("<form method=\"post\" action=\"network.cgi\">\n");
printf("	<table width=\"90%%\" border=\"0\" id=\"table1\">\n");
printf("		<tr>\n");
printf("			<td class=\"header\"><strong>");
 ePrint(ehttp_xml.get("/dnake/network/title")); printf("</strong></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td><hr></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td>\n");
printf("			<table border=\"0\" id=\"table2\">\n");
printf("				<tr>\n");
printf("					<td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/network/dhcp")); printf("</td>\n");
printf("					<td><input type=\"checkbox\" name=\"dhcp\" value=\"1\" ");
 if (p.getInt("/params/dhcp", 0)) ePrint("checked"); printf("/></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>&nbsp;</td>\n");
printf("					<td>&nbsp;</td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/network/ip")); printf("</td>\n");
printf("					<td><input style=\"width:180px;\" name=\"ip\" value=\"");
 ePrint(p.getText("/params/ip")); printf("\"></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>");
 ePrint(ehttp_xml.get("/dnake/network/mask")); printf("</td>\n");
printf("					<td>\n");
printf("					<input style=\"width:180px;\" name=\"mask\" value=\"");
 ePrint(p.getText("/params/mask")); printf("\"></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>");
 ePrint(ehttp_xml.get("/dnake/network/gateway")); printf("</td>\n");
printf("					<td>\n");
printf("					<input style=\"width:180px;\" name=\"gateway\" value=\"");
 ePrint(p.getText("/params/gateway")); printf("\"></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>");
 ePrint(ehttp_xml.get("/dnake/network/dns")); printf("</td>\n");
printf("					<td>\n");
printf("					<input style=\"width:180px;\" name=\"dns\" value=\"");
 ePrint(p.getText("/params/dns")); printf("\"></td>\n");
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

