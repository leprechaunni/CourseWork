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

GLfloat point_an[] = {
	//vertices			//colors
	0.f, 0.f, 0.0f,		1.f, 0.f, 0.f
};

GLfloat line_an[] = {
	-0.2f, 0.f, 0.0f,		1.0f, 1.0f, 0.f,
	 0.2f, 0.f, 0.0f,		0.f, 0.f, 1.f
};

GLfloat square_an[] = {
	-0.3f, -0.3f, 0.0f,
	-0.3f,  0.3f, 0.0f,
	 0.3f,  0.3f, 0.f,
	 0.3f, -0.3f, 0.f
};

GLfloat triangle_an[] = {
	-0.15f, -0.1f, 0.f,
	 0.15f, -0.1f, 0.f,
	 0.0f,   0.2f, 0.f
};

GLfloat romb_an[] = {
	-0.3f, 0.f,  0.f,
	 0.f,  0.2f, 0.f,
	 0.3f, 0.f,  0.f,
	 0.f, -0.2f, 0.f
};

GLfloat polygon_an[] = {
	-0.3f,  0.0f, 0.f,
	 0.0f,  0.3f, 0.f,
	 0.3f,  0.0f, 0.f,
	 0.2f, -0.3f, 0.f,
	-0.2f, -0.3f, 0.f
};


GLfloat texture[] = {

	0.f,  1.0f,
	1.0f, 1.0f,
	1.f,  0.0f,
	0.f,  0.f

};


float m_rotate = 0;
float m_left_right = 0;
float m_up_down = 0;
float m_sizex = 1;
float m_sizey = 1;
int m_change = 0;
int m_color;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		m_rotate+=glm::radians(0.1f);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		m_rotate -= glm::radians(0.1f);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_left_right -=0.001f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_left_right +=0.001f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_up_down += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_up_down -= 0.001f;

	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		m_sizex += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
		m_sizex -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_KP_DIVIDE) == GLFW_PRESS)
		m_sizey += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_KP_MULTIPLY) == GLFW_PRESS)
		m_sizey -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_sizex = 1;
		m_sizey = 1;
	}

	if (glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS)
		m_change = 1;
	if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
		m_change = 2;
	if (glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_PRESS)
		m_change = 3;
	if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
		m_change = 4;
	if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS)
		m_change = 5;
	if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
		m_change = 6;

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		m_color = 1;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		m_color = 2;
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		m_color = 3;
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		m_color = 4;
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		m_color = 5;
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		m_color = 6;
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
		m_color = 7;
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
		m_color = 8;
	//if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
		//m_color = 9;

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
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "My Title", NULL, NULL);
	//GLFWwindow* window = glfwCreateWindow(1600, 900, "My Title", glfwGetPrimaryMonitor(), NULL);
	//to create a full screen window
	if (window == NULL) 
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate(); 
		
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	

	Manager manager(argv[0]);
	
	auto pRedShaderProgram_an = manager.loadShaders("pRed_an", "resource/vertex_animation.txt", "resource/fragment_red.txt");
	if (!pRedShaderProgram_an)
	{
		cerr << "cant create shader program: " << "pRed_an" << endl;
		return -1;
	}


	auto pOrangeShaderProgram_an = manager.loadShaders("pOrange_an", "resource/vertex_animation.txt", "resource/fragment_orange.txt");
	if (!pOrangeShaderProgram_an)
	{
		cerr << "cant create shader program: " << "pOrange_an" << endl;
		return -1;
	}


	auto pYellowShaderProgram_an = manager.loadShaders("pYellow_an", "resource/vertex_animation.txt", "resource/fragment_yellow.txt");
	if (!pYellowShaderProgram_an)
	{
		cerr << "cant create shader program: " << "pYellow_an" << endl;
		return -1;
	}


	auto pGreenShaderProgram_an = manager.loadShaders("pGreen_an", "resource/vertex_animation.txt", "resource/fragment_green.txt");
	if (!pGreenShaderProgram_an)
	{
		cerr << "cant create shader program: " << "pGreen_an" << endl;
		return -1;
	}


	auto pCyanShaderProgram_an = manager.loadShaders("pCyan_an", "resource/vertex_animation.txt", "resource/fragment_cyan.txt");
	if (!pCyanShaderProgram_an)
	{
		cerr << "cant create shader program: " << "pCyan_an" << endl;
		return -1;
	}


	auto pBlueShaderProgram_an = manager.loadShaders("pBlue_an", "resource/vertex_animation.txt", "resource/fragment_blue.txt");
	if (!pBlueShaderProgram_an)
	{
		cerr << "cant create shader program: " << "pBlue_an" << endl;
		return -1;
	}


	auto pPurpleShaderProgram_an = manager.loadShaders("pPurple_an", "resource/vertex_animation.txt", "resource/fragment_purple.txt");
	if (!pPurpleShaderProgram_an)
	{
		cerr << "cant create shader program: " << "pPurple_an" << endl;
		return -1;
	}


	auto pColShaderProgram_an = manager.loadShaders("pCol_an", "resource/vertex_animation.txt", "resource/fragment_pCol.txt");
	if (!pColShaderProgram_an)
	{
		cerr << "cant create shader program: " << "pCol_an" << endl;
		return -1;
	}


	auto pLightShaderProgram_an = manager.loadShaders("pLight", "resource/vertex_animation.txt", "resource/fragment_light.txt");
	if (!pLightShaderProgram_an)
	{
		cerr << "cant create shader program: " << "pLight" << endl;
		return -1;
	}


	auto pTextureShaderProgram_an = manager.loadShaders("texture_an", "resource/vertex_animation.txt", "resource/fragment_texture.txt");
	if (!pTextureShaderProgram_an)
	{
		cerr << "cant create shader program: " << "texture_an" << endl;
		return -1;
	}
	auto tex = manager.loadTexture("WallTexture", "resource/wall.jpg");

	{
		GLuint VBO[8], VAO[7];
		glGenVertexArrays(7, VAO);
		glGenBuffers(8, VBO); //create
		

		//point
		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); //type
		glBufferData(GL_ARRAY_BUFFER, sizeof(point_an), point_an, GL_STATIC_DRAW); //put data in buffer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		//line
		glBindVertexArray(VAO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]); //type
		glBufferData(GL_ARRAY_BUFFER, sizeof(line_an), line_an, GL_STATIC_DRAW); //put data in buffer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		//square 
		glBindVertexArray(VAO[2]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);//vertices
		glBufferData(GL_ARRAY_BUFFER, sizeof(square_an), square_an, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);//texture
		glBufferData(GL_ARRAY_BUFFER, sizeof(texture), texture, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(2);

		//triangle
		glBindVertexArray(VAO[3]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[4]); 
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_an), triangle_an, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		//romb
		glBindVertexArray(VAO[4]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(romb_an), romb_an, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		//polygon
		glBindVertexArray(VAO[5]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[6]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_an), polygon_an, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		

		while (!glfwWindowShouldClose(window))
		{
			processInput(window);
			//glfwSetKeyCallback(window, key_callback);

			glClearColor(0.7f, 0.4f, 0.7f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);


		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //karkas regim
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			
			glm::mat4 projectionMatrix = glm::ortho(-1.f, 1.f, -1.f, 1.f, -100.f, 100.f);//clip space
			//передаем в вертексный шейдер и перемножаем с вектором координат и подаем на выход шейдера

			
			if (m_color == 1) pRedShaderProgram_an->use();
			if (m_color == 2) pOrangeShaderProgram_an->use();
			if (m_color == 3) pYellowShaderProgram_an->use();
			if (m_color == 4) pGreenShaderProgram_an->use();
			if (m_color == 5) pCyanShaderProgram_an->use();
			if (m_color == 6) pBlueShaderProgram_an->use();
			if (m_color == 7) pPurpleShaderProgram_an->use();
			if (m_color == 8) pLightShaderProgram_an->use();
			//if (m_color == 9) pColShaderProgram_an->use();

			float timeValue = glfwGetTime();
			float redValue = (sin(timeValue) / 1.5f) + 1.0f;
			float greenValue = (cos(timeValue) / 2.0f) + 0.5f;
			float blueValue = (sin(timeValue)) + 0.5f;
			int vertexColorLocation = glGetUniformLocation(pLightShaderProgram_an->m_ID, "ourColor");
			glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);

			glm::mat4 polygon = glm::mat4(1.f); //единичная матрица
			//using glm add to it moving
			polygon = glm::translate(polygon, glm::vec3(m_left_right, m_up_down, 0.f));//object->world space
			//опускаем view matrix тк камера неподвижна и матрица будет единичной с центром (0,0,0)
			polygon = glm::rotate(polygon, m_rotate, glm::vec3(0.0f, 0.0f, 1.f));
			polygon = glm::scale(polygon, glm::vec3(m_sizex, m_sizey, 1.f));

			glPointSize(m_sizex);
			glm::mat4 point = glm::mat4(1.f);
			point = glm::translate(point, glm::vec3(m_left_right, m_up_down, 0.f));
			point = glm::rotate(point, m_rotate, glm::vec3(0.f, 0.f, 1.f));
			
			
			glLineWidth(10.f);
			glm::mat4 line = glm::mat4(1.f);
			line = glm::translate(line, glm::vec3(m_left_right, m_up_down, 0.f));
			line = glm::rotate(line, m_rotate, glm::vec3(0.f, 0.f, 1.f));
			line = glm::scale(line, glm::vec3(m_sizex, m_sizey, 1.f));

			//pTextureShaderProgram_an->use();
			//pTextureShaderProgram_an->setInt("tex", 0);
			//tex->bind();

			glm::mat4 square = glm::mat4(1.f);
			square = glm::translate(square, glm::vec3(m_left_right, m_up_down, 0.f));
			square = glm::rotate(square, m_rotate, glm::vec3(0.f, 0.f, 1.f));
			square = glm::scale(square, glm::vec3(m_sizex, m_sizey, 1.f));

			
			glm::mat4 triangle = glm::mat4(1.f);
			triangle = glm::translate(triangle, glm::vec3(m_left_right, m_up_down, 0.f));
			triangle = glm::rotate(triangle, m_rotate, glm::vec3(0.f, 0.f, 1.f));
			triangle = glm::scale(triangle, glm::vec3(m_sizex, m_sizey, 1.f));

			glm::mat4 romb = glm::mat4(1.f);
			romb = glm::translate(romb, glm::vec3(m_left_right, m_up_down, 0.f));
			romb = glm::rotate(romb, m_rotate, glm::vec3(0.f, 0.f, 1.f));
			romb = glm::scale(romb, glm::vec3(m_sizex, m_sizey, 1.f));
			
						

			pPurpleShaderProgram_an->setMatrix4("projectionMat", projectionMatrix);

			if (m_change == 1)
			{
				glBindVertexArray(VAO[0]);
				pPurpleShaderProgram_an->setMatrix4("modelMat", point);
				glDrawArrays(GL_POINTS, 0, 1);
			}
			if (m_change == 2)
			{
				glBindVertexArray(VAO[1]);
				pPurpleShaderProgram_an->setMatrix4("modelMat", line);
				glDrawArrays(GL_LINES, 0, 2);
			}
			if (m_change == 3)
			{
				glBindVertexArray(VAO[3]);
				pPurpleShaderProgram_an->setMatrix4("modelMat", triangle);
				glDrawArrays(GL_TRIANGLES, 0, 3);
			}
			if (m_change == 4)
			{
				glBindVertexArray(VAO[2]);
				pPurpleShaderProgram_an->setMatrix4("modelMat", square);
				glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			}
			if (m_change == 5)
			{
				glBindVertexArray(VAO[4]);
				pPurpleShaderProgram_an->setMatrix4("modelMat", romb);
				glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			}
			if (m_change == 6)
			{
				glBindVertexArray(VAO[5]);
				pPurpleShaderProgram_an->setMatrix4("modelMat", polygon);
				glDrawArrays(GL_TRIANGLE_FAN, 0, 5);
			}
			

			glBindVertexArray(0);
			
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glDeleteBuffers(7, VAO);
		glDeleteBuffers(8, VBO);
	}
	glfwTerminate();
	return 0;
	
}