/* xplxml.h
 * author: pangyemeng
 */

/*
<?xml version="1.0" encoding="ISO-8859-1"?>

  <flow num="1">
     <frame type="eth">
        <prop name="eth.type" value="5" />
     </frame>
  </flow>
  
  <flow num=2>
  ...
  </flow>
  
  ...
*/

#ifndef __XPLXML_H__
#define __XPLXML_H__

#define XPL_HEADER          "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\r\n<?xml-stylesheet type=\"text/css\" href=\"/css/flows.css\"?>\r\n\r\n"
#define XPL_FLOW_OPEN       "<flow>\r\n  <number>--- Decoding info: stream %d ---</number>\r\n"
#define XPL_FLOW_CLOSE      "</flow>\r\n"
#define XPL_GRP_FRAME_OPEN  "<grp>\r\n"
#define XPL_GRP_FRAME_CLOSE "</grp>\r\n"
#define XPL_FRAME_OPEN      "  <frame>\r\n    <frm_type>%s</frm_type>\r\n"
#define XPL_FRAME_CLOSE     "  </frame>\r\n"
#define XPL_PROP            "    <prop>\r\n      <name>%s</name>\r\n      <value>%s</value>\r\n    </prop>\r\n"




#endif /* __XPLXML_H__ */
