import express from 'express';
import Productos from '../model/productos.js';

const router = express.Router();

// Middleware para cargar categorías en todas las vistas
router.use(async (req, res, next) => {
  try {
    const categorias = await Productos.distinct('category');
    res.locals.categorias = categorias; // Esto permite acceder a `categorias` en `base.html`
  } catch (err) {
    console.error('Error al cargar categorías:', err);
    res.locals.categorias = []; // Si falla, establece un array vacío para evitar errores
  }
  next();
});

// Ruta para la portada
router.get('/portada', async (req, res) => {
  try {
    const productos = await Productos.find({});
    const carrito = req.session.carrito || [];
    res.render('portada.html', { productos, carrito, categorias: res.locals.categorias, titulo: 'Productos Destacados' });
  } catch (err) {
    console.error(err);
    res.status(500).send({ err });
  }
});

router.post('/buscar', async (req, res) => {
  const query = req.body.query.toLowerCase(); // Obtener la consulta y convertirla a minúsculas
  try {
    const productos = await Productos.find({
      $or: [
        { title: { $regex: query, $options: 'i' } }, // Buscar en el título
        { description: { $regex: query, $options: 'i' } } // Buscar en la descripción
      ]
    });

    const carrito = req.session.carrito || [];
    res.render('portada.html', { productos, carrito, categorias: res.locals.categorias, titulo: `Productos sobre "${query}"` });
  } catch (err) {
    console.error(err); // Para facilitar la depuración
    res.status(500).send({ err });
  }
});

// Ruta para mostrar productos por categoría
router.get('/categoria', async (req, res) => {
  try {
    const categoria = req.query.nombre;
    const categorias = await Productos.distinct('category');
    const productos = await Productos.find(categoria ? { category: categoria } : {});
    res.render('portada.html', { productos, categorias, categoriaSeleccionada: categoria, titulo: `Productos en la categoría "${categoria}"` });
  } catch (err) {
    console.error(err);
    res.status(500).send({ err });
  }
});

router.get('/productos/:id', async (req, res) => {
  try {
    const producto = await Productos.findById(req.params.id);
    if (!producto) {
      return res.status(404).send('Producto no encontrado');
    }
    res.render('detalle_producto.html', { producto });
  } catch (err) {
    res.status(500).send(err);
  }
});

router.post('/carrito/agregar', async (req, res) => {
  const { productoId } = req.body;
  
  // Asegúrate de inicializar la sesión si no está ya creada
  if (!req.session.carrito) {
    req.session.carrito = [];
  }
  
  // Busca el producto por ID y agrégalo al carrito
  const producto = await Productos.findById(productoId);
  if (producto) {
    req.session.carrito.push(producto); // Añade el producto a la sesión
    console.log(req.session.carrito); // Para depuración
    res.redirect('/carrito'); // Redirige a la página del carrito
  } else {
    res.status(404).send('Producto no encontrado');
  }
});

// Ruta para ver el carrito
router.get('/carrito', (req, res) => {
  const carrito = req.session.carrito || [];
  const total = carrito.reduce((sum, producto) => sum + producto.price, 0); // Cambiar de precio a price
  res.render('carrito.html', { carrito, total });
});

export default router;
