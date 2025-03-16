import fetch from 'node-fetch';  // Asegúrate de usar node-fetch
import fs from 'fs-extra';
import path from 'path';

const carpetaImagenes = './imagenes';  // Carpeta donde guardaremos las imágenes

// Función para descargar y guardar las imágenes
async function descargarImagen(url, nombreArchivo) {
  const response = await fetch(url);
  //const buffer = await response.buffer();
  const buffer = await response.arrayBuffer();

  const rutaArchivo = path.join(carpetaImagenes, nombreArchivo);
  await fs.outputFile(rutaArchivo, buffer);
  console.log(`Imagen guardada: ${nombreArchivo}`);
}

// Función para descargar todas las imágenes de los productos
async function descargarImagenesProductos() {
  try {
    // Creamos la carpeta si no existe
    await fs.ensureDir(carpetaImagenes);

    const response = await fetch('https://fakestoreapi.com/products');
    const productos = await response.json();

    // Descargar cada imagen
    for (const producto of productos) {
      const nombreArchivo = `${producto.id}-${producto.title.replace(/\s+/g, '_')}.jpg`;
      await descargarImagen(producto.image, nombreArchivo);
    }

    console.log('Todas las imágenes han sido descargadas.');
  } catch (err) {
    console.error('Error al descargar las imágenes:', err);
  }
}

descargarImagenesProductos();
