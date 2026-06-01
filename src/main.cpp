// WIN32_LEAN_AND_MEAN передаётся через -D в компиляторе
#include <windows.h>
#include <wingdi.h>


// GL типы - объявляем вручную, НЕ включаем <GL/gl.h>
typedef unsigned int   GLenum;
typedef unsigned char  GLboolean;
typedef unsigned int   GLbitfield;
typedef signed char    GLbyte;
typedef short          GLshort;
typedef int            GLint;
typedef int            GLsizei;
typedef unsigned char  GLubyte;
typedef unsigned short GLushort;
typedef unsigned int   GLuint;
typedef float          GLfloat;
typedef float          GLclampf;
typedef double         GLdouble;
typedef double         GLclampd;

#define GL_FALSE    0
#define GL_TRUE     1
#define GL_NO_ERROR 0

#include "gl_proxy.h"
#include "overlay.h"
#include <cstdio>

// ============================================================
// Типы функций
// ============================================================
typedef void      (WINAPI *pf_glAccum)               (GLenum, GLfloat);
typedef void      (WINAPI *pf_glAlphaFunc)            (GLenum, GLclampf);
typedef GLboolean (WINAPI *pf_glAreTexturesResident)  (GLsizei, const GLuint*, GLboolean*);
typedef void      (WINAPI *pf_glArrayElement)         (GLint);
typedef void      (WINAPI *pf_glBegin)                (GLenum);
typedef void      (WINAPI *pf_glBindTexture)          (GLenum, GLuint);
typedef void      (WINAPI *pf_glBitmap)               (GLsizei, GLsizei, GLfloat, GLfloat, GLfloat, GLfloat, const GLubyte*);
typedef void      (WINAPI *pf_glBlendColor)           (GLclampf, GLclampf, GLclampf, GLclampf);
typedef void      (WINAPI *pf_glBlendEquation)        (GLenum);
typedef void      (WINAPI *pf_glBlendFunc)            (GLenum, GLenum);
typedef void      (WINAPI *pf_glCallList)             (GLuint);
typedef void      (WINAPI *pf_glCallLists)            (GLsizei, GLenum, const void*);
typedef void      (WINAPI *pf_glClear)                (GLbitfield);
typedef void      (WINAPI *pf_glClearAccum)           (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void      (WINAPI *pf_glClearColor)           (GLclampf, GLclampf, GLclampf, GLclampf);
typedef void      (WINAPI *pf_glClearDepth)           (GLclampd);
typedef void      (WINAPI *pf_glClearIndex)           (GLfloat);
typedef void      (WINAPI *pf_glClearStencil)         (GLint);
typedef void      (WINAPI *pf_glClipPlane)            (GLenum, const GLdouble*);
typedef void      (WINAPI *pf_glColor3b)              (GLbyte, GLbyte, GLbyte);
typedef void      (WINAPI *pf_glColor3bv)             (const GLbyte*);
typedef void      (WINAPI *pf_glColor3d)              (GLdouble, GLdouble, GLdouble);
typedef void      (WINAPI *pf_glColor3dv)             (const GLdouble*);
typedef void      (WINAPI *pf_glColor3f)              (GLfloat, GLfloat, GLfloat);
typedef void      (WINAPI *pf_glColor3fv)             (const GLfloat*);
typedef void      (WINAPI *pf_glColor3i)              (GLint, GLint, GLint);
typedef void      (WINAPI *pf_glColor3iv)             (const GLint*);
typedef void      (WINAPI *pf_glColor3s)              (GLshort, GLshort, GLshort);
typedef void      (WINAPI *pf_glColor3sv)             (const GLshort*);
typedef void      (WINAPI *pf_glColor3ub)             (GLubyte, GLubyte, GLubyte);
typedef void      (WINAPI *pf_glColor3ubv)            (const GLubyte*);
typedef void      (WINAPI *pf_glColor3ui)             (GLuint, GLuint, GLuint);
typedef void      (WINAPI *pf_glColor3uiv)            (const GLuint*);
typedef void      (WINAPI *pf_glColor3us)             (GLushort, GLushort, GLushort);
typedef void      (WINAPI *pf_glColor3usv)            (const GLushort*);
typedef void      (WINAPI *pf_glColor4b)              (GLbyte, GLbyte, GLbyte, GLbyte);
typedef void      (WINAPI *pf_glColor4bv)             (const GLbyte*);
typedef void      (WINAPI *pf_glColor4d)              (GLdouble, GLdouble, GLdouble, GLdouble);
typedef void      (WINAPI *pf_glColor4dv)             (const GLdouble*);
typedef void      (WINAPI *pf_glColor4f)              (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void      (WINAPI *pf_glColor4fv)             (const GLfloat*);
typedef void      (WINAPI *pf_glColor4i)              (GLint, GLint, GLint, GLint);
typedef void      (WINAPI *pf_glColor4iv)             (const GLint*);
typedef void      (WINAPI *pf_glColor4s)              (GLshort, GLshort, GLshort, GLshort);
typedef void      (WINAPI *pf_glColor4sv)             (const GLshort*);
typedef void      (WINAPI *pf_glColor4ub)             (GLubyte, GLubyte, GLubyte, GLubyte);
typedef void      (WINAPI *pf_glColor4ubv)            (const GLubyte*);
typedef void      (WINAPI *pf_glColor4ui)             (GLuint, GLuint, GLuint, GLuint);
typedef void      (WINAPI *pf_glColor4uiv)            (const GLuint*);
typedef void      (WINAPI *pf_glColor4us)             (GLushort, GLushort, GLushort, GLushort);
typedef void      (WINAPI *pf_glColor4usv)            (const GLushort*);
typedef void      (WINAPI *pf_glColorMask)            (GLboolean, GLboolean, GLboolean, GLboolean);
typedef void      (WINAPI *pf_glColorMaterial)        (GLenum, GLenum);
typedef void      (WINAPI *pf_glColorPointer)         (GLint, GLenum, GLsizei, const void*);
typedef void      (WINAPI *pf_glCopyPixels)           (GLint, GLint, GLsizei, GLsizei, GLenum);
typedef void      (WINAPI *pf_glCopyTexImage1D)       (GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint);
typedef void      (WINAPI *pf_glCopyTexImage2D)       (GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint);
typedef void      (WINAPI *pf_glCopyTexSubImage1D)    (GLenum, GLint, GLint, GLint, GLint, GLsizei);
typedef void      (WINAPI *pf_glCopyTexSubImage2D)    (GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
typedef void      (WINAPI *pf_glCopyTexSubImage3D)    (GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
typedef void      (WINAPI *pf_glCullFace)             (GLenum);
typedef void      (WINAPI *pf_glDeleteLists)          (GLuint, GLsizei);
typedef void      (WINAPI *pf_glDeleteTextures)       (GLsizei, const GLuint*);
typedef void      (WINAPI *pf_glDepthFunc)            (GLenum);
typedef void      (WINAPI *pf_glDepthMask)            (GLboolean);
typedef void      (WINAPI *pf_glDepthRange)           (GLclampd, GLclampd);
typedef void      (WINAPI *pf_glDisable)              (GLenum);
typedef void      (WINAPI *pf_glDisableClientState)   (GLenum);
typedef void      (WINAPI *pf_glDrawArrays)           (GLenum, GLint, GLsizei);
typedef void      (WINAPI *pf_glDrawBuffer)           (GLenum);
typedef void      (WINAPI *pf_glDrawElements)         (GLenum, GLsizei, GLenum, const void*);
typedef void      (WINAPI *pf_glDrawPixels)           (GLsizei, GLsizei, GLenum, GLenum, const void*);
typedef void      (WINAPI *pf_glDrawRangeElements)    (GLenum, GLuint, GLuint, GLsizei, GLenum, const void*);
typedef void      (WINAPI *pf_glEdgeFlag)             (GLboolean);
typedef void      (WINAPI *pf_glEdgeFlagPointer)      (GLsizei, const void*);
typedef void      (WINAPI *pf_glEdgeFlagv)            (const GLboolean*);
typedef void      (WINAPI *pf_glEnable)               (GLenum);
typedef void      (WINAPI *pf_glEnableClientState)    (GLenum);
typedef void      (WINAPI *pf_glEnd)                  ();
typedef void      (WINAPI *pf_glEndList)              ();
typedef void      (WINAPI *pf_glEvalCoord1d)          (GLdouble);
typedef void      (WINAPI *pf_glEvalCoord1dv)         (const GLdouble*);
typedef void      (WINAPI *pf_glEvalCoord1f)          (GLfloat);
typedef void      (WINAPI *pf_glEvalCoord1fv)         (const GLfloat*);
typedef void      (WINAPI *pf_glEvalCoord2d)          (GLdouble, GLdouble);
typedef void      (WINAPI *pf_glEvalCoord2dv)         (const GLdouble*);
typedef void      (WINAPI *pf_glEvalCoord2f)          (GLfloat, GLfloat);
typedef void      (WINAPI *pf_glEvalCoord2fv)         (const GLfloat*);
typedef void      (WINAPI *pf_glEvalMesh1)            (GLenum, GLint, GLint);
typedef void      (WINAPI *pf_glEvalMesh2)            (GLenum, GLint, GLint, GLint, GLint);
typedef void      (WINAPI *pf_glEvalPoint1)           (GLint);
typedef void      (WINAPI *pf_glEvalPoint2)           (GLint, GLint);
typedef void      (WINAPI *pf_glFeedbackBuffer)       (GLsizei, GLenum, GLfloat*);
typedef void      (WINAPI *pf_glFinish)               ();
typedef void      (WINAPI *pf_glFlush)                ();
typedef void      (WINAPI *pf_glFogf)                 (GLenum, GLfloat);
typedef void      (WINAPI *pf_glFogfv)                (GLenum, const GLfloat*);
typedef void      (WINAPI *pf_glFogi)                 (GLenum, GLint);
typedef void      (WINAPI *pf_glFogiv)                (GLenum, const GLint*);
typedef void      (WINAPI *pf_glFrontFace)            (GLenum);
typedef void      (WINAPI *pf_glFrustum)              (GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble);
typedef GLuint    (WINAPI *pf_glGenLists)             (GLsizei);
typedef void      (WINAPI *pf_glGenTextures)          (GLsizei, GLuint*);
typedef void      (WINAPI *pf_glGetBooleanv)          (GLenum, GLboolean*);
typedef void      (WINAPI *pf_glGetClipPlane)         (GLenum, GLdouble*);
typedef void      (WINAPI *pf_glGetDoublev)           (GLenum, GLdouble*);
typedef GLenum    (WINAPI *pf_glGetError)             ();
typedef void      (WINAPI *pf_glGetFloatv)            (GLenum, GLfloat*);
typedef void      (WINAPI *pf_glGetIntegerv)          (GLenum, GLint*);
typedef void      (WINAPI *pf_glGetLightfv)           (GLenum, GLenum, GLfloat*);
typedef void      (WINAPI *pf_glGetLightiv)           (GLenum, GLenum, GLint*);
typedef void      (WINAPI *pf_glGetMapdv)             (GLenum, GLenum, GLdouble*);
typedef void      (WINAPI *pf_glGetMapfv)             (GLenum, GLenum, GLfloat*);
typedef void      (WINAPI *pf_glGetMapiv)             (GLenum, GLenum, GLint*);
typedef void      (WINAPI *pf_glGetMaterialfv)        (GLenum, GLenum, GLfloat*);
typedef void      (WINAPI *pf_glGetMaterialiv)        (GLenum, GLenum, GLint*);
typedef void      (WINAPI *pf_glGetPixelMapfv)        (GLenum, GLfloat*);
typedef void      (WINAPI *pf_glGetPixelMapuiv)       (GLenum, GLuint*);
typedef void      (WINAPI *pf_glGetPixelMapusv)       (GLenum, GLushort*);
typedef void      (WINAPI *pf_glGetPointerv)          (GLenum, void**);
typedef void      (WINAPI *pf_glGetPolygonStipple)    (GLubyte*);
typedef const GLubyte* (WINAPI *pf_glGetString)       (GLenum);
typedef void      (WINAPI *pf_glGetTexEnvfv)          (GLenum, GLenum, GLfloat*);
typedef void      (WINAPI *pf_glGetTexEnviv)          (GLenum, GLenum, GLint*);
typedef void      (WINAPI *pf_glGetTexGendv)          (GLenum, GLenum, GLdouble*);
typedef void      (WINAPI *pf_glGetTexGenfv)          (GLenum, GLenum, GLfloat*);
typedef void      (WINAPI *pf_glGetTexGeniv)          (GLenum, GLenum, GLint*);
typedef void      (WINAPI *pf_glGetTexImage)          (GLenum, GLint, GLenum, GLenum, void*);
typedef void      (WINAPI *pf_glGetTexLevelParameterfv)(GLenum, GLint, GLenum, GLfloat*);
typedef void      (WINAPI *pf_glGetTexLevelParameteriv)(GLenum, GLint, GLenum, GLint*);
typedef void      (WINAPI *pf_glGetTexParameterfv)    (GLenum, GLenum, GLfloat*);
typedef void      (WINAPI *pf_glGetTexParameteriv)    (GLenum, GLenum, GLint*);
typedef void      (WINAPI *pf_glHint)                 (GLenum, GLenum);
typedef void      (WINAPI *pf_glIndexd)               (GLdouble);
typedef void      (WINAPI *pf_glIndexdv)              (const GLdouble*);
typedef void      (WINAPI *pf_glIndexf)               (GLfloat);
typedef void      (WINAPI *pf_glIndexfv)              (const GLfloat*);
typedef void      (WINAPI *pf_glIndexi)               (GLint);
typedef void      (WINAPI *pf_glIndexiv)              (const GLint*);
typedef void      (WINAPI *pf_glIndexMask)            (GLuint);
typedef void      (WINAPI *pf_glIndexPointer)         (GLenum, GLsizei, const void*);
typedef void      (WINAPI *pf_glIndexs)               (GLshort);
typedef void      (WINAPI *pf_glIndexsv)              (const GLshort*);
typedef void      (WINAPI *pf_glIndexub)              (GLubyte);
typedef void      (WINAPI *pf_glIndexubv)             (const GLubyte*);
typedef void      (WINAPI *pf_glInitNames)            ();
typedef void      (WINAPI *pf_glInterleavedArrays)    (GLenum, GLsizei, const void*);
typedef GLboolean (WINAPI *pf_glIsEnabled)            (GLenum);
typedef GLboolean (WINAPI *pf_glIsList)               (GLuint);
typedef GLboolean (WINAPI *pf_glIsTexture)            (GLuint);
typedef void      (WINAPI *pf_glLightf)               (GLenum, GLenum, GLfloat);
typedef void      (WINAPI *pf_glLightfv)              (GLenum, GLenum, const GLfloat*);
typedef void      (WINAPI *pf_glLighti)               (GLenum, GLenum, GLint);
typedef void      (WINAPI *pf_glLightiv)              (GLenum, GLenum, const GLint*);
typedef void      (WINAPI *pf_glLightModelf)          (GLenum, GLfloat);
typedef void      (WINAPI *pf_glLightModelfv)         (GLenum, const GLfloat*);
typedef void      (WINAPI *pf_glLightModeli)          (GLenum, GLint);
typedef void      (WINAPI *pf_glLightModeliv)         (GLenum, const GLint*);
typedef void      (WINAPI *pf_glLineStipple)          (GLint, GLushort);
typedef void      (WINAPI *pf_glLineWidth)            (GLfloat);
typedef void      (WINAPI *pf_glListBase)             (GLuint);
typedef void      (WINAPI *pf_glLoadIdentity)         ();
typedef void      (WINAPI *pf_glLoadMatrixd)          (const GLdouble*);
typedef void      (WINAPI *pf_glLoadMatrixf)          (const GLfloat*);
typedef void      (WINAPI *pf_glLoadName)             (GLuint);
typedef void      (WINAPI *pf_glLogicOp)              (GLenum);
typedef void      (WINAPI *pf_glMap1d)                (GLenum, GLdouble, GLdouble, GLint, GLint, const GLdouble*);
typedef void      (WINAPI *pf_glMap1f)                (GLenum, GLfloat, GLfloat, GLint, GLint, const GLfloat*);
typedef void      (WINAPI *pf_glMap2d)                (GLenum, GLdouble, GLdouble, GLint, GLint, GLdouble, GLdouble, GLint, GLint, const GLdouble*);
typedef void      (WINAPI *pf_glMap2f)                (GLenum, GLfloat, GLfloat, GLint, GLint, GLfloat, GLfloat, GLint, GLint, const GLfloat*);
typedef void      (WINAPI *pf_glMapGrid1d)            (GLint, GLdouble, GLdouble);
typedef void      (WINAPI *pf_glMapGrid1f)            (GLint, GLfloat, GLfloat);
typedef void      (WINAPI *pf_glMapGrid2d)            (GLint, GLdouble, GLdouble, GLint, GLdouble, GLdouble);
typedef void      (WINAPI *pf_glMapGrid2f)            (GLint, GLfloat, GLfloat, GLint, GLfloat, GLfloat);
typedef void      (WINAPI *pf_glMaterialf)            (GLenum, GLenum, GLfloat);
typedef void      (WINAPI *pf_glMaterialfv)           (GLenum, GLenum, const GLfloat*);
typedef void      (WINAPI *pf_glMateriali)            (GLenum, GLenum, GLint);
typedef void      (WINAPI *pf_glMaterialiv)           (GLenum, GLenum, const GLint*);
typedef void      (WINAPI *pf_glMatrixMode)           (GLenum);
typedef void      (WINAPI *pf_glMultMatrixd)          (const GLdouble*);
typedef void      (WINAPI *pf_glMultMatrixf)          (const GLfloat*);
typedef void      (WINAPI *pf_glNewList)              (GLuint, GLenum);
typedef void      (WINAPI *pf_glNormal3b)             (GLbyte, GLbyte, GLbyte);
typedef void      (WINAPI *pf_glNormal3bv)            (const GLbyte*);
typedef void      (WINAPI *pf_glNormal3d)             (GLdouble, GLdouble, GLdouble);
typedef void      (WINAPI *pf_glNormal3dv)            (const GLdouble*);
typedef void      (WINAPI *pf_glNormal3f)             (GLfloat, GLfloat, GLfloat);
typedef void      (WINAPI *pf_glNormal3fv)            (const GLfloat*);
typedef void      (WINAPI *pf_glNormal3i)             (GLint, GLint, GLint);
typedef void      (WINAPI *pf_glNormal3iv)            (const GLint*);
typedef void      (WINAPI *pf_glNormal3s)             (GLshort, GLshort, GLshort);
typedef void      (WINAPI *pf_glNormal3sv)            (const GLshort*);
typedef void      (WINAPI *pf_glNormalPointer)        (GLenum, GLsizei, const void*);
typedef void      (WINAPI *pf_glOrtho)                (GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble);
typedef void      (WINAPI *pf_glPassThrough)          (GLfloat);
typedef void      (WINAPI *pf_glPixelMapfv)           (GLenum, GLsizei, const GLfloat*);
typedef void      (WINAPI *pf_glPixelMapuiv)          (GLenum, GLsizei, const GLuint*);
typedef void      (WINAPI *pf_glPixelMapusv)          (GLenum, GLsizei, const GLushort*);
typedef void      (WINAPI *pf_glPixelStoref)          (GLenum, GLfloat);
typedef void      (WINAPI *pf_glPixelStorei)          (GLenum, GLint);
typedef void      (WINAPI *pf_glPixelTransferf)       (GLenum, GLfloat);
typedef void      (WINAPI *pf_glPixelTransferi)       (GLenum, GLint);
typedef void      (WINAPI *pf_glPixelZoom)            (GLfloat, GLfloat);
typedef void      (WINAPI *pf_glPointSize)            (GLfloat);
typedef void      (WINAPI *pf_glPolygonMode)          (GLenum, GLenum);
typedef void      (WINAPI *pf_glPolygonOffset)        (GLfloat, GLfloat);
typedef void      (WINAPI *pf_glPolygonStipple)       (const GLubyte*);
typedef void      (WINAPI *pf_glPopAttrib)            ();
typedef void      (WINAPI *pf_glPopClientAttrib)      ();
typedef void      (WINAPI *pf_glPopMatrix)            ();
typedef void      (WINAPI *pf_glPopName)              ();
typedef void      (WINAPI *pf_glPrioritizeTextures)   (GLsizei, const GLuint*, const GLclampf*);
typedef void      (WINAPI *pf_glPushAttrib)           (GLbitfield);
typedef void      (WINAPI *pf_glPushClientAttrib)     (GLbitfield);
typedef void      (WINAPI *pf_glPushMatrix)           ();
typedef void      (WINAPI *pf_glPushName)             (GLuint);
typedef void      (WINAPI *pf_glRasterPos2d)          (GLdouble, GLdouble);
typedef void      (WINAPI *pf_glRasterPos2dv)         (const GLdouble*);
typedef void      (WINAPI *pf_glRasterPos2f)          (GLfloat, GLfloat);
typedef void      (WINAPI *pf_glRasterPos2fv)         (const GLfloat*);
typedef void      (WINAPI *pf_glRasterPos2i)          (GLint, GLint);
typedef void      (WINAPI *pf_glRasterPos2iv)         (const GLint*);
typedef void      (WINAPI *pf_glRasterPos2s)          (GLshort, GLshort);
typedef void      (WINAPI *pf_glRasterPos2sv)         (const GLshort*);
typedef void      (WINAPI *pf_glRasterPos3d)          (GLdouble, GLdouble, GLdouble);
typedef void      (WINAPI *pf_glRasterPos3dv)         (const GLdouble*);
typedef void      (WINAPI *pf_glRasterPos3f)          (GLfloat, GLfloat, GLfloat);
typedef void      (WINAPI *pf_glRasterPos3fv)         (const GLfloat*);
typedef void      (WINAPI *pf_glRasterPos3i)          (GLint, GLint, GLint);
typedef void      (WINAPI *pf_glRasterPos3iv)         (const GLint*);
typedef void      (WINAPI *pf_glRasterPos3s)          (GLshort, GLshort, GLshort);
typedef void      (WINAPI *pf_glRasterPos3sv)         (const GLshort*);
typedef void      (WINAPI *pf_glRasterPos4d)          (GLdouble, GLdouble, GLdouble, GLdouble);
typedef void      (WINAPI *pf_glRasterPos4dv)         (const GLdouble*);
typedef void      (WINAPI *pf_glRasterPos4f)          (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void      (WINAPI *pf_glRasterPos4fv)         (const GLfloat*);
typedef void      (WINAPI *pf_glRasterPos4i)          (GLint, GLint, GLint, GLint);
typedef void      (WINAPI *pf_glRasterPos4iv)         (const GLint*);
typedef void      (WINAPI *pf_glRasterPos4s)          (GLshort, GLshort, GLshort, GLshort);
typedef void      (WINAPI *pf_glRasterPos4sv)         (const GLshort*);
typedef void      (WINAPI *pf_glReadBuffer)           (GLenum);
typedef void      (WINAPI *pf_glReadPixels)           (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void*);
typedef void      (WINAPI *pf_glRectd)                (GLdouble, GLdouble, GLdouble, GLdouble);
typedef void      (WINAPI *pf_glRectdv)               (const GLdouble*, const GLdouble*);
typedef void      (WINAPI *pf_glRectf)                (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void      (WINAPI *pf_glRectfv)               (const GLfloat*, const GLfloat*);
typedef void      (WINAPI *pf_glRecti)                (GLint, GLint, GLint, GLint);
typedef void      (WINAPI *pf_glRectiv)               (const GLint*, const GLint*);
typedef void      (WINAPI *pf_glRects)                (GLshort, GLshort, GLshort, GLshort);
typedef void      (WINAPI *pf_glRectsv)               (const GLshort*, const GLshort*);
typedef GLint     (WINAPI *pf_glRenderMode)           (GLenum);
typedef void      (WINAPI *pf_glRotated)              (GLdouble, GLdouble, GLdouble, GLdouble);
typedef void      (WINAPI *pf_glRotatef)              (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void      (WINAPI *pf_glScaled)               (GLdouble, GLdouble, GLdouble);
typedef void      (WINAPI *pf_glScalef)               (GLfloat, GLfloat, GLfloat);
typedef void      (WINAPI *pf_glScissor)              (GLint, GLint, GLsizei, GLsizei);
typedef void      (WINAPI *pf_glSelectBuffer)         (GLsizei, GLuint*);
typedef void      (WINAPI *pf_glShadeModel)           (GLenum);
typedef void      (WINAPI *pf_glStencilFunc)          (GLenum, GLint, GLuint);
typedef void      (WINAPI *pf_glStencilMask)          (GLuint);
typedef void      (WINAPI *pf_glStencilOp)            (GLenum, GLenum, GLenum);
typedef void      (WINAPI *pf_glTexCoord1d)           (GLdouble);
typedef void      (WINAPI *pf_glTexCoord1dv)          (const GLdouble*);
typedef void      (WINAPI *pf_glTexCoord1f)           (GLfloat);
typedef void      (WINAPI *pf_glTexCoord1fv)          (const GLfloat*);
typedef void      (WINAPI *pf_glTexCoord1i)           (GLint);
typedef void      (WINAPI *pf_glTexCoord1iv)          (const GLint*);
typedef void      (WINAPI *pf_glTexCoord1s)           (GLshort);
typedef void      (WINAPI *pf_glTexCoord1sv)          (const GLshort*);
typedef void      (WINAPI *pf_glTexCoord2d)           (GLdouble, GLdouble);
typedef void      (WINAPI *pf_glTexCoord2dv)          (const GLdouble*);
typedef void      (WINAPI *pf_glTexCoord2f)           (GLfloat, GLfloat);
typedef void      (WINAPI *pf_glTexCoord2fv)          (const GLfloat*);
typedef void      (WINAPI *pf_glTexCoord2i)           (GLint, GLint);
typedef void      (WINAPI *pf_glTexCoord2iv)          (const GLint*);
typedef void      (WINAPI *pf_glTexCoord2s)           (GLshort, GLshort);
typedef void      (WINAPI *pf_glTexCoord2sv)          (const GLshort*);
typedef void      (WINAPI *pf_glTexCoord3d)           (GLdouble, GLdouble, GLdouble);
typedef void      (WINAPI *pf_glTexCoord3dv)          (const GLdouble*);
typedef void      (WINAPI *pf_glTexCoord3f)           (GLfloat, GLfloat, GLfloat);
typedef void      (WINAPI *pf_glTexCoord3fv)          (const GLfloat*);
typedef void      (WINAPI *pf_glTexCoord3i)           (GLint, GLint, GLint);
typedef void      (WINAPI *pf_glTexCoord3iv)          (const GLint*);
typedef void      (WINAPI *pf_glTexCoord3s)           (GLshort, GLshort, GLshort);
typedef void      (WINAPI *pf_glTexCoord3sv)          (const GLshort*);
typedef void      (WINAPI *pf_glTexCoord4d)           (GLdouble, GLdouble, GLdouble, GLdouble);
typedef void      (WINAPI *pf_glTexCoord4dv)          (const GLdouble*);
typedef void      (WINAPI *pf_glTexCoord4f)           (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void      (WINAPI *pf_glTexCoord4fv)          (const GLfloat*);
typedef void      (WINAPI *pf_glTexCoord4i)           (GLint, GLint, GLint, GLint);
typedef void      (WINAPI *pf_glTexCoord4iv)          (const GLint*);
typedef void      (WINAPI *pf_glTexCoord4s)           (GLshort, GLshort, GLshort, GLshort);
typedef void      (WINAPI *pf_glTexCoord4sv)          (const GLshort*);
typedef void      (WINAPI *pf_glTexCoordPointer)      (GLint, GLenum, GLsizei, const void*);
typedef void      (WINAPI *pf_glTexEnvf)              (GLenum, GLenum, GLfloat);
typedef void      (WINAPI *pf_glTexEnvfv)             (GLenum, GLenum, const GLfloat*);
typedef void      (WINAPI *pf_glTexEnvi)              (GLenum, GLenum, GLint);
typedef void      (WINAPI *pf_glTexEnviv)             (GLenum, GLenum, const GLint*);
typedef void      (WINAPI *pf_glTexGend)              (GLenum, GLenum, GLdouble);
typedef void      (WINAPI *pf_glTexGendv)             (GLenum, GLenum, const GLdouble*);
typedef void      (WINAPI *pf_glTexGenf)              (GLenum, GLenum, GLfloat);
typedef void      (WINAPI *pf_glTexGenfv)             (GLenum, GLenum, const GLfloat*);
typedef void      (WINAPI *pf_glTexGeni)              (GLenum, GLenum, GLint);
typedef void      (WINAPI *pf_glTexGeniv)             (GLenum, GLenum, const GLint*);
typedef void      (WINAPI *pf_glTexImage1D)           (GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void*);
typedef void      (WINAPI *pf_glTexImage2D)           (GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*);
typedef void      (WINAPI *pf_glTexImage3D)           (GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*);
typedef void      (WINAPI *pf_glTexParameterf)        (GLenum, GLenum, GLfloat);
typedef void      (WINAPI *pf_glTexParameterfv)       (GLenum, GLenum, const GLfloat*);
typedef void      (WINAPI *pf_glTexParameteri)        (GLenum, GLenum, GLint);
typedef void      (WINAPI *pf_glTexParameteriv)       (GLenum, GLenum, const GLint*);
typedef void      (WINAPI *pf_glTexSubImage1D)        (GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void*);
typedef void      (WINAPI *pf_glTexSubImage2D)        (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void*);
typedef void      (WINAPI *pf_glTexSubImage3D)        (GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void*);
typedef void      (WINAPI *pf_glTranslated)           (GLdouble, GLdouble, GLdouble);
typedef void      (WINAPI *pf_glTranslatef)           (GLfloat, GLfloat, GLfloat);
typedef void      (WINAPI *pf_glVertex2d)             (GLdouble, GLdouble);
typedef void      (WINAPI *pf_glVertex2dv)            (const GLdouble*);
typedef void      (WINAPI *pf_glVertex2f)             (GLfloat, GLfloat);
typedef void      (WINAPI *pf_glVertex2fv)            (const GLfloat*);
typedef void      (WINAPI *pf_glVertex2i)             (GLint, GLint);
typedef void      (WINAPI *pf_glVertex2iv)            (const GLint*);
typedef void      (WINAPI *pf_glVertex2s)             (GLshort, GLshort);
typedef void      (WINAPI *pf_glVertex2sv)            (const GLshort*);
typedef void      (WINAPI *pf_glVertex3d)             (GLdouble, GLdouble, GLdouble);
typedef void      (WINAPI *pf_glVertex3dv)            (const GLdouble*);
typedef void      (WINAPI *pf_glVertex3f)             (GLfloat, GLfloat, GLfloat);
typedef void      (WINAPI *pf_glVertex3fv)            (const GLfloat*);
typedef void      (WINAPI *pf_glVertex3i)             (GLint, GLint, GLint);
typedef void      (WINAPI *pf_glVertex3iv)            (const GLint*);
typedef void      (WINAPI *pf_glVertex3s)             (GLshort, GLshort, GLshort);
typedef void      (WINAPI *pf_glVertex3sv)            (const GLshort*);
typedef void      (WINAPI *pf_glVertex4d)             (GLdouble, GLdouble, GLdouble, GLdouble);
typedef void      (WINAPI *pf_glVertex4dv)            (const GLdouble*);
typedef void      (WINAPI *pf_glVertex4f)             (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void      (WINAPI *pf_glVertex4fv)            (const GLfloat*);
typedef void      (WINAPI *pf_glVertex4i)             (GLint, GLint, GLint, GLint);
typedef void      (WINAPI *pf_glVertex4iv)            (const GLint*);
typedef void      (WINAPI *pf_glVertex4s)             (GLshort, GLshort, GLshort, GLshort);
typedef void      (WINAPI *pf_glVertex4sv)            (const GLshort*);
typedef void      (WINAPI *pf_glVertexPointer)        (GLint, GLenum, GLsizei, const void*);
typedef void      (WINAPI *pf_glViewport)             (GLint, GLint, GLsizei, GLsizei);

// WGL - типы уже есть в wingdi.h
typedef HGLRC  (WINAPI *pf_wglCreateContext)         (HDC);
typedef BOOL   (WINAPI *pf_wglDeleteContext)         (HGLRC);
typedef HGLRC  (WINAPI *pf_wglGetCurrentContext)     ();
typedef HDC    (WINAPI *pf_wglGetCurrentDC)          ();
typedef PROC   (WINAPI *pf_wglGetProcAddress)        (LPCSTR);
typedef BOOL   (WINAPI *pf_wglMakeCurrent)           (HDC, HGLRC);
typedef BOOL   (WINAPI *pf_wglShareLists)            (HGLRC, HGLRC);
typedef BOOL   (WINAPI *pf_wglSwapBuffers)           (HDC);
typedef HGLRC  (WINAPI *pf_wglCreateLayerContext)    (HDC, int);
typedef BOOL   (WINAPI *pf_wglCopyContext)           (HGLRC, HGLRC, UINT);
typedef int    (WINAPI *pf_wglChoosePixelFormat)     (HDC, const PIXELFORMATDESCRIPTOR*);
typedef BOOL   (WINAPI *pf_wglDescribeLayerPlane)    (HDC, int, int, UINT, LPLAYERPLANEDESCRIPTOR);
typedef int    (WINAPI *pf_wglDescribePixelFormat)   (HDC, int, UINT, LPPIXELFORMATDESCRIPTOR);
typedef HANDLE (WINAPI *pf_wglGetDefaultProcAddress) (LPCSTR);
typedef int    (WINAPI *pf_wglGetLayerPaletteEntries)(HDC, int, int, int, COLORREF*);
typedef int    (WINAPI *pf_wglGetPixelFormat)        (HDC);
typedef BOOL   (WINAPI *pf_wglRealizeLayerPalette)   (HDC, int, BOOL);
typedef int    (WINAPI *pf_wglSetLayerPaletteEntries)(HDC, int, int, int, const COLORREF*);
typedef BOOL   (WINAPI *pf_wglSetPixelFormat)        (HDC, int, const PIXELFORMATDESCRIPTOR*);
typedef BOOL   (WINAPI *pf_wglSwapLayerBuffers)      (HDC, UINT);
typedef DWORD  (WINAPI *pf_wglSwapMultipleBuffers)   (UINT, const WGLSWAP*);
typedef BOOL   (WINAPI *pf_wglUseFontBitmapsA)       (HDC, DWORD, DWORD, DWORD);
typedef BOOL   (WINAPI *pf_wglUseFontBitmapsW)       (HDC, DWORD, DWORD, DWORD);
typedef BOOL   (WINAPI *pf_wglUseFontOutlinesA)      (HDC, DWORD, DWORD, DWORD, FLOAT, FLOAT, int, LPGLYPHMETRICSFLOAT);
typedef BOOL   (WINAPI *pf_wglUseFontOutlinesW)      (HDC, DWORD, DWORD, DWORD, FLOAT, FLOAT, int, LPGLYPHMETRICSFLOAT);
typedef int    (WINAPI *pf_ChoosePixelFormat)        (HDC, const PIXELFORMATDESCRIPTOR*);
typedef int    (WINAPI *pf_DescribePixelFormat)      (HDC, int, UINT, LPPIXELFORMATDESCRIPTOR);
typedef int    (WINAPI *pf_GetPixelFormat)           (HDC);
typedef BOOL   (WINAPI *pf_SetPixelFormat)           (HDC, int, const PIXELFORMATDESCRIPTOR*);
typedef BOOL   (WINAPI *pf_SwapBuffers)              (HDC);

// ============================================================
// Указатели
// ============================================================
#define DECL(fn) static pf_##fn real_##fn = nullptr
DECL(glAccum); DECL(glAlphaFunc); DECL(glAreTexturesResident); DECL(glArrayElement);
DECL(glBegin); DECL(glBindTexture); DECL(glBitmap); DECL(glBlendColor);
DECL(glBlendEquation); DECL(glBlendFunc); DECL(glCallList); DECL(glCallLists);
DECL(glClear); DECL(glClearAccum); DECL(glClearColor); DECL(glClearDepth);
DECL(glClearIndex); DECL(glClearStencil); DECL(glClipPlane);
DECL(glColor3b); DECL(glColor3bv); DECL(glColor3d); DECL(glColor3dv);
DECL(glColor3f); DECL(glColor3fv); DECL(glColor3i); DECL(glColor3iv);
DECL(glColor3s); DECL(glColor3sv); DECL(glColor3ub); DECL(glColor3ubv);
DECL(glColor3ui); DECL(glColor3uiv); DECL(glColor3us); DECL(glColor3usv);
DECL(glColor4b); DECL(glColor4bv); DECL(glColor4d); DECL(glColor4dv);
DECL(glColor4f); DECL(glColor4fv); DECL(glColor4i); DECL(glColor4iv);
DECL(glColor4s); DECL(glColor4sv); DECL(glColor4ub); DECL(glColor4ubv);
DECL(glColor4ui); DECL(glColor4uiv); DECL(glColor4us); DECL(glColor4usv);
DECL(glColorMask); DECL(glColorMaterial); DECL(glColorPointer);
DECL(glCopyPixels); DECL(glCopyTexImage1D); DECL(glCopyTexImage2D);
DECL(glCopyTexSubImage1D); DECL(glCopyTexSubImage2D); DECL(glCopyTexSubImage3D);
DECL(glCullFace); DECL(glDeleteLists); DECL(glDeleteTextures);
DECL(glDepthFunc); DECL(glDepthMask); DECL(glDepthRange);
DECL(glDisable); DECL(glDisableClientState);
DECL(glDrawArrays); DECL(glDrawBuffer); DECL(glDrawElements);
DECL(glDrawPixels); DECL(glDrawRangeElements);
DECL(glEdgeFlag); DECL(glEdgeFlagPointer); DECL(glEdgeFlagv);
DECL(glEnable); DECL(glEnableClientState); DECL(glEnd); DECL(glEndList);
DECL(glEvalCoord1d); DECL(glEvalCoord1dv); DECL(glEvalCoord1f); DECL(glEvalCoord1fv);
DECL(glEvalCoord2d); DECL(glEvalCoord2dv); DECL(glEvalCoord2f); DECL(glEvalCoord2fv);
DECL(glEvalMesh1); DECL(glEvalMesh2); DECL(glEvalPoint1); DECL(glEvalPoint2);
DECL(glFeedbackBuffer); DECL(glFinish); DECL(glFlush);
DECL(glFogf); DECL(glFogfv); DECL(glFogi); DECL(glFogiv);
DECL(glFrontFace); DECL(glFrustum); DECL(glGenLists); DECL(glGenTextures);
DECL(glGetBooleanv); DECL(glGetClipPlane); DECL(glGetDoublev);
DECL(glGetError); DECL(glGetFloatv); DECL(glGetIntegerv);
DECL(glGetLightfv); DECL(glGetLightiv);
DECL(glGetMapdv); DECL(glGetMapfv); DECL(glGetMapiv);
DECL(glGetMaterialfv); DECL(glGetMaterialiv);
DECL(glGetPixelMapfv); DECL(glGetPixelMapuiv); DECL(glGetPixelMapusv);
DECL(glGetPointerv); DECL(glGetPolygonStipple); DECL(glGetString);
DECL(glGetTexEnvfv); DECL(glGetTexEnviv);
DECL(glGetTexGendv); DECL(glGetTexGenfv); DECL(glGetTexGeniv);
DECL(glGetTexImage); DECL(glGetTexLevelParameterfv); DECL(glGetTexLevelParameteriv);
DECL(glGetTexParameterfv); DECL(glGetTexParameteriv); DECL(glHint);
DECL(glIndexd); DECL(glIndexdv); DECL(glIndexf); DECL(glIndexfv);
DECL(glIndexi); DECL(glIndexiv); DECL(glIndexMask); DECL(glIndexPointer);
DECL(glIndexs); DECL(glIndexsv); DECL(glIndexub); DECL(glIndexubv);
DECL(glInitNames); DECL(glInterleavedArrays);
DECL(glIsEnabled); DECL(glIsList); DECL(glIsTexture);
DECL(glLightf); DECL(glLightfv); DECL(glLighti); DECL(glLightiv);
DECL(glLightModelf); DECL(glLightModelfv); DECL(glLightModeli); DECL(glLightModeliv);
DECL(glLineStipple); DECL(glLineWidth); DECL(glListBase);
DECL(glLoadIdentity); DECL(glLoadMatrixd); DECL(glLoadMatrixf); DECL(glLoadName);
DECL(glLogicOp);
DECL(glMap1d); DECL(glMap1f); DECL(glMap2d); DECL(glMap2f);
DECL(glMapGrid1d); DECL(glMapGrid1f); DECL(glMapGrid2d); DECL(glMapGrid2f);
DECL(glMaterialf); DECL(glMaterialfv); DECL(glMateriali); DECL(glMaterialiv);
DECL(glMatrixMode); DECL(glMultMatrixd); DECL(glMultMatrixf); DECL(glNewList);
DECL(glNormal3b); DECL(glNormal3bv); DECL(glNormal3d); DECL(glNormal3dv);
DECL(glNormal3f); DECL(glNormal3fv); DECL(glNormal3i); DECL(glNormal3iv);
DECL(glNormal3s); DECL(glNormal3sv); DECL(glNormalPointer);
DECL(glOrtho); DECL(glPassThrough);
DECL(glPixelMapfv); DECL(glPixelMapuiv); DECL(glPixelMapusv);
DECL(glPixelStoref); DECL(glPixelStorei); DECL(glPixelTransferf); DECL(glPixelTransferi);
DECL(glPixelZoom); DECL(glPointSize); DECL(glPolygonMode); DECL(glPolygonOffset);
DECL(glPolygonStipple); DECL(glPopAttrib); DECL(glPopClientAttrib);
DECL(glPopMatrix); DECL(glPopName); DECL(glPrioritizeTextures);
DECL(glPushAttrib); DECL(glPushClientAttrib); DECL(glPushMatrix); DECL(glPushName);
DECL(glRasterPos2d); DECL(glRasterPos2dv); DECL(glRasterPos2f); DECL(glRasterPos2fv);
DECL(glRasterPos2i); DECL(glRasterPos2iv); DECL(glRasterPos2s); DECL(glRasterPos2sv);
DECL(glRasterPos3d); DECL(glRasterPos3dv); DECL(glRasterPos3f); DECL(glRasterPos3fv);
DECL(glRasterPos3i); DECL(glRasterPos3iv); DECL(glRasterPos3s); DECL(glRasterPos3sv);
DECL(glRasterPos4d); DECL(glRasterPos4dv); DECL(glRasterPos4f); DECL(glRasterPos4fv);
DECL(glRasterPos4i); DECL(glRasterPos4iv); DECL(glRasterPos4s); DECL(glRasterPos4sv);
DECL(glReadBuffer); DECL(glReadPixels);
DECL(glRectd); DECL(glRectdv); DECL(glRectf); DECL(glRectfv);
DECL(glRecti); DECL(glRectiv); DECL(glRects); DECL(glRectsv);
DECL(glRenderMode); DECL(glRotated); DECL(glRotatef);
DECL(glScaled); DECL(glScalef); DECL(glScissor); DECL(glSelectBuffer);
DECL(glShadeModel); DECL(glStencilFunc); DECL(glStencilMask); DECL(glStencilOp);
DECL(glTexCoord1d); DECL(glTexCoord1dv); DECL(glTexCoord1f); DECL(glTexCoord1fv);
DECL(glTexCoord1i); DECL(glTexCoord1iv); DECL(glTexCoord1s); DECL(glTexCoord1sv);
DECL(glTexCoord2d); DECL(glTexCoord2dv); DECL(glTexCoord2f); DECL(glTexCoord2fv);
DECL(glTexCoord2i); DECL(glTexCoord2iv); DECL(glTexCoord2s); DECL(glTexCoord2sv);
DECL(glTexCoord3d); DECL(glTexCoord3dv); DECL(glTexCoord3f); DECL(glTexCoord3fv);
DECL(glTexCoord3i); DECL(glTexCoord3iv); DECL(glTexCoord3s); DECL(glTexCoord3sv);
DECL(glTexCoord4d); DECL(glTexCoord4dv); DECL(glTexCoord4f); DECL(glTexCoord4fv);
DECL(glTexCoord4i); DECL(glTexCoord4iv); DECL(glTexCoord4s); DECL(glTexCoord4sv);
DECL(glTexCoordPointer);
DECL(glTexEnvf); DECL(glTexEnvfv); DECL(glTexEnvi); DECL(glTexEnviv);
DECL(glTexGend); DECL(glTexGendv); DECL(glTexGenf); DECL(glTexGenfv);
DECL(glTexGeni); DECL(glTexGeniv);
DECL(glTexImage1D); DECL(glTexImage2D); DECL(glTexImage3D);
DECL(glTexParameterf); DECL(glTexParameterfv); DECL(glTexParameteri); DECL(glTexParameteriv);
DECL(glTexSubImage1D); DECL(glTexSubImage2D); DECL(glTexSubImage3D);
DECL(glTranslated); DECL(glTranslatef);
DECL(glVertex2d); DECL(glVertex2dv); DECL(glVertex2f); DECL(glVertex2fv);
DECL(glVertex2i); DECL(glVertex2iv); DECL(glVertex2s); DECL(glVertex2sv);
DECL(glVertex3d); DECL(glVertex3dv); DECL(glVertex3f); DECL(glVertex3fv);
DECL(glVertex3i); DECL(glVertex3iv); DECL(glVertex3s); DECL(glVertex3sv);
DECL(glVertex4d); DECL(glVertex4dv); DECL(glVertex4f); DECL(glVertex4fv);
DECL(glVertex4i); DECL(glVertex4iv); DECL(glVertex4s); DECL(glVertex4sv);
DECL(glVertexPointer); DECL(glViewport);
DECL(wglCreateContext); DECL(wglDeleteContext);
DECL(wglGetCurrentContext); DECL(wglGetCurrentDC);
DECL(wglGetProcAddress); DECL(wglMakeCurrent); DECL(wglShareLists);
DECL(wglSwapBuffers); DECL(wglCreateLayerContext); DECL(wglCopyContext);
DECL(wglChoosePixelFormat); DECL(wglDescribeLayerPlane);
DECL(wglDescribePixelFormat); DECL(wglGetDefaultProcAddress);
DECL(wglGetLayerPaletteEntries); DECL(wglGetPixelFormat);
DECL(wglRealizeLayerPalette); DECL(wglSetLayerPaletteEntries);
DECL(wglSetPixelFormat); DECL(wglSwapLayerBuffers); DECL(wglSwapMultipleBuffers);
DECL(wglUseFontBitmapsA); DECL(wglUseFontBitmapsW);
DECL(wglUseFontOutlinesA); DECL(wglUseFontOutlinesW);
DECL(ChoosePixelFormat); DECL(DescribePixelFormat);
DECL(GetPixelFormat); DECL(SetPixelFormat); DECL(SwapBuffers);
#undef DECL

// ============================================================
// Загрузка
// ============================================================
static void InitAllProcs() {
    static bool done = false;
    if (done) return;
    done = true;
#define LOAD(fn) real_##fn = (pf_##fn)GetRealGLProc(#fn)
    LOAD(glAccum); LOAD(glAlphaFunc); LOAD(glAreTexturesResident); LOAD(glArrayElement);
    LOAD(glBegin); LOAD(glBindTexture); LOAD(glBitmap); LOAD(glBlendColor);
    LOAD(glBlendEquation); LOAD(glBlendFunc); LOAD(glCallList); LOAD(glCallLists);
    LOAD(glClear); LOAD(glClearAccum); LOAD(glClearColor); LOAD(glClearDepth);
    LOAD(glClearIndex); LOAD(glClearStencil); LOAD(glClipPlane);
    LOAD(glColor3b); LOAD(glColor3bv); LOAD(glColor3d); LOAD(glColor3dv);
    LOAD(glColor3f); LOAD(glColor3fv); LOAD(glColor3i); LOAD(glColor3iv);
    LOAD(glColor3s); LOAD(glColor3sv); LOAD(glColor3ub); LOAD(glColor3ubv);
    LOAD(glColor3ui); LOAD(glColor3uiv); LOAD(glColor3us); LOAD(glColor3usv);
    LOAD(glColor4b); LOAD(glColor4bv); LOAD(glColor4d); LOAD(glColor4dv);
    LOAD(glColor4f); LOAD(glColor4fv); LOAD(glColor4i); LOAD(glColor4iv);
    LOAD(glColor4s); LOAD(glColor4sv); LOAD(glColor4ub); LOAD(glColor4ubv);
    LOAD(glColor4ui); LOAD(glColor4uiv); LOAD(glColor4us); LOAD(glColor4usv);
    LOAD(glColorMask); LOAD(glColorMaterial); LOAD(glColorPointer);
    LOAD(glCopyPixels); LOAD(glCopyTexImage1D); LOAD(glCopyTexImage2D);
    LOAD(glCopyTexSubImage1D); LOAD(glCopyTexSubImage2D); LOAD(glCopyTexSubImage3D);
    LOAD(glCullFace); LOAD(glDeleteLists); LOAD(glDeleteTextures);
    LOAD(glDepthFunc); LOAD(glDepthMask); LOAD(glDepthRange);
    LOAD(glDisable); LOAD(glDisableClientState);
    LOAD(glDrawArrays); LOAD(glDrawBuffer); LOAD(glDrawElements);
    LOAD(glDrawPixels); LOAD(glDrawRangeElements);
    LOAD(glEdgeFlag); LOAD(glEdgeFlagPointer); LOAD(glEdgeFlagv);
    LOAD(glEnable); LOAD(glEnableClientState); LOAD(glEnd); LOAD(glEndList);
    LOAD(glEvalCoord1d); LOAD(glEvalCoord1dv); LOAD(glEvalCoord1f); LOAD(glEvalCoord1fv);
    LOAD(glEvalCoord2d); LOAD(glEvalCoord2dv); LOAD(glEvalCoord2f); LOAD(glEvalCoord2fv);
    LOAD(glEvalMesh1); LOAD(glEvalMesh2); LOAD(glEvalPoint1); LOAD(glEvalPoint2);
    LOAD(glFeedbackBuffer); LOAD(glFinish); LOAD(glFlush);
    LOAD(glFogf); LOAD(glFogfv); LOAD(glFogi); LOAD(glFogiv);
    LOAD(glFrontFace); LOAD(glFrustum); LOAD(glGenLists); LOAD(glGenTextures);
    LOAD(glGetBooleanv); LOAD(glGetClipPlane); LOAD(glGetDoublev);
    LOAD(glGetError); LOAD(glGetFloatv); LOAD(glGetIntegerv);
    LOAD(glGetLightfv); LOAD(glGetLightiv);
    LOAD(glGetMapdv); LOAD(glGetMapfv); LOAD(glGetMapiv);
    LOAD(glGetMaterialfv); LOAD(glGetMaterialiv);
    LOAD(glGetPixelMapfv); LOAD(glGetPixelMapuiv); LOAD(glGetPixelMapusv);
    LOAD(glGetPointerv); LOAD(glGetPolygonStipple); LOAD(glGetString);
    LOAD(glGetTexEnvfv); LOAD(glGetTexEnviv);
    LOAD(glGetTexGendv); LOAD(glGetTexGenfv); LOAD(glGetTexGeniv);
    LOAD(glGetTexImage); LOAD(glGetTexLevelParameterfv); LOAD(glGetTexLevelParameteriv);
    LOAD(glGetTexParameterfv); LOAD(glGetTexParameteriv); LOAD(glHint);
    LOAD(glIndexd); LOAD(glIndexdv); LOAD(glIndexf); LOAD(glIndexfv);
    LOAD(glIndexi); LOAD(glIndexiv); LOAD(glIndexMask); LOAD(glIndexPointer);
    LOAD(glIndexs); LOAD(glIndexsv); LOAD(glIndexub); LOAD(glIndexubv);
    LOAD(glInitNames); LOAD(glInterleavedArrays);
    LOAD(glIsEnabled); LOAD(glIsList); LOAD(glIsTexture);
    LOAD(glLightf); LOAD(glLightfv); LOAD(glLighti); LOAD(glLightiv);
    LOAD(glLightModelf); LOAD(glLightModelfv); LOAD(glLightModeli); LOAD(glLightModeliv);
    LOAD(glLineStipple); LOAD(glLineWidth); LOAD(glListBase);
    LOAD(glLoadIdentity); LOAD(glLoadMatrixd); LOAD(glLoadMatrixf); LOAD(glLoadName);
    LOAD(glLogicOp);
    LOAD(glMap1d); LOAD(glMap1f); LOAD(glMap2d); LOAD(glMap2f);
    LOAD(glMapGrid1d); LOAD(glMapGrid1f); LOAD(glMapGrid2d); LOAD(glMapGrid2f);
    LOAD(glMaterialf); LOAD(glMaterialfv); LOAD(glMateriali); LOAD(glMaterialiv);
    LOAD(glMatrixMode); LOAD(glMultMatrixd); LOAD(glMultMatrixf); LOAD(glNewList);
    LOAD(glNormal3b); LOAD(glNormal3bv); LOAD(glNormal3d); LOAD(glNormal3dv);
    LOAD(glNormal3f); LOAD(glNormal3fv); LOAD(glNormal3i); LOAD(glNormal3iv);
    LOAD(glNormal3s); LOAD(glNormal3sv); LOAD(glNormalPointer);
    LOAD(glOrtho); LOAD(glPassThrough);
    LOAD(glPixelMapfv); LOAD(glPixelMapuiv); LOAD(glPixelMapusv);
    LOAD(glPixelStoref); LOAD(glPixelStorei); LOAD(glPixelTransferf); LOAD(glPixelTransferi);
    LOAD(glPixelZoom); LOAD(glPointSize); LOAD(glPolygonMode); LOAD(glPolygonOffset);
    LOAD(glPolygonStipple); LOAD(glPopAttrib); LOAD(glPopClientAttrib);
    LOAD(glPopMatrix); LOAD(glPopName); LOAD(glPrioritizeTextures);
    LOAD(glPushAttrib); LOAD(glPushClientAttrib); LOAD(glPushMatrix); LOAD(glPushName);
    LOAD(glRasterPos2d); LOAD(glRasterPos2dv); LOAD(glRasterPos2f); LOAD(glRasterPos2fv);
    LOAD(glRasterPos2i); LOAD(glRasterPos2iv); LOAD(glRasterPos2s); LOAD(glRasterPos2sv);
    LOAD(glRasterPos3d); LOAD(glRasterPos3dv); LOAD(glRasterPos3f); LOAD(glRasterPos3fv);
    LOAD(glRasterPos3i); LOAD(glRasterPos3iv); LOAD(glRasterPos3s); LOAD(glRasterPos3sv);
    LOAD(glRasterPos4d); LOAD(glRasterPos4dv); LOAD(glRasterPos4f); LOAD(glRasterPos4fv);
    LOAD(glRasterPos4i); LOAD(glRasterPos4iv); LOAD(glRasterPos4s); LOAD(glRasterPos4sv);
    LOAD(glReadBuffer); LOAD(glReadPixels);
    LOAD(glRectd); LOAD(glRectdv); LOAD(glRectf); LOAD(glRectfv);
    LOAD(glRecti); LOAD(glRectiv); LOAD(glRects); LOAD(glRectsv);
    LOAD(glRenderMode); LOAD(glRotated); LOAD(glRotatef);
    LOAD(glScaled); LOAD(glScalef); LOAD(glScissor); LOAD(glSelectBuffer);
    LOAD(glShadeModel); LOAD(glStencilFunc); LOAD(glStencilMask); LOAD(glStencilOp);
    LOAD(glTexCoord1d); LOAD(glTexCoord1dv); LOAD(glTexCoord1f); LOAD(glTexCoord1fv);
    LOAD(glTexCoord1i); LOAD(glTexCoord1iv); LOAD(glTexCoord1s); LOAD(glTexCoord1sv);
    LOAD(glTexCoord2d); LOAD(glTexCoord2dv); LOAD(glTexCoord2f); LOAD(glTexCoord2fv);
    LOAD(glTexCoord2i); LOAD(glTexCoord2iv); LOAD(glTexCoord2s); LOAD(glTexCoord2sv);
    LOAD(glTexCoord3d); LOAD(glTexCoord3dv); LOAD(glTexCoord3f); LOAD(glTexCoord3fv);
    LOAD(glTexCoord3i); LOAD(glTexCoord3iv); LOAD(glTexCoord3s); LOAD(glTexCoord3sv);
    LOAD(glTexCoord4d); LOAD(glTexCoord4dv); LOAD(glTexCoord4f); LOAD(glTexCoord4fv);
    LOAD(glTexCoord4i); LOAD(glTexCoord4iv); LOAD(glTexCoord4s); LOAD(glTexCoord4sv);
    LOAD(glTexCoordPointer);
    LOAD(glTexEnvf); LOAD(glTexEnvfv); LOAD(glTexEnvi); LOAD(glTexEnviv);
    LOAD(glTexGend); LOAD(glTexGendv); LOAD(glTexGenf); LOAD(glTexGenfv);
    LOAD(glTexGeni); LOAD(glTexGeniv);
    LOAD(glTexImage1D); LOAD(glTexImage2D); LOAD(glTexImage3D);
    LOAD(glTexParameterf); LOAD(glTexParameterfv); LOAD(glTexParameteri); LOAD(glTexParameteriv);
    LOAD(glTexSubImage1D); LOAD(glTexSubImage2D); LOAD(glTexSubImage3D);
    LOAD(glTranslated); LOAD(glTranslatef);
    LOAD(glVertex2d); LOAD(glVertex2dv); LOAD(glVertex2f); LOAD(glVertex2fv);
    LOAD(glVertex2i); LOAD(glVertex2iv); LOAD(glVertex2s); LOAD(glVertex2sv);
    LOAD(glVertex3d); LOAD(glVertex3dv); LOAD(glVertex3f); LOAD(glVertex3fv);
    LOAD(glVertex3i); LOAD(glVertex3iv); LOAD(glVertex3s); LOAD(glVertex3sv);
    LOAD(glVertex4d); LOAD(glVertex4dv); LOAD(glVertex4f); LOAD(glVertex4fv);
    LOAD(glVertex4i); LOAD(glVertex4iv); LOAD(glVertex4s); LOAD(glVertex4sv);
    LOAD(glVertexPointer); LOAD(glViewport);
    LOAD(wglCreateContext); LOAD(wglDeleteContext);
    LOAD(wglGetCurrentContext); LOAD(wglGetCurrentDC);
    LOAD(wglGetProcAddress); LOAD(wglMakeCurrent); LOAD(wglShareLists);
    LOAD(wglSwapBuffers); LOAD(wglCreateLayerContext); LOAD(wglCopyContext);
    LOAD(wglChoosePixelFormat); LOAD(wglDescribeLayerPlane);
    LOAD(wglDescribePixelFormat); LOAD(wglGetDefaultProcAddress);
    LOAD(wglGetLayerPaletteEntries); LOAD(wglGetPixelFormat);
    LOAD(wglRealizeLayerPalette); LOAD(wglSetLayerPaletteEntries);
    LOAD(wglSetPixelFormat); LOAD(wglSwapLayerBuffers); LOAD(wglSwapMultipleBuffers);
    LOAD(wglUseFontBitmapsA); LOAD(wglUseFontBitmapsW);
    LOAD(wglUseFontOutlinesA); LOAD(wglUseFontOutlinesW);
    LOAD(ChoosePixelFormat); LOAD(DescribePixelFormat);
    LOAD(GetPixelFormat); LOAD(SetPixelFormat); LOAD(SwapBuffers);
#undef LOAD
}

// ============================================================
// DllMain
// ============================================================
BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID) {
    (void)hInst;
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hInst);
            if (!InitRealGL()) return FALSE;
            InitAllProcs();
            Log("Proxy DLL attached successfully");
            break;
        case DLL_PROCESS_DETACH:
            ShutdownRealGL();
            break;
    }
    return TRUE;
}

// ============================================================
// Экспортируемые функции
// ============================================================
extern "C" {

// --- Перехваченные ---
BOOL WINAPI wglSwapBuffers(HDC hdc) {
    OnSwapBuffers(hdc);
    return real_wglSwapBuffers ? real_wglSwapBuffers(hdc) : TRUE;
}
BOOL WINAPI SwapBuffers(HDC hdc) {
    OnSwapBuffers(hdc);
    return real_SwapBuffers ? real_SwapBuffers(hdc) : TRUE;
}
PROC WINAPI wglGetProcAddress(LPCSTR name) {
    return real_wglGetProcAddress ? real_wglGetProcAddress(name) : nullptr;
}

// --- Forward GL ---
void WINAPI glAccum(GLenum op,GLfloat v){if(real_glAccum)real_glAccum(op,v);}
void WINAPI glAlphaFunc(GLenum f,GLclampf r){if(real_glAlphaFunc)real_glAlphaFunc(f,r);}
GLboolean WINAPI glAreTexturesResident(GLsizei n,const GLuint* t,GLboolean* r){return real_glAreTexturesResident?real_glAreTexturesResident(n,t,r):GL_FALSE;}
void WINAPI glArrayElement(GLint i){if(real_glArrayElement)real_glArrayElement(i);}
void WINAPI glBegin(GLenum m){if(real_glBegin)real_glBegin(m);}
void WINAPI glBindTexture(GLenum t,GLuint x){if(real_glBindTexture)real_glBindTexture(t,x);}
void WINAPI glBitmap(GLsizei w,GLsizei h,GLfloat xo,GLfloat yo,GLfloat xm,GLfloat ym,const GLubyte* b){if(real_glBitmap)real_glBitmap(w,h,xo,yo,xm,ym,b);}
void WINAPI glBlendColor(GLclampf r,GLclampf g,GLclampf b,GLclampf a){if(real_glBlendColor)real_glBlendColor(r,g,b,a);}
void WINAPI glBlendEquation(GLenum m){if(real_glBlendEquation)real_glBlendEquation(m);}
void WINAPI glBlendFunc(GLenum s,GLenum d){if(real_glBlendFunc)real_glBlendFunc(s,d);}
void WINAPI glCallList(GLuint l){if(real_glCallList)real_glCallList(l);}
void WINAPI glCallLists(GLsizei n,GLenum t,const void* l){if(real_glCallLists)real_glCallLists(n,t,l);}
void WINAPI glClear(GLbitfield m){if(real_glClear)real_glClear(m);}
void WINAPI glClearAccum(GLfloat r,GLfloat g,GLfloat b,GLfloat a){if(real_glClearAccum)real_glClearAccum(r,g,b,a);}
void WINAPI glClearColor(GLclampf r,GLclampf g,GLclampf b,GLclampf a){if(real_glClearColor)real_glClearColor(r,g,b,a);}
void WINAPI glClearDepth(GLclampd d){if(real_glClearDepth)real_glClearDepth(d);}
void WINAPI glClearIndex(GLfloat c){if(real_glClearIndex)real_glClearIndex(c);}
void WINAPI glClearStencil(GLint s){if(real_glClearStencil)real_glClearStencil(s);}
void WINAPI glClipPlane(GLenum p,const GLdouble* e){if(real_glClipPlane)real_glClipPlane(p,e);}
void WINAPI glColor3b(GLbyte r,GLbyte g,GLbyte b){if(real_glColor3b)real_glColor3b(r,g,b);}
void WINAPI glColor3bv(const GLbyte* v){if(real_glColor3bv)real_glColor3bv(v);}
void WINAPI glColor3d(GLdouble r,GLdouble g,GLdouble b){if(real_glColor3d)real_glColor3d(r,g,b);}
void WINAPI glColor3dv(const GLdouble* v){if(real_glColor3dv)real_glColor3dv(v);}
void WINAPI glColor3f(GLfloat r,GLfloat g,GLfloat b){if(real_glColor3f)real_glColor3f(r,g,b);}
void WINAPI glColor3fv(const GLfloat* v){if(real_glColor3fv)real_glColor3fv(v);}
void WINAPI glColor3i(GLint r,GLint g,GLint b){if(real_glColor3i)real_glColor3i(r,g,b);}
void WINAPI glColor3iv(const GLint* v){if(real_glColor3iv)real_glColor3iv(v);}
void WINAPI glColor3s(GLshort r,GLshort g,GLshort b){if(real_glColor3s)real_glColor3s(r,g,b);}
void WINAPI glColor3sv(const GLshort* v){if(real_glColor3sv)real_glColor3sv(v);}
void WINAPI glColor3ub(GLubyte r,GLubyte g,GLubyte b){if(real_glColor3ub)real_glColor3ub(r,g,b);}
void WINAPI glColor3ubv(const GLubyte* v){if(real_glColor3ubv)real_glColor3ubv(v);}
void WINAPI glColor3ui(GLuint r,GLuint g,GLuint b){if(real_glColor3ui)real_glColor3ui(r,g,b);}
void WINAPI glColor3uiv(const GLuint* v){if(real_glColor3uiv)real_glColor3uiv(v);}
void WINAPI glColor3us(GLushort r,GLushort g,GLushort b){if(real_glColor3us)real_glColor3us(r,g,b);}
void WINAPI glColor3usv(const GLushort* v){if(real_glColor3usv)real_glColor3usv(v);}
void WINAPI glColor4b(GLbyte r,GLbyte g,GLbyte b,GLbyte a){if(real_glColor4b)real_glColor4b(r,g,b,a);}
void WINAPI glColor4bv(const GLbyte* v){if(real_glColor4bv)real_glColor4bv(v);}
void WINAPI glColor4d(GLdouble r,GLdouble g,GLdouble b,GLdouble a){if(real_glColor4d)real_glColor4d(r,g,b,a);}
void WINAPI glColor4dv(const GLdouble* v){if(real_glColor4dv)real_glColor4dv(v);}
void WINAPI glColor4f(GLfloat r,GLfloat g,GLfloat b,GLfloat a){if(real_glColor4f)real_glColor4f(r,g,b,a);}
void WINAPI glColor4fv(const GLfloat* v){if(real_glColor4fv)real_glColor4fv(v);}
void WINAPI glColor4i(GLint r,GLint g,GLint b,GLint a){if(real_glColor4i)real_glColor4i(r,g,b,a);}
void WINAPI glColor4iv(const GLint* v){if(real_glColor4iv)real_glColor4iv(v);}
void WINAPI glColor4s(GLshort r,GLshort g,GLshort b,GLshort a){if(real_glColor4s)real_glColor4s(r,g,b,a);}
void WINAPI glColor4sv(const GLshort* v){if(real_glColor4sv)real_glColor4sv(v);}
void WINAPI glColor4ub(GLubyte r,GLubyte g,GLubyte b,GLubyte a){if(real_glColor4ub)real_glColor4ub(r,g,b,a);}
void WINAPI glColor4ubv(const GLubyte* v){if(real_glColor4ubv)real_glColor4ubv(v);}
void WINAPI glColor4ui(GLuint r,GLuint g,GLuint b,GLuint a){if(real_glColor4ui)real_glColor4ui(r,g,b,a);}
void WINAPI glColor4uiv(const GLuint* v){if(real_glColor4uiv)real_glColor4uiv(v);}
void WINAPI glColor4us(GLushort r,GLushort g,GLushort b,GLushort a){if(real_glColor4us)real_glColor4us(r,g,b,a);}
void WINAPI glColor4usv(const GLushort* v){if(real_glColor4usv)real_glColor4usv(v);}
void WINAPI glColorMask(GLboolean r,GLboolean g,GLboolean b,GLboolean a){if(real_glColorMask)real_glColorMask(r,g,b,a);}
void WINAPI glColorMaterial(GLenum f,GLenum m){if(real_glColorMaterial)real_glColorMaterial(f,m);}
void WINAPI glColorPointer(GLint s,GLenum t,GLsizei st,const void* p){if(real_glColorPointer)real_glColorPointer(s,t,st,p);}
void WINAPI glCopyPixels(GLint x,GLint y,GLsizei w,GLsizei h,GLenum t){if(real_glCopyPixels)real_glCopyPixels(x,y,w,h,t);}
void WINAPI glCopyTexImage1D(GLenum t,GLint l,GLenum f,GLint x,GLint y,GLsizei w,GLint b){if(real_glCopyTexImage1D)real_glCopyTexImage1D(t,l,f,x,y,w,b);}
void WINAPI glCopyTexImage2D(GLenum t,GLint l,GLenum f,GLint x,GLint y,GLsizei w,GLsizei h,GLint b){if(real_glCopyTexImage2D)real_glCopyTexImage2D(t,l,f,x,y,w,h,b);}
void WINAPI glCopyTexSubImage1D(GLenum t,GLint l,GLint xo,GLint x,GLint y,GLsizei w){if(real_glCopyTexSubImage1D)real_glCopyTexSubImage1D(t,l,xo,x,y,w);}
void WINAPI glCopyTexSubImage2D(GLenum t,GLint l,GLint xo,GLint yo,GLint x,GLint y,GLsizei w,GLsizei h){if(real_glCopyTexSubImage2D)real_glCopyTexSubImage2D(t,l,xo,yo,x,y,w,h);}
void WINAPI glCopyTexSubImage3D(GLenum t,GLint l,GLint xo,GLint yo,GLint zo,GLint x,GLint y,GLsizei w,GLsizei h){if(real_glCopyTexSubImage3D)real_glCopyTexSubImage3D(t,l,xo,yo,zo,x,y,w,h);}
void WINAPI glCullFace(GLenum m){if(real_glCullFace)real_glCullFace(m);}
void WINAPI glDeleteLists(GLuint l,GLsizei r){if(real_glDeleteLists)real_glDeleteLists(l,r);}
void WINAPI glDeleteTextures(GLsizei n,const GLuint* t){if(real_glDeleteTextures)real_glDeleteTextures(n,t);}
void WINAPI glDepthFunc(GLenum f){if(real_glDepthFunc)real_glDepthFunc(f);}
void WINAPI glDepthMask(GLboolean f){if(real_glDepthMask)real_glDepthMask(f);}
void WINAPI glDepthRange(GLclampd n,GLclampd f){if(real_glDepthRange)real_glDepthRange(n,f);}
void WINAPI glDisable(GLenum c){if(real_glDisable)real_glDisable(c);}
void WINAPI glDisableClientState(GLenum a){if(real_glDisableClientState)real_glDisableClientState(a);}
void WINAPI glDrawArrays(GLenum m,GLint f,GLsizei c){if(real_glDrawArrays)real_glDrawArrays(m,f,c);}
void WINAPI glDrawBuffer(GLenum m){if(real_glDrawBuffer)real_glDrawBuffer(m);}
void WINAPI glDrawElements(GLenum m,GLsizei c,GLenum t,const void* i){if(real_glDrawElements)real_glDrawElements(m,c,t,i);}
void WINAPI glDrawPixels(GLsizei w,GLsizei h,GLenum f,GLenum t,const void* p){if(real_glDrawPixels)real_glDrawPixels(w,h,f,t,p);}
void WINAPI glDrawRangeElements(GLenum m,GLuint s,GLuint e,GLsizei c,GLenum t,const void* i){if(real_glDrawRangeElements)real_glDrawRangeElements(m,s,e,c,t,i);}
void WINAPI glEdgeFlag(GLboolean f){if(real_glEdgeFlag)real_glEdgeFlag(f);}
void WINAPI glEdgeFlagPointer(GLsizei s,const void* p){if(real_glEdgeFlagPointer)real_glEdgeFlagPointer(s,p);}
void WINAPI glEdgeFlagv(const GLboolean* f){if(real_glEdgeFlagv)real_glEdgeFlagv(f);}
void WINAPI glEnable(GLenum c){if(real_glEnable)real_glEnable(c);}
void WINAPI glEnableClientState(GLenum a){if(real_glEnableClientState)real_glEnableClientState(a);}
void WINAPI glEnd(){if(real_glEnd)real_glEnd();}
void WINAPI glEndList(){if(real_glEndList)real_glEndList();}
void WINAPI glEvalCoord1d(GLdouble u){if(real_glEvalCoord1d)real_glEvalCoord1d(u);}
void WINAPI glEvalCoord1dv(const GLdouble* u){if(real_glEvalCoord1dv)real_glEvalCoord1dv(u);}
void WINAPI glEvalCoord1f(GLfloat u){if(real_glEvalCoord1f)real_glEvalCoord1f(u);}
void WINAPI glEvalCoord1fv(const GLfloat* u){if(real_glEvalCoord1fv)real_glEvalCoord1fv(u);}
void WINAPI glEvalCoord2d(GLdouble u,GLdouble v){if(real_glEvalCoord2d)real_glEvalCoord2d(u,v);}
void WINAPI glEvalCoord2dv(const GLdouble* u){if(real_glEvalCoord2dv)real_glEvalCoord2dv(u);}
void WINAPI glEvalCoord2f(GLfloat u,GLfloat v){if(real_glEvalCoord2f)real_glEvalCoord2f(u,v);}
void WINAPI glEvalCoord2fv(const GLfloat* u){if(real_glEvalCoord2fv)real_glEvalCoord2fv(u);}
void WINAPI glEvalMesh1(GLenum m,GLint i1,GLint i2){if(real_glEvalMesh1)real_glEvalMesh1(m,i1,i2);}
void WINAPI glEvalMesh2(GLenum m,GLint i1,GLint i2,GLint j1,GLint j2){if(real_glEvalMesh2)real_glEvalMesh2(m,i1,i2,j1,j2);}
void WINAPI glEvalPoint1(GLint i){if(real_glEvalPoint1)real_glEvalPoint1(i);}
void WINAPI glEvalPoint2(GLint i,GLint j){if(real_glEvalPoint2)real_glEvalPoint2(i,j);}
void WINAPI glFeedbackBuffer(GLsizei s,GLenum t,GLfloat* b){if(real_glFeedbackBuffer)real_glFeedbackBuffer(s,t,b);}
void WINAPI glFinish(){if(real_glFinish)real_glFinish();}
void WINAPI glFlush(){if(real_glFlush)real_glFlush();}
void WINAPI glFogf(GLenum p,GLfloat v){if(real_glFogf)real_glFogf(p,v);}
void WINAPI glFogfv(GLenum p,const GLfloat* v){if(real_glFogfv)real_glFogfv(p,v);}
void WINAPI glFogi(GLenum p,GLint v){if(real_glFogi)real_glFogi(p,v);}
void WINAPI glFogiv(GLenum p,const GLint* v){if(real_glFogiv)real_glFogiv(p,v);}
void WINAPI glFrontFace(GLenum m){if(real_glFrontFace)real_glFrontFace(m);}
void WINAPI glFrustum(GLdouble l,GLdouble r,GLdouble b,GLdouble t,GLdouble n,GLdouble f){if(real_glFrustum)real_glFrustum(l,r,b,t,n,f);}
GLuint WINAPI glGenLists(GLsizei r){return real_glGenLists?real_glGenLists(r):0;}
void WINAPI glGenTextures(GLsizei n,GLuint* t){if(real_glGenTextures)real_glGenTextures(n,t);}
void WINAPI glGetBooleanv(GLenum p,GLboolean* d){if(real_glGetBooleanv)real_glGetBooleanv(p,d);}
void WINAPI glGetClipPlane(GLenum p,GLdouble* e){if(real_glGetClipPlane)real_glGetClipPlane(p,e);}
void WINAPI glGetDoublev(GLenum p,GLdouble* d){if(real_glGetDoublev)real_glGetDoublev(p,d);}
GLenum WINAPI glGetError(){return real_glGetError?real_glGetError():GL_NO_ERROR;}
void WINAPI glGetFloatv(GLenum p,GLfloat* d){if(real_glGetFloatv)real_glGetFloatv(p,d);}
void WINAPI glGetIntegerv(GLenum p,GLint* d){if(real_glGetIntegerv)real_glGetIntegerv(p,d);}
void WINAPI glGetLightfv(GLenum l,GLenum p,GLfloat* v){if(real_glGetLightfv)real_glGetLightfv(l,p,v);}
void WINAPI glGetLightiv(GLenum l,GLenum p,GLint* v){if(real_glGetLightiv)real_glGetLightiv(l,p,v);}
void WINAPI glGetMapdv(GLenum t,GLenum q,GLdouble* v){if(real_glGetMapdv)real_glGetMapdv(t,q,v);}
void WINAPI glGetMapfv(GLenum t,GLenum q,GLfloat* v){if(real_glGetMapfv)real_glGetMapfv(t,q,v);}
void WINAPI glGetMapiv(GLenum t,GLenum q,GLint* v){if(real_glGetMapiv)real_glGetMapiv(t,q,v);}
void WINAPI glGetMaterialfv(GLenum f,GLenum p,GLfloat* v){if(real_glGetMaterialfv)real_glGetMaterialfv(f,p,v);}
void WINAPI glGetMaterialiv(GLenum f,GLenum p,GLint* v){if(real_glGetMaterialiv)real_glGetMaterialiv(f,p,v);}
void WINAPI glGetPixelMapfv(GLenum m,GLfloat* v){if(real_glGetPixelMapfv)real_glGetPixelMapfv(m,v);}
void WINAPI glGetPixelMapuiv(GLenum m,GLuint* v){if(real_glGetPixelMapuiv)real_glGetPixelMapuiv(m,v);}
void WINAPI glGetPixelMapusv(GLenum m,GLushort* v){if(real_glGetPixelMapusv)real_glGetPixelMapusv(m,v);}
void WINAPI glGetPointerv(GLenum p,void** v){if(real_glGetPointerv)real_glGetPointerv(p,v);}
void WINAPI glGetPolygonStipple(GLubyte* m){if(real_glGetPolygonStipple)real_glGetPolygonStipple(m);}
const GLubyte* WINAPI glGetString(GLenum n){return real_glGetString?real_glGetString(n):nullptr;}
void WINAPI glGetTexEnvfv(GLenum t,GLenum p,GLfloat* v){if(real_glGetTexEnvfv)real_glGetTexEnvfv(t,p,v);}
void WINAPI glGetTexEnviv(GLenum t,GLenum p,GLint* v){if(real_glGetTexEnviv)real_glGetTexEnviv(t,p,v);}
void WINAPI glGetTexGendv(GLenum c,GLenum p,GLdouble* v){if(real_glGetTexGendv)real_glGetTexGendv(c,p,v);}
void WINAPI glGetTexGenfv(GLenum c,GLenum p,GLfloat* v){if(real_glGetTexGenfv)real_glGetTexGenfv(c,p,v);}
void WINAPI glGetTexGeniv(GLenum c,GLenum p,GLint* v){if(real_glGetTexGeniv)real_glGetTexGeniv(c,p,v);}
void WINAPI glGetTexImage(GLenum t,GLint l,GLenum f,GLenum ty,void* p){if(real_glGetTexImage)real_glGetTexImage(t,l,f,ty,p);}
void WINAPI glGetTexLevelParameterfv(GLenum t,GLint l,GLenum p,GLfloat* v){if(real_glGetTexLevelParameterfv)real_glGetTexLevelParameterfv(t,l,p,v);}
void WINAPI glGetTexLevelParameteriv(GLenum t,GLint l,GLenum p,GLint* v){if(real_glGetTexLevelParameteriv)real_glGetTexLevelParameteriv(t,l,p,v);}
void WINAPI glGetTexParameterfv(GLenum t,GLenum p,GLfloat* v){if(real_glGetTexParameterfv)real_glGetTexParameterfv(t,p,v);}
void WINAPI glGetTexParameteriv(GLenum t,GLenum p,GLint* v){if(real_glGetTexParameteriv)real_glGetTexParameteriv(t,p,v);}
void WINAPI glHint(GLenum t,GLenum m){if(real_glHint)real_glHint(t,m);}
void WINAPI glIndexd(GLdouble c){if(real_glIndexd)real_glIndexd(c);}
void WINAPI glIndexdv(const GLdouble* c){if(real_glIndexdv)real_glIndexdv(c);}
void WINAPI glIndexf(GLfloat c){if(real_glIndexf)real_glIndexf(c);}
void WINAPI glIndexfv(const GLfloat* c){if(real_glIndexfv)real_glIndexfv(c);}
void WINAPI glIndexi(GLint c){if(real_glIndexi)real_glIndexi(c);}
void WINAPI glIndexiv(const GLint* c){if(real_glIndexiv)real_glIndexiv(c);}
void WINAPI glIndexMask(GLuint m){if(real_glIndexMask)real_glIndexMask(m);}
void WINAPI glIndexPointer(GLenum t,GLsizei s,const void* p){if(real_glIndexPointer)real_glIndexPointer(t,s,p);}
void WINAPI glIndexs(GLshort c){if(real_glIndexs)real_glIndexs(c);}
void WINAPI glIndexsv(const GLshort* c){if(real_glIndexsv)real_glIndexsv(c);}
void WINAPI glIndexub(GLubyte c){if(real_glIndexub)real_glIndexub(c);}
void WINAPI glIndexubv(const GLubyte* c){if(real_glIndexubv)real_glIndexubv(c);}
void WINAPI glInitNames(){if(real_glInitNames)real_glInitNames();}
void WINAPI glInterleavedArrays(GLenum f,GLsizei s,const void* p){if(real_glInterleavedArrays)real_glInterleavedArrays(f,s,p);}
GLboolean WINAPI glIsEnabled(GLenum c){return real_glIsEnabled?real_glIsEnabled(c):GL_FALSE;}
GLboolean WINAPI glIsList(GLuint l){return real_glIsList?real_glIsList(l):GL_FALSE;}
GLboolean WINAPI glIsTexture(GLuint t){return real_glIsTexture?real_glIsTexture(t):GL_FALSE;}
void WINAPI glLightf(GLenum l,GLenum p,GLfloat v){if(real_glLightf)real_glLightf(l,p,v);}
void WINAPI glLightfv(GLenum l,GLenum p,const GLfloat* v){if(real_glLightfv)real_glLightfv(l,p,v);}
void WINAPI glLighti(GLenum l,GLenum p,GLint v){if(real_glLighti)real_glLighti(l,p,v);}
void WINAPI glLightiv(GLenum l,GLenum p,const GLint* v){if(real_glLightiv)real_glLightiv(l,p,v);}
void WINAPI glLightModelf(GLenum p,GLfloat v){if(real_glLightModelf)real_glLightModelf(p,v);}
void WINAPI glLightModelfv(GLenum p,const GLfloat* v){if(real_glLightModelfv)real_glLightModelfv(p,v);}
void WINAPI glLightModeli(GLenum p,GLint v){if(real_glLightModeli)real_glLightModeli(p,v);}
void WINAPI glLightModeliv(GLenum p,const GLint* v){if(real_glLightModeliv)real_glLightModeliv(p,v);}
void WINAPI glLineStipple(GLint f,GLushort p){if(real_glLineStipple)real_glLineStipple(f,p);}
void WINAPI glLineWidth(GLfloat w){if(real_glLineWidth)real_glLineWidth(w);}
void WINAPI glListBase(GLuint b){if(real_glListBase)real_glListBase(b);}
void WINAPI glLoadIdentity(){if(real_glLoadIdentity)real_glLoadIdentity();}
void WINAPI glLoadMatrixd(const GLdouble* m){if(real_glLoadMatrixd)real_glLoadMatrixd(m);}
void WINAPI glLoadMatrixf(const GLfloat* m){if(real_glLoadMatrixf)real_glLoadMatrixf(m);}
void WINAPI glLoadName(GLuint n){if(real_glLoadName)real_glLoadName(n);}
void WINAPI glLogicOp(GLenum o){if(real_glLogicOp)real_glLogicOp(o);}
void WINAPI glMap1d(GLenum t,GLdouble u1,GLdouble u2,GLint s,GLint o,const GLdouble* p){if(real_glMap1d)real_glMap1d(t,u1,u2,s,o,p);}
void WINAPI glMap1f(GLenum t,GLfloat u1,GLfloat u2,GLint s,GLint o,const GLfloat* p){if(real_glMap1f)real_glMap1f(t,u1,u2,s,o,p);}
void WINAPI glMap2d(GLenum t,GLdouble u1,GLdouble u2,GLint us,GLint uo,GLdouble v1,GLdouble v2,GLint vs,GLint vo,const GLdouble* p){if(real_glMap2d)real_glMap2d(t,u1,u2,us,uo,v1,v2,vs,vo,p);}
void WINAPI glMap2f(GLenum t,GLfloat u1,GLfloat u2,GLint us,GLint uo,GLfloat v1,GLfloat v2,GLint vs,GLint vo,const GLfloat* p){if(real_glMap2f)real_glMap2f(t,u1,u2,us,uo,v1,v2,vs,vo,p);}
void WINAPI glMapGrid1d(GLint n,GLdouble u1,GLdouble u2){if(real_glMapGrid1d)real_glMapGrid1d(n,u1,u2);}
void WINAPI glMapGrid1f(GLint n,GLfloat u1,GLfloat u2){if(real_glMapGrid1f)real_glMapGrid1f(n,u1,u2);}
void WINAPI glMapGrid2d(GLint nu,GLdouble u1,GLdouble u2,GLint nv,GLdouble v1,GLdouble v2){if(real_glMapGrid2d)real_glMapGrid2d(nu,u1,u2,nv,v1,v2);}
void WINAPI glMapGrid2f(GLint nu,GLfloat u1,GLfloat u2,GLint nv,GLfloat v1,GLfloat v2){if(real_glMapGrid2f)real_glMapGrid2f(nu,u1,u2,nv,v1,v2);}
void WINAPI glMaterialf(GLenum f,GLenum p,GLfloat v){if(real_glMaterialf)real_glMaterialf(f,p,v);}
void WINAPI glMaterialfv(GLenum f,GLenum p,const GLfloat* v){if(real_glMaterialfv)real_glMaterialfv(f,p,v);}
void WINAPI glMateriali(GLenum f,GLenum p,GLint v){if(real_glMateriali)real_glMateriali(f,p,v);}
void WINAPI glMaterialiv(GLenum f,GLenum p,const GLint* v){if(real_glMaterialiv)real_glMaterialiv(f,p,v);}
void WINAPI glMatrixMode(GLenum m){if(real_glMatrixMode)real_glMatrixMode(m);}
void WINAPI glMultMatrixd(const GLdouble* m){if(real_glMultMatrixd)real_glMultMatrixd(m);}
void WINAPI glMultMatrixf(const GLfloat* m){if(real_glMultMatrixf)real_glMultMatrixf(m);}
void WINAPI glNewList(GLuint l,GLenum m){if(real_glNewList)real_glNewList(l,m);}
void WINAPI glNormal3b(GLbyte x,GLbyte y,GLbyte z){if(real_glNormal3b)real_glNormal3b(x,y,z);}
void WINAPI glNormal3bv(const GLbyte* v){if(real_glNormal3bv)real_glNormal3bv(v);}
void WINAPI glNormal3d(GLdouble x,GLdouble y,GLdouble z){if(real_glNormal3d)real_glNormal3d(x,y,z);}
void WINAPI glNormal3dv(const GLdouble* v){if(real_glNormal3dv)real_glNormal3dv(v);}
void WINAPI glNormal3f(GLfloat x,GLfloat y,GLfloat z){if(real_glNormal3f)real_glNormal3f(x,y,z);}
void WINAPI glNormal3fv(const GLfloat* v){if(real_glNormal3fv)real_glNormal3fv(v);}
void WINAPI glNormal3i(GLint x,GLint y,GLint z){if(real_glNormal3i)real_glNormal3i(x,y,z);}
void WINAPI glNormal3iv(const GLint* v){if(real_glNormal3iv)real_glNormal3iv(v);}
void WINAPI glNormal3s(GLshort x,GLshort y,GLshort z){if(real_glNormal3s)real_glNormal3s(x,y,z);}
void WINAPI glNormal3sv(const GLshort* v){if(real_glNormal3sv)real_glNormal3sv(v);}
void WINAPI glNormalPointer(GLenum t,GLsizei s,const void* p){if(real_glNormalPointer)real_glNormalPointer(t,s,p);}
void WINAPI glOrtho(GLdouble l,GLdouble r,GLdouble b,GLdouble t,GLdouble n,GLdouble f){if(real_glOrtho)real_glOrtho(l,r,b,t,n,f);}
void WINAPI glPassThrough(GLfloat t){if(real_glPassThrough)real_glPassThrough(t);}
void WINAPI glPixelMapfv(GLenum m,GLsizei n,const GLfloat* v){if(real_glPixelMapfv)real_glPixelMapfv(m,n,v);}
void WINAPI glPixelMapuiv(GLenum m,GLsizei n,const GLuint* v){if(real_glPixelMapuiv)real_glPixelMapuiv(m,n,v);}
void WINAPI glPixelMapusv(GLenum m,GLsizei n,const GLushort* v){if(real_glPixelMapusv)real_glPixelMapusv(m,n,v);}
void WINAPI glPixelStoref(GLenum p,GLfloat v){if(real_glPixelStoref)real_glPixelStoref(p,v);}
void WINAPI glPixelStorei(GLenum p,GLint v){if(real_glPixelStorei)real_glPixelStorei(p,v);}
void WINAPI glPixelTransferf(GLenum p,GLfloat v){if(real_glPixelTransferf)real_glPixelTransferf(p,v);}
void WINAPI glPixelTransferi(GLenum p,GLint v){if(real_glPixelTransferi)real_glPixelTransferi(p,v);}
void WINAPI glPixelZoom(GLfloat x,GLfloat y){if(real_glPixelZoom)real_glPixelZoom(x,y);}
void WINAPI glPointSize(GLfloat s){if(real_glPointSize)real_glPointSize(s);}
void WINAPI glPolygonMode(GLenum f,GLenum m){if(real_glPolygonMode)real_glPolygonMode(f,m);}
void WINAPI glPolygonOffset(GLfloat f,GLfloat u){if(real_glPolygonOffset)real_glPolygonOffset(f,u);}
void WINAPI glPolygonStipple(const GLubyte* m){if(real_glPolygonStipple)real_glPolygonStipple(m);}
void WINAPI glPopAttrib(){if(real_glPopAttrib)real_glPopAttrib();}
void WINAPI glPopClientAttrib(){if(real_glPopClientAttrib)real_glPopClientAttrib();}
void WINAPI glPopMatrix(){if(real_glPopMatrix)real_glPopMatrix();}
void WINAPI glPopName(){if(real_glPopName)real_glPopName();}
void WINAPI glPrioritizeTextures(GLsizei n,const GLuint* t,const GLclampf* p){if(real_glPrioritizeTextures)real_glPrioritizeTextures(n,t,p);}
void WINAPI glPushAttrib(GLbitfield m){if(real_glPushAttrib)real_glPushAttrib(m);}
void WINAPI glPushClientAttrib(GLbitfield m){if(real_glPushClientAttrib)real_glPushClientAttrib(m);}
void WINAPI glPushMatrix(){if(real_glPushMatrix)real_glPushMatrix();}
void WINAPI glPushName(GLuint n){if(real_glPushName)real_glPushName(n);}
void WINAPI glRasterPos2d(GLdouble x,GLdouble y){if(real_glRasterPos2d)real_glRasterPos2d(x,y);}
void WINAPI glRasterPos2dv(const GLdouble* v){if(real_glRasterPos2dv)real_glRasterPos2dv(v);}
void WINAPI glRasterPos2f(GLfloat x,GLfloat y){if(real_glRasterPos2f)real_glRasterPos2f(x,y);}
void WINAPI glRasterPos2fv(const GLfloat* v){if(real_glRasterPos2fv)real_glRasterPos2fv(v);}
void WINAPI glRasterPos2i(GLint x,GLint y){if(real_glRasterPos2i)real_glRasterPos2i(x,y);}
void WINAPI glRasterPos2iv(const GLint* v){if(real_glRasterPos2iv)real_glRasterPos2iv(v);}
void WINAPI glRasterPos2s(GLshort x,GLshort y){if(real_glRasterPos2s)real_glRasterPos2s(x,y);}
void WINAPI glRasterPos2sv(const GLshort* v){if(real_glRasterPos2sv)real_glRasterPos2sv(v);}
void WINAPI glRasterPos3d(GLdouble x,GLdouble y,GLdouble z){if(real_glRasterPos3d)real_glRasterPos3d(x,y,z);}
void WINAPI glRasterPos3dv(const GLdouble* v){if(real_glRasterPos3dv)real_glRasterPos3dv(v);}
void WINAPI glRasterPos3f(GLfloat x,GLfloat y,GLfloat z){if(real_glRasterPos3f)real_glRasterPos3f(x,y,z);}
void WINAPI glRasterPos3fv(const GLfloat* v){if(real_glRasterPos3fv)real_glRasterPos3fv(v);}
void WINAPI glRasterPos3i(GLint x,GLint y,GLint z){if(real_glRasterPos3i)real_glRasterPos3i(x,y,z);}
void WINAPI glRasterPos3iv(const GLint* v){if(real_glRasterPos3iv)real_glRasterPos3iv(v);}
void WINAPI glRasterPos3s(GLshort x,GLshort y,GLshort z){if(real_glRasterPos3s)real_glRasterPos3s(x,y,z);}
void WINAPI glRasterPos3sv(const GLshort* v){if(real_glRasterPos3sv)real_glRasterPos3sv(v);}
void WINAPI glRasterPos4d(GLdouble x,GLdouble y,GLdouble z,GLdouble w){if(real_glRasterPos4d)real_glRasterPos4d(x,y,z,w);}
void WINAPI glRasterPos4dv(const GLdouble* v){if(real_glRasterPos4dv)real_glRasterPos4dv(v);}
void WINAPI glRasterPos4f(GLfloat x,GLfloat y,GLfloat z,GLfloat w){if(real_glRasterPos4f)real_glRasterPos4f(x,y,z,w);}
void WINAPI glRasterPos4fv(const GLfloat* v){if(real_glRasterPos4fv)real_glRasterPos4fv(v);}
void WINAPI glRasterPos4i(GLint x,GLint y,GLint z,GLint w){if(real_glRasterPos4i)real_glRasterPos4i(x,y,z,w);}
void WINAPI glRasterPos4iv(const GLint* v){if(real_glRasterPos4iv)real_glRasterPos4iv(v);}
void WINAPI glRasterPos4s(GLshort x,GLshort y,GLshort z,GLshort w){if(real_glRasterPos4s)real_glRasterPos4s(x,y,z,w);}
void WINAPI glRasterPos4sv(const GLshort* v){if(real_glRasterPos4sv)real_glRasterPos4sv(v);}
void WINAPI glReadBuffer(GLenum m){if(real_glReadBuffer)real_glReadBuffer(m);}
void WINAPI glReadPixels(GLint x,GLint y,GLsizei w,GLsizei h,GLenum f,GLenum t,void* p){if(real_glReadPixels)real_glReadPixels(x,y,w,h,f,t,p);}
void WINAPI glRectd(GLdouble x1,GLdouble y1,GLdouble x2,GLdouble y2){if(real_glRectd)real_glRectd(x1,y1,x2,y2);}
void WINAPI glRectdv(const GLdouble* v1,const GLdouble* v2){if(real_glRectdv)real_glRectdv(v1,v2);}
void WINAPI glRectf(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2){if(real_glRectf)real_glRectf(x1,y1,x2,y2);}
void WINAPI glRectfv(const GLfloat* v1,const GLfloat* v2){if(real_glRectfv)real_glRectfv(v1,v2);}
void WINAPI glRecti(GLint x1,GLint y1,GLint x2,GLint y2){if(real_glRecti)real_glRecti(x1,y1,x2,y2);}
void WINAPI glRectiv(const GLint* v1,const GLint* v2){if(real_glRectiv)real_glRectiv(v1,v2);}
void WINAPI glRects(GLshort x1,GLshort y1,GLshort x2,GLshort y2){if(real_glRects)real_glRects(x1,y1,x2,y2);}
void WINAPI glRectsv(const GLshort* v1,const GLshort* v2){if(real_glRectsv)real_glRectsv(v1,v2);}
GLint WINAPI glRenderMode(GLenum m){return real_glRenderMode?real_glRenderMode(m):0;}
void WINAPI glRotated(GLdouble a,GLdouble x,GLdouble y,GLdouble z){if(real_glRotated)real_glRotated(a,x,y,z);}
void WINAPI glRotatef(GLfloat a,GLfloat x,GLfloat y,GLfloat z){if(real_glRotatef)real_glRotatef(a,x,y,z);}
void WINAPI glScaled(GLdouble x,GLdouble y,GLdouble z){if(real_glScaled)real_glScaled(x,y,z);}
void WINAPI glScalef(GLfloat x,GLfloat y,GLfloat z){if(real_glScalef)real_glScalef(x,y,z);}
void WINAPI glScissor(GLint x,GLint y,GLsizei w,GLsizei h){if(real_glScissor)real_glScissor(x,y,w,h);}
void WINAPI glSelectBuffer(GLsizei s,GLuint* b){if(real_glSelectBuffer)real_glSelectBuffer(s,b);}
void WINAPI glShadeModel(GLenum m){if(real_glShadeModel)real_glShadeModel(m);}
void WINAPI glStencilFunc(GLenum f,GLint r,GLuint m){if(real_glStencilFunc)real_glStencilFunc(f,r,m);}
void WINAPI glStencilMask(GLuint m){if(real_glStencilMask)real_glStencilMask(m);}
void WINAPI glStencilOp(GLenum f,GLenum z,GLenum p){if(real_glStencilOp)real_glStencilOp(f,z,p);}
void WINAPI glTexCoord1d(GLdouble s){if(real_glTexCoord1d)real_glTexCoord1d(s);}
void WINAPI glTexCoord1dv(const GLdouble* v){if(real_glTexCoord1dv)real_glTexCoord1dv(v);}
void WINAPI glTexCoord1f(GLfloat s){if(real_glTexCoord1f)real_glTexCoord1f(s);}
void WINAPI glTexCoord1fv(const GLfloat* v){if(real_glTexCoord1fv)real_glTexCoord1fv(v);}
void WINAPI glTexCoord1i(GLint s){if(real_glTexCoord1i)real_glTexCoord1i(s);}
void WINAPI glTexCoord1iv(const GLint* v){if(real_glTexCoord1iv)real_glTexCoord1iv(v);}
void WINAPI glTexCoord1s(GLshort s){if(real_glTexCoord1s)real_glTexCoord1s(s);}
void WINAPI glTexCoord1sv(const GLshort* v){if(real_glTexCoord1sv)real_glTexCoord1sv(v);}
void WINAPI glTexCoord2d(GLdouble s,GLdouble t){if(real_glTexCoord2d)real_glTexCoord2d(s,t);}
void WINAPI glTexCoord2dv(const GLdouble* v){if(real_glTexCoord2dv)real_glTexCoord2dv(v);}
void WINAPI glTexCoord2f(GLfloat s,GLfloat t){if(real_glTexCoord2f)real_glTexCoord2f(s,t);}
void WINAPI glTexCoord2fv(const GLfloat* v){if(real_glTexCoord2fv)real_glTexCoord2fv(v);}
void WINAPI glTexCoord2i(GLint s,GLint t){if(real_glTexCoord2i)real_glTexCoord2i(s,t);}
void WINAPI glTexCoord2iv(const GLint* v){if(real_glTexCoord2iv)real_glTexCoord2iv(v);}
void WINAPI glTexCoord2s(GLshort s,GLshort t){if(real_glTexCoord2s)real_glTexCoord2s(s,t);}
void WINAPI glTexCoord2sv(const GLshort* v){if(real_glTexCoord2sv)real_glTexCoord2sv(v);}
void WINAPI glTexCoord3d(GLdouble s,GLdouble t,GLdouble r){if(real_glTexCoord3d)real_glTexCoord3d(s,t,r);}
void WINAPI glTexCoord3dv(const GLdouble* v){if(real_glTexCoord3dv)real_glTexCoord3dv(v);}
void WINAPI glTexCoord3f(GLfloat s,GLfloat t,GLfloat r){if(real_glTexCoord3f)real_glTexCoord3f(s,t,r);}
void WINAPI glTexCoord3fv(const GLfloat* v){if(real_glTexCoord3fv)real_glTexCoord3fv(v);}
void WINAPI glTexCoord3i(GLint s,GLint t,GLint r){if(real_glTexCoord3i)real_glTexCoord3i(s,t,r);}
void WINAPI glTexCoord3iv(const GLint* v){if(real_glTexCoord3iv)real_glTexCoord3iv(v);}
void WINAPI glTexCoord3s(GLshort s,GLshort t,GLshort r){if(real_glTexCoord3s)real_glTexCoord3s(s,t,r);}
void WINAPI glTexCoord3sv(const GLshort* v){if(real_glTexCoord3sv)real_glTexCoord3sv(v);}
void WINAPI glTexCoord4d(GLdouble s,GLdouble t,GLdouble r,GLdouble q){if(real_glTexCoord4d)real_glTexCoord4d(s,t,r,q);}
void WINAPI glTexCoord4dv(const GLdouble* v){if(real_glTexCoord4dv)real_glTexCoord4dv(v);}
void WINAPI glTexCoord4f(GLfloat s,GLfloat t,GLfloat r,GLfloat q){if(real_glTexCoord4f)real_glTexCoord4f(s,t,r,q);}
void WINAPI glTexCoord4fv(const GLfloat* v){if(real_glTexCoord4fv)real_glTexCoord4fv(v);}
void WINAPI glTexCoord4i(GLint s,GLint t,GLint r,GLint q){if(real_glTexCoord4i)real_glTexCoord4i(s,t,r,q);}
void WINAPI glTexCoord4iv(const GLint* v){if(real_glTexCoord4iv)real_glTexCoord4iv(v);}
void WINAPI glTexCoord4s(GLshort s,GLshort t,GLshort r,GLshort q){if(real_glTexCoord4s)real_glTexCoord4s(s,t,r,q);}
void WINAPI glTexCoord4sv(const GLshort* v){if(real_glTexCoord4sv)real_glTexCoord4sv(v);}
void WINAPI glTexCoordPointer(GLint s,GLenum t,GLsizei st,const void* p){if(real_glTexCoordPointer)real_glTexCoordPointer(s,t,st,p);}
void WINAPI glTexEnvf(GLenum t,GLenum p,GLfloat v){if(real_glTexEnvf)real_glTexEnvf(t,p,v);}
void WINAPI glTexEnvfv(GLenum t,GLenum p,const GLfloat* v){if(real_glTexEnvfv)real_glTexEnvfv(t,p,v);}
void WINAPI glTexEnvi(GLenum t,GLenum p,GLint v){if(real_glTexEnvi)real_glTexEnvi(t,p,v);}
void WINAPI glTexEnviv(GLenum t,GLenum p,const GLint* v){if(real_glTexEnviv)real_glTexEnviv(t,p,v);}
void WINAPI glTexGend(GLenum c,GLenum p,GLdouble v){if(real_glTexGend)real_glTexGend(c,p,v);}
void WINAPI glTexGendv(GLenum c,GLenum p,const GLdouble* v){if(real_glTexGendv)real_glTexGendv(c,p,v);}
void WINAPI glTexGenf(GLenum c,GLenum p,GLfloat v){if(real_glTexGenf)real_glTexGenf(c,p,v);}
void WINAPI glTexGenfv(GLenum c,GLenum p,const GLfloat* v){if(real_glTexGenfv)real_glTexGenfv(c,p,v);}
void WINAPI glTexGeni(GLenum c,GLenum p,GLint v){if(real_glTexGeni)real_glTexGeni(c,p,v);}
void WINAPI glTexGeniv(GLenum c,GLenum p,const GLint* v){if(real_glTexGeniv)real_glTexGeniv(c,p,v);}
void WINAPI glTexImage1D(GLenum t,GLint l,GLint i,GLsizei w,GLint b,GLenum f,GLenum ty,const void* p){if(real_glTexImage1D)real_glTexImage1D(t,l,i,w,b,f,ty,p);}
void WINAPI glTexImage2D(GLenum t,GLint l,GLint i,GLsizei w,GLsizei h,GLint b,GLenum f,GLenum ty,const void* p){if(real_glTexImage2D)real_glTexImage2D(t,l,i,w,h,b,f,ty,p);}
void WINAPI glTexImage3D(GLenum t,GLint l,GLint i,GLsizei w,GLsizei h,GLsizei d,GLint b,GLenum f,GLenum ty,const void* p){if(real_glTexImage3D)real_glTexImage3D(t,l,i,w,h,d,b,f,ty,p);}
void WINAPI glTexParameterf(GLenum t,GLenum p,GLfloat v){if(real_glTexParameterf)real_glTexParameterf(t,p,v);}
void WINAPI glTexParameterfv(GLenum t,GLenum p,const GLfloat* v){if(real_glTexParameterfv)real_glTexParameterfv(t,p,v);}
void WINAPI glTexParameteri(GLenum t,GLenum p,GLint v){if(real_glTexParameteri)real_glTexParameteri(t,p,v);}
void WINAPI glTexParameteriv(GLenum t,GLenum p,const GLint* v){if(real_glTexParameteriv)real_glTexParameteriv(t,p,v);}
void WINAPI glTexSubImage1D(GLenum t,GLint l,GLint x,GLsizei w,GLenum f,GLenum ty,const void* p){if(real_glTexSubImage1D)real_glTexSubImage1D(t,l,x,w,f,ty,p);}
void WINAPI glTexSubImage2D(GLenum t,GLint l,GLint x,GLint y,GLsizei w,GLsizei h,GLenum f,GLenum ty,const void* p){if(real_glTexSubImage2D)real_glTexSubImage2D(t,l,x,y,w,h,f,ty,p);}
void WINAPI glTexSubImage3D(GLenum t,GLint l,GLint x,GLint y,GLint z,GLsizei w,GLsizei h,GLsizei d,GLenum f,GLenum ty,const void* p){if(real_glTexSubImage3D)real_glTexSubImage3D(t,l,x,y,z,w,h,d,f,ty,p);}
void WINAPI glTranslated(GLdouble x,GLdouble y,GLdouble z){if(real_glTranslated)real_glTranslated(x,y,z);}
void WINAPI glTranslatef(GLfloat x,GLfloat y,GLfloat z){if(real_glTranslatef)real_glTranslatef(x,y,z);}
void WINAPI glVertex2d(GLdouble x,GLdouble y){if(real_glVertex2d)real_glVertex2d(x,y);}
void WINAPI glVertex2dv(const GLdouble* v){if(real_glVertex2dv)real_glVertex2dv(v);}
void WINAPI glVertex2f(GLfloat x,GLfloat y){if(real_glVertex2f)real_glVertex2f(x,y);}
void WINAPI glVertex2fv(const GLfloat* v){if(real_glVertex2fv)real_glVertex2fv(v);}
void WINAPI glVertex2i(GLint x,GLint y){if(real_glVertex2i)real_glVertex2i(x,y);}
void WINAPI glVertex2iv(const GLint* v){if(real_glVertex2iv)real_glVertex2iv(v);}
void WINAPI glVertex2s(GLshort x,GLshort y){if(real_glVertex2s)real_glVertex2s(x,y);}
void WINAPI glVertex2sv(const GLshort* v){if(real_glVertex2sv)real_glVertex2sv(v);}
void WINAPI glVertex3d(GLdouble x,GLdouble y,GLdouble z){if(real_glVertex3d)real_glVertex3d(x,y,z);}
void WINAPI glVertex3dv(const GLdouble* v){if(real_glVertex3dv)real_glVertex3dv(v);}
void WINAPI glVertex3f(GLfloat x,GLfloat y,GLfloat z){if(real_glVertex3f)real_glVertex3f(x,y,z);}
void WINAPI glVertex3fv(const GLfloat* v){if(real_glVertex3fv)real_glVertex3fv(v);}
void WINAPI glVertex3i(GLint x,GLint y,GLint z){if(real_glVertex3i)real_glVertex3i(x,y,z);}
void WINAPI glVertex3iv(const GLint* v){if(real_glVertex3iv)real_glVertex3iv(v);}
void WINAPI glVertex3s(GLshort x,GLshort y,GLshort z){if(real_glVertex3s)real_glVertex3s(x,y,z);}
void WINAPI glVertex3sv(const GLshort* v){if(real_glVertex3sv)real_glVertex3sv(v);}
void WINAPI glVertex4d(GLdouble x,GLdouble y,GLdouble z,GLdouble w){if(real_glVertex4d)real_glVertex4d(x,y,z,w);}
void WINAPI glVertex4dv(const GLdouble* v){if(real_glVertex4dv)real_glVertex4dv(v);}
void WINAPI glVertex4f(GLfloat x,GLfloat y,GLfloat z,GLfloat w){if(real_glVertex4f)real_glVertex4f(x,y,z,w);}
void WINAPI glVertex4fv(const GLfloat* v){if(real_glVertex4fv)real_glVertex4fv(v);}
void WINAPI glVertex4i(GLint x,GLint y,GLint z,GLint w){if(real_glVertex4i)real_glVertex4i(x,y,z,w);}
void WINAPI glVertex4iv(const GLint* v){if(real_glVertex4iv)real_glVertex4iv(v);}
void WINAPI glVertex4s(GLshort x,GLshort y,GLshort z,GLshort w){if(real_glVertex4s)real_glVertex4s(x,y,z,w);}
void WINAPI glVertex4sv(const GLshort* v){if(real_glVertex4sv)real_glVertex4sv(v);}
void WINAPI glVertexPointer(GLint s,GLenum t,GLsizei st,const void* p){if(real_glVertexPointer)real_glVertexPointer(s,t,st,p);}
void WINAPI glViewport(GLint x,GLint y,GLsizei w,GLsizei h){if(real_glViewport)real_glViewport(x,y,w,h);}

// WGL
HGLRC WINAPI wglCreateContext(HDC h){return real_wglCreateContext?real_wglCreateContext(h):nullptr;}
BOOL WINAPI wglDeleteContext(HGLRC c){return real_wglDeleteContext?real_wglDeleteContext(c):FALSE;}
HGLRC WINAPI wglGetCurrentContext(){return real_wglGetCurrentContext?real_wglGetCurrentContext():nullptr;}
HDC WINAPI wglGetCurrentDC(){return real_wglGetCurrentDC?real_wglGetCurrentDC():nullptr;}
BOOL WINAPI wglMakeCurrent(HDC h,HGLRC c){return real_wglMakeCurrent?real_wglMakeCurrent(h,c):FALSE;}
BOOL WINAPI wglShareLists(HGLRC a,HGLRC b){return real_wglShareLists?real_wglShareLists(a,b):FALSE;}
HGLRC WINAPI wglCreateLayerContext(HDC h,int l){return real_wglCreateLayerContext?real_wglCreateLayerContext(h,l):nullptr;}
BOOL WINAPI wglCopyContext(HGLRC s,HGLRC d,UINT m){return real_wglCopyContext?real_wglCopyContext(s,d,m):FALSE;}
int WINAPI wglChoosePixelFormat(HDC h,const PIXELFORMATDESCRIPTOR* p){return real_wglChoosePixelFormat?real_wglChoosePixelFormat(h,p):0;}
BOOL WINAPI wglDescribeLayerPlane(HDC h,int pf,int l,UINT n,LPLAYERPLANEDESCRIPTOR d){return real_wglDescribeLayerPlane?real_wglDescribeLayerPlane(h,pf,l,n,d):FALSE;}
int WINAPI wglDescribePixelFormat(HDC h,int pf,UINT n,LPPIXELFORMATDESCRIPTOR d){return real_wglDescribePixelFormat?real_wglDescribePixelFormat(h,pf,n,d):0;}
HANDLE WINAPI wglGetDefaultProcAddress(LPCSTR n){return real_wglGetDefaultProcAddress?real_wglGetDefaultProcAddress(n):nullptr;}
int WINAPI wglGetLayerPaletteEntries(HDC h,int l,int s,int n,COLORREF* c){return real_wglGetLayerPaletteEntries?real_wglGetLayerPaletteEntries(h,l,s,n,c):0;}
int WINAPI wglGetPixelFormat(HDC h){return real_wglGetPixelFormat?real_wglGetPixelFormat(h):0;}
BOOL WINAPI wglRealizeLayerPalette(HDC h,int l,BOOL r){return real_wglRealizeLayerPalette?real_wglRealizeLayerPalette(h,l,r):FALSE;}
int WINAPI wglSetLayerPaletteEntries(HDC h,int l,int s,int n,const COLORREF* c){return real_wglSetLayerPaletteEntries?real_wglSetLayerPaletteEntries(h,l,s,n,c):0;}
BOOL WINAPI wglSetPixelFormat(HDC h,int pf,const PIXELFORMATDESCRIPTOR* p){return real_wglSetPixelFormat?real_wglSetPixelFormat(h,pf,p):FALSE;}
BOOL WINAPI wglSwapLayerBuffers(HDC h,UINT f){return real_wglSwapLayerBuffers?real_wglSwapLayerBuffers(h,f):FALSE;}
DWORD WINAPI wglSwapMultipleBuffers(UINT n,const WGLSWAP* s){return real_wglSwapMultipleBuffers?real_wglSwapMultipleBuffers(n,s):0;}
BOOL WINAPI wglUseFontBitmapsA(HDC h,DWORD f,DWORD c,DWORD l){return real_wglUseFontBitmapsA?real_wglUseFontBitmapsA(h,f,c,l):FALSE;}
BOOL WINAPI wglUseFontBitmapsW(HDC h,DWORD f,DWORD c,DWORD l){return real_wglUseFontBitmapsW?real_wglUseFontBitmapsW(h,f,c,l):FALSE;}
BOOL WINAPI wglUseFontOutlinesA(HDC h,DWORD f,DWORD c,DWORD l,FLOAT d,FLOAT e,int fmt,LPGLYPHMETRICSFLOAT g){return real_wglUseFontOutlinesA?real_wglUseFontOutlinesA(h,f,c,l,d,e,fmt,g):FALSE;}
BOOL WINAPI wglUseFontOutlinesW(HDC h,DWORD f,DWORD c,DWORD l,FLOAT d,FLOAT e,int fmt,LPGLYPHMETRICSFLOAT g){return real_wglUseFontOutlinesW?real_wglUseFontOutlinesW(h,f,c,l,d,e,fmt,g):FALSE;}

// GDI
int WINAPI ChoosePixelFormat(HDC h,const PIXELFORMATDESCRIPTOR* p){return real_ChoosePixelFormat?real_ChoosePixelFormat(h,p):0;}
int WINAPI DescribePixelFormat(HDC h,int pf,UINT n,LPPIXELFORMATDESCRIPTOR d){return real_DescribePixelFormat?real_DescribePixelFormat(h,pf,n,d):0;}
int WINAPI GetPixelFormat(HDC h){return real_GetPixelFormat?real_GetPixelFormat(h):0;}
BOOL WINAPI SetPixelFormat(HDC h,int pf,const PIXELFORMATDESCRIPTOR* p){return real_SetPixelFormat?real_SetPixelFormat(h,pf,p):FALSE;}

} // extern "C"