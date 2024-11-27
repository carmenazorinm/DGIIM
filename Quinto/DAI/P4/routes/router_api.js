import express from 'express';
import Productos from '../model/productos.js'; // Asegúrate de que Productos esté correctamente exportado.

const router = express.Router();

// GET /api/ratings - Lista de ratings de todos los productos.
router.get('/ratings', async (req, res) => {
  try {
    const productos = await Productos.find({}, 'title rating'); // Obtén título y rating.
    res.status(200).json(productos);
  } catch (err) {
    res.status(500).json({ error: 'Error al obtener los ratings' });
  }
});

// GET /api/ratings/:id - Rating de un producto específico.
router.get('/ratings/:id', async (req, res) => {
  try {
    const producto = await Productos.findById(req.params.id, 'title rating');
    if (!producto) {
      return res.status(404).json({ error: 'Producto no encontrado' });
    }
    res.status(200).json(producto);
  } catch (err) {
    res.status(500).json({ error: 'Error al obtener el rating del producto' });
  }
});

// PUT /api/ratings/:id - Modificar el rating de un producto.
router.put('/ratings/:id', async (req, res) => {
  const { rating } = req.body;

  // Validación básica del rating.
  if (typeof rating !== 'number' || rating < 0 || rating > 5) {
    return res.status(400).json({ error: 'El rating debe ser un número entre 0 y 5' });
  }

  try {
    const producto = await Productos.findByIdAndUpdate(
      req.params.id,
      { rating },
      { new: true, runValidators: true }
    );
    if (!producto) {
      return res.status(404).json({ error: 'Producto no encontrado' });
    }
    res.status(200).json(producto);
  } catch (err) {
    res.status(500).json({ error: 'Error al modificar el rating del producto' });
  }
});

export default router;
