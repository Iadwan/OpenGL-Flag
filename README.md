# OpenGL



# Start with Flag Rendering
![Flag](Flag.png)


// 1. Put vertex data in GPU memory
glBufferData(...);

// 2. Tell GPU how to interpret it
glVertexAttribPointer(...);

// 3. Tell GPU which shaders to use
glUseProgram(shaderProgram);

// 4. Tell GPU which vertex data to use
glBindVertexArray(VAO);

// 5. START THE GPU WORK
glDrawArrays(GL_TRIANGLES, 0, 3);

// 6. Show the completed frame
glfwSwapBuffers(window);


## OpenGL Rendering Pipeline

```mermaid
flowchart TD

    %% =========================
    %% CPU SIDE
    %% =========================

    CPU["🖥️ CPU<br/>Your C++ Application"]

    DRAW["glDrawArrays()<br/>Start Drawing"]

    DRIVER["OpenGL Driver<br/>Translates API Commands"]


    %% =========================
    %% GPU SIDE
    %% =========================

    subgraph GPU["🎮 GPU"]

        COMMAND["GPU Command Processing"]

        subgraph VERTEX_STAGE["1️⃣ Vertex Processing"]
            VERTEX_DATA["Vertex Data<br/>VBO / VAO"]
            VERTEX_SHADER["Vertex Shader<br/>gl_Position = vec4(aPos, 1.0)"]
        end

        ASSEMBLY["2️⃣ Primitive Assembly<br/>GL_TRIANGLES"]

        TRIANGLE["🔺 Triangle"]

        RASTER["3️⃣ Rasterization<br/>Triangle → Fragments"]

        FRAGMENTS["Fragments<br/>Potential Pixels"]

        FRAGMENT_SHADER["4️⃣ Fragment Processing<br/>Fragment Shader"]

        DEPTH["5️⃣ Depth / Stencil Test<br/>Currently Not Enabled"]

        BLEND["6️⃣ Blending<br/>Currently Not Enabled"]

        FRAMEBUFFER["7️⃣ Framebuffer<br/>Rendered Pixels"]

    end


    %% =========================
    %% DISPLAY
    %% =========================

    SWAP["glfwSwapBuffers()"]

    DISPLAY["🖥️ DISPLAY<br/>Monitor"]


    %% =========================
    %% FLOW
    %% =========================

    CPU --> DRAW
    DRAW --> DRIVER
    DRIVER --> COMMAND

    COMMAND --> VERTEX_DATA
    VERTEX_DATA --> VERTEX_SHADER

    VERTEX_SHADER --> ASSEMBLY
    ASSEMBLY --> TRIANGLE
    TRIANGLE --> RASTER
    RASTER --> FRAGMENTS
    FRAGMENTS --> FRAGMENT_SHADER

    FRAGMENT_SHADER --> DEPTH
    DEPTH --> BLEND
    BLEND --> FRAMEBUFFER

    FRAMEBUFFER --> SWAP
    SWAP --> DISPLAY


    %% =========================
    %% YOUR CODE CONNECTIONS
    %% =========================

    CODE1["Your C++:<br/>glBufferData()"]
    CODE2["Your C++:<br/>glVertexAttribPointer()"]
    CODE3["Your GLSL:<br/>Vertex Shader"]
    CODE4["Your GLSL:<br/>Fragment Shader"]
    CODE5["Your C++:<br/>glClear()"]
    CODE6["Your C++:<br/>glfwSwapBuffers()"]

    CODE1 -.-> VERTEX_DATA
    CODE2 -.-> VERTEX_DATA
    CODE3 -.-> VERTEX_SHADER
    CODE4 -.-> FRAGMENT_SHADER
    CODE5 -.-> FRAMEBUFFER
    CODE6 -.-> SWAP


    %% =========================
    %% STYLING
    %% =========================

    classDef cpu fill:#dbeafe,stroke:#2563eb,stroke-width:2px,color:#111;
    classDef gpu fill:#dcfce7,stroke:#16a34a,stroke-width:2px,color:#111;
    classDef shader fill:#fef3c7,stroke:#d97706,stroke-width:2px,color:#111;
    classDef stage fill:#f3e8ff,stroke:#9333ea,stroke-width:2px,color:#111;
    classDef output fill:#fee2e2,stroke:#dc2626,stroke-width:2px,color:#111;
    classDef code fill:#f1f5f9,stroke:#64748b,stroke-width:1px,color:#111;

    class CPU,DRAW,DRIVER cpu;
    class COMMAND,VERTEX_DATA,ASSEMBLY,TRIANGLE,RASTER,FRAGMENTS,DEPTH,BLEND,FRAMEBUFFER gpu;
    class VERTEX_SHADER,FRAGMENT_SHADER shader;
    class RASTER,ASSEMBLY,DEPTH,BLEND stage;
    class SWAP,DISPLAY output;
    class CODE1,CODE2,CODE3,CODE4,CODE5,CODE6 code;
```
