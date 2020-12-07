#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource_yellow = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";
const char* fragmentShaderSource_green = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";
const char* fragmentShaderSource_orange = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

GLfloat vertices1[] = {
	-0.5f, 0.5f, 0.0f,
	0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f
};

GLfloat vertices2[] = {
	1.0f, 1.0f, 0.0f,
	0.5f, 0.0f, 0.0f,
	1.0f, -1.0f, 0.0f
};

GLfloat vertices_kv[] = {
	0.5f,  0.25f, 0.0f,  //verh_r
	0.5f, -0.25f, 0.0f,  //niz_r
	0.0f, -0.25f, 0.0f,  //niz_l
	0.f,  0.25f, 0.0f   //verh_l
};

GLuint indices[] = {
	0, 1, 3,
	1, 2, 3
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

	GLuint vertexShader; //the shader object
	vertexShader = glCreateShader(GL_VERTEX_SHADER); //create, (type)
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); 
	glCompileShader(vertexShader);

	GLuint fragmentShader_yel; //the shader object
	fragmentShader_yel = glCreateShader(GL_FRAGMENT_SHADER); //create, (type)
	glShaderSource(fragmentShader_yel, 1, &fragmentShaderSource_yellow, NULL);
	glCompileShader(fragmentShader_yel);

	GLuint shaderProgram1;
	shaderProgram1 = glCreateProgram(); 
	glAttachShader(shaderProgram1, vertexShader); //put vertSh in shProg
	glAttachShader(shaderProgram1, fragmentShader_yel); //put fragSh in shProg
	glLinkProgram(shaderProgram1); //linking

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader_yel);


	GLuint fragmentShader_gr; //the shader object
	fragmentShader_gr = glCreateShader(GL_FRAGMENT_SHADER); //create, (type)
	glShaderSource(fragmentShader_gr, 1, &fragmentShaderSource_green, NULL);
	glCompileShader(fragmentShader_gr);

	GLuint shaderProgram2;
	shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader); //put vertSh in shProg
	glAttachShader(shaderProgram2, fragmentShader_gr); //put fragSh in shProg
	glLinkProgram(shaderProgram2); //linking

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader_gr);


	GLuint fragmentShader_or; //the shader object
	fragmentShader_or = glCreateShader(GL_FRAGMENT_SHADER); //create, (type)
	glShaderSource(fragmentShader_or, 1, &fragmentShaderSource_orange, NULL);
	glCompileShader(fragmentShader_or);

	GLuint shaderProgram3;
	shaderProgram3 = glCreateProgram();
	glAttachShader(shaderProgram3, vertexShader); //put vertSh in shProg
	glAttachShader(shaderProgram3, fragmentShader_or); //put fragSh in shProg
	glLinkProgram(shaderProgram3); //linking

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader_or);

	
	
	GLuint VBO[3], VAO[3], EBO;
	glGenVertexArrays(3, VAO);
	glGenBuffers(3, VBO); //create
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	


	/*int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	*/

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

		glUseProgram(shaderProgram1);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		
		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0); 

		glUseProgram(shaderProgram3);
		glBindVertexArray(VAO[2]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//glfwSwapBuffers will swap the color buffer that is used to render to during 
	//this render iteration and show it as output to the screen.
	//glfwPollEvents function checks if any events are triggered, updates the 
	//window state, and calls the corresponding functions

	
	glDeleteBuffers(3, VAO);
	glDeleteBuffers(3, VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram1);
	glDeleteProgram(shaderProgram2);
	glDeleteProgram(shaderProgram3);
	glfwTerminate();
	return 0;
	
}