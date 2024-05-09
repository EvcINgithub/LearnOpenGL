#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<Myfunction.h>
#include<Window/Window.h>
#include<Window/const.h>

Camera Mycamera = Camera();

//-------------------------------------------------------------------������
void mouse_callback(GLFWwindow*, double, double);
void scroll_callback(GLFWwindow* window, double, double);
void processInput(Window*);
void render();


int main() {
	//-------------------------------------------------------------------��ʼ��
	selfInit();
	//-------------------------------------------------------------------����������
	Window Mywindow = Window(DEFAULT_SCR_WIDTH, DEFAULT_SCR_HEIGHT, "LearnOpenGL", true);

	glfwSetCursorPosCallback(Mywindow.window, mouse_callback); //����ƶ���Ӧ����
	glfwSetScrollCallback(Mywindow.window,scroll_callback);   //��������Ӧ����

	//-------------------------------------------------------------------��Ⱦ
	while (!glfwWindowShouldClose(Mywindow.window)) {
		processInput(&Mywindow);  //�������봦��



		//---------------------------------------------------------ά����Ⱦʱ��
		float currentFrame = glfwGetTime();
		Mywindow.deltaTime = currentFrame - Mywindow.lastFrame;
		Mywindow.lastFrame = currentFrame;

		//-------------------------------------------------------------------��Ⱦ
		render();

		//-------------------------------------------------------------------��Ⱦ����
		glfwSwapBuffers(Mywindow.window); //ִ��˫�������
		glfwPollEvents();

	}



	//-------------------------------------------------------------------�������ͷ���Դ
	glfwTerminate();
	return 0;
}


//-------------------------------------------------------------------����ʵ��
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
	float yoffset = lastY - ypos; // ע���������෴�ģ���Ϊy�����Ǵӵײ����������������
	lastX = xpos;
	lastY = ypos;

	Mycamera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	Mycamera.ProcessMouseRoll(static_cast<float>(yoffset));
}

