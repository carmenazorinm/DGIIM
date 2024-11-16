import express from 'express';
import jwt from 'jsonwebtoken';
import bcrypt from 'bcrypt';
import Usuarios from '../model/usuarios.js';
import dotenv from 'dotenv';

dotenv.config();

const router = express.Router();

// Mostrar formulario de login
router.get('/login', (req, res) => {
  res.render('login.html');
});

// Recoger datos del formulario de login
router.post('/login', async (req, res) => {
  const { username, password } = req.body;

  try {
    const user = await Usuarios.findOne({ username });
    if (!user) {
        return res.status(401).send('Usuario no encontrado');
    }

    //const validPassword = await bcrypt.compare(password, user.password);
    if (user.password !== password) {
        return res.status(401).send('Contraseña incorrecta');
    }

    const token = jwt.sign({ usuario: user.username }, process.env.SECRET_KEY, { expiresIn: '1h' });

    res
    .cookie('access_token', token, { httpOnly: true, secure: process.env.IN === 'production' })
    .render('bienvenida.html', { usuario: user.username });
  } catch (error) {
    console.error('Error en /login:', error);
    res.status(500).send('Error en el servidor');
  }
});

// Logout: Limpiar la cookie de autenticación
router.get('/logout', (req, res) => {
  const usuario = req.username;
  res.clearCookie('access_token').render('despedida.html', { usuario });
});

router.get('/bienvenida', (req, res) => {
    const usuario = req.username; // Usuario autenticado desde el middleware
    if (!usuario) {
      return res.redirect('/login');
    }
    res.render('bienvenida.html', { usuario });
});

export default router;
