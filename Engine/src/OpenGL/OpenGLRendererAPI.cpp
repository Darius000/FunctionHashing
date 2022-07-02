#include "PCH.h"
#include "OpenGLRendererAPI.h"
#include <glad/glad.h>

void OpenGLMessageCallback(unsigned source, unsigned type, unsigned id, unsigned severity,
	int length, const char* message, const void* userParam)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH: LOG_CRITICAL(message); return;
	case GL_DEBUG_SEVERITY_MEDIUM: LOG_ERROR(message); return;
	case GL_DEBUG_SEVERITY_LOW: LOG_WARN(message); return;
	case GL_DEBUG_SEVERITY_NOTIFICATION: LOG_TRACE(message); return;
	}

}

void OpenGLRendererAPI::Init()
{
#ifdef DEBUG

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(OpenGLMessageCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);

#endif // DEBUG

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
	glClearColor(color.x, color.y, color.z, color.w);
}

void OpenGLRendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::Flush()
{
	glFlush();
}

void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexcount)
{
	vertexArray->Bind();
	auto count = indexcount ? indexcount : vertexArray->GetIndexBuffer()->GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRendererAPI::SetLineWidth(float width)
{
	glLineWidth(width);
}
