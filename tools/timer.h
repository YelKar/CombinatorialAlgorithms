#pragma once
#include <chrono>
#include <cmath>
#include <iostream>
#include <utility>

namespace tools {
    class Delta {
    private:
	    std::int64_t nanoseconds;

    public:
        Delta() : nanoseconds(0) {}
        explicit Delta(std::int64_t ns) : nanoseconds(ns) {}

        [[nodiscard]] std::int64_t ToNanoseconds() const { return nanoseconds; }
        [[nodiscard]] double ToMicroseconds() const { return static_cast<double>(nanoseconds) / 1e3; }
        [[nodiscard]] double ToMilliseconds() const { return static_cast<double>(nanoseconds) / 1e6; }
        [[nodiscard]] double ToSeconds() const { return static_cast<double>(nanoseconds) / 1e9; }
        [[nodiscard]] double ToMinutes() const { return ToSeconds() / 60; }
        [[nodiscard]] double ToHours() const { return ToMinutes() / 60; }
        [[nodiscard]] double ToDays() const { return ToHours() / 24; }
        [[nodiscard]] double ToYears() const { return ToDays() / 365; }

        [[nodiscard]] std::string ToString() const {
            std::ostringstream oss;
            oss << "Delta(" << nanoseconds << "ns)";
            return oss.str();
        }

        template<typename T>
        Delta operator *(T num) {
            Delta d(this->nanoseconds * num);
            return d;
        }

        template<typename T>
        void operator *=(T num) {
            this->nanoseconds *= num;
        }

	    std::int64_t& operator *() {
			return this->nanoseconds;
		}

	    std::int64_t operator *() const {
			return this->nanoseconds;
		}
    };

	class Timer {
		using Clock = std::chrono::high_resolution_clock;
	public:
		void Restart() {
			m_start = Clock::now();
			m_running = true;
		}
		Delta GetDelta() {
			return Delta((Clock::now() - m_start).count());
		}
		virtual Delta Stop() {
			m_running = false;
			return GetDelta();
		}

		[[nodiscard]] bool IsRunning() const {
			return m_running;
		}

		template<typename Fn, typename... Args>
		static Delta Measure(Fn&& fn, Args&&... args) {
			Timer timer;
			fn(std::forward<Args>(args)...);
			return timer.GetDelta();
		}
	private:
		Clock::time_point m_start = Clock::now();
		bool m_running = true;
	};

	class LoggingTimer : public Timer {
		using Clock = std::chrono::high_resolution_clock;
	public:
		explicit LoggingTimer(std::string name)
			: m_name(std::move(name))
		{
		}
		~LoggingTimer() {
			LoggingTimer::Stop();
		}
		Delta Stop() override {
			if (IsRunning()) {
				auto delta = Timer::Stop();
				std::cout << m_name << ": " << delta.ToSeconds() << "s" << std::endl;
				return delta;
			}
			return Delta(0);
		}
		[[nodiscard]] std::string GetName() const {
			return m_name;
		}

		template<typename Fn, typename... Args>
		static Delta Measure(std::string name, Fn&& fn, Args&&... args) {
			LoggingTimer timer(std::move(name));
			fn(std::forward<Args>(args)...);
			return timer.Stop();
		}
	private:
		std::string m_name;
	};
}
