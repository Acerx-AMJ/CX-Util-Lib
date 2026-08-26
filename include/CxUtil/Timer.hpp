#ifndef CX_UTIL_TIMER_HPP
#define CX_UTIL_TIMER_HPP

#include "Config.hpp" // IWYU pragma: export
#include <chrono>
#include <thread>
#include <cmath>

namespace cx::util
{
   namespace
   {
      using Clock = std::chrono::steady_clock;
      using TimePoint = std::chrono::time_point<Clock>;
      using Duration = std::chrono::duration<float>;
   } // namespace

   /// @brief Format time.
   /// @param seconds Time in seconds.
   /// @return Formatted time.
   inline std::string formatTime(float seconds, const std::string& separator = ":") noexcept
   {
      const int hours = static_cast<int>(seconds / 3600);
      seconds = std::fmod(seconds, 3600);
      const int minutes = static_cast<int>(seconds / 60);
      seconds = std::fmod(seconds, 60);

      return std::format("{:02}{}{:02}{}{:05.2f}", hours, separator, minutes, separator, seconds);
   }

   /// @brief Delay code execution.
   /// @param seconds Time in seconds.
   inline bool wait(float seconds) noexcept
   {
      std::this_thread::sleep_for(Duration(seconds));
      return true;
   }

   /// @brief Measure time.
   class BasicTimer
   {
   public:
      // Constructors

      /// @brief Start the timer.
      inline BasicTimer() noexcept
      {
         start = Clock::now();
      };

      /// @brief Start the timer at the given time.
      /// @param seconds Time in seconds.
      inline BasicTimer(float seconds) noexcept
      {
         const Duration duration(seconds);
         start = Clock::now() - std::chrono::duration_cast<Clock::duration>(duration);
      }

      ~BasicTimer() = default;

      // Time functions

      /// @brief Reset timer.
      inline void reset() noexcept
      {
         start = Clock::now();
      }

      /// @brief Get total elapsed time and reset timer.
      /// @return Time in seconds.
      inline float restart() noexcept
      {
         const auto now = Clock::now();
         const float elapsed = Duration(now - start).count();

         start = std::move(now);
         return elapsed;
      }

      /// @brief Get total elapsed time.
      /// @return Time in seconds.
      inline float getElapsed() const noexcept
      {
         return Duration(Clock::now() - start).count();
      }

      /// @brief Set elapsed time.
      /// @param seconds Time in seconds.
      inline void setElapsed(float seconds) noexcept
      {
         const Duration duration(seconds);
         start = Clock::now() - std::chrono::duration_cast<Clock::duration>(duration);
      }

   protected:
      TimePoint start;
   };

   /// @brief Pause and measure time.
   class Timer
   {
   public:
      // Constructors

      /// @brief Start the timer.
      inline Timer() noexcept
      {
         start = Clock::now();
      }

      /// @brief Start the timer at the given time.
      /// @param seconds Time in seconds.
      inline Timer(float seconds) noexcept
      {
         elapsed = seconds;
         start = Clock::now();
      }

      ~Timer() = default;

      // Time functions

      /// @brief Reset timer.
      inline void reset() noexcept
      {
         paused = false;
         elapsed = 0.f;
         start = Clock::now();
      }

      /// @brief Get total elapsed time and reset timer.
      /// @return Time in seconds.
      inline float restart() noexcept
      {
         const auto now = Clock::now();
         const float total = elapsed + (paused ? 0.f : Duration(now - start).count());

         paused = false;
         elapsed = 0.f;
         start = std::move(now);

         return total;
      }

      /// @brief Get total elapsed time.
      /// @return Time in seconds.
      inline float getElapsed() const noexcept
      {
         return elapsed + (paused ? 0.f : Duration(Clock::now() - start).count());
      }

      /// @brief Set elapsed time.
      /// @param seconds Time in seconds.
      inline void setElapsed(float seconds) noexcept
      {
         elapsed = seconds;
         start = Clock::now();
      }

      // Pause functions

      /// @brief Set timer paused.
      /// @param isPaused Should timer be paused.
      inline void setPaused(bool isPaused) noexcept
      {
         if (isPaused && !paused)
         {
            paused = true;
            elapsed += Duration(Clock::now() - start).count();
         }
         else if (!isPaused && paused)
         {
            paused = false;
            start = Clock::now();
         }
      }

      /// @brief Toggle timer paused.
      inline void togglePaused() noexcept
      {
         if (paused)
            start = Clock::now();
         else
            elapsed += Duration(Clock::now() - start).count();

         paused = !paused;
      }

      /// @brief Pause the timer.
      inline void pause() noexcept
      {
         if (!paused)
         {
            paused = true;
            elapsed += Duration(Clock::now() - start).count();
         }
      }

      /// @brief Resume the timer.
      inline void resume() noexcept
      {
         if (paused)
         {
            paused = false;
            start = Clock::now();
         }
      }

      /// @brief Check if timer is paused.
      /// @return True if paused.
      inline bool isPaused() const noexcept
      {
         return paused;
      }

   protected:
      TimePoint start;
      float elapsed = 0.f;
      bool paused = false;
   };

   /// @brief Count down a timer.
   class BasicCountdownTimer : public BasicTimer
   {
   public:
      // Constructors

      /// @brief Start countdown timer.
      /// @param seconds Time in seconds.
      inline BasicCountdownTimer(float seconds) noexcept
      {
         target = seconds;
         start = Clock::now();
      }
      
      ~BasicCountdownTimer() = default;

      // Time functions

      /// @brief Set target time.
      /// @param seconds Time in seconds.
      inline void setTarget(float seconds) noexcept
      {
         target = seconds;
      }

      /// @brief Get target time.
      /// @return Time in seconds.
      inline float getTarget() const noexcept
      {
         return target;
      }

      /// @brief Get remaining time.
      /// @return Time in seconds.
      inline float getRemaining() const noexcept
      {
         const float total = target - Duration(Clock::now() - start).count();
         return (total <= 0.f ? 0.f : total);
      }

      /// @brief Check if timer is finished counting down.
      /// @return True if finished.
      inline bool isFinished() const noexcept
      {
         return target - Duration(Clock::now() - start).count() <= 0.f;
      }

   protected:
      float target = 0.f;
   };

   /// @brief Count down and pause a timer.
   class CountdownTimer : public Timer
   {
   public:
      // Constructors

      /// @brief Start countdown timer.
      /// @param seconds Time in seconds.
      inline CountdownTimer(float seconds) noexcept
      {
         target = seconds;
         start = Clock::now();
      }
      
      ~CountdownTimer() = default;

      // Time functions

      /// @brief Set target time.
      /// @param seconds Time in seconds.
      inline void setTarget(float seconds) noexcept
      {
         target = seconds;
      }

      /// @brief Get target time.
      /// @return Time in seconds.
      inline float getTarget() const noexcept
      {
         return target;
      }

      /// @brief Get remaining time.
      /// @return Time in seconds.
      inline float getRemaining() const noexcept
      {
         const float total = target - (elapsed + (paused ? 0.f : Duration(Clock::now() - start).count()));
         return (total <= 0.f ? 0.f : total);
      }

      /// @brief Check if timer is finished counting down.
      /// @return True if finished.
      inline bool isFinished() const noexcept
      {
         return target - (elapsed + (paused ? 0.f : Duration(Clock::now() - start).count())) <= 0.f;
      }

   protected:
      float target = 0.f;
   };

   /// @brief Measure laps.
   class BasicLapTimer : public BasicTimer
   {
   public:
      // Constructors

      /// @brief Start the lap timer.
      inline BasicLapTimer() noexcept
      {
         start = Clock::now();
      }

      /// @brief Start the lap timer at the given time point.
      /// @param seconds Time in seconds.
      inline BasicLapTimer(float seconds) noexcept
      {
         const Duration duration(seconds);
         start = Clock::now() - std::chrono::duration_cast<Clock::duration>(duration);
      }

      ~BasicLapTimer() = default;

      // Lap functions

      /// @brief Push back a lap.
      inline void lap() noexcept
      {
         auto now = Clock::now();
         laps.push_back(Duration(now - start).count());
         start = std::move(now);
      }

      /// @brief Get recorded laps.
      /// @return Laps.
      inline const std::vector<float>& getLaps() const noexcept
      {
         return laps;
      }

      /// @brief Get total elapsed time.
      inline float getTotalElapsed() const noexcept
      {
         float total = 0.f;

         for (const auto& lap : laps)
            total += lap;
         return total + Duration(Clock::now() - start).count();
      }

   protected:
      std::vector<float> laps;
   };

   /// @brief Measure and pause laps.
   class LapTimer : public Timer
   {
   public:
      // Constructors

      /// @brief Start the lap timer.
      inline LapTimer() noexcept
      {
         start = Clock::now();
      }

      /// @brief Start the lap timer at the given time point.
      /// @param seconds Time in seconds.
      inline LapTimer(float seconds) noexcept
      {
         elapsed = seconds;
         start = Clock::now();
      }

      ~LapTimer() = default;

      // Lap functions

      /// @brief Push back a lap.
      inline void lap() noexcept
      {
         auto now = Clock::now();
         laps.push_back(elapsed + (paused ? 0.f : Duration(now - start).count()));
         elapsed = 0.f;
         start = std::move(now);
      }

      /// @brief Get recorded laps.
      /// @return Laps.
      inline const std::vector<float>& getLaps() const noexcept
      {
         return laps;
      }

      /// @brief Get total elapsed time.
      inline float getTotalElapsed() const noexcept
      {
         float total = 0.f;

         for (const auto& lap : laps)
            total += lap;
         return total + elapsed + (paused ? 0.f : Duration(Clock::now() - start).count());
      }

   protected:
      std::vector<float> laps;
   };
} // namespace cx::util

#endif // CX_UTIL_TIMER_HPP
