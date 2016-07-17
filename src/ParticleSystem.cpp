
#include <cstdio>
#include <ctime>

#include "gl.hpp"
#include "FPSCounter.hpp"
#include "ParticleSystem.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "GLContext.hpp"
#include "CLContext.hpp"
#include "Utils.hpp"
#include "Particle.hpp"
#include "GravityPoint.hpp"
#include "Renderer.hpp"
#include "Control.hpp"
#include "Matrix4.hpp"
#include "Vec3.hpp"

ParticleSystem &	ParticleSystem::instance(GLContext * glContext, CLContext * clContext, cl_uint particleCount)
{
	static ParticleSystem *	ps;

	if (ps == nullptr)
	{
		if (glContext != nullptr && clContext != nullptr)
			ps = new ParticleSystem(*glContext, *clContext, particleCount);
		else
			Utils::die("The first call to ParticleSystem::instance must have a GL context and a CL context.");
	}

	return *ps;
}

ParticleSystem::ParticleSystem(GLContext & glContext, CLContext & clContext, cl_uint particleCount) :
	cl(clContext),
	gl(glContext),
	camera(glContext.windowSize),
	gpManager(GravityPointManager(3)),
	particleCount(particleCount)
{
	_createShaderPrograms();

	_createBuffers();

	cl.addSource(Utils::readFile("kernel/header.cl"));
	cl.addSource(Utils::readFile("kernel/init.cl"));
	cl.addSource(Utils::readFile("kernel/update.cl"));
	cl.buildProgram();

	_updateLocalAndGlobalSizes();

	gl.renderer = [&](void *data)
	{
		(void)data;
		update();
	};

	glfwSetKeyCallback(gl.window, Control::onKeyboard);
	glfwSetMouseButtonCallback(gl.window, Control::onMouseClick);
	glfwSetCursorPosCallback(gl.window, Control::onMouseMove);
	glfwSetWindowSizeCallback(gl.window, GLContext::resizeWindow);
}

ParticleSystem::~ParticleSystem()
{
	delete gl.programs["particle"];
	delete gl.programs["gp"];
}

void		ParticleSystem::init(const std::string & initFunction)
{
	initCamera();
	gpManager.freeAllGPs();

	try
	{
		cl::CommandQueue &	queue = cl.queue;
		cl::Kernel			kernel(cl.program, initFunction.c_str());

		kernel.setArg(0, cl.vbos[0]);
		kernel.setArg(1, sizeof(cl_uint), &particleCount);

		queue.enqueueAcquireGLObjects(&cl.vbos);
		queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(particleCount), cl::NullRange);
		queue.finish();
		queue.enqueueReleaseGLObjects(&cl.vbos);
	}
	catch (const cl::Error & e)
	{
		Utils::die(
			"Error while initializing particles: %s returned %s (%i).\n",
			e.what(),
			CLContext::getErrorString(e.err()).c_str(),
			e.err()
		);
	}
}

void		ParticleSystem::initCamera()
{
	camera.matrix = Matrix4::identity.translate(Vec3(0, 0, 1.735f));
	camera.linearVelocity = Vec3::zero;
	camera.angularVelocity = Vec3::zero;
	camera.rotation = Quaternion::identity;
	camera.resolution = gl.windowSize;
}

void		ParticleSystem::update()
{
	updateParticles();
	camera.update();
	updateUniforms();
	Renderer::render(*this);
}

void		ParticleSystem::updateGPBuffer() const
{
	glBindBuffer(GL_ARRAY_BUFFER, gl.vbos["gp"]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GravityPoint) * gpManager.gpCount, gpManager.gravityPoints.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void		ParticleSystem::updateParticles() const
{
	static std::clock_t	lastTime = std::clock();
	std::clock_t		newTime;

	try
	{
		cl::CommandQueue &	queue = cl.queue;

		updateGPBuffer();

		newTime = std::clock();
		lastTime = newTime;

		if (!_paused)
		{
			// cl_float	deltaTime = 1000.f * (newTime - lastTime) / CLOCKS_PER_SEC;

			cl::Kernel	kernel(cl.program, "update_particles");
			kernel.setArg(0, cl.vbos[0]);
			kernel.setArg(1, cl.vbos[1]);
			// kernel.setArg(2, sizeof(cl_float), &deltaTime);

			glFinish();

			queue.enqueueAcquireGLObjects(&cl.vbos);
			queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(globalSize), cl::NDRange(localSize));
			queue.finish();
			queue.enqueueReleaseGLObjects(&cl.vbos);
		}
	}
	catch (const cl::Error & e)
	{
		Utils::die("An error occured while particles updating", e);
	}
}

void		ParticleSystem::updateUniforms() const
{
	const ShaderProgram *	program;
	const GravityPoint &	gp = gpManager.gravityPoints[0];
	GLint					uniID;
	const Matrix4			mvp = camera.projectionMatrix * camera.matrix.inverse();

	program = gl.programs["particle"];
	program->enable();
	uniID = glGetUniformLocation(program->id, "gp");
	glUniform4f(uniID, gp.s[0], gp.s[1], gp.s[2], gp.s[3]);
	uniID = glGetUniformLocation(program->id, "mvp");
	glUniformMatrix4fv(uniID, 1, GL_FALSE, mvp.data);
	program->disable();

	program = gl.programs["gp"];
	program->enable();
	uniID = glGetUniformLocation(program->id, "mvp");
	glUniformMatrix4fv(uniID, 1, GL_FALSE, mvp.data);
	program->disable();
}

void		ParticleSystem::togglePause()
{
	_paused = !_paused;
}

void		ParticleSystem::_createBuffers()
{
	GLuint	vbos[2];
	GLuint	vaos[2];

	glGenBuffers(2, vbos);
	gl.vbos["particle"] = vbos[0];
	gl.vbos["gp"] = vbos[1];

	glGenVertexArrays(2, vaos);
	gl.vaos["particle"] = vaos[0];
	gl.vaos["gp"] = vaos[1];

	_configureParticleBuffer();
	_configureGPBuffer();

	try
	{
		cl::BufferGL	clBuffer;

		cl.vbos.push_back(cl::BufferGL(cl.context, CL_MEM_READ_WRITE, gl.vbos["particle"], nullptr));
		cl.vbos.push_back(cl::BufferGL(cl.context, CL_MEM_READ_ONLY, gl.vbos["gp"], nullptr));
	}
	catch (const cl::Error & e)
	{
		Utils::die("Error while creating the particle CL buffer", e);
	}
}

void		ParticleSystem::_configureParticleBuffer()
{
	GLuint	size = sizeof(Particle) * static_cast<GLuint>(particleCount);
	GLuint	vbo = gl.vbos["particle"];
	GLuint	vao = gl.vaos["particle"];
	GLuint	programID = gl.programs["particle"]->id;
	GLuint	attribID;

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_COPY);

	attribID = glGetAttribLocation(programID, "inPosition");
	glEnableVertexAttribArray(attribID);
	glVertexAttribPointer(attribID, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), nullptr);

	attribID = glGetAttribLocation(programID, "inVelocity");
	glEnableVertexAttribArray(attribID);
	glVertexAttribPointer(attribID, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void *)(sizeof(cl_float4)));

	glBindVertexArray(0);
}

void		ParticleSystem::_configureGPBuffer()
{
	GLuint	size = sizeof(GravityPoint) * gpManager.gpCount;
	GLuint	vbo = gl.vbos["gp"];
	GLuint	vao = gl.vaos["gp"];

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, gpManager.gravityPoints.data(), GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GravityPoint), nullptr);

	glBindVertexArray(0);
}

void		ParticleSystem::_createShaderPrograms()
{
	gl.programs["particle"] = new ShaderProgram({
		new Shader(GL_VERTEX_SHADER, "shader/particle_vertex.glsl"),
		new Shader(GL_FRAGMENT_SHADER, "shader/particle_fragment.glsl")
	});

	gl.programs["gp"] = new ShaderProgram({
		//&Shader(GL_GEOMETRY_SHADER, "shader/gp_geometry.glsl"),
		new Shader(GL_VERTEX_SHADER, "shader/gp_vertex.glsl"),
		new Shader(GL_FRAGMENT_SHADER, "shader/gp_fragment.glsl")
	});
}

void		ParticleSystem::_updateLocalAndGlobalSizes()
{
	cl::Kernel	kernel(cl.program, "update_particles");
	cl_int		result;

	result = clGetKernelWorkGroupInfo(
		kernel(),
		cl.device(),
		CL_KERNEL_WORK_GROUP_SIZE,
		sizeof(size_t),
		&localSize,
		nullptr
	);

	globalSize = ((particleCount / PARTICLES_PER_KERNEL) / localSize) * localSize;
}

std::ostream &	operator<<(std::ostream & os, const ParticleSystem & ps)
{
	os
		<< "OpenCL: " << ps.cl << std::endl
		<< "OpenGL: " << ps.gl << std::endl
		<< (ps.globalSize * PARTICLES_PER_KERNEL) << " particles" << std::endl;

	return os;
}
