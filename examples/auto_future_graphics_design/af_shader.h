#pragma once
/*
#include "imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"*/
#include <vector>
#include <map>
#include <functional>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <glm/gtx/norm.hpp>
#if !defined(IMGUI_WAYLAND)
#include <GL/gl3w.h>
#else
#include"../../deps/glad/glad.h"
#endif
#include "fab.h"
using namespace fab;
using namespace std;
/**
* @brief basic variable type of the shader  \n
*/
struct shader_variable
{
	GLenum _variable_type;
	GLuint _location;
	GLuint _size;
	shader_variable(){}
	shader_variable(GLenum vtp, GLuint loc, GLuint size) :_variable_type(vtp), _location(loc),_size(size){}
};
typedef map<string, shader_variable> mshader_variable_list;
/**
* @brief  af_shader, process unit of gpu for rendering ui components \n
*/
class af_shader
{
	/** all the type of attribute variables  of shader */
	mshader_variable_list _att_list;
	/** all the type of uniform variables of shader */
	mshader_variable_list _unf_list;
	GLuint _shader_program_id, _vertex_shader, _fragment_shader;
	string _name;
	/** whether shader is valid */
	bool _valid{ false };
	/** vertex shader source code and fragment shader source code */
	string _vs_code, _fs_code;
public:
	af_shader(const GLchar* vertex_shader_source, const GLchar* fragment_shader_source);
	~af_shader();
	string get_name() { return _name; }
	void set_name(string name){ _name = name; };
	mshader_variable_list& get_uf_defs(){ return _unf_list; }
	string get_vs_code(){ return _vs_code; }
	string get_fs_code(){ return _fs_code; }
	void refresh_sourcecode(string& vertex_shader_source, string& fragment_shader_source);
	
	void build();
	void refresh_viarable_list();
#if !defined(IMGUI_DISABLE_DEMO_WINDOWS)
public:
	string compile_error_info;
	string _vs_name, _fs_name;
	
	bool _vs_selected{ false };
	bool _fs_selected{ false };
	void reset_sel(){ _vs_selected = _fs_selected = false; }
#endif
	bool is_valid(){ return _valid; }
	void use(){ glUseProgram(_shader_program_id); }
	bool vertex_att_pointer(initializer_list<string> att_name_list);
	//template<typename T> bool uniform(string unf_name, GLsizei icnt, T* pvalue);
	bool uniform(string unf_name, float* pvalue);
	bool uniform(string unf_name, int* pvalue);
	bool uniform(string unf_name, double* pvalue);

	bool uniform(string unf_name, int ivalue);

};

typedef map<string,shared_ptr<af_shader>> maf_shader;
extern maf_shader g_af_shader_list;