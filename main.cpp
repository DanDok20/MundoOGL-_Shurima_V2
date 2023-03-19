//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "glm.h"
#include <FreeImage.h> //*** Para Textura: Incluir librería
#include "malla.h";

//-----------------------------------------------------------------------------


class myWindow : public cwc::glutWindow
{
protected:
   cwc::glShaderManager SM;
   cwc::glShader *shader;
   cwc::glShader* shader1; //Para Textura: variable para abrir los shader de textura
   GLuint ProgramObject;
   clock_t time0,time1;
   float timer010;  // timer counting 0->1->0
   bool bUp;        // flag if counting up or down.
   GLMmodel* objmodel_ptr;
   GLMmodel* objmodel_ptr1; //*** Para Textura: variable para objeto texturizado
   GLMmodel* objmodel_ptr_piso;
   GLMmodel* objmodel_ptr_sofa;
   GLMmodel* objmodel_ptr_silla;
   GLMmodel* objmodel_ptr_escalera;
   GLMmodel* objmodel_ptr_pared;
   GLMmodel* objmodel_ptr_persona;
   GLMmodel* objmodel_ptr_chimenea;
   GLMmodel* objmodel_ptr_mesa;
   GLMmodel* objmodel_ptr_lampara;
   GLuint texid; //*** Para Textura: variable que almacena el identificador de textura
   malla* miMallaPiso;
   malla* miMallaSofa;
   malla* miMallaSilla;
   malla* miMallaEscalera;
   malla* miMallaPared;
   malla* miMallaPersona;
   malla* miMallaChimenea;
   malla* miMallaMesa;
   malla* miMallaLampara;



public:
	myWindow(){}

	//*** Para Textura: aqui adiciono un método que abre la textura en JPG
	void initialize_textures(char* Texture)
	{
		int w, h;
		GLubyte* data = 0;
		//data = glmReadPPM("soccer_ball_diffuse.ppm", &w, &h);
		//std::cout << "Read soccer_ball_diffuse.ppm, width = " << w << ", height = " << h << std::endl;

		//dib1 = loadImage("soccer_ball_diffuse.jpg"); //FreeImage

		glGenTextures(1, &texid);
		glBindTexture(GL_TEXTURE_2D, texid);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		// Loading JPG file
		// JPG
		char* JPG;
		JPG = "https://thumbs.dreamstime.com/b/texture-soccer-ball-13533294.jpg";
		FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(JPG, 0),JPG);  //*** Para Textura: esta es la ruta en donde se encuentra la textura

		FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
		int nWidth = FreeImage_GetWidth(pImage);
		int nHeight = FreeImage_GetHeight(pImage);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

		FreeImage_Unload(pImage);
		//
		glEnable(GL_TEXTURE_2D);
	}


	virtual void OnRender(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
      //timer010 = 0.09; //for screenshot!

      glPushMatrix();
	  //glRotatef(timer010 * 360, 0.5, 1.0f, 0.1f);
	  glTranslatef(0, 0, -35);
	  glRotatef(20, 1, 0, 0);
      if (shader) shader->begin();
		  

			//(float x, float y, float z, float tamanio, float rotacion, float rx, float ry, float rz); los ultimos son de rotacion
			//Piso
			//Centro
			miMallaPiso->AgregarMalla(0, 0, 0, 5, 0, 1, 0, 0);
			miMallaPiso->AgregarMalla(0, 0, 6, 5, 0, 1, 0, 0);
			miMallaPiso->AgregarMalla(0, 0, -6, 5, 0, 1, 0, 0);
			miMallaPiso->AgregarMalla(0, 0, 12, 5, 0, 1, 0, 0);
			miMallaPiso->AgregarMalla(0, 0, -12, 5, 0, 1, 0, 0);
			//Derecha
			miMallaPiso->AgregarMalla(8, 0, 0, 5, 0, 1, 0, 0);
			miMallaPiso->AgregarMalla(8, 0, 6, 5, 0, 1, 0, 0);
			miMallaPiso->AgregarMalla(8, 0, -6, 5, 0, 1, 0, 0);
			miMallaPiso->AgregarMalla(8, 0, 12, 5, 0, 1, 0, 0);
			miMallaPiso->AgregarMalla(8, 0, -12, 5, 0, 1, 0, 0);
			//Izquierda
			miMallaPiso->AgregarMalla(-8, 0, 0, 5, 0, 1, 0, 0);
			miMallaPiso->AgregarMalla(-8, 0, 6, 5, 0, 1, 0, 0);
			miMallaPiso->AgregarMalla(-8, 0, -6, 5, 0, 1, 0, 0);
			miMallaPiso->AgregarMalla(-8, 0, 12, 5, 0, 1, 0, 0);
			miMallaPiso->AgregarMalla(-8, 0, -12, 5, 0, 1, 0, 0);
			//Arriba
			miMallaPiso->AgregarMalla(8,4, -12, 5, 0, 1, 0, 0);
			miMallaPiso->AgregarMalla(0, 4, -12, 5, 0, 1, 0, 0);
			miMallaPiso->AgregarMalla(-8, 4, -12, 5, 0, 1, 0, 0);
			miMallaPiso->AgregarMalla(8, 4, -6, 5, 0, 1, 0, 0);
			miMallaPiso->AgregarMalla(0, 4, -6, 5, 0, 1, 0, 0);
			miMallaPiso->AgregarMalla(-8, 4, -6, 5, 0, 1, 0, 0);
	
			//Personas abajo
			miMallaPersona->AgregarMalla(0, 1, 0, 5, 0, 1, 0, 0);
			miMallaPersona->AgregarMalla(0, 1, -4, 5, 0, 1, 0, 0);
			miMallaPersona->AgregarMalla(4, 1, 0, 5, 0, 1, 0, 0);
			miMallaPersona->AgregarMalla(5, 1, 6, 5, 0, 1, 0, 0);
			miMallaPersona->AgregarMalla(5, 1, 8, 5, 0, 1, 0, 0);
			//Personas arriba
			miMallaPersona->AgregarMalla(-5, 5, -6, 5, 0, 1, 0, 0);
			miMallaPersona->AgregarMalla(-7, 5, -6, 5, 0, 1, 0, 0);

			//Escalera
			miMallaEscalera->AgregarMalla(11, 3.2, 0, 3, 0, 1, 0, 0);

			//Silllas
			miMallaSilla->AgregarMalla(-9, 1, -11, 15, 0, 1, 0, 0);

			//Mesa
			miMallaMesa->AgregarMalla(0, 1, 3, 0.9, 0, 1, 0, 0);
			miMallaMesa->AgregarMalla(10, 1, -1, 0.9, 0, 1, 0, 0);
			miMallaMesa->AgregarMalla(-9, 1, 4.5, 0.9, 0, 1, 0, 0);
			miMallaMesa->AgregarMalla(-10.5, 1, -8, 0.9, 0, 1, 0, 0);

			//Lampara
			miMallaLampara->AgregarMalla(-7, 1, -11, 0.9, 0, 1, 0, 0);

			//Sofa
			miMallaSofa->AgregarMalla(1, 1, -11, 1.5, 0, 1, 0, 0);

			//Chimenea
			miMallaChimenea->AgregarMalla(-7, 1, 9, 1.7, 0, 1, 0, 0);

			//Pared lado Fondo
			//Izquierda
			miMallaPared->AgregarMalla(-10.1, 1, -14.5, 20, 0, 1, 0, 0);
			miMallaPared->AgregarMalla(-10.1, 3, -14.5, 20, 0, 1, 0, 0);
			miMallaPared->AgregarMalla(-10.1, 6, -14.5, 20, 0, 1, 0, 0);
			//Centro Izuqierda
			miMallaPared->AgregarMalla(-5, 1, -14.5, 20, 0, 1, 0, 0);
			miMallaPared->AgregarMalla(-5, 3, -14.5, 20, 0, 1, 0, 0);
			miMallaPared->AgregarMalla(-5, 6, -14.5, 20, 0, 1, 0, 0);
			//Centro
			miMallaPared->AgregarMalla(0, 1, -14.5, 20, 0, 1, 0, 0);
			miMallaPared->AgregarMalla(0, 3, -14.5, 20, 0, 1, 0, 0);
			miMallaPared->AgregarMalla(0, 6, -14.5, 20, 0, 1, 0, 0);
			//Centro Derecha
			miMallaPared->AgregarMalla(5, 6, -14.5, 20, 0, 1, 0, 0);
			miMallaPared->AgregarMalla(5, 5, -14.5, 20, 0, 1, 0, 0);
			//Derecha
			miMallaPared->AgregarMalla(10.1, 1, -14.5, 20, 0, 1, 0, 0);
			miMallaPared->AgregarMalla(10.1, 3, -14.5, 20, 0, 1, 0, 0);
			miMallaPared->AgregarMalla(10.1, 6, -14.5, 20, 0, 1, 0, 0);

			//Paredes lado izquierdo
			//Paredes atras medio 1
			miMallaPared->AgregarMalla(-12.7, 1, -4, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(-12.7, 3.5, -4, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(-12.7, 6, -4, -14.5, 90, 0, 1, 0);
			//Paredes atras medio 2
			miMallaPared->AgregarMalla(-12.7, 1, -8, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(-12.7, 3.5, -8, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(-12.7, 6, -8, -14.5, 90, 0, 1, 0);
			//Paredes atras
			miMallaPared->AgregarMalla(-12.7, 1, -12, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(-12.7, 3.5, -12, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(-12.7, 6, -12, -14.5, 90, 0, 1, 0);
			//Paredes Centro
			miMallaPared->AgregarMalla(-12.7, 1, 0, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(-12.7, 3.5, 0, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(-12.7, 6, 0, -14.5, 90, 0, 1, 0);
			//Paredes adelante medio 1
			miMallaPared->AgregarMalla(-12.7, 1, 4, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(-12.7, 3.5, 4, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(-12.7, 6, 4, -14.5, 90, 0, 1, 0);
			//Paredes adelante medio 2
			miMallaPared->AgregarMalla(-12.7, 1, 8, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(-12.7, 3.5, 8, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(-12.7, 6, 8, -14.5, 90, 0, 1, 0);
			//Paredes adelante
			miMallaPared->AgregarMalla(-12.7, 1, 12, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(-12.7, 3.5, 12, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(-12.7, 6, 12, -14.5, 90, 0, 1, 0);

			//Paredes lado derecho
			//Paredes atras medio 1
			miMallaPared->AgregarMalla(12.7, 1, -4, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(12.7, 3.5, -4, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(12.7, 6, -4, -14.5, 90, 0, 1, 0);
			//Paredes atras medio 2
			miMallaPared->AgregarMalla(12.7, 1, -8, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(12.7, 3.5, -8, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(12.7, 6, -8, -14.5, 90, 0, 1, 0);
			//Paredes atras
			miMallaPared->AgregarMalla(12.7, 1, -12, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(12.7, 3.5, -12, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(12.7, 6, -12, -14.5, 90, 0, 1, 0);
			//Paredes Centro
			miMallaPared->AgregarMalla(12.7, 1, 0, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(12.7, 3.5, 0, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(12.7, 6, 0, -14.5, 90, 0, 1, 0);
			//Paredes adelante medio 1
			miMallaPared->AgregarMalla(12.7, 1, 4, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(12.7, 3.5, 4, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(12.7, 6, 4, -14.5, 90, 0, 1, 0);
			//Paredes adelante medio 2
			miMallaPared->AgregarMalla(12.7, 1, 8, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(12.7, 3.5, 8, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(12.7, 6, 8, -14.5, 90, 0, 1, 0);
			//Paredes adelante
			miMallaPared->AgregarMalla(12.7, 1, 12, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(12.7, 3.5, 12, -14.5, 90, 0, 1, 0);
			miMallaPared->AgregarMalla(12.7, 6, 12, -14.5, 90, 0, 1, 0);

			

      if (shader) shader->end();

	  //*** Para Textura: llamado al shader para objetos texturizados
	  if (shader1) shader1->begin();
		 miMallaSofa->PintarMalla(1, 1, -11, 1.5, 0, 1, 0, 0, texid);
	  if (shader1) shader1->end();


      glutSwapBuffers();
      glPopMatrix();

      UpdateTimer();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit()
	{
		glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		miMallaPiso = new malla();
		miMallaSofa = new malla();
		miMallaSilla = new malla();
		miMallaEscalera = new malla();
		miMallaPared = new malla();
		miMallaPersona = new malla();
		miMallaChimenea = new malla();
		miMallaMesa = new malla();
		miMallaLampara = new malla();

		shader = SM.loadfromFile("vertexshader.txt","fragmentshader.txt"); // load (and compile, link) from file
		if (shader==0) 
         std::cout << "Error Loading, compiling or linking shader\n";
      else
      {
         ProgramObject = shader->GetProgramObject();
      }

	 //*** Para Textura: abre los shaders para texturas
		shader1 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
		if (shader1 == 0)
			std::cout << "Error Loading, compiling or linking shader\n";
		else
		{
			ProgramObject = shader1->GetProgramObject();
		}

      time0 = clock();
      timer010 = 0.0f;
      bUp = true;


	  char* mallap;
	  mallap = "./MALLAS/NBose/Piso.obj";
	  miMallaPiso->AbrirMalla(mallap);
	  mallap = "./MALLAS/NBose/Sofa.obj";
	  miMallaSofa->AbrirMalla(mallap);
	  mallap = "./MALLAS/NBose/Silla.obj";
	  miMallaSilla->AbrirMalla(mallap);
	  mallap = "./MALLAS/NBose/Escalera.obj";
	  miMallaEscalera->AbrirMalla(mallap);
	  mallap = "./MALLAS/NBose/Pared.obj";
	  miMallaPared->AbrirMalla(mallap);
	  mallap = "./MALLAS/NBose/Persona.obj";
	  miMallaPersona->AbrirMalla(mallap);
	  mallap = "./MALLAS/NBose/Chimenea.obj";
	  miMallaChimenea->AbrirMalla(mallap);
	  mallap = "./MALLAS/NBose/Mesa.obj";
	  miMallaMesa->AbrirMalla(mallap);
	  mallap = "./MALLAS/NBose/Lampara.obj";
	  miMallaLampara->AbrirMalla(mallap);


	  /*
	  //*** Para Textura: abrir malla de objeto a texturizar
	  objmodel_ptr1 = NULL;

	  if (!objmodel_ptr1)
	  {
		  objmodel_ptr1 = glmReadOBJ("./Mallas/bola.obj");
		  if (!objmodel_ptr1)
			  exit(0);

		  glmUnitize(objmodel_ptr1);
		  glmFacetNormals(objmodel_ptr1);
		  glmVertexNormals(objmodel_ptr1, 90.0);
	  }
 
	  //*** Para Textura: abrir archivo de textura
	  char* Texture;
	  Texture = "./Mallas/bola.jpg";
	  initialize_textures(Texture);
      DemoLight();
	  */

	}

	virtual void OnResize(int w, int h)
   {
      if(h == 0) h = 1;
	   float ratio = 1.0f * (float)w / (float)h;

      glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	
	   glViewport(0, 0, w, h);

      gluPerspective(45,ratio,1,100);
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	   gluLookAt(0.0f,0.0f,4.0f, 
		          0.0,0.0,-1.0,
			       0.0f,1.0f,0.0f);
   }
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}    
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close Window!
		} 
	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
      if (cAscii == 's')      // s: Shader
         shader->enable();
      else if (cAscii == 'f') // f: Fixed Function
         shader->disable();
	}

   void UpdateTimer()
   {
      time1 = clock();
      float delta = static_cast<float>(static_cast<double>(time1-time0)/static_cast<double>(CLOCKS_PER_SEC));
      delta = delta / 4;
      if (delta > 0.00005f)
      {
         time0 = clock();
         if (bUp)
         {
            timer010 += delta;
            if (timer010>=1.0f) { timer010 = 1.0f; bUp = false;}
         }
         else
         {
            timer010 -= delta;
            if (timer010<=0.0f) { timer010 = 0.0f; bUp = true;}
         }
      }
   }

   void DemoLight(void)
   {
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_NORMALIZE);
     
    /* // Light model parameters:
     // -------------------------------------------
     
     GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
     
     glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
     glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
     
     // -------------------------------------------
     // Spotlight Attenuation
     
     GLfloat spot_direction[] = {1.0, -1.0, -1.0 };
     GLint spot_exponent = 30;
     GLint spot_cutoff = 180;
     
     glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
     glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
     glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
    
     GLfloat Kc = 1.0;
     GLfloat Kl = 0.0;
     GLfloat Kq = 0.0;
     
     glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,Kc);
     glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
     glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);
     
     
     // ------------------------------------------- 
     // Lighting parameters:

     GLfloat light_pos[] = {0.0f, 5.0f, 5.0f, 1.0f};
     GLfloat light_Ka[]  = {1.0f, 0.5f, 0.5f, 1.0f};
     GLfloat light_Kd[]  = {1.0f, 0.1f, 0.1f, 1.0f};
     GLfloat light_Ks[]  = {1.0f, 1.0f, 1.0f, 1.0f};

     glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
     glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
     glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

     // -------------------------------------------
     // Material parameters:

     GLfloat material_Ka[] = {0.5f, 0.0f, 0.0f, 1.0f};
     GLfloat material_Kd[] = {0.4f, 0.4f, 0.5f, 1.0f};
     GLfloat material_Ks[] = {0.8f, 0.8f, 0.0f, 1.0f};
     GLfloat material_Ke[] = {0.1f, 0.0f, 0.0f, 0.0f};
     GLfloat material_Se = 20.0f;

     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
     glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);*/
   }
}; 

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
	virtual void OnInit() {std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

