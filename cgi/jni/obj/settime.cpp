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

    req.request("/ui/web/settime/read", NULL);
    p.load(req.body());

    char mDstStart[24] = {};
    char mDstEnd[24] = {};
    char mYear[24] = {};
    char mMon[24] = {};
    char mDay[24] = {};
    char mHour[24] = {};
    char mMin[24] = {};
    char mSec[24] = {};

    sscanf(p.getText("/params/settime/settime"), "%[^-]-%[^-]-%[^ ] %[^:]:%[^:]:%[^:]", mYear, mMon, mDay, mHour, mMin, mSec);

    if(form_method == POST) {
        p.setText("/params/settime/tz", eGetText("setTimeZone")); 
        p.setText("/params/ntp/server", eGetText("server"));
        p.setInt("/params/ntp/enable", eGetInt("ntp"));
        p.setInt("/params/settime/hour_24", eGetInt("hour_24"));
        p.setInt("/params/settime/date", eGetInt("date_format"));

        char setTime[32] = {};
        int err = 0;
        int t0 = eGetInt("set_hour");
        int t1 = eGetInt("set_min");
        int t2 = eGetInt("set_second");
        int t3 = eGetInt("set_year");
        int t4 = eGetInt("set_mon");
        int t5 = eGetInt("set_day");

        if (t0 < 0 || t0 > 23 || t1 < 0 || t1 > 59 || t2 < 0 || t2 > 59 ||
                t3 < 1970 || t3 > 2034 || t4 < 1 || t4 > 12 || t5 < 0) {
            err = 1;
        }

        /* 判断是否为闰年 */
        if (t4 == 4 || t4 == 6 || t4 == 9 || t4 == 11) {
            if (t5 > 30) 
                err = 1;
        } else if (t4 != 2) {
            if (t5 > 31)
                err = 1;
        }
        if (t3 % 400 == 0 || (t3 % 4 == 0 && t3 % 100 != 0)) {
            if (t4 == 2) {
                if (t5 > 29) 
                   err = 1;
            }
        } else {
            if (t4 == 2) {
                if (t5 > 28) 
                    err = 1;
            }
        }

        if (!err) {
            sprintf(setTime, "%04d-%02d-%02d %02d:%02d:%02d", t3, t4, t5, t0, t1, t2);     
            printf("time=%s\n", setTime);
            p.setText("/params/settime/settime", setTime);
        }
        
        sprintf(mDstStart, "%d.%d.%d/%02d", eGetInt("startMon"), eGetInt("startWeek"), eGetInt("startDay"), eGetInt("startHour"));
        sprintf(mDstEnd, "%d.%d.%d/%02d", eGetInt("endMon"), eGetInt("endWeek"), eGetInt("endDay"), eGetInt("endHour"));

        p.setInt("/params/dst/enable", eGetInt("dstEnable"));
        
        if (eGetInt("dstEnable") == 1) {
            p.setText("/params/dst/start", mDstStart);
            p.setText("/params/dst/end", mDstEnd);
            p.setInt("/params/dst/bias", eGetInt("bias"));
        }
        req.request("/ui/web/settime/write", p.data());
        printf("%d", t3);    
    }

printf("    \n");
printf("<html>\n");
printf("\n");
printf("<head>\n");
printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
printf("<style type=\"text/css\">\n");
printf("    .table {\n");
printf("        border-collapse: separate;\n");
printf("        border-spacing: 10px 10px\n");
printf("    }\n");
printf("    .input {\n");
printf("        text-align:center;\n");
printf("    }\n");
printf("    select {\n");
printf("        text-align: center;\n");
printf("        text-align-last: center;\n");
printf("    }\n");
printf("</style>\n");
printf("<script src=\"/js/jquery-1.8.0.min.js\"></script>\n");
printf("<script>\n");
printf("\n");
printf("    var strMonth=[\"\", \"January\", \"February\", \"March\", \"April\", \"May\", \"June\", \"July\",\n");
printf("        \"August\", \"September\", \"October\", \"November\", \"December\"];\n");
printf("\n");
printf("    var strDay=[\"Sunday\", \"Monday\", \"Tuesday\", \"Wednesday\",\n");
printf("        \"Thursday\", \"Friday\", \"Saturday\"];\n");
printf("\n");
printf("    var strWeek=[\"\", \"First In Month\", \"Second In Month\", \"Third In Month\",\n");
printf("        \"Fourth In Month\", \"Last In Month\"];\n");
printf("\n");
printf("    var dstBias=[\"30\", \"60\", \"90\", \"120\", \"150\", \"180\", \"210\", \"240\"];\n");
printf("    var packet_name=\"\";\n");
printf("\n");
printf("    var timeZone=[\"-12:00\", \"-11:00\", \"-10:00\", \"-09:30\", \"-09:00\", \"-08:00\",\n");
printf("        \"-07:00\", \"-06:00\", \"-05:00\", \"-04:00\", \"-03:30\", \"-03:00\", \"-02:00\",\n");
printf("        \"-01:00\", \"+00:00\", \"+01:00\", \"+02:00\", \"+03:00\", \"+04:00\", \"+04:30\",\n");
printf("        \"+05:00\", \"+05:30\", \"+05:45\", \"+06:00\", \"+06:30\", \"+07:00\", \"+08:00\",\n");
printf("        \"+08:45\", \"+09:00\", \"+09:30\", \"+10:00\", \"+10:30\", \"+11:00\", \"+12:00\",\n");
printf("        \"+12:45\", \"+13:00\", \"+14:00\"];\n");
printf("\n");
printf("    var myBias= ");
 ePrint(p.getInt("/params/dst/bias", 30)); printf(";\n");
printf("    var myTimeZone = \"");
 ePrint(p.getText("/params/settime/tz", "+08:00")); printf("\";\n");
printf("    var startTime = \"");
 ePrint(p.getText("/params/dst/start", "1.1.1/01")); printf("\";\n");
printf("    var endTime = \"");
 ePrint(p.getText("/params/dst/end", "1.1.1/02")); printf("\";\n");
printf("\n");
printf("    function save() {\n");
printf("        var targetUrl = $(\"#post_form\").attr(\"action\");    \n");
printf("            var data = $(\"#post_form\").serialize();     \n");
printf("            $.ajax({ \n");
printf("                type:\'post\',  \n");
printf("                url:targetUrl, \n");
printf("                cache: false,\n");
printf("                data:data,  //重点必须为一个变量如：data\n");
printf("                dataType:\'json\',  //预期服务器返回的数据类型JSON\n");
printf("                success:function(data){      \n");
printf("                },\n");
printf("                error:function(){ \n");
printf("                }\n");
printf("            })\n");
printf("            setTimeout(function () {\n");
printf("				downloadFile(packet_name);\n");
printf("			}, 600);\n");
printf("\n");
printf("        location.replace(\"settime.cgi\");\n");
printf("   \n");
printf("            console.log(\"submit ok\");\n");
printf("        }\n");
printf("\n");
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
printf("        document.getElementById(\"set_hour\").value = hour;\n");
printf("        document.getElementById(\"set_min\").value = min;\n");
printf("        document.getElementById(\"set_second\").value = sec;\n");
printf("        document.getElementById(\"set_year\").value = year;\n");
printf("        document.getElementById(\"set_mon\").value = mon;\n");
printf("        document.getElementById(\"set_day\").value = day;\n");
printf("    }\n");
printf("    function text_disabled(action) {\n");
printf("        if (action == 1) {\n");
printf("            document.getElementById(\"ntp\").checked = true;\n");
printf("        } else {\n");
printf("            document.getElementById(\"set_hour\").readOnly = false;\n");
printf("            document.getElementById(\"set_min\").readOnly = false;\n");
printf("            document.getElementById(\"set_second\").readOnly = false;\n");
printf("            document.getElementById(\"set_year\").readOnly = false;\n");
printf("            document.getElementById(\"set_mon\").readOnly = false;\n");
printf("            document.getElementById(\"set_day\").readOnly = false;\n");
printf("        }\n");
printf("    }\n");
printf("\n");
printf("    function preFixZero(num, n) {\n");
printf("        return (Array(n).join(0) + num).slice(-n);\n");
printf("    }\n");
printf("\n");
printf("    function selected_timezone(action) {\n");
printf("        for (var i = 0; i < timeZone.length; i++) {\n");
printf("            if(timeZone[i] == action) {\n");
printf("                document.getElementById(\"setTimeZone\").options[i].selected = true;\n");
printf("                break;\n");
printf("            }\n");
printf("        }\n");
printf("    }\n");
printf("\n");
printf("    function selected_dstBias(action) {\n");
printf("        for (var i = 0; i < dstBias.length; i++) {\n");
printf("            if(dstBias[i] == action) {\n");
printf("                document.getElementById(\"bias\").options[i].selected = true;\n");
printf("                break;\n");
printf("            }\n");
printf("        }\n");
printf("    }\n");
printf("\n");
printf("    function selected_dst(selectedId, action) {\n");
printf("        var select = document.getElementById(selectedId);\n");
printf("	    select.options[action].selected = true;\n");
printf("    }\n");
printf("\n");
printf("    function setInit() {\n");
printf("        var endTimeStr    = endTime.replace(/\\//g, \'.\');\n");
printf("	    var startTimeStr  = startTime.replace(/\\//g, \'.\');\n");
printf("        var endTimeInfo   = endTimeStr.split(\'.\');\n");
printf("	    var startTimeInfo = startTimeStr.split(\'.\');\n");
printf("        console.log(startTimeInfo[0]-1);\n");
printf("        console.log(startTimeInfo[1]-1);\n");
printf("        console.log(startTimeInfo[2]);\n");
printf("\n");
printf("        selected_timezone(myTimeZone);\n");
printf("        selected_dstBias(myBias);\n");
printf("        selected_dst(\"startMon\", parseInt(startTimeInfo[0]-1));\n");
printf("        selected_dst(\"startWeek\", parseInt(startTimeInfo[1]-1));\n");
printf("        selected_dst(\"startDay\", parseInt(startTimeInfo[2]));\n");
printf("        selected_dst(\"startHour\", parseInt(startTimeInfo[3]));\n");
printf("        selected_dst(\"endMon\", parseInt(endTimeInfo[0]-1));\n");
printf("        selected_dst(\"endWeek\", parseInt(endTimeInfo[1]-1));\n");
printf("        selected_dst(\"endDay\", parseInt(endTimeInfo[2]));\n");
printf("        selected_dst(\"endHour\", parseInt(endTimeInfo[3]));\n");
printf("    }\n");
printf("</script>\n");
printf("<link href=\"/css/style.css\" rel=\"stylesheet\" type=\"text/css\">\n");
printf("</head>\n");
printf("\n");
printf("\n");
printf("<body>\n");
printf("<form method=\"post\" action=\"settime.cgi\" id=\"post_form\">\n");
printf("    <input type=\"hidden\" id=\"action\" name=\"action\" value=\"");
 ePrint(p.getText("/params/ntp/enable")); printf("\" />\n");
printf("    <table width=\"90%%\" border=\"0\" id=\"table1\" class=\"table\">\n");
printf("        <tr>\n");
printf("            <td class=\"header\"><strong>");
 ePrint(ehttp_xml.get("/dnake/time/title")); printf("</strong></td>\n");
printf("        </tr>\n");
printf("        <tr>\n");
printf("            <td><hr></td>       \n");
printf("        </tr>\n");
printf("    </table>\n");
printf("    <table border=\"0\" id=\"table2\" class=\"table\">\n");
printf("        <tr>\n");
printf("            <td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/time/ntp")); printf("</td>\n");
printf("            <td><input type=\"checkbox\" name=\"ntp\" id=\"ntp\" value=\"1\" /></td>\n");
printf("        </tr>\n");
printf("        <tr>\n");
printf("            <td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/time/server")); printf("</td>\n");
printf("            <td>\n");
printf("                <input type=\"text\" class=\"input\" style=\"width:180px;\" name=\"server\" value=\"");
 ePrint(p.getText("/params/ntp/server")); printf("\" id=\"server\">\n");
printf("            </td>\n");
printf("        </tr>\n");
printf("        <tr>\n");
printf("            <td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/time/hour_24")); printf("</td>\n");
printf("            <td><input type=\"checkbox\" name=\"hour_24\" value=\"1\" ");
 if (p.getInt("/params/settime/hour_24", 0)) ePrint("checked"); printf(" /></td>\n");
printf("        </tr>\n");
printf("        <tr>\n");
printf("            <td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/time/tz")); printf("</td>\n");
printf("            <td>\n");
printf("                <select name=\"setTimeZone\" id=\"setTimeZone\" class=\"input\" style=\"width:180px;\">\n");
printf("                    <script>\n");
printf("                        for (var i = 0; i < timeZone.length; i++) {\n");
printf("                            document.write(\"<option value=\'\" + timeZone[i] + \"\'>\" + \"UTC\" + timeZone[i] + \"</option>\");\n");
printf("                        }\n");
printf("                    </script>\n");
printf("                </select>\n");
printf("            </td>\n");
printf("        </tr>  \n");
printf("        <tr>\n");
printf("            <td>&nbsp;</td>\n");
printf("            <td>&nbsp;</td>\n");
printf("        </tr>           \n");
printf("        <tr>\n");
printf("            <td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/time/sync_pc")); printf("</td>\n");
printf("            <td>\n");
printf("                <input type=\"button\" value=\"");
 ePrint(ehttp_xml.get("/dnake/sync_time")); printf("\" onClick=\"on_sync_button()\" required>\n");
printf("            </td>\n");
printf("        </tr>\n");
printf("        <tr>\n");
printf("            <td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/time/hour")); printf("</td>\n");
printf("            <td>\n");
printf("                <input  type=\"text\" readOnly  class=\"input\" style=\"width:50;\" name=\"set_hour\" value=\"");
 ePrint(mHour); printf("\" id=\"set_hour\">  :\n");
printf("                <input  type=\"text\" readOnly class=\"input\" style=\"width:50;\" name=\"set_min\" value=\"");
 ePrint(mMin); printf("\" id=\"set_min\">  :\n");
printf("                <input  type=\"text\" readOnly class=\"input\" style=\"width:50;\" name=\"set_second\" value=\"");
 ePrint(mSec); printf("\" id=\"set_second\">\n");
printf("            </td>\n");
printf("        </tr>\n");
printf("        <tr>\n");
printf("            <td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/time/date_format")); printf("</td>\n");
printf("            <td>\n");
printf("                <select name=\"date_format\" style=\"width:180px;\">\n");
printf("                    <option value=\"0\" ");
 if(p.getInt("/params/settime/date", 0) == 0) ePrint("selected"); printf(">DD/MM/YYYY</option>\n");
printf("                    <option value=\"1\" ");
 if(p.getInt("/params/settime/date", 0) == 1) ePrint("selected"); printf(">MM/DD/YYYY</option>\n");
printf("                    <option value=\"2\" ");
 if(p.getInt("/params/settime/date", 0) == 2) ePrint("selected"); printf(">YYYY/MM/DD</option>\n");
printf("                </select>   \n");
printf("            </td>\n");
printf("        </tr>\n");
printf("        <tr>\n");
printf("            <td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/time/date")); printf("</td>\n");
printf("            <td>\n");
printf("                <input readOnly class=\"input\" style=\"width:50;\" name=\"set_year\" value=\"");
 ePrint(mYear); printf("\" id=\"set_year\"> /\n");
printf("                <input readOnly class=\"input\" style=\"width:50;\" name=\"set_mon\" value=\"");
 ePrint(mMon); printf("\" id=\"set_mon\"> /\n");
printf("                <input readOnly class=\"input\" style=\"width:50;\" name=\"set_day\" value=\"");
 ePrint(mDay); printf("\" id=\"set_day\">\n");
printf("            </td>\n");
printf("        </tr>\n");
printf("        <tr>\n");
printf("            <td>&nbsp;</td>\n");
printf("            <td>&nbsp;</td>\n");
printf("        </tr>   \n");
printf("        <tr>\n");
printf("            <td>");
 ePrint(ehttp_xml.get("/dnake/dst/enable")); printf("</td>\n");
printf("            <td><input type=\"checkbox\" id=\"dstEnable\" name=\"dstEnable\" value=\"1\" ");
 if (p.getInt("/params/dst/enable", 0)) ePrint("checked"); printf("/></td>\n");
printf("        </tr>\n");
printf("        <tbody id=\"Dst\">\n");
printf("            <tr>\n");
printf("                <td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/dst/start")); printf("</td>\n");
printf("                <td>\n");
printf("                    <select name=\"startMon\" id=\"startMon\" style=\"width:110px;\">\n");
printf("                        <script>\n");
printf("                            for (var i=1; i<=12; i++) {\n");
printf("								document.write(\"<option value=\'\" + i + \"\'>\" + strMonth[i] + \"</option>\");\n");
printf("							}\n");
printf("                        </script>\n");
printf("                    </select>\n");
printf("                    <select name=\"startWeek\" id=\"startWeek\" style=\"width:110px;\">\n");
printf("                        <script>\n");
printf("                            for (var i=1; i<=7; i++) {\n");
printf("								document.write(\"<option value=\'\" + i + \"\'>\" + strWeek[i] + \"</option>\");\n");
printf("							}\n");
printf("                        </script>\n");
printf("                    </select>\n");
printf("                    <select name=\"startDay\" id=\"startDay\" style=\"width:110px;\">\n");
printf("                        <script>\n");
printf("                            for (var i=0; i<7; i++) {\n");
printf("								document.write(\"<option value=\'\" + i + \"\'>\" + strDay[i] + \"</option>\");\n");
printf("							}\n");
printf("                        </script>\n");
printf("                    </select>\n");
printf("                    <select id=\"startHour\" name=\"startHour\" style=\"width:110px\">\n");
printf("                        <script>\n");
printf("                            for (var i=0; i<=23; i++) {\n");
printf("                                document.write(\"<option value=\'\" + i + \"\'>\" + preFixZero(i, 2) + \":00\" + \"</option>\");\n");
printf("                            }\n");
printf("                        </script>\n");
printf("                    </select>\n");
printf("                </td>\n");
printf("            </tr>\n");
printf("            <tr>\n");
printf("                <td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/dst/end")); printf("</td>\n");
printf("                <td>\n");
printf("                    <select name=\"endMon\" id=\"endMon\" style=\"width:110px;\">\n");
printf("                        <script>\n");
printf("                            for (var i=1; i<=12; i++) {\n");
printf("								document.write(\"<option value=\'\" + i + \"\'>\" + strMonth[i] + \"</option>\");\n");
printf("							}\n");
printf("                        </script>\n");
printf("                    </select>\n");
printf("                    <select name=\"endWeek\" id=\"endWeek\" style=\"width:110px;\">\n");
printf("                        <script>\n");
printf("                            for (var i=1; i<=7; i++) {\n");
printf("								document.write(\"<option value=\'\" + i + \"\'>\" + strWeek[i] + \"</option>\");\n");
printf("							}\n");
printf("                        </script>\n");
printf("                    </select>\n");
printf("                    <select name=\"endDay\" id=\"endDay\" style=\"width:110px;\">\n");
printf("                        <script>\n");
printf("                            for (var i=0; i<7; i++) {\n");
printf("								document.write(\"<option value=\'\" + i + \"\'>\" + strDay[i] + \"</option>\");\n");
printf("							}\n");
printf("                        </script>\n");
printf("                    </select>\n");
printf("                    <select id=\"endHour\" name=\"endHour\" style=\"width:110px\">\n");
printf("                        <script>\n");
printf("                            for (var i=0; i<=23; i++) {\n");
printf("                                document.write(\"<option value=\'\" + i + \"\'>\" + preFixZero(i, 2) + \":00\" + \"</option>\");\n");
printf("                            }\n");
printf("                        </script>\n");
printf("                    </select>\n");
printf("                    </select>\n");
printf("                </td>\n");
printf("            </tr>\n");
printf("        </tbody>\n");
printf("        <tr>\n");
printf("            <td width=\"96\">");
 ePrint(ehttp_xml.get("/dnake/dst/bias")); printf("</td>\n");
printf("            <td>\n");
printf("                <select id=\"bias\" name=\"bias\" style=\"width:110px\">\n");
printf("                    <script>\n");
printf("                        for (var i=0; i < dstBias.length; i++) {\n");
printf("                            document.write(\"<option value=\'\" + dstBias[i] + \"\'>\" + dstBias[i] + \"min\" + \"</option>\");\n");
printf("                        }\n");
printf("                    </script>\n");
printf("                </select>                   \n");
printf("            </td>\n");
printf("        </tr>\n");
printf("        <tr>\n");
printf("            <td>&nbsp;</td>\n");
printf("        </tr>   \n");
printf("    </table>\n");
printf("    <table width=\"90%%\" border=\"0\" id=\"table3\" class=\"table\">\n");
printf("        <tr>\n");
printf("            <td><hr></td>\n");
printf("        </tr>\n");
printf("        <tr>\n");
printf("            <td>\n");
printf("            <input type=\"button\" onclick=\"save()\" value=\"");
 ePrint(ehttp_xml.get("/dnake/submit")); printf("\"></td>\n");
printf("        </tr>\n");
printf("    </table>\n");
printf("    <script type=\"text/javascript\">\n");
printf("        var x = document.getElementById(\'action\').value;\n");
printf("        window.onload = function() {\n");
printf("            text_disabled(x);\n");
printf("            setInit();\n");
printf("        };\n");
printf("    </script>\n");
printf("</form>\n");
printf("\n");
printf("</body>\n");
printf("</html>\n");
printf("    ");
}

