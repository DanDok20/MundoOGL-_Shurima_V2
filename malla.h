#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include "glm.h"
#include <time.h>
#include <FreeImage.h> //*** Para Textura: Incluir librería


class malla
{
private:
	GLMmodel* objmodel_ptr;
	GLMmodel* mallap;
public:
	malla();

	void AbrirMalla(char* mallap);

	void AgregarMalla(float x, float y, float z, float tamanio, float rotacion, float rx, float ry, float rz);

	void PintarMalla(float x, float y, float z, float tamanio, float rotacion, float rx, float ry, float rz, GLuint& texid);

};

