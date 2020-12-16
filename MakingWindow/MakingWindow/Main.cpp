#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <glm/glm/vec2.hpp>
#include <glm/glm/mat4x4.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "ShaderProgram.h"
#include "Manager.h"
#include "stb_image.h"
#include "Texture2D.h"


using namespace std;

GLfloat triangle[] = {
	 0.5f,  0.5f, 0.0f,
	 0.2f, 0.3f, 0.0f,
	0.2f, 0.8f, 0.0f
};

GLfloat vertices2[] = {

	1.0f,  1.0f,  0.0f,
	1.0f, -1.0f,  0.0f,
	0.6f,  1.0f,  0.0f,
	0.6f, -1.0f,  0.0f

};
GLfloat texture[] = {

	1.0f,  1.0f,
	1.0f,  0.0f,
	0.0f,  1.0f,
	0.0f,  0.0f

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

	auto tex = manager.loadTexture("DefaultTexture", "resource/wall.jpg");

	



	{
		GLuint VBO[7], VAO[7], EBO;
		glGenVertexArrays(7, VAO);
		glGenBuffers(7, VBO); //create
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); //type
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW); //put data in buffer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(VAO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]); //type
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW); //put data in buffer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[6]); //type
		glBufferData(GL_ARRAY_BUFFER, sizeof(texture), texture, GL_STATIC_DRAW); //put data in buffer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);


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
			pGreenShaderProgram->setInt("tex", 0);
			glBindVertexArray(VAO[1]);
			tex->bind();
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glBindVertexArray(0);


			pOrangeShaderProgram->use();
			glBindVertexArray(VAO[2]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			/*pOrangeShaderProgram->use();

			glm::mat4 modelMatrix_1 = glm::mat4(1.f); //единичная матрица
			//using glm add to it moving
			modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(0.5f*200.f, 200.f, 0.f));//object->world space
			//опускаем view matrix тк камера неподвижна и матрица будет единичной с центром (0,0,0)
			modelMatrix_1 = glm::rotate(modelMatrix_1, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.f));
			
			glm::mat4 modelMatrix_2 = glm::mat4(1.f);
			modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(400.f, 300.f, 0.f));
			modelMatrix_2 = glm::rotate(modelMatrix_2, (float)tan(glfwGetTime()), glm::vec3(0.f, 0.f, 1.f));
			modelMatrix_2 = glm::scale(modelMatrix_2, glm::vec3((float)sin(glfwGetTime()), (float)sin(glfwGetTime()), 1.f));

			glm::mat4 projectionMatrix = glm::ortho(0.f, 800.f, 0.f, 600.f, -100.f, 100.f);//clip space
			//передаем в вертексный шейдер и перемножаем с вектором координат и подаем на выход шейдера
			pOrangeShaderProgram->setMatrix4("projectionMat", projectionMatrix);
						
			glBindVertexArray(VAO[0]);
			pOrangeShaderProgram->setMatrix4("modelMat", modelMatrix_1);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			pOrangeShaderProgram->setMatrix4("modelMat", modelMatrix_2);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);*/
			

			

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	//glfwSwapBuffers will swap the color buffer that is used to render to during 
	//this render iteration and show it as output to the screen.
	//glfwPollEvents function checks if any events are triggered, updates the 
	//window state, and calls the corresponding functions



		glDeleteBuffers(7, VAO);
		glDeleteBuffers(7, VBO);
		glDeleteBuffers(1, &EBO);
	}
	glfwTerminate();
	return 0;
	
}