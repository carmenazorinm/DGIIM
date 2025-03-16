import express from 'express';
import nunjucks from 'nunjucks';
import connectDB from './model/db.js';
import session from 'express-session';

const app = express();
connectDB();

const IN = process.env.IN || 'development';

app.use(express.urlencoded({ extended: true }));

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

// Importar rutas
import TiendaRouter from './routes/router_tienda.js';
app.use('/', TiendaRouter);

const PORT = process.env.PORT || 8000;
app.listen(PORT, () => {
  console.log(`Servidor ejecutándose en http://localhost:${PORT}`);
});
