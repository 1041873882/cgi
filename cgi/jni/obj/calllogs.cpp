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

    req.request("/ui/web/calllogs/read", NULL);
    p.load(req.body());

    if(form_method == POST) {

        

        req.request("/ui/web/calllogs/write", p.data());     
    }
printf("    \n");
printf("<html>\n");
printf("\n");
printf("<head>\n");
printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
printf("<style type=\"text/css\">\n");
printf("    .table11_3 table {\n");
printf("        width:100%%;\n");
printf("        margin:15px 0;\n");
printf("        border:0;\n");
printf("       \n");
printf("    }\n");
printf("    .table11_3 th {\n");
printf("        background-color:rgb(170, 172, 170);\n");
printf("        font-weight: normal;\n");
printf("        text-align:center;\n");
printf("    }\n");
printf("    .table11_3,.table11_3 th,.table11_3 td {\n");
printf("        font-size:0.95em;\n");
printf("        padding:4px;\n");
printf("        border-collapse:collapse;\n");
printf("        word-wrap: break-word;        \n");
printf("    }\n");
printf("    .table11_3 th,.table11_3 td {\n");
printf("        border-width:5px 0 5px 0;\n");
printf("        border:2px inset #ffffff;\n");
printf("        line-height:2em;\n");
printf("    }\n");
printf("\n");
printf("    .table11_3 td {\n");
printf("        text-align:center;\n");
printf("    }\n");
printf("\n");
printf("    .table11_3 tr {\n");
printf("        border: 1px solid #ffffff;\n");
printf("    }\n");
printf("    /* .table11_3 tr:hover {\n");
printf("        background-color: #FF69B4;\n");
printf("    } */\n");
printf("\n");
printf("</style>\n");
printf("<script src=\"/js/jquery-1.8.0.min.js\"></script>\n");
printf("<script>\n");
printf("function Page(iAbsolute, sTableId, sTBodyId,sPageId) {\n");
printf("    this.absolute = iAbsolute; //每页最大记录数\n");
printf("    this.tableId = sTableId;\n");
printf("    this.tBodyId = sTBodyId;\n");
printf("    this.rowCount = 0; //记录数\n");
printf("    this.pageCount = 0; //页数\n");
printf("    this.pageIndex = 0; //页索引\n");
printf("    this.__oTable__ = null; //表格引用\n");
printf("    this.__oTBody__ = null; //要分页内容\n");
printf("    this.__dataRows__ = 0; //记录行引用\n");
printf("    this.__oldTBody__ = null;\n");
printf("    this.pageId = sPageId;//显示当前页数的span的ID\n");
printf("\n");
printf("    this.__init__(); //初始化;   \n");
printf("};\n");
printf("\n");
printf("function loadXMLDoc(dname) {\n");
printf("    if (window.XMLHttpRequest) {\n");
printf("        xhttp = new XMLHttpRequest();\n");
printf("    }else {\n");
printf("        xhttp = new ActiveXObject(\"Microsoft.XMLHTTP\");\n");
printf("    }\n");
printf("    xhttp.open(\"GET\", dname, false);\n");
printf("    xhttp.send(\"\");\n");
printf("    return xhttp.responseXML;\n");
printf("}\n");
printf("function selectAll(sel) {\n");
printf("    let selects = document.getElementsByName(\"select\");\n");
printf("    for (let select of selects ) {\n");
printf("        select.checked = sel.checked;\n");
printf("    }\n");
printf("    let sels = document.getElementsByName(\"selAll\");\n");
printf("    for (let selAll of sels) {\n");
printf("        selAll.checked = sel.checked;\n");
printf("    }\n");
printf("}\n");
printf("\n");
printf("function delSel(del) {\n");
printf("    let selects = document.getElementsByName(\"select\");\n");
printf("    if (!del) {\n");
printf("        for (let i=0;i<selects.length;i++) {\n");
printf("            selects[i].parentNode.parentNode.parentNode.removeChild(selects[i].parentNode.parentNode);\n");
printf("                i--;\n");
printf("        }\n");
printf("    } else {\n");
printf("        for (let i=0;i<selects.length;i++) {\n");
printf("            if(selects[i].checked){\n");
printf("                selects[i].parentNode.parentNode.parentNode.removeChild(selects[i].parentNode.parentNode);\n");
printf("                i--;\n");
printf("            }\n");
printf("        }\n");
printf("    }\n");
printf("}\n");
printf("\n");
printf("function ReadXml() {\n");
printf("    var xmldoc = loadXMLDoc(\"/cgi-bin/talk.xml\");\n");
printf("    //获得指定节点\n");
printf("    var divmsg = document.getElementById(\"xmlMsg\");\n");
printf("    var msg = \"<table id=\'mytable\' width=\'90%%\' class=\'table11_3\'><tr><th>Index</th><th>Room NO.</th><th>type</th><th>Local Time</th><th>Destination</th><td style=\'border:none\'><input type=\'checkbox\' name=\'selAll\' onclick=\'selectAll(this)\'></td><tr>\";\n");
printf("    var iii = xmldoc.getElementsByTagName(\"max\")[0].firstChild.nodeValue;\n");
printf("    \n");
printf("    console.log(iii);\n");
printf("\n");
printf("    var max = xmldoc.getElementsByTagName(\"d0\");\n");
printf("    for (var i = 0; i < iii; i++) {\n");
printf("        var d = \"d\" + i;\n");
printf("        var x = i+1;\n");
printf("        nodes = xmldoc.getElementsByTagName(d)[0];\n");
printf("        msg += \"<tr>\";\n");
printf("        msg += \"<td>\" + x + \"</td>\";\n");
printf("        msg += \"<td>\" + nodes.getElementsByTagName(\"id\")[0].firstChild.nodeValue + \"</td>\";\n");
printf("        msg += \"<td>\" + nodes.getElementsByTagName(\"timeout\")[0].firstChild.nodeValue + \"</td>\";\n");
printf("        msg += \"<td>\" + nodes.getElementsByTagName(\"timeout\")[0].firstChild.nodeValue + \"</td>\";\n");
printf("        msg += \"<td>\" + nodes.getElementsByTagName(\"timeout\")[0].firstChild.nodeValue + \"</td>\";\n");
printf("        msg += \"<td style=\'border:none\'>\" + \"<input type=\'checkbox\' name=\'select\' value=\'1\'>\" + \"</td>\";\n");
printf("        msg += \"</tr>\";\n");
printf("        // nodes[i] = xmldoc.getElementsByTagName(d);\n");
printf("    }\n");
printf("    msg += \"<tr>\";\n");
printf("    msg += \"<th colspan=\'5\'>\";\n");
printf("    msg += \"<button type=\'button\'>Prev</button>\";\n");
printf("    msg += \"<button type=\'button\'>Prev</button>\";\n");
printf("    msg += \"<button type=\'button\'>Prev</button>\";\n");
printf("    msg += \"<button type=\'button\' onclick=\'delSel(0)\'>Delete All</button>\"\n");
printf("    msg += \"<button type=\'button\' onclick=\'delSel(1)\'>Delete</button>\"   \n");
printf("    msg += \"</th>\";\n");
printf("    msg += \"<tr>\";\n");
printf("    msg += \"</table>\";\n");
printf("    divmsg.innerHTML = msg;\n");
printf("}\n");
printf("</script>\n");
printf("</head>\n");
printf("\n");
printf("\n");
printf("\n");
printf("<body>\n");
printf("    <table width=\"90%%\" border=\"0\" id=\"table1\">\n");
printf("        <tr>\n");
printf("            <td class=\"header\"><strong>");
 ePrint(ehttp_xml.get("/dnake/calllogs/title")); printf("</strong></td>\n");
printf("        </tr>\n");
printf("        <tr>\n");
printf("            <td><hr></td>       \n");
printf("        </tr>\n");
printf("    </table>\n");
printf("    <form id=\"form1\">\n");
printf("        <div>\n");
printf("          <input type=\"button\" value=\"JS读取XML\" onclick=\"ReadXml()\" /><br />\n");
printf("          <div id=\"xmlMsg\">\n");
printf("          </div>\n");
printf("        </div>\n");
printf("    </form>\n");
printf("</table>\n");
printf("</body>\n");
printf("</html>\n");
}

