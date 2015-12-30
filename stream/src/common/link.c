/* link.c
 * link all source to be used anywhere
 * author: pangyemeng
 */


extern void strutil_link(void);
extern void embedded_link(void);
extern void f_format_link(void);
extern void genfun_link(void);

void CommonLink(void)
{
    /* neccesary only to link strutils, embedded, fileformat */
    strutil_link();
    embedded_link();
    f_format_link();
    genfun_link();
}
