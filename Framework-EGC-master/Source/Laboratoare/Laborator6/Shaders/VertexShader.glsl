#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 3) in vec3 v_normala;
layout(location = 2) in vec2 v_coord;
layout(location = 1) in vec3 v_color;


// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;
uniform vec3 colorSphere;

// TODO: output values to fragment shader
out vec3 frag_position;
out vec3 frag_normala;
out vec2 frag_coord;
out vec3 frag_color;


void main()
{
	// TODO: send output to fragment shader
	//pamant
	if(colorSphere == vec3(0.196f, 0.804f, 0.196f)){
		frag_color =  colorSphere + vec3(-0.196,-0.412,-0.196) * time;
	}
	
	//cer
	if(colorSphere == vec3(0.000f, 1.000f, 1.000f)){
		frag_color =  colorSphere + vec3(0.294,-1.000,-0.490) * time;
	}

	if(colorSphere == vec3(0.412, 0.412, 0.412)) {
		frag_color =  colorSphere + vec3(-0.312,-0.312,-0.312) * time;
	}

	if(colorSphere == vec3(0.863, 0.863, 0.863)){
			frag_color =  colorSphere + vec3(-0.2,-0.2,-0.2) * time;
	}

	if(colorSphere == vec3(0.000, 0.392, 0.000)){
			frag_color =  colorSphere + vec3(0.000, 0.392, 0.000);
	}
	frag_position = v_position;
	frag_coord = v_coord;
	frag_normala = v_normala;

	gl_Position = Projection * View * Model * vec4(v_position , 1.0);
}
