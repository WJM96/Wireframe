Hiya! This is a small wavefront model (.obj file) viewer build in C. It 
renders the model in "wireframe" (lines, no textures etc.) mode. You can 
navigate your view with the arrow keys. 

up/down: zoom forward/backwards
left/right: rotate around the up/down axis
z/x: rotate around the left/right axis

Bugs:
File parsing is terribly picky. A stray comment will totally knock it out. 
.obj files that define vertex normals or texture coordinates in their face 
data will also break it.

Lines are not clipped at the viewing plane. If the model intersects the 
viewing window, there will be lines all over the place and the whole 
experience will be extremely upsetting. Zoom out.


Compile using the included bash file ("compile.sh");

It requires SDL2 to compile and run properly
