//WINDOW CLASS IMPLEMENTATION FILE
#include "Window.h"

//DEFAULT CONSTRUCTOR
Window::Window() {
}

//CONSTRUCTOR w/ PARAMETERS
Window::Window(int _width, int _height, std::string _title, bool initialize) {
    width = _width;
    height = _height;
    title = _title;
    initialized = false;
	windowOpen = true;

    if(initialize)
        init();
}

//DECONSTRUCTOR
Window::~Window() {

}

//INITIALIZE
void Window::init() {

    // Initialize GLFW
	if(!glfwInit()) {
		std::cout << "GLFW Initialization failed\n";
		exit(0);
	}

    //hint settings
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if( window == NULL ){
		std::cout << "Failed to open window\n";
	}

    //other opengl settings
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
    glfwSwapInterval(0);
	
    // Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW\n";
		glfwTerminate();
		exit(0);
	}

    initialized = true;

    //TEMP
	glGenVertexArrays(1, &vertexArrayId);
	glBindVertexArray(vertexArrayId);
    programId = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );
	matrixId = glGetUniformLocation(programId, "MVP");
    projection = glm::perspective(glm::radians(45.0f), 1600.0f / 900.0f, 0.1f, 100000.0f);
	camera  = glm::lookAt(glm::vec3(0,30,-50), // Camera is at (4,3,-3), in World Space
		glm::vec3(0,0,0), // and looks at the origin
		glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	position = vec3( 5, 5, 5 );
	
}

#include <stdint.h>
#include <stddef.h>

//LOOP
//Desc. draw loop for window
void Window::draw() {

    if(!initialized)
        init();

	Vertex v1(-1.f, -1.f, 0.f, 1.f, 0.5f, 1.f);
	Vertex v2(1.f, -1.f, 0.f, 0.7f, 0.2f, 0.8f);
	Vertex v3(0.f, 1.f, 0.f, 0.3f, 0.6f, 1.f);
	
	db.addVertex(v1);
	db.addVertex(v2);
	db.addVertex(v3);
	
	Vertex v4(-10.f, -10.f, 10.f, 1.f, 0.5f, 1.f);
	Vertex v5(10.f, -10.f, 10.f, 0.7f, 0.2f, 0.8f);
	Vertex v6(10.f, 10.f, 10.f, 0.3f, 0.6f, 1.f);
	
	db.addVertex(v4);
	db.addVertex(v5);
	db.addVertex(v6);

	loadModel("car.obj", db);
	
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, db.getVertexSize(), db.getVertexData(), GL_DYNAMIC_DRAW);

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, db.getColorSize(), db.getColorData(), GL_DYNAMIC_DRAW);

	do	{


		//fps
		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();
		//printf("fps:%.0f\n",(1.0f/deltaTime));
		input();
        
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programId);

		//vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//color
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	
		//draw	
		MVP = mesh.getModelViewProjection(projection, camera);
		glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, db.getN_Vertices());
		
		//disable buffers
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		//swap and poll
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );

    close();
}

//CLOSE
void Window::close() {
    // Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteProgram(programId);
	glDeleteVertexArrays(1, &vertexArrayId);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	windowOpen = false;
	std::cout << "Window Closed\n";
}

//IS OPEN
bool Window::isOpen() {
	return windowOpen;
}

//MOUSE MOUSE MOVEMENT
void Window::input() {
		
		//forward and backwards
		if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			position += direction * moveSpeed;
		else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			position -= direction * moveSpeed;

		//left and right
		if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			position -=  glm::normalize(glm::cross(direction, glm::vec3(0, 1, 0))) * moveSpeed;

		else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			position +=  glm::normalize(glm::cross(direction, glm::vec3(0, 1, 0))) * moveSpeed;
		
		if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			
		//	for(int i=0; i<9; i++)
		//		cubeData[i] -= 1;
			//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(cubeData), cubeData, GL_DYNAMIC_DRAW);
		}else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		//	for(int i=0; i<9; i++)
		//		cubeData[i] += 1;
			//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(cubeData), cubeData, GL_DYNAMIC_DRAW);
		}
		
		
        if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            //glm::vec3 pos = cube.getPosition();
            //pos.y += 0.1f;
            //cube.setPosition(pos.x, pos.y, pos.z);
        }
	
	//free cam
    double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window, width/2, height/2);
	horizontalAngle += mouseSpeed * float(width/2 - xpos );
	verticalAngle   += mouseSpeed * float( height/2 - ypos);
	direction = glm::vec3(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
	vec3 right = vec3(sin(horizontalAngle - 3.14f/2.0f), 0, cos(horizontalAngle - 3.14f/2.0f));
	vec3 up = cross( right, direction );
    camera = lookAt(position, position+direction, up);

}

void Window::loadModel(std::string file, Drawbuffer& db) {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	bool res = loadOBJ("car.obj", vertices, uvs, normals);

	for(int i=0; i<vertices.size(); i++) {
		float r = ((double) rand() / (RAND_MAX));
		float g = ((double) rand() / (RAND_MAX));
		float b = ((double) rand() / (RAND_MAX));
 
		//std::cout << r << ' ' << g << ' ' << b << '\n';
 		Vertex v(vertices[i][0], vertices[i][1], vertices[i][2], r, g, b);
		db.addVertex(v);
	}
}

//LOAD SHADERS
GLuint Window::LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
