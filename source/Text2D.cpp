
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "Texture.h"
#include "Shader.h"
#include "Tools.h"

#include "Text2D.h"

unsigned int text2DTextureID;
unsigned int text2DVertexBufferID;
unsigned int text2DUVBufferID;
Texture *textTexture;
Shader *text2DShader;

void initText2D(char * texturePath){

	// Initialize texture
    textTexture = new Texture(texturePath, GL_RGB);
	text2DTextureID = textTexture->getTexture();

	// Initialize VBO
	glGenBuffers(1, &text2DVertexBufferID);
	glGenBuffers(1, &text2DUVBufferID);

	// Initialize Shader
	text2DShader = new Shader ("../shader/textVertexShader.glsl", "../shader/textFragmentShader.glsl");
}


void printText2D(const char * text, int x, int y, int size){

	unsigned int length = strlen(text);

	// Fill buffers
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> UVs;
	for ( unsigned int i=0 ; i<length ; i++ ){
		
		glm::vec2 vertex_up_left    = glm::vec2( x+i*size     , y+size );
		glm::vec2 vertex_up_right   = glm::vec2( x+i*size+size, y+size );
		glm::vec2 vertex_down_right = glm::vec2( x+i*size+size, y      );
		glm::vec2 vertex_down_left  = glm::vec2( x+i*size     , y      );

		vertices.push_back(vertex_up_left   );
		vertices.push_back(vertex_down_left );
		vertices.push_back(vertex_up_right  );

		vertices.push_back(vertex_down_right);
		vertices.push_back(vertex_up_right);
		vertices.push_back(vertex_down_left);

		char character = text[i];
		float uv_x = (character%16)/16.0f;
		float uv_y = (character/16)/16.0f;

		glm::vec2 uv_up_left    = glm::vec2( uv_x           , uv_y );
		glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, uv_y );
		glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f) );
		glm::vec2 uv_down_left  = glm::vec2( uv_x           , (uv_y + 1.0f/16.0f) );
		UVs.push_back(uv_up_left   );
		UVs.push_back(uv_down_left );
		UVs.push_back(uv_up_right  );

		UVs.push_back(uv_down_right);
		UVs.push_back(uv_up_right);
		UVs.push_back(uv_down_left);
	}

	GLuint bufVertices = makeBuffer(&vertices[0], vertices.size(), sizeof(float) * 2);		    
	GLuint bufTexCoords = makeBuffer(&UVs[0], UVs.size(), sizeof(float) * 2);
	GLuint vao;
    glGenVertexArrays(1, &vao);

	text2DShader->use();

    glBindVertexArray(vao);

	assignVBOtoAttribute(text2DShader,"vertexPosition_screenspace",bufVertices,2);
	assignVBOtoAttribute(text2DShader, "vertexUV", bufTexCoords, 2);

	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, text2DTextureID);
    text2DShader->set("myTextureSampler", 0);

	glBindVertexArray(vao);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glDisable(GL_BLEND);
		
	glBindVertexArray(0);
}

void cleanupText2D(){

	// Delete buffers
	glDeleteBuffers(1, &text2DVertexBufferID);
	glDeleteBuffers(1, &text2DUVBufferID);

	// Delete texture
	glDeleteTextures(1, &text2DTextureID);

	// Delete shader
	//glDeleteProgram(Text2DShaderID);
	delete textTexture;
    delete text2DShader;
}
