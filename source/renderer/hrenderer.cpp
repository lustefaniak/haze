/***************************************************************************
 *   Copyright (C) 2007 by Łukasz Stefaniak   *
 *   lustefaniak@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "../Haze.h"
#include "hrenderer.h" // class's header file

template<> HRenderer* Singleton<HRenderer>::ms_Singleton = 0;

// class constructor
HRenderer::HRenderer() {
    // insert your code here
    m_uiNormalizationCubeMap=0;

}

// class destructor
HRenderer::~HRenderer() {
    // insert your code here
}

bool HRenderer::InitShaders() {
    ShaderManager=new glShaderManager();
    assert(ShaderManager);

    glShader* shader = ShaderManager->loadfromFile("shaders/test.vert","shaders/test.frag");
    if (shader) m_Shaders["basic"]=shader;
    else cout << "Error Loading, compiling or linking shader\n";


    return shader!=NULL;
}



int CheckGLError(char *file, int line) {
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR) {
        const GLubyte* sError = gluErrorString(glErr);

        if (sError)
            cout << "GL Error #" << glErr << "(" << gluErrorString(glErr) << ") " << " in File " << file << " at line: " << line << endl;
        else
            cout << "GL Error #" << glErr << " (no message available)" << " in File " << file << " at line: " << line << endl;

        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}
#define CHECK_GL_ERROR() CheckGLError(__FILE__, __LINE__)
// renderuje list�polygon�, materia musi by�ten sam dla wszystkich
void HRenderer::Render ( HGPoly * polylist,HLight * light ) {

    HMaterial * Material=NULL;
    if ( !polylist ) return;
    Material=HMaterialManager::GetSingleton().GetMaterial ( polylist->p->material );
    if ( !Material ) return;
    int i;
    int j;
    int lightmappass=-1;
    int LastGLPrimitive=0;
    int GLPrimitive=0;
    glColor4f ( 1,1,1,1 );






    glShader * shader=m_Shaders["basic"];
    assert(shader);
    shader->begin();

    HGPoly * Current=polylist;
    glActiveTextureARB ( GL_TEXTURE0_ARB );
    HTextureManager::GetSingleton().Bind ( Material->m_mpPasses[0].textureid );
    shader->setUniform1i("Sampler0",0);

    glActiveTextureARB ( GL_TEXTURE1_ARB );
    HTextureManager::GetSingleton().Bind ( Material->m_mpPasses[0].textureid );
    shader->setUniform1i("Sampler1",1);

    Current->m_Lightmap->Upload ( GL_TEXTURE2_ARB );
    shader->setUniform1i("Lightmap",2);


    char buff[10];

    for (int c=0, i=0;i<Material->m_iNumPasses;i++ ) {
        glActiveTextureARB ( GL_TEXTURE0_ARB+i );

        sprintf(buff,"Sampler%d\0",c);

        if ( Material->m_mpPasses[i].passmode==PM_LIGHTMAP ) {
            lightmappass=i;
        } else {
            c++;
            HTextureManager::GetSingleton().Bind ( Material->m_mpPasses[i].textureid );

            shader->setUniform1i(buff,i);

        }
    }

    sprintf(buff,"Sampler%d\0",lightmappass);

    for ( Current=polylist;Current;Current=Current->Rendering_Next ) {
        if ( Current->m_Verts.num==3 ) GLPrimitive=GL_TRIANGLES;
        if ( Current->m_Verts.num==4 ) GLPrimitive=GL_QUADS;
        if ( Current->m_Verts.num>4 ) GLPrimitive=GL_POLYGON;

        glActiveTextureARB(GL_TEXTURE0_ARB+lightmappass);
        if ( Current->m_Lightmap ) {
            Current->m_Lightmap->Upload ( GL_TEXTURE0_ARB+lightmappass );


            shader->setUniform1i("Lightmap",lightmappass);

        } else {
            glActiveTextureARB ( GL_TEXTURE0_ARB+lightmappass );

        }
        glActiveTexture ( GL_TEXTURE0_ARB );
        glBegin ( GLPrimitive );


        glNormal3fv ( Current->p->n );
        for ( j=0;j<Current->m_Verts.num;j++ ) {
            for ( i=0;i<Material->m_iNumPasses;i++ ) {
                if ( Material->m_mpPasses[i].texgenmode==TGM_NORMAL )
                    glMultiTexCoord2fv ( GL_TEXTURE0_ARB+i,Current->m_Verts[j].tex1 );
            }

            if ( lightmappass!=-1 ) {
                glMultiTexCoord2fv ( GL_TEXTURE0_ARB+lightmappass,Current->m_Verts[j].tex2 );
            }

            glVertex3fv ( Current->m_Verts[j].pos );
        }

        glEnd();
    }

    shader->end();

    for (int i=0;i<5;i++) {
        glActiveTexture ( GL_TEXTURE0_ARB+i );
        glDisable ( GL_TEXTURE_2D );
        glDisable ( GL_TEXTURE_1D );
    }

}



//TO JEST STARA IMPLEMENTACJA RENDEROWANIA:
/*    HGPoly* Current=NULL;
    HMaterial * Material=NULL;
    if ( !polylist ) return;
    Material=HMaterialManager::GetSingleton().GetMaterial ( polylist->p->material );
    if ( !Material ) return;
    int i;
    int j;
    int lightmappass=-1;
    int LastGLPrimitive=0;
    int GLPrimitive=0;
    glColor4f ( 1,1,1,1 );
    debug("setting material...\n");
    debug("material has %d passes\n",Material->m_iNumPasses);
    fflush(stdout);

    if (Material->m_iNumPasses==2&&Material->m_mpPasses[0].passmode==PM_NORMAL&&Material->m_mpPasses[0].passmode==PM_LIGHTMAP) {
        for (Current=polylist;Current;Current=Current->Rendering_Next) {
            if (Current->m_Verts.num==3) GLPrimitive=GL_TRIANGLES;
            if (Current->m_Verts.num==4) GLPrimitive=GL_QUADS;
            if (Current->m_Verts.num>4) GLPrimitive=GL_POLYGON;
            if (LastGLPrimitive!=GLPrimitive||LastGLPrimitive==GL_POLYGON) {
                glEnd();
                glBegin(GLPrimitive);
            } else {
                glBegin(GLPrimitive);
            }
            if (lightmappass!=-1) {
                glActiveTextureARB(GL_TEXTURE0_ARB+lightmappass);
                if (Current->m_Lightmap) Current->m_Lightmap->Upload(GL_TEXTURE0_ARB+lightmappass);
            }
            glNormal3fv(Current->p->n);
            for (j=0;j<Current->m_Verts.num;j++) {

                glMultiTexCoord2fv(GL_TEXTURE0_ARB,Current->m_Verts[j].tex1);
                glMultiTexCoord2fv(GL_TEXTURE1_ARB,Current->m_Verts[j].tex2);


                glVertex3fv(Current->m_Verts[j].pos);
            }


        }
        glEnd();
        return;
    }

    glActiveTexture ( GL_TEXTURE0_ARB );
    glDisable ( GL_TEXTURE_2D );
    glDisable ( GL_TEXTURE_1D );
    glActiveTexture ( GL_TEXTURE1_ARB );
    glDisable ( GL_TEXTURE_2D );
    glDisable ( GL_TEXTURE_1D );
    glActiveTexture ( GL_TEXTURE2_ARB );
    glDisable ( GL_TEXTURE_2D );
    glDisable ( GL_TEXTURE_1D );
    glActiveTexture ( GL_TEXTURE3_ARB );
    glDisable ( GL_TEXTURE_2D );
    glDisable ( GL_TEXTURE_1D );
    glActiveTexture ( GL_TEXTURE4_ARB );
    glDisable ( GL_TEXTURE_2D );
    glDisable ( GL_TEXTURE_1D );
    glActiveTexture ( GL_TEXTURE5_ARB );
    glDisable ( GL_TEXTURE_2D );
    glDisable ( GL_TEXTURE_1D );

    if ( Material->m_iNumPasses>0&&Material->m_mpPasses[0].passmode==PM_BUMPMAP ) {
        matrix_t inverseModelMatrix;
        vec3_t objectLightPosition;
        inverseModelMatrix=HEngineCore::GetSingleton().m_pCamera->m_mMatrix;
        inverseModelMatrix.Inverse ( HEngineCore::GetSingleton().m_pCamera->m_mMatrix );
        if ( light ) objectLightPosition=light->m_Position*inverseModelMatrix;
        glActiveTextureARB ( GL_TEXTURE0_ARB );
        HTextureManager::GetSingleton().Bind ( Material->m_mpPasses[0].textureid );
//    HTextureManager::GetSingleton().Bind(m_WorldBrushes[i]->m_Polys[j]->p->bumpmap);
//      HTextureManager::GetSingleton().Bind(HTextureManager::GetSingleton().Load("normalmap"));
        glEnable ( GL_TEXTURE_2D );

        //Bind normalisation cube map to texture unit 1
        glActiveTextureARB ( GL_TEXTURE1_ARB );
        if ( !m_uiNormalizationCubeMap ) GenerateNormalizationCubeMap();
        glBindTexture ( GL_TEXTURE_CUBE_MAP_ARB, m_uiNormalizationCubeMap );
        glEnable ( GL_TEXTURE_CUBE_MAP_ARB );
        glActiveTextureARB ( GL_TEXTURE0_ARB );

        //Set up texture environment to do (tex0 dot tex1)*color
        glTexEnvi ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB );
        glTexEnvi ( GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_TEXTURE );
        glTexEnvi ( GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_REPLACE );

        glActiveTextureARB ( GL_TEXTURE1_ARB );

        glTexEnvi ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB );
        glTexEnvi ( GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_TEXTURE );
        glTexEnvi ( GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_DOT3_RGB_ARB );
        glTexEnvi ( GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_PREVIOUS_ARB );

        glActiveTextureARB ( GL_TEXTURE0_ARB );
        for ( Current=polylist;Current;Current=Current->Rendering_Next ) {
            if ( Current->m_Verts.num==3 ) glBegin ( GL_TRIANGLES );
            if ( Current->m_Verts.num==4 ) glBegin ( GL_QUADS );
            if ( Current->m_Verts.num>4 ) glBegin ( GL_POLYGON );
            glNormal3fv ( Current->p->n );
            int k;
            for ( k=0;k<Current->m_Verts.num;k++ ) {

                glMultiTexCoord2fvARB ( GL_TEXTURE0_ARB,Current->m_Verts[k].tex1 );
                float s;
                float t;
                float r;
                vec3_t tmp;
                tmp=objectLightPosition-Current->m_Verts[k].pos;
                tmp.Normalize();
                s=Current->stangent.Dot ( tmp );
                t=Current->ttangent.Dot ( tmp );
                r=Current->p->n.Dot ( tmp );
                glMultiTexCoord3fARB ( GL_TEXTURE1_ARB,s,t,r );
                glMultiTexCoord2fARB ( GL_TEXTURE2_ARB,Current->m_Verts[k].tex1[0],Current->m_Verts[k].tex1[1] );
                glMultiTexCoord2fARB ( GL_TEXTURE3_ARB,Current->m_Verts[k].tex2[0],Current->m_Verts[k].tex2[1] );
                glVertex3fv ( Current->m_Verts[k].pos );
            }
            glEnd();
        }
        //Disable textures
        glDisable ( GL_TEXTURE_2D );

        glActiveTextureARB ( GL_TEXTURE1_ARB );
        glDisable ( GL_TEXTURE_CUBE_MAP_ARB );
        glActiveTextureARB ( GL_TEXTURE0_ARB );

        //Return to standard modulate texenv
        glTexEnvi ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
        glBlendFunc ( GL_DST_COLOR, GL_ZERO );
        glEnable ( GL_BLEND );
    }





    for ( i=0;i<Material->m_iNumPasses;i++ ) {
//  debug("pass%d is a ",i);
//  fflush(stdout);
        if ( Material->m_mpPasses[i].passmode==PM_BUMPMAP ) {
//  Material->m_mpPasses[i].passmode==PM_NONE;
//  debug("bumpmap must be first pass!!!\n");
//  debug("Bumpmapping unsupported now!!!\n");
//  fflush(stdout);
            continue;
        } else if ( Material->m_mpPasses[i].passmode==PM_LIGHTMAP ) {
            glActiveTextureARB ( GL_TEXTURE0_ARB+i );
            glEnable ( GL_TEXTURE_2D );
//  glEnable(GL_BLEND);
//  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            lightmappass=i;
//  debug("lightmappass\n");
//  fflush(stdout);
        } else if ( Material->m_mpPasses[i].passmode==PM_NORMAL ) {
//  debug("normalpass\n");
//  fflush(stdout);
            glActiveTextureARB ( GL_TEXTURE0_ARB+i );
            glEnable ( GL_TEXTURE_2D );
            HTextureManager::GetSingleton().Bind ( Material->m_mpPasses[i].textureid );
            if ( i==0 ) glTexEnvi ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
            else glTexEnvi ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
            if ( Material->m_mpPasses[i].texgenmode==TGM_ENVIRONMENT ) {
                // set texture generation mode to sphere mapping
                glTexGeni ( GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP );
                glTexGeni ( GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP );

                // switch on automatic texture coord generation
                glEnable ( GL_TEXTURE_GEN_S );
                glEnable ( GL_TEXTURE_GEN_T );

            }
        } else if ( Material->m_mpPasses[i].passmode==PM_GLOW ) {
//  debug("glowpass\n");
//  fflush(stdout);
            glActiveTextureARB ( GL_TEXTURE0_ARB+i );
            glEnable ( GL_TEXTURE_2D );
            glEnable ( GL_BLEND );
//  glBlendFunc(GL_SRC_ALPHA, GL_ONE);

            glBlendFunc ( GL_ONE, GL_ONE );
            HTextureManager::GetSingleton().Bind ( Material->m_mpPasses[i].textureid );
        } else {
//  debug("unsupportedpadd\n");
//  fflush(stdout);

        }

    }
    debug("rendering polys..\n");
    fflush ( stdout );
    for ( Current=polylist;Current;Current=Current->Rendering_Next ) {
        if ( Current->m_Verts.num==3 ) GLPrimitive=GL_TRIANGLES;
        if ( Current->m_Verts.num==4 ) GLPrimitive=GL_QUADS;
        if ( Current->m_Verts.num>4 ) GLPrimitive=GL_POLYGON;
        if ( LastGLPrimitive!=GLPrimitive||LastGLPrimitive==GL_POLYGON||lightmappass!=-1 ) {
            glEnd();
            //glActiveTextureARB(GL_TEXTURE0_ARB+lightmappass);
            if ( Current->m_Lightmap ) {
                Current->m_Lightmap->Upload ( GL_TEXTURE0_ARB+lightmappass );
            } else {
                glActiveTextureARB ( GL_TEXTURE0_ARB+lightmappass );
                glDisable ( GL_TEXTURE_2D );
            }

            glBegin ( GLPrimitive );
        } else {
            glBegin ( GLPrimitive );
        }


        glNormal3fv ( Current->p->n );
        for ( j=0;j<Current->m_Verts.num;j++ ) {
            for ( i=0;i<Material->m_iNumPasses;i++ ) {
                if ( Material->m_mpPasses[i].texgenmode==TGM_NORMAL )
                    glMultiTexCoord2fv ( GL_TEXTURE0_ARB+i,Current->m_Verts[j].tex1 );
            }


            if ( lightmappass!=-1 ) {
                glMultiTexCoord2fv ( GL_TEXTURE0_ARB+lightmappass,Current->m_Verts[j].tex2 );
            }

            glVertex3fv ( Current->m_Verts[j].pos );
        }


    }
    glEnd();
    debug("disablig state");
    fflush(stdout);

    for ( i=0;i<Material->m_iNumPasses;i++ ) {
        if ( Material->m_mpPasses[i].passmode==PM_BUMPMAP ) {}
        else if ( Material->m_mpPasses[i].passmode==PM_LIGHTMAP ) {
            glActiveTextureARB ( GL_TEXTURE0_ARB+i );
            glDisable ( GL_TEXTURE_2D );
            glDisable ( GL_BLEND );
            lightmappass=-1;
        } else if ( Material->m_mpPasses[i].passmode==PM_NORMAL ) {
            glActiveTextureARB ( GL_TEXTURE0_ARB+i );
            glDisable ( GL_TEXTURE_2D );
            if ( Material->m_mpPasses[i].texgenmode==TGM_ENVIRONMENT ) {
                // switch on automatic texture coord generation
                glDisable ( GL_TEXTURE_GEN_S );
                glDisable ( GL_TEXTURE_GEN_T );

            }
        } else if ( Material->m_mpPasses[i].passmode==PM_GLOW ) {
            glActiveTextureARB ( GL_TEXTURE0_ARB+i );
            glDisable ( GL_TEXTURE_2D );
            glDisable ( GL_BLEND );
            glBlendFunc ( GL_SRC_ALPHA, GL_ONE );
            HTextureManager::GetSingleton().Bind ( Material->m_mpPasses[i].textureid );
        } else {}
    }

    if ( Material->m_iNumPasses>0&&Material->m_mpPasses[0].passmode==PM_BUMPMAP ) {
        glDisable ( GL_BLEND );
        glBlendFunc ( GL_SRC_ALPHA, GL_ONE );
    }
    debug("render done");
}*/




// generuje takie co
int HRenderer::GenerateNormalizationCubeMap() {
    /* TODO (#1#): Implement HWorld::GenerateNormalizationCubeMap() */
    /* TODO (#1#): Implement HTextureNormalizationCubeMap::Load() */
    if ( glIsTexture ( m_uiNormalizationCubeMap ) ) {
        glDeleteTextures ( 1,&m_uiNormalizationCubeMap );
    }
    glGenTextures ( 1,&m_uiNormalizationCubeMap );
    glBindTexture ( GL_TEXTURE_CUBE_MAP_ARB,m_uiNormalizationCubeMap );
    unsigned char * data=new unsigned char[32*32*3];
    assert ( data );
//  debug("generating normalization_cube_map\n");
    //some useful variables
    int size=32;
    float offset=0.5f;
    float halfSize=16.0f;
    vec3_t tempVector;
    unsigned char * bytePtr;

    //positive x
    bytePtr=data;
    int j;
    for ( j=0; j<size; j++ ) {
        for ( int i=0; i<size; i++ ) {
            tempVector[0]=halfSize;
            tempVector[1]=- ( j+offset-halfSize );
            tempVector[2]=- ( i+offset-halfSize );

            tempVector.Normalize();
            tempVector.PackTo01();

            bytePtr[0]= ( unsigned char ) ( tempVector[0]*255 );
            bytePtr[1]= ( unsigned char ) ( tempVector[1]*255 );
            bytePtr[2]= ( unsigned char ) ( tempVector[2]*255 );

            bytePtr+=3;
        }
    }
    glTexImage2D (  GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
                    0, GL_RGBA8, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, data );

    //negative x
    bytePtr=data;

    for ( j=0; j<size; j++ ) {
        for ( int i=0; i<size; i++ ) {
            tempVector[0]= ( -halfSize );
            tempVector[1]= ( - ( j+offset-halfSize ) );
            tempVector[2]= ( ( i+offset-halfSize ) );

            tempVector.Normalize();
            tempVector.PackTo01();

            bytePtr[0]= ( unsigned char ) ( tempVector[0]*255 );
            bytePtr[1]= ( unsigned char ) ( tempVector[1]*255 );
            bytePtr[2]= ( unsigned char ) ( tempVector[2]*255 );

            bytePtr+=3;
        }
    }
    glTexImage2D (  GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
                    0, GL_RGBA8, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, data );

    //positive y
    bytePtr=data;

    for ( j=0; j<size; j++ ) {
        for ( int i=0; i<size; i++ ) {
            tempVector[0]= ( i+offset-halfSize );
            tempVector[1]= ( halfSize );
            tempVector[2]= ( ( j+offset-halfSize ) );

            tempVector.Normalize();
            tempVector.PackTo01();

            bytePtr[0]= ( unsigned char ) ( tempVector[0]*255 );
            bytePtr[1]= ( unsigned char ) ( tempVector[1]*255 );
            bytePtr[2]= ( unsigned char ) ( tempVector[2]*255 );

            bytePtr+=3;
        }
    }
    glTexImage2D (  GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
                    0, GL_RGBA8, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, data );

    //negative y
    bytePtr=data;

    for ( j=0; j<size; j++ ) {
        for ( int i=0; i<size; i++ ) {
            tempVector[0]= ( i+offset-halfSize );
            tempVector[1]= ( -halfSize );
            tempVector[2]= ( - ( j+offset-halfSize ) );

            tempVector.Normalize();
            tempVector.PackTo01();

            bytePtr[0]= ( unsigned char ) ( tempVector[0]*255 );
            bytePtr[1]= ( unsigned char ) ( tempVector[1]*255 );
            bytePtr[2]= ( unsigned char ) ( tempVector[2]*255 );

            bytePtr+=3;
        }
    }
    glTexImage2D (  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
                    0, GL_RGBA8, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, data );

    //positive z
    bytePtr=data;

    for ( j=0; j<size; j++ ) {
        for ( int i=0; i<size; i++ ) {
            tempVector[0]= ( i+offset-halfSize );
            tempVector[1]= ( - ( j+offset-halfSize ) );
            tempVector[2]= ( halfSize );

            tempVector.Normalize();
            tempVector.PackTo01();

            bytePtr[0]= ( unsigned char ) ( tempVector[0]*255 );
            bytePtr[1]= ( unsigned char ) ( tempVector[1]*255 );
            bytePtr[2]= ( unsigned char ) ( tempVector[2]*255 );

            bytePtr+=3;
        }
    }
    glTexImage2D (  GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
                    0, GL_RGBA8, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, data );

    //negative z
    bytePtr=data;

    for ( j=0; j<size; j++ ) {
        for ( int i=0; i<size; i++ ) {
            tempVector[0]= ( - ( i+offset-halfSize ) );
            tempVector[1]= ( - ( j+offset-halfSize ) );
            tempVector[2]= ( -halfSize );

            tempVector.Normalize();
            tempVector.PackTo01();

            bytePtr[0]= ( unsigned char ) ( tempVector[0]*255 );
            bytePtr[1]= ( unsigned char ) ( tempVector[1]*255 );
            bytePtr[2]= ( unsigned char ) ( tempVector[2]*255 );

            bytePtr+=3;
        }
    }
    glTexImage2D (  GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
                    0, GL_RGBA8, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, data );

    delete [] data;
    glTexParameteri ( GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri ( GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri ( GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE_EXT );
    glTexParameteri ( GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE_EXT );
    glTexParameteri ( GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_R_EXT, GL_CLAMP_TO_EDGE_EXT );

}

