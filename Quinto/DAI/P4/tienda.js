import express from 'express';
import nunjucks from 'nunjucks';
import connectDB from './model/db.js';
import TiendaRouter from './routes/router_tienda.js';
import UsuariosRouter from './routes/usuarios.js';
import routerApi from './routes/router_api.js';
import session from 'express-session';
import cookieParser from 'cookie-parser';
import jwt from 'jsonwebtoken';
import dotenv from 'dotenv';
import logger from './logger.js';

dotenv.config();

const app = express();
connectDB();

const IN = process.env.IN || 'development';

app.use(express.urlencoded({ extended: true }));
app.use(express.json());
app.use(cookieParser());

//  habilitar el uso de sesiones, lo cual permitirá guardar el carrito de cada usuario
app.use(session({
  secret: 'my-secret',
  resave: false,
  saveUninitialized: false
}));

nunjucks.configure('views', {
  autoescape: true,
  noCache: IN === 'development',
  watch: IN === 'development',
  express: app
});
app.set('view engine', 'html');

// Archivos estáticos
app.use(express.static('public'));

// // Prueba del servidor
// app.get('/hola', (req, res) => {
//   res.send('Hola desde el servidor');
// });

// Middleware de autenticación
const autentificacion = (req, res, next) => {
  const token = req.cookies.access_token;

  if (token) {
    try {
      const data = jwt.verify(token, process.env.SECRET_KEY);
      req.username = data.usuario; // Añadimos el usuario al request
      req.admin = data.admin; // Información adicional sobre roles
    } catch {
      console.error('Token inválido:', err);
    }
  } else {
    req.username = null;
    req.admin = false;
  }
  next();
};

// Middleware global para registrar todas las solicitudes
app.use((req, res, next) => {
  logger.info(`Petición: ${req.method} ${req.url}`);
  next();
});

// intercepta el 
app.use(autentificacion);

// Importar rutas
app.use('/', TiendaRouter);
app.use('/',UsuariosRouter);
app.use('/api', routerApi);

const PORT = process.env.PORT || 8000;
app.listen(PORT, () => {
  console.log(`Servidor ejecutándose en http://localhost:${PORT}`);
});
