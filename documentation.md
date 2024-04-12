# Brody Foster, Ryan Groves, HW2 Documentation

## 1. Objects

### .obj Files
Our VBO and VAO data are determined be reading data from a .obj file. .obj files have the following properties that we utilize: vertices and faces. Vertices are read using lines that start with "v " and faces from lines that start with "f ". Vertex data gives us each vertex in order and their positions, and faces tell us which vertices are part of each face. We use this data to create a separate triangles data structure.

### Separate Triangles Data Structure
This data structure is created by treating the vertices of each face as separate from the vertices of any other face. Essentially this means that is a vertex is part of more than one face, then its data is stored more than once, once for each face. We use the face data to determine which vertices that we found must have their data used by this face (ie. vertices 1, 2, and 4). The vertices are put into the VBO in this order.

### VBO and VAO
The VBO and VAO help us build up the vertex data in a simple container. Our VBO contains 3 floats for location, 3 floats for the normal, then 3 floats for color for each vertex, and contains every used vertex in order of how they appear on faces. For instance if face 1 had vertices 1, 2, 4 and face 2 had vertices 1, 3, 4, then the VBO would contain vertices in the following order 1, 2, 4, 1, 3, 4. Notice that vertices 1 and 4 are duplicated as they appear in multiple faces, this is because of our separate triangles data structure. The VAO defines the properties of each vertex by telling us that there are 6 floats for each color, and a normal vector.

### EBO
The EBO or element buffer object stores indices which openGL can use to determine what vertex is supposed to be drawn next. This buffer is important in creating the indexed triangles data structure. We replace the VBO variable in certain areas of code with the EBO in order to switch what data type we are using, for instance we swapped to EBO in the glBindBuffer() command and swapped  glDrawArrays with glDrawElements. The EBO is important to use here for our new data structure because it allows us to not simply pass vertices into the buffer multiple times but instead reference the same piece of vertex data more than once. So instead of having to put vertex A into the buffer once for every triangle it is a part of, the EBO uses the index of that vertex multiple times without storing the data itself more than once.

### Indexed Triangles
The indexed triangles data structure was implemented by saving one copy of each vertex into a list that could be referenced using indices stored within the faces themselves. This essentially allows us to store only one copy of each vertex's data. Faces stil store 3 vertices but instead store indices / pointers to each vertex instead of an individual copy.

## 2. Shader

### Vertex Shaders
Our vertex shaders consist of the following: colorVertex and basicVertex, both take in a position and color that consist of 3 floats each, and outputs a vec4 vertexColor. In main, both set gl_Position to be equal to the input position with one extra float on the end of value 1.0. This means that gl_Position contains a vec4 instead of the input vec3. BasicVertex sets the color to be consistent accross all vertices, while colorVertex sets the color to be equal to the input color value.

### Fragment Shaders
Our fragment shaders consist of only one shader currently, that being basicFragment.fs. This shader takes in a vec4 color and in main sets its output (vec4 FragColor) to be equal to the input.

### Vertex and Fragment Shader Files (.vs and .fs)
Our program is able to use separate .vs and .fs files to create and manage our shaders. Shaders are loaded within our main.cpp file. Both shaders are loaded at once using the line Shader loadedShader("file1.vs", "file2.fs"); Then in the main loop we make sure to use our shader instead of the default shader by replacing glUseProgram(ShaderProgram) with loadedShader.use(). 

## 3. Transformations

### Transformations Class (Model View Matrix)
The following transformations were implemented within our code:

1. Model Space -> World Space Transformation
This tansformation changes our model space within which all vertices have their origin at the object center, to the world space in which all vertices have the world origin as their object center. This allows us to move the model around the world space.

2. World Space -> Camera Space Transformation
This transformation changes our world space to the camera space, where the origin is now the camera center. This allows us to get data and positions relative to the camera.

3. Camera Space -> Normalized Device Coordinates Transformation
This transformation brings all vertex location data to be on a normalized coordinate system where all axes have a value of -1.0 to 1.0. The normals can be effected by this, but color is not.

The final transformation, normalized device coordinates to screen space transformation, is handled by openGL automatically so we do not implement it ourselves.

We have 3 linear transformations that can be done to an object using the Model View Matrix. These would be moving, scaling, and rotating in real time. These transformations happen in transformation 1: model space -> world space. This means that the vertex data is not being effected but instead the matrix being applied to the vertices in order to transform to world space is being changed.

Moving an object requires adding a specific number to each vertex coordinate.

Scaling an object requires scaling the vertex coordinate numbers using GLM scale.

Rotating an object was implemented using GLM rotate.

#### CPU/GPU Implementation
We had a hard time determining if the perspective matrix should *always* be applied on the GPU as we were a little confused at times. The difference here was whether the GPU could transform the coordinates by being sent the untransformed coordinates and matrices, or if we send the already transformed coordinates (doing the transforms on the CPU). It would make sense that we should transform each vertex in parallel, so we believe the GPU would be ideal. We assumed that perspective was supposed to always be done on the GPU. We can however change between these two implementations by changing the boolean named "transformOnCPU" in main.cpp.

We saw little to no difference however, in the speed when changing this boolean value.

Step 3 listed above is always done on the GPU, however steps 1 and 2 can be done on the CPU if this boolean is changed.

## 4. Instructions / Tutorial

Please reference our README.md file to learn how to use our implemented code.