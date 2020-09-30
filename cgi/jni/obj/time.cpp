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

        const char *pp[6];
        char *pp1[6]; 

        char time[128];
        int ntp;
        ntp = eGetInt("ntp");
        
        //printf("sel = %s\n", eGetText("sel"));
        p.setText("/params/settime/tz", eGetText("sel")); 
        p.setInt("/params/ntp/enable", ntp);
        strcpy(time, eGetText("time"));
              
        int t0 = -1;
        int t1 = -1;
        int t2 = -1;
        int t3 = -1;
        int t4 = -1;
        int t5 = -1;

        pp[0] = strtok(time, "-");
        pp[1] = strtok(NULL, "-");
        pp[2] = strtok(NULL, " ");
        pp[3] = strtok(NULL, ":");
        pp[4] = strtok(NULL, ":");
        pp[5] = strtok(NULL, ":");  
    
    
        if (pp[0] != NULL && strlen(pp[0]) == 4 && pp[1] != NULL && (strlen(pp[1]) == 1 || strlen(pp[1]) == 2) &&
                pp[2] != NULL && (strlen(pp[2]) == 1 || strlen(pp[2]) == 2) && pp[3] != NULL && (strlen(pp[3]) == 1 || strlen(pp[3]) == 2) && 
                    pp[4] != NULL && (strlen(pp[4]) == 1||strlen(pp[4]) == 2) && pp[5] != NULL && (strlen(pp[5]) == 1 || strlen(pp[5]) == 2)) {  
            t0 = atoi(pp[0]);
            t1 = atoi(pp[1]);
            t2 = atoi(pp[2]);
            t3 = atoi(pp[3]);
            t4 = atoi(pp[4]);
            t5 = atoi(pp[5]);
        }
    
        if (t0 >= 1970 && t0 <= 2037 && t1 >= 1 && t1 < 12 && t2 >= 1 && t2 < 31 && 
                t3 >= 0 && t3 < 24 && t4 >= 0 && t4 < 60 && t5 >= 0 && t5 < 60) {
            p.setText("/params/settime/time", eGetText("time"));    //这里必须先放前面，否者会出现问题
            p.setText("/params/settime/year",pp[0]);
            p.setText("/params/settime/mon",pp[1]);
            p.setText("/params/settime/date",pp[2]);
            p.setText("/params/settime/hour",pp[3]);
            p.setText("/params/settime/min",pp[4]);
            p.setText("/params/settime/sec",pp[5]);
            
        }
        req.request("/ui/web/time/write", p.data());     
    }
printf("    \n");
printf("<html>\n");
printf("\n");
printf("<head>\n");
printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
printf("<SCRIPT src=\"/ie3d.js\"></SCRIPT>\n");
printf("<SCRIPT src=\"/ToolboxClient.js\"></SCRIPT>\n");
printf("<SCRIPT src=\"/Toolbox.js\"></SCRIPT>\n");
printf("<link href=\"/css/style.css\" rel=\"stylesheet\" type=\"text/css\">\n");
printf("<style>\n");
printf("    a:link,a:visited\n");
printf("    {\n");
printf("        display:block;\n");
printf("        font-weight:bold;\n");
printf("        color:#FFFFFF;\n");
printf("        background-color:#98bf21;\n");
printf("        width:120px;\n");
printf("        text-align:center;\n");
printf("        padding:4px;\n");
printf("        text-decoration:none;\n");
printf("    }\n");
printf("    a:hover,a:active\n");
printf("    {\n");
printf("        background-color:#000000;\n");
printf("    }\n");
printf("    </style>\n");
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
printf("        document.getElementById(\"time\").value = year+\"-\"+mon+\"-\"+day+\" \"+hour+\":\"+min+\":\"+sec;\n");
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
printf("            <td><hr></td>       \n");
printf("        </tr>\n");
printf("        <tr>\n");
printf("            <td>\n");
printf("            <table border=\"0\" id=\"table2\">\n");
printf("                <tr>            \n");
printf("                    <td><a href=\"/cgi-bin/time.cgi\" target=\"main\" >Time</a></td>\n");
printf("                    <td><a href=\"/cgi-bin/dst.cgi\" target=\"main\" >DST</a></td>\n");
printf("                </tr>\n");
printf("                <tr>\n");
printf("					<td>&nbsp;</td>\n");
printf("					<td>&nbsp;</td>\n");
printf("                </tr>\n");
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
printf("                        <select name=\"sel\" style=\"width:180px;\">\n");
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
printf("                        <input  type=\"text\" style=\"width:180px;\" name=\"time\" value=\"");
 ePrint(p.getText("/params/settime/time")); printf("\" id=\"time\">\n");
printf("                    </td>\n");
printf("                    <td><input type=\"button\" value=\"");
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

