/* Disciplina: Processamento Gr�fico
 * Alunos: Melissa Viana Kunst e Luiz Felipe Giacobbo
 * GB - Desenvolvimento de um Jogo 2D com Sprites
 */


#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <assert.h>
#include <stb_image.h>
#include <glad/glad.h> 	
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>	
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;

// Dimens�es da janela (pode ser alterado em tempo de execu��o)
const GLuint WIDTH = 800, HEIGHT = 600;
const float velMax = 0.5f, velMin = 0.1f;
const float FPS = 12.0f;
const int numlives = 3;
const int maxItems = 4;
const int spriteSheetColuns = 6, spriteSheetLines = 3;


enum sprites_states { IDLE = 1, MOVING_RIGHT, MOVING_LEFT };
enum sprites_effect { NONE, COLLECT, DENY };

//Estrutura de dados das Sprites
struct Sprite {

	GLfloat VAO;
	GLfloat textureID;
	vec3 pos;
	vec3 dimensions;
	float angle;

	int nAnimations;
	int nFrames;
	int iAnimation;
	int iFrame;
	float ds, dt;

	float vel;

	vec2 PMax, PMin;
	int effect;
};

// Prot�tipo da fun��o de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Prot�tipos (ou Cabe�alhos) das fun��es
int setupShader();
int loadTexture(string filePath, int& width, int& height);

void drawSprite(GLuint shaderID, Sprite& sprite);
void updateSprite(GLuint shaderID, Sprite& sprite);
void moveSprite(GLuint shaderID, Sprite& sprite); /*Implementa a movimenta��o do personagem principal com as teclas de seta ou "A" e "D" (movimento horizontal). Cada tecla ajusta a posi��o e o estado de anima��o do personagem.*/

void updateItems(GLuint shader, Sprite& sprite);
void spawnItem(Sprite& sprite);/*Respons�vel por definir a posi��o inicial e a velocidade aleat�ria dos itens que caem. Os itens s�o reposicionados aleatoriamente no eixo X e sua velocidade � ajustada aleatoriamente.*/

void calculateAABB(Sprite& sprite);
bool checkCollision(Sprite one, Sprite two);

Sprite initializeSprite(GLuint textureID,
	vec3 dimensions,
	vec3 position,
	int effect = NONE,
	int nAnimations = 1,
	int nFrames = 1,
	float vel = 1.5f,
	float angle = 0.0);

// Vari�veis globais
bool keys[1024];
float velCharacter = velMin;
float velItems = velMin;
float lastSpawnX = 400.0;
float lastTime = 0;
int lives = numlives;
int itemsTextureID[4];


int main() {

	srand(time(0));

	for (int i = 0; i < 1024; i++) { keys[i] = false; }


	// Inicializa��o da GLFW
	glfwInit();

	// Muita aten��o aqui: alguns ambientes n�o aceitam essas configura��es
	// Voc� deve adaptar para a vers�o do OpenGL suportada por sua placa
	// Sugest�o: comente essas linhas de c�digo para desobrir a vers�o e
	// depois atualize (por exemplo: 4.5 com 4 e 5)
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

	// Essencial para computadores da Apple
	// #ifdef __APPLE__
	//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// #endif

	// Cria��o da janela GLFW

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Melissa Viana Kunst e Luiz Felipe Giacobbo - GRAU B - Processamento Grafico", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da fun��o de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d fun��es da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { cout << "Failed to initialize GLAD" << std::endl; }/*Inicializa a API OpenGL utilizando a biblioteca GLAD, garantindo compatibilidade com OpenGL 3.3 ou superior.*/

	// Obtendo as informa��es de vers�o
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Definindo as dimens�es da viewport com as mesmas dimens�es da janela da aplica��o
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Compilando e buildando o programa de shader
	GLuint shaderID = setupShader();
	glUseProgram(shaderID);

	//Cria��o dos sprites - objetos da cena
	Sprite background, character, fruit, icecube;
	vector <Sprite> items;


	int score = 0;
	bool gameover = false;
	int imgWidth, imgHeight, textureID;

	// Carregando uma textura do personagem e armazenando seu id
	textureID = loadTexture("../Textures/Backgrounds/background.png", imgWidth, imgHeight);
	background = initializeSprite(textureID, vec3(imgWidth * 0.4, imgHeight * 0.4, 1.0), vec3(400, 300, 0));

	textureID = loadTexture("../Textures/Characters/character.png", imgWidth, imgHeight);
	character = initializeSprite(textureID, vec3(imgWidth * 3.0, imgHeight * 3.0, 1.0), vec3(400, 100, 0), NONE, spriteSheetLines, spriteSheetColuns, velCharacter);

	textureID = loadTexture("../Textures/Items/fruit.png", imgWidth, imgHeight);
	fruit = initializeSprite(textureID, vec3(imgWidth * 0.1, imgHeight * 0.1, 1.0), vec3(0, 0, 0), COLLECT);

	textureID = loadTexture("../Textures/Items/icecube.png", imgWidth, imgHeight);
	icecube = initializeSprite(textureID, vec3(imgWidth * 1.5, imgHeight * 1.5, 1.0), vec3(0, 0, 0), DENY);


	for (int i = 0; i < maxItems; i++) {
		int n = rand() % 2;
		if (n == 1) { items.push_back(fruit); }
		else { items.push_back(icecube); }
		spawnItem(items[i]);
	}

	//Ativando o primeiro buffer de textura da OpenGL
	glActiveTexture(GL_TEXTURE0);

	// Enviar a informa��o de qual vari�vel armazenar� o buffer da textura
	glUniform1i(glGetUniformLocation(shaderID, "textureBuffer"), 0);

	// Matriz de proje��o paralela ortogr�fica
	mat4 projection = ortho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);/*Configura a matriz de proje��o ortogr�fica 2D para mapear o espa�o da tela e os objetos do jogo.*/
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"), 1, GL_FALSE, value_ptr(projection));

	//Habilitando o teste de profundidade
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	//Habilitando a transpar�ncia
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	character.iAnimation = IDLE; // = 1

	cout << "Score: " << score << endl;/*Exibe a pontua��o atual do jogador no terminal ap�s coletar um item.*/
	cout << "Vidas: " << lives << endl;/*Atualiza o n�mero de vidas do jogador ao colidir com itens prejudiciais. Quando as vidas chegam a 0, o jogo termina.*/

	// Loop da aplica��o - "game loop"
	while (!glfwWindowShouldClose(window) && !gameover) {

		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as fun��es de callback correspondentes
		glfwPollEvents();

		// Limpa o buffer de cor
		glClearColor(193 / 255.0f, 229 / 255.0f, 245 / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUniform2f(glGetUniformLocation(shaderID, "offsetTexture"), 0.0, 0.0);

		 // Atualiza as hitboxes e verifica colis�es
        calculateAABB(character);
        for (int i = 0; i < items.size(); i++) {
            calculateAABB(items[i]);
            if (checkCollision(character, items[i])) {
                // Atualiza pontua��o ou vidas com base no tipo de item
                if (items[i].effect == COLLECT) {
                    score++;
                    cout << "Score: " << score << endl;
                } else if (items[i].effect == DENY) {
                    lives--;
                    cout << "Vidas: " << lives << endl;
                }

                // Reposiciona o item ap�s a colis�o
                int n = rand() % 2;
                if (n == 1) { items[i] = fruit; }
                else { items[i] = icecube; }
                spawnItem(items[i]);
            }
        }

		// Renderiza os sprites na tela
		drawSprite(shaderID, background);
		moveSprite(shaderID, character);
		updateSprite(shaderID, character);
		drawSprite(shaderID, character);

		glUniform2f(glGetUniformLocation(shaderID, "offsetTexture"), 0.0, 0.0);

		// Atualiza e desenha itens
		for (int i = 0; i < items.size(); i++) {
			drawSprite(shaderID, items[i]);
			updateItems(shaderID, items[i]);
		}

		if (lives <= 0) {
			gameover = true;
			cout << "GAME OVER!" << endl;/*Implementa a l�gica de "Game Over" quando as vidas do jogador chegam a zero.*/
		}

		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	if (!glfwWindowShouldClose(window)) { glfwSetWindowShouldClose(window, GL_TRUE); }
	// Pede pra OpenGL desalocar os buffers
	//glDeleteVertexArrays(1, character.VAO);
	// Finaliza a execu��o da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { glfwSetWindowShouldClose(window, GL_TRUE); }
	if (action == GLFW_PRESS) { keys[key] = true; }
	else if (action == GLFW_RELEASE) { keys[key] = false; }
}

//  A fun��o retorna o identificador do programa de shader
int setupShader() {
	// C�digo do shader de v�rtices (Vertex Shader)
	const GLchar* vertexShaderSource = R"(
		#version 400
		layout (location = 0) in vec3 coordenadasDaGeometria;
		layout (location = 1) in vec2 coordenadasDaTextura;
		uniform mat4 projection;
		uniform mat4 model;
		out vec2 textureCoord;
		void main() {
   			gl_Position = projection * model * vec4( coordenadasDaGeometria , 1.0 );
			textureCoord = vec2( coordenadasDaTextura.s , 1.0 - coordenadasDaTextura.t );
		}
	)";

	// C�digo do shader de fragmentos (Fragment Shader)
	const GLchar* fragmentShaderSource = R"(
		#version 400
		in vec2 textureCoord;			 // inclu�do
		uniform sampler2D textureBuffer; // inclu�do
		uniform vec2 offsetTexture;		 // inclu�do
		out vec4 color;
		void main() { color = texture(textureBuffer,textureCoord + offsetTexture); }	// modificado
	)";

	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Checando erros de compila��o (exibi��o via log no terminal)
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Checando erros de compila��o (exibi��o via log no terminal)
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Linkando os shaders e criando o identificador do programa de shader
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Checando por erros de linkagem
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}

Sprite initializeSprite(GLuint textureID, vec3 dimensions, vec3 position, int effect, int nAnimations, int nFrames, float vel, float angle)
{
	Sprite sprite;
	sprite.textureID = textureID;/*Associa texturas carregadas aos sprites do jogo, permitindo o uso de imagens para representar os personagens, itens e o fundo.*/
	sprite.dimensions.x = dimensions.x / nFrames;
	sprite.dimensions.y = dimensions.y / nAnimations;
	sprite.pos = position;
	sprite.effect = effect;
	sprite.nAnimations = nAnimations;
	sprite.nFrames = nFrames;
	sprite.angle = angle;
	sprite.iFrame = 0;
	sprite.iAnimation = 0;
	sprite.vel = vel;

	sprite.ds = 1.0 / (float)nFrames;
	sprite.dt = 1.0 / (float)nAnimations;

	GLfloat vertices[] = {
		-0.5,  0.5, 0.0,    0.0,    sprite.dt,
		-0.5, -0.5, 0.0,    0.0,       0.0,
		 0.5,  0.5, 0.0, sprite.ds, sprite.dt,

		 -0.5, -0.5, 0.0,    0.0,       0.0,
		  0.5,  0.5, 0.0, sprite.ds, sprite.dt,
		  0.5, -0.5, 0.0, sprite.ds,    0.0
	};

	GLuint VBO, VAO;
	// Gera��o do identificador do VBO
	glGenBuffers(1, &VBO);/*Cria��o e configura��o do VBO para armazenar os v�rtices dos objetos do jogo.*/
	// Faz a conex�o (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Gera��o do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de v�rtices
	// e os ponteiros para os atributos
	glBindVertexArray(VAO);
	// Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo)

	//Atributo posi��o - coord x, y, z - 3 valores
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo coordenada de textura - coord s, t - 2 valores
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Observe que isso � permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de v�rtice
	// atualmente vinculado - para que depois possamos desvincular com seguran�a
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (� uma boa pr�tica desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	sprite.VAO = VAO;

	return sprite;
}

void drawSprite(GLuint shaderID, Sprite& sprite)
{
	glBindVertexArray(sprite.VAO); // Conectando ao buffer de geometria
	glBindTexture(GL_TEXTURE_2D, sprite.textureID); //conectando com o buffer de textura que ser� usado no draw

	// Matriz de modelo: transforma��es na geometria (objeto)
	mat4 model = mat4(1); // matriz identidade
	// Transla��o
	model = translate(model, sprite.pos);
	// Rota��o
	model = rotate(model, radians(sprite.angle), vec3(0.0, 0.0, 1.0));
	// Escala
	model = scale(model, sprite.dimensions);

	glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0); // Desconectando ao buffer de geometria
	glBindTexture(GL_TEXTURE_2D, 0); // Desconectando com o buffer de textura 
}



void updateSprite(GLuint shaderID, Sprite& sprite) {
	/* Atualiza a anima��o do sprite com base no tempo decorrido desde o �ltimo quadro. */

	// Incrementando o �ndice do frame apenas quando fechar a taxa de FPS desejada
	float now = glfwGetTime();

	// Calcula o tempo desde o �ltimo quadro
	float dt = now - lastTime;

	// Verifica se � hora de atualizar para o pr�ximo quadro da anima��o
	if (dt >= 1 / FPS) {
		sprite.iFrame = (sprite.iFrame + 1) % sprite.nFrames;//incrementando ciclicamente o indice do Frame
		lastTime = now; // Atualiza o tempo do �ltimo quadro
	}

	// Calcula o deslocamento na textura para exibir o quadro atual da anima��o
	vec2 offsetTexture;
	offsetTexture.s = sprite.iFrame * sprite.ds; // Deslocamento horizontal
	offsetTexture.t = sprite.iAnimation * sprite.dt; // Deslocamento vertical

	// Envia o deslocamento para o shader
	glUniform2f(glGetUniformLocation(shaderID, "offsetTexture"), offsetTexture.s, offsetTexture.t); // enviando cor para vari�vel uniform offsetTex
}




int loadTexture(string filePath, int& width, int& height) {
	/* Carrega uma textura de um arquivo e a associa a um ID de textura OpenGL. */

	// Cria e vincula a textura
	GLuint textureID; // id da textura a ser carregada

	// Gera o identificador da textura na mem�ria
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Ajuste dos par�metros de wrapping e filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 

	// Carregamento da imagem usando a fun��o stbi_load da biblioteca stb_image
	int nrChannels;
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);


	if (data) {
	
		if (nrChannels == 3) {  // jpg, bmp
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else { // assume que � 4 canais png
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		
		std::cout << "Failed to load texture " << filePath << std::endl;
	}

	
	stbi_image_free(data);

	
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID; 
}


void moveSprite(GLuint shaderID, Sprite& sprite) {
	/* Gerencia o movimento horizontal do sprite com base nas teclas pressionadas. */

	// Movimento para a esquerda
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
		sprite.pos.x -= sprite.vel; // Diminui a posi��o X
		sprite.iAnimation = MOVING_LEFT; // Define a anima��o para movimento � esquerda
	}

	// Movimento para a direita
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
		sprite.pos.x += sprite.vel; // Aumenta a posi��o X
		sprite.iAnimation = MOVING_RIGHT; // Define a anima��o para movimento � direita
	}

	// Sem movimento
	if (!keys[GLFW_KEY_A] && !keys[GLFW_KEY_D] && !keys[GLFW_KEY_LEFT] && !keys[GLFW_KEY_RIGHT]) {
		sprite.iAnimation = IDLE; // Define a anima��o para inatividade
	}
}


void spawnItem(Sprite& sprite) {
	/* Configura a posi��o inicial e a velocidade de um item de forma aleat�ria. */

	// Define os limites de posi��o no eixo X
	int max = lastSpawnX + 250;
	if (max > 790) max = 790;
	int min = lastSpawnX - 250;
	if (min < 10) min = 10;

	// Gera uma posi��o X aleat�ria dentro dos limites
	sprite.pos.x = rand() % (max - min + 1) + min;
	lastSpawnX = sprite.pos.x; // Atualiza a �ltima posi��o gerada

	// Define a posi��o Y inicial
	sprite.pos.y = 600;

	// Define a velocidade do item
	sprite.vel = velItems;
	int n = rand() % 3;
	if (n == 1) {
		sprite.vel += sprite.vel * 0.11; // Aumenta ligeiramente a velocidade
	}
	else if (n == 2) {
		sprite.vel -= sprite.vel * 0.11; // Reduz ligeiramente a velocidade
	}
}


void updateItems(GLuint shader, Sprite& sprite) {
	/* Atualiza a posi��o do item. Se o item sair da tela, ele � reposicionado. */

	// Verifica se o item ainda est� na tela
	if (sprite.pos.y > 50) {
		sprite.pos.y -= sprite.vel; // Move o item para baixo
	}
	else {
		// Reposiciona o item caso saia da tela
		spawnItem(sprite);
	}
}


void calculateAABB(Sprite& sprite) {
	/* Calcula a bounding box (AABB) do sprite para detec��o de colis�o. */

	// Coordenadas m�nimas da bounding box
	sprite.PMin.x = sprite.pos.x - sprite.dimensions.x / 2.0;
	sprite.PMin.y = sprite.pos.y - sprite.dimensions.y / 2.0;

	// Coordenadas m�ximas da bounding box
	sprite.PMax.x = sprite.pos.x + sprite.dimensions.x / 2.0;
	sprite.PMax.y = sprite.pos.y + sprite.dimensions.y / 2.0;
}


bool checkCollision(Sprite one, Sprite two) {
	/* Verifica se h� colis�o entre dois sprites usando suas bounding boxes (AABB). */

	// Verifica a interse��o no eixo X
	bool collisionX = (one.PMax.x >= two.PMin.x) && (two.PMax.x >= one.PMin.x);

	// Verifica a interse��o no eixo Y
	bool collisionY = (one.PMax.y >= two.PMin.y) && (two.PMax.y >= one.PMin.y);

	// Retorna verdadeiro se houver colis�o em ambos os eixos
	return collisionX && collisionY;
}

