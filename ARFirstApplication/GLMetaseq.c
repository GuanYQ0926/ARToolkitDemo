#define __GLMETASEQ_C__
#include "GLMetaseq.h"

/*

GLMetaseq
The MIT License
Copyright (c) 2009 Sunao Hashimoto and Keisuke Konishi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


GLMetaseq
MIT   C Z   X
Copyright (c) 2009 Sunao Hashimoto and Keisuke Konishi

 È º É è ß é ð   É ] ¢ A { \ t g E F A ¨ æ Ñ Ö A ¶   Ì t @ C   i È º u \ t g
 E F A v j Ì ¡ » ð æ ¾ · é · × Ä Ì l É Î µ A \ t g E F A ð ³ § À É µ ¤ ± Æ ð
 ³   Å   Â µ Ü · B ± ê É Í A \ t g E F A Ì ¡ » ð g p A ¡ Ê A Ï X A     A f Ú A
 Ð z A T u   C Z   X A ¨ æ Ñ/ Ü ½ Í Ì   · é     A ¨ æ Ñ \ t g E F A ð ñ   · é
   è É ¯ ¶ ± Æ ð   Â · é     à ³ § À É Ü Ü ê Ü · B

 ã L Ì   ì   \ ¦ ¨ æ Ñ {   ø \ ¦ ð A \ t g E F A Ì · × Ä Ì ¡ » Ü ½ Í d v È   ª
 É L Ú · é à Ì Æ µ Ü · B

 \ t g E F A Í u » ó Ì Ü Ü v Å A ¾ ¦ Å   é © Ã Ù Å   é © ð â í ¸ A ½ ç Ì Û Ø
 à È ­ ñ   ³ ê Ü · B ± ± Å ¢ ¤ Û Ø Æ Í A ¤ i « A Á è Ì Ú I Ö Ì K   « A ¨ æ Ñ
     ñ N Q É Â ¢ Ä Ì Û Ø à Ü Ý Ü · ª A » ê É À è ³ ê é à Ì Å Í   è Ü ¹ ñ B
 ì Ò Ü ½ Í   ì   Ò Í A _ ñ s × A s @ s × A Ü ½ Í » ê È O Å   ë ¤ Æ A \ t g
 E F A É N ö Ü ½ Í Ö A µ A   é ¢ Í \ t g E F A Ì g p Ü ½ Í » Ì ¼ Ì µ ¢ É
 æ Á Ä ¶ ¶ é ê Ø Ì ¿   A ¹ Q A » Ì ¼ Ì ` ± É Â ¢ Ä ½ ç Ì Ó C à   í È ¢ à Ì
 Æ µ Ü · B

*/

/*=========================================================================
 y ± Ì \ [ X à Å Ì Ý L ø È O   [ o   Ï   z
=========================================================================*/

static TEXTURE_POOL l_texPool[MAX_TEXTURE];             //  e N X `   v [  
static int                      l_texPoolnum;                           //  e N X `   Ì  
static int                      l_GLMetaseqInitialized = 0;     //    ú » t   O


/*=========================================================================
 y Ö   é ¾ z
=========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

void    endianConverter(void *addr,unsigned int size);
void    TGAHeaderEndianConverter(       STR_TGA_HEAD *tgah );
int             IsExtensionSupported( char* szTargetExtension );

GLuint          mqoSetTexturePool(char *texfile, char *alpfile, unsigned char alpha );
void            mqoClearTexturePool();
GLubyte*        mqoLoadTextureEx(char *texfile,char *alpfile,int *tex_size,unsigned char alpha);
int                     mqoLoadFile(MQO_OBJECT *mqoobj,char *filename,double scale,unsigned char alpha);
MQO_OBJECT*     mqoCreateList(int num);
int                     mqoCreateListObject( MQO_OBJECT *obj, int id, char *filename,double scale,unsigned char alpha);

void mqoCallListObject(MQO_OBJECT object[],int num);
void mqoClearObject(MQO_OBJECT object[],int from,int num);
void mqoDeleteObject(MQO_OBJECT * object,int num);
void mqoGetDirectory(const char *path_file, char *path_dir);
void mqoSnormal(glPOINT3f A, glPOINT3f B, glPOINT3f C, glPOINT3f *normal);
void mqoReadMaterial(FILE *fp, MQO_MATDATA M[]);
void mqoReadVertex(FILE *fp, glPOINT3f V[]);
int      mqoReadBVertex(FILE *fp,glPOINT3f V[]);
void mqoReadFace(FILE *fp, MQO_FACE F[]);
void mqoReadObject(FILE *fp, MQO_OBJDATA *obj);

void mqoMakeArray(MQO_MATERIAL *mat, int matpos,MQO_FACE F[], int fnum,glPOINT3f V[],
                                  glPOINT3f N[], double facet, glCOLOR4f *mcol, double scale, unsigned char alpha );

glPOINT3f *mqoVertexNormal(MQO_OBJDATA *obj);

void mqoMakePolygon(MQO_OBJDATA *readObj, MQO_OBJECT *mqoobj,
                                        glPOINT3f N[], MQO_MATDATA M[], int n_mat, double scale, unsigned char alpha);

void mqoMakeObjectsEx(MQO_OBJECT *mqoobj, MQO_OBJDATA obj[], int n_obj, MQO_MATDATA M[],int n_mat,
                                          double scale,unsigned char alpha);

#ifdef __cplusplus
}
#endif


/*=========================================================================
 y Ö   zendianConverter
 y p r z G   f B A   Ï ·
 y ø   z
                addr     A h   X
                size     T C Y

 y ß l z È µ
=========================================================================*/

void endianConverter(void *addr,unsigned int size)
{
        unsigned int pos;
        char c;
        if ( size <= 1 ) return;
        for ( pos = 0; pos < size/2; pos++ ) {
                c = *(((char *)addr)+pos);
                *(((char *)addr)+pos) = *(((char *)addr)+(size-1 - pos));
                *(((char *)addr)+(size-1 - pos)) = c;
        }
}


/*=========================================================================
 y Ö   zTGAHeaderEndianConverter
 y p r zTGA Ì w b _ Ì G   f B A   Ï ·
 y ø   z
                tgah    TGA Ì w b _

 y ß l z È µ
=========================================================================*/

void TGAHeaderEndianConverter(  STR_TGA_HEAD *tgah )
{
        endianConverter(&tgah->color_map_entry,sizeof(tgah->color_map_entry));
        endianConverter(&tgah->x,sizeof(tgah->x));
        endianConverter(&tgah->y,sizeof(tgah->y));
        endianConverter(&tgah->width,sizeof(tgah->width));
        endianConverter(&tgah->height,sizeof(tgah->height));
}


/*=========================================================================
 y Ö   zIsExtensionSupported
 y p r zOpenGL Ì g £ @ \ ª T | [ g ³ ê Ä ¢ é © Ç ¤ © ² × é
 y ø   z
                szTargetExtension        g £ @ \ Ì ¼ O

 y ß l z1 F T | [ g ³ ê Ä ¢ é C0 F ³ ê Ä ¢ È ¢
=========================================================================*/

int IsExtensionSupported( char* szTargetExtension )
{
        const unsigned char *pszExtensions = NULL;
        const unsigned char *pszStart;
        unsigned char *pszWhere, *pszTerminator;

        // Extension  Ì ¼ O ª ³ µ ¢ © ² × é(NULL â ó   ÍNG j
        pszWhere = (unsigned char *) strchr( szTargetExtension, ' ' );
        if ( pszWhere || *szTargetExtension == (char)NULL )
                return 0;

        // Extension  Ì ¶   ñ ð   ¾ · é
        pszExtensions = glGetString( GL_EXTENSIONS );

        //  ¶   ñ Ì   É K v È extension  ª   é © ² × é
        pszStart = pszExtensions;
        for (;;)
        {
                pszWhere = (unsigned char *) strstr( (const char *) pszStart, szTargetExtension );
                if ( !pszWhere )
                        break;
                pszTerminator = pszWhere + strlen( szTargetExtension );
                if ( pszWhere == pszStart || *( pszWhere - 1 ) == ' ' )
                if ( *pszTerminator == ' ' || *pszTerminator == (char)NULL )
                        return 1;
                pszStart = pszTerminator;
        }
        return 0;
}


/*=========================================================================
 y Ö   zmqoInit
 y p r z   ^ Z R C A   [ _ Ì   ú »
 y ø   z È µ
 y ß l z È µ
=========================================================================*/

void mqoInit(void)
{
        //  e N X `   v [     ú »
        memset(l_texPool,0,sizeof(l_texPool));
        l_texPoolnum = 0;

        //  ¸ _ o b t @ Ì T | [ g Ì ` F b N
        g_isVBOSupported = IsExtensionSupported("GL_ARB_vertex_buffer_object");
        g_isVBOSupported = 0;

#ifdef WIN32
        glGenBuffersARB = NULL;
        glBindBufferARB = NULL;
        glBufferDataARB = NULL;
        glDeleteBuffersARB = NULL;

        if ( g_isVBOSupported ) {
                // printf("OpenGL :  ¸ _ o b t @ ð T | [ g µ Ä ¢ é Ì Å g p µ Ü ·\n");
                // GL  Ö   Ì | C   ^ ð   ¾ · é
                glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
                glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
                glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
                glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");
        }
#endif

        //    ú » t   O
        l_GLMetaseqInitialized = 1;
}


/*=========================================================================
 y Ö   zmqoCleanup
 y p r z   ^ Z R C A   [ _ Ì I ¹    
 y ø   z È µ
 y ß l z È µ
=========================================================================*/

void mqoCleanup(void)
{
        mqoClearTexturePool();  //  e N X `   v [   Ì N   A
}


/*=========================================================================
 y Ö   zmqoSetTexturePool
 y p r z e N X `   v [   É e N X `   ð Ç Ý   Þ
 y ø   z
                texfile          e N X `   t @ C   ¼
                alpfile          A   t @ t @ C   ¼
                alpha            A   t @

 y ß l z e N X `  ID
 y d l z e N X `   ª Ü ¾ Ç Ý   Ü ê Ä ¢ È ¯ ê Î Ç Ý   Ý C e N X `   o ^
                 · Å É Ç Ý   Ü ê Ä ¢ ê Î o ^ µ ½ à Ì ð Ô ·.
=========================================================================*/

GLuint mqoSetTexturePool(char *texfile, char *alpfile, unsigned char alpha )
{
        int pos;
        GLubyte *image;

        for ( pos = 0; pos < l_texPoolnum; pos++ ) {
                if ( alpha != l_texPool[pos].alpha ) {
                        continue;
                }
                if ( texfile != NULL ) {
                        if ( strcmp(texfile,l_texPool[pos].texfile) != 0 ) {
                                continue;
                        }
                }
                if ( alpfile != NULL ) {
                        if ( strcmp(alpfile,l_texPool[pos].alpfile) != 0 ) {
                                continue;
                        }
                }
                break;
        }
        if ( pos < l_texPoolnum ) { // · Å É Ç Ý   Ý Ï Ý
                return  l_texPool[pos].texture_id;
        }
        if ( MAX_TEXTURE <= pos ) {
                printf("%s:mqoSetTexturePool  e N X `   Ç Ý   Ý Ì æ s «\n",__FILE__);
                return -1;
        }
        image = mqoLoadTextureEx(texfile,alpfile,&l_texPool[pos].texsize,alpha);
        if ( image == NULL ) {
                return -1;
        }

        if ( texfile != NULL ) strncpy(l_texPool[pos].texfile,texfile,MAX_PATH);
        if ( alpfile != NULL ) strncpy(l_texPool[pos].alpfile,alpfile,MAX_PATH);
        l_texPool[pos].alpha = alpha;

        glPixelStorei(GL_UNPACK_ALIGNMENT,4);
        glPixelStorei(GL_PACK_ALIGNMENT,4);
        glGenTextures(1,&l_texPool[pos].texture_id);                    //  e N X `   ð ¶ ¬
        glBindTexture(GL_TEXTURE_2D,l_texPool[pos].texture_id); //  e N X `   Ì   è   Ä

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, l_texPool[pos].texsize, l_texPool[pos].texsize,
                                        0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        l_texPoolnum = pos+1;

        // o ^ · ê Î A Ç Ý   ñ ¾ o b t @ Í s v
        free(image);
        glBindTexture(GL_TEXTURE_2D,0); //  f t H   g e N X `   Ì   è   Ä

        return l_texPool[pos].texture_id;
}


/*=========================================================================
 y Ö   zmqoClearTexturePool()
 y p r z e N X `   v [   Ì J ú
 y ø   z È µ
 y ß l z È µ
=========================================================================*/

void mqoClearTexturePool()
{
        int pos;
        for ( pos = 0; pos < l_texPoolnum; pos++ ) {
                glDeleteTextures(1, &l_texPool[pos].texture_id);        //  e N X `   î ñ ð í  
        }

        memset(l_texPool,0,sizeof(l_texPool));
        l_texPoolnum = 0;
}


/*=========================================================================
 y Ö   zmqoLoadTextureEx
 y p r z t @ C   © ç e N X `   æ   ð ì ¬ · é
 y ø   z
                texfile          t @ C   ¼
                alpfile          A   t @ t @ C   ¼
                tex_size         e N X `   Ì T C Y i ê Ó Ì · ³ j ð Ô ·

 y ß l z e N X `   æ   Ö Ì | C   ^ i ¸ s   ÍNULL j
 y d l z24bit r b g } b v C ¨ æ Ñ8,24,32bit s f `
                 T C Y Í u ê Ó ª2 Ìn æ Ì ³ û ` v É À è
                libjpeg,libpng i O     C u     j ª L ê ÎJPEG,PNG Ì Ç Ý   Ý Â \
=========================================================================*/

GLubyte* mqoLoadTextureEx(char *texfile,char *alpfile,int *tex_size,unsigned char alpha)
{
        FILE *fp;
        size_t namelen;
        char ext[4];
        char wbuf[3];
        int isTGA;
        int isPNG;
        int isJPEG;
        int other;
        int     y,x,size;
        int fl;
        char *filename[2];
        int width[2];
        int sts;
        STR_TGA_HEAD tgah;
        GLubyte *pImage, *pRead;

#if DEF_USE_LIBJPEG
        struct jpeg_decompress_struct cinfo;
        struct jpeg_error_mgr jerr;
        JSAMPARRAY jpegimage;
#endif
#if DEF_USE_LIBPNG
        unsigned char **pngimage;
        unsigned long   pngwidth, pngheight;
        int                             pngdepth;
        int             color_type;
#endif

        filename[0] = texfile;
        filename[1] = alpfile;
        width[0] = -1;
        width[1] = -1;
        pImage = NULL;
        fp = NULL;
        sts = 0;
#if DEF_USE_LIBJPEG
        jpegimage = NULL;
#endif
#if DEF_USE_LIBPNG
        pngimage = NULL;
#endif
        size = - 1;
        for ( fl = 0; fl < 2; fl++ ) {// e N X `    fl=0     A   t @  fl=1
                if ( filename[fl] == NULL ) continue;
                namelen = strlen(filename[fl]);
                ext[0] = tolower(filename[fl][namelen-3]);
                ext[1] = tolower(filename[fl][namelen-2]);
                ext[2] = tolower(filename[fl][namelen-1]);
                ext[3] = 0x00;
                isTGA = (strcmp(ext,"tga")==0)?1:0;
                isPNG = (strcmp(ext,"png")==0)?1:0;
                isJPEG = (strcmp(ext,"jpg")==0)?1:0;
                /* */
                if ( (! isTGA) && (! isPNG) &&(! isJPEG) ) {
                        filename[fl][namelen-3] = 'b';
                        filename[fl][namelen-2] = 'm';
                        filename[fl][namelen-1] = 'p';
                }
                /* */
                if ( fl == 1 ) { // A   t @ Ì Ç Ý   Ý Í s f `or o m f
                        if ( ! (isTGA || isPNG) ) {
                                printf(" A   t @ Ì t @ C   É Î   Å « È ¢ ¨%s\n",filename[fl]);
                                break;
                        }
                }
                if ( fp != NULL ) fclose(fp);
                if ( (fp=fopen(filename[fl],"rb"))==NULL ) {
                        printf("%s: e N X `   Ç Ý   Ý G   [[%s]\n",__FILE__,filename[fl]);
                        continue;
                }
                //  w b _ Ì   [ h
                if ( isTGA ) {
                        fread(&tgah,sizeof(STR_TGA_HEAD),1,fp);
#if DEF_IS_LITTLE_ENDIAN
#else
                        TGAHeaderEndianConverter(&tgah);
#endif
                        size = width[fl] = tgah.width;
                }
                if ( isJPEG ) {
#if DEF_USE_LIBJPEG
                        unsigned int i;
                        cinfo.err = jpeg_std_error( &jerr );
                        jpeg_create_decompress( &cinfo );       // ð   p î ñ ì ¬
                        jpeg_stdio_src( &cinfo, fp );           // Ç Ý   Ý t @ C   w è
                        jpeg_read_header( &cinfo, TRUE );       //jpeg w b _ Ç Ý   Ý
                        jpeg_start_decompress( &cinfo );        // ð   J n

                        if ( cinfo.out_color_components == 3 && cinfo.out_color_space == JCS_RGB ) {
                                if ( jpegimage != NULL ) {
                                        for (i = 0; i < cinfo.output_height; i++) free(jpegimage[i]);            //  È º Q s Í Q   ³ z ñ ð ð ú µ Ü ·
                                        free(jpegimage);
                                }
                                // Ç Ý   Ý f [ ^ z ñ Ì ì ¬
                                jpegimage = (JSAMPARRAY)malloc( sizeof( JSAMPROW ) * cinfo.output_height );
                                for ( i = 0; i < cinfo.output_height; i++ ) {
                                        jpegimage[i] = (JSAMPROW)malloc( sizeof( JSAMPLE ) * cinfo.out_color_components * cinfo.output_width );
                                }
                                // ð   f [ ^ Ç Ý   Ý
                                while( cinfo.output_scanline < cinfo.output_height ) {
                                        jpeg_read_scanlines( &cinfo,
                                                jpegimage + cinfo.output_scanline,
                                                cinfo.output_height - cinfo.output_scanline
                                        );
                                }
                                size = width[fl] = cinfo.output_width;
                        }

                        jpeg_finish_decompress( &cinfo );       // ð   I ¹
                        jpeg_destroy_decompress( &cinfo );      // ð   p î ñ ð ú
                        if ( !(cinfo.out_color_components == 3 && cinfo.out_color_space == JCS_RGB) ) {
                                printf("JPEG  Î   Å « È ¢ t H [ } b g ¨%s\n",filename[fl]);
                        }
#else
                        printf(" ± Ì e N X `   Í Î   Å « È ¢ t H [ } b g ¨%s\n",filename[fl]);
                        continue;
#endif
                }
                if ( isPNG ) {
#if DEF_USE_LIBPNG
                        png_structp     png_ptr;
                        png_infop       info_ptr;
                        int             bit_depth, interlace_type;
                        unsigned int             i;
                        int j,k;
                        png_ptr = png_create_read_struct(                       // png_ptr \ ¢ Ì ð m Û E   ú » µ Ü ·
                                                        PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
                        info_ptr = png_create_info_struct(png_ptr);             // info_ptr \ ¢ Ì ð m Û E   ú » µ Ü ·
                        png_init_io(png_ptr, fp);                               // libpng Éfp ð m ç ¹ Ü ·
                        png_read_info(png_ptr, info_ptr);                       // PNG t @ C   Ì w b _ ð Ç Ý   Ý Ü ·
                        png_get_IHDR(png_ptr, info_ptr, &pngwidth, &pngheight,        // IHDR `     N î ñ ð æ ¾ µ Ü ·
                                                        &bit_depth, &color_type, &interlace_type,
                                                        &j,&k);
                        if ( pngimage != NULL ) {
                                for (i = 0; i < pngheight; i++) free(pngimage[i]);            //  È º Q s Í Q   ³ z ñ ð ð ú µ Ü ·
                                free(pngimage);
                        }
                        pngimage = (png_bytepp)malloc(pngheight * sizeof(png_bytep)); //  È º R s Í Q   ³ z ñ ð m Û µ Ü ·
                        i = png_get_rowbytes(png_ptr, info_ptr);
                        pngdepth = i / pngwidth;
                        for (i = 0; i < pngheight; i++)
                                        pngimage[i] = (png_bytep)malloc(png_get_rowbytes(png_ptr, info_ptr));
                        png_read_image(png_ptr, pngimage);                         //  æ   f [ ^ ð Ç Ý   Ý Ü ·

                        png_destroy_read_struct(                                //  Q Â Ì \ ¢ Ì Ì       ð ð ú µ Ü ·
                &png_ptr, &info_ptr, (png_infopp)NULL);
                        size = width[fl] = pngwidth;
#else
                        printf(" ± Ì e N X `   Í Î   Å « È ¢ t H [ } b g ¨%s\n",filename[fl]);
                        continue;
#endif
                }
                if ( width[fl] == -1 ) {// R R Ü Å « Ä T C Y ª w è ³ ê Ä ¢ È ¢ @   @ r b g } b v
                        fseek(fp,14+4,SEEK_SET);                //  æ     ª i [ ³ ê Ä ¢ é Ê u Ü Å V [ N
                        fread(&size,sizeof(int),1,fp);  // BiWidth Ì î ñ ¾ ¯ æ ¾
                        fseek(fp,14+40,SEEK_SET);               //  æ f f [ ^ ª i [ ³ ê Ä ¢ é Ê u Ü Å V [ N
#if DEF_IS_LITTLE_ENDIAN
#else
                        endianConverter(&size,sizeof(int));
#endif
                        width[fl] = size;

                }
                if ( width[0] != -1 && width[1] != -1 ) {
                        if ( width[0] != width[1] ) {
                                sts = -1;
                                break;
                        }
                }
                if ( fl == 1 && isTGA ) { // A   t @ Ì Ç Ý   Ý Í s f ` Ì W r b g   m N       R Q r b g t  
                        if ( !(
                                (tgah.depth == 8 && tgah.type == DEF_TGA_TYPE_MONO) ||
                                (tgah.depth == 32 && tgah.type == DEF_TGA_TYPE_FULL)
                                ) ) {
                                break;
                        }
                }
                if ( fl == 1 && isPNG ) { // A   t @ Ì Ç Ý   Ý Í o m f Ì g D   [ J   [ { A   t @     O   [ X P [   { A   t @
#if DEF_USE_LIBPNG
                        if ( !(
                                (color_type== 6 ) ||
                                (color_type== 4 )
                                ) ) {
                                break;
                        }
#endif
                }

                //        Ì m Û
                if ( pImage == NULL ) {
                        pImage = (GLubyte*)malloc(sizeof(unsigned char)*size*size*4);
                }
                if (pImage==NULL) return NULL;
                for (y=0; y<size; y++){
                        pRead = pImage + (size-1-y)*4*size;
                        for (x=0; x<size; x++) {
                                other = 1;
                                if ( fl == 0 ) {
                                        if ( isJPEG ) {
#if DEF_USE_LIBJPEG
                                                pRead[0]= jpegimage[size-1-y][x*3];
                                                pRead[1]= jpegimage[size-1-y][x*3+1];
                                                pRead[2]= jpegimage[size-1-y][x*3+2];
                                                pRead[3] = alpha;                               // A
                                                other = 0;
#endif
                                        }
                                        if ( isPNG ) {
#if DEF_USE_LIBPNG
                                                if ( color_type == 2 || color_type==6 ) {
                                                        pRead[0]= pngimage[size-1-y][x*pngdepth];
                                                        pRead[1]= pngimage[size-1-y][x*pngdepth+1];
                                                        pRead[2]= pngimage[size-1-y][x*pngdepth+2];
                                                        pRead[3] = alpha;                               // A
                                                        if ( color_type == 6 ) {
                                                                pRead[3]= pngimage[size-1-y][x*pngdepth+3];
                                                        }
                                                }
                                                other = 0;
#endif
                                        }
                                        if ( other )  {
                                                fread(&pRead[2],1,1,fp);        // B
                                                fread(&pRead[1],1,1,fp);        // G
                                                fread(&pRead[0],1,1,fp);        // R
                                                pRead[3] = alpha;                               // A
                                                if ( isTGA && tgah.depth == 32 ) {
                                                        fread(&pRead[3],1,1,fp);        // A
                                                        if ( alpha < pRead[3] ) pRead[3] = alpha;
                                                }
                                        }
                                }
                                else {
                                        if ( isPNG ) {
#if DEF_USE_LIBPNG
                                                if ( color_type == 6 ) { // g D   [ J   [ { A   t @
                                                        pRead[3]= pngimage[size-1-y][x*pngdepth+3];
                                                }
                                                if ( color_type == 4 ) { // O   [ X P [   { A   t @
                                                        pRead[3]= pngimage[size-1-y][x*pngdepth+1];
                                                }
                                                if ( alpha < pRead[3] ) pRead[3] = alpha;
#endif
                                        }
                                        if ( isTGA ) {
                                                if ( tgah.depth == 32 ) { // ¢ ç È ¢ f [ ^ ð Ç Ý ò Î ·
                                                        fread(wbuf,3,1,fp);     // BGR
                                                }
                                                fread(&pRead[3],1,1,fp);        // A
                                                if ( alpha < pRead[3] ) pRead[3] = alpha;
                                        }
                                }
                                pRead+=4;
                        }
                }
                fclose(fp);
                fp = NULL;
        }
        if ( sts != 0 ) {
                if ( pImage != NULL ) free(pImage);
                if ( fp != NULL ) fclose(fp);
        }
#if DEF_USE_LIBPNG
        if ( pngimage != NULL ) {
                unsigned int uy;
                for (uy = 0; uy < pngheight; uy++) free(pngimage[uy]);            //  È º Q s Í Q   ³ z ñ ð ð ú µ Ü ·
                free(pngimage);
        }
#endif
#if DEF_USE_LIBJPEG
        if ( jpegimage != NULL ) {
                unsigned int uy;
                for (uy = 0; uy < cinfo.output_height; uy++) free(jpegimage[uy]);            //  È º Q s Í Q   ³ z ñ ð ð ú µ Ü ·
                free(jpegimage);
        }
#endif
        if ( size < 0 ) {
                if ( pImage != NULL ) free(pImage);
                pImage = NULL;
        }
        *tex_size = size;

        return pImage;
}


/*=========================================================================
 y Ö   zmqoLoadFile
 y p r z   ^ Z R C A t @ C  (*.mqo) © ç f [ ^ ð Ç Ý   Þ
 y ø   z
                mqoobj          MQO I u W F N g
                filename         t @ C   Ì p X
                scale            g å ¦
                alpha            A   t @

 y ß l z ¬ ÷ F1  ^  ¸ s F0
=========================================================================*/

int mqoLoadFile( MQO_OBJECT *mqoobj, char *filename, double scale, unsigned char alpha)
{
        FILE                    *fp;
        MQO_OBJDATA             obj[MAX_OBJECT];
        MQO_MATDATA             *M = NULL;

        char    buf[SIZE_STR];          //  ¶   ñ Ç Ý   Ý o b t @
        char    path_dir[SIZE_STR];     //  f B   N g   Ì p X
        char    path_tex[SIZE_STR];     //  e N X `   t @ C   Ì p X
        char    path_alp[SIZE_STR];     //  A   t @ e N X `   t @ C   Ì p X
        int             n_mat = 0;                      //  } e   A    
        int             n_obj = 0;                      //  I u W F N g  
        int             i;

        // Material ÆObject Ì Ç Ý   Ý
        fp = fopen(filename,"rb");
        if (fp==NULL) return 0;

        mqoobj->alpha = alpha;
        memset(obj,0,sizeof(obj));

        i = 0;
        while ( !feof(fp) ) {
                fgets(buf,SIZE_STR,fp);

                // Material
                if (strstr(buf,"Material")) {
                        sscanf(buf,"Material %d", &n_mat);
                        M = (MQO_MATDATA*) calloc( n_mat, sizeof(MQO_MATDATA) );
                        mqoReadMaterial(fp,M);
                }

                // Object
                if (strstr(buf,"Object")) {
                        sscanf(buf,"Object %s", obj[i].objname);
                        mqoReadObject(fp, &obj[i]);
                        i++;
                }
        }
        n_obj = i;
        fclose(fp);

        //  p X Ì æ ¾
        mqoGetDirectory(filename, path_dir);

        //  e N X `   Ì o ^
        for (i=0; i<n_mat; i++) {
                if (M[i].useTex) {

                        if (strstr(M[i].texFile,":")) {
                                strcpy(path_tex, M[i].texFile); //  â Î p X Ì ê  
                        } else {
                                sprintf(path_tex,"%s%s",path_dir,M[i].texFile); //    Î p X Ì ê  
                        }

                        if ( M[i].alpFile[0] != (char)0 ) {
                                if (strstr(M[i].texFile,":")) {
                                        strcpy(path_alp, M[i].alpFile); //  â Î p X Ì ê  
                                } else {
                                        sprintf(path_alp,"%s%s",path_dir,M[i].alpFile); //    Î p X Ì ê  
                                }
                                M[i].texName = mqoSetTexturePool(path_tex,path_alp,alpha);
                        }
                        else {
                                M[i].texName = mqoSetTexturePool(path_tex,NULL,alpha);
                        }
                }
        }

        mqoMakeObjectsEx( mqoobj, obj, n_obj, M, n_mat, scale, alpha );

        //  I u W F N g Ì f [ ^ Ì J ú
        for (i=0; i<n_obj; i++) {
                free(obj[i].V);
                free(obj[i].F);
        }

        //  } e   A   Ì J ú
        free(M);

        return 1;
}


/*=========================================================================
 y Ö   zmqoCreateList
 y p r zMQO I u W F N g ð w è   m Û · é
 y ø   znum               MQO I u W F N g Ì  

 y ß l zMQO I u W F N g
=========================================================================*/

MQO_OBJECT* mqoCreateList(int num)
{
        MQO_OBJECT *obj;

        //    ú » ³ ê Ä È © Á ½ ç   ú »
        if ( ! l_GLMetaseqInitialized ) mqoInit();

        //  Ì æ m Û Æ   ú »
        obj = (MQO_OBJECT *)malloc(sizeof(MQO_OBJECT)*num);
        memset(obj, 0, sizeof(MQO_OBJECT)*num);

        return obj;
}


/*=========================================================================
 y Ö   zmqoCreateListObject
 y p r z   ^ Z R C A t @ C  (*.mqo) © çMQO I u W F N g z ñ ð ì ¬ · é

 y ø   zmqoobj            MQO I u W F N g
                i                        Ç Ý   Ý æ Ô   ii Ô Ú ÉMQO t @ C   ð Ç Ý   Þ j
                filename         t @ C   Ì p X
                scale            g å ¦
                alpha            A   t @ w è i S Ì Ì A   t @ l ð w è i0 `255 j j

 y ß l z X e [ ^ X @   F Ù í @ O F ³ í
=========================================================================*/

int mqoCreateListObject(MQO_OBJECT *mqoobj, int i, char *filename, double scale, unsigned char alpha )
{
        int ret;
        ret = 0;
        if ( mqoobj == (MQO_OBJECT *)NULL ) return -1;
        if (! mqoLoadFile(&mqoobj[i], filename, scale, alpha)) ret = -1;
        return ret;
}


/*=========================================================================
 y Ö   zmqoCallListObject
 y p r zMQO I u W F N g ðOpenGL Ì æ Ê ã É Ä Ñ o ·
 y ø   z
                mqoobj          MQO I u W F N g z ñ
                num                      z ñ Ô   (0 ` j

 y ß l z È µ
=========================================================================*/

void mqoCallListObject(MQO_OBJECT mqoobj[],int num)
{

        MQO_INNER_OBJECT        *obj;
        MQO_MATERIAL            *mat;
        GLfloat                         matenv[4];
        GLint                           bindGL_TEXTURE_2D       = 0;
        GLboolean                       isGL_TEXTURE_2D         = GL_FALSE;
        GLboolean                       isGL_BLEND                      = GL_FALSE;
        GLint                           blendGL_SRC_ALPHA       = 0;
        GLint                           intFrontFace;

        int             o, m, offset;
        double  dalpha;
        char    *base;

        if ( mqoobj == NULL) return;

        glPushMatrix();
                //   ^ Z R Í ¸ _ Ì À Ñ ª \ Ê © ç Ý Ä E ñ è
                glGetIntegerv(GL_FRONT_FACE,&intFrontFace);
                glFrontFace(GL_CW);
                dalpha = (double)mqoobj[num].alpha/(double)255;

                for ( o=0; o<mqoobj[num].objnum; o++ ) {        //  à   I u W F N g   [ v

                        obj = &mqoobj[num].obj[o];
                        if ( ! obj->isVisible ) continue;
                        glShadeModel(((obj->isShadingFlat))?GL_FLAT:GL_SMOOTH);

                        for ( m = 0; m < obj->matnum; m++ ) {   // } e   A     [ v

                                mat = &obj->mat[m];
                                if ( mat->datanum == 0 ) continue;

                                if ( mat->isValidMaterialInfo ) {       //  } e   A   Ì î ñ Ý è
                                        memcpy(matenv,mat->dif,sizeof(matenv));
                                        matenv[3] *= dalpha;
                                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matenv);
                                        memcpy(matenv,mat->amb,sizeof(matenv));
                                        matenv[3] *= dalpha;
                                        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matenv);
                                        memcpy(matenv,mat->spc,sizeof(matenv));
                                        matenv[3] *= dalpha;
                                        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matenv);
                                        memcpy(matenv,mat->emi,sizeof(matenv));
                                        matenv[3] *= dalpha;
                                        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matenv);
                                        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat->power);
                                }

                                if ( mat->isUseTexture) {       //  e N X `   ª   é ê  
                                        glEnableClientState( GL_VERTEX_ARRAY );
                                        glEnableClientState( GL_NORMAL_ARRAY );
                                        glEnableClientState( GL_TEXTURE_COORD_ARRAY );

                                        isGL_TEXTURE_2D = glIsEnabled(GL_TEXTURE_2D);
                                        isGL_BLEND = glIsEnabled(GL_BLEND);
                                        glGetIntegerv(GL_TEXTURE_BINDING_2D,&bindGL_TEXTURE_2D);
//                                      glGetIntegerv(GL_BLEND_SRC_ALPHA,&blendGL_SRC_ALPHA);

                                        glEnable(GL_TEXTURE_2D);
                                        glEnable(GL_BLEND);
                                        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

                                        glBindTexture(GL_TEXTURE_2D,mat->texture_id);

                                        if ( g_isVBOSupported ) {       //  ¸ _ o b t @ g p
                                                base = (char *)NULL;    //  A h   X ÍNULL ª æ ª
                                                glBindBufferARB( GL_ARRAY_BUFFER_ARB, mat->VBO_id ); //  ¸ _ o b t @ ð   Ñ Â ¯ é
                                        }
                                        else {
                                                //  ¸ _ z ñ Ì   Í A A h   X ð » Ì Ü Ü ü ê é
                                                base = (char *)mat->vertex_t[0].point;
                                        }

                                        //  ¸ _ z ñ ð Ý è
                                        offset = (int)( (char *)mat->vertex_t[0].point - (char *)mat->vertex_t[0].point );
                                        glVertexPointer( 3, GL_FLOAT, sizeof(VERTEX_TEXUSE) , base + offset );

                                        //  e N X `   À W z ñ ð Ý è
                                        offset = (int)((char *)mat->vertex_t[0].uv-(char *)mat->vertex_t[0].point);
                                        glTexCoordPointer( 2, GL_FLOAT, sizeof(VERTEX_TEXUSE) , base + offset );

                                        //  @ ü z ñ ð Ý è
                                        offset = (int)((char *)mat->vertex_t[0].normal-(char *)mat->vertex_t[0].point);
                                        glNormalPointer( GL_FLOAT, sizeof(VERTEX_TEXUSE) , base+offset );

                                        //  F Ý è
                                        glColor4f(mat->color[0],mat->color[1],mat->color[2],mat->color[3]);

                                        //  ` æ À s
                                        glDrawArrays( GL_TRIANGLES, 0, mat->datanum );

                                        glBindTexture(GL_TEXTURE_2D,bindGL_TEXTURE_2D);
                                        if( isGL_BLEND == GL_FALSE ) glDisable(GL_BLEND);
                                        if( isGL_TEXTURE_2D == GL_FALSE ) glDisable(GL_TEXTURE_2D);

                                        if ( g_isVBOSupported ) {                                               //  ¸ _ o b t @ g p
                                                glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );      //  ¸ _ o b t @ ð f t H   g Ö
                                        }

                                        glDisableClientState( GL_VERTEX_ARRAY );
                                        glDisableClientState( GL_NORMAL_ARRAY );
                                        glDisableClientState( GL_TEXTURE_COORD_ARRAY );
                                }
                                else {  //  e N X `   ª È ¢ ê  

                                        glEnableClientState( GL_VERTEX_ARRAY );
                                        glEnableClientState( GL_NORMAL_ARRAY );
                                //      glEnableClientState( GL_COLOR_ARRAY );

                                        isGL_BLEND = glIsEnabled(GL_BLEND);
                                        glEnable(GL_BLEND);
                                        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

                                        if ( g_isVBOSupported ) {       //  ¸ _ o b t @ g p
                                                base = (char *)NULL;
                                                glBindBufferARB( GL_ARRAY_BUFFER_ARB, mat->VBO_id );
                                        }
                                        else {
                                                base = (char *)mat->vertex_p[0].point;
                                        }

                                        //  ¸ _ z ñ ð Ý è
                                        offset = (int)((char *)mat->vertex_p[0].point-(char *)mat->vertex_p[0].point);
                                        glVertexPointer( 3, GL_FLOAT, sizeof(VERTEX_NOTEX) , base+offset );

                                        //  @ ü z ñ ð Ý è
                                        offset = (int)((char *)mat->vertex_p[0].normal-(char *)mat->vertex_p[0].point);
                                        glNormalPointer( GL_FLOAT, sizeof(VERTEX_NOTEX) , base+offset );

                                        //  F Ý è
                                        glColor4f(mat->color[0],mat->color[1],mat->color[2],mat->color[3]);
                                //      offset = (int)((char *)mat->vertex_p[0].color-(char *)mat->vertex_p[0].point);
                                //      glColorPointer(4,GL_FLOAT,sizeof(VERTEX_NOTEX),base+offset);

                                        //  ` æ À s
                                        glDrawArrays( GL_TRIANGLES, 0, mat->datanum );

                                        if( isGL_BLEND == GL_FALSE ) glDisable(GL_BLEND);
                                        if ( g_isVBOSupported ) {                                               //  ¸ _ o b t @ g p
                                                glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );      //  ¸ _ o b t @ ð f t H   g Ö
                                        }

                                //      glDisableClientState( GL_COLOR_ARRAY );
                                        glDisableClientState( GL_VERTEX_ARRAY );
                                        glDisableClientState( GL_NORMAL_ARRAY );

                                }
                        }
                }

                //   ^ Z R Í ¸ _ Ì À Ñ ª \ Ê © ç Ý Ä E ñ è i ³ Ì Ý è É à Ç · j
                glFrontFace(intFrontFace);
        glPopMatrix();
}


/*=========================================================================
 y Ö   zmqoGetDirectory
 y p r z t @ C   ¼ ð Ü Þ p X ¶   ñ © ç f B   N g   Ì p X Ì Ý ð   o · é
 y ø   z
                *path_file       t @ C   ¼ ð Ü Þ p X ¶   ñ i ü Í j
                *path_dir        t @ C   ¼ ð   ¢ ½ p X ¶   ñ i o Í j

 y ß l z È µ
 y d l z á F
                "C:/data/file.bmp"  ¨ "C:/data/"
                "data/file.mqo"     ¨ "data/"
=========================================================================*/

void mqoGetDirectory(const char *path_file, char *path_dir)
{
        char *pStr;
        int len;

        pStr = MAX( strrchr(path_file,'\\'), strrchr(path_file,'/') );
        len = MAX((int)(pStr-path_file)+1,0);
        strncpy(path_dir,path_file,len);
        path_dir[len] = (char)0;
}


/*=========================================================================
 y Ö   zmqoSnormal
 y p r z @ ü x N g   ð   ß é
 y ø   z
                A               3   ³ À W ã Ì _A
                B               3   ³ À W ã Ì _B
                C               3   ³ À W ã Ì _C
                *normal  x N g  BA Æ x N g  BC Ì @ ü x N g   i E Ë ¶ û ü j

 y ß l z È µ
 y d l z   ^ Z R C A É ¨ ¢ Ä Ê ð \ ¬ · é ¸ _ Ì Ô   Í C \ ¦ Ê © ç © Ä
                   v ñ è É L q µ Ä   é D Â Ü è C ¸ _A,B,C  ª   Á ½ Æ « C
                   ß é × « @ ü ÍBA ÆBC Ì O Ï É æ Á Ä   ß ç ê é
=========================================================================*/

void mqoSnormal(glPOINT3f A, glPOINT3f B, glPOINT3f C, glPOINT3f *normal)
{
        double norm;
        glPOINT3f vec0,vec1;

        //  x N g  BA
        vec0.x = A.x - B.x;
        vec0.y = A.y - B.y;
        vec0.z = A.z - B.z;

        //  x N g  BC
        vec1.x = C.x - B.x;
        vec1.y = C.y - B.y;
        vec1.z = C.z - B.z;

        //  @ ü x N g  
        normal->x = vec0.y * vec1.z - vec0.z * vec1.y;
        normal->y = vec0.z * vec1.x - vec0.x * vec1.z;
        normal->z = vec0.x * vec1.y - vec0.y * vec1.x;

        //  ³ K »
        norm = normal->x * normal->x + normal->y * normal->y + normal->z * normal->z;
        norm = sqrt ( norm );

        normal->x /= norm;
        normal->y /= norm;
        normal->z /= norm;
}


/*=========================================================================
 y Ö   zmqoReadMaterial
 y p r z } e   A   î ñ Ì Ç Ý   Ý
 y ø   z
                fp               t @ C   | C   ^
                M                } e   A   z ñ

 y ß l z È µ
 y d l zmqoCreateModel(), mqoCreateSequence() Ì T u Ö   D
=========================================================================*/

void mqoReadMaterial(FILE *fp, MQO_MATDATA M[])
{
        GLfloat         dif, amb, emi, spc;
        glCOLOR4f       c;
        char            buf[SIZE_STR];
        char            *pStrEnd, *pStr;
        int                     len;
        int                     i = 0;

        while (1) {
                fgets(buf,SIZE_STR,fp); //  s Ç Ý   Ý
                if (strstr(buf,"}")) break;

                pStr = strstr(buf,"col(");      //  Þ ¿ ¼ Ç Ý ò Î µ
                sscanf( pStr,
                                "col(%f %f %f %f) dif (%f) amb(%f) emi(%f) spc(%f) power(%f)",
                                &c.r, &c.g, &c.b, &c.a, &dif, &amb, &emi, &spc, &M[i].power );

                //  ¸ _ J   [
                M[i].col = c;

                //  g U õ
                M[i].dif[0] = dif * c.r;
                M[i].dif[1] = dif * c.g;
                M[i].dif[2] = dif * c.b;
                M[i].dif[3] = c.a;

                //  ü Í õ
                M[i].amb[0] = amb * c.r;
                M[i].amb[1] = amb * c.g;
                M[i].amb[2] = amb * c.b;
                M[i].amb[3] = c.a;

                //  © È Æ ¾
                M[i].emi[0] = emi * c.r;
                M[i].emi[1] = emi * c.g;
                M[i].emi[2] = emi * c.b;
                M[i].emi[3] = c.a;

                //  ½ Ë õ
                M[i].spc[0] = spc * c.r;
                M[i].spc[1] = spc * c.g;
                M[i].spc[2] = spc * c.b;
                M[i].spc[3] = c.a;

                // tex F Í l } b s   O ¼
                if ( (pStr = strstr(buf,"tex(")) != NULL ) {
                        M[i].useTex = TRUE;

                        pStrEnd = strstr(pStr,")")-1;
                        len = pStrEnd - (pStr+5);
                        strncpy(M[i].texFile,pStr+5,len);
                        M[i].texFile[len] = (char)0;
                        if ( (pStr = strstr(buf,"aplane(")) != NULL ) {
                                pStrEnd = strstr(pStr,")")-1;
                                len = pStrEnd - (pStr+8);
                                strncpy(M[i].alpFile,pStr+8,len);
                                M[i].alpFile[len] = (char)0;
                        }
                        else {
                                M[i].alpFile[0] = (char)0;
                        }

                } else {
                        M[i].useTex = FALSE;
                        M[i].texFile[0] = (char)0;
                        M[i].alpFile[0] = (char)0;
                }

                i++;
        }

}


/*=========================================================================
 y Ö   zmqoReadVertex
 y p r z ¸ _ î ñ Ì Ç Ý   Ý
 y ø   z
                fp               » Ý I [ v   µ Ä ¢ é   ^ Z R C A t @ C   Ì t @ C   | C   ^
                V                ¸ _ ð i [ · é z ñ

 y ß l z È µ
 y d l zmqoReadObject() Ì T u Ö  
=========================================================================*/

void mqoReadVertex(FILE *fp, glPOINT3f V[])
{
        char buf[SIZE_STR];
        int  i=0;

        while (1) {
                fgets(buf,SIZE_STR,fp);
                if (strstr(buf,"}")) break;
                sscanf(buf,"%f %f %f",&V[i].x,&V[i].y,&V[i].z);
                i++;
        }
}


/*=========================================================================
 y Ö   zmqoReadBVertex
 y p r z o C i   ` ® Ì ¸ _ î ñ ð Ç Ý   Þ
 y ø   z
                fp               » Ý I [ v   µ Ä ¢ é   ^ Z R C A t @ C   Ì t @ C   | C   ^
                V                ¸ _ ð i [ · é z ñ

 y ß l z ¸ _  
 y d l zmqoReadObject() Ì T u Ö  
=========================================================================*/

int mqoReadBVertex(FILE *fp, glPOINT3f V[])
{
        int n_vertex,i;
        float *wf;
        int size;
        char cw[256];
        char *pStr;

        fgets(cw,sizeof(cw),fp);
        if ( (pStr = strstr(cw,"Vector")) != NULL ) {
                sscanf(pStr,"Vector %d [%d]",&n_vertex,&size);  //  ¸ _   A f [ ^ T C Y ð Ç Ý   Þ
        }
        else {
                return -1;
        }
        //MQO t @ C   Ì o C i   ¸ _ f [ ^ Íintel ` ® i   g   G f B A   j
        wf = (float *)malloc(size);
        fread(wf,size,1,fp);
        for ( i = 0; i < n_vertex; i++ ) {
                V[i].x = wf[i*3+0];
                V[i].y = wf[i*3+1];
                V[i].z = wf[i*3+2];
#if DEF_IS_LITTLE_ENDIAN
#else
                endianConverter((void *)&V[i].x,sizeof(V[i].x));
                endianConverter(&V[i].y,sizeof(V[i].y));
                endianConverter(&V[i].z,sizeof(V[i].z));
#endif
        }
        free(wf);

        // "}" Ü Å Ç Ý ò Î µ
        {
                char buf[SIZE_STR];
                while (1) {
                        fgets(buf,SIZE_STR,fp);
                        if (strstr(buf,"}")) break;
                }
        }

        return n_vertex;
}


/*=========================================================================
 y Ö   zmqoReadFace
 y p r z Ê î ñ Ì Ç Ý   Ý
 y ø   z
                fp               t @ C   | C   ^
                F                Ê z ñ

 y ß l z È µ
 y d l zmqoReadObject() Ì T u Ö  
=========================================================================*/

void mqoReadFace(FILE *fp, MQO_FACE F[])
{
        char buf[SIZE_STR];
        char *pStr;
        int  i=0;

        while (1) {
                fgets(buf,SIZE_STR,fp);
                if (strstr(buf,"}")) break;

                //  Ê ð \ ¬ · é ¸ _  
                sscanf(buf,"%d",&F[i].n);

                //  ¸ _(V) Ì Ç Ý   Ý
                if ( (pStr = strstr(buf,"V(")) != NULL ) {
                        switch (F[i].n) {
                                case 3:
//   ^ Z R Í ¸ _ Ì À Ñ ª \ Ê © ç Ý Ä E ñ è
// Ç Ý   Ý   É À × Ö ¦ é û @ à   é B ¯ Ç A \ Ê Ì Ý è ð
//glFrontFace Å Ï ¦ é Ù ¤ ª X } [ g H
                                        sscanf(pStr,"V(%d %d %d)",&F[i].v[0],&F[i].v[1],&F[i].v[2]);
//                                      sscanf(pStr,"V(%d %d %d)",&F[i].v[2],&F[i].v[1],&F[i].v[0]);
                                        break;
                                case 4:
                                        sscanf(pStr,"V(%d %d %d %d)",&F[i].v[0],&F[i].v[1],&F[i].v[2],&F[i].v[3]);
//                                      sscanf(pStr,"V(%d %d %d %d)",&F[i].v[3],&F[i].v[2],&F[i].v[1],&F[i].v[0]);
                                        break;
                                default:
                                        break;
                        }
                }

                //  } e   A  (M) Ì Ç Ý   Ý
                F[i].m = 0;
                if ( (pStr = strstr(buf,"M(")) != NULL ) {
                        sscanf(pStr,"M(%d)",&F[i].m);
                }
                else { //  } e   A   ª Ý è ³ ê Ä ¢ È ¢ Ê
                        F[i].m = -1;
                }

                // UV } b v(UV) Ì Ç Ý   Ý
                if ( (pStr = strstr(buf,"UV(")) != NULL ) {
                        switch (F[i].n) {
                                case 3: //  ¸ _  3
                                        sscanf(pStr,"UV(%f %f %f %f %f %f)",
                                                                        &F[i].uv[0].x, &F[i].uv[0].y,
                                                                        &F[i].uv[1].x, &F[i].uv[1].y,
                                                                        &F[i].uv[2].x, &F[i].uv[2].y
                                                                        );
                                        break;

                                case 4: //  ¸ _  4
                                        sscanf(pStr,"UV(%f %f %f %f %f %f %f %f)",
                                                                        &F[i].uv[0].x, &F[i].uv[0].y,
                                                                        &F[i].uv[1].x, &F[i].uv[1].y,
                                                                        &F[i].uv[2].x, &F[i].uv[2].y,
                                                                        &F[i].uv[3].x, &F[i].uv[3].y
                                                                        );
                                        break;
                                default:
                                        break;
                        }
                }

                i++;
        }

}


/*=========================================================================
 y Ö   zmqoReadObject
 y p r z I u W F N g î ñ Ì Ç Ý   Ý
 y ø   z
                fp               t @ C   | C   ^
                obj              I u W F N g î ñ

 y ß l z È µ
 y d l z ± Ì Ö   Å P Â Ì I u W F N g î ñ ª Ç Ý   Ü ê é D
=========================================================================*/

void mqoReadObject(FILE *fp, MQO_OBJDATA *obj)
{
        char buf[SIZE_STR];

        while (1) {
                fgets(buf,SIZE_STR,fp);
                if (strstr(buf,"}")) break;

                // visible
                if (strstr(buf,"visible ")) {
                        sscanf(buf," visible %d", &obj->visible);
                }

                // shading
                if (strstr(buf,"shading ")) {
                        sscanf(buf," shading %d", &obj->shading);
                }

                // facet
                if (strstr(buf,"facet ")) {
                        sscanf(buf," facet %f", &obj->facet);
                }

                // vertex
                if (strstr(buf,"vertex ")) {
                        sscanf(buf," vertex %d", &obj->n_vertex);
                        obj->V = (glPOINT3f*) calloc( obj->n_vertex, sizeof(glPOINT3f) );
                        mqoReadVertex(fp, obj->V);
                }
                // BVertex
                if (strstr(buf,"BVertex"))      {
                        sscanf(buf," BVertex %d", &obj->n_vertex);
                        obj->V = (glPOINT3f*) calloc( obj->n_vertex, sizeof(glPOINT3f) );
                        mqoReadBVertex(fp,obj->V);
                }

                // face
                if (strstr(buf,"face ")) {
                        sscanf(buf," face %d", &obj->n_face);
                        obj->F = (MQO_FACE*) calloc( obj->n_face, sizeof(MQO_FACE) );
                        mqoReadFace(fp, obj->F);
                }

        }

}


/*=========================================================================
 y Ö   zmqoMakeArray
 y p r z ¸ _ z ñ Ì ì ¬
 y ø   z
                mat              } e   A   i ± Ì   É ¸ _ f [ ^ ð Ü Þ j
                matpos   Þ ¿ Ô  
                F                Ê
                fnum     Ê  
                V                ¸ _
                N                @ ü
                facet    X   [ W   O p
                mcol     F
                scale    X P [  
                alpha    A   t @

 y ß l z È µ
 y d l z ¸ _ z ñ Í · × Ä O p É · é Ì Å A l p Í O p   Q É ª  
                  0  3      0    0  3
                         ¨ @ ¢ @ @ ¤
                  1  2     1  2   2
=========================================================================*/

void mqoMakeArray( MQO_MATERIAL *mat, int matpos, MQO_FACE F[], int fnum,glPOINT3f V[],
                                   glPOINT3f N[], double facet, glCOLOR4f *mcol, double scale, unsigned char alpha )
{
        int f;
        int i;
        int dpos;
        double s;
        glPOINT3f normal;       //  @ ü x N g  

        dpos = 0;
        mat->color[0] = mcol->r;
        mat->color[1] = mcol->g;
        mat->color[2] = mcol->b;
        mat->color[3] = mcol->a;
        if ( mat->isUseTexture ) {
                for ( f = 0; f < fnum; f++ ){
                        if ( F[f].m != matpos ) continue;
                        if ( F[f].n == 3 ) {
                                mqoSnormal(V[F[f].v[0]],V[F[f].v[1]],V[F[f].v[2]],&normal);     //  @ ü x N g   ð v Z
                                for ( i = 0; i < 3; i++ ) {
                                        mat->vertex_t[dpos].point[0] = V[F[f].v[i]].x*scale;
                                        mat->vertex_t[dpos].point[1] = V[F[f].v[i]].y*scale;
                                        mat->vertex_t[dpos].point[2] = V[F[f].v[i]].z*scale;
                                        mat->vertex_t[dpos].uv[0] = F[f].uv[i].x;
                                        mat->vertex_t[dpos].uv[1] = F[f].uv[i].y;
                                        s = acos(normal.x*N[F[f].v[i]].x + normal.y*N[F[f].v[i]].y + normal.z*N[F[f].v[i]].z);
                                        if ( facet < s ) {
                                                //  X   [ W   O p @   i ¸ _ @ ü Æ Ê @ ü Ì p x j Ì Æ « Í Ê @ ü ð ¸ _ @ ü Æ · é
                                                mat->vertex_t[dpos].normal[0] = normal.x;
                                                mat->vertex_t[dpos].normal[1] = normal.y;
                                                mat->vertex_t[dpos].normal[2] = normal.z;
                                        }
                                        else {
                                                mat->vertex_t[dpos].normal[0] = N[F[f].v[i]].x;
                                                mat->vertex_t[dpos].normal[1] = N[F[f].v[i]].y;
                                                mat->vertex_t[dpos].normal[2] = N[F[f].v[i]].z;
                                        }
                                        dpos++;
                                }
                        }
                        // S ¸ _ i l p j Í R ¸ _ i O p j   Q É ª  
                        if ( F[f].n == 4 ) {
                                mqoSnormal(V[F[f].v[0]],V[F[f].v[1]],V[F[f].v[2]],&normal);     //  @ ü x N g   ð v Z
                                for ( i = 0; i < 4; i++ ) {
                                        if ( i == 3 ) continue;
                                        mat->vertex_t[dpos].point[0] = V[F[f].v[i]].x*scale;
                                        mat->vertex_t[dpos].point[1] = V[F[f].v[i]].y*scale;
                                        mat->vertex_t[dpos].point[2] = V[F[f].v[i]].z*scale;
                                        mat->vertex_t[dpos].uv[0] = F[f].uv[i].x;
                                        mat->vertex_t[dpos].uv[1] = F[f].uv[i].y;
                                        s = acos(normal.x*N[F[f].v[i]].x + normal.y*N[F[f].v[i]].y + normal.z*N[F[f].v[i]].z);
                                        if ( facet < s ) {
                                                mat->vertex_t[dpos].normal[0] = normal.x;
                                                mat->vertex_t[dpos].normal[1] = normal.y;
                                                mat->vertex_t[dpos].normal[2] = normal.z;
                                        }
                                        else {
                                                mat->vertex_t[dpos].normal[0] = N[F[f].v[i]].x;
                                                mat->vertex_t[dpos].normal[1] = N[F[f].v[i]].y;
                                                mat->vertex_t[dpos].normal[2] = N[F[f].v[i]].z;
                                        }
                                        dpos++;
                                }
                                mqoSnormal(V[F[f].v[0]],V[F[f].v[2]],V[F[f].v[3]],&normal);     //  @ ü x N g   ð v Z
                                for ( i = 0; i < 4; i++ ) {
                                        if ( i == 1 ) continue;
                                        mat->vertex_t[dpos].point[0] = V[F[f].v[i]].x*scale;
                                        mat->vertex_t[dpos].point[1] = V[F[f].v[i]].y*scale;
                                        mat->vertex_t[dpos].point[2] = V[F[f].v[i]].z*scale;
                                        mat->vertex_t[dpos].uv[0] = F[f].uv[i].x;
                                        mat->vertex_t[dpos].uv[1] = F[f].uv[i].y;
                                        s = acos(normal.x*N[F[f].v[i]].x + normal.y*N[F[f].v[i]].y + normal.z*N[F[f].v[i]].z);
                                        if ( facet < s ) {
                                                mat->vertex_t[dpos].normal[0] = normal.x;
                                                mat->vertex_t[dpos].normal[1] = normal.y;
                                                mat->vertex_t[dpos].normal[2] = normal.z;
                                        }
                                        else {
                                                mat->vertex_t[dpos].normal[0] = N[F[f].v[i]].x;
                                                mat->vertex_t[dpos].normal[1] = N[F[f].v[i]].y;
                                                mat->vertex_t[dpos].normal[2] = N[F[f].v[i]].z;
                                        }
                                        dpos++;
                                }
                        }
                }
        }
        else {
                if ( alpha != 255 ) {
                        mat->color[3] = (double)alpha/(double)255;
                }
                for ( f = 0; f < fnum; f++ ){
                        if ( F[f].m != matpos ) continue;
                        if ( F[f].n == 3 ) {
                                mqoSnormal(V[F[f].v[0]],V[F[f].v[1]],V[F[f].v[2]],&normal);             //  @ ü x N g   ð v Z
                                for ( i = 0; i < 3; i++ ) {
                                        mat->vertex_p[dpos].point[0] = V[F[f].v[i]].x*scale;
                                        mat->vertex_p[dpos].point[1] = V[F[f].v[i]].y*scale;
                                        mat->vertex_p[dpos].point[2] = V[F[f].v[i]].z*scale;
                                        mat->vertex_p[dpos].normal[0] = normal.x;
                                        mat->vertex_p[dpos].normal[1] = normal.y;
                                        mat->vertex_p[dpos].normal[2] = normal.z;
                                        s = acos(normal.x*N[F[f].v[i]].x + normal.y*N[F[f].v[i]].y + normal.z*N[F[f].v[i]].z);
                                        if ( facet < s ) {
                                                mat->vertex_p[dpos].normal[0] = normal.x;
                                                mat->vertex_p[dpos].normal[1] = normal.y;
                                                mat->vertex_p[dpos].normal[2] = normal.z;
                                        }
                                        else {
                                                mat->vertex_p[dpos].normal[0] = N[F[f].v[i]].x;
                                                mat->vertex_p[dpos].normal[1] = N[F[f].v[i]].y;
                                                mat->vertex_p[dpos].normal[2] = N[F[f].v[i]].z;
                                        }
                                        dpos++;
                                }
                        }
                        // S ¸ _ i l p j Í R ¸ _ i O p j   Q É ª  
                        if ( F[f].n == 4 ) {
                                mqoSnormal(V[F[f].v[0]],V[F[f].v[1]],V[F[f].v[2]],&normal);             //  @ ü x N g   ð v Z
                                for ( i = 0; i < 4; i++ ) {
                                        if ( i == 3 ) continue;
                                        mat->vertex_p[dpos].point[0] = V[F[f].v[i]].x*scale;
                                        mat->vertex_p[dpos].point[1] = V[F[f].v[i]].y*scale;
                                        mat->vertex_p[dpos].point[2] = V[F[f].v[i]].z*scale;
                                        mat->vertex_p[dpos].normal[0] = normal.x;
                                        mat->vertex_p[dpos].normal[1] = normal.y;
                                        mat->vertex_p[dpos].normal[2] = normal.z;
                                        s = acos(normal.x*N[F[f].v[i]].x + normal.y*N[F[f].v[i]].y + normal.z*N[F[f].v[i]].z);
                                        if ( facet < s ) {
                                                mat->vertex_p[dpos].normal[0] = normal.x;
                                                mat->vertex_p[dpos].normal[1] = normal.y;
                                                mat->vertex_p[dpos].normal[2] = normal.z;
                                        }
                                        else {
                                                mat->vertex_p[dpos].normal[0] = N[F[f].v[i]].x;
                                                mat->vertex_p[dpos].normal[1] = N[F[f].v[i]].y;
                                                mat->vertex_p[dpos].normal[2] = N[F[f].v[i]].z;
                                        }
                                        dpos++;
                                }
                                mqoSnormal(V[F[f].v[0]],V[F[f].v[2]],V[F[f].v[3]],&normal);             //  @ ü x N g   ð v Z
                                for ( i = 0; i < 4; i++ ) {
                                        if ( i == 1 ) continue;
                                        mat->vertex_p[dpos].point[0] = V[F[f].v[i]].x*scale;
                                        mat->vertex_p[dpos].point[1] = V[F[f].v[i]].y*scale;
                                        mat->vertex_p[dpos].point[2] = V[F[f].v[i]].z*scale;
                                        mat->vertex_p[dpos].normal[0] = normal.x;
                                        mat->vertex_p[dpos].normal[1] = normal.y;
                                        mat->vertex_p[dpos].normal[2] = normal.z;
                                        s = acos(normal.x*N[F[f].v[i]].x + normal.y*N[F[f].v[i]].y + normal.z*N[F[f].v[i]].z);
                                        if ( facet < s ) {
                                                mat->vertex_p[dpos].normal[0] = normal.x;
                                                mat->vertex_p[dpos].normal[1] = normal.y;
                                                mat->vertex_p[dpos].normal[2] = normal.z;
                                        }
                                        else {
                                                mat->vertex_p[dpos].normal[0] = N[F[f].v[i]].x;
                                                mat->vertex_p[dpos].normal[1] = N[F[f].v[i]].y;
                                                mat->vertex_p[dpos].normal[2] = N[F[f].v[i]].z;
                                        }
                                        dpos++;
                                }
                        }
                }
        }
}


/*=========================================================================
 y Ö   zmqoVertexNormal
 y p r z ¸ _ @ ü Ì v Z
 y ø   z
                obj                      I u W F N g î ñ

 y ß l z @ ü z ñ
 y d l z S ¸ _ Ì Ê Í O p ` É ª   µ Ä v Z
                 ß è l Í K ¸ Ä Ñ o µ ³ Å ð ú ifree j · é ± Æ I
=========================================================================*/

glPOINT3f * mqoVertexNormal(MQO_OBJDATA *obj)
{
        int f;
        int v;
        int i;
        double len;
        glPOINT3f fnormal;      //  Ê @ ü x N g  
        MQO_FACE *F;
        glPOINT3f *V;
        glPOINT3f *ret;
        F = obj->F;
        V = obj->V;
        ret = (glPOINT3f *)calloc(obj->n_vertex,sizeof(glPOINT3f));
        // Ê Ì @ ü ð ¸ _ É « µ   Ý
        for ( f = 0; f < obj->n_face; f++ ) {
                if ( obj->F[f].n == 3 ) {
                        mqoSnormal(V[F[f].v[0]],V[F[f].v[1]],V[F[f].v[2]],&fnormal);
                        for ( i = 0; i < 3; i++ ) {
                                ret[F[f].v[i]].x += fnormal.x;
                                ret[F[f].v[i]].y += fnormal.y;
                                ret[F[f].v[i]].z += fnormal.z;
                        }
                }
                if ( obj->F[f].n == 4 ) {
                        mqoSnormal(V[F[f].v[0]],V[F[f].v[1]],V[F[f].v[2]],&fnormal);
                        for ( i = 0; i < 4; i++ ) {
                                if ( i == 3 ) continue;
                                ret[F[f].v[i]].x += fnormal.x;
                                ret[F[f].v[i]].y += fnormal.y;
                                ret[F[f].v[i]].z += fnormal.z;
                        }
                        mqoSnormal(V[F[f].v[0]],V[F[f].v[2]],V[F[f].v[3]],&fnormal);
                        for ( i = 0; i < 4; i++ ) {
                                if ( i == 1 ) continue;
                                ret[F[f].v[i]].x += fnormal.x;
                                ret[F[f].v[i]].y += fnormal.y;
                                ret[F[f].v[i]].z += fnormal.z;
                        }
                }
        }
        // ³ K »
        for ( v = 0; v < obj->n_vertex; v++ ) {
                if ( ret[v].x == 0 && ret[v].y == 0 && ret[v].z == 0 ) {
                        // Ê É g í ê Ä È ¢ _
                        continue;
                }
                len = sqrt(ret[v].x*ret[v].x + ret[v].y*ret[v].y + ret[v].z*ret[v].z);
                if ( len != 0 ) {
                        ret[v].x = ret[v].x/len;
                        ret[v].y = ret[v].y/len;
                        ret[v].z = ret[v].z/len;
                }
        }

        return ret;
}

/*=========================================================================
 y Ö   zmqoMakePolygon
 y p r z |   S   Ì ¶ ¬
 y ø   z
                readObj          Ç Ý   ñ ¾ I u W F N g î ñ
                mqoobj          MQO I u W F N g
                N[]                      @ ü z ñ
                M[]                      } e   A   z ñ
                n_mat            } e   A    
                scale            X P [  
                alpha            A   t @

 y ß l z È µ
=========================================================================*/

void mqoMakePolygon(MQO_OBJDATA *readObj, MQO_OBJECT *mqoobj,
                                        glPOINT3f N[], MQO_MATDATA M[], int n_mat, double scale, unsigned char alpha)
{

        MQO_INNER_OBJECT                *setObj;
        MQO_MATERIAL                    *material;
        glCOLOR4f                               defcol;
        glCOLOR4f                               *pcol;
        int                                             f, m, *mat_vnum;
        int                                             fnum;
        MQO_FACE                                *F;
        glPOINT3f                               *V;
        double                                  facet;


        setObj = &mqoobj->obj[mqoobj->objnum];
        strcpy(setObj->objname,readObj->objname);
        setObj->isVisible = readObj->visible;
        setObj->isShadingFlat = (readObj->shading == 0);
        F = readObj->F;
        fnum = readObj->n_face;
        V = readObj->V;
        facet = readObj->facet;

        // face Ì   Å Ì } e   A     Ì ¸ _ Ì  
        // M=NULL Ì Æ « AF[].m = 0  ª ü Á Ä ­ é
        if ( M == NULL ) n_mat = 1;

        mat_vnum = (int *)malloc(sizeof(int)*n_mat);
        memset(mat_vnum,0,sizeof(int)*n_mat);

        for ( f = 0; f < fnum; f++ ){
                if( F[f].m < 0 ) continue; //  } e   A   ª Ý è ³ ê Ä ¢ È ¢ Ê
                if ( F[f].n == 3 ) {
                        mat_vnum[F[f].m] += 3;
                }
                if ( F[f].n == 4 ) {
                        // S ¸ _ i l p j Í R ¸ _ i O p j   Q É ª  
                        //  0  3      0    0  3
                        //         ¨ @ ¢ @ @ ¤
                        //  1  2     1  2   2
                        //  S ¸ _ Ì ½ Ê f [ ^ Í
                        //  R ¸ _ Ì ½ Ê f [ ^   Q Â
                        mat_vnum[F[f].m] += 3*2;
                }
                if ( setObj->matnum < F[f].m+1 ) setObj->matnum = F[f].m+1;
        }

        //  } e   A   Ê É ¸ _ z ñ ð ì ¬ · é
        setObj->mat = (MQO_MATERIAL *)malloc(sizeof(MQO_MATERIAL)*setObj->matnum);
        memset(setObj->mat,0,sizeof(MQO_MATERIAL)*setObj->matnum);

        for ( m = 0; m < setObj->matnum; m++ ) {
                material = &setObj->mat[m];
                material->datanum = mat_vnum[m];
                material->isValidMaterialInfo = (M != NULL);

                if ( mat_vnum[m] <= 0 ) continue;
                if ( material->isValidMaterialInfo ) {
                        memcpy(material->dif,M[m].dif,sizeof(material->dif));
                        memcpy(material->amb,M[m].amb,sizeof(material->amb));
                        memcpy(material->spc,M[m].spc,sizeof(material->spc));
                        memcpy(material->emi,M[m].emi,sizeof(material->emi));
                        material->power = M[m].power;
                        material->isUseTexture = M[m].useTex;
                        pcol = &M[m].col;
                }
                else {
                        defcol.r = 1.0;
                        defcol.g = 1.0;
                        defcol.b = 1.0;
                        defcol.a = 1.0;
                        material->isUseTexture = 0;
                        pcol = &defcol;
                }
                if ( material->isUseTexture ) {
                        material->vertex_t = (VERTEX_TEXUSE *)calloc(material->datanum,sizeof(VERTEX_TEXUSE));
                        material->texture_id = M[m].texName;
                }
                else {
                        material->vertex_p = (VERTEX_NOTEX *)calloc(material->datanum,sizeof(VERTEX_NOTEX));
                }
                mqoMakeArray(material,m,F,fnum,V,N,facet,pcol,scale,alpha);
                if (g_isVBOSupported) {
                        if ( material->isUseTexture ) {
                                glGenBuffersARB( 1, &material->VBO_id );
                                glBindBufferARB( GL_ARRAY_BUFFER_ARB, material->VBO_id  );
                                glBufferDataARB( GL_ARRAY_BUFFER_ARB, material->datanum*sizeof(VERTEX_TEXUSE), material->vertex_t, GL_STATIC_DRAW_ARB );
                        }
                        else {
                                glGenBuffersARB( 1, &material->VBO_id );
                                glBindBufferARB( GL_ARRAY_BUFFER_ARB, material->VBO_id  );
                                glBufferDataARB( GL_ARRAY_BUFFER_ARB, material->datanum*sizeof(VERTEX_NOTEX), material->vertex_p, GL_STATIC_DRAW_ARB );
                        }
                }
        }
        mqoobj->objnum++;
        if ( MAX_OBJECT <= mqoobj->objnum ) {
                printf("MQO t @ C   Ç Ý   Ý F @ Å å I u W F N g   ð ´ ¦ Ü µ ½[%d]\n",mqoobj->objnum);
                mqoobj->objnum = MAX_OBJECT-1;
        }

        free(mat_vnum);

}


/*=========================================================================
 y Ö   zmqoMakeObjectsEx
 y p r z I u W F N g Ì f [ ^ © ç |   S     f   ð ì ¬ · é
 y ø   z
                mqoobj  MQO I u W F N g
                obj              I u W F N g z ñ
                n_obj    I u W F N g Ì Â  
                M                } e   A   z ñ
                n_mat    } e   A   Ì Â  
                scale    g å ¦
                alpha    A   t @

 y ß l z È µ
=========================================================================*/

void mqoMakeObjectsEx( MQO_OBJECT *mqoobj, MQO_OBJDATA obj[], int n_obj, MQO_MATDATA M[],int n_mat,
                                           double scale,unsigned char alpha)
{
        int i;
        glPOINT3f *N;
        for (i=0; i<n_obj; i++) {
                N = mqoVertexNormal(&obj[i]);
                mqoMakePolygon(
                                &obj[i],
                                mqoobj,
                                N,
                                M,n_mat,
                                scale,
                                alpha);
                free(N);
        }
}


/*=========================================================================
 y Ö   zmqoCreateModel
 y p r zMQO t @ C   © çMQO   f   ð ì ¬ · é
 y ø   z
                filename        MQO t @ C  
                scale            g å ¦ i1.0 Å » Ì Ü Ü j

 y ß l zMQO_MODEL iMQO   f   j
=========================================================================*/

MQO_MODEL mqoCreateModel(char *filename, double scale)
{
        MQO_MODEL ret;
        ret = mqoCreateList(1);
        if ( mqoCreateListObject(ret,1-1,filename,scale,(unsigned char)255) < 0 ) {
                mqoDeleteObject(ret,1);
                ret = NULL;
        }
        return ret;
}


/*=========================================================================
 y Ö   zmqoCreateSequenceEx
 y p r z A Ô ÌMQO t @ C   © çMQO V [ P   X ð ì ¬ · é
 y ø   z
                format           t @ C   ¼ Ì   ®
                n_file           t @ C    
                scale            g å ¦ i1.0 Å » Ì Ü Ü j
                fade_inout      0: » Ì Ü Ü @ ³ F t F [ h C   @   F t F [ h A E g
                                         â Î l Í ø Ê ð © ¯ é t   [    
                alpha            A   t @

 y ß l zMQO_SEQUENCE iMQO V [ P   X j
 y õ l z A Ô Í0 © ç J n
=========================================================================*/

MQO_SEQUENCE mqoCreateSequenceEx(const char *format, int n_file, double scale,
                                                                 int fade_inout, unsigned char alpha)
{
        MQO_SEQUENCE retSeq;
        int iret;
        int seq;
        char filename[SIZE_STR];
        short setAlpha;
        short calAlpha;
        int frames;

        retSeq.n_frame = 0;
        if ( format == NULL ) {
                return retSeq;
        }
        calAlpha = alpha;
        frames = abs(fade_inout);
        frames = MAX(frames,n_file);
        setAlpha = (fade_inout<=0)?alpha:0;

        retSeq.model = mqoCreateList(n_file);
        for ( seq = 0; seq < frames; seq++ ) {
                if ( seq < n_file ) {
                        sprintf(filename,format,seq);
                }
                if ( (fade_inout !=  0) && ((frames-1) == seq) ) {
                        setAlpha = (fade_inout<0)?0:calAlpha;
                }
                iret = mqoCreateListObject(retSeq.model,seq,filename,scale,(unsigned char)setAlpha);
                if ( iret == - 1 ) {
                        seq--;
                        mqoClearObject(retSeq.model,seq,n_file-seq);
                        break;
                }
                if ( fade_inout !=  0 ) {
                        if ( fade_inout<0 ) {
                                if ( (n_file-seq) <= (-1*fade_inout) ) {
                                        setAlpha -= (calAlpha/(-1*fade_inout));
                                        if ( setAlpha < 0 ) setAlpha = 0;
                                }
                        }
                        else {
                                setAlpha += (calAlpha/fade_inout);
                                if ( calAlpha < setAlpha ) setAlpha = calAlpha;
                        }
                }
        }
        retSeq.n_frame = seq;
        return retSeq;
}


/*=========================================================================
 y Ö   zmqoCreateSequence
 y p r z A Ô ÌMQO t @ C   © çMQO V [ P   X ð ì ¬ · é
 y ø   z
                format           t @ C   ¼ Ì t H [ } b g
                n_file           t @ C    
                scale            g å ¦ i1.0 Å » Ì Ü Ü j

 y ß l zMQO_SEQUENCE iMQO V [ P   X j
 y õ l z A Ô Í0 © ç J n
=========================================================================*/

MQO_SEQUENCE mqoCreateSequence(const char *format, int n_file, double scale)
{
        return mqoCreateSequenceEx(format, n_file, scale, 0, (unsigned char)255);
}


/*=========================================================================
 y Ö   zmqoCallModel
 y p r zMQO   f   ðOpenGL Ì æ Ê ã É Ä Ñ o ·
 y ø   z
                model           MQO   f  

 y ß l z È µ
=========================================================================*/

void mqoCallModel(MQO_MODEL model)
{
        mqoCallListObject(model, 0);
}


/*=========================================================================
 y Ö   zmqoCallSequence
 y p r zMQO V [ P   X ðOpenGL Ì æ Ê É Ä Ñ o ·
 y ø   z
                seq             MQO V [ P   X
                i                t   [   Ô  

 y ß l z È µ
 y d l zMQO V [ P   X Ì   © ç w è µ ½ t   [   Ô   Ì   f   ð Ä Ñ o ·
=========================================================================*/

void mqoCallSequence(MQO_SEQUENCE seq, int i)
{
        if ( i>=0 && i<seq.n_frame ) {
                mqoCallListObject(seq.model,i);
        }
}


/*=========================================================================
 y Ö   zmqoClearObject
 y p r zMQO I u W F N g Ì N   A
 y ø   z
                object  MQO I u W F N g z ñ
                from     í   J n Ô   i0 ` j
                num              í   · é Â  

 y ß l z È µ
=========================================================================*/

void mqoClearObject( MQO_OBJECT object[], int from, int num )
{
        int                                     loop, o, m;
        MQO_INNER_OBJECT        *obj;
        MQO_MATERIAL            *mat;

        if ( object == NULL ) return;

        for ( loop = from; loop < from + num; loop++ ) {
                for ( o = 0; o < (object+from)->objnum; o++ ) {

                        obj = &(object+loop)->obj[o];
                        for ( m = 0; m < obj->matnum; m++ ) {
                                mat = &obj->mat[m];
                                if ( mat->datanum <= 0 ) continue;
                                if ( g_isVBOSupported ) {
                                        //  ¸ _ o b t @ Ì í  
                                        glDeleteBuffersARB( 1, &mat->VBO_id );
                                }

                                //  ¸ _ z ñ Ì í  
                                if ( mat->isUseTexture ) {
                                        if ( mat->vertex_t != NULL ) {
                                                free(mat->vertex_t);
                                                mat->vertex_t = NULL;
                                        }
                                }
                                else {
                                        if ( mat->vertex_p != NULL ) {
                                                free(mat->vertex_p);
                                                mat->vertex_p = NULL;
                                        }
                                }
                        }
                        if ( obj->mat != NULL ) {
                                free(obj->mat);
                                obj->mat = NULL;
                        }
                        obj->matnum = 0;
                }
        }

}


/*=========================================================================
 y Ö   zmqoDeleteObject
 y p r zMQO I u W F N g ð í   · é
 y ø   z
                object  MQO I u W F N g z ñ
                num              í   · é Â  

 y ß l z È µ
=========================================================================*/

void mqoDeleteObject(MQO_OBJECT object[], int num)
{
        mqoClearObject(object,0,num);
        free(object);
}


/*=========================================================================
 y Ö   zmqoDeleteModel
 y p r zMQO   f   ð í   · é
 y ø   z
                model   MQO   f  

 y ß l z È µ
 y õ l z í       ð s Á ½ Ï   ð Ä   p · é Â \ « ª   é ê   Í
                 ± Ì Ö   Ì À s ã ÉNULL ð ã ü µ Ä ¨ ­ ± Æ
=========================================================================*/

void mqoDeleteModel(MQO_MODEL model)
{
        mqoDeleteObject(model,1);
}


/*=========================================================================
 y Ö   zmqoDeleteSequence
 y p r zMQO V [ P   X ð í   · é
 y ø   z
                seq             MQO V [ P   X

 y õ l z í       ð s Á ½ Ï   ð Ä   p · é Â \ « ª   é ê   Í
                 ± Ì Ö   Ì À s ã ÉNULL ð ã ü µ Ä ¨ ­ ± Æ
=========================================================================*/

void mqoDeleteSequence(MQO_SEQUENCE seq)
{
        mqoDeleteObject( seq.model, seq.n_frame );
}
