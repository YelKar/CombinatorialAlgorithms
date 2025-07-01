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

        [[nodiscard]] double ToNanoseconds() const { return nanoseconds; }
        [[nodiscard]] double ToMicroseconds() const { return nanoseconds / 1e3; }
        [[nodiscard]] double ToMilliseconds() const { return nanoseconds / 1e6; }
        [[nodiscard]] double ToSeconds() const { return nanoseconds / 1e9; }
        [[nodiscard]] double ToMinutes() const { return ToSeconds() / 60; }
        [[nodiscard]] double ToHours() const { return ToMinutes() / 60; }
        [[nodiscard]] double ToDays() const { return ToHours() / 24; }
        [[nodiscard]] double ToYears() const { return ToDays() / 365; }

        [[nodiscard]] std::string ToString() const {
            std::ostringstream oss;
            oss << "Delta {\n"
                << "    nanoseconds = " << ToNanoseconds() << "\n"
                << "    microseconds = " << ToMicroseconds() << "\n"
                << "    milliseconds = " << ToMilliseconds() << "\n"
                << "    seconds = " << ToSeconds() << "\n"
                << "    minutes = " << ToMinutes() << "\n"
                << "    hours = " << ToHours() << "\n"
                << "    days = " << ToDays() << "\n"
                << "    years = " << ToYears() << "\n"
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
        void Start() {
            _start = std::chrono::high_resolution_clock::now();
        }

        Delta GetDelta() {
            Delta delta(static_cast<double>((std::chrono::high_resolution_clock::now() - _start).count()));
            return delta;
        }
    };
}
