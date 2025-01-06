import { MongoClient } from 'mongodb'
  
console.log( '🏁 seed.js ----------------->')

// del archivo .env
const USER_DB = process.env.USER_DB;
const PASS = process.env.PASS;
const DB_HOST = process.env.DB_HOST || 'localhost';
const PORT = process.env.PORT || '27017';
const DB = process.env.DB || 'myProject';

const url = `mongodb://${USER_DB}:${PASS}@${DB_HOST}:${PORT}/${DB}?authSource=admin`;
const client = new MongoClient(url);
  
// Database Name
const dbName = 'myProject';

async function productosMasDe100() {
	try {
		await client.connect();
		const db = client.db(dbName);
		const collection = db.collection("productos");
		const resultado = collection.find({ price: { $gt: 100 }, });
		console.log('Productos de más de 100$:');
		for await (const doc of resultado) {
			console.log(doc);
		}
	
    } finally {
		await client.close();
	}
}

async function productosWinterOrdenadosPorPrecio() {
	try {
		await client.connect();
		const db = client.db(dbName);
		const collection = db.collection("productos");
		const resultado = await collection.find({ description: /winter/i }).sort({ price: 1}).toArray();
		console.log("productos que contienen 'winter' en la descripcion ordenados por precio", resultado);
	
    } finally {
		await client.close();
	}
}

async function joyeriaOrdenadaPorRating() {
	try {
		await client.connect();
		const db = client.db(dbName);
		const collection = db.collection("productos");
		const resultado = await collection.find({ category: 'jewelery' }).sort({ 'rating.rate': -1 }).toArray();
		console.log('Productos de joyería ordenados por rating: ', resultado);
	
    } finally {
		await client.close();
	}
}

async function totalResenas() {
	try {
		await client.connect();
		const db = client.db(dbName);
		const collection = db.collection("productos");
		const resultado = await collection.aggregate([
			{ $group: { _id: null, totalResenas: { $sum: '$rating.count' } } }
		]).toArray();
		console.log('Total de reseñas:', resultado[0].totalResenas);
	
    } finally {
		await client.close();
	}
}

async function puntuacionMediaPorCategoria() {
	try {
		await client.connect();
		const db = client.db(dbName);
		const collection = db.collection("productos");
		const resultado = await collection.aggregate([
			{ $group: { _id: '$category', puntuacionMedia: { $avg: '$rating.rate' } } }
		]).toArray();
		console.log('Puntuacion media por categoria de producto: ', resultado);
	
    } finally {
		await client.close();
	}
}

async function usuariosSinDigitosEnPassword() {
	try {
		await client.connect();
		const db = client.db(dbName);
		const collection = db.collection("usuarios");
		const resultado = await collection.find({ password: { $not: /\d/ } }).toArray();
		console.log('Usuarios sin digitos en el password: ', resultado);
	
    } finally {
		await client.close();
	}
}
  
// función asíncrona
async function Inserta_datos_en_colección (colección, url) {
                                  
  try {
    const datos = await fetch(url).then(res => res.json())
    //console.log(datos)

    // ... Insertar datos en la BD aquí -> SOLO UNA VEZ
	// try{
	// 	await client.connect();
	// 	const db = client.db(dbName);
	// 	const coll = db.collection(colección)
	// 	const result = await coll.insertMany(datos);
	// 	console.log(result.insertedIds);

	// } finally {
	// 	await client.close();
	// }

	// ... Borrar datos en la BD aquí -> si has ejecutado lo anterior más de una vez
	// const db = client.db(dbName);
	// const coll = db.collection(colección)
	// const result = await coll.deleteMany({});

    return `${datos.length} datos traidos para ${colección}`

  } catch (err) {
      err.errorResponse += ` en fetch ${colección}`
      throw err    
  }
}
  
// Inserción consecutiva
Inserta_datos_en_colección('productos', 'https://fakestoreapi.com/products')
   .then((r)=>console.log(`Todo bien: ${r}`))                                 // OK
   .then(()=>productosMasDe100())
   .then(()=>productosWinterOrdenadosPorPrecio())
   .then(()=>joyeriaOrdenadaPorRating())
   .then(()=>totalResenas())
   .then(()=>puntuacionMediaPorCategoria())
   .then(()=>Inserta_datos_en_colección('usuarios', 'https://fakestoreapi.com/users'))
   .then((r)=>console.log(`Todo bien: ${r}`))                                // OK
   .then(()=>usuariosSinDigitosEnPassword())
   .catch((err)=>console.error('Algo mal: ', err.errorResponse))             // error
  

console.log('Lo primero que pasa')
