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
#include "htexturefile.h" // class's header file
#include <png.h>

// class constructor
HTextureFile::HTextureFile(string filename):HTexture(filename) {
    m_uiID=0;
    m_iManagerID=0;
    this->Load(filename);
}

// class destructor
HTextureFile::~HTextureFile() {
    // insert your code here
}

// wczytuje tekstur�z pliku
int HTextureFile::Load(string filename) {
    /* DONE (#1#): Implement HTextureFile::Load() */
    FILE* fp=NULL;
    fp=fopen(filename.c_str(),"rb");
    m_sName=filename;
    if (!fp) {
        return 0;
    }
//  debug("HTextureFile.Load(\"%s\")\n",filename.c_str());
    GLubyte sig[8];
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    int colorType, bitDepth;
    int rowBytes;
    unsigned char* data=NULL;

    fread(sig, 1, 8, fp);
    if (!png_check_sig(sig, 8)) {
        hlog("Bad PNG signature in '%s'\n",filename.c_str());
        return 0;   /* bad signature */
    }


    /* could pass pointers to user-defined error handlers instead of NULLs: */

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        hlog("OUT OF MEMORY while reading '%s'!!!\n",filename.c_str());
        return 0;   /* out of memory */
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        hlog("OUT OF MEMORY while reading '%s'!!!\n",filename.c_str());
        return 0;   /* out of memory */
    }


    /* we could create a second info struct here (end_info), but it's only
    * useful if we want to keep pre- and post-IDAT chunk info separated
    * (mainly for PNG-aware image editors and converters) */


    /* setjmp() must be called in every function that calls a PNG-reading
    * libpng function */

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        return 0;
    }


    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);  /* we already read the 8 signature bytes */

    png_read_info(png_ptr, info_ptr);  /* read all PNG info up to image data */


    int sizeX = png_get_image_width(png_ptr, info_ptr);
    int sizeY = png_get_image_height(png_ptr, info_ptr);
    //obj->depth = 1;
    colorType = png_get_color_type( png_ptr, info_ptr);
    bitDepth = png_get_bit_depth( png_ptr, info_ptr);


    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        return 0;
    }


    /* expand palette images to RGB, low-bit-depth grayscale images to 8 bits,
    * transparency chunks to full alpha channel; strip 16-bit-per-sample
    * images to 8 bits per sample; and convert grayscale to RGB[A] */

    if (colorType == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(png_ptr);
    }
    if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8) {
        png_set_gray_1_2_4_to_8(png_ptr);
    }
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(png_ptr);
    }



    /* all transformations have been registered; now update info_ptr data,
    * get rowbytes and channels, and allocate image memory */

    png_read_update_info(png_ptr, info_ptr);

    rowBytes = png_get_rowbytes(png_ptr, info_ptr);
    int channels = (int)png_get_channels(png_ptr, info_ptr);

    //GLubyte *buffer = new GLubyte[rowBytes * obj->height];
    data = ((unsigned char*)malloc(sizeof(unsigned char)*rowBytes*sizeY));
    GLubyte **rowPointers = new GLubyte*[sizeY];

    /* set the individual row_pointers to point at the correct offsets */

    for ( int ii = 0;  ii < sizeY;  ++ii) {
        rowPointers[ii] = data + ii*rowBytes;
    }


    /* now we can go ahead and just read the whole image */

    png_read_image(png_ptr, rowPointers);


    /* and we're done!  (png_read_end() can be omitted if no processing of
    * post-IDAT text/time/etc. is desired) */
    /*      glPixelTransferf(GL_RED_SCALE,1.5f);                // Scale RGB By 50%, So That We Have Only
            glPixelTransferf(GL_GREEN_SCALE,1.5f);              // Half Intenstity
            glPixelTransferf(GL_BLUE_SCALE,1.5f);*/
    delete []rowPointers;
    if (glIsTexture(m_uiID)) {
        glDeleteTextures(1,&m_uiID);
    }
    glGenTextures(1,&m_uiID);
    glBindTexture(GL_TEXTURE_2D,m_uiID);

    int textureType = GL_RGB;

    // If the image is 32-bit (4 channels), then we need to specify GL_RGBA for an alpha
    if (channels == 4)
        textureType = GL_RGBA;
    // Build Mipmaps (builds different versions of the picture for distances - looks better)
    gluBuild2DMipmaps(GL_TEXTURE_2D, channels, sizeX,
                      sizeY, textureType, GL_UNSIGNED_BYTE, data);


    /*  if (mode & T_NOREPEAT_S){
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      } else {*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    /*  }
      if (mode & T_NOREPEAT_T){
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      } else {*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    /* }
     */
//Assign the mip map levels and texture info
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Set a filtering value of GL_LINEAR_MIPMAP_LINEAR to take advantage of
    // anisotropic texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // Largest Anistropic Texture Ratio
    GLfloat fLargestSupportedAnisotropy;

    // Determine largest supported anistropic texture ratio
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargestSupportedAnisotropy);

    // Set anisotropic texture filter ratio (1:1 is isotropic which is the same
    // as not using anisotropic filtering)
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, &fLargestSupportedAnisotropy);

    free(data);
    /*         if (bitDepth<=8)
             {
                bitDepth = 8;
                obj->bdata = buffer;
             }
             else
             {
                obj->sdata = (GLushort *)buffer;
             }
    */

    png_read_end(png_ptr, NULL);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(fp);
//         IMG_Flip(pImageData);
    m_uiWidth=sizeX;
    m_uiHeight=sizeY;
    return 1;

}

// aduje tekstur�do karty
int HTextureFile::Bind() {
    /* DONE (#1#): Implement HTextureFile::Bind() */
    glBindTexture(GL_TEXTURE_2D,m_uiID);
    return m_uiID;
}

// pusta funkcja ale musi by�
int HTextureFile::Update() {
    /* DONE (#1#): Implement HTextureFile::Update() */
    return 1;
}


