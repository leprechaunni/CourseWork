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

//задание координат вершин и цвета
GLfloat point_an[] = {
	//vertices			//colors
	0.f, 0.f, 0.0f
};

GLfloat line_an[] = {
	-0.5f, 0.f, 0.0f,
	 0.5f, 0.f, 0.0f
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

GLfloat background[] = {
	-1.f, 1.f, 0.f,		0.f, 0.f, 0.f,
	-0.6f, 1.f, 0.f,	0.f, 0.f, 0.f,
	-0.6f, -1.f, 0.f,	0.f, 0.f, 0.f,
	-1.f, -1.f, 0.f,	0.f, 0.f, 0.f
};


GLfloat square_col_r[] = {
	-0.9f, 0.9f, 0.0f,		1.0f, 0.f, 0.f,
	-0.9f,  0.8f, 0.0f,		1.0f, 0.f, 0.f,
	 -0.8f,  0.8f, 0.f,		1.0f, 0.f, 0.f,
	 -0.8f, 0.9f, 0.f,		1.0f, 0.f, 0.f
};

GLfloat square_col_o[] = {
	-0.7f, 0.9f, 0.0f,		1.0f, 0.5f, 0.f,
	-0.7f, 0.8f, 0.0f,		1.0f, 0.5f, 0.f,
	-0.6f, 0.8f, 0.f,		1.0f, 0.5f, 0.f,
	-0.6f, 0.9f, 0.f,		1.0f, 0.5f, 0.f
};

GLfloat square_col_y[] = {
	-0.5f, 0.9f, 0.0f,		1.0f, 1.f, 0.f,
	-0.5f, 0.8f, 0.0f,		1.0f, 1.f, 0.f,
	-0.4f, 0.8f, 0.f,		1.0f, 1.f, 0.f,
	-0.4f, 0.9f, 0.f,		1.0f, 1.f, 0.f
};

GLfloat square_col_g[] = {
	-0.3f, 0.9f, 0.0f,		0.0f, 1.f, 0.f,
	-0.3f, 0.8f, 0.0f,		0.0f, 1.f, 0.f,
	-0.2f, 0.8f, 0.f,		0.0f, 1.f, 0.f,
	-0.2f, 0.9f, 0.f,		0.0f, 1.f, 0.f
};

GLfloat square_col_c[] = {
	-0.1f, 0.9f, 0.0f,		0.0f, 0.5f, 1.f,
	-0.1f, 0.8f, 0.0f,		0.0f, 0.5f, 1.f,
	 0.f,  0.8f, 0.f,		0.0f, 0.5f, 1.f,
	 0.f,  0.9f, 0.f,		0.0f, 0.5f, 1.f
};

GLfloat square_col_b[] = {
	0.1f, 0.9f, 0.0f,		0.0f, 0.f, 1.f,
	0.1f, 0.8f, 0.0f,		0.0f, 0.f, 1.f,
	0.2f, 0.8f, 0.f,		0.0f, 0.f, 1.f,
	0.2f, 0.9f, 0.f,		0.0f, 0.f, 1.f
};

GLfloat square_col_p[] = {
	0.3f, 0.9f, 0.0f,		1.0f, 0.f, 1.f,
	0.3f, 0.8f, 0.0f,		1.0f, 0.f, 1.f,
	0.4f, 0.8f, 0.f,		1.0f, 0.f, 1.f,
	0.4f, 0.9f, 0.f,		1.0f, 0.f, 1.f
};

GLfloat point_sh[] = {
	//vertices			//colors
	-0.87f, 0.63f, 0.0f,		1.f, 1.f, 1.f,
	-0.87f, 0.68f, 0.f,		1.f, 1.f, 1.f,
	-0.83f, 0.68f, 0.f,		1.f, 1.f, 1.f,
	-0.83f, 0.63f, 0.f,		1.f, 1.f, 1.f
};

GLfloat line_sh[] = {
	-0.95f, 0.5f, 0.0f,		1.0f, 1.0f, 1.f,
	-0.75f, 0.5f, 0.0f,		1.f, 1.f, 1.f
};

GLfloat triangle_sh[] =
{
	-0.92f, 0.25f, 0.f,		1.f, 1.f, 1.f,
	-0.78f, 0.25f, 0.f,		1.f, 1.f, 1.f,
	-0.85f, 0.4f, 0.f,		1.f, 1.f, 1.f
};

GLfloat square_sh[] = {
	-0.92f, 0.2f, 0.0f,		1.f, 1.f, 1.f,
	-0.92f, 0.05f, 0.f,		1.f, 1.f, 1.f,
	-0.78f, 0.05f, 0.f,		1.f, 1.f, 1.f,
	-0.78f, 0.2f, 0.f,		1.f, 1.f, 1.f
};

GLfloat romb_sh[] = {
	-0.95f, -0.1f, 0.f,		1.f, 1.f, 1.f,
	-0.85f, -0.2f, 0.f,		1.f, 1.f, 1.f,
	-0.75f, -0.1f, 0.f,		1.f, 1.f, 1.f,
	-0.85f,  0.0f, 0.f,		1.f, 1.f, 1.f
};

GLfloat polygon_sh[] = {
	-0.95f, -0.35f, 0.f,		1.f, 1.f, 1.f,
	-0.85f, -0.27f, 0.f,		1.f, 1.f, 1.f,
	-0.75f, -0.35f, 0.f,		1.f, 1.f, 1.f,
	-0.8f,  -0.45f, 0.f,		1.f, 1.f, 1.f,
	-0.9f,  -0.45f, 0.f,		1.f, 1.f, 1.f
};

GLfloat group_list1[] = {
	-0.1f, 0.3f, 0.0f,		1.f, 1.f, 1.f,
	-0.1f, 0.1f, 0.0f,		1.f, 1.f, 1.f,
	0.0f, 0.2f, 0.0f,		1.f, 1.f, 1.f
};
GLfloat group_list2[] = {
	-0.07f, 0.3f, 0.0f,		1.f, 1.f, 1.f,
	0.07f, 0.3f, 0.0f,		1.f, 1.f, 1.f,
	0.0f, 0.2f, 0.0f,		1.f, 1.f, 1.f
};
GLfloat group_list3[] = {
	0.0f, 0.2f, 0.0f,		1.f, 1.f, 1.f,
	0.1f, 0.3f, 0.0f,		1.f, 1.f, 1.f,
	0.1f, 0.1f, 0.0f,		1.f, 1.f, 1.f
};
GLfloat group_list4[] = {
	0.0f, 0.2f, 0.0f,		1.f, 1.f, 1.f,
	0.08f, 0.08f, 0.0f,		1.f, 1.f, 1.f,
	-0.08f, 0.08f, 0.0f,	1.f, 1.f, 1.f
};
GLfloat group_st[] = {
	0.0f, 0.05f, 0.0f,		1.f, 1.f, 1.f,
	0.0f, -0.4f, 0.0f,		1.f, 1.f, 1.f
};
GLfloat group_lep[] = {
	0.0f, -0.3f, 0.0f,		1.f, 1.f, 1.f,
	0.1f, -0.2f, 0.0f,		1.f, 1.f, 1.f,
	0.13f, -0.1f, 0.0f,		1.f, 1.f, 1.f,
	0.05f, -0.18f, 0.0f,	1.f, 1.f, 1.f
};


//объявление переменных для работы с выбором фигуры, изменением ее цвета, размера и формы
float m_rotate = 0;
float m_left_right = 0;
float m_up_down = 0;
float m_sizex = 1;
float m_sizey = 1;
float m_size = 1;
int m_change = 0;
int m_color;

//функция обратного вызова
//вызывается при каждом изменении размера окна, чтобы скорректировать размер области окна просмотра
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//убеждаемся, что окно просмотра соответствует новым размерам окна
	glViewport(0, 0, width, height);
}

//функция пользовательского ввода с клавиатуры
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && m_left_right >= -1.f)
		m_left_right -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && m_left_right <= 1.f)
		m_left_right += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && m_up_down <= 1.f)
		m_up_down += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && m_up_down >= -1.f)
		m_up_down -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		m_rotate += glm::radians(0.1f);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		m_rotate -= glm::radians(0.1f);

	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		m_sizex += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS && m_sizex > 0)
		m_sizex -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_KP_DIVIDE) == GLFW_PRESS)
		m_sizey += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_KP_MULTIPLY) == GLFW_PRESS && m_sizey > 0)
		m_sizey -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		m_size += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && m_size > 0)
		m_size -= 0.001f;
}

//функция определения координат курсора на экране
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
}
//объявление переменных, в которые будут записаны х и у координаты положения курсора
double xpos, ypos;

//функция пользовательского ввода с помощью мыши
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (xpos<80 && xpos > 40 && ypos>30 && ypos<60 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_color = 1;
	if (xpos < 160 && xpos > 120 && ypos > 30 && ypos < 60 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_color = 2;
	if (xpos < 240 && xpos > 200 && ypos > 30 && ypos < 60 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_color = 3;
	if (xpos < 320 && xpos > 280 && ypos > 30 && ypos < 60 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_color = 4;
	if (xpos < 400 && xpos > 360 && ypos > 30 && ypos < 60 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_color = 5;
	if (xpos < 480 && xpos > 440 && ypos > 30 && ypos < 60 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_color = 6;
	if (xpos < 560 && xpos > 520 && ypos > 30 && ypos < 60 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_color = 7;
	if (xpos < 640 && xpos > 600 && ypos > 30 && ypos < 60 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_color = 8;

	if (xpos < 70 && xpos > 49 && ypos > 95 && ypos < 112 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_change = 1;
	if (xpos < 100 && xpos > 20 && ypos > 140 && ypos < 155 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_change = 2;
	if (xpos < 88 && xpos > 32 && ypos > 180 && ypos < 225 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_change = 3;
	if (xpos < 88 && xpos > 32 && ypos > 237 && ypos < 285 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_change = 4;
	if (xpos < 100 && xpos > 20 && ypos > 300 && ypos < 360 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_change = 5;
	if (xpos < 100 && xpos > 20 && ypos > 375 && ypos < 440 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_change = 6;
	if (xpos < 82 && xpos > 35 && ypos > 458 && ypos < 543 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_change = 7;
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
	

	//инициализация библиотеки GLFW
	glfwInit(); 
	//установка минимальных необходимых параметров OpenGL	
	//указали, что будем исользовать версию 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //major
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //minor
	//указываем, что хотим явно использовать core-profile
	//чтобы не подгружать лишние для нас OpenGL-функции, 
	//предназначенные для поддержания обратной совместимости приложений
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//создаем объект window, представляющий окно приложения
	GLFWwindow* window = glfwCreateWindow(800, 600, "My Title", NULL, NULL);
	//GLFWwindow* window = glfwCreateWindow(1600, 900, "My Title", glfwGetPrimaryMonitor(), NULL);
	//to create a full screen window
	if (window == NULL) 
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate(); 
		
		return -1;
	}
	//сообщаем GLFW сделать контекст нашего окна основным контекстом в текущем потоке
	glfwMakeContextCurrent(window);

	//сообщаем GLFW, что хотим вызывать функцию framebuffer_size_callback
	//каждый раз при изменении размеров окна
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//инициализация GLAD, чтобы потом пользоваться функциями OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	//в качестве параметра передаем GLAD-функцию, 
	//которая загружает адреса указателей на OpenGL-функции
	//функция glfwGetProcAddress() 
	//самостоятельно может определить нужные для работы функции


	Manager manager(argv[0]);

	//загружаем шейдеры из текстового файла в программу
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
	auto tex = manager.loadTexture("BackgroundTexture", "image/img.jpg");

	{
		//объявление вершинного буфера и вершинного массива
		GLuint VBO[25], VAO[25];
		glGenVertexArrays(25, VAO);
		glGenBuffers(25, VBO); //create

		//menu
		//colors
		//связываем объект вершинного масива
		glBindVertexArray(VAO[6]);
		//связываем и устанавливаем вершинный буфер
		glBindBuffer(GL_ARRAY_BUFFER, VBO[6]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(square_col_r), square_col_r, GL_STATIC_DRAW);
		//1-тип буфера, в который копируем данные
		//2-размер данных в байтах, которые передаем в буфер
		//3-данные, которые хотим отправить
		//4-то, как видеокарта управляет переданными ей данными(указываются 1 раз и исп-ся много раз)
		//сообщаем OpenGL как он должен интерпретировать данные вершин
		//устанавливаем указатели вершинных атрибутов
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		//1-какой атрибут вершины хотим настроить
		//2-определяем размер вершинного атрибута
		//3-указываем тип данных
		//(vec* в GLSL состоит из значений типа с плавающей точкой)
		//4-указываем, хотим ли, чтобы данные были нормализованны
		//5-шаг. говорит о пространстве между последовательными атрибутами вершин
		//6-смещение того места, с которого начинаются данные в буфере
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		//передаем расположение вершинного атрибута в качестве аргумента
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(VAO[7]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[7]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(square_col_o), square_col_o, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(VAO[8]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[8]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(square_col_y), square_col_y, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(VAO[9]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[9]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(square_col_g), square_col_g, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(VAO[10]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[10]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(square_col_c), square_col_c, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(VAO[11]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[11]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(square_col_b), square_col_b, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(VAO[12]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[12]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(square_col_p), square_col_p, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		
		//shapes
		glBindVertexArray(VAO[13]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[13]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(point_sh), point_sh, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(VAO[14]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[14]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(line_sh), line_sh, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(VAO[15]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[15]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_sh), triangle_sh, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(VAO[16]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[16]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(square_sh), square_sh, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(VAO[17]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[17]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(romb_sh), romb_sh, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(VAO[18]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[18]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_sh), polygon_sh, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		//point
		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); //type
		glBufferData(GL_ARRAY_BUFFER, sizeof(point_an), point_an, GL_STATIC_DRAW); //put data in buffer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		//line
		glBindVertexArray(VAO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]); //type
		glBufferData(GL_ARRAY_BUFFER, sizeof(line_an), line_an, GL_STATIC_DRAW); //put data in buffer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		//square 
		glBindVertexArray(VAO[2]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);//vertices
		glBufferData(GL_ARRAY_BUFFER, sizeof(square_an), square_an, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		//triangle
		glBindVertexArray(VAO[3]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[3]); 
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_an), triangle_an, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		//romb
		glBindVertexArray(VAO[4]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(romb_an), romb_an, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		//polygon
		glBindVertexArray(VAO[5]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_an), polygon_an, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(VAO[19]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[19]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(group_list1), group_list1, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindVertexArray(VAO[20]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[20]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(group_list2), group_list2, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindVertexArray(VAO[21]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[21]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(group_list3), group_list3, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindVertexArray(VAO[22]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[22]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(group_list4), group_list4, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindVertexArray(VAO[23]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[23]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(group_st), group_st, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindVertexArray(VAO[24]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[24]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(group_lep), group_lep, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		
		//отменяем привязку вершинного буфера и вергинного массива
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		

		//цикл рендеринга
		while (!glfwWindowShouldClose(window))
		{
			//пользовательский ввод
			processInput(window);
			//glfwSetKeyCallback(window, key_callback);
			glfwSetMouseButtonCallback(window, mouse_button_callback);
			glfwGetCursorPos(window, &xpos, &ypos);

			//выполнение рендеринга
			//задаем цвет окна
			glClearColor(0.7f, 0.4f, 0.7f, 1.0f);
			//очистка буфера цвета
			glClear(GL_COLOR_BUFFER_BIT);
			//glClear() использует текущие настройки цвета
			//установленные при помощи функции glClearColor()

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //karkas regim
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


			glm::mat4 projectionMatrix = glm::ortho(-1.f, 1.f, -1.f, 1.f, -100.f, 100.f);//clip space
			//передаем в вертексный шейдер и перемножаем с вектором координат и подаем на выход шейдера

			float timeValue = glfwGetTime();
			float redValue = (sin(timeValue) / 1.5f) + 1.0f;
			float greenValue = (cos(timeValue) / 2.0f) + 0.5f;
			float blueValue = (sin(timeValue)) + 0.5f;
			int vertexColorLocation = glGetUniformLocation(pLightShaderProgram_an->m_ID, "ourColor");
			glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);

			

			//многоугольник
			glm::mat4 polygon = glm::mat4(1.f); //единичная матрица
			//using glm add to it moving
			//перемещение элемента
			polygon = glm::translate(polygon, glm::vec3(m_left_right, m_up_down, 0.f));//object->world space
			//опускаем view matrix тк камера неподвижна и матрица будет единичной с центром (0,0,0)
			//поворот элемента
			polygon = glm::rotate(polygon, m_rotate, glm::vec3(0.0f, 0.0f, 1.f));
			//масштаб элемента по оси х или у
			polygon = glm::scale(polygon, glm::vec3(m_sizex, m_sizey, 1.f));
			//масштаб элемента по оси х и у
			polygon = glm::scale(polygon, glm::vec3(m_size, m_size, 1.f));


			//точка
			//размер точки
			glPointSize(m_size);
			glm::mat4 point = glm::mat4(1.f);
			point = glm::translate(point, glm::vec3(m_left_right, m_up_down, 0.f));
			point = glm::rotate(point, m_rotate, glm::vec3(0.f, 0.f, 1.f));
			

			//прямая
			//ширина прямой
			glLineWidth(10.f);
			glm::mat4 line = glm::mat4(1.f);
			line = glm::translate(line, glm::vec3(m_left_right, m_up_down, 0.f));
			line = glm::rotate(line, m_rotate, glm::vec3(0.f, 0.f, 1.f));
			line = glm::scale(line, glm::vec3(m_sizex, m_sizey, 1.f));
			line = glm::scale(line, glm::vec3(m_size, m_size, 1.f));


			pTextureShaderProgram_an->use();
			pTextureShaderProgram_an->setInt("tex", 0);
			tex->bind();

			//квадрат
			glm::mat4 square = glm::mat4(1.f);
			square = glm::translate(square, glm::vec3(m_left_right, m_up_down, 0.f));
			square = glm::rotate(square, m_rotate, glm::vec3(0.f, 0.f, 1.f));
			square = glm::scale(square, glm::vec3(m_sizex, m_sizey, 1.f));
			square = glm::scale(square, glm::vec3(m_size, m_size, 1.f));

			
			//треугольник
			glm::mat4 triangle = glm::mat4(1.f);
			triangle = glm::translate(triangle, glm::vec3(m_left_right, m_up_down, 0.f));
			triangle = glm::rotate(triangle, m_rotate, glm::vec3(0.f, 0.f, 1.f));
			triangle = glm::scale(triangle, glm::vec3(m_sizex, m_sizey, 1.f));
			triangle = glm::scale(triangle, glm::vec3(m_size, m_size, 1.f));


			//ромб
			glm::mat4 romb = glm::mat4(1.f);
			romb = glm::translate(romb, glm::vec3(m_left_right, m_up_down, 0.f));
			romb = glm::rotate(romb, m_rotate, glm::vec3(0.f, 0.f, 1.f));
			romb = glm::scale(romb, glm::vec3(m_sizex, m_sizey, 1.f));
			romb = glm::scale(romb, glm::vec3(m_size, m_size, 1.f));


			//группа элементов
			glm::mat4 group = glm::mat4(1.f);
			group = glm::translate(group, glm::vec3(m_left_right, m_up_down, 0.f));
			group = glm::rotate(group, m_rotate, glm::vec3(0.f, 0.f, 1.f));
			group = glm::scale(group, glm::vec3(m_sizex, m_sizey, 1.f));
			group = glm::scale(group, glm::vec3(m_size, m_size, 1.f));


			pPurpleShaderProgram_an->setMatrix4("projectionMat", projectionMatrix);
			//выбор элемента
			if (m_change == 1)
			{
				//связываем нужный VAO
				glBindVertexArray(VAO[0]);
				//выбираем нужную шейдерную программму
				pPurpleShaderProgram_an->setMatrix4("modelMat", point);
				//рисуем
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
			if (m_change == 7)
			{
				glBindVertexArray(VAO[19]);
				pPurpleShaderProgram_an->setMatrix4("modelMat", group);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				glBindVertexArray(VAO[20]);
				pPurpleShaderProgram_an->setMatrix4("modelMat", group);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				glBindVertexArray(VAO[21]);
				pPurpleShaderProgram_an->setMatrix4("modelMat", group);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				glBindVertexArray(VAO[22]);
				pPurpleShaderProgram_an->setMatrix4("modelMat", group);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				glBindVertexArray(VAO[23]);
				pPurpleShaderProgram_an->setMatrix4("modelMat", group);
				glDrawArrays(GL_LINES, 0, 2);
				glBindVertexArray(VAO[24]);
				pPurpleShaderProgram_an->setMatrix4("modelMat", group);
				glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			}

			//отрисовка элементов меню
			//colors
			pColShaderProgram_an->use();
			glm::mat4 background = glm::mat4(1.f);
			background = glm::translate(background, glm::vec3(0.f, 0.f, 0.f));
			glBindVertexArray(VAO[6]);
			pColShaderProgram_an->setMatrix4("modelMat", background);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glBindVertexArray(VAO[7]);
			pColShaderProgram_an->setMatrix4("modelMat", background);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glBindVertexArray(VAO[8]);
			pColShaderProgram_an->setMatrix4("modelMat", background);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glBindVertexArray(VAO[9]);
			pColShaderProgram_an->setMatrix4("modelMat", background);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glBindVertexArray(VAO[10]);
			pColShaderProgram_an->setMatrix4("modelMat", background);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glBindVertexArray(VAO[11]);
			pColShaderProgram_an->setMatrix4("modelMat", background);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glBindVertexArray(VAO[12]);
			pColShaderProgram_an->setMatrix4("modelMat", background);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

			//shapes
			glm::mat4 background1 = glm::mat4(1.f);
			background1 = glm::translate(background1, glm::vec3(-0.85f, -0.65f, 0.f));
			background1 = glm::scale(background1, glm::vec3(-0.5f, 0.4f, 1.f));
			glBindVertexArray(VAO[19]);
			pPurpleShaderProgram_an->setMatrix4("modelMat", background1);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(VAO[20]);
			pPurpleShaderProgram_an->setMatrix4("modelMat", background1);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(VAO[21]);
			pPurpleShaderProgram_an->setMatrix4("modelMat", background1);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(VAO[22]);
			pPurpleShaderProgram_an->setMatrix4("modelMat", background1);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(VAO[23]);
			pPurpleShaderProgram_an->setMatrix4("modelMat", background1);
			glDrawArrays(GL_LINES, 0, 2);
			glBindVertexArray(VAO[24]);
			pPurpleShaderProgram_an->setMatrix4("modelMat", background1);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

			glBindVertexArray(VAO[13]);//pont
			pColShaderProgram_an->setMatrix4("modelMat", background);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glBindVertexArray(VAO[14]);//line
			pColShaderProgram_an->setMatrix4("modelMat", background);
			glDrawArrays(GL_LINES, 0, 2);
			glBindVertexArray(VAO[15]);//triangle
			pColShaderProgram_an->setMatrix4("modelMat", background);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
			glBindVertexArray(VAO[16]);//square
			pColShaderProgram_an->setMatrix4("modelMat", background);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glBindVertexArray(VAO[17]);//romb
			pColShaderProgram_an->setMatrix4("modelMat", background);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glBindVertexArray(VAO[18]);//polygon
			pColShaderProgram_an->setMatrix4("modelMat", background);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 5);

			//выбор цвета
			if (m_color == 1) pRedShaderProgram_an->use();
			if (m_color == 2) pOrangeShaderProgram_an->use();
			if (m_color == 3) pYellowShaderProgram_an->use();
			if (m_color == 4) pGreenShaderProgram_an->use();
			if (m_color == 5) pCyanShaderProgram_an->use();
			if (m_color == 6) pBlueShaderProgram_an->use();
			if (m_color == 7) pPurpleShaderProgram_an->use();
			if (m_color == 8) pTextureShaderProgram_an->use();			
			
			//освобождаем вершинный массив
			glBindVertexArray(0);
			
			//ообмен содержимым front- и back- буферов
			//отслеживание событий ввода/вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		//освобождаем ресурсы, как только они выполнили свою функцию
		glDeleteBuffers(25, VAO);
		glDeleteBuffers(25, VBO);
	}
	//завершение, освобождение всех ранее задействованных GLFW-ресурсов
	glfwTerminate();
	system("PAUSE");
	return 0;
	
}