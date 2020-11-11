#pragma once

#include "Event.h"

#include <sstream>

namespace Combustion {
	class CB_API WindowResizedEvent : public Event {
	public:
		WindowResizedEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {

		}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizedEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};

	class CB_API WindowClosedEvent : public Event {
	public:
		WindowClosedEvent() {
		
		}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class CB_API AppTickEvent : public Event {
	public:
		AppTickEvent() {

		}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class CB_API AppUpdateEvent : public Event {
	public:
		AppUpdateEvent() {

		}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class CB_API AppRenderEvent : public Event {
	public:
		AppRenderEvent() {

		}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}