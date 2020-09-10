#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cgivars.h"
#include "eHttp.h"
#include "dmsg.h"

void process(char **getvars, char **postvars, int form_method)
{
 print_html_header(); printf("<html>\n");
printf("\n");
printf("<head>\n");
printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
printf("<link href=\"/css/style.css\" rel=\"stylesheet\" type=\"text/css\">\n");
printf("</head>\n");
printf("\n");
printf("<script language=JavaScript>\n");
printf("function sys_logout()\n");
printf("{\n");
printf("	try{\n");
printf("		var agent=navigator.userAgent.toLowerCase();\n");
printf("		if (agent.indexOf(\"msie\") != -1) {\n");
printf("			document.execCommand(\"ClearAuthenticationCache\");\n");
printf("		} else {\n");
printf("			var obj = createXMLObject();\n");
printf("			obj.open(\"GET\",\".force_logout_offer_login_mozilla\",true,\"logout\",\"logout\");\n");
printf("			obj.send(\"\");\n");
printf("			obj.abort();\n");
printf("		}\n");
printf("	} catch(e) {\n");
printf("	}\n");
printf("\n");
printf("	parent.location.href=\"/\";\n");
printf("}\n");
printf("\n");
printf("function createXMLObject() {\n");
printf("	try {\n");
printf("		var obj = null;\n");
printf("		if (window.XMLHttpRequest) {\n");
printf("			obj = new XMLHttpRequest();\n");
printf("		} else if (window.ActiveXObject) {\n");
printf("			obj = new ActiveXObject(\"Microsoft.XMLHTTP\");\n");
printf("		}\n");
printf("		return obj;\n");
printf("	} catch (e) {\n");
printf("	}\n");
printf("	return null;\n");
printf("}\n");
printf("</script>\n");
printf("\n");
printf("<body>\n");
printf("	<table width=\"90%%\" border=\"0\" id=\"table1\">\n");
printf("		<tr>\n");
printf("			<td class=\"header\"><strong>");
 ePrint(ehttp_xml.get("/dnake/logout/title")); printf("</strong></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td><hr></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td>");
 ePrint(ehttp_xml.get("/dnake/logout/prompt")); printf("</td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td>&nbsp;</td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td><input type=\"button\" value=\"");
 ePrint(ehttp_xml.get("/dnake/submit")); printf("\" onClick=\"sys_logout()\"></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td><hr></td>\n");
printf("		</tr>\n");
printf("		<tr>\n");
printf("			<td>&nbsp;</td>\n");
printf("		</tr>\n");
printf("	</table>\n");
printf("</body>\n");
printf("</html>\n");
}

