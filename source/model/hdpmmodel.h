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

#ifndef HDPMMODEL_H
#define HDPMMODEL_H

#include "hmodel.h" // inheriting class's header file

/*
========================================================================

.DPM model file format

========================================================================
*/

#define DPMHEADER               "DARKPLACESMODEL\0"

#define DPM_MAX_NAME            32
#define DPM_MAX_MESHES          32
#define DPM_MAX_FRAMES          65536
#define DPM_MAX_TRIS            65536
#define DPM_MAX_VERTS           (DPM_MAX_TRIS * 3)
#define DPM_MAX_BONES           256
#define DPM_MAX_SHADERS         256
#define DPM_MAX_FILESIZE        16777216
#define DPM_MAX_ATTACHMENTS     DPM_MAX_BONES
#define DPM_MAX_LODS            4

// model format related flags
#define DPM_BONEFLAG_ATTACH     1
#define DPM_MODELTYPE           2

typedef struct {
    char id[16];            // "DARKPLACESMODEL\0", length 16
    unsigned int type;      // 2 (hierarchical skeletal pose)
    unsigned int filesize;  // size of entire model file
    float mins[3], maxs[3], yawradius, allradius; // for clipping uses

    // these offsets are relative to the file
    unsigned int num_bones;
    unsigned int num_meshes;
    unsigned int num_frames;
    unsigned int ofs_bones;
    unsigned int ofs_meshes;
    unsigned int ofs_frames;
}
ddpmheader_t;

// there may be more than one of these
typedef struct {
    // these offsets are relative to the file
    char shadername[32];        // name of the shader to use
    unsigned int num_verts;
    unsigned int num_tris;
    unsigned int ofs_verts;
    unsigned int ofs_texcoords;
    unsigned int ofs_indices;
    unsigned int ofs_groupids;
}
ddpmmesh_t;

// one per bone
typedef struct {
    // name examples: upperleftarm leftfinger1 leftfinger2 hand, etc
    char name[DPM_MAX_NAME];
    signed int parent;      // parent bone number
    unsigned int flags;     // flags for the bone
}
ddpmbone_t;

typedef struct {
    float matrix[3][4];
}
ddpmbonepose_t;

// immediately followed by bone positions for the frame
typedef struct {
    // name examples: idle_1 idle_2 idle_3 shoot_1 shoot_2 shoot_3, etc
    char name[DPM_MAX_NAME];
    float mins[3], maxs[3], yawradius, allradius; // for clipping uses
    unsigned int ofs_bonepositions;
}
ddpmframe_t;

// one or more of these per vertex
typedef struct {
    float origin[3];        // vertex location (these blend)
    float influence;        // influence fraction (these must add up to 1)
    float normal[3];        // surface normal (these blend)
    unsigned int bonenum;   // number of the bone
}
ddpmbonevert_t;

// variable size, parsed sequentially
typedef struct {
    unsigned int numbones;
    // immediately followed by 1 or more ddpmbonevert_t structures
    ddpmbonevert_t verts[1];
}
ddpmvertex_t;

typedef struct {
    float           st[2];
}
ddpmcoord_t;


/*
 * do czytania modeli z plik� dpm
 */
class HDPMModel : public HModel {
public:
    // class constructor
    HDPMModel();
    // class destructor
    ~HDPMModel();
};

#endif // HDPMMODEL_H

