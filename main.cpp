#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<Myfunction.h>
#include<Window/Window.h>
#include<Window/const.h>

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

	//-------------------------------------------------------------------渲染
	while (!glfwWindowShouldClose(Mywindow.window)) {
		processInput(&Mywindow);  //键盘输入处理



		//---------------------------------------------------------维护渲染时间
		float currentFrame = glfwGetTime();
		Mywindow.deltaTime = currentFrame - Mywindow.lastFrame;
		Mywindow.lastFrame = currentFrame;

		//-------------------------------------------------------------------渲染
		render();

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

