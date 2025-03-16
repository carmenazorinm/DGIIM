import express from 'express';
import Productos from '../model/productos.js';
import Usuarios from '../model/usuarios.js';
import logger from '../logger.js'; // Importamos el logger

const router = express.Router();

// Middleware para cargar categorías en todas las vistas
router.use(async (req, res, next) => {
  try {
    const categorias = await Productos.distinct('category');
    res.locals.categorias = categorias; // Esto permite acceder a `categorias` en `base.html`
    logger.info('Categorías cargadas correctamente');
  } catch (err) {
    logger.error(`Error al cargar categorías: ${err.message}`);
    res.locals.categorias = []; // Si falla, establece un array vacío para evitar errores
  }
  next();
});

// Ruta para la portada
router.get('/portada', async (req, res) => {
  try {
    const productos = await Productos.find({});
    const carrito = req.session.carrito || [];
    logger.info('Productos obtenidos para la portada');
    res.render('portada.html', { productos, carrito, categorias: res.locals.categorias, titulo: 'Productos Destacados', usuario: req.username });
  } catch (err) {
    logger.error(`Error al obtener productos para la portada: ${err.message}`);
    res.status(500).send({ err });
  }
});

// Ruta para buscar productos
router.post('/buscar', async (req, res) => {
  const query = req.body.query.toLowerCase(); // Obtener la consulta y convertirla a minúsculas
  try {
    const productos = await Productos.find({
      $or: [
        { title: { $regex: query, $options: 'i' } }, // Buscar en el título
        { description: { $regex: query, $options: 'i' } } // Buscar en la descripción
      ]
    });
    logger.info(`Búsqueda realizada con query: "${query}"`);
    const carrito = req.session.carrito || [];
    res.render('portada.html', { productos, carrito, categorias: res.locals.categorias, titulo: `Productos sobre "${query}"`, usuario: req.username });
  } catch (err) {
    logger.error(`Error al realizar la búsqueda: ${err.message}`);
    res.status(500).send({ err });
  }
});

// Ruta para mostrar productos por categoría
router.get('/categoria', async (req, res) => {
  try {
    const categoria = req.query.nombre;
    const productos = await Productos.find(categoria ? { category: categoria } : {});
    logger.info(`Productos obtenidos para la categoría: "${categoria || 'todas'}"`);
    res.render('portada.html', { productos, categorias: res.locals.categorias, categoriaSeleccionada: categoria, titulo: `Productos en la categoría "${categoria}"`, usuario: req.username });
  } catch (err) {
    logger.error(`Error al obtener productos por categoría: ${err.message}`);
    res.status(500).send({ err });
  }
});

// Ruta para mostrar detalles de un producto
router.get('/productos/:id', async (req, res) => {
  try {
    const producto = await Productos.findById(req.params.id);
    if (!producto) {
      logger.warn(`Producto con ID ${req.params.id} no encontrado`);
      return res.status(404).send('Producto no encontrado');
    }
    logger.info(`Producto con ID ${req.params.id} encontrado`);
    res.render('detalle_producto.html', { producto, usuario: req.username, admin: req.admin });
  } catch (err) {
    logger.error(`Error al obtener el producto con ID ${req.params.id}: ${err.message}`);
    res.status(500).send(err);
  }
});

// Ruta para agregar un producto al carrito
router.post('/carrito/agregar', async (req, res) => {
  const { productoId } = req.body;
  
  if (!req.session.carrito) {
    req.session.carrito = [];
  }

  try {
    const producto = await Productos.findById(productoId);
    if (producto) {
      req.session.carrito.push(producto);
      logger.info(`Producto con ID ${productoId} agregado al carrito`);
      res.redirect('/carrito');
    } else {
      logger.warn(`Intento de agregar un producto no encontrado al carrito: ID ${productoId}`);
      res.status(404).send('Producto no encontrado');
    }
  } catch (err) {
    logger.error(`Error al agregar producto al carrito: ${err.message}`);
    res.status(500).send('Error al agregar producto al carrito');
  }
});

// Ruta para ver el carrito
router.get('/carrito', (req, res) => {
  const carrito = req.session.carrito || [];
  const total = carrito.reduce((sum, producto) => sum + producto.price, 0);
  logger.info('Carrito visualizado por el usuario');
  res.render('carrito.html', { carrito, total, usuario: req.username });
});

// Ruta para editar un producto
router.post('/editar-producto/:id', async (req, res) => {
  if (!req.admin) {
    logger.warn(`Intento de editar producto por un usuario no autorizado: ID ${req.params.id}`);
    return res.status(403).send('No tienes permiso para realizar esta acción');
  }

  const { nuevoTitulo, nuevoPrecio } = req.body;

  try {
    const producto = await Productos.findByIdAndUpdate(
      req.params.id,
      { title: nuevoTitulo, price: nuevoPrecio },
      { new: true, runValidators: true }
    );
    logger.info(`Producto con ID ${req.params.id} editado con éxito`);
    res.redirect(`/productos/${producto._id}`);
  } catch (error) {
    logger.error(`Error al editar el producto con ID ${req.params.id}: ${error.message}`);
    res.status(400).send('Error al actualizar el producto');
  }
});

export default router;
