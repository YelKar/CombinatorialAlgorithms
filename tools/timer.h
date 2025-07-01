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

        [[nodiscard]] double toNanoseconds() const { return nanoseconds; }
        [[nodiscard]] double toMicroseconds() const { return nanoseconds / 1e3; }
        [[nodiscard]] double toMilliseconds() const { return nanoseconds / 1e6; }
        [[nodiscard]] double toSeconds() const { return nanoseconds / 1e9; }
        [[nodiscard]] double toMinutes() const { return toSeconds() / 60; }
        [[nodiscard]] double toHours() const { return toMinutes() / 60; }
        [[nodiscard]] double toDays() const { return toHours() / 24; }
        [[nodiscard]] double toYears() const { return toDays() / 365; }

        [[nodiscard]] std::string toString() const {
            std::ostringstream oss;
            oss << "Delta {\n"
                << "    nanoseconds = " << toNanoseconds() << "\n"
                << "    microseconds = " << toMicroseconds() << "\n"
                << "    milliseconds = " << toMilliseconds() << "\n"
                << "    seconds = " << toSeconds() << "\n"
                << "    minutes = " << toMinutes() << "\n"
                << "    hours = " << toHours() << "\n"
                << "    days = " << toDays() << "\n"
                << "    years = " << toYears() << "\n"
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
