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

    req.request("/ui/web/time/read", NULL);
    p.load(req.body());

    if(form_method == POST) {
        char hour[12];
        int ntp;
        ntp = eGetInt("ntp");

        p.setInt("/params/ntp/enable", ntp);
        if (!ntp) {
            strcpy(hour, eGetText("hour"));
            if (hour != NULL && atoi(hour) > 0 && atoi(hour) < 24) {
                p.setText("/params/settime/hours", hour);
            }
        }        
        req.request("/ui/web/time/write", p.data());
    }
printf("    \n");
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
printf("<form method=\"post\" action=\"time.cgi\">\n");
printf("    <table width=\"90%%\" border=\"0\" id=\"table1\">\n");
printf("        <tr>\n");
printf("            <td class=\"header\"><strong>");
 ePrint(ehttp_xml.get("/dnake/time/title")); printf("</strong></td>\n");
printf("        </tr>\n");
printf("        <tr>\n");
printf("            <td><hr></td>\n");
printf("        </tr>\n");
printf("        <tr>\n");
printf("            <td>\n");
printf("            <table border=\"0\" id=\"table2\">\n");
printf("				<tr>\n");
printf("					<td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/time/ntp")); printf("</td>\n");
printf("					<td><input type=\"checkbox\" name=\"ntp\" value=\"1\" ");
 if (p.getInt("/params/ntp/enable", 0)) ePrint("checked"); printf("/></td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>&nbsp;</td>\n");
printf("					<td>&nbsp;</td>\n");
printf("				</tr>\n");
printf("                <tr>\n");
printf("                    <td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/time/hour")); printf("</td>\n");
printf("                    <td>\n");
printf("                    <input style=\"width:80px;\" name=\"hour\" value=\"");
 ePrint(p.getText("/params/settime/hours")); printf("\"></td>\n");
printf("                </tr>\n");
printf("                <tr>\n");
printf("                    <td>&nbsp;</td>\n");
printf("                    <td>&nbsp;</td>\n");
printf("                </tr>\n");
printf("                </table>\n");
printf("            </td>\n");
printf("        </tr>\n");
printf("        <tr>\n");
printf("            <td><hr></td>\n");
printf("        </tr>\n");
printf("        <tr>\n");
printf("            <td>\n");
printf("            <input type=\"submit\" value=\"");
 ePrint(ehttp_xml.get("/dnake/submit")); printf("\"></td>\n");
printf("        </tr>\n");
printf("    </table>\n");
printf("</form>\n");
printf("\n");
printf("</body>\n");
printf("</html>\n");
printf("    ");
}

