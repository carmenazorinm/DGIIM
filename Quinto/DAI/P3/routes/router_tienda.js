import express from 'express';
import Productos from '../model/productos.js';
import Usuarios from '../model/usuarios.js';

const router = express.Router();

// Middleware para cargar categorías en todas las vistas
router.use(async (req, res, next) => {
  try {
    const categorias = await Productos.distinct('category');
    res.locals.categorias = categorias;
  } catch (err) {
    console.error('Error al cargar categorías:', err);
    res.locals.categorias = [];
  }
  next();
});

// Ruta para la portada
router.get('/portada', async (req, res) => {
  try {
    const productos = await Productos.find({});
    const carrito = req.session.carrito || [];
    const usuario = req.username; // Añadir usuario si está autentificado
    console.log("Usuario autenticado:", usuario);
    res.render('portada.html', { productos, carrito, categorias: res.locals.categorias, titulo: 'Productos Destacados',usuario });
  } catch (err) {
    console.error(err);
    res.status(500).send({ err });
  }
});

router.post('/buscar', async (req, res) => {
  const query = req.body.query.toLowerCase(); 
  try {
    const productos = await Productos.find({
      $or: [
        { title: { $regex: query, $options: 'i' } }, 
        { description: { $regex: query, $options: 'i' } } 
      ]
    });

    const carrito = req.session.carrito || [];
    res.render('portada.html', { productos, carrito, categorias: res.locals.categorias, titulo: `Productos sobre "${query}"` });
  } catch (err) {
    console.error(err); 
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

// Ruta para agregar un producto al carrito
router.post('/carrito/agregar', async (req, res) => {
  const { productoId } = req.body;

  // Asegúrate de que el usuario esté autenticado
  if (!req.username) {
    return res.status(401).send('Debes estar autenticado para agregar productos al carrito.');
  }

  const username = req.username;

  // Busca al usuario por su nombre de usuario
  const usuario = await Usuarios.findOne({ username });
  if (!usuario) {
    return res.status(404).send('Usuario no encontrado');
  }

  // Busca el producto por ID
  const producto = await Productos.findById(productoId);
  if (!producto) {
    return res.status(404).send('Producto no encontrado');
  }

  // Agrega el producto al carrito del usuario
  usuario.carrito.push(producto._id);
  await usuario.save(); // Guarda el carrito actualizado

  res.redirect('/carrito');
});

// Ruta para ver el carrito
router.get('/carrito', async (req, res) => {
  if (!req.username) {
    return res.status(401).send('Debes estar autenticado para ver el carrito.');
  }

  const username = req.username;

  // Busca al usuario y carga el carrito
  const usuario = await Usuarios.findOne({ username }).populate('carrito'); // Usa populate para obtener los productos completos
  if (!usuario) {
    return res.status(404).send('Usuario no encontrado');
  }

  const carrito = usuario.carrito;
  const total = carrito.reduce((sum, producto) => sum + producto.price, 0);

  res.render('carrito.html', { carrito, total });
});

export default router;
