#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<Myfunction.h>
#include<Window/Window.h>
#include<Window/const.h>
#include<Shader/Shader.h>
#include<Texture/Texture.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <map>
using namespace std;


Camera Mycamera = Camera();

//-------------------------------------------------------------------函数区
void mouse_callback(GLFWwindow*, double, double);
void scroll_callback(GLFWwindow* window, double, double);
void processInput(Window*);
void render();


int main() {
	//-------------------------------------------------------------------初始化
	selfInit();
	//-------------------------------------------------------------------构建上下文
	Window Mywindow = Window(DEFAULT_SCR_WIDTH, DEFAULT_SCR_HEIGHT, "LearnOpenGL", true);

	glfwSetCursorPosCallback(Mywindow.window, mouse_callback); //鼠标移动响应函数
	glfwSetScrollCallback(Mywindow.window,scroll_callback);   //鼠标滚轮响应函数

	//Shader Myshader = Shader("D:\\dependence_OPENGL\\include\\Shader\\Blending\\vs.vs", "D:\\dependence_OPENGL\\include\\Shader\\Blending\\fs.fs");
    Shader Myshader = Shader("D:\\dependence_OPENGL\\include\\Shader\\Blending\\vs.vs", "E:\\LearnOpenGL\\LearnOpenGL\\resource\\shader\\fs_blending.fs");

	//-------------------------------------------------------------------测试设置
	glEnable(GL_DEPTH_TEST);//开启深度测试
	//glDepthMask(GL_FALSE);      //依赖于深度测试开启，此项使得深度缓冲不再更新
	// glDepthFunc(GL_LESS);      //设置深度测试的函数，详见下表
	// GL_ALWAYS 	永远通过深度测试
	//GL_NEVER 	永远不通过深度测试
	//GL_LESS 	在片段深度值小于缓冲的深度值时通过测试
	//GL_EQUAL 	在片段深度值等于缓冲区的深度值时通过测试
	//GL_LEQUAL 	在片段深度值小于等于缓冲区的深度值时通过测试
	//GL_GREATER 	在片段深度值大于缓冲区的深度值时通过测试
	//GL_NOTEQUAL 	在片段深度值不等于缓冲区的深度值时通过测试
	//GL_GEQUAL 	在片段深度值大于等于缓冲区的深度值时通过测试

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    //函数接受两个参数，来设置源和目标因子
    //-------------------------------------------------------------------数据
    float cubeVertices[] = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    float planeVertices[] = {
        // positions          // texture Coords 
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };
    float transparentVertices[] = {
        // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
        1.0f,  0.5f,  0.0f,  1.0f,  0.0f
    };
    // cube VAO
    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // plane VAO
    unsigned int planeVAO, planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // transparent VAO
    unsigned int transparentVAO, transparentVBO;
    glGenVertexArrays(1, &transparentVAO);
    glGenBuffers(1, &transparentVBO);
    glBindVertexArray(transparentVAO);
    glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);

    // load textures
    // -------------
    unsigned int cubeTexture = loadTexture("resource/wall.jpg");
    unsigned int floorTexture = loadTexture("resource/wall.jpg");
    unsigned int transparentTexture = loadTexture("resource/windows.png");


    vector<glm::vec3> vegetation
    {
        glm::vec3(-1.5f, 0.0f, -0.48f),
        glm::vec3(1.5f, 0.0f, 0.51f),
        glm::vec3(0.0f, 0.0f, 0.7f),
        glm::vec3(-0.3f, 0.0f, -2.3f),
        glm::vec3(0.5f, 0.0f, -0.6f)
    };

    // Myshader configuration
    // --------------------
    Myshader.use();
    Myshader.setInt("texture1", 0);

    //不要打乱渲染顺序
    std::map<float, glm::vec3> sorted;
    for (unsigned int i = 0; i < vegetation.size(); i++)
    {
        float distance = glm::length(Mycamera.cameraPos - vegetation[i]);
        sorted[distance] = vegetation[i];
    }


	//-------------------------------------------------------------------渲染
	while (!glfwWindowShouldClose(Mywindow.window)) {
		processInput(&Mywindow);  //键盘输入处理

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除上一次渲染时的颜色与深度缓冲


		//-------------------------------------------------------------------渲染
		render();
        Myshader.use();
        glm::mat4 projection = Mycamera.getProjection();
        glm::mat4 view = Mycamera.getView();
        glm::mat4 model = glm::mat4(1.0f);
        Myshader.setMat4("projection", projection);
        Myshader.setMat4("view", view);
        // cubes
        glBindVertexArray(cubeVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cubeTexture);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        Myshader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        Myshader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // floor
        glBindVertexArray(planeVAO);
        glBindTexture(GL_TEXTURE_2D, floorTexture);
        model = glm::mat4(1.0f);
        Myshader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // vegetation
        glBindVertexArray(transparentVAO);
        glBindTexture(GL_TEXTURE_2D, transparentTexture);
        /*
                for (unsigned int i = 0; i < vegetation.size(); i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, vegetation[i]);
            Myshader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        
        */


        
        for(std::map<float,glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it) 
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, it->second);              
            Myshader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        //但是如果反向观察会发现从反面看仍然是不透明的
		//---------------------------------------------------------维护渲染时间
		float currentFrame = glfwGetTime();
		Mywindow.deltaTime = currentFrame - Mywindow.lastFrame;
		Mywindow.lastFrame = currentFrame;
		//-------------------------------------------------------------------渲染结束
		glfwSwapBuffers(Mywindow.window); //执行双缓冲操作
		glfwPollEvents();

	}



	//-------------------------------------------------------------------结束，释放资源
	glfwTerminate();
	return 0;
}


//-------------------------------------------------------------------函数实现
void render() {
    


	return;
}


void processInput(Window* win) {
	if (glfwGetKey(win->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(win->window, true);
	if (glfwGetKey(win->window, GLFW_KEY_W) == GLFW_PRESS)
		Mycamera.ProcessKeyboard(FORWARD, win->deltaTime);
	if (glfwGetKey(win->window, GLFW_KEY_S) == GLFW_PRESS)
		Mycamera.ProcessKeyboard(BACKWARD, win->deltaTime);
	if (glfwGetKey(win->window, GLFW_KEY_A) == GLFW_PRESS)
		Mycamera.ProcessKeyboard(LEFT, win->deltaTime);
	if (glfwGetKey(win->window, GLFW_KEY_D) == GLFW_PRESS)
		Mycamera.ProcessKeyboard(RIGHT, win->deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	static bool firstMouse = true;
	static int lastX = 400, lastY = 300;
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
	lastX = xpos;
	lastY = ypos;

	Mycamera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	Mycamera.ProcessMouseRoll(static_cast<float>(yoffset));
}

