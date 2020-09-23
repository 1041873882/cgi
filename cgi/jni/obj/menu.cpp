#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cgivars.h"
#include "eHttp.h"
#include "dmsg.h"

void process(char **getvars, char **postvars, int form_method)
{
 print_html_header(); printf("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"\n");
printf("\"http://www.w3.org/TR/html4/loose.dtd\">\n");
printf("<html>\n");
printf("<head>\n");
printf("<title>Untitled Document</title>\n");
printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
printf("\n");
printf("<script language=\"JavaScript\" type=\"text/JavaScript\">\n");
printf("function tabOut(o , color,bg) {\n");
printf(" o.style.backgroundColor = color; \n");
printf("		o.style.backgroundImage  = bg;\n");
printf("}\n");
printf("</script>\n");
printf("<SCRIPT src=\"/ie3d.js\"></SCRIPT>\n");
printf("<SCRIPT src=\"/ToolboxClient.js\"></SCRIPT>\n");
printf("<SCRIPT src=\"/Toolbox.js\"></SCRIPT>\n");
printf("<link href=\"/css/style.css\" rel=\"stylesheet\" type=\"text/css\">\n");
printf("</head>\n");
printf("\n");
printf("<body>\n");
printf("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\">\n");
printf("<tr>\n");
printf("	<td width=\"163\"><img src=\"/images/SystemUI_05.gif\" width=\"163\" height=\"16\" alt=\"\"></td>\n");
printf("</tr>\n");
printf("<tr  onMouseOver=\"this.style.background=\'beige url(/images/button_bg_over.gif)  no-repeat top center\'\" onMouseOut=\"tabOut(this , \'#99cc33\',\'\')\">\n");
printf("	<td class=\"menu\"><A href=\"/cgi-bin/main.cgi\" target=\"main\">");
 ePrint(ehttp_xml.get("/dnake/menu/main")); printf("</A></td>\n");
printf("</tr>\n");
printf("\n");

if (!strcmp(eGetUser(), "user")) {
printf("\n");
printf("\n");
printf("<tr>\n");
printf("	<td><img src=\"/images/SystemUI_08.jpg\" width=\"163\" height=\"2\" alt=\"\"></td>\n");
printf("</tr>\n");
printf("<tr class=\"menu\" onMouseOver=\"this.style.background=\'beige url(/images/button_bg_over.gif)  no-repeat top center\'\" onMouseOut=\"tabOut(this , \'#99cc33\',\'\')\">\n");
printf("	<td class=\"menu\"><a href=\"/cgi-bin/ipc.cgi\" target=\"main\">");
 ePrint(ehttp_xml.get("/dnake/menu/ipc")); printf("</a></td>\n");
printf("</tr>\n");
printf("\n");

} else if (!strcmp(eGetUser(), "admin")) {
printf("\n");
printf("\n");
printf("<tr>\n");
printf("	<td><img src=\"/images/SystemUI_08.jpg\" width=\"163\" height=\"2\" alt=\"\"></td>\n");
printf("</tr>\n");
printf("<tr class=\"menu\" onMouseOver=\"this.style.background=\'beige url(/images/button_bg_over.gif)  no-repeat top center\'\" onMouseOut=\"tabOut(this , \'#99cc33\',\'\')\">\n");
printf("	<td class=\"menu\"><a href=\"/cgi-bin/network.cgi\" target=\"main\">");
 ePrint(ehttp_xml.get("/dnake/menu/network")); printf("</a></td>\n");
printf("</tr>\n");
printf("<tr>\n");
printf("	<td><img src=\"/images/SystemUI_08.jpg\" width=\"163\" height=\"2\" alt=\"\"></td>\n");
printf("</tr>\n");
printf("<tr class=\"menu\" onMouseOver=\"this.style.background=\'beige url(/images/button_bg_over.gif)  no-repeat top center\'\" onMouseOut=\"tabOut(this , \'#99cc33\',\'\')\">\n");
printf("	<td class=\"menu\"><a href=\"/cgi-bin/room.cgi\" target=\"main\">");
 ePrint(ehttp_xml.get("/dnake/menu/room")); printf("</a></td>\n");
printf("</tr>\n");
printf("<tr>\n");
printf("	<td><img src=\"/images/SystemUI_08.jpg\" width=\"163\" height=\"2\" alt=\"\"></td>\n");
printf("</tr>\n");
printf("<tr class=\"menu\" onMouseOver=\"this.style.background=\'beige url(/images/button_bg_over.gif)  no-repeat top center\'\" onMouseOut=\"tabOut(this , \'#99cc33\',\'\')\">\n");
printf("	<td class=\"menu\"><a href=\"/cgi-bin/voip.cgi\" target=\"main\">");
 ePrint(ehttp_xml.get("/dnake/menu/voip")); printf("</a></td>\n");
printf("</tr>\n");
printf("<tr>\n");
printf("	<td><img src=\"/images/SystemUI_08.jpg\" width=\"163\" height=\"2\" alt=\"\"></td>\n");
printf("</tr>\n");
printf("<tr class=\"menu\" onMouseOver=\"this.style.background=\'beige url(/images/button_bg_over.gif)  no-repeat top center\'\" onMouseOut=\"tabOut(this , \'#99cc33\',\'\')\">\n");
printf("	<td class=\"menu\"><a href=\"/cgi-bin/advanced.cgi\" target=\"main\">");
 ePrint(ehttp_xml.get("/dnake/menu/advanced")); printf("</a></td>\n");
printf("</tr>\n");
printf("<tr>\n");
printf("	<td><img src=\"/images/SystemUI_08.jpg\" width=\"163\" height=\"2\" alt=\"\"></td>\n");
printf("</tr>\n");
printf("<tr class=\"menu\" onMouseOver=\"this.style.background=\'beige url(/images/button_bg_over.gif)  no-repeat top center\'\" onMouseOut=\"tabOut(this , \'#99cc33\',\'\')\">\n");
printf("	<td class=\"menu\"><a href=\"/cgi-bin/other.cgi\" target=\"main\">");
 ePrint(ehttp_xml.get("/dnake/menu/other")); printf("</a></td>\n");
printf("</tr>\n");
printf("<tr>\n");
printf("	<td><img src=\"/images/SystemUI_08.jpg\" width=\"163\" height=\"2\" alt=\"\"></td>\n");
printf("</tr>\n");
printf("<tr class=\"menu\" onMouseOver=\"this.style.background=\'Coral url(/images/button_bg_over.gif)  no-repeat top center\'\" onMouseOut=\"tabOut(this , \'#99cc33\',\'\')\">\n");
printf("	<td class=\"menu\"><a href=\"/cgi-bin/time.cgi\" target=\"main\">");
 ePrint(ehttp_xml.get("/dnake/menu/time")); printf("</a></td>\n");
printf("</tr>\n");
printf("<tr>\n");
printf("	<td><img src=\"/images/SystemUI_08.jpg\" width=\"163\" height=\"2\" alt=\"\"></td>\n");
printf("</tr>\n");
printf("<tr class=\"menu\" onMouseOver=\"this.style.background=\'Coral url(/images/button_bg_over.gif)  no-repeat top center\'\" onMouseOut=\"tabOut(this , \'#99cc33\',\'\')\">\n");
printf("	<td class=\"menu\"><a href=\"/cgi-bin/tcpdump.cgi\" target=\"main\">");
 ePrint(ehttp_xml.get("/dnake/menu/tcpdump")); printf("</a></td>\n");
printf("</tr>\n");
printf("\n");
printf("\n");

} else if (!strcmp(eGetUser(), "special")) {
printf("\n");
printf("\n");
printf("<tr>\n");
printf("	<td><img src=\"/images/SystemUI_08.jpg\" width=\"163\" height=\"2\" alt=\"\"></td>\n");
printf("</tr>\n");
printf("<tr class=\"menu\" onMouseOver=\"this.style.background=\'beige url(/images/button_bg_over.gif)  no-repeat top center\'\" onMouseOut=\"tabOut(this , \'#99cc33\',\'\')\">\n");
printf("	<td class=\"menu\"><a href=\"/cgi-bin/advanced2.cgi\" target=\"main\">");
 ePrint(ehttp_xml.get("/dnake/menu/advanced2")); printf("</a></td>\n");
printf("</tr>\n");
printf("\n");

}
printf("\n");
printf("\n");
printf("<tr>\n");
printf("	<td><img src=\"/images/SystemUI_08.jpg\" width=\"163\" height=\"2\" alt=\"\"></td>\n");
printf("</tr>\n");
printf("<tr class=\"menu\" onMouseOver=\"this.style.background=\'beige url(/images/button_bg_over.gif)  no-repeat top center\'\" onMouseOut=\"tabOut(this , \'#99cc33\',\'\')\">\n");
printf("	<td class=\"menu\"><a href=\"/cgi-bin/logout.cgi\" target=\"main\">");
 ePrint(ehttp_xml.get("/dnake/menu/logout")); printf("</a></td>\n");
printf("</tr>\n");
printf("<tr>\n");
printf("	<td><img src=\"/images/SystemUI_08.jpg\" width=\"163\" height=\"2\" alt=\"\"></td>\n");
printf("</tr>  \n");
printf("<tr class=\"menu\" onMouseOver=\"this.style.background=\'beige url(/images/button_bg_over.gif)  no-repeat top center\'\" onMouseOut=\"tabOut(this , \'#99cc33\',\'\')\">\n");
printf("	<td class=\"menu\">&nbsp;</td>\n");
printf("</tr>\n");
printf("<tr>\n");
printf("	<td><img src=\"/images/SystemUI_08.jpg\" width=\"163\" height=\"2\" alt=\"\"></td>\n");
printf("</tr>\n");
printf("<tr class=\"menu\" onMouseOver=\"this.style.background=\'beige url(/images/button_bg_over.gif)  no-repeat top center\'\" onMouseOut=\"tabOut(this , \'#99cc33\',\'\')\">\n");
printf("	<td class=\"menu\">&nbsp;</td>\n");
printf("</tr> \n");
printf("<tr>\n");
printf("	<td><img src=\"/images/SystemUI_08.jpg\" width=\"163\" height=\"2\" alt=\"\"></td>\n");
printf("</tr> \n");
printf("<tr class=\"menu\" onMouseOver=\"this.style.background=\'beige url(/images/button_bg_over.gif)  no-repeat top center\'\" onMouseOut=\"tabOut(this , \'#99cc33\',\'\')\">\n");
printf("	<td class=\"menu\">&nbsp;</td>\n");
printf("</tr>\n");
printf("<tr>\n");
printf("	<td><img src=\"/images/SystemUI_08.jpg\" width=\"163\" height=\"2\" alt=\"\"></td>\n");
printf("</tr>\n");
printf("<tr class=\"menu\" onMouseOver=\"this.style.background=\'beige url(/images/button_bg_over.gif)  no-repeat top center\'\" onMouseOut=\"tabOut(this , \'#99cc33\',\'\')\">\n");
printf("	<td class=\"menu\">&nbsp;</td>\n");
printf("</tr>\n");
printf("<tr>\n");
printf("	<td><img src=\"/images/SystemUI_08.jpg\" width=\"163\" height=\"2\" alt=\"\"></td>\n");
printf("</tr>\n");
printf("<tr class=\"menu\" onMouseOver=\"this.style.background=\'beige url(/images/button_bg_over.gif)  no-repeat top center\'\" onMouseOut=\"tabOut(this , \'#99cc33\',\'\')\">\n");
printf("	<td class=\"menu\">&nbsp;</td>\n");
printf("</tr>\n");
printf("\n");
printf("<tr >\n");
printf("<td  class=\"menu\">&nbsp;</td>\n");
printf("</tr>\n");
printf("<tr>\n");
printf("	<td><img src=\"/images/SystemUI_11.gif\" width=\"163\" height=\"17\" alt=\"\"></td>\n");
printf("</tr>\n");
printf("</table>\n");
printf("</body>\n");
printf("</html>\n");
}

