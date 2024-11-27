import { createLogger, transports, format } from 'winston';


const logger = createLogger({
    level: 'info', // Nivel de logging
    format: format.combine(
        format.timestamp(),
        format.printf(({ timestamp, level, message }) => {
            return `[${timestamp}] ${level.toUpperCase()}: ${message}`;
        })
    ),
    transports: [
        new transports.Console(), // Logs en consola
        new transports.File({ filename: 'logs/app.log' }) // Logs en archivo
    ]
});

export default logger;
