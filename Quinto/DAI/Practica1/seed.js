import { MongoClient } from 'mongodb';
import fetch from 'node-fetch';
import dotenv from 'dotenv';

dotenv.config();

console.log(' seed.js ----------->');

const USER_DB = process.env.USERDB
const PASS = process.env.PASS

const url = `mongodb://${USER_DB}:${PASS}@localhost:27017`
const client = new MongoClient(url);

const dbName = 'myProject';

async function productosMasDe100() {
	const db = client.db(dbName);
	const productos = db.collection('productos');
	const resultado = await productos.find({price: { $gt:100 } }).toArray();
	console.log('Productos con precio mayor a 100$', resultado);
}

async function productosWinterOrdenadosPorPrecio() {
	const db = client.db(dbName);
	const productos = db.collection('productos');
	const resultado = await productos.find({ description: /winter/i }).sort({ price: 1}).toArray();
	console.log("productos que contienen 'winter' en la descripcion ordenados por precio", resultado);
}

async function joyeriaOrdenadaPorRating() {
	const db = client.db(dbName);
	const productos = db.collection('productos');
	const resultado = await productos.find({ category: 'jewelery' }).sort({ 'rating.rate': -1 }).toArray();
	console.log('Productos de joyería ordenados por rating: ', resultado);
}

async function totalResenas() {
	const db = client.db(dbName);
	const productos = db.collection('productos');
	const resultado = await productos.aggregate([
		{ $group: { _id: null, totalResenas: { $sum: '$rating.count' } } }
	]).toArray();
	console.log('Total de reseñas:', resultado[0].totalResenas);
}

async function puntuacionMediaPorCategoria() {
	const db = client.db(dbName);
	const productos = db.collection('productos');
	const resultado = await productos.aggregate([
		{ $group: { _id: '$category', puntuacionMedia: { $avg: '$rating.rate' } } }
	]).toArray();
	console.log('Puntuacion media por categoria de producto: ', resultado);
}

async function usuariosSinDigitosEnPassword() {
	const db = client.db(dbName);
	const usuarios = db.collection('usuarios');
	const resultado = await usuarios.find({ password: { $not: /\d/ } }).toArray();
	console.log('Usuarios sin digitos en el password: ', resultado);
}

async function Inserta_datos_en_coleccion (coleccion, url) {
	try{
		const datos = await fecth(url).then(res => res.json())
		return `${datos.length} datos traidos para ${coleccion}`
	} catch (err) {
		err.errorResponse += ` en fecth ${coleccion}`
		throw err
    	}
}

Inserta_datos_en_coleccion('productos', 'https://fakestoreapi.com/products')
	.then((r)=>console.log(`Todo bien: ${r}`))
	.then(()=>Inserta_datos_en_coleccion('usuarios','https://fakestoreapi.com/users'))
	.then((r)=>console.log(`Todo bien: ${r}`))1
	.catch((err)=>console.error('Algo mal: ', err.errorResponse))

console.log('Lo primero que pasa')
