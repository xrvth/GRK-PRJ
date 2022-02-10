#include "glew.h"
#include "freeglut.h"
#include "glm.hpp"
#include "ext.hpp"
#include <iostream>
#include <cmath>

#include "Shader_Loader.h"
#include "Render_Utils.h"
#include "Camera.h"
#include "Texture.h"

GLuint programColor;
GLuint programTexture;
GLuint texture_coral1;
GLuint texture_turtl;
GLuint texture_shell;
GLuint texture_terrain;
GLuint texture_fish;
GLuint texture_coral2;
GLuint octo_texture;
GLuint puff_texture;
GLuint shel_texture;


Core::Shader_Loader shaderLoader;

obj::Model shipModel;
obj::Model sphereModel;
obj::Model spherModel;
obj::Model shellModel;
obj::Model terrainModel;
obj::Model fogModel;
obj::Model fishModel;
obj::Model coral2Model;
obj::Model octoModel;
obj::Model puffModel;

float cameraAngle = 0;
glm::vec3 cameraPos = glm::vec3(-5, 0, 0);
glm::vec3 cameraDir;

glm::mat4 cameraMatrix, perspectiveMatrix;

glm::vec3 lightDir = glm::normalize(glm::vec3(1.0f, -0.9f, -1.0f));

void keyboard(unsigned char key, int x, int y)
{
	float angleSpeed = 0.1f;
	float moveSpeed = 0.1f;
	switch(key)
	{
	case 'z': cameraAngle -= angleSpeed; break;
	case 'x': cameraAngle += angleSpeed; break;
	case 'w': cameraPos += cameraDir * moveSpeed; break;
	case 's': cameraPos -= cameraDir * moveSpeed; break;
	case 'd': cameraPos += glm::cross(cameraDir, glm::vec3(0,1,0)) * moveSpeed; break;
	case 'a': cameraPos -= glm::cross(cameraDir, glm::vec3(0,1,0)) * moveSpeed; break;
	}
}

glm::mat4 createCameraMatrix()
{
	// Computation of camera basis vectors.
	cameraDir = glm::vec3(cosf(cameraAngle), 0.0f, sinf(cameraAngle));
	glm::vec3 up = glm::vec3(0,1,0);

	return Core::createViewMatrix(cameraPos, cameraDir, up);
}

void drawObjectColor(obj::Model * model, glm::mat4 modelMatrix, glm::vec3 color)
{
	GLuint program = programColor;

	glUseProgram(program);

	glUniform3f(glGetUniformLocation(program, "objectColor"), color.x, color.y, color.z);
	glUniform3f(glGetUniformLocation(program, "lightDir"), lightDir.x, lightDir.y, lightDir.z);

	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);

	Core::DrawModel(model);

	glUseProgram(0);
}


void drawObjectTexture(obj::Model * model, glm::mat4 modelMatrix, GLuint texture)
{
	GLuint program = programTexture;

	glUseProgram(program);

	Core::SetActiveTexture(texture, "tex", program, 0);
	glUniform3f(glGetUniformLocation(program, "lightDir"), lightDir.x, lightDir.y, lightDir.z);

	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);

	Core::DrawModel(model);

	glUseProgram(0);
}

void renderScene()
{
	// Update of camera and perspective matrices
	cameraMatrix = createCameraMatrix();
	perspectiveMatrix = Core::createPerspectiveMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.5f, 1.0f, 0.5f);


	//glm::mat4 rotate = glm::translate(cameraPos + cameraDir * 0.5f + glm::vec3(1, -2, -1)) * glm::rotate(-cameraAngle + glm::radians(90.0f), glm::vec3(0, 1, 0)) * glm::scale(glm::vec3(0.1f));


	glm::mat4 shipModelMatrix = glm::translate(cameraPos + cameraDir * 0.5f + glm::vec3(0,-1.0f,0)) * glm::rotate(-cameraAngle + glm::radians(90.0f), glm::vec3(-5,-2,2)) * glm::scale(glm::vec3(0.017f));
	drawObjectTexture(&shipModel, shipModelMatrix, texture_turtl);

	glm::mat4 rotate = glm::translate(glm::vec3(20, -5, 20)) * glm::rotate(-cameraAngle + glm::radians(90.0f), glm::vec3(0, -4, 0)) * glm::scale(glm::vec3(0.25f));

	glm::mat4 rotate2 = glm::translate(glm::vec3(2, -4, -3)) * glm::rotate(-cameraAngle + glm::radians(90.0f), glm::vec3(-5, 1, 0)) * glm::scale(glm::vec3(0.15f));
	glm::mat4 rotate3 = glm::translate(glm::vec3(20, -4, 7)) * glm::rotate(-cameraAngle + glm::radians(90.0f), glm::vec3(-5, 1, 0)) * glm::scale(glm::vec3(0.17f));

	glm::mat4 rotate4 = glm::translate(glm::vec3(17, -4, 3)) * glm::rotate(-cameraAngle + glm::radians(90.0f), glm::vec3(-5, 1, 0)) * glm::scale(glm::vec3(0.05f));

	glm::mat4 rotate5 = glm::translate(glm::vec3(17, -2, 3)) * glm::rotate(-cameraAngle + glm::radians(45.0f), glm::vec3(-5, 1, -5)) * glm::scale(glm::vec3(0.05f));
	glm::mat4 rotate5_1 = glm::translate(glm::vec3(18, 0, 4)) * glm::rotate(-cameraAngle + glm::radians(45.0f), glm::vec3(-5, 1, -5)) * glm::scale(glm::vec3(0.05f));
	glm::mat4 rotate5_2 = glm::translate(glm::vec3(13, -2, 6)) * glm::rotate(-cameraAngle + glm::radians(45.0f), glm::vec3(-5, 1, -5)) * glm::scale(glm::vec3(0.05f));
	glm::mat4 rotate5_3 = glm::translate(glm::vec3(14, 2, 2)) * glm::rotate(-cameraAngle + glm::radians(45.0f), glm::vec3(-5, 1, -5)) * glm::scale(glm::vec3(0.05f));
	glm::mat4 rotate5_4 = glm::translate(glm::vec3(19, -3, 1)) * glm::rotate(-cameraAngle + glm::radians(45.0f), glm::vec3(-5, 1, -5)) * glm::scale(glm::vec3(0.05f));

	glm::mat4 rotate6 = glm::translate(glm::vec3(2, -2, -3)) * glm::rotate(cameraAngle + glm::radians(0.0f), glm::vec3(5, 1, 5)) * glm::scale(glm::vec3(0.05f));
	//glm::mat4 rotate6_1 = glm::translate(glm::vec3(18, 0, 4)) * glm::rotate(-cameraAngle + glm::radians(180.0f), glm::vec3(-5, 1, -5)) * glm::scale(glm::vec3(0.05f));
	//glm::mat4 rotate6_2 = glm::translate(glm::vec3(13, -2, 6)) * glm::rotate(-cameraAngle + glm::radians(180.0f), glm::vec3(-5, 1, -5)) * glm::scale(glm::vec3(0.05f));
	//glm::mat4 rotate6_3 = glm::translate(glm::vec3(14, 2, 2)) * glm::rotate(-cameraAngle + glm::radians(180.0f), glm::vec3(-5, 1, -5)) * glm::scale(glm::vec3(0.05f));
	//glm::mat4 rotate6_4 = glm::translate(glm::vec3(19, -3, 1)) * glm::rotate(-cameraAngle + glm::radians(180.0f), glm::vec3(-5, 1, -5)) * glm::scale(glm::vec3(0.05f));

	glm::mat4 rotate7 = glm::translate(glm::vec3(10, 10, -8)) * glm::rotate(-cameraAngle + glm::radians(90.0f), glm::vec3(-10, 30, 20)) * glm::scale(glm::vec3(1.2f));

	glm::mat4 rotate8 = glm::translate(glm::vec3(20, 12, 8)) * glm::rotate(-cameraAngle + glm::radians(90.0f), glm::vec3(-10, 30, 20)) * glm::scale(glm::vec3(0.08f));

	glm::mat4 rotate9 = glm::translate(glm::vec3(50, -4, -17)) * glm::rotate(-cameraAngle + glm::radians(90.0f), glm::vec3(-10, 30, 20)) * glm::scale(glm::vec3(4.0f));
	glm::mat4 rotate9_1 = glm::translate(glm::vec3(30, -4, 17)) * glm::rotate(-cameraAngle + glm::radians(180.0f), glm::vec3(-10, 30, 20)) * glm::scale(glm::vec3(2.0f));
	glm::mat4 rotate9_2 = glm::translate(glm::vec3(27, 10, -14)) * glm::rotate(-cameraAngle + glm::radians(45.0f), glm::vec3(-5, 1, -5)) * glm::scale(glm::vec3(0.1f));
	glm::mat4 rotate9_3 = glm::translate(glm::vec3(31, 9, -10)) * glm::rotate(-cameraAngle + glm::radians(45.0f), glm::vec3(-5, 1, -5)) * glm::scale(glm::vec3(0.1f));
	glm::mat4 rotate9_4 = glm::translate(glm::vec3(24, 11, -16)) * glm::rotate(-cameraAngle + glm::radians(45.0f), glm::vec3(-5, 1, -5)) * glm::scale(glm::vec3(0.1f));

	//glm::mat4 rotate10 = glm::translate(glm::vec3(30, -4, -17)) * glm::rotate(-cameraAngle + glm::radians(90.0f), glm::vec3(-10, 30, 20)) * glm::scale(glm::vec3(0.5f));

	//drawObjectTexture(&sphereModel, glm::translate(glm::vec3(2,0,-5)), texture);
	drawObjectTexture(&terrainModel, rotate, texture_terrain);
	drawObjectTexture(&spherModel, rotate2, texture_coral1);
	drawObjectTexture(&spherModel, rotate3, texture_coral1);
	drawObjectTexture(&octoModel, rotate7, octo_texture);
	//drawObjectTexture(&spherModel, rotate, texture_coral1);

	//drawObjectTexture(&shellModel, rotate4, texture_coral1);

	//drawObjectTexture(&shellModel, rotate4, texture_shell);

	drawObjectTexture(&fishModel, rotate5, texture_fish);
	drawObjectTexture(&fishModel, rotate5_1, texture_fish);
	drawObjectTexture(&fishModel, rotate5_2, texture_shell);
	drawObjectTexture(&fishModel, rotate5_3, texture_fish);
	drawObjectTexture(&fishModel, rotate5_4, texture_fish);

	drawObjectTexture(&fishModel, rotate6, texture_fish);

	drawObjectTexture(&puffModel, rotate8, puff_texture);

	drawObjectTexture(&coral2Model, rotate9, texture_coral2);
	drawObjectTexture(&coral2Model, rotate9_1, texture_coral2);

	drawObjectTexture(&fishModel, rotate9_2, texture_shell);
	drawObjectTexture(&fishModel, rotate9_3, texture_fish);
	drawObjectTexture(&fishModel, rotate9_4, texture_shell);

	//drawObjectTexture(&shellModel, rotate10, shel_texture);
	
	glutSwapBuffers();
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	programColor = shaderLoader.CreateProgram("shaders/shader_color.vert", "shaders/shader_color.frag");
	programTexture = shaderLoader.CreateProgram("shaders/shader_tex.vert", "shaders/shader_tex.frag");
	texture_coral1 = Core::LoadTexture("textures/coral.png");
	texture_shell = Core::LoadTexture("textures/CalidiousDesert_diffuse.png");
	texture_turtl = Core::LoadTexture("textures/Turtle_SG_albedo.png");
	spherModel = obj::loadModelFromFile("models/coral.obj");
	coral2Model = obj::loadModelFromFile("models/tree_coral.obj");
	texture_coral2 = Core::LoadTexture("textures/images.png");
	shipModel = obj::loadModelFromFile("models/turtl2.obj");
	//shellModel = obj::loadModelFromFile("models/coralfish.obj");
	terrainModel = obj::loadModelFromFile("models/seashell_obj.obj");
	//terrainModel = obj::loadModelFromFile("models/mountains.obj");
	texture_terrain = Core::LoadTexture("textures/Mars__Land5_D.png");
	//fogModel = obj::loadModelFromFile("models/clouds.obj");
	fishModel = obj::loadModelFromFile("models/fishie.obj");
	texture_fish = Core::LoadTexture("textures/coralfish_texture.png");
	octoModel = obj::loadModelFromFile("models/Jellyfish_001.obj");
	octo_texture = Core::LoadTexture("textures/Jellyfish_001_tex.png");
	puffModel = obj::loadModelFromFile("models/cuttle.obj");
	puff_texture = Core::LoadTexture("textures/texture.png");
	//shellModel = obj::loadModelFromFile("models/Stone.obj");
	//shel_texture = Core::LoadTexture("textures/stone.png");
}

void shutdown()
{
	shaderLoader.DeleteProgram(programColor);
	shaderLoader.DeleteProgram(programTexture);
}

void idle()
{
	glutPostRedisplay();
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL Pierwszy Program");
	glewInit();

	init();
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);

	glutMainLoop();

	shutdown();

	return 0;
}
