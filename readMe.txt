#Extra Credit Task: 

Understanding and explanation:
Demonstrate an understanding of the inefficiency in the current method of drawing complex shapes and explain it clearly.

There are a couple inefficiencies with this code:
- I have the the geometries setup in the main but it should be set up in a different 'shapes' folder for cleaner code
- Every frame, the function calls glVertexAttribPointer() to redefine attribute pointers for vertex colors
- The program constantly switches between different rendering modes using a large switch statement in myRenderScene()
- The function myRenderScene() updates the GL_ARRAY_BUFFER with glBufferData() every frame for the triangle vertices
- Creating new windows on TAB key press contains a lot of duplicated code for shaders, geometries and main loop.