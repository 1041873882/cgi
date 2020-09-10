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
	char fw[128], talk[128];
	const char *s;
	dmsg req;
	dxml p;

	strcpy(fw, "ERR");
	strcpy(talk, "ERR");

	req.request("/talk/version", NULL);
	p.load(req.body());
	s = p.getText("/params/version");
	if (s) strcpy(fw, s);

	req.request("/ui/version", NULL);
	p.load(req.body());
	s = p.getText("/params/version");
	if (s) strcpy(talk, s);
	int proxy = p.getInt("/params/proxy", 0);

	struct sockaddr_in eth0_addr;
	int eth0 = __local_if_addr("eth0", &eth0_addr);
	struct sockaddr_in eth1_addr;
	int eth1 = __local_if_addr("eth1", &eth1_addr);
	struct sockaddr_in wlan_addr;
	int wlan = __local_if_addr("wlan0", &wlan_addr);
printf("<html>\n");
printf("<head>\n");
printf("  <link href=\"css/style.css\" rel=\"stylesheet\" type=\"text/css\">\n");
printf("  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
printf("  <title>main</title>\n");
printf("</head>\n");
printf("\n");
printf("<body>\n");
printf("<center>\n");
printf("  <tr>\n");
printf("    <td width=\"109\">&nbsp;</td>\n");
printf("  </tr>\n");
printf("  <table border=0 width=90%%>\n");
printf("    <tr><td class=\"header\">\n");
printf("        <p align=\"center\"><strong><font size=\"5\">");
 ePrint(ehttp_xml.get("/dnake/main/title")); printf("</font></strong></td></tr>\n");
printf("    <tr><td><hr></td></tr>\n");
printf("    </table>\n");
printf("</center>\n");
printf("<center>\n");
printf("<table width=\"90%%\" id=\"table1\">\n");
printf("	<tr>\n");
printf("		<td width=\"109\">&nbsp;</td>\n");
printf("		<td width=\"87\">");
 ePrint(ehttp_xml.get("/dnake/main/fw_version")); printf("</td>\n");
printf("		<td align=\"left\">");
 ePrint(fw); printf("</td>\n");
printf("	</tr>\n");
printf("	<tr>\n");
printf("		<td width=\"109\">&nbsp;</td>\n");
printf("		<td width=\"87\">");
 ePrint(ehttp_xml.get("/dnake/main/ui_version")); printf("</td>\n");
printf("		<td align=\"left\">");
 ePrint(talk); printf("</td>\n");
printf("	</tr>\n");
printf("	<tr>\n");
printf("		<td>&nbsp;</td>\n");
printf("		<td>&nbsp;</td>\n");
printf("		<td align=\"left\">&nbsp;</td>\n");
printf("	</tr>\n");
printf("	<tr>\n");
printf("		<td width=\"109\">&nbsp;</td>\n");
printf("		<td width=\"87\">SIP:</td>\n");
printf("		<td align=\"left\">");
 proxy ? ePrint("OK") : ePrint("ERR"); printf("</td>\n");
printf("	</tr>\n");

	if (!eth0) {
printf("\n");
printf("	<tr>\n");
printf("		<td width=\"109\">&nbsp;</td>\n");
printf("		<!-- <td width=\"87\">LAN1:</td> -->  \n");
printf("		<td width=\"87\">ybh_LAN1:</td>\n");
printf("		<td align=\"left\">");
 ePrint(inet_ntoa(eth0_addr.sin_addr)); printf("</td>\n");
printf("	</tr>\n");

}
printf("\n");

	if (!eth1) {
printf("\n");
printf("	<tr>\n");
printf("		<td width=\"109\">&nbsp;</td>\n");
printf("		<td width=\"87\">LAN2:</td>\n");
printf("		<td align=\"left\">");
 ePrint(inet_ntoa(eth1_addr.sin_addr)); printf("</td>\n");
printf("	</tr>\n");

}
printf("\n");

	if (!wlan) {
printf("\n");
printf("	<tr>\n");
printf("		<td width=\"109\">&nbsp;</td>\n");
printf("		<td width=\"87\">WLAN:</td>\n");
printf("		<td align=\"left\">");
 ePrint(inet_ntoa(wlan_addr.sin_addr)); printf("</td>\n");
printf("	</tr>\n");

}
printf("\n");
printf("	<tr>\n");
printf("		<td>&nbsp;</td>\n");
printf("		<td>&nbsp;</td>\n");
printf("		<td align=\"left\">&nbsp;</td>\n");
printf("	</tr>\n");
printf("</table>\n");
printf("</center>\n");
printf("<center>\n");
printf("<table width=\"90%%\">\n");
printf("<tr><td align=\"center\"><hr></td></tr>\n");
printf("<tr><td align=\"center\"></td></tr>\n");
printf("</table>\n");
printf("</center>\n");
printf(" </body>\n");
printf("</html>\n");
}

