#include "color_shader.h"
#include "control_common_def.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
// Shader sources
const GLchar* vertexSource = R"glsl(
    attribute vec3 position;
    attribute vec3 qcolor;
    attribute vec2 texcoord;
    varying vec3 Color;
    varying vec2 Texcoord;
    uniform highp mat4 model;
    uniform highp mat4 view;
    uniform highp mat4 proj;
    void main()
    {
        Color = qcolor;
        Texcoord = texcoord;
        gl_Position = proj * view * model * vec4(position, 1.0);
        //gl_Position =  vec4(position, 1.0);
    }
)glsl";
const GLchar* fragmentSource = R"glsl(
    #version 150 core
    varying vec3 Color;
    varying vec2 Texcoord;
    out vec4 outColor;
    //uniform sampler2D texPuppy;
    void main()
    {
        //outColor = texture(texPuppy, Texcoord);
        outColor = vec4(Color, 1.0);
    }

)glsl";

color_shader::color_shader()
{

	//vertex shader
	_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertex_shader, 1, &vertexSource, NULL);
	glCompileShader(_vertex_shader);
	GLint status;
	glGetShaderiv(_vertex_shader, GL_COMPILE_STATUS, &status);
	if (status!=GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(_vertex_shader, 512, NULL, buffer);
		printf("shader error:%s\n", buffer);
		
	}
	//fragment shader
	_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragment_shader, 1, &fragmentSource, NULL);
	glCompileShader(_fragment_shader);
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(_vertex_shader, 512, NULL, buffer);
		printf("shader2 error:%s\n", buffer);

	}
	//link
	_shader_program_id = glCreateProgram();
	glAttachShader(_shader_program_id, _vertex_shader);
	glAttachShader(_shader_program_id, _fragment_shader);
	glBindFragDataLocation(_shader_program_id, 0, "outColor");
	glLinkProgram(_shader_program_id);
	glUseProgram(_shader_program_id);
	//glBindVertexArray(tgmesh._vao);
	//glBindBuffer(GL_ARRAY_BUFFER, tgmesh._vbo);

	_mattr_list["position"] = shader_attribute(en_attr_vec3, glGetAttribLocation(_shader_program_id, "position"));
	_mattr_list["qcolor"] = shader_attribute(en_attr_vec3, glGetAttribLocation(_shader_program_id, "qcolor"));
	_mattr_list["texcoord"] = shader_attribute(en_attr_vec2, glGetAttribLocation(_shader_program_id, "texcoord"));

	/*
	glEnableVertexAttribArray(_postion);
	glVertexAttribPointer(_postion, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);

	_color = glGetAttribLocation(_shader_program, "qcolor");
	glEnableVertexAttribArray(_color);
	glVertexAttribPointer(_color, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	_texcord = glGetAttribLocation(_shader_program, "texcoord");
	glEnableVertexAttribArray(_texcord);
	glVertexAttribPointer(_texcord, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	*/
	GLuint _model = glGetUniformLocation(_shader_program_id, "model");
	glm::mat4 model = glm::mat4();
	glUniformMatrix4fv(_model, 1, GL_FALSE, glm::value_ptr(model));
	_munf_list["model"] = shader_uniform(en_unf_mat4, _model);

	GLuint _view = glGetUniformLocation(_shader_program_id, "view");
	glm::mat4 view = glm::lookAt(
		glm::vec3(-1.5f, 1.5f, -1.5f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, -1.0f, 0.0f)
		);
	glUniformMatrix4fv(_view, 1, GL_FALSE, glm::value_ptr(view));
	_munf_list["view"] = shader_uniform(en_unf_mat4, _view);

	GLuint _proj = glGetUniformLocation(_shader_program_id, "proj");
	glm::mat4 proj = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 1.0f, 10.0f);
	//glm::mat4 cb = proj*view*model;
	//float* pview = glm::value_ptr(cb);
	//for (int ii = 0; ii < 16; ++ii)
	//{
	//	printf("%f,", *pview++);
	//	if (ii % 4 == 3)
	//	{
	//		printf("\n");
	//	}
	//}
	glUniformMatrix4fv(_proj, 1, GL_FALSE, glm::value_ptr(proj));
	_munf_list["proj"] = shader_uniform(en_unf_mat4, _proj);


}



/*
#include <chrono>

void color_shader::render()
{
	GLint last_program, last_array_buffer, last_element_array_buffer, last_vertex_array;
	glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &last_element_array_buffer);
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);
	static auto t_start = std::chrono::high_resolution_clock::now();
	auto t_now = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(
		model,
		time* glm::radians(30.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
		);
	glUniformMatrix4fv(_model, 1, GL_FALSE, glm::value_ptr(model));

	//glEnable(GL_DEPTH_TEST);
	glUseProgram(_shader_program);
	glBindVertexArray(_tmesh._vao);
	glBindBuffer(GL_ARRAY_BUFFER, _tmesh._vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _tmesh._ebo);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	glUseProgram(last_program);
	glBindVertexArray(last_vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, last_element_array_buffer);

}

*/