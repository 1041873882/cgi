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
    
        //printf("enable = %d\n", eGetInt("action")); 
        p.setInt("/params/tcpdump/enable", eGetInt("action"));
        p.setInt("/params/tcpdump/port", eGetInt("port"));

        req.request("/ui/web/tcpdump/write", p.data());     
    }
printf("    \n");
printf("<!DOCTYPE html>\n");
printf("<html>\n");
printf("\n");
printf("<head>\n");
printf("    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
printf("    <link href=\"/css/style.css\" rel=\"stylesheet\" type=\"text/css\">\n");
printf("    <style>\n");
printf("    .button {\n");
printf("        background-color: #4CAF50; /* Green */\n");
printf("        border: none;\n");
printf("        color: white;\n");
printf("        padding: 15px 32px;\n");
printf("        text-align: center;\n");
printf("        text-decoration: none;\n");
printf("        display: inline-block;\n");
printf("        font-size: 16px;\n");
printf("        margin: 4px 2px;\n");
printf("        cursor: pointer;\n");
printf("    }\n");
printf("\n");
printf("    .button:disabled {  \n");
printf("        opacity: 0.6;\n");
printf("        cursor: not-allowed;\n");
printf("    }\n");
printf("    .Headline {\n");
printf("        font-family: Verdana, Arial, Helvetica, sans-serif;\n");
printf("        font-size: 18px;\n");
printf("        font-weight: bolder;\n");
printf("        color: #4CAF50;\n");
printf("        text-decoration: none;\n");
printf("        line-height:23px;\n");
printf("    }\n");
printf("    </style>\n");
printf("    <script src=\"/js/jquery-1.8.0.min.js\"></script>\n");
printf("    <script>\n");
printf("        var capture_status=0;\n");
printf("    \n");
printf("        //ajax异步提交表单\n");
printf("        function save() {\n");
printf("            var targetUrl = $(\"#post_form\").attr(\"action\");    \n");
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
printf("        }\n");
printf("    \n");
printf("        function downloadFile(url) {\n");
printf("            var aTag = document.createElement(\'a\');\n");
printf("            aTag.download = url;\n");
printf("            aTag.href = \"/cgi-bin/\"+url;\n");
printf("            aTag.click();\n");
printf("        }\n");
printf("        function dosubmit(action) {\n");
printf("            var form = document.getElementById(\'post_form\');\n");
printf("            document.getElementById(\'action\').value=action;\n");
printf("            var fileName = \"proc22.pcap\";\n");
printf("            save();\n");
printf("            button_disabled(action);\n");
printf("            if (action == 0) {\n");
printf("                setTimeout(function() {\n");
printf("                   downloadFile(fileName);\n");
printf("                }, 400);\n");
printf("            }\n");
printf("        } \n");
printf("        function button_disabled(enable) {\n");
printf("            if(enable) {\n");
printf("                document.getElementById(\'start\').disabled = true;\n");
printf("                document.getElementById(\'stop\').disabled = false;\n");
printf("            } else {\n");
printf("                document.getElementById(\'start\').disabled = false;\n");
printf("                document.getElementById(\'stop\').disabled = true;\n");
printf("            }\n");
printf("        }\n");
printf("    </script>\n");
printf("</head>\n");
printf("\n");
printf("<body>\n");
printf("    <div>\n");
printf("        <p class=\"Headline\"><strong>");
 ePrint(ehttp_xml.get("/dnake/tcpdump/title")); printf("</strong></p>\n");
printf("        <hr>\n");
printf("\n");
printf("        <form method=\"post\" action=\"capture.cgi\" id=\"post_form\">\n");
printf("            <input type=\"hidden\" id=\"action\" name=\"action\" value=\"");
 ePrint(p.getText("/params/tcpdump/enable")); printf("\" />\n");
printf("            <p width=\"150\">port:   \n");
printf("            <select name=\"port\" style=\"width:100px;\">\n");
printf("                <option value=\"0\" ");
if(p.getInt("/params/tcpdump/port", 0) == 0) ePrint("selected");printf(">eth0</option>\n");
printf("                <option value=\"1\" ");
if(p.getInt("/params/tcpdump/port", 0) == 1) ePrint("selected");printf(">lo</option>\n");
printf("            </select>\n");
printf("            </p>\n");
printf("        </form><br />\n");
printf("        <input type=\"button\" class=\"button\" id=\"start\" onclick=\"dosubmit(1)\" value=\"Start\" />\n");
printf("        <input type=\"button\" class=\"button\" id=\"stop\" onclick=\"dosubmit(0)\" value=\"Stop\" />\n");
printf("        <br />\n");
printf("        <br />\n");
printf("        <hr>\n");
printf("    </div>\n");
printf("\n");
printf("    <script type=\"text/javascript\">\n");
printf("        var x = document.getElementById(\'action\').value;\n");
printf("\n");
printf("        window.onload = function() {\n");
printf("            button_disabled(x);\n");
printf("        };\n");
printf("                    \n");
printf("        //console.log(555);\n");
printf("    </script>\n");
printf("</body>\n");
printf("\n");
printf("</html>\n");
}

