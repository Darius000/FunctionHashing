#include "Application.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"
#include <iostream>

extern bool g_ApplicationRunning;

namespace BHive
{
	static void glfwErrorCallback(int error, const char* description)
	{
		if (error == 0) return;

		fprintf(stderr, "Error %d: Result = %s\n", error, description);

		if (error < 0)
			abort();
	}


	Application::Application(const ApplicationSpecification& applicationspecification , ApplicationCommandLineArgs args)
		:m_Specification(applicationspecification), m_CommandLineArgs(args)
	{
		Init();
	}

	Application::~Application()
	{
		Shutdown();
	}


	void Application::Run()
	{
		while (!glfwWindowShouldClose(m_Window) && m_Running)
		{
			glfwPollEvents();

			m_Time = (float)glfwGetTime();
			m_DeltaTime = m_Time > 0.0f ? m_Time - m_LastTime : (1.0f / 60.0f);
			m_LastTime = m_Time;

			if (!m_Minimized)
			{
				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

				//Update IMGUI
				{
					static bool dockSpaceOpen = true;
					static bool opt_fullscreen_persistant = true;
					static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
					bool opt_fullscreen = opt_fullscreen_persistant;

					ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
					if (opt_fullscreen)
					{
						ImGuiViewport* viewport = ImGui::GetMainViewport();
						ImGui::SetNextWindowPos(viewport->Pos);
						ImGui::SetNextWindowSize(viewport->Size);
						ImGui::SetNextWindowViewport(viewport->ID);
						ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
						ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
						window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
						window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
					}

					if (opt_flags & ImGuiDockNodeFlags_PassthruCentralNode)
						window_flags |= ImGuiWindowFlags_NoBackground;

					ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
					ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
					ImGui::PopStyleVar();

					if (opt_fullscreen)
						ImGui::PopStyleVar(2);

					// Dockspace
					ImGuiIO& io = ImGui::GetIO();
					ImGuiStyle& style = ImGui::GetStyle();
					SetDefaultTheme();

					style.WindowMinSize.x = 150.0f;
					if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
					{
						ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
						ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
					}

					{
						if (m_MenuBarCallback)
						{
							if (ImGui::BeginMenuBar())
							{
								m_MenuBarCallback();
								ImGui::EndMenuBar();
							}
						}

						for (auto& layer : m_LayerStack)
						{
							layer->OnUIRender();
						}

						ImGui::End();
					}

					ImGui::Render();
					ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

					if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
					{
						GLFWwindow* backup_current_context = glfwGetCurrentContext();
						ImGui::UpdatePlatformWindows();
						ImGui::RenderPlatformWindowsDefault();
						glfwMakeContextCurrent(backup_current_context);
					}
				}

			}

			//GLFW
			{
				glfwPollEvents();

				glfwSwapBuffers(m_Window);
			}
		}

	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::SetDefaultTheme()
	{
		auto orange = ImVec4(1.0f, .5f, 0.0f, 1.0f);
		auto dark_orange = ImVec4(.8f, .2f, 0.0f, 1.0f);

		ImGuiStyle& style = ImGui::GetStyle();
		
		style.Colors[ImGuiCol_Tab] = orange;
		style.Colors[ImGuiCol_TabActive] = orange;
		style.Colors[ImGuiCol_TabUnfocusedActive] = dark_orange;
	}

	void Application::Init()
	{
		//GLFW
		{
			int status = glfwInit();
			glfwSetErrorCallback(glfwErrorCallback);
			

			m_Window = glfwCreateWindow((int)m_Specification.m_Width, (int)m_Specification.m_Height,
				m_Specification.m_Name.c_str(), nullptr, nullptr);

			//init opengl
			glfwMakeContextCurrent(m_Window);

			int gladstatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

			if (!gladstatus)
			{
				std::cout << "Failed to load GLAD" << std::endl;
			}

			glLineWidth(1.0f);
			glEnable(GL_LINE_SMOOTH);


			////set glfw window context to opengl version 4.6
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			glfwSwapInterval(true);

			glfwSetWindowUserPointer(m_Window, &m_Specification);
		}

		//IMGUI
		{
			//Init IMGUI
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();


			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

			ImGui::StyleColorsDark();

			ImGuiStyle& style = ImGui::GetStyle();
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				style.WindowRounding = 0.0f;
				style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			}

			
			ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
			ImGui_ImplOpenGL3_Init("#version 460");

			ImFontConfig fontConfig;
			fontConfig.FontDataOwnedByAtlas = false;
			ImFont* robotoFont = io.Fonts->AddFontFromFileTTF("../BHive/Resources/Roboto-Regular.ttf", 20.0f, &fontConfig);
			io.FontDefault = robotoFont;

		}
	}

	void Application::Shutdown()
	{
		for (auto& layer : m_LayerStack)
			layer->OnDetach();

		m_LayerStack.clear();


		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(m_Window);
		glfwTerminate();

		g_ApplicationRunning = false;
	}

	Application* Application::s_Instance = nullptr;

}