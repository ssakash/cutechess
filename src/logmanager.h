/*
    This file is part of SloppyGUI.

    SloppyGUI is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SloppyGUI is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SloppyGUI.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QtGlobal>
#include <QList>

#include "manager.h"

class LoggerBase;

/**
 * LogManager is a singleton type class for handling logging.
 *
 * The functionality of LogManager resolves around the different loggers
 * derieved from the LoggerBase class. Different loggers enable logging
 * messages to different output formats such as to the GUI and standard
 * output steams.
 *
 * LogManager always has one logger enabled called the StdOutLogger which
 * log messages to standard output and standard error.
 *
 * You can create your own loggers by creating a derieved class from
 * LoggerBase and calling the addLogger() method.
 *
 * For application logging purposes you shouldn't use this class directly
 * but use Qt's own logging functions such as qDebug(), qWarning(),
 * qCritical() and qFatal().
 *
 * You can control the output of messages by setting the logging level
 * higher (setLoggingLevel() method).
 *
 * @see StdOutLogger
 * @see GuiLogger
 * @see setLoggingLevel
*/
class LogManager : public ManagerBase<LogManager>
{
	friend class ManagerBase<LogManager>;

	public:
		/**
		 * Adds new a logger to the list of loggers.
		 * @param logger Logger to add.
		*/
		void addLogger(LoggerBase* logger);

		/**
		 * Restores the default logger (standard output logger) and
		 * removes all other loggers.
		*/
		void restoreDefaultLogger();

		/**
		 * Logs a message with the currently installed loggers.
		 * You should use Qt's debug message functions (qDebug, qWarning etc.)
		 * instead of calling this function.
		 * @param type Message's type.
		 * @param message The message.
		*/
		void log(QtMsgType type, const char *message);

		/**
		 * Sets the visibility of logging messages.
		 * Logging level controls which messages are passed to the active
		 * loggers. If the message's level is lower than the current
		 * logging level the message is ignored.
		 * The priorities of the messages are (from lowest):
		 *
		 * Debug messages
		 * Warning messages
		 * Critical messages
		 * Fatal messages
		 *
		 * So for example calling this method with value QtWarningMsg would
		 * allow only warning, critical and fatal messages to pass.
		 *
		 * @param level The level that message must be in order to be logged.
		 * @see loggingLevel
		*/
		void setLoggingLevel(QtMsgType level);

		/**
		 * Return the current logging level.
		 * @return Current logging level.
		 * @see setLoggingLevel
		*/
		QtMsgType loggingLevel() const;

		/**
		 * Custom message handler for Qt.
		*/
		static void messageHandler(QtMsgType type, const char *message);

	protected:
		LogManager();
		~LogManager();

	private:
		QList<LoggerBase*> m_loggers;
		QtMsgType m_loggingLevel;
};

#endif // LOGMANAGER_H
