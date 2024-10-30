import express from 'express';
import Productos from '../model/productos.js';

const router = express.Router();

router.get('/portada', async (req, res) => {
  try {
    const productos = await Productos.find({});
    res.render('portada.html', { productos });
  } catch (err) {
    res.status(500).send({ err });
  }
});

export default router;
