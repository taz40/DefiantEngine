#pragma once

namespace Defiant {
	class TimeStep {
	public:
		TimeStep(float time) 
			: m_Time(time){
		}

		operator float() const { return m_Time; }
		
		float GetSecconds() const { return m_Time; }
		float GetMiliseconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};
}