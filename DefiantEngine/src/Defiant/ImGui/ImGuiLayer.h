#pragma once

#include "Defiant/Layer.h"
#include "Defiant/Events/MouseEvent.h"
#include "Defiant/Events/KeyEvent.h"
#include "Defiant/Events/ApplicationEvent.h"

namespace Defiant {
	
	class DE_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:

		float m_Time = 0;
	};

}