/*
** EPITECH PROJECT, 2025
** LoggerLib
** File description:
** Logger
*/

#pragma once

    #include <ctime>
    #include <string>
    #include <fstream>
    #include <iomanip>
    #include <iostream>
    #include <filesystem>

namespace debug {
    class Logger {
        public:
            enum class Output {
                Console,
                File,
                Both
            };
            
            static Logger& getInstance();

            static void clearLogFile();
            static bool infoLog(const std::string& message);
            static bool debugLog(const std::string& message);
            static bool warningLog(const std::string& message);
            static bool infoLog(const std::string& message, Output output);
            static bool debugLog(const std::string& message, Output output = Output::File);
            static bool warningLog(const std::string& message, Output output = Output::File);
            
            static Output getDefaultOutput();

            static void setDefaultOutput(Output output);
        private:
            Logger();
            ~Logger();
            Logger(const Logger&) = delete;
            Logger& operator=(const Logger&) = delete;

            void logCurrentTime() const;
            void logCurrentHour() const;

            void setLogFile(const std::string& filePath);

            std::string getLogFile() const;

            bool createLogFile();
            bool logFileExists() const;
            bool logFileIsWritable() const;
            bool log(const std::string& message);

            Output _output;
            std::string _logFilePath;
    };
}

/************************************************************
**           >>>>   STATIC  MEMBER VARIABLES   <<<<        **
************************************************************/


inline constexpr debug::Logger::Output Console = debug::Logger::Output::Console;
inline constexpr debug::Logger::Output File = debug::Logger::Output::File;
inline constexpr debug::Logger::Output Both = debug::Logger::Output::Both;


/************************************************************
 *          >>>>   STATIC  MEMBER FUNCTIONS   <<<<         **
************************************************************/


/**
 * @brief Log an info message with the current time.
 *
 * This function logs the message with the current time.
 * @param message The message to log.
 * @param output (optional) The output destination for the log (console, file, or both).
 * @return true if the log was successful, false otherwise.
 */
inline void InfoLog(const std::string& msg, debug::Logger::Output output)
{
    debug::Logger::getInstance().infoLog(msg, output);
}

/**
 * @brief Log an info message with the current time.
 *
 * This function logs the message with the current time.
 * @param message The message to log.
 * @param output (optional) The output destination for the log (console, file, or both).
 * @return true if the log was successful, false otherwise.
 */
inline void InfoLog(const std::string& msg)
{
    debug::Logger::getInstance().infoLog(msg, debug::Logger::getDefaultOutput());
}

/**
 * @brief Log a message with the current time.
 *
 * This function logs the message with the current time.
 * @param message The message to log.
 * @param output (optional) The output destination for the log (console, file, or both).
 * @return true if the log was successful, false otherwise.
 */
inline void DebugLog(const std::string& msg, debug::Logger::Output output)
{
    debug::Logger::getInstance().debugLog(msg, output);
}

/**
 * @brief Log a message with the current time.
 *
 * This function logs the message with the current time.
 * @param message The message to log.
 * @param output (optional) The output destination for the log (console, file, or both).
 * @return true if the log was successful, false otherwise.
 */
inline void DebugLog(const std::string& msg)
{
    debug::Logger::getInstance().debugLog(msg, debug::Logger::getDefaultOutput());
}

/**
 * @brief Log a warning message with the current time.
 *
 * This function logs the message with the current time.
 * @param message The message to log.
 * @param output (optional) The output destination for the log (console, file, or both).
 * @return true if the log was successful, false otherwise.
 */
inline void WarningLog(const std::string& msg, debug::Logger::Output output)
{
    debug::Logger::getInstance().warningLog(msg, output);
}

/**
 * @brief Log a warning message with the current time.
 *
 * This function logs the message with the current time.
 * @param message The message to log.
 * @param output (optional) The output destination for the log (console, file, or both).
 * @return true if the log was successful, false otherwise.
 */
inline void WarningLog(const std::string& msg)
{
    debug::Logger::getInstance().warningLog(msg, debug::Logger::getDefaultOutput());
}

/**
 * @brief Clear the log file.
 *
 * This function clears the log file by truncating it.
 */
inline static void clearLogFile()
{
    debug::Logger::clearLogFile();
}

/**
 * @brief Set the default output for the logger.
 *
 * This function sets the default output for the logger.
 * @param output The output destination for the log (console, file, or both).
 */
inline static void setDefaultOutput(debug::Logger::Output output)
{
    debug::Logger::setDefaultOutput(output);
}

/**
 * @brief Get the default output for the logger.
 *
 * This function returns the default output for the logger.
 * @return The default output destination for the log (console, file, or both).
 */
inline static debug::Logger::Output getDefaultOutput()
{
    return debug::Logger::getDefaultOutput();
}
