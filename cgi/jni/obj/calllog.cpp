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

    req.request("/ui/web/calllog/read", NULL);
    p.load(req.body());

    if(form_method == POST) {
        char s1[2];
        char action[256];
        const char *pp = eGetText("action");
        memcpy(s1, pp, 1); s1[1] = 0;
        strcpy(action, pp);

        if (strcmp(s1, "-") != 0) {
            p.setInt("/params/calllog/num", eGetInt("num"));
            p.setText("/params/calllog/action", eGetText("action"));
        }
        req.request("/ui/web/calllog/write", p.data());     
    }
printf("    \n");
printf("<html>\n");
printf("<head>\n");
printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
printf("<link href=\"/css/style.css\" rel=\"stylesheet\" type=\"text/css\">\n");
printf("<style type=\"text/css\">\n");
printf("    .table_1 table {\n");
printf("        width:90%%;\n");
printf("        margin: auto;\n");
printf("        border:0;\n");
printf("    }\n");
printf("    .table_1 th {\n");
printf("        margin: auto;\n");
printf("        background-color:rgb(170, 172, 170);\n");
printf("        font-weight: normal;\n");
printf("        text-align:center;\n");
printf("    }\n");
printf("    .table_1,.table_1 th,.table_1 td {\n");
printf("        color: black;\n");
printf("        font-size:0.95em;\n");
printf("        padding:4px;\n");
printf("        border-collapse:collapse;\n");
printf("        word-wrap: break-word;        \n");
printf("    }\n");
printf("    .table_1 th,.table_1 td {\n");
printf("        border-width:5px 0 5px 0;\n");
printf("        border:2px inset #ffffff;\n");
printf("        line-height:2em;\n");
printf("    }\n");
printf("\n");
printf("    .table_1 td {\n");
printf("        text-align:center;\n");
printf("    }\n");
printf("\n");
printf("    .table_1 tr {\n");
printf("        border: 1px solid #ffffff;\n");
printf("    }\n");
printf("\n");
printf("    .table_2 th {\n");
printf("        width:90%%;\n");
printf("        word-spacing: 80px;\n");
printf("        background-color:rgb(170, 172, 170);\n");
printf("        font-weight: normal;\n");
printf("        text-align:left;  \n");
printf("        color: black;\n");
printf("    }\n");
printf("    .table_2 input, .table_2 select{\n");
printf("        color: black;\n");
printf("    }\n");
printf("</style>\n");
printf("<script>\n");
printf("var calllogEnable = \"");
 ePrint(p.getInt("/params/calllog/enable", 0)); printf("\";\n");
printf("if (calllogEnable == \"0\") {\n");
printf("    var xmlDoc = loadXMLDoc(\"/logger/talk.xml\");\n");
printf("    var max = xmlDoc.getElementsByTagName(\"max\")[0].firstChild.nodeValue;\n");
printf("    console.log(\"max = \" + max);\n");
printf("} else {\n");
printf("    var max = 0;\n");
printf("}\n");
printf("// var xmlDoc = loadXMLDoc(\"/logger/talk.xml\");\n");
printf("// // xmlDoc.async=true;\n");
printf("// var max = xmlDoc.getElementsByTagName(\"max\")[0].firstChild.nodeValue;\n");
printf("\n");
printf("var numCount;       //数据总数量\n");
printf("var columnsCounts;  //数据列数量\n");
printf("var pageCount;      //每页显示的数量\n");
printf("var pageNum;        //总页数\n");
printf("var currPageNum ;   //当前页数\n");
printf("var blockTable;     //页面标签变量\n");
printf("\n");
printf("function firstPage(){\n");
printf("    hide();\n");
printf("    currPageNum = 1;\n");
printf("    for(i = 1; i < pageCount + 1; i++){\n");
printf("        blockTable.rows[i].style.display = \"\";\n");
printf("    }\n");
printf("}\n");
printf("\n");
printf("\n");
printf("function prePage(){\n");
printf("    var select = document.getElementById(\"pageno\"); \n");
printf("    // if (currPageNum == 1) {\n");
printf("    //     alert(\"This is first paper!\");\n");
printf("    // } else {\n");
printf("    if (currPageNum != 1) {\n");
printf("        hide();\n");
printf("        currPageNum--;\n");
printf("        var firstR = firstRow(currPageNum);\n");
printf("        var lastR = lastRow(firstR);\n");
printf("        for(i = firstR; i < lastR; i++){\n");
printf("            blockTable.rows[i].style.display = \"\";\n");
printf("        }\n");
printf("        select.options[currPageNum-1].selected = true;\n");
printf("    }\n");
printf("}\n");
printf("\n");
printf("function nextPage(){\n");
printf("    var select = document.getElementById(\"pageno\"); \n");
printf("    if (currPageNum != 10) {\n");
printf("        hide();\n");
printf("        currPageNum++;\n");
printf("        var firstR = firstRow(currPageNum);\n");
printf("        var lastR = lastRow(firstR);\n");
printf("        for(i = firstR; i < lastR; i ++){\n");
printf("            blockTable.rows[i].style.display = \"\";\n");
printf("        }\n");
printf("        select.options[currPageNum-1].selected = true;\n");
printf("    }\n");
printf("}\n");
printf("\n");
printf("function selPage() {\n");
printf("    hide();\n");
printf("    var sel = document.getElementById(\"pageno\");\n");
printf("    currPageNum = sel.value;\n");
printf("    var firstR = firstRow(currPageNum);\n");
printf("    var lastR = lastRow(firstR);\n");
printf("    for(i = firstR; i < lastR; i ++){\n");
printf("        blockTable.rows[i].style.display = \"\";\n");
printf("    }\n");
printf("}\n");
printf("\n");
printf("//隐藏所有行\n");
printf("function hide(){\n");
printf("    var sel = document.getElementsByName(\"selAll\");\n");
printf("    for(var i=0; i<sel.length; i++){\n");
printf("        sel[i].checked=false\n");
printf("    } \n");
printf("    for(var i = 1; i < numCount + 1; i ++){\n");
printf("        blockTable.rows[i].style.display = \"none\";\n");
printf("    }\n");
printf("}\n");
printf("\n");
printf("// 计算将要显示的页面的首行和尾行\n");
printf("function firstRow(currPageNum){\n");
printf("    return pageCount*(currPageNum - 1) + 1;\n");
printf("}\n");
printf("\n");
printf("function lastRow(firstRow){\n");
printf("    var lastRow = firstRow + pageCount;\n");
printf("    if(lastRow > numCount + 1){\n");
printf("        lastRow = numCount + 1;\n");
printf("    }\n");
printf("    return lastRow;\n");
printf("}\n");
printf("\n");
printf("function loadXMLDoc(dname) {\n");
printf("    if (window.XMLHttpRequest) {\n");
printf("        xhttp = new XMLHttpRequest();\n");
printf("    }else {\n");
printf("        xhttp = new ActiveXObject(\"Microsoft.XMLHTTP\");\n");
printf("    }\n");
printf("\n");
printf("    xhttp.open(\"GET\", dname, false);\n");
printf("    xhttp.send(\"\");\n");
printf("    return xhttp.responseXML;\n");
printf("}\n");
printf("\n");
printf("function selectAll(sel) {\n");
printf("    let selects = document.getElementsByName(\"select\");\n");
printf("    var d = 0;\n");
printf("    for (let i = 0; i < 10; i++) {\n");
printf("        d = i  + ((currPageNum - 1) * 10);\n");
printf("        selects[d].checked = sel.checked;\n");
printf("    }\n");
printf("}\n");
printf("\n");
printf("function delSel(del) {\n");
printf("    var page = document.getElementById(\"pageno\").value\n");
printf("    var form = document.getElementById(\"form1\");\n");
printf("    var d = 0;\n");
printf("    var x = 0;\n");
printf("    var end = 0;\n");
printf("    \n");
printf("    let selects = document.getElementsByName(\"select\");\n");
printf("    if (!del) {\n");
printf("\n");
printf("        for (let i = max - 1; i >= 0; i--) {\n");
printf("            x = x + i + \".\";\n");
printf("            end = i;\n");
printf("        }\n");
printf("        d = max;\n");
printf("        document.getElementById(\'action\').value = x +end;\n");
printf("        document.getElementById(\'num\').value = d;\n");
printf("    } else {\n");
printf("\n");
printf("        for (let i=selects.length-1; i >=0; i--) {\n");
printf("            if(selects[i].checked && i < max) {\n");
printf("                d++;\n");
printf("                end = i;\n");
printf("            }\n");
printf("        }\n");
printf("    \n");
printf("        for (let i = selects.length-1; i >= 0; i--) {\n");
printf("            if(selects[i].checked && i < max) {\n");
printf("                if (i != end)\n");
printf("                    x = x + i + \".\";\n");
printf("            }\n");
printf("        }\n");
printf("\n");
printf("        document.getElementById(\'action\').value = x + end;\n");
printf("        document.getElementById(\'num\').value = d;\n");
printf("    }\n");
printf("    form.submit();\n");
printf("}\n");
printf("</script>\n");
printf("</head>\n");
printf("\n");
printf("\n");
printf("<body>\n");
printf("<form id=\"form1\" method=\"post\" action=\"calllog.cgi\">\n");
printf("    <input type=\"hidden\" id=\"num\" name=\"num\" value=\"0\" />\n");
printf("    <input type=\"hidden\" id=\"action\" name=\"action\" value=\"-1\" />\n");
printf("    <table width=\"90%%\" border=0\"\" id=\"table1\">\n");
printf("        <tr>\n");
printf("            <td class=\"header\"><strong>");
 ePrint(ehttp_xml.get("/dnake/calllog/title")); printf("</strong></td>\n");
printf("        </tr>\n");
printf("        <tr>\n");
printf("            <td><hr></td>       \n");
printf("        </tr>\n");
printf("    </table>\n");
printf("    <table width=\"90%%\" border=\"0\" id=\"table2\" class=\"table_1\">\n");
printf("        <tr>\n");
printf("            <th>Index</th><th>Room NO.</th><th>type</th><th>Local Time</th><th>Destination</th>\n");
printf("            <td style=\'border:none\'><input type=\'checkbox\' name=\'selAll\' onclick=\'selectAll(this)\'></td>\n");
printf("        </tr>\n");
printf("        <tbody id=\"group_one\">\n");
printf("            <script>\n");
printf("                for (var i = 0; i < 100; i++) {\n");
printf("                    var x = i+1;\n");
printf("                    document.write(\"<tr>\"+\"<td>\" + x + \"</td>\");\n");
printf("                    if (i < max) {\n");
printf("                        // xmlDoc.async=true;\n");
printf("                        var d = \"d\"+i;\n");
printf("                        var typeText;\n");
printf("                        nodes = xmlDoc.getElementsByTagName(d)[0];\n");
printf("                        var type = nodes.getElementsByTagName(\"type\")[0].firstChild.nodeValue;\n");
printf("                    \n");
printf("                        if (type == 1)\n");
printf("                            typeText = \"Monitoring\";\n");
printf("                        else if (type == 2)\n");
printf("                            typeText = \"Calling\";\n");
printf("                        else\n");
printf("                            typeText = \"Missed\";\n");
printf("                            \n");
printf("                        document.write(\"<td>\" + nodes.getElementsByTagName(\"id\")[0].firstChild.nodeValue + \"</td>\" + \n");
printf("                                       \"<td>\" + typeText + \"</td>\" + \n");
printf("                                       \"<td>\" + nodes.getElementsByTagName(\"date\")[0].firstChild.nodeValue + \"</td>\" + \n");
printf("                                       \"<td>\" + nodes.getElementsByTagName(\"timeout\")[0].firstChild.nodeValue + \"</td>\");  \n");
printf("                    } else {\n");
printf("                        document.write(\"<td>\" + \"</td>\" + \"<td>\" + \"</td>\" + \"<td>\" + \"</td>\" + \"<td>\" + \"</td>\");\n");
printf("                    }  \n");
printf("                    document.write(\"<td style=\'border:none\'>\" + \"<input type=\'checkbox\' name=\'select\' value=\'1\'>\" + \"</td>\" + \"</tr>\");\n");
printf("                }           \n");
printf("            </script>   \n");
printf("            <table id=\"table3\" class=\"table_2\" width=\"84.5%%\">\n");
printf("                <tr>\n");
printf("                    <th height=\"30px\" colspan=\"5\">\n");
printf("                        Page: \n");
printf("                        <select id=\"pageno\" name=\"pageno\" onclick=\"selPage();\" style=\"width:50px\" >\n");
printf("                            <script>\n");
printf("                                for (var i=1; i<=10; i++) {\n");
printf("                                    document.write(\"<option value=\'\" + i + \"\'>\" + i + \"</option>\");                            \n");
printf("                                }\n");
printf("                                \n");
printf("                            </script>\n");
printf("                        </select>\n");
printf("                        <input type=\"button\" onclick=\"prePage();\" value=\"Prev\" />     \n");
printf("                        <input type=\"button\" onclick=\"nextPage();\" value=\"Next\" />\n");
printf("                        <input type=\"button\" onclick=\'delSel(1)\' value=\"Delete\" />\n");
printf("                        <input type=\"button\" onclick=\'delSel(0)\' value=\"Delete All\" />\n");
printf("                    </th>\n");
printf("                </tr>\n");
printf("            </table>\n");
printf("        </tbody>\n");
printf("    </table>\n");
printf("    </form>\n");
printf("    <script type=\"text/javascript\" language=\"javascript\"> \n");
printf("        window.onload = function(){ \n");
printf("            blockTable = document.getElementById(\"table2\");\n");
printf("\n");
printf("            numCount = blockTable.rows.length - 1;       //取table的行数作为数据总数量（减去标题行1）\n");
printf("            pageCount = 10;\n");
printf("            pageNum = parseInt(numCount/pageCount);\n");
printf("            if(0 != numCount%%pageCount){\n");
printf("                pageNum += 1;\n");
printf("            }\n");
printf("            firstPage();\n");
printf("        }; \n");
printf("    </script> \n");
printf("</body>\n");
printf("</html>\n");
}
