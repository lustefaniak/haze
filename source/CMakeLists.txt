include(FindOpenGL)
include(FindSDL)
include(FindPNG)


SET( haze_SRCS
	main.cpp

camera/hcamera.cpp
camera/hfrustum.cpp

console/hccommand.cpp
console/hconsole.cpp
console/hcparams.cpp
console/hcvar.cpp

core/endian.cpp
core/errors.cpp
core/fileutils.cpp
core/henginecore.cpp
core/hlog.cpp
core/hparser.cpp
core/htimer.cpp
core/singleton.cpp

game/hbulletmanager.cpp
game/hgame.cpp
game/hgamefpp.cpp
game/hgamehud.cpp
game/hlevel.cpp
game/hsky.cpp

geometry/hbsp.cpp
geometry/hgbbox.cpp
geometry/hgbrush.cpp
geometry/hgbrushplane.cpp
geometry/hgbsphere.cpp
geometry/hgplane.cpp
geometry/hgpoly.cpp
geometry/hgvert.cpp
geometry/hplane.cpp

gui/hfont.cpp
gui/hgui.cpp
gui/hguibutton.cpp
gui/hguidesktop.cpp
gui/hguilabel.cpp
gui/hguimouse.cpp
gui/hguiobject.cpp
gui/hguipanel.cpp
gui/hguiwindow.cpp

	input/hinputsystem.cpp

	light/hlight.cpp
	light/hlightmap.cpp
	light/hlightmapgenerator.cpp
	light/hlightsystem.cpp

	material/hmaterial.cpp
	material/hmaterialmanager.cpp
	material/htexture.cpp
	material/htexturefile.cpp
	material/htexturemanager.cpp
	material/htexturenormalizationcubemap.cpp

	math/matrix.cpp
	math/util3d.cpp

	model/hdpmmodel.cpp
	model/hmodel.cpp

	objects/hobject.cpp
	objects/hobjectfactory.cpp
	objects/hobjectsnow.cpp
	objects/hobjectwater.cpp

	particles/hparticlerenderer.cpp
	particles/hparticlerendererrain.cpp
	particles/hparticlerenderersnow.cpp
	particles/hparticlesystem.cpp
	particles/hparticlesystemrain.cpp
	particles/hparticlesystemsnow.cpp

	renderer/hrenderer.cpp
	renderer/hrendererwindow.cpp
	renderer/glsl.cpp
	
	world/hentity.cpp
	world/hworld.cpp
	world/hworldfromqmap.cpp
)

SET( haze_HEADERS

camera/hcamera.cpp
camera/hcamera.h
camera/hfrustum.cpp
camera/hfrustum.h

console/hccommand.cpp
console/hccommand.h
console/hconsole.cpp
console/hconsole.h
console/hcparams.cpp
console/hcparams.h
console/hcvar.cpp
console/hcvar.h

core/errors.h
core/fileutils.hpp
core/henginecore.cpp
core/henginecore.h
core/hlog.cpp
core/hlog.h
core/hparser.cpp
core/hparser.h
core/htimer.cpp
core/htimer.h
core/list.h
#core/mmgr.h
#core/nommgr.h
core/singleton.h
core/utility.h

game/hbulletmanager.cpp
game/hbulletmanager.h
game/hgame.cpp
game/hgame.h
game/hgamefpp.cpp
game/hgamefpp.h
game/hgamehud.cpp
game/hgamehud.h
game/hlevel.cpp
game/hlevel.h
game/hsky.cpp
game/hsky.h

geometry/hbsp.cpp
geometry/hbsp.h
geometry/hgbbox.cpp
geometry/hgbbox.h
geometry/hgbrush.cpp
geometry/hgbrush.h
geometry/hgbrushplane.cpp
geometry/hgbrushplane.h
geometry/hgbsphere.cpp
geometry/hgbsphere.h
geometry/hgplane.cpp
geometry/hgplane.h
geometry/hgpoly.cpp
geometry/hgpoly.h
geometry/hgvert.cpp
geometry/hgvert.h
geometry/hplane.cpp
geometry/hplane.h

gui/hfont.cpp
gui/hfont.h
gui/hgui.cpp
gui/hgui.h
gui/hguibutton.cpp
gui/hguibutton.h
gui/hguidesktop.cpp
gui/hguidesktop.h
gui/hguilabel.cpp
gui/hguilabel.h
gui/hguimouse.cpp
gui/hguimouse.h
gui/hguiobject.cpp
gui/hguiobject.h
gui/hguipanel.cpp
gui/hguipanel.h
gui/hguiwindow.cpp
gui/hguiwindow.h

input/hinputsystem.cpp
input/hinputsystem.h

light/hlight.cpp
light/hlight.h
light/hlightmap.cpp
light/hlightmap.h
light/hlightmapgenerator.cpp
light/hlightmapgenerator.h
light/hlightsystem.cpp
light/hlightsystem.h

material/hmaterial.cpp
material/hmaterial.h
material/hmaterialmanager.cpp
material/hmaterialmanager.h
material/htexture.cpp
material/htexture.h
material/htexturefile.cpp
material/htexturefile.h
material/htexturemanager.cpp
material/htexturemanager.h
material/htexturenormalizationcubemap.cpp
material/htexturenormalizationcubemap.h

math/mathlib.c
math/mathlib.h
math/mathlib2.h
math/matrix.cpp
math/matrix.h
math/plane.h
math/util3d.cpp
math/util3d.h
math/vector.h
model/hdpmmodel.cpp
model/hdpmmodel.h
model/hmodel.cpp
model/hmodel.h

objects/hobject.cpp
objects/hobject.h
objects/hobjectfactory.cpp
objects/hobjectfactory.h
objects/hobjectsnow.cpp
objects/hobjectsnow.h
objects/hobjectwater.cpp
objects/hobjectwater.h

particles/hparticlerenderer.cpp
particles/hparticlerenderer.h
particles/hparticlerendererrain.cpp
particles/hparticlerendererrain.h
particles/hparticlerenderersnow.cpp
particles/hparticlerenderersnow.h
particles/hparticlesystem.cpp
particles/hparticlesystem.h
particles/hparticlesystemrain.cpp
particles/hparticlesystemrain.h
particles/hparticlesystemsnow.cpp
particles/hparticlesystemsnow.h

renderer/extensions.h
renderer/glati.h
renderer/hrenderer.cpp
renderer/hrenderer.h
renderer/hrendererwindow.cpp
renderer/hrendererwindow.h
renderer/wglati.h

script/hscript.cpp
script/hscript.h
script/hscriptobject.cpp
script/hscriptobject.h

world/hentity.cpp
world/hentity.h
world/hworld.cpp
world/hworld.h
world/hworldfromqmap.h

)

# verbose - on
#SET( CMAKE_VERBOSE_MAKEFILE  ON )

# definitions for the project
ADD_DEFINITIONS( -Wall )

SET( HazeIncludes . )

INCLUDE_DIRECTORIES	( ${HazeIncludes} ${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
ADD_EXECUTABLE		( haze	${haze_SRCS} )
TARGET_LINK_LIBRARIES	( haze ${OPENGL_LIBRARIES} ${SDL_LIBRARY} ${PNG_LIBRARIES} GLEW)


INSTALL_TARGETS( /bin/ haze )
