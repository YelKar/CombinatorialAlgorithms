#pragma once
#include <chrono>
#include <cmath>

namespace tools {
    class Delta {
    private:
        double nanoseconds;

    public:
        Delta() : nanoseconds(0) {}
        explicit Delta(double ns) : nanoseconds(ns) {}

        [[nodiscard]] double getNanoseconds() const { return nanoseconds; }
        [[nodiscard]] double getMicroseconds() const { return nanoseconds / 1e3; }
        [[nodiscard]] double getMilliseconds() const { return nanoseconds / 1e6; }
        [[nodiscard]] double getSeconds() const { return nanoseconds / 1e9; }
        [[nodiscard]] double getMinutes() const { return getSeconds() / 60; }
        [[nodiscard]] double getHours() const { return getMinutes() / 60; }
        [[nodiscard]] double getDays() const { return getHours() / 24; }
        [[nodiscard]] double getYears() const { return getDays() / 365; }

        [[nodiscard]] std::string toString() const {
            std::ostringstream oss;
            oss << "Delta {\n"
                << "    nanoseconds = " << getNanoseconds() << "\n"
                << "    microseconds = " << getMicroseconds() << "\n"
                << "    milliseconds = " << getMilliseconds() << "\n"
                << "    seconds = " << getSeconds() << "\n"
                << "    minutes = " << getMinutes() << "\n"
                << "    hours = " << getHours() << "\n"
                << "    days = " << getDays() << "\n"
                << "    years = " << getYears() << "\n"
                << "}";
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

		double& operator *() {
			return this->nanoseconds;
		}

		double operator *() const {
			return this->nanoseconds;
		}
    };

    class Timer {
        std::chrono::high_resolution_clock::time_point _start;
    public:
        void start() {
            _start = std::chrono::high_resolution_clock::now();
        }

        Delta getDelta() {
            Delta delta(static_cast<double>((std::chrono::high_resolution_clock::now() - _start).count()));
            return delta;
        }
    };
}
