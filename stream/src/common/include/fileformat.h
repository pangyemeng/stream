/* fileformat.h
 * File format functions: uncompress, decode, ...
 * author: pangyemeng
 */

#ifndef __FILEFORMAT_H__
#define __FILEFORMAT_H__

/* multipart/form-data; boundary file format */
typedef struct _multipart_f multipart_f;
struct _multipart_f {
    char *name;           /* part name */
    char *value;          /* value */
    unsigned short vlen;  /* value lenght */
    char *file_name;      /* file name of part */
    char *file_path;      /* file path */
    char *content_type;   /* file content_type */
    char *content_range;  /* content range */
    multipart_f *nxt;     /* next part */
};


int FFormatUncompress(const char *encoding, const char *file_in,  const char *file_out);
int FFormatCopy(char *old, char *new);
multipart_f *FFormatMultipart(const char *file_name, const char *boundary);
void FFormatMultipartPrint(multipart_f *mp);
int FFormatMultipartFree(multipart_f *mp);

#endif
