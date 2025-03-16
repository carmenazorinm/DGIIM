import express from 'express';
import jwt from 'jsonwebtoken';
import Usuarios from '../model/usuarios.js';
import dotenv from 'dotenv';
import logger from '../logger.js';

dotenv.config();

const router = express.Router();

// Mostrar formulario de login
router.get('/login', (req, res) => {
  logger.info('Formulario de login solicitado.');
  res.render('login.html');
});

// Procesar el login
router.post('/login', async (req, res) => {
  const { username, password } = req.body;

  if (!username || !password) {
    logger.warn('Intento de login fallido: falta de datos.');
    return res.status(400).render('login.html', { error: 'Debe completar todos los campos' });
  }

  try {
    const user = await Usuarios.findOne({ username });
    if (!user) {
      logger.warn(`Intento de login fallido: Usuario "${username}" no encontrado.`);
      return res.status(401).render('login.html', { error: 'Usuario no encontrado' });
    }

    if (user.password !== password) {
      logger.warn(`Intento de login fallido: Contraseña incorrecta para el usuario "${username}".`);
      return res.status(401).render('login.html', { error: 'Contraseña incorrecta' });
    }

    // Generar token JWT
    const token = jwt.sign({ usuario: user.username, admin: user.admin }, process.env.SECRET_KEY);

    logger.info(`Login exitoso: Usuario "${username}".`);
    res.cookie('access_token', token, {
      httpOnly: true,
      secure: process.env.NODE_ENV === 'production', // Solo en https si está en producción
    }).render('bienvenida.html', { usuario: user.username });
  } catch (error) {
    logger.error(`Error al procesar el login: ${error.message}`);
    res.status(500).send('Error en el servidor');
  }
});

// Logout
router.get('/logout', (req, res) => {
  const usuario = req.username || 'usuario desconocido';
  logger.info(`Logout realizado por: "${usuario}".`);
  res.clearCookie('access_token').render('despedida.html', { usuario });
});

export default router;
