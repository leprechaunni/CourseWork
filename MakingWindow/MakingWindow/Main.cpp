#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <iostream>
#include "ShaderProgram.h"
#include "Manager.h"

using namespace std;

/*
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"out vec4 vertexColor_yel;\n"
"out vec4 vertexColor_gr;\n"
"out vec4 vertexColor_or;\n"
"out vec3 ourColor_1;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"	ourColor_1 = color;\n"
"	vertexColor_yel = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"	vertexColor_gr = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
"	vertexColor_or = vec4(1.0f, 0.5f, 0.0f, 1.0f);\n"
"}\0";
const char* fragmentShaderSource_yellow = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";
const char* fragmentShaderSource_green = "#version 330 core\n"
"in vec4 vertexColor_gr;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vertexColor_gr;\n"
"}\n\0";
const char* fragmentShaderSource_orange = "#version 330 core\n"
"in vec3 ourColor_1;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor_1, 1.0f);\n"
"}\n\0";
*/


GLfloat vertices1[] = {
	-0.5f, 0.5f, 0.0f,
	 0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f
};

GLfloat vertices2[] = {

	1.0f,  1.0f,  0.0f,
	1.0f, -1.0f,  0.0f,
	0.6f,  1.0f,  0.0f,
	0.6f, -1.0f,  0.0f

};

GLfloat vertices_kv[] = {
			//koordinates	//colors
	0.5f,  0.25f, 0.0f,		1.0f, 0.0f, 0.0f, //verh_r
	0.5f, -0.25f, 0.0f,		0.0f, 1.0f, 0.0f, //niz_r
	0.0f, -0.25f, 0.0f,		1.0f, 0.0f, 1.0f,//niz_l
	0.0f,  0.25f, 0.0f,		0.0f, 1.0f, 0.0f//verh_l
};

GLuint indices[] = {
	0, 1, 3,
	1, 2, 3
};

GLfloat point[] = {
	-0.9f, -0.4f, 0.0f
};

GLfloat line[] = {
	-0.8f, 0.8f, 0.0f,
	-0.8f, 0.3f, 0.0f
};

GLfloat polygon[] = {
	0.2f, 0.0f, 0.0f,
	-0.2, 0.0f, 0.0f,
	-0.4f, 0.2f, 0.0f,
	0.0f, 0.4f, 0.0f,
	0.4f, 0.2f, 0.0f
};

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


int main(int argc, char** argv)
{
	glfwInit(); //initializes the GLFW library
	//sets the minimum required OpGL vers
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //major
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //minor
	//GLFW_OPENGL_PROFILE указывает, д какого профиля OpGL следует создать контекст
	//core profile - основной профиль
	//сообщаем, что хотим явно использовать основной профиль - мы получим доступ
	//к меньшему подмножеству функций OpGL без обратной совместимости ф-й
	//к-е нам больше не нужны 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "My Title", NULL, NULL);
	//GLFWwindow* window = glfwCreateWindow(1600, 900, "My Title", glfwGetPrimaryMonitor(), NULL);
	//to create a full screen window
	if (window == NULL) 
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate(); //Эта функция уничтожает все оставшиеся окна и курсоры, 
		//восстанавливает любые измененные гамма-рампы и освобождает любые другие 
		//выделенные ресурсы
		
		return -1;
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

	Manager manager(argv[0]);
	auto pGreenShaderProgram = manager.loadShaders("GreenShader", "resource/vertex.txt", "resource/fragment_green.txt");
	if (!pGreenShaderProgram)
	{
		cerr << "cant create shader program: " << "GreenShader" << endl;
		return -1;
	}

	auto pYellowShaderProgram = manager.loadShaders("YellowShader", "resource/vertex.txt", "resource/fragment_yellow.txt");
	if (!pYellowShaderProgram)
	{
		cerr << "cant create shader program: " << "YellowShader" << endl;
		return -1;
	}

	auto pOrangeShaderProgram = manager.loadShaders("OrangeShader", "resource/vertex.txt", "resource/fragment_orange.txt");
	if (!pOrangeShaderProgram)
	{
		cerr << "cant create shader program: " << "OrangeShader" << endl;
		return -1;
	}

	{



		GLuint VBO[6], VAO[6], EBO;
		glGenVertexArrays(6, VAO);
		glGenBuffers(6, VBO); //create
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); //type
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW); //put data in buffer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(VAO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]); //type
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW); //put data in buffer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(VAO[2]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2]); //type
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_kv), vertices_kv, GL_STATIC_DRAW); //put data in buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //type
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(VAO[3]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[3]); //type
		glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW); //put data in buffer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(VAO[4]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[4]); //type
		glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW); //put data in buffer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(VAO[5]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[5]); //type
		glBufferData(GL_ARRAY_BUFFER, sizeof(polygon), polygon, GL_STATIC_DRAW); //put data in buffer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);






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


		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //karkas regim
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			pYellowShaderProgram->use();
			float timeValue = glfwGetTime();
			float redValue = (sin(timeValue) / 1.5f) + 1.0f;
			float greenValue = (cos(timeValue) / 2.0f) + 0.5f;
			float blueValue = (sin(timeValue) ) + 0.5f;
			int vertexColorLocation = glGetUniformLocation(pYellowShaderProgram->m_ID, "ourColor");
			glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);

			glBindVertexArray(VAO[0]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
		

			pGreenShaderProgram->use();
			glBindVertexArray(VAO[1]);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glBindVertexArray(0);

		
			pOrangeShaderProgram->use();
			glBindVertexArray(VAO[2]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		/*
		shaderProgram_gr.use();
		glBindVertexArray(VAO[3]);
		glDrawArrays(GL_POINTS, 0, 1);
		glBindVertexArray(0);

		//shaderProgram_or.use();
		glBindVertexArray(VAO[4]);
		//glLineWidth(5);
		glDrawArrays(GL_LINES, 0, 2);
		glBindVertexArray(0);

		//shaderProgram_or.use();
		glBindVertexArray(VAO[5]);
		glDrawArrays(GL_LINE_LOOP, 0, 5);
		glBindVertexArray(0);
		*/



			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	//glfwSwapBuffers will swap the color buffer that is used to render to during 
	//this render iteration and show it as output to the screen.
	//glfwPollEvents function checks if any events are triggered, updates the 
	//window state, and calls the corresponding functions



		glDeleteBuffers(6, VAO);
		glDeleteBuffers(6, VBO);
		glDeleteBuffers(1, &EBO);
	}
	glfwTerminate();
	return 0;
	
}