#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

//While the size of a window is measured in screen coordinates, OpenGL works 
//with pixels. The size you pass into glViewport, for example, 
//should be in pixels
//The callback function receives the new size of the framebuffer when it is 
//resized, which can for example be used to update the OpenGL viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
//Whenever the window changes in size, GLFW calls this function and fills in 
//the proper arguments for you to process

//process all input: query GLFW whether relevant keys are pressed/released 
//this frame and react accordingly
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

/*void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
	// и приложение после этого закроется
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}*/


int main()
{
	glfwInit(); //initializes the GLFW library
	//sets the minimum required OpGL vers
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //major
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //minor
	//GLFW_OPENGL_PROFILE указывает, д какого профиля OpGL следует создать контекст
	//core profile - основной профиль
	//сообщаем, что хотим явно использовать основной профиль - мы получим доступ
	//к меньшему подмножеству функций OpGL без обратной совместимости ф-й
	//к-е нам больше не нужны (???)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "My Title", NULL, NULL);
	//GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", glfwGetPrimaryMonitor(), NULL);
	//to create a full screen window
	if (window == NULL) 
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate(); //Эта функция уничтожает все оставшиеся окна и курсоры, 
		//восстанавливает любые измененные гамма-рампы и освобождает любые другие 
		//выделенные ресурсы
		
		return -1; //(???)
	}
	glfwMakeContextCurrent(window);
	
	//We do have to tell GLFW we want to call this function on every 
	//window resize by registering it
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//When the window is first displayed framebuffer_size_callback gets called 
	//as well with the resulting window dimensions.
	
	//GLAD управляет указателями функций для OpenGL, поэтому мы хотим 
	//инициализировать GLAD перед вызовом любой функции OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	//Мы передаем GLAD функцию для загрузки адреса указателей функций OpenGL, 
	//который является специфичным для ОС. GLFW дает нам glfwGetProcAddress, 
	//который определяет правильную функцию, основанную на том, 
	//для какой ОС мы компилируем.

	//We have to tell OpenGL the size of the rendering window so OpenGL knows 
	//how we want to display the data and coordinates with respect to the window
	//glViewport(0, 0, 800, 600);

	//We don't want the application to draw a single image 
	//and then immediately quit and close the window
	//so we have to create the render loop, that keeps on 
	//running until we tell GLFW to stop
	//This function returns the value of the close flag of the specified window.
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		//glfwSetKeyCallback(window, key_callback);

		glClearColor(0.7f, 0.4f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//glfwSwapBuffers will swap the color buffer that is used to render to during 
	//this render iteration and show it as output to the screen.
	//glfwPollEvents function checks if any events are triggered, updates the 
	//window state, and calls the corresponding functions

	
	glfwTerminate();
	return 0;
	
}