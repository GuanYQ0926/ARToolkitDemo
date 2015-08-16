#ifndef __GLMETASEQ_H__
#define __GLMETASEQ_H__

/*=========================================================================================
           ^ Z R C A ? �� ? �� ?   f  (*.mqo) eOpenGL ? �� ? Y   T ?   e �� ? ? ?C/C++ p w b _
=========================================================================================*/

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

 �� o �� �� ? �� e   �� ] �� A { \ t g E F A �� ? ? ? A ?   �� t @ C   i �� o u \ t g
 E F A v j �� ? ? e ? ? �� �� �� �� ? �� l �� ? �� A \ t g E F A e 3 �� �� �� �� �� �� ? e
 3   ?   ? �� �� �� B �� �� �� �� A \ t g E F A �� ? ? e g p A ? �� A ? X A     A f �� A
 D z A T u   C Z   X A �� ? ?/ �� ? �� ��   �� ��     A �� ? ? \ t g E F A e ?   �� ��
   �� �� �� ? �� ? e   ? �� ��     �� 3 �� �� �� �� �� �� �� �� B

 ? L ��   ��   \ | �� ? ? {   ? \ | e A \ t g E F A �� �� �� ? �� ? ? �� ? �� d v ��   a
 �� L �� �� �� �� �� ? �� �� �� B

 \ t g E F A �� u ? �� �� �� �� v ? A ? | ?   �� ? ? �� ?   �� ? e a �� ? A ? ? �� ? ?
 �� �� - ?   3 �� �� �� B �� �� ? �� �� ? ? ? �� A �� i ? A �� �� �� �� I ? �� K   ? A �� ? ?
     ? N Q �� ? �� ? �� ? ? �� �� Y �� �� a A ? �� �� �� �� 3 �� �� �� �� ? ��   �� �� 1 ? B
 �� �� �� ? ��   ��   �� �� A _ ? s �� A s @ s �� A �� ? �� ? �� �� O ?   ? �� ? A \ t g
 E F A �� N ? �� ? �� ? A �� A   �� �� �� \ t g E F A �� g p �� ? �� ? �� ? �� �� �� ��
 ? �� ? ? ? �� �� ? �� ?   A 1 Q A ? �� ? �� ` �� �� ? �� ? ? ? �� �� C ��   �� �� �� �� ��
 ? �� �� �� B
*/

/*
----------------------------------------------------------------------------------------
        1.  �� �� w b _ e g �� ? ? ��   �� _
----------------------------------------------------------------------------------------

           ? Y   Y ? \ �� e N X `   �� ?   ` ? ��bmp Ctga Cjpeg Cpng
         @ ? ? ��
         @ @jpeg �� ? Y   Y �� ��JPEG   C u     ilibjpeg.lib, jpeglib.h j a �� r K v
         @ @jpeg �� ? Y   Y e L ? �� �� �� �� �� C �� �� w b _ �� DEF_USE_LIBJPEG  e 1  �� �� �� �� ?

         @     png �� ? Y   Y �� ��PNG   C u     ilibpng.lib, zlib.lib, png.h ,zlib.h j a �� r K v
         @ @png �� ? Y   Y e L ? �� �� �� �� �� C �� �� w b _ �� DEF_USE_LIBPNG   e 1  �� �� �� �� ?

           e N X `   ?   �� T C Y �� u �� �� a2 ��n ? T C Y(64,128,256 c) �� 3 ? ` v �� �� ��


----------------------------------------------------------------------------------------
        2.  g �� ?(1) 1 ? ��MQO t @ C   e ? Y   ? ? \ | �� �� ��  
----------------------------------------------------------------------------------------

        (1)    �� ? iARToolKit �� ��   CargInit() �� ? �� g p j

                mqoInit();

        (2)  t @ C   ? ? ��   f   �� ? Y   Y

                MQO_MODEL model;
                model = mqoCreateModel( "mario.mqo", 1.0 );

        (3)    f   �� ? ? o ��

                mqoCallModel( model );

        (4)    f   �� ��  

                mqoDeleteModel( model );

        (5)  I 1     i v   O     I 1   �� a �� ? - ? 3 �� j

                mqoCleanup();

----------------------------------------------------------------------------------------
        3.  g �� ?(2)  A ? t @ C   e ? Y   ? ? \ | �� �� ��  
----------------------------------------------------------------------------------------

        (1)    �� ? iARToolKit �� ��   CargInit() �� ? �� g p j

                mqoInit();

        (2)  A ? V [ P   X �� �� ?

           @ �� Fmario0.mqo  ` mario9.mqo  e ? Y   T

                MQO_SEQUENCE seq;
                seq = mqoCreateSequence( "mario%d.mqo", 10, 1.0 );

        (3)  A ? V [ P   X �� w �� t   [   �� ? ? o �� ii �� t   [   ?   j

                mqoCallSequence( seq, i );

        (4)  A ? V [ P   X �� ��  

                mqoDeleteSequence( seq );

        (5)  I 1     i v   O     I 1   �� a �� ? - ? 3 �� j

                mqoCleanup();

----------------------------------------------------------------------------------------
        4.  ? �� d l
----------------------------------------------------------------------------------------

           \ | @ \
         E T | [ g �� ? �� ��MQO t @ C   �� o [ W     �� uMetasequoia Ver1.0/2.0 `2.4 v

         E ?   �� ? �� �� T ? ? ?
         @ F i ? j
         @ e N X `   } b v i o   v } b v ? ?   ^UV } b s   O �� Y j

         E ?   �� ? �� �� I u W F N g ? ?
         @ \ | ^ ? \ | �� ? �� ? |
         @ X   [ W   O �� L 3
         @ ? _ @ �� e   ? �� ? ? �� X   [ W   O p
         @ ? _ ? ?
         @ �� ? ? i ? _ J   [ ? ?   j

         E �� �� E ? �� E ? ] �� �� �� ? ?  
         E   ^ { [   �� ? ?  

           d l
         E `     N ? �� �� �� ? �� ? ? ?   ? ? ?   �� ? �� e �� �� �� �� ? �� �� �� ? �� �� a
         @ ? �� �� ? �� �� �� ? �� �� D
         E e N X `   �� p X �� ? o C g ?   e ? ? �� ? �� ?
         @ ? �� �� ? ��'\'(0x5c) a'/'(0x2f) a �� �� �� ? �� �� ? �� �� - e N X `   a ? ? �� �� D
         E ��   F �� } e   A   �� ?   �� ? �� �� �� D
         @Object `     N ��face `     N �� T ? C   f b N X iM(%d) j a-1 �� �� ?   D

*/



/*=========================================================================
 y   [ U a C �� ? Y �� z
=========================================================================*/

#define MAX_TEXTURE                             100                     //  e N X `   �� ? ? ? �� �� ��  
#define MAX_OBJECT                              50                      // 1 ? ��MQO t @ C   �� �� ? ? I u W F N g  
#define SIZE_STR                                256                     //  ?   ? o b t @ �� T C Y
#define DEF_IS_LITTLE_ENDIAN    1                       //  G   f B A   w �� iintel n=1 j
#define DEF_USE_LIBJPEG                 0                       // libjpeg �� g p i1: g p 0: �� g p j
#define DEF_USE_LIBPNG                  0                       // libpng  �� g p i1: g p 0: �� g p j



/*=========================================================================
 y R   p C   I v V     z
=========================================================================*/

// JPEG e g p �� ��
#ifdef D_JPEG
        #undef  DEF_USE_LIBJPEG
        #define DEF_USE_LIBJPEG 1
#endif

// JPEG e g p �� �� ��
#ifdef D_NO_JPEG
        #undef  DEF_USE_LIBJPEG
        #define DEF_USE_LIBJPEG 0
#endif

// PNG e g p �� ��
#ifdef D_PNG
        #undef  DEF_USE_LIBPNG
        #define DEF_USE_LIBPNG 1
#endif

// PNG e g p �� �� ��
#ifdef D_NO_PNG
        #undef  DEF_USE_LIBPNG
        #define DEF_USE_LIBPNG 0
#endif


/*=========================================================================
 y w b _ z
=========================================================================*/

#ifdef WIN32
        #include <windows.h>
#else
        #ifndef MAX_PATH
                #define MAX_PATH    256
        #endif
        #ifndef TRUE
                #define TRUE    (1==1)
        #endif
        #ifndef FALSE
            #define FALSE   (1!=1)
        #endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
        #include <OpenGL/gl.h>
        #include <OpenGL/glu.h>
        #include <GLUT/glut.h>
        #include <OpenGL/glext.h>
#else
        #include <GL/gl.h>
        #include <GL/glu.h>
        #include <GL/glut.h>
//      #include <gl/glext.h>
#endif


/*=========================================================================
 y @ \ Y �� z libjpeg g p Y ��
=========================================================================*/

#if DEF_USE_LIBJPEG

        #define XMD_H // INT16 ?INT32 �� ? �� ` G   [ e h ?
        #ifdef FAR
                #undef FAR
        #endif

        #include "jpeglib.h"
        #pragma comment(lib,"jpeg.lib")

#endif


/*=========================================================================
 y @ \ Y �� z libpng g p Y ��
=========================================================================*/

#if DEF_USE_LIBPNG

        #include "png.h"
        #include "zlib.h"
        #pragma comment(lib,"libpng.lib")
        #pragma comment(lib,"zlib.lib")

#endif


/*=========================================================================
 y } N   �� ` z  ? ? l } N  
=========================================================================*/

#ifndef MAX
        #define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#endif


/*=========================================================================
 y ^ �� ` z TGA t H [ } b g
=========================================================================*/

#define DEF_TGA_COLOR_MAP_FLAG_VALID    1
#define DEF_TGA_TYPE_NON                                0
#define DEF_TGA_TYPE_INDEX                              1
#define DEF_TGA_TYPE_FULL                               2
#define DEF_TGA_TYPE_MONO                               3
#define DEF_TGA_TYPE_RLEINDEX                   9
#define DEF_TGA_TYPE_RLEFULL                    10
#define DEF_TGA_TYPE_RLEMONO                    11
#define DEF_TGA_BIT_INFO_RIGHT_TO_LEFT  0x00
#define DEF_TGA_BIT_INFO_LEFT_TO_RIGHT  0x10
#define DEF_TGA_BIT_INFO_DOWN_TO_TOP    0x00
#define DEF_TGA_BIT_INFO_TOP_TO_DOWN    0x20

typedef struct {
        unsigned char   id;
        unsigned char   color_map_flag;
        unsigned char   type;
        unsigned short  color_map_entry;
        unsigned char   color_map_entry_size;
        unsigned short  x;
        unsigned short  y;
        unsigned short  width;
        unsigned short  height;
        unsigned char   depth;
        unsigned char   bit_info;
} STR_TGA_HEAD;


/*=========================================================================
 y ^ �� ` z OpenGL p F \ �� �� (4 Ffloat)
=========================================================================*/
typedef struct {
        GLfloat r;
        GLfloat g;
        GLfloat b;
        GLfloat a;
} glCOLOR4f;


/*=========================================================================
 y ^ �� ` z OpenGL p Q   3 �� W \ �� �� (float)
=========================================================================*/
typedef struct {
        GLfloat x;
        GLfloat y;
} glPOINT2f;


/*=========================================================================
 y ^ �� ` z OpenGL p R   3 �� W \ �� �� (float)
=========================================================================*/
typedef struct tag_glPOINT3f {
        GLfloat x;
        GLfloat y;
        GLfloat z;
} glPOINT3f;


/*=========================================================================
 y ^ �� ` z  �� ? ? \ �� ��
=========================================================================*/
typedef struct {
        int                     n;              // 1 ? �� �� e \ ? �� �� ? _ ��   i3 `4 j
        int                     m;              //  �� �� T ? ?  
        int                     v[4];   //  ? _ ?   e i [ �� ? z ?
        glPOINT2f       uv[4];  // UV } b v
} MQO_FACE;


/*=========================================================================
 y ^ �� ` z  T ? ? ? \ �� �� i t @ C   ? ? ? ? e ? Y   T ? �� g p j
=========================================================================*/
typedef struct {
        glCOLOR4f       col;                            //  F
        GLfloat         dif[4];                         //  g U ?
        GLfloat         amb[4];                         //  �� �� ?
        GLfloat         emi[4];                         //  ? �� ? ?
        GLfloat         spc[4];                         //  ? ? ?
        GLfloat         power;                          //  ? ? ? �� - 3
        int                     useTex;                         //  e N X `   �� L 3
        char            texFile[SIZE_STR];      //  e N X `   t @ C  
        char            alpFile[SIZE_STR];      //  A   t @ e N X `   t @ C  
        GLuint          texName;                        //  e N X `   ?
} MQO_MATDATA;


/*=========================================================================
 y ^ �� ` z  I u W F N g \ �� �� i p [ c P ? �� f [ ^ j
=========================================================================*/
typedef struct {
        char            objname[SIZE_STR];      //  p [ c ?
        int                     visible;                        //  ?   �� ?
        int                     shading;                        //  V F [ f B   O i0: t   b g ^1: O   [ j
        float           facet;                          //  X   [ W   O p
        int                     n_face;                         //  ��  
        int                     n_vertex;                       //  ? _  
        MQO_FACE        *F;                                     //  ��
        glPOINT3f       *V;                                     //  ? _
} MQO_OBJDATA;


/*=========================================================================
 y ^ �� ` z  e N X `   v [  
=========================================================================*/
typedef struct {
        GLuint                  texture_id;                     //  e N X `  ID
        int                             texsize;                        //  e N X `   T C Y
        char                    texfile[MAX_PATH];      //  e N X `   t @ C  
        char                    alpfile[MAX_PATH];      //  A   t @ e N X `   t @ C  
        unsigned char   alpha;                          //  A   t @
} TEXTURE_POOL;


/*=========================================================================
 y ^ �� ` z  ? _ f [ ^ i e N X `   g p   j
=========================================================================*/
typedef struct {
        GLfloat point[3];       //  ? _ z ? (x, y, z)
        GLfloat normal[3];      //  @ �� z ? (x, y, z)
        GLfloat uv[2];          // UV z ? (u, v)
} VERTEX_TEXUSE;


/*=========================================================================
 y ^ �� ` z  ? _ f [ ^ i e N X `   s g p   j
=========================================================================*/
typedef struct {
        GLfloat point[3];       //  ? _ z ? (x, y, z)
        GLfloat normal[3];      //  @ �� z ? (x, y, z)
} VERTEX_NOTEX;


/*=========================================================================
 y ^ �� ` z  } e   A   ? ? i } e   A   �� �� ? _ z ? e   ? j
=========================================================================*/
typedef struct {
        int                             isValidMaterialInfo;//  } e   A   ? ? �� L ?/ 3 ?
        int                             isUseTexture;           //  e N X `   �� L 3 FUSE_TEXTURE / NOUSE_TEXTURE
        GLuint                  texture_id;                     //  e N X `   �� ? O(OpenGL)
        GLuint                  VBO_id;                         //  ? _ o b t @ ��ID(OpenGL) @ ?   �� ? ��   ? �� g p
        int                             datanum;                        //  ? _  
        GLfloat                 color[4];                       //  F z ? (r, g, b, a)
        GLfloat                 dif[4];                         //  g U ?
        GLfloat                 amb[4];                         //  �� �� ?
        GLfloat                 emi[4];                         //  ? �� ? ?
        GLfloat                 spc[4];                         //  ? ? ?
        GLfloat                 power;                          //  ? ? ? �� - 3
        VERTEX_NOTEX    *vertex_p;                      //  |   S   �� Y ��   �� ? _ z ?
        VERTEX_TEXUSE   *vertex_t;                      //  e N X `   g p   �� ? _ z ?
} MQO_MATERIAL;


/*=========================================================================
 y ^ �� ` z  ��   I u W F N g i1 ? �� p [ c e ?   j
=========================================================================*/
typedef struct {
        char                    objname[SIZE_STR];              //  I u W F N g ?
        int                             isVisible;                              // 0 F ? \ | @ ? �� ? F \ |
        int                             isShadingFlat;                  //  V F [ f B   O   [ h
        int                             matnum;                                 //  g p } e   A    
        MQO_MATERIAL    *mat;                                   //  } e   A   z ?
} MQO_INNER_OBJECT;


/*=========================================================================
 y ^ �� ` z MQO I u W F N g i1 ? ��   f   e ?   j @ |MQO_MODEL �� �� ��
=========================================================================*/
typedef struct {
        unsigned char           alpha;                          //  ? _ z ? �� ?   �� w �� 3 �� ? A   t @ l i Q ? p j
        int                                     objnum;                         //  ��   I u W F N g  
        MQO_INNER_OBJECT        obj[MAX_OBJECT];        //  ��   I u W F N g z ?
} MQO_OBJECT;


/*=========================================================================
 y ^ �� ` z MQO_MODEL \ �� ��
=========================================================================*/
typedef MQO_OBJECT * MQO_MODEL;         // MQO_MODEL �� ? ? ` ? \ �� �� ? �� A h   X


/*=========================================================================
 y ^ �� ` z MQO V [ P   X
=========================================================================*/
typedef struct {
        MQO_MODEL       model;          //    f  
        int                     n_frame;        //  t   [    
} MQO_SEQUENCE;


/*=========================================================================
 y ^ �� ` z glext.h  ? ? �� VBO Extension  �� �� `
=========================================================================*/
#ifdef WIN32
        #define GL_ARRAY_BUFFER_ARB     0x8892
        #define GL_STATIC_DRAW_ARB      0x88E4
        typedef void (APIENTRY * PFNGLBINDBUFFERARBPROC)    (GLenum target, GLuint buffer);
        typedef void (APIENTRY * PFNGLDELETEBUFFERSARBPROC) (GLsizei n, const GLuint *buffers);
        typedef void (APIENTRY * PFNGLGENBUFFERSARBPROC)    (GLsizei n, GLuint *buffers);
        typedef void (APIENTRY * PFNGLBUFFERDATAARBPROC)    (GLenum target, int size, const GLvoid *data, GLenum usage);
#endif


/*=========================================================================
 y O   [ o   ?   �� ` z
=========================================================================*/

#ifdef __GLMETASEQ_C__
        #define __GLMETASEQ_C__EXTERN
#else
        #define __GLMETASEQ_C__EXTERN extern
#endif

__GLMETASEQ_C__EXTERN int g_isVBOSupported;     // OpenGL �� ? _ o b t @ �� T | [ g L 3

#ifdef WIN32
        // VBO Extension  ?   �� | C   ^
        __GLMETASEQ_C__EXTERN PFNGLGENBUFFERSARBPROC glGenBuffersARB;           // VBO  ? O ? ?
        __GLMETASEQ_C__EXTERN PFNGLBINDBUFFERARBPROC glBindBufferARB;           // VBO    ? ? ��
        __GLMETASEQ_C__EXTERN PFNGLBUFFERDATAARBPROC glBufferDataARB;           // VBO  f [ ^   [ h
        __GLMETASEQ_C__EXTERN PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;     // VBO  ��  
#endif

#undef __GLMETASEQ_C__EXTERN


/*=========================================================================
 y ?   �� ? z
=========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif


//    �� ?
void mqoInit(void);

//  I 1    
void mqoCleanup(void);

//    f   ? ?
MQO_MODEL        mqoCreateModel(char *filename, double scale);

//  V [ P   X ? ?
MQO_SEQUENCE mqoCreateSequence(const char *format, int n_file, double scale);

//  V [ P   X ? ? i g �� ? j
MQO_SEQUENCE mqoCreateSequenceEx(const char *format, int n_file, double scale,
                                                                 int fade_inout, unsigned char alpha);

//    f   ? ? o ��
void mqoCallModel(MQO_MODEL model);

//  V [ P   X ? ? o ��
void mqoCallSequence(MQO_SEQUENCE seq, int i);

//    f   �� ��  
void mqoDeleteModel(MQO_MODEL model);

//  V [ P   X �� ��  
void mqoDeleteSequence(MQO_SEQUENCE seq);


#ifdef __cplusplus
}
#endif




#endif  // -- end of header --