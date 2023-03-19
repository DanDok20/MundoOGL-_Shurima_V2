#include "malla.h"

malla::malla() {}

void malla::AbrirMalla(char* mallap) {
	objmodel_ptr = NULL;
	if (!objmodel_ptr)
	{
		objmodel_ptr = glmReadOBJ(mallap);
		if (!objmodel_ptr)
			exit(0);

		glmUnitize(objmodel_ptr);
		glmFacetNormals(objmodel_ptr);
		glmVertexNormals(objmodel_ptr, 90.0);
	}

}

void malla::AgregarMalla(float x, float y, float z, float tamanio, float rotacion, float rx, float ry, float rz) {
	if (objmodel_ptr) {
		glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(rotacion, rx, ry, rz);
		glScalef(tamanio, tamanio, tamanio);
		glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL);
		glPopMatrix();
	}
}

void malla::PintarMalla(float x, float y, float z, float tamanio, float rotacion, float rx, float ry, float rz, GLuint& texid) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(rotacion, rx, ry, rz);
	glScalef(tamanio, tamanio, tamanio);
	glBindTexture(GL_TEXTURE_2D, texid);
	glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glPopMatrix();
}