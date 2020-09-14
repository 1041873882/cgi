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

        const char *pp1[3]; 
        const char *pp2[3]; 
        char time[128];
        char date[128];
        char hour[12];
        int ntp;
        int y;
        ntp = eGetInt("ntp");
        
        printf("tz = %s\n", eGetText("sel"));
        p.setText("/params/settime/time", eGetText("time")); 
        p.setText("/params/settime/date", eGetText("date")); 
        p.setText("/params/settime/tz", eGetText("sel")); 
        p.setInt("/params/ntp/enable", ntp);
        strcpy(time, eGetText("time"));
        strcpy(date, eGetText("date"));
        pp1[0] = strtok(time, ":");
        pp1[1] = strtok(NULL, ":");
        pp1[2] = strtok(NULL, ":");
        pp2[0] = strtok(date, "-");
        pp2[1] = strtok(NULL, "-");
        pp2[2] = strtok(NULL, "-");  
        
        if (pp1[0] != NULL && atoi(pp1[0]) > 0 && atoi(pp1[0]) < 24 && pp1[1] != NULL && atoi(pp1[1]) > 0 && atoi(pp1[1]) < 60 && 
                pp1[2] != NULL && atoi(pp1[2]) > 0 && atoi(pp1[2]) < 60) {
            p.setText("/params/settime/hour", pp1[0]);
            p.setText("/params/settime/min", pp1[1]);
            p.setText("/params/settime/sec", pp1[2]);

            //printf("hour = %s min = %s sec = %s\n", pp[0], pp[1], pp[2]);
        }

        if (pp2[0] != NULL && strlen(pp2[0]) == 4 && pp2[1] != NULL && atoi(pp2[1]) > 0 && atoi(pp2[1]) < 13 && 
                pp2[2] != NULL && atoi(pp2[2]) > 0 && atoi(pp2[2]) < 31) {

            p.setText("/params/settime/year", pp2[0]);
            p.setText("/params/settime/mon", pp2[1]);
            p.setText("/params/settime/day", pp2[2]);
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
printf("<script>\n");
printf("    function on_sync_button()\n");
printf("    {\n");
printf("        var p = new Date();\n");
printf("        var hour = String(p.getHours());\n");
printf("        var min = String(p.getMinutes());\n");
printf("        var sec = String(p.getSeconds());\n");
printf("        var year = String(p.getFullYear());\n");
printf("        var mon = String(p.getMonth()+1);\n");
printf("        var day = String(p.getDate());\n");
printf("\n");
printf("        document.getElementById(\"time\").value = hour+\":\"+min+\":\"+sec;\n");
printf("        document.getElementById(\"date\").value = year+\"-\"+mon+\"-\"+day;\n");
printf("    }\n");
printf("</script>\n");
printf("\n");
printf("\n");
printf("<body>\n");
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
printf("                </tr>\n");
printf("\n");
printf("                <tr>\n");
printf("                    <td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/time/tz")); printf("</td>\n");
printf("                    <td>\n");
printf("                        <select name=\"sel\" style=\"width:120px;\">\n");
printf("                            <option value=\"+01:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+01:00") == 0) ePrint("selected"); printf(">UTC+1</option>\n");
printf("                            <option value=\"+02:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+02:00") == 0) ePrint("selected"); printf(">UTC+2</option>\n");
printf("                            <option value=\"+03:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+03:00") == 0) ePrint("selected"); printf(">UTC+3</option>\n");
printf("                            <option value=\"+03:30\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+03:30") == 0) ePrint("selected"); printf(">UTC+3:30</option>\n");
printf("                            <option value=\"+04:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+04:00") == 0) ePrint("selected"); printf(">UTC+4</option>\n");
printf("                            <option value=\"+04:30\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+04:30") == 0) ePrint("selected"); printf(">UTC+4:30</option>\n");
printf("                            <option value=\"+05:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+05:00") == 0) ePrint("selected"); printf(">UTC+5</option>\n");
printf("                            <option value=\"+05:30\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+05:30") == 0) ePrint("selected"); printf(">UTC+5:30</option>\n");
printf("                            <option value=\"+05:45\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+05:45") == 0) ePrint("selected"); printf(">UTC+5:45</option>\n");
printf("                            <option value=\"+06:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+06:00") == 0) ePrint("selected"); printf(">UTC+6</option>\n");
printf("                            <option value=\"+06:30\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+06:30") == 0) ePrint("selected"); printf(">UTC+6:30</option>\n");
printf("                            <option value=\"+07:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+07:00") == 0) ePrint("selected"); printf(">UTC+7</option>\n");
printf("                            <option value=\"+08:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+08:00") == 0) ePrint("selected"); printf(">UTC+8</option>\n");
printf("                            <option value=\"+08:30\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+08:30") == 0) ePrint("selected"); printf(">UTC+8:30</option>\n");
printf("                            <option value=\"+08:45\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+08:45") == 0) ePrint("selected"); printf(">UTC+8:45</option>\n");
printf("                            <option value=\"+09:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+09:00") == 0) ePrint("selected"); printf(">UTC+9</option>\n");
printf("                            <option value=\"+09:30\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+09:30") == 0) ePrint("selected"); printf(">UTC+9:30</option>\n");
printf("                            <option value=\"+10:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+10:00") == 0) ePrint("selected"); printf(">UTC+10</option>\n");
printf("                            <option value=\"+10:30\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+10:30") == 0) ePrint("selected"); printf(">UTC+10:30</option>\n");
printf("                            <option value=\"+11:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+11:00") == 0) ePrint("selected"); printf(">UTC+11</option>\n");
printf("                            <option value=\"+12:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+12:00") == 0) ePrint("selected"); printf(">UTC+12</option>\n");
printf("                            <option value=\"+12:45\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+12:45") == 0) ePrint("selected"); printf(">UTC+12:45</option>\n");
printf("                            <option value=\"+13:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+13:00") == 0) ePrint("selected"); printf(">UTC+13</option>\n");
printf("                            <option value=\"+13:45\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+13:45") == 0) ePrint("selected"); printf(">UTC+13:45</option>\n");
printf("                            <option value=\"+14:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+14:00") == 0) ePrint("selected"); printf(">UTC+14</option>\n");
printf("                            <option value=\"+00:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "+00:00") == 0) ePrint("selected"); printf(">UTC+0</option>\n");
printf("                            <option value=\"-01:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "-01:00") == 0) ePrint("selected"); printf(">UTC-1</option>\n");
printf("                            <option value=\"-02:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "-02:00") == 0) ePrint("selected"); printf(">UTC-2</option>\n");
printf("                            <option value=\"-02:30\" ");
 if(strcmp(p.getText("/params/settime/tz"), "-02:30") == 0) ePrint("selected"); printf(">UTC-2:30</option>\n");
printf("                            <option value=\"-03:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "-03:00") == 0) ePrint("selected"); printf(">UTC-3</option>\n");
printf("                            <option value=\"-03:30\" ");
 if(strcmp(p.getText("/params/settime/tz"), "-03:30") == 0) ePrint("selected"); printf(">UTC-3:30</option>\n");
printf("                            <option value=\"-04:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "-04:00") == 0) ePrint("selected"); printf(">UTC-4</option>\n");
printf("                            <option value=\"-05:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "-05:00") == 0) ePrint("selected"); printf(">UTC-5</option>\n");
printf("                            <option value=\"-06:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "-06:00") == 0) ePrint("selected"); printf(">UTC-6</option>\n");
printf("                            <option value=\"-07:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "-07:00") == 0) ePrint("selected"); printf(">UTC-7</option>\n");
printf("                            <option value=\"-08:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "-08:00") == 0) ePrint("selected"); printf(">UTC-8</option>\n");
printf("                            <option value=\"-09:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "-09:00") == 0) ePrint("selected"); printf(">UTC-9</option>\n");
printf("                            <option value=\"-09:30\" ");
 if(strcmp(p.getText("/params/settime/tz"), "-09:30") == 0) ePrint("selected"); printf(">UTC-9:30</option>\n");
printf("                            <option value=\"-10:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "-10:00") == 0) ePrint("selected"); printf(">UTC-10</option>\n");
printf("                            <option value=\"-11:00\" ");
 if(strcmp(p.getText("/params/settime/tz"), "-11:00") == 0) ePrint("selected"); printf(">UTC-11</option>\n");
printf("                        </select>\n");
printf("                    </td>\n");
printf("                </tr>  \n");
printf("                <tr>\n");
printf("					<td>&nbsp;</td>\n");
printf("					<td>&nbsp;</td>\n");
printf("                </tr>           \n");
printf("                <tr>\n");
printf("                    <td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/time/m_time")); printf("</td>\n");
printf("                    <td>\n");
printf("                    <input  type=\"text\" style=\"width:120px;\" name=\"time\" value=\"");
 ePrint(p.getText("/params/settime/time")); printf("\", id=\"time\"></td>\n");
printf("                    <td>\n");
printf("                        <input  type=\"text\" style=\"width:120px;\" name=\"date\" value=\"");
 ePrint(p.getText("/params/settime/date")); printf("\", id=\"date\"></td>\n");
printf("                    <td>\n");
printf("                    <input type=\"button\" value=\"");
 ePrint(ehttp_xml.get("/dnake/sync_time")); printf("\" onClick=\"on_sync_button()\" required></td>\n");
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

