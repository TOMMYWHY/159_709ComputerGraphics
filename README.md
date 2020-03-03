# computer graphics 159.709
#### Daniel Playne
## week 01

### course content
1. real-time 3D rendering methods
2. coordinate spaces & transforms
3. 3D object representation

* rendering
> 2 dimentional image   
> viewing frustrum(field of view)

* 3D coordinates
> vertexes  ->  edges ->    faces
> polygonal modelling 

* rasterisation **栅格化**
>   the faces are (usually) filled in and drawn in the correct depth order.
>  A polygon is ‘filled in’ by rasterisation, finding the pixels that it encom- passes.
rasterisation => filled

* shading    
* texuring
>  more realistic appearance
 > Vertexes are mapped to a 2D texture by the use of** UV coordinates.**

* projection
 > perspective projection

* rendering pipeline
 > The graphics rendering pipeline (or just pipeline) has the job of taking the description of a scene(  *surfaces, materials, textures, lights, visual effects* ) and step-by-step turning it into the two-dimensional image that can be finally displayed on the screen.

     1. application : 
            run on the CPU  
            updating the position
            Detecting collisions between objects
    
     2. geometry
         2.1   model & view tranform : model space; word space; eye space
         2.2    vertex shading
         2.3    projection
                        orthographic正向影像     perspective透视投影
         2.4    clipping 裁切
         2.5    screen mapping
                        screen coordinate

     3. rasteriser
         3.1 triangle setup
         3.1 triangle traversal
         3.1 pixel shading
                fragement shader
         3.1 merging
                combination    stencil-buffer


* z-buffering
    color buffer     depth buffer

* ray-tracing    光线追踪
>especially important for reflections
translucent surfaces
computationally  expensive


#### libs
glfw : widow keyboard.. basic action

glew: extension wrangle    使opengl 与 本机显卡 api matching
> macos dont need glew









