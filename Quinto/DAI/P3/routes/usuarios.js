import express from 'express';
import jwt from 'jsonwebtoken';
import Usuarios from '../model/usuarios.js';
import dotenv from 'dotenv';

dotenv.config();

const router = express.Router();

// Mostrar formulario de login
router.get('/login', (req, res) => {
  res.render('login.html');
});

// Procesar el login
router.post('/login', async (req, res) => {
  const { username, password } = req.body;

  if (!username || !password) {
    //console.log('Faltan datos');
    return res.status(400).render('login.html', { error: 'Debe completar todos los campos' });
  }

  try {
    const user = await Usuarios.findOne({ username });
    if (!user) {
      //console.log('Usuario no encontrado');
      return res.status(401).render('login.html', { error: 'Usuario no encontrado' });
    }

    if (user.password !== password) {
      return res.status(401).render('login.html', { error: 'Contraseña incorrecta' });
    }
    // const esValida = await user.compararPassword(password);
    // if (!esValida) {
    //   console.log('Contraseña incorrecta');
    //   return res.status(401).render('login.html', { error: 'Contraseña incorrecta' });
    // }

    // Generar token JWT
    const token = jwt.sign({ usuario: user.username, admin: user.admin }, process.env.SECRET_KEY);

    res.cookie('access_token', token, {
      httpOnly: true,
      secure: process.env.NODE_ENV === 'production', // Solo en https si está en producción
    }).render('bienvenida.html', { usuario: user.username });
  } catch (error) {
    console.error(error);
    res.status(500).send('Error en el servidor');
  }
});

// Logout
router.get('/logout', (req, res) => {
  const usuario = req.username;
  res.clearCookie('access_token').render('despedida.html', { usuario });
});

export default router;
