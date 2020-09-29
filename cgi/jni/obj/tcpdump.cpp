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

    req.request("/ui/web/tcpdump/read", NULL);
    p.load(req.body());
      
    if(form_method == POST) {
    
        //printf("enable = %d\n", eGetInt("sel")); 
        p.setInt("/params/tcpdump/enable", eGetInt("sel"));

        req.request("/ui/web/tcpdump/write", p.data());     
    }
printf("    \n");
printf("<!DOCTYPE html>\n");
printf("<html>\n");
printf("\n");
printf("<head>\n");
printf("    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
printf("    <script src=\"/js/jquery-1.8.0.min.js\"></script>\n");
printf("</head>\n");
printf("<style>\n");
printf("    a {color: #696B83;TEXT-DECORATION: none}\n");
printf("    a:active {background: #AFC1DC}\n");
printf("    .DownButtonNormal{\n");
printf("        height: 28px;\n");
printf("        line-height: 28px;\n");
printf("        padding: 0 11px;\n");
printf("        background: rgb(34, 138, 74);\n");
printf("        border: 1px #E5E7EA solid;\n");
printf("        border-radius: 3px;\n");
printf("        display: inline-block;\n");
printf("        font-size: 12px;\n");
printf("        outline: none;\n");
printf("     }   \n");
printf("</style>\n");
printf("\n");
printf("<script>\n");
printf("    function start() {\n");
printf("        document.getElementById(\"start\").disabled = true;\n");
printf("        \n");
printf("    }\n");
printf("    function stop() {\n");
printf("        document.getElementById(\"start\").disabled = false;\n");
printf("        var $form = $(\'<form method=\"GET\"></form>\');\n");
printf("            $form.attr(\'action\', \'/cgi-bin/proc.pcap\');\n");
printf("            $form.appendTo($(\'body\'));\n");
printf("            $form.submit();\n");
printf("    }\n");
printf("    function ret() {\n");
printf("        if (confirm(\"确认执行吗？\")) {\n");
printf("            return true;\n");
printf("        }\n");
printf("        return false;\n");
printf("    }\n");
printf("    function sel() {\n");
printf("        var x = document.getElementById(stop).value;\n");
printf("        var y = 0;\n");
printf("        \n");
printf("    }\n");
printf("</script>\n");
printf("\n");
printf("<body>\n");
printf("<form onSubmit=\"return ret()\" method=\"post\" action=\"tcpdump.cgi\">\n");
printf("<table width=\"90%%\" border=\"0\" id=\"table1\">\n");
printf("    <tr>\n");
printf("        <td style=\"color:#408080\"><strong>");
 ePrint(ehttp_xml.get("/dnake/tcpdump/title")); printf("</strong></td>\n");
printf("    </tr>\n");
printf("    <tr>\n");
printf("        <td><hr></td>\n");
printf("    </tr>\n");
printf("\n");
printf("    <tr>\n");
printf("        <td><input type=\"radio\" value=\"1\" name=\"sel\" id=\"start\">start\n");
printf("        <input type=\"radio\" value=\"0\" name=\"sel\" id=\"stop\" checked=\"checked\">stop</td>\n");
printf("        <input type=\"hidden\" name=\"enable\" value=\"666\" id=\"yc\" />\n");
printf("    </tr>\n");
printf("    <tr>\n");
printf("        <td>&nbsp;</td>\n");
printf("        <td>&nbsp;</td>\n");
printf("    </tr>\n");
printf("    <tr>\n");
printf("        <td>\n");
printf("            <input type=\"submit\" value=\"execute\">\n");
printf("        </td>\n");
printf("    </tr>\n");
printf("    <tr>\n");
printf("        <td>&nbsp;</td>\n");
printf("        <td>&nbsp;</td>\n");
printf("    </tr>\n");
printf("    <tr>\n");
printf("        <td>\n");
printf("        <a class=\"DownButtonNormal\" name=\"DownLoadHistEvent\" style=\"color:#ffffff\" download=\"proc22.pcap\" href=\"proc22.pcap\">Download</a></td>\n");
printf("    </tr>\n");
printf("    <tr>\n");
printf("        <td>&nbsp;</td>\n");
printf("    </tr>\n");
printf("    <tr>\n");
printf("        <td><hr></td>\n");
printf("    </tr>\n");
printf("</table>\n");
printf("</form>\n");
printf("</body>\n");
printf("\n");
printf("</html>\n");
}

